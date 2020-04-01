#ifndef MARITIME_AIS_H
#define MARITIME_AIS_H

// #include "maritime.h"
// #include <Rcpp.h>

#include "ais.h"
#include "maritime-ais-msgs.h"
#include "maritime-utils.h"

namespace maritime {
namespace ais {

inline std::string get_nth_field(const std::string& x,
                                 const std::size_t n,
                                 const std::string& delim_str) {
  if (x.empty()) {
    return "";
  }

  std::size_t prev = 0;
  std::size_t off = x.find(delim_str);
  std::size_t count = 0;

  for (; off != std::string::npos && count != n;
       off = x.find(delim_str, off + 1), count++) {
    prev = off + delim_str.size();
  }

  if (count == n) {
    return x.substr(prev, off - prev);
  }

  return "";
}

inline std::string get_body(const std::string& nmea_string) {
  auto out = get_nth_field(nmea_string, 5, ",");
  maritime::rstrip(out);
  return out;
}

enum class MSG_TYPE {
  unknown = 0,
  msg_1_2_3 = 1,
  msg_4_11 = 2,
  msg_5 = 3,
  msg_6 = 4,
  msg_7_13 = 5,
  msg_8 = 6,
  msg_9 = 7,
  msg_10 = 8,
  msg_11 = 9,
  msg_12 = 10,
  msg_14 = 11,
  msg_15 = 12,
  msg_16 = 13,
  msg_17 = 14,
  msg_18 = 15,
  msg_19 = 16,
  msg_20 = 17,
  msg_21 = 18,
  msg_22 = 19,
  msg_23 = 20,
  msg_24 = 21,
  msg_25 = 22,
  msg_26 = 23,
  msg_27 = 24
};

inline MSG_TYPE get_msg_type(const std::string& body) {
  if (body.empty()) {
    return MSG_TYPE::unknown;
  }

  switch (body[0]) {
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

}  // namespace ais
}  // namespace maritime

#endif