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

// #define MIN_SENTENCE_SIZE  (long)21;
// #define MAX_SENTENCE_SIZE 120
// #define std::size_t MAX_PAYLOAD_SIZE = 80;

constexpr long MIN_SENTENCE_SIZE = 21;
constexpr std::size_t MAX_SENTENCE_SIZE = 120;
constexpr std::size_t MAX_PAYLOAD_SIZE = 80;

class Sentence {
 public:
  std::array<char, MAX_SENTENCE_SIZE> data{'\0'};
  std::size_t line_number;

  Sentence() = default;

  Sentence(const char* first,
           const char* last,
           const std::size_t _line_number) noexcept
      : line_number(_line_number) {
    std::size_t i = 0;
    std::copy_if(                                                            //
        std::make_move_iterator(first), std::make_move_iterator(last),       //
        std::begin(this->data),                                              //
        [&i](const char c) { return i++ < MAX_SENTENCE_SIZE && c != '\r'; }  //
    );
  };

  Sentence(const char* first, const char* last) noexcept {
    std::size_t i = 0;
    std::copy_if(                                                            //
        std::make_move_iterator(first), std::make_move_iterator(last),       //
        std::begin(this->data),                                              //
        [&i](const char c) { return i++ < MAX_SENTENCE_SIZE && c != '\r'; }  //
    );
  };

  Sentence(std::string&& x, const std::size_t _line_number) noexcept
      : line_number(_line_number) {
    std::move(std::begin(x), std::end(x), std::begin(this->data));
  };

  std::string to_string() const {
    return std::string(std::begin(this->data), std::end(this->data));
  };

  const char* c_str() const { return std::begin(this->data); };

  bool is_valid() const noexcept {
    if (this->data[0] != '!' || this->data[6] != ',') {
      return false;
    }

    auto asterisk_it = std::begin(this->data);
    const auto it_end = std::end(this->data);
    while (                       //
        *asterisk_it != '*'       //
        && *asterisk_it != '\0'   //
        && asterisk_it != it_end  //
    ) {
      // if (*asterisk_it == '*') {
      //   break;
      // }
      asterisk_it++;
    }

    // const auto it_pos = asterisk_it - std::begin(this->data);
    if (*asterisk_it != '*'                                          //
        || asterisk_it - std::begin(this->data) < MIN_SENTENCE_SIZE  //
        || asterisk_it + 1 == it_end                                 //
        || asterisk_it + 2 == it_end) {
      return false;
    }

    // `*asterisk_it` should now be `'*'`
    // if (asterisk_it + 1 == it_end || asterisk_it + 2 == it_end) {
    //   return false;
    // }

    // const uint8_t target_checksum = std::accumulate(  //
    //     std::begin(this->data) + 1, asterisk_it,      //
    //     0,                                            //
    //     std::bit_xor<uint8_t>()                       //
    // );                                                //

    // char checksum[3] = {
    //     *(asterisk_it + 1),  //
    //     *(asterisk_it + 2),  //
    //     '\0'                 //
    // };

    // const uint8_t test_checksum = std::strtol(checksum, nullptr, 16);

    // return target_checksum == test_checksum;
    return                                                              //
        std::accumulate(                                                //
            std::begin(this->data) + 1, asterisk_it,                    //
            (uint8_t)0,                                                 //
            std::bit_xor<uint8_t>()                                     //
            )                                                           //
        ==                                                              //
        (uint8_t)std::strtol(                                           //
            std::begin(                                                 //
                (const char[]){*(asterisk_it + 1), *(asterisk_it + 2)}  //
                ),                                                      //
            nullptr, 16                                                 //
        );                                                              //
  }
};

struct Payload {
  std::array<char, MAX_PAYLOAD_SIZE> data{'\0'};

  Payload() = default;

  Payload(std::string&& x) {
    std::move(std::begin(x), std::end(x),  //
              std::begin(this->data));
  };

  std::string to_string() const {
    return std::string(std::begin(this->data), std::end(this->data));
  };

  const char* c_str() const { return std::begin(this->data); };
};

