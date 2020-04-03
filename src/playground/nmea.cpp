// [[Rcpp::plugins(cpp17)]]
// [[Rcpp::plugins(openmp)]]

// [[Rcpp::depends(rmio)]]

#include <Rcpp.h>
#include <omp.h>

#include <mio/mmap.hpp>

// fff// [[Rcpp::export]]
// std::vector<uint8_t> calc_checksum(const std::vector<std::string>& x) {
//   std::vector<uint8_t> out(x.size());

// #pragma omp parallel for
//   for (std::size_t i = 0; i < x.size(); ++i) {
//     auto chr = x[i].c_str() + 1;
//     uint8_t res = 0;
//     while (*chr != '*' && *chr != '\r' && *chr != '\n' && *chr != '\0') {
//       res ^= (uint8_t) * (chr++);
//     }
//     out[i] = res;
//   }

//   return out;
// };

// fff[[Rcpp::export]]

// std::vector<std::string> split_fields(const std::string& x) {
//   const auto n_out = std::count_if(x.begin(), x.end(),
//                                    [](const char& chr) { return chr == ',';
//                                    });

//   std::vector<std::string> out;
//   out.reserve(n_out + 1);

//   std::string element;
//   std::stringstream sstream(std::string(x.begin(), x.end()));
//   while (std::getline(sstream, element, ',')) {
//     out.push_back(element);
//   }

//   return out;
// }

// std::vector<std::string> split_fields(const std::string& x) {
//   // const auto n_out = std::count_if(x.begin(), x.end(),
//   //  [](const char& chr) { return chr == ','; });

//   std::vector<std::string> out(8, "");
//   // out.reserve(n_out + 1);

//   int count = 0;
//   std::string element;
//   std::stringstream sstream(std::string(x.begin(), x.end()));
//   while (std::getline(sstream, element, ',') && count < 8) {
//     out[count++] = element;
//   }

//   return out;
// }

// // ff[[Rcpp::export()]]
// bool is_valid_checksum(const std::string& x) {
//   if (x.size() < 3 || x[0] != '!') {
//     return false;
//   }
//   const auto asterisk = std::find(x.begin(), x.end(), '*');
//   if (asterisk == x.end()) {
//     return false;
//   }

//   const uint8_t target_int =
//       std::accumulate(x.begin() + 1, asterisk, 0, std::bit_xor<uint8_t>());

//   std::stringstream target;
//   target << std::hex << target_int;
//   const std::string checksum_string(asterisk + 1, asterisk + 3);

//   return target_int == strtol(checksum_string.c_str(), NULL, 16);
// }

// // [[Rcpp::export]]
// std::vector<bool> is_valid_checksum2(const std::vector<std::string>& x) {
//   const auto n = x.size();
//   std::vector<bool> out(n);

//   // #pragma omp parallel for
//   for (std::size_t i = 0; i < n; ++i) {
//     // #pragma omp critical
//     out[i] = is_valid_checksum(x[i]);
//   }

//   return out;
// }

// constexpr const uint8_t target_checksum(
//     const std::string::const_iterator& begin,
//     const std::string::const_iterator& end) {
//   return std::accumulate(begin + 1, end, 0, std::bit_xor<uint8_t>());
// }

// constexpr const uint8_t test_checksum(
//     const std::string::const_iterator& begin,
//     const std::string::const_iterator& end) {
//       return
//   return std::accumulate(begin + 1, end, 0, std::bit_xor<uint8_t>());
// }

// ff [[Rcpp::export()]]
bool is_valid(const std::string& x) noexcept {
  if (x.size() < 14 || x[0] != '!' || x[6] != ',') {
    return false;
  }

  const auto asterisk = std::find(x.begin(), x.end(), '*');
  if (asterisk == x.end() || asterisk + 1 == x.end() ||
      asterisk + 2 == x.end()) {
    return false;
  }

  const uint8_t target_checksum =
      std::accumulate(x.begin() + 1, asterisk, 0, std::bit_xor<uint8_t>());

  const uint8_t test_checksum =
      std::strtol(std::string(asterisk + 1, asterisk + 3).c_str(), nullptr, 16);

  return target_checksum == test_checksum;
}

// // ff[[Rcpp::export]]
// std::vector<std::size_t> which_valid(const std::vector<std::string>& x) {
//   std::vector<std::size_t> out;
//   out.reserve(x.size());
//   for (std::size_t i = 0; i < x.size(); ++i) {
//     if (is_valid(std::string(x[i]))) {
//       out.push_back(i);
//     }
//   }

//   return out;
// }

struct Talker {
  char data[6];
  Talker() = default;
  Talker(const std::string& x) noexcept {
    if (x.size() == 6) {
      this->data[0] = x[1];
      this->data[1] = x[2];
      this->data[2] = x[3];
      this->data[3] = x[4];
      this->data[4] = x[5];
      this->data[5] = '\0';
    }
  }
  std::string to_string() const {
    return std::string(std::begin(this->data), std::end(this->data));
  }
};

struct Payload {
  std::string data;
  Payload() = default;
  Payload(const std::string& x) : data(x){};
  std::string to_string() const { return this->data; };
};

// inline bool operator==(const Talker& lhs, const Talker& rhs) {
//   return lhs.data == rhs.data;
// }
// inline bool operator==(const Payload& lhs, const Payload& rhs) {
//   return lhs.data == rhs.data;
// }

class NMEA {
 public:
  // std::string line;
  Payload payload;
  Talker talker;
  std::size_t line_number;
  short fragment_count;
  short fragment_number;
  short message_id;
  char channel;
  short fill_bits;
  char checksum[2];

 public:
  NMEA() = default;

  bool are_same_sentence(const NMEA& rhs) const noexcept {
    return this->line_number == rhs.line_number - 1       //
           && this->message_id == rhs.message_id          //
           && this->fragment_count == rhs.fragment_count  //
           && this->channel == rhs.channel                //
           && std::string(this->talker.data) == std::string(rhs.talker.data);
  };

  static NMEA from_string(const std::string line,
                          const std::size_t line_number) noexcept {
    std::vector<std::string> split(8, "");
    int count = 0;
    std::string element("", 1);
    std::stringstream sstream(line);
    while (std::getline(sstream, element, ',') && count < 8) {
      split[count++] = element;
    }

    NMEA out;

    out.line_number = line_number;
    out.talker = Talker(split[0]);
    if (!split[1].empty()) {
      out.fragment_count = split[1][0] - 48;
    }
    if (!split[2].empty()) {
      out.fragment_number = split[2][0] - 48;
    }
    if (!split[3].empty()) {
      out.message_id = split[3][0] - 48;
    }
    if (!split[4].empty()) {
      out.channel = split[4][0];
    }

    out.payload = split[5];

    if (split[6].size() == 4) {
      out.fill_bits = split[6][0] - 48;
      out.checksum[0] = split[6][2];
      out.checksum[1] = split[6][3];
    }

    return out;
  };

  SEXP as_list() const {
    using Rcpp::_;
    return Rcpp::List::create(                         //
        _["line_number"] = this->line_number,          //
        _["talker"] = this->talker.to_string(),        //
        _["fragment_count"] = this->fragment_count,    //
        _["fragment_number"] = this->fragment_number,  //
        _["message_id"] = this->message_id,            //
        _["channel"] = this->channel,                  //
        _["to_string"] = this->payload.to_string(),    //
        _["fill_bits"] = this->fill_bits,              //
        _["checksum"] = this->checksum                 //
    );
  }
};

class NMEA_rowise {
 public:
  std::vector<NMEA> data;
  std::vector<NMEA> waiting;

 public:
  NMEA_rowise(const std::size_t approx_size) {
    this->data.reserve(approx_size);
  };

  void push(const NMEA& nmea) {
    if (nmea.fragment_count == 1) {
      data.push_back(nmea);
      return;
    }

    if (this->waiting.size() == 0) {
      waiting.push_back(nmea);
      return;
    }

    if (!waiting.back().are_same_sentence(nmea)) {
      waiting.clear();
      waiting.push_back(nmea);
      return;
    }

    if (nmea.fragment_count != nmea.fragment_number) {
      waiting.push_back(nmea);
      return;
    }

    std::string final_payload;
    for (const auto& val : waiting) {
      final_payload += val.payload.data;
    }

    NMEA combo_nmea;
    combo_nmea.line_number = -1;
    combo_nmea.talker = waiting.back().talker;
    combo_nmea.fragment_count = waiting.back().fragment_count;
    combo_nmea.fragment_number = -1;
    combo_nmea.message_id = waiting.back().message_id;
    combo_nmea.channel = waiting.back().channel;
    combo_nmea.payload.data = final_payload;
    combo_nmea.fill_bits = waiting.back().fill_bits;

    data.push_back(combo_nmea);
    waiting.clear();
  };

