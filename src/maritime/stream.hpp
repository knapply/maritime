#ifndef MARITIME_STREAM_HPP
#define MARITIME_STREAM_HPP

#include "Rcpp_compat.hpp"
//
#include <progress.hpp>
//
#include <algorithm>
#include <array>
#include <mio/mmap.hpp>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

#include "maritime/proto_msg_dfs.hpp"
#include "msg_type.hpp"
#include "openmp.hpp"

constexpr long MIN_SENTENCE_SIZE = 21;
constexpr std::size_t MAX_SENTENCE_SIZE = 120;
constexpr std::size_t MAX_PAYLOAD_SIZE = 80;

// Sentence ====================================================================

class Sentence {
 public:
  std::array<char, MAX_SENTENCE_SIZE> data{{'\0'}};
  std::size_t line_number;

  Sentence() = default;

  Sentence(const char* first,
           const char* last,
           const std::size_t _line_number) noexcept
      : line_number(_line_number) {
    std::size_t i = 0;
    std::copy_if(                                                            //
        first, last,                                                         //
        std::begin(this->data),                                              //
        [&i](const char c) { return i++ < MAX_SENTENCE_SIZE && c != '\r'; }  //
    );
  };

  Sentence(const char* first, const char* last) noexcept {
    std::size_t i = 0;
    std::copy_if(                                                            //
        first, last,                                                         //
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
    while (*asterisk_it != '*'      //
           && *asterisk_it != '\0'  //
           && asterisk_it != it_end) {
      asterisk_it++;
    }

    if (*asterisk_it != '*'                                          //
        || asterisk_it - std::begin(this->data) < MIN_SENTENCE_SIZE  //
        || asterisk_it + 1 == it_end                                 //
        || asterisk_it + 2 == it_end) {
      return false;
    }

    const uint8_t target_checksum = std::accumulate(  //
        std::begin(this->data) + 1, asterisk_it,      //
        0,                                            //
        std::bit_xor<uint8_t>()                       //
    );                                                //

    char checksum[3] = {
        *(asterisk_it + 1),  //
        *(asterisk_it + 2),  //
        '\0'                 //
    };

    const uint8_t test_checksum = std::strtol(checksum, nullptr, 16);

    return target_checksum == test_checksum;
  }
};

// Payload =====================================================================

struct Payload {
  std::array<char, MAX_PAYLOAD_SIZE> data{{'\0'}};

  Payload() = default;

  Payload(std::string&& x) {
    std::move(std::begin(x), std::end(x), std::begin(this->data));
  };

  std::string to_string() const {
    return std::string(std::begin(this->data), std::end(this->data));
  };

  const char* c_str() const { return std::begin(this->data); };

  MSG_TYPE get_msg_type() const {
    switch (data[0]) {
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
  };
};

// Talker ======================================================================

struct Talker {
  char data[3];

  Talker() = default;

  Talker(const char* x) noexcept {
    this->data[0] = x[1];
    this->data[1] = x[2];
    this->data[2] = '\0';
  }

  std::string to_string() const {
    return std::string(std::begin(this->data), std::end(this->data));
  }
};

// NMEA ========================================================================

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

  NMEA(Payload&& _payload,
       Talker&& _talker,
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

  NMEA(Sentence&& x) : line_number(x.line_number), time_start(NA_REAL) {
    constexpr short n_split = 9;

    std::array<std::string, n_split> split;
    std::size_t split_count = 0;
    std::string element;

    std::stringstream sstream(x.c_str());
    while (std::getline(sstream, element, ',') && split_count < n_split) {
      split[split_count++] = element;
    }

    this->talker = Talker(split[0].c_str());
    this->fragment_count = split[1][0] - '0';
    this->fragment_number = split[2][0] - '0';
    if (!split[3].empty()) {
      this->message_id = split[3][0] - '0';
    }
    this->channel = split[4][0];

    this->payload = std::move(split[5]);

    if (split[6].size() == 4) {
      this->fill_bits = split[6][0] - '0';
      this->checksum[0] = split[6][2];
      this->checksum[1] = split[6][3];
    }

    if (split[7].size() >= 10  //
        && std::all_of(split[7].begin(), split[7].end(), ::isdigit)) {
      this->time_start = std::stoll(split[7] + '\0');
    }
  };

  bool are_same_sentence(const NMEA& rhs) const noexcept {
    return  // this->line_number == rhs.line_number - 1       //
            //  &&
        this->message_id == rhs.message_id             //
        && this->fragment_count == rhs.fragment_count  //
        && this->channel == rhs.channel                //
        && this->talker.data[0] == rhs.talker.data[0]  //
        && this->talker.data[1] == rhs.talker.data[1];
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
  };
};

// NMEA_w_time =================================================================

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

// NMEA_atom ===================================================================

template <class libais_T>
struct NMEA_atom {
  libais_T msg;
  std::size_t line_number;
  double time;