// static inline void rstrip(std::string& x) {
//   x.erase(                                         //
//       std::remove_if(                              //
//           std::begin(x), std::end(x),              //
//           [](char& c) { return std::isspace(c); }  //
//           ),                                       //
//       std::end(x)                                  //
//   );
// }

struct Talker {
  char data[3];

  Talker() = default;

  Talker(const char* x) noexcept {
    // if (x.size() == 6) {
    this->data[0] = x[1];
    this->data[1] = x[2];
    this->data[2] = '\0';
    // this->data[2] = x[3];
    // this->data[3] = x[4];
    // this->data[4] = x[5];
    // this->data[5] = '\0';
    // }
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
  // double time_end;

 public:
  NMEA() = default;

  NMEA(const Payload& _payload,
       const Talker& _talker,
       const std::size_t _line_number,
       const short _fragment_count,
       const short _fragment_number,
       const short _message_id,
       const char _channel,
       const short _fill_bits,
       const char _checksum1,
       const char _checksum2,
       const double _time_start)
  //  const double _time_end)
  noexcept
      : payload(_payload),
        talker(_talker),
        line_number(_line_number),
        fragment_count(_fragment_count),
        message_id(_message_id),
        channel(_channel),
        fill_bits(_fill_bits),
        time_start(_time_start) {
    // time_end(_time_end) {
    checksum[0] = _checksum1;
    checksum[1] = _checksum2;
  };

  // NMEA(const char* begin, const char* end, const std::size_t line_number)
  // noexcept;
  NMEA(Sentence&&) noexcept;

  bool are_same_sentence(const NMEA& rhs) const noexcept;

  // static NMEA from_string(const std::string line,
  // const std::size_t line_number) noexcept;

  SEXP as_list() const;
};

//
//
// NMEA implementations
// ====================================================================
inline bool NMEA::are_same_sentence(const NMEA& rhs) const noexcept {
  return //this->line_number == rhs.line_number - 1       //
        //  && 
         this->message_id == rhs.message_id          //
         && this->fragment_count == rhs.fragment_count  //
         && this->channel == rhs.channel                //
         && this->talker.data[0] == rhs.talker.data[0]  //
         && this->talker.data[1] == rhs.talker.data[1];
}

inline NMEA::NMEA(Sentence&& x) noexcept
    : line_number(x.line_number), time_start(NA_REAL) {
  constexpr short n_split = 9;

  std::array<std::string, n_split> split;
  std::size_t split_count = 0;
  std::string element;

  std::stringstream sstream(x.c_str());
  while (std::getline(sstream, element, ',') && split_count < n_split) {
    split[split_count++] = element;
  }

  this->talker = Talker(split[0].c_str());
  // if (!split[1].empty()) {
  this->fragment_count = split[1][0] - '0';
  // }
  // if (!split[2].empty()) {
  this->fragment_number = split[2][0] - '0';
  // }
  if (!split[3].empty()) {
    this->message_id = split[3][0] - '0';
  }
  // if (!split[4].empty()) {
  this->channel = split[4][0];
  // }

  this->payload = std::move(split[5]);

  if (split[6].size() == 4) {
    this->fill_bits = split[6][0] - '0';
    this->checksum[0] = split[6][2];
    this->checksum[1] = split[6][3];
  }

  if (split[7].size() >= 10  //
      && std::all_of(split[7].begin(), split[7].end(), ::isdigit)) {
    this->time_start = std::stoll(split[7].data());

    // if (split[8].size() >= 10  //
    //     && std::all_of(split[8].begin(), split[8].end(), ::isdigit)) {
    //   this->time_end = std::stoll(split[8].data());
    // }
  }

  // this->time_start = NA_REAL;
  // this->time_end = NA_REAL;
  // }

  // return out;
}

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

// ======================================================================
struct NMEA_w_time {
  Payload payload;
  short fill_bits;
  std::size_t line_number;
  double time;

