#ifndef MARITIME_STREAM_HPP
#define MARITIME_STREAM_HPP

#include <Rcpp.h>

#include <algorithm>
#include <array>
#include <mio/mmap.hpp>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

#include "msg_type.hpp"
#include "openmp.hpp"
// #include "stdcompat.hpp"

// inline bool is_valid(const std::string& x) noexcept {
//   if (x.size() < 14 || x[0] != '!' || x[6] != ',') {
//     return false;
//   }

//   const auto asterisk = std::find(std::begin(x), std::end(x), '*');
//   if (asterisk == std::end(x)         //
//       || asterisk + 1 == std::end(x)  //
//       || asterisk + 2 == std::end(x)) {
//     return false;
//   }

//   const uint8_t target_checksum =
//       std::strtol(std::string(asterisk + 1, asterisk + 3).c_str(), nullptr,
//       16);

//   const uint8_t test_checksum =
//       std::accumulate(std::begin(x) + 1, asterisk, 0,
//       std::bit_xor<uint8_t>());

//   return target_checksum == test_checksum;
// }

struct Payload {
  std::string data;
  Payload() = default;
  Payload(const std::string& x) : data(x){};
  std::string to_string() const { return this->data; };
};

static inline void rstrip(std::string& x) {
  x.erase(                                         //
      std::remove_if(                              //
          std::begin(x), std::end(x),              //
          [](char& c) { return std::isspace(c); }  //
          ),                                       //
      std::end(x));
}

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

class NMEA {
 public:
  Payload payload;
  Talker talker;
  std::size_t line_number;
  short fragment_count;
  short fragment_number;
  short message_id;
  char channel;
  short fill_bits;
  char checksum[2];
  double time_start;
  double time_end;

 public:
  NMEA() = default;

  bool are_same_sentence(const NMEA& rhs) const noexcept;

  static NMEA from_string(const std::string line,
                          const std::size_t line_number) noexcept;

  SEXP as_list() const;
};

//
//
// NMEA implementations
// ====================================================================
inline bool NMEA::are_same_sentence(const NMEA& rhs) const noexcept {
  return this->line_number == rhs.line_number - 1       //
         && this->message_id == rhs.message_id          //
         && this->fragment_count == rhs.fragment_count  //
         && this->channel == rhs.channel                //
         && this->talker.to_string() == rhs.talker.to_string();
};

inline NMEA NMEA::from_string(const std::string line,
                              const std::size_t line_number) noexcept {
  constexpr std::size_t n_split = 10;
  std::vector<std::string> split(n_split);
  std::size_t split_count = 0;
  std::string element;
  std::stringstream sstream(line);
  while (std::getline(sstream, element, ',') && split_count < n_split) {
    split[split_count++] = element;
  }

  //   vec_chr to_print(n_split);
  //   for (std::size_t i = 0; i < n_split; ++i) {
  //       to_print[i] = split[i];
  //   }
  //   Rcpp::print(to_print);

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

  if (!split[7].empty()) {
    if (std::all_of(split[7].begin(), split[7].end(), ::isdigit)) {
      out.time_start = std::stoll(split[7].data());
    }

    if (!split[8].empty()) {
      if (std::all_of(split[8].begin(), split[8].end(), ::isdigit)) {
        out.time_end = std::stoll(split[8].data());
      }
    }
  }

  return out;
};