  NMEA_atom() = default;

  NMEA_atom(NMEA_w_time&& nmea)
      : msg(libais_T(nmea.payload.c_str(), nmea.fill_bits)),
        line_number(nmea.line_number),
        time(nmea.time){};
};

template <class libais_T>
inline std::vector<NMEA_atom<libais_T>> vectorize(  //
    std::vector<NMEA_w_time>&& nmeas,               //
    Progress& progress                              //
) {
  const auto n = nmeas.size();
  std::vector<NMEA_atom<libais_T>> out(n);

#pragma omp parallel for simd
  for (std::size_t i = 0; i < n; ++i) {
    progress.increment();
    out[i] = NMEA_atom<libais_T>(std::move(nmeas[i]));
  }

  return out;
}

// NMEA_Stream =================================================================

class NMEA_Stream {
 public:
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

  std::vector<NMEA> incomplete;

  NMEA_Stream() = default;

  NMEA_Stream(const std::size_t approx_size) {
    incomplete.reserve(10);
    m_1_2_3.reserve(approx_size * 0.5);
    m_5.reserve(approx_size * 0.4);
    m_18.reserve(approx_size * 0.2);
  };

  std::size_t n_total_messages() {
    return m_1_2_3.size()   //
           + m_4_11.size()  //
           + m_5.size()     //
                            //  + m_6.size()
           + m_7_13.size()  //
                            //  + m_8.size()
           + m_9.size()     //
           + m_10.size()    //
           + m_12.size()    //
           + m_14.size()    //
           + m_15.size()    //
           + m_16.size()    //
           + m_17.size()    //
           + m_18.size()    //
           + m_19.size()    //
           + m_20.size()    //
           + m_21.size()    //
           + m_22.size()    //
           + m_23.size()    //
           + m_24.size()    //
           + m_25.size()    //
           + m_26.size()    //
           + m_27.size();   //
  };

  std::size_t count_msgs(const MSG_TYPE msg_type) const;

  void push_dispatch(NMEA_w_time&& nmea);

  void push(NMEA&& nmea);

  static NMEA_Stream from_file(const std::string&);

 private:
  template <MSG_TYPE msg_type, class msg_df_T, class libais_T>
  SEXP _build_df(std::vector<NMEA_w_time>&& nmeas, Progress& progress) {
    auto atoms = vectorize<libais_T>(std::move(nmeas), progress);

    msg_df_T out(atoms.size());
    for (std::size_t i = 0; i < atoms.size(); ++i) {
      progress.increment();
      out.push(std::move(atoms[i].msg), atoms[i].line_number, atoms[i].time);
    }

    return as_df(std::move(out));
  };

 public:
  template <MSG_TYPE msg_type>
  SEXP build_df(Progress&);

  SEXP build_df_impl(const MSG_TYPE msg_type, Progress& progress);