  NMEA_w_time(NMEA&& nmea)
      : payload(nmea.payload),
        fill_bits(nmea.fill_bits),
        line_number(nmea.line_number),
        time(nmea.time_start){};
  NMEA_w_time(Payload&& _payload,
              const short _fill_bits,
              const std::size_t _line_number,
              const double _time_start)
      : payload(_payload),
        fill_bits(_fill_bits),
        line_number(_line_number),
        time(_time_start){};
};

//
//
// NMEA_Stream =========================================================

inline MSG_TYPE get_msg_type2(const Payload& payload) {
  switch (payload.data[0]) {
    case '1':  // class A position
    case '2':
    case '3':
      return MSG_TYPE::msg_1_2_3;

    case '4':  // 4: basestation report
    case ';':  // 11: UTC date response
      return MSG_TYPE::msg_4_11;

    case '5':  // 5: ship and cargo
      return MSG_TYPE::msg_5;

    case '6':  // 6 - Addressed binary message
      return MSG_TYPE::msg_6;

    case '7':  // FALLTHROUGH - 7 - ACK for addressed binary message
    case '=':  // 13 - ASRM Ack  (safety message)
      return MSG_TYPE::msg_7_13;

    case '8':  // 8 - Binary broadcast message (BBM)
      return MSG_TYPE::msg_8;

    case '9':  // 9 - SAR Position
      return MSG_TYPE::msg_9;

    case ':':  // 10 - UTC Query
      return MSG_TYPE::msg_10;

      // ';' 11 - See 4

    case '<':  // 12 - ASRM
      return MSG_TYPE::msg_12;

      // 13 - See 7

    case '>':  // 14 - SRBM - Safety broadcast
      return MSG_TYPE::msg_14;

    case '?':  // 15 - Interrogation
      return MSG_TYPE::msg_15;

    case '@':  // 16 - Assigned mode command
      return MSG_TYPE::msg_16;

    case 'A':  // 17 - GNSS broadcast
      return MSG_TYPE::msg_17;

    case 'B':  // 18 - Position, Class B
      return MSG_TYPE::msg_18;

    case 'C':  // 19 - Position and ship, Class B
      return MSG_TYPE::msg_19;

    case 'D':  // 20 - Data link management
      return MSG_TYPE::msg_20;

    case 'E':  // 21 - Aids to navigation report
      return MSG_TYPE::msg_21;

    case 'F':  // 22 - Channel Management
      return MSG_TYPE::msg_22;

    case 'G':  // 23 - Group Assignment Command
      return MSG_TYPE::msg_23;

    case 'H':  // 24 - Static data report
      return MSG_TYPE::msg_24;

    case 'I':  // 25 - Single slot binary message - addressed or broadcast
      return MSG_TYPE::msg_25;

    case 'J':  // 26 - Multi slot binary message with comm state
      return MSG_TYPE::msg_26;

    case 'K':  // 27 - Long-range AIS broadcast message
      return MSG_TYPE::msg_27;

      // case 'L':  // 28 - UNKNOWN
      //   return MSG_TYPE::unknown;
      //   break;

    default:
      return MSG_TYPE::unknown;
  }
}

class NMEA_Stream {
 public:
  // std::vector<NMEA_w_time> complete;
  std::vector<NMEA> incomplete;
  std::vector<NMEA_w_time> m_1_2_3;
  std::vector<NMEA_w_time> m_4_11;
  std::vector<NMEA_w_time> m_5;
  // std::vector<NMEA_w_time> m_6;
  std::vector<NMEA_w_time> m_7_13;
  // std::vector<NMEA_w_time> m_8;
  std::vector<NMEA_w_time> m_9;
  std::vector<NMEA_w_time> m_10;
  std::vector<NMEA_w_time> m_12;
  std::vector<NMEA_w_time> m_14;
  std::vector<NMEA_w_time> m_15;
  std::vector<NMEA_w_time> m_16;
  std::vector<NMEA_w_time> m_17;
  std::vector<NMEA_w_time> m_18;
  std::vector<NMEA_w_time> m_19;
  std::vector<NMEA_w_time> m_20;
  std::vector<NMEA_w_time> m_21;
  std::vector<NMEA_w_time> m_22;
  std::vector<NMEA_w_time> m_23;
  std::vector<NMEA_w_time> m_24;
  std::vector<NMEA_w_time> m_25;
  std::vector<NMEA_w_time> m_26;
  std::vector<NMEA_w_time> m_27;