inline SEXP NMEA::as_list() const {
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

//
//
// NMEA_Stream =========================================================

class NMEA_Stream {
 public:
  std::vector<NMEA> complete;
  std::vector<NMEA> incomplete;

  NMEA_Stream() = default;

  NMEA_Stream(const std::size_t approx_size) {
    this->complete.reserve(approx_size);
    this->incomplete.reserve(20);
  };

  void push(const NMEA& nmea);

  std::map<MSG_TYPE, std::size_t> count_msg_types() const;

  SEXP as_df(const int n_max) const;

  static NMEA_Stream from_file(const std::string& file_path);
};

//
//
// NMEA_Stream implementations
// =======================================================

inline void NMEA_Stream::push(const NMEA& nmea) {
  if (nmea.fragment_count == 1) {
    complete.push_back(nmea);
    return;
  }

  if (this->incomplete.size() == 0) {
    incomplete.push_back(nmea);
    return;
  }

  if (!incomplete.back().are_same_sentence(nmea)) {
    incomplete.clear();
    incomplete.push_back(nmea);
    return;
  }

  if (nmea.fragment_count != nmea.fragment_number) {
    incomplete.push_back(nmea);
    return;
  }

  incomplete.push_back(nmea);
  std::string final_payload;
  for (const auto& val : incomplete) {
    final_payload += val.payload.data;
  }

  NMEA combo_nmea;
  combo_nmea.line_number = -1;
  combo_nmea.talker = incomplete.back().talker;
  combo_nmea.fragment_count = incomplete.back().fragment_count;
  combo_nmea.fragment_number = -1;
  combo_nmea.message_id = incomplete.back().message_id;
  combo_nmea.channel = incomplete.back().channel;
  combo_nmea.payload.data = final_payload;
  combo_nmea.fill_bits = incomplete.back().fill_bits;

  combo_nmea.time_start = incomplete.back().time_start;
  combo_nmea.time_end = incomplete.back().time_end;

  complete.push_back(combo_nmea);
  incomplete.clear();
};

inline SEXP NMEA_Stream::as_df(const int n_max) const {
  const auto max_rows = this->complete.size();
  std::size_t n_rows;
  if (n_max == -1) {
    n_rows = max_rows;
  } else if (static_cast<std::size_t>(n_max) > max_rows) {
    n_rows = max_rows;
  } else {
    n_rows = static_cast<std::size_t>(n_max);
  }

  vec_int _line_number(n_rows);
  vec_chr _talker(n_rows);
  vec_int _fragment_count(n_rows);
  vec_int _fragment_number(n_rows);
  vec_int _message_id(n_rows);
  vec_chr _channel(n_rows);
  vec_chr _payload(n_rows);
  vec_int _fill_bits(n_rows);

  vec_dbl _time_start(n_rows);
  _time_start.attr("class") = vec_chr{"POSIXct", "POSIXt"};
  _time_start.attr("tzone") = "UTC";
  vec_dbl _time_end(n_rows);
  _time_end.attr("class") = vec_chr{"POSIXct", "POSIXt"};
  _time_end.attr("tzone") = "UTC";

  for (std::size_t i = 0; i < n_rows; ++i) {
    if (i % 1000 == 0) {
      R_CheckUserInterrupt();
    }
    _line_number[i] = this->complete[i].line_number;
    _talker[i] = this->complete[i].talker.to_string();
    _fragment_count[i] = this->complete[i].fragment_count;
    _fragment_number[i] = this->complete[i].fragment_number;
    _message_id[i] = this->complete[i].message_id;
    _channel[i] = std::string(1, this->complete[i].channel);
    _payload[i] = this->complete[i].payload.to_string();
    _fill_bits[i] = this->complete[i].fill_bits;
    _time_start[i] = this->complete[i].time_start;
    _time_end[i] = this->complete[i].time_end;
  }

  using Rcpp::_;
  auto out = Rcpp::List::create(                //
      _["line_number"] = _line_number,          //
      _["talker"] = _talker,                    //
      _["fragment_count"] = _fragment_count,    //
      _["fragment_number"] = _fragment_number,  //
      _["message_id"] = _message_id,            //
      _["channel"] = _channel,                  //
      _["payload"] = _payload,                  //
      _["fill_bits"] = _fill_bits,              //
      _["time_start"] = _time_start,            //
      _["time_end"] = _time_end                 //
  );

  out.attr("row.names") = Rcpp::seq_len(n_rows);
  out.attr("class") = "data.frame";

  return out;
};

inline NMEA_Stream NMEA_Stream::from_file(const std::string& file_path) {
  constexpr std::size_t init_line_size = 110;
  constexpr auto delim = '\n';

  std::error_code error;
  mio::mmap_source mmap;
  mmap.map(file_path, error);
  if (error) {
    Rcpp::stop("mmap error");
  }

  const auto file_size = mmap.size();

  //   `valid_lines` index into `offsets`, which index into `mmap`

  std::vector<std::size_t> offsets;
  offsets.reserve(file_size / init_line_size);
  offsets.push_back(0);
  // ^^^^^^^^^^^^^^^^^^ 1st line's 1st char
  //                    `n_lines` is size(offsets) - 1
  for (std::size_t i = 0; i < file_size; ++i) {
    if (mmap[i] == delim) {
      offsets.push_back(i + 1);
      //                ^^^^^^
      //                  \n + 1: 1st character on subsequent lines
    }
  }

  const auto n_lines = offsets.size() - 1;
  std::vector<std::size_t> which_valid;
  which_valid.reserve(n_lines);

  for (std::size_t i = 0; i < n_lines; ++i) {
    const auto first_chr = mmap.begin() + offsets[i];
    const auto last_chr = mmap.begin() + offsets[i + 1];
    // const auto last_chr = mmap.begin() + offsets[i + 1] - 1;
    //                                                 ^^^^^
    //                  standard: lines end with \r\n (-2), but not necessarily
    //                  `rstrip(line)` before pushing
    std::string line(first_chr, last_chr);
    if (is_valid(line)) {
      which_valid.push_back(i);
    }
  }

  const auto n_messages = which_valid.size() - 1;
  std::vector<NMEA> messages(n_messages);
#pragma omp parallel for
  for (std::size_t i = 0; i < n_messages; ++i) {
    const auto first_chr = mmap.begin() + offsets[which_valid[i]];
    const auto last_chr = mmap.begin() + offsets[which_valid[i + 1]];
    // const auto last_chr = mmap.begin() + offsets[which_valid[i + 1]] - 1;
    std::string line(first_chr, last_chr);
    rstrip(line);
    const auto nmea = NMEA::from_string(line, i);
    messages[i] = nmea;
  }

  mmap.unmap();

  NMEA_Stream out(n_messages);
  for (const auto& nmea : messages) {
    out.push(nmea);
  }

  return out;
}

// inline std::map<MSG_TYPE, std::size_t> NMEA_Stream::count_msg_types() const {
//   std::map<MSG_TYPE, std::size_t> out{
//       {MSG_TYPE::unknown, 0}, {MSG_TYPE::msg_1_2_3, 0}, {MSG_TYPE::msg_4_11,
//       0}, {MSG_TYPE::msg_5, 0},   {MSG_TYPE::msg_6, 0}, {MSG_TYPE::msg_7_13,
//       0}, {MSG_TYPE::msg_8, 0},   {MSG_TYPE::msg_9, 0}, {MSG_TYPE::msg_10,
//       0}, {MSG_TYPE::msg_11, 0},  {MSG_TYPE::msg_12, 0}, {MSG_TYPE::msg_14,
//       0}, {MSG_TYPE::msg_15, 0},  {MSG_TYPE::msg_16, 0}, {MSG_TYPE::msg_17,
//       0}, {MSG_TYPE::msg_18, 0},  {MSG_TYPE::msg_19, 0}, {MSG_TYPE::msg_20,
//       0}, {MSG_TYPE::msg_21, 0},  {MSG_TYPE::msg_22, 0}, {MSG_TYPE::msg_23,
//       0}, {MSG_TYPE::msg_24, 0},  {MSG_TYPE::msg_25, 0}, {MSG_TYPE::msg_26,
//       0}, {MSG_TYPE::msg_27, 0}  //
//   };

// #pragma omp parallel for reduction(+ : out)
//   for (std::size_t i = 0; i < this->complete.size(); ++i) {
//     out[get_msg_type(this->complete[i].payload)]++;
//   }

//   return out;
// }

//
#endif