  SEXP build_df_list(Progress& progress);
};

// =============================================================================

inline std::size_t NMEA_Stream::count_msgs(const MSG_TYPE msg_type) const {
  switch (msg_type) {
    case MSG_TYPE::msg_1_2_3:
      return m_1_2_3.size();
    case MSG_TYPE::msg_4_11:
      return m_4_11.size();
    case MSG_TYPE::msg_5:
      return m_5.size();
    case MSG_TYPE::msg_6:
      return 0;
    case MSG_TYPE::msg_7_13:
      return m_7_13.size();
    case MSG_TYPE::msg_8:
      return 0;
    case MSG_TYPE::msg_9:
      return m_9.size();
    case MSG_TYPE::msg_10:
      return m_10.size();
    case MSG_TYPE::msg_12:
      return m_12.size();
    case MSG_TYPE::msg_14:
      return m_14.size();
    case MSG_TYPE::msg_15:
      return m_15.size();
    case MSG_TYPE::msg_16:
      return m_16.size();
    case MSG_TYPE::msg_17:
      return m_17.size();
    case MSG_TYPE::msg_18:
      return m_18.size();
    case MSG_TYPE::msg_19:
      return m_19.size();
    case MSG_TYPE::msg_20:
      return m_20.size();
    case MSG_TYPE::msg_21:
      return m_21.size();
    case MSG_TYPE::msg_22:
      return m_22.size();
    case MSG_TYPE::msg_23:
      return m_23.size();
    case MSG_TYPE::msg_24:
      return m_24.size();
    case MSG_TYPE::msg_25:
      return m_25.size();
    case MSG_TYPE::msg_26:
      return m_26.size();
    case MSG_TYPE::msg_27:
      return m_27.size();

    default:
      return 0;
  }
}

inline void NMEA_Stream::push_dispatch(NMEA_w_time&& nmea) {
  switch (nmea.payload.get_msg_type()) {
    // 1_2_3, 5, and 18 are most common, so they're up front
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

template <>
inline SEXP NMEA_Stream::build_df<MSG_TYPE::msg_1_2_3>(Progress& progress) {
  return _build_df<MSG_TYPE::msg_1_2_3, Msgs_1_2_3, libais::Ais1_2_3>(
      std::move(m_1_2_3), progress  //
  );
}
template <>
inline SEXP NMEA_Stream::build_df<MSG_TYPE::msg_4_11>(Progress& progress) {
  return _build_df<MSG_TYPE::msg_4_11, Msgs_4_11, libais::Ais4_11>(
      std::move(m_4_11), progress  //
  );
}
template <>
inline SEXP NMEA_Stream::build_df<MSG_TYPE::msg_5>(Progress& progress) {
  return _build_df<MSG_TYPE::msg_5, Msgs_5, libais::Ais5>(
      std::move(m_5), progress  //
  );
}
template <>
inline SEXP NMEA_Stream::build_df<MSG_TYPE::msg_6>(Progress& progress) {
  return R_NilValue;
}
template <>
inline SEXP NMEA_Stream::build_df<MSG_TYPE::msg_7_13>(Progress& progress) {
  return _build_df<MSG_TYPE::msg_7_13, Msgs_7_13, libais::Ais7_13>(
      std::move(m_7_13), progress  //
  );
}
template <>
inline SEXP NMEA_Stream::build_df<MSG_TYPE::msg_8>(Progress& progress) {
  return R_NilValue;
}
template <>
inline SEXP NMEA_Stream::build_df<MSG_TYPE::msg_9>(Progress& progress) {
  return _build_df<MSG_TYPE::msg_9, Msgs_9, libais::Ais9>(
      std::move(m_9), progress  //
  );
}
template <>
inline SEXP NMEA_Stream::build_df<MSG_TYPE::msg_10>(Progress& progress) {
  return _build_df<MSG_TYPE::msg_10, Msgs_10, libais::Ais10>(
      std::move(m_10), progress  //
  );
}
template <>
inline SEXP NMEA_Stream::build_df<MSG_TYPE::msg_12>(Progress& progress) {
  return _build_df<MSG_TYPE::msg_12, Msgs_12, libais::Ais12>(
      std::move(m_12), progress  //
  );
}
template <>
inline SEXP NMEA_Stream::build_df<MSG_TYPE::msg_14>(Progress& progress) {
  return _build_df<MSG_TYPE::msg_14, Msgs_14, libais::Ais14>(
      std::move(m_14), progress  //
  );
}
template <>
inline SEXP NMEA_Stream::build_df<MSG_TYPE::msg_15>(Progress& progress) {
  return _build_df<MSG_TYPE::msg_15, Msgs_15, libais::Ais15>(
      std::move(m_15), progress  //
  );
}
template <>
inline SEXP NMEA_Stream::build_df<MSG_TYPE::msg_16>(Progress& progress) {
  return _build_df<MSG_TYPE::msg_16, Msgs_16, libais::Ais16>(
      std::move(m_16), progress  //
  );
}
template <>
inline SEXP NMEA_Stream::build_df<MSG_TYPE::msg_17>(Progress& progress) {
  return _build_df<MSG_TYPE::msg_17, Msgs_17, libais::Ais17>(
      std::move(m_17), progress  //
  );
}
template <>
inline SEXP NMEA_Stream::build_df<MSG_TYPE::msg_18>(Progress& progress) {
  return _build_df<MSG_TYPE::msg_18, Msgs_18, libais::Ais18>(
      std::move(m_18), progress  //
  );
}
template <>
inline SEXP NMEA_Stream::build_df<MSG_TYPE::msg_19>(Progress& progress) {
  return _build_df<MSG_TYPE::msg_19, Msgs_19, libais::Ais19>(
      std::move(m_19), progress  //
  );
}
template <>
inline SEXP NMEA_Stream::build_df<MSG_TYPE::msg_20>(Progress& progress) {
  return _build_df<MSG_TYPE::msg_20, Msgs_20, libais::Ais20>(
      std::move(m_20), progress  //
  );
}
template <>
inline SEXP NMEA_Stream::build_df<MSG_TYPE::msg_21>(Progress& progress) {
  return _build_df<MSG_TYPE::msg_21, Msgs_21, libais::Ais21>(
      std::move(m_21), progress  //
  );
}
template <>
inline SEXP NMEA_Stream::build_df<MSG_TYPE::msg_22>(Progress& progress) {
  return _build_df<MSG_TYPE::msg_22, Msgs_22, libais::Ais22>(
      std::move(m_22), progress  //
  );
}
template <>
inline SEXP NMEA_Stream::build_df<MSG_TYPE::msg_23>(Progress& progress) {
  return _build_df<MSG_TYPE::msg_23, Msgs_23, libais::Ais23>(
      std::move(m_23), progress  //
  );
}
template <>
inline SEXP NMEA_Stream::build_df<MSG_TYPE::msg_24>(Progress& progress) {
  return _build_df<MSG_TYPE::msg_24, Msgs_24, libais::Ais24>(
      std::move(m_24), progress  //
  );
}
template <>
inline SEXP NMEA_Stream::build_df<MSG_TYPE::msg_25>(Progress& progress) {
  return _build_df<MSG_TYPE::msg_25, Msgs_25, libais::Ais25>(
      std::move(m_25), progress  //
  );
}
template <>
inline SEXP NMEA_Stream::build_df<MSG_TYPE::msg_26>(Progress& progress) {
  return _build_df<MSG_TYPE::msg_26, Msgs_26, libais::Ais26>(
      std::move(m_26), progress  //
  );
}
template <>
inline SEXP NMEA_Stream::build_df<MSG_TYPE::msg_27>(Progress& progress) {
  return _build_df<MSG_TYPE::msg_27, Msgs_27, libais::Ais27>(
      std::move(m_27), progress  //
  );
}

inline SEXP NMEA_Stream::build_df_impl(const MSG_TYPE msg_type,
                                       Progress& progress) {
  switch (msg_type) {
    case MSG_TYPE::msg_1_2_3:
      return build_df<MSG_TYPE::msg_1_2_3>(progress);
    case MSG_TYPE::msg_4_11:
      return build_df<MSG_TYPE::msg_4_11>(progress);
    case MSG_TYPE::msg_5:
      return build_df<MSG_TYPE::msg_5>(progress);
    case MSG_TYPE::msg_6:
      return R_NilValue;
    case MSG_TYPE::msg_7_13:
      return build_df<MSG_TYPE::msg_7_13>(progress);
    case MSG_TYPE::msg_8:
      return R_NilValue;
    case MSG_TYPE::msg_9:
      return build_df<MSG_TYPE::msg_9>(progress);
    case MSG_TYPE::msg_10:
      return build_df<MSG_TYPE::msg_10>(progress);
    case MSG_TYPE::msg_12:
      return build_df<MSG_TYPE::msg_12>(progress);
    case MSG_TYPE::msg_14:
      return build_df<MSG_TYPE::msg_14>(progress);
    case MSG_TYPE::msg_15:
      return build_df<MSG_TYPE::msg_15>(progress);
    case MSG_TYPE::msg_16:
      return build_df<MSG_TYPE::msg_16>(progress);
    case MSG_TYPE::msg_17:
      return build_df<MSG_TYPE::msg_17>(progress);
    case MSG_TYPE::msg_18:
      return build_df<MSG_TYPE::msg_18>(progress);
    case MSG_TYPE::msg_19:
      return build_df<MSG_TYPE::msg_19>(progress);
    case MSG_TYPE::msg_20:
      return build_df<MSG_TYPE::msg_20>(progress);
    case MSG_TYPE::msg_21:
      return build_df<MSG_TYPE::msg_21>(progress);
    case MSG_TYPE::msg_22:
      return build_df<MSG_TYPE::msg_22>(progress);
    case MSG_TYPE::msg_23:
      return build_df<MSG_TYPE::msg_23>(progress);
    case MSG_TYPE::msg_24:
      return build_df<MSG_TYPE::msg_24>(progress);
    case MSG_TYPE::msg_25:
      return build_df<MSG_TYPE::msg_25>(progress);
    case MSG_TYPE::msg_26:
      return build_df<MSG_TYPE::msg_26>(progress);
    case MSG_TYPE::msg_27:
      return build_df<MSG_TYPE::msg_27>(progress);

    default:
      return R_NilValue;
  }
}

inline SEXP NMEA_Stream::build_df_list(Progress& progress) {
  Rcpp::List out;

  out["msgs_1_2_3"] = build_df<MSG_TYPE::msg_1_2_3>(progress);
  out["msgs_4_11"] = build_df<MSG_TYPE::msg_4_11>(progress);
  out["msgs_5"] = build_df<MSG_TYPE::msg_5>(progress);
  out["msgs_7_13"] = build_df<MSG_TYPE::msg_7_13>(progress);
  out["msgs_9"] = build_df<MSG_TYPE::msg_9>(progress);
  out["msgs_10"] = build_df<MSG_TYPE::msg_10>(progress);
  out["msgs_12"] = build_df<MSG_TYPE::msg_12>(progress);
  out["msgs_14"] = build_df<MSG_TYPE::msg_14>(progress);
  out["msgs_15"] = build_df<MSG_TYPE::msg_15>(progress);
  out["msgs_16"] = build_df<MSG_TYPE::msg_16>(progress);
  out["msgs_17"] = build_df<MSG_TYPE::msg_17>(progress);
  out["msgs_18"] = build_df<MSG_TYPE::msg_18>(progress);
  out["msgs_19"] = build_df<MSG_TYPE::msg_19>(progress);
  out["msgs_20"] = build_df<MSG_TYPE::msg_20>(progress);
  out["msgs_21"] = build_df<MSG_TYPE::msg_21>(progress);
  out["msgs_22"] = build_df<MSG_TYPE::msg_22>(progress);
  out["msgs_23"] = build_df<MSG_TYPE::msg_23>(progress);
  out["msgs_24"] = build_df<MSG_TYPE::msg_24>(progress);
  out["msgs_25"] = build_df<MSG_TYPE::msg_25>(progress);
  out["msgs_26"] = build_df<MSG_TYPE::msg_26>(progress);
  out["msgs_27"] = build_df<MSG_TYPE::msg_27>(progress);

  return out;
};

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
          incomplete.back()
              .time_start  // this should be incomplete.front().time_start
          )                // but most msg_5 times get nuked that way...
                           // I'm screwing up something with std::move()...?
  );
  incomplete.clear();
};
//
//
//
//
//
//


//
inline NMEA_Stream NMEA_Stream::from_file(const std::string& file_path) {
  constexpr auto delim = '\n';

  std::error_code error;
  mio::mmap_source mmap;
  mmap.map(file_path, error);
  if (error) {
    Rcpp::stop("mmap error");
  }

  const auto file_size = mmap.size();

  //   `valid_lines` index into `offsets` which index into `mmap`

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
#pragma omp parallel for
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
#pragma omp parallel for
  for (std::size_t i = 0; i < n_nmeas; ++i) {
    nmeas[i] = NMEA(std::move(sentences[which_valid[i]]));
  }

  NMEA_Stream out(n_nmeas);
  for (auto& nmea : nmeas) {
    out.push(std::move(nmea));
  }

  return out;
}

#endif