  NMEA_Stream() = default;

  NMEA_Stream(const std::size_t approx_size) {
    this->incomplete.reserve(20);
    m_1_2_3.reserve(approx_size * 0.5);
    // m_4_11.reserve(approx_size * 0.2);
    m_5.reserve(approx_size * 0.4);
    // m_7_13.reserve();
    // m_9.reserve();
    // m_10.reserve();
    // m_12.reserve();
    // m_14.reserve();
    // m_15.reserve();
    // m_16.reserve();
    // m_17.reserve();
    m_18.reserve(approx_size * 0.2);
    // m_19.reserve();
    // m_20.reserve();
    // m_21.reserve();
    // m_22.reserve();
    // m_23.reserve();
    // m_24.reserve();
    // m_25.reserve();
    // m_26.reserve();
    // m_27.reserve();
  };
  void push_dispatch(NMEA_w_time&& nmea);
  void push(NMEA&& nmea);

  // std::map<MSG_TYPE, std::size_t> count_msg_types() const;

  // SEXP as_df(const int n_max) const;

  // static NMEA_Stream from_file(const std::string& file_path);

  static NMEA_Stream from_file2(const std::string&);
};

//
//
// NMEA_Stream implementations
// =======================================================
inline void NMEA_Stream::push_dispatch(NMEA_w_time&& nmea) {
  switch (get_msg_type2(nmea.payload)) {
    // 1_2_3, 5, and 18 are by far the most common, so they're up front
    case MSG_TYPE::msg_1_2_3:
      m_1_2_3.push_back(std::move(nmea));
      break;

    case MSG_TYPE::msg_5:
      m_5.push_back(std::move(nmea));
      break;

    case MSG_TYPE::msg_18:
      m_18.push_back(std::move(nmea));
      break;

    case MSG_TYPE::msg_4_11:
      m_4_11.push_back(std::move(nmea));
      break;

    case MSG_TYPE::msg_6:
      // m_6.push_back(std::move(nmea));
      break;

    case MSG_TYPE::msg_7_13:
      m_7_13.push_back(std::move(nmea));
      break;

    case MSG_TYPE::msg_8:
      // m_8.push_back(std::move(nmea));
      break;

    case MSG_TYPE::msg_9:
      m_9.push_back(std::move(nmea));
      break;

    case MSG_TYPE::msg_10:
      m_10.push_back(std::move(nmea));
      break;

    case MSG_TYPE::msg_12:
      m_12.push_back(std::move(nmea));
      break;

    case MSG_TYPE::msg_14:
      m_14.push_back(std::move(nmea));
      break;

    case MSG_TYPE::msg_15:
      m_15.push_back(std::move(nmea));
      break;

    case MSG_TYPE::msg_16:
      m_16.push_back(std::move(nmea));
      break;

    case MSG_TYPE::msg_17:
      m_17.push_back(std::move(nmea));
      break;

    case MSG_TYPE::msg_19:
      m_19.push_back(std::move(nmea));
      break;

    case MSG_TYPE::msg_20:
      m_20.push_back(std::move(nmea));
      break;

    case MSG_TYPE::msg_21:
      m_21.push_back(std::move(nmea));
      break;

    case MSG_TYPE::msg_22:
      m_22.push_back(std::move(nmea));
      break;

    case MSG_TYPE::msg_23:
      m_23.push_back(std::move(nmea));
      break;

    case MSG_TYPE::msg_24:
      m_24.push_back(std::move(nmea));
      break;

    case MSG_TYPE::msg_25:
      m_25.push_back(std::move(nmea));
      break;

    case MSG_TYPE::msg_26:
      m_26.push_back(std::move(nmea));
      break;

    case MSG_TYPE::msg_27:
      m_27.push_back(std::move(nmea));
      break;

    default:
      break;
  }
}

inline void NMEA_Stream::push(NMEA&& nmea) {
  if (nmea.fragment_count == 1) {
    push_dispatch(std::move(nmea));
    return;
  }

  if (this->incomplete.size() == 0) {
    incomplete.push_back(std::move(nmea));
    return;
  }

  if (!incomplete.back().are_same_sentence(std::move(nmea))) {
    incomplete.clear();
    incomplete.push_back(std::move(nmea));
    return;
  }

  if (nmea.fragment_count != nmea.fragment_number) {
    incomplete.push_back(std::move(nmea));
    return;
  }

  incomplete.push_back(std::move(nmea));
  Payload final_payload;
  for (auto& val : incomplete) {
    auto current_end = std::find(std::begin(final_payload.data),  //
                                 std::end(final_payload.data),    //
                                 '\0');

    std::move(std::begin(val.payload.data), std::end(val.payload.data),
              current_end);
  }

  push_dispatch(                           //
      NMEA_w_time(                         //
          std::move(final_payload),        //
          incomplete.back().fill_bits,     //
          incomplete.front().line_number,  //
          incomplete.front().time_start    //
          )                                //
  );
  incomplete.clear();
};

// inline SEXP NMEA_Stream::as_df(const int n_max) const {
//   const auto max_rows = this->complete.size();
//   std::size_t n_rows;
//   if (n_max == -1) {
//     n_rows = max_rows;
//   } else if (static_cast<std::size_t>(n_max) > max_rows) {
//     n_rows = max_rows;
//   } else {
//     n_rows = static_cast<std::size_t>(n_max);
//   }

//   vec_int _line_number(n_rows);
//   vec_chr _talker(n_rows);
//   vec_int _fragment_count(n_rows);
//   vec_int _fragment_number(n_rows);
//   vec_int _message_id(n_rows);
//   vec_chr _channel(n_rows);
//   vec_chr _payload(n_rows);
//   vec_int _fill_bits(n_rows);

//   vec_dbl _time_start(n_rows);
//   _time_start.attr("class") = vec_chr{"POSIXct", "POSIXt"};
//   _time_start.attr("tzone") = "UTC";
//   vec_dbl _time_end(n_rows);
//   _time_end.attr("class") = vec_chr{"POSIXct", "POSIXt"};
//   _time_end.attr("tzone") = "UTC";

//   for (std::size_t i = 0; i < n_rows; ++i) {
//     if (i % 1000 == 0) {
//       R_CheckUserInterrupt();
//     }
//     // _line_number[i] = this->complete[i].line_number;
//     // _talker[i] = this->complete[i].talker.to_string();
//     // _fragment_count[i] = this->complete[i].fragment_count;
//     // _fragment_number[i] = this->complete[i].fragment_number;
//     // _message_id[i] = this->complete[i].message_id;
//     // _channel[i] = std::string(1, this->complete[i].channel);
//     _payload[i] = this->complete[i].payload.to_string();
//     _fill_bits[i] = this->complete[i].fill_bits;
//     _time_start[i] = this->complete[i].time_start;
//     _time_end[i] = this->complete[i].time_end;
//   }
//
//   using Rcpp::_;
//   auto out = Rcpp::List::create(  //
//                                   // _["line_number"] = _line_number, //
//                                   // _["talker"] = _talker, //
//                                   // _["fragment_count"] = _fragment_count,
//                                   //
//                                   // _["fragment_number"] = _fragment_number,
//                                   //
//                                   // _["message_id"] = _message_id, //
//                                   // _["channel"] = _channel, //
//       _["payload"] = _payload,    //
//       _["fill_bits"] = _fill_bits,    //
//       _["time_start"] = _time_start,  //
//       _["time_end"] = _time_end       //
//   );

//   out.attr("row.names") = Rcpp::seq_len(n_rows);
//   out.attr("class") = "data.frame";

//   return out;
// };

// inline NMEA_Stream NMEA_Stream::from_file(const std::string& file_path) {
//   constexpr std::size_t init_line_size = 100;
//   constexpr auto delim = '\n';

//   std::error_code error;
//   mio::mmap_source mmap;
//   mmap.map(file_path, error);
//   if (error) {
//     Rcpp::stop("mmap error");
//   }

//   const auto file_size = mmap.size();

//   //   `valid_lines` index into `offsets`, which index into `mmap`

//   std::vector<std::size_t> offsets;
//   offsets.reserve(file_size / init_line_size);
//   offsets.push_back(0);
//   // ^^^^^^^^^^^^^^^^^^ 1st line's 1st char
//   //                    `n_lines` is size(offsets) - 1
//   for (std::size_t i = 0; i < file_size; ++i) {
//     if (mmap[i] == delim) {
//       offsets.push_back(i + 1);
//       //                ^^^^^^
//       //                  \n + 1: 1st character on subsequent lines
//     }
//   }

//   const auto n_lines = offsets.size() - 1;
//   std::vector<std::size_t> which_valid;
//   which_valid.reserve(n_lines);

//   for (std::size_t i = 0; i < n_lines; ++i) {
//     const auto first_chr = mmap.begin() + offsets[i];
//     const auto last_chr = mmap.begin() + offsets[i + 1];
//     // const auto last_chr = mmap.begin() + offsets[i + 1] - 1;
//     //                                                 ^^^^^
//     //                  standard: lines end with \r\n (-2), but not
//     necessarily
//     //                  `rstrip(line)` before pushing
//     // if (last_chr - first_chr < 14) {
//     // continue;
//     // }
//     Sentence line(first_chr, last_chr);
//     if (line.is_valid()) {
//       which_valid.push_back(std::move(i));
//     }
//   }

//   if (which_valid.size() <= 1) {
//     Rcpp::stop("no valid lines.");
//   }

//   const auto n_messages = which_valid.size() - 1;
//   std::vector<NMEA> messages(n_messages);
// #pragma omp parallel for
//   for (std::size_t i = 0; i < n_messages; ++i) {
//     const auto first_chr = mmap.begin() + offsets[which_valid[i]];
//     const auto last_chr = mmap.begin() + offsets[which_valid[i + 1]];
//     // const auto last_chr = mmap.begin() + offsets[which_valid[i + 1]] - 1;

//     // Sentence(first_chr, last_chr);
//     // rstrip(line);
//     // const auto nmea = NMEA(Sentence(first_chr, last_chr), i);
//     messages[i] = NMEA(Sentence(first_chr, last_chr, i));
//   }

//   mmap.unmap();

//   NMEA_Stream out(n_messages);
//   for (auto& nmea : messages) {
//     out.push(std::move(nmea));
//   }

//   return out;
// }

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

inline NMEA_Stream NMEA_Stream::from_file2(const std::string& file_path) {
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
  offsets.reserve(file_size / MAX_SENTENCE_SIZE);
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
  std::vector<Sentence> sentences(n_lines);
#pragma omp parallel for simd
  for (std::size_t i = 0; i < n_lines; ++i) {
    sentences[i] = Sentence(            //
        mmap.begin() + offsets[i],      //
        mmap.begin() + offsets[i + 1],  //
        i                               //
    );
  }

  // mmap.unmap();

  std::vector<std::size_t> which_valid;
  which_valid.reserve(n_lines);

  for (std::size_t i = 0; i < n_lines; ++i) {
    if (sentences[i].is_valid()) {
      which_valid.push_back(i);
    }
  }

  const auto n_nmeas = which_valid.size();

  if (n_nmeas < 1) {
    Rcpp::stop("no valid lines.");
  }

  std::vector<NMEA> nmeas(n_nmeas);
#pragma omp parallel for simd
  for (std::size_t i = 0; i < n_nmeas; ++i) {
    nmeas[i] = NMEA(std::move(sentences[which_valid[i]]));
  }

  NMEA_Stream out(n_nmeas);
  for (auto&& nmea : nmeas) {
    out.push(std::move(nmea));
  }

  return out;
}

#endif