  SEXP as_df() const {
    const auto n_rows = this->data.size();
    // Rcpp::CharacterVector _line(n_rows);
    Rcpp::IntegerVector _line_number(n_rows);
    Rcpp::CharacterVector _talker(n_rows);
    Rcpp::IntegerVector _fragment_count(n_rows);
    Rcpp::IntegerVector _fragment_number(n_rows);
    Rcpp::IntegerVector _message_id(n_rows);
    Rcpp::CharacterVector _channel(n_rows);
    Rcpp::CharacterVector _payload(n_rows);
    Rcpp::IntegerVector _fill_bits(n_rows);

    for (std::size_t i = 0; i < n_rows; ++i) {
      // _line[i] = this->data[i].line;
      _line_number[i] = this->data[i].line_number;
      _talker[i] = this->data[i].talker.to_string();
      _fragment_count[i] = this->data[i].fragment_count;
      _fragment_number[i] = this->data[i].fragment_number;
      _message_id[i] = this->data[i].message_id;
      _channel[i] = std::string(1, this->data[i].channel);
      _payload[i] = this->data[i].payload.data;
      _fill_bits[i] = this->data[i].fill_bits;
    }

    using Rcpp::_;
    auto out = Rcpp::List::create(                //
                                                  // _["line"] = _line,
        _["line_number"] = _line_number,          //
        _["talker"] = _talker,                    //
        _["fragment_count"] = _fragment_count,    //
        _["fragment_number"] = _fragment_number,  //
        _["message_id"] = _message_id,            //
        _["channel"] = _channel,                  //
        _["payload"] = _payload,                  //
        _["fill_bits"] = _fill_bits               //
    );
    out.attr("row.names") = Rcpp::seq_len(n_rows);
    out.attr("class") = "data.frame";

    return out;
  };
  //
};

// fff[[Rcpp::export]]
// SEXP test(const std::vector<std::string>& x, const bool return_null = true) {
//   const auto valid_indices = which_valid(x);
//   std::vector<NMEA> valid_lines(valid_indices.size());

// #pragma omp parallel for
//   for (std::size_t i = 0; i < valid_indices.size(); ++i) {
//     const auto nmea = NMEA::from_string(x[valid_indices[i]], i);
//     valid_lines[i] = nmea;
//   }

//   if (return_null) {
//     return R_NilValue;
//   }
//   Rcpp::CharacterMatrix r_out(valid_lines.size(), 9);
//   for (std::size_t i = 0; i < valid_lines.size(); ++i) {
//     const auto vec = valid_lines[i].as_vector();
//     r_out.row(i) = vec;
//   }
//   r_out.attr("dimnames") = NMEA::dim_names();
//   return r_out;
// }

// #include <fstream>

// [[Rcpp::export]]
bool test() {
  return std::string("AIVDM") == std::string("AIVDM");
}

// [[Rcpp::export]]
SEXP test2(const std::string& file_path, const bool return_null = true) {
  constexpr std::size_t init_line_size = 110;
  constexpr auto delim = '\n';

  std::error_code error;
  mio::mmap_source mmap;
  mmap.map(file_path, error);
  if (error) {
    Rcpp::stop("mmap error");
  }

  const auto file_size = mmap.size();

  std::vector<std::size_t> offsets;
  offsets.reserve(file_size / init_line_size);
  offsets.push_back(0);  // first character of first line
  for (std::size_t i = 0; i < file_size; ++i) {
    if (mmap[i] == delim) {
      offsets.push_back(i + 1);  // first character of subsequent lines
    }
  }

  const auto n_lines = offsets.size() - 1;
  std::vector<std::size_t> which_valid;
  which_valid.reserve(n_lines);

  for (std::size_t i = 0; i < n_lines; ++i) {
    const auto first_chr = mmap.begin() + offsets[i];
    const auto last_chr = mmap.begin() + offsets[i + 1] - 2;  // -\r\n
    const std::string line(first_chr, last_chr);
    if (is_valid(line)) {
      which_valid.push_back(i);
    }
  }

  const auto n_messages = which_valid.size() - 1;
  std::vector<NMEA> messages(n_messages);
#pragma omp parallel for
  for (std::size_t i = 0; i < n_messages; ++i) {
    const auto first_chr = mmap.begin() + offsets[which_valid[i]];
    const auto last_chr = mmap.begin() + offsets[which_valid[i + 1]] - 2;
    const std::string line(first_chr, last_chr);
    const auto nmea = NMEA::from_string(line, i);
    messages[i] = nmea;
  }

  mmap.unmap();

  NMEA_rowise res(n_messages);
  for (const auto& nmea : messages) {
    res.push(nmea);
  }

  Rcpp::Rcout << res.data.size() << std::endl;

  if (return_null) {
    return R_NilValue;
  }

  return res.as_df();
}

/*** R
file_path <- "inst/example-data/big-files/20181219.log"
# lines <- readr::read_lines("inst/example-data/big-files/20181219.log")
# lines <- readr::read_file("inst/example-data/big-files/20181219.log")
# unlisted <- stringi::stri_split_fixed(lines, ",", simplify = TRUE) #
# res <- test2(file_path, return_null = FALSE)
# tibble::as_tibble(res)
# res <- test2("inst/example-data/big-files/20181210.log",
             # return_null = FALSE)
# max(nchar(unlisted))
# res <- test2(file_path, return_null = FALSE)
# res <- test(lines[1:100], return_null = FALSE)

# df <- data.table::rbindlist(res) #

# mat <- do.call(rbind, res) # res <- sapply(lines, test, USE.NAMES = FALSE) #

bench::mark(res <- test2(file_path, return_null = TRUE),
            iterations = 3)


# res <- test(lines[1:10], return_null = FALSE)
*/
