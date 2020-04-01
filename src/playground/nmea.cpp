// [[Rcpp::plugins(cpp17)]]
// [[Rcpp::plugins(openmp)]]

#include <Rcpp.h>
#include <omp.h>

// [[Rcpp::export]]
std::vector<uint8_t> calc_checksum(const std::vector<std::string>& x) {
  std::vector<uint8_t> out(x.size());

#pragma omp parallel for
  for (std::size_t i = 0; i < x.size(); ++i) {
    auto chr = x[i].c_str() + 1;
    uint8_t res = 0;
    while (*chr != '*' && *chr != '\r' && *chr != '\n' && *chr != '\0') {
      res ^= (uint8_t) * (chr++);
    }
    out[i] = res;
  }

  return out;
};

// fff[[Rcpp::export]]

std::vector<std::string> split_fields(const std::string_view& x) {
  const auto n_out = std::count_if(x.begin(), x.end(),
                                   [](const char& chr) { return chr == ','; });

  std::vector<std::string> out;
  out.reserve(n_out + 1);

  std::string element;
  std::stringstream sstream(std::string(x.begin(), x.end()));
  while (std::getline(sstream, element, ',')) {
    out.push_back(element);
  }

  return out;
}

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

//ff [[Rcpp::export()]]
bool is_valid(const std::string_view& x) {
  if (x.size() < 14 || x[0] != '!' || x[6] != ',') {
    return false;
  }

  const auto asterisk = std::find(x.begin(), x.end(), '*');
  if (asterisk == x.end()) {
    return false;
  }

  const uint8_t target_int =
      std::accumulate(x.begin() + 1, asterisk, 0, std::bit_xor<uint8_t>());

  std::stringstream target;
  target << std::hex << target_int;
  const std::string checksum_string(asterisk + 1, asterisk + 3);

  return target_int == strtol(checksum_string.c_str(), NULL, 16);
}

// [[Rcpp::export]]
std::vector<std::size_t> which_valid(const std::vector<std::string>& x) {
  std::vector<std::size_t> out;
  out.reserve(x.size());
  for (std::size_t i = 0; i < x.size(); ++i) {
    if (is_valid(std::string_view(x[i]))) {
      out.push_back(i);
    }
  }

  return out;
}

class NMEA {
  std::array<char, 5> talker;
  short fragment_count;
  short fragment_number;
  short message_id;
  char channel;
  std::array<char, 82> payload;
  short fill_bits;
  std::array<char, 2> checksum;

 public:
  NMEA()
      : talker({' '}),
        fragment_count(-1),
        fragment_number(-1),
        message_id(' '),
        channel(' '),
        payload({' '}),
        fill_bits(-1),
        checksum({' '}){};

  NMEA(const std::array<char, 5>& _talker,
       const short& _fragment_count,
       const short& _fragment_number,
       const short& _message_id,
       const char& _channel,
       const std::array<char, 82>& _payload,
       const short& _fill_bits,
       const std::array<char, 2>& _checksum)
      : talker(_talker),
        fragment_count(_fragment_count),
        fragment_number(_fragment_number),
        message_id(_message_id),
        channel(_channel),
        payload(_payload),
        fill_bits(_fill_bits),
        checksum(_checksum){};

  static NMEA from_split_string(const std::vector<std::string>& split) {
    std::array<char, 5> talker{' '};
    if (split[0].size() == 6) {
      talker[0] = split[0][1];
      talker[1] = split[0][2];
      talker[2] = split[0][3];
      talker[3] = split[0][4];
      talker[4] = split[0][5];
    }

    short fragment_count = -1;
    if (!split[1].empty()) {
      fragment_count = split[1][0] - 48;
    }
    short fragment_number = -1;
    if (!split[2].empty()) {
      fragment_number = split[2][0] - 48;
    }
    short message_id = -1;
    if (!split[3].empty()) {
      message_id = split[3][0] - 48;
    }
    char channel = ' ';
    if (!split[4].empty()) {
      channel = split[4][0];
    }

    std::array<char, 82> payload{' '};
    std::copy(split[5].begin(), split[5].end() - 1, payload.begin());

    short fill_bits = -1;
    std::array<char, 2> checksum{' '};
    if (split[6].size() == 4) {
      fill_bits = split[6][0] - 48;
      checksum[0] = split[6][2];
      checksum[1] = split[6][3];
    }

    return NMEA(talker, fragment_count, fragment_number, message_id, channel,
                payload, fill_bits, checksum);
  };
  Rcpp::CharacterVector as_vector() {
    return Rcpp::CharacterVector::create(                          //
        std::string(this->talker.begin(), this->talker.end()),     //
        Rcpp::String(this->fragment_count),                        //
        Rcpp::String(this->fragment_number),                       //
        Rcpp::String(this->message_id),                            //
        this->channel,                                             //
        std::string(this->payload.begin(), this->payload.end()),   //
        Rcpp::String(this->fill_bits),                             //
        std::string(this->checksum.begin(), this->checksum.end())  //
    );
  };

  static std::array<std::string, 8> col_names() {
    return std::array<std::string, 8>{
        "talker",  "fragment_count", "fragment_number", "message_id",
        "channel", "payload",        "fill_bits",       "checksum"};
  }

  static Rcpp::List dim_names() {
    return Rcpp::List::create(R_NilValue, col_names());
  }

  SEXP as_matrix(const bool col_names = true) const {
    Rcpp::CharacterMatrix out(1, 8);
    out[0] = std::string(this->talker.begin(), this->talker.end());
    out[1] = this->fragment_count;
    out[2] = this->fragment_number;
    out[3] = this->message_id;
    out[4] = this->channel;
    out[5] = std::string(this->payload.begin(), this->payload.end());
    out[6] = this->fill_bits;
    out[7] = std::string(this->checksum.begin(), this->checksum.end());

    if (col_names) {
      out.attr("dimnames") = Rcpp::List::create(R_NilValue, col_names);
    }

    return out;
  };
};

// [[Rcpp::export]]
SEXP test(const std::vector<std::string>& x) {
  const auto valid_indices = which_valid(x);

  std::vector<NMEA> valid_lines(valid_indices.size());
  std::vector<NMEA> res;
  res.reserve(x.size());
#pragma omp parallel for simd
  for (std::size_t i = 0; i < valid_indices.size(); ++i) {
    const auto split = split_fields(x[valid_indices[i]]);
    const auto nmea = NMEA::from_split_string(split);
    valid_lines[i] = nmea;
  }

//   Rcpp::CharacterMatrix r_out(valid_lines.size(), 8);
//   for (std::size_t i = 0; i < valid_lines.size(); ++i) {
//     const auto vec = valid_lines[i].as_vector();
//     r_out.row(i) = vec;
//   }
//   r_out.attr("dimnames") = NMEA::dim_names();
//   return r_out;
    return R_NilValue;
}


/*** R
# lines <-readr::read_lines("inst/example-data/big-files/20181219.log")
# unlisted <- stringi::stri_split_fixed(lines, ",", simplify = TRUE)
# max(nchar(unlisted))
# res <- test(lines)
# df <- data.table::rbindlist(res)
# mat <- do.call(rbind, res)
# res <- sapply(lines, test, USE.NAMES = FALSE)
# bench::mark(res <- test(lines))
# res <- test(lines)
*/
