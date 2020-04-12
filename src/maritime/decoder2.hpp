#ifndef MARITIME_DECODER2_HPP
#define MARITIME_DECODER2_HPP

// #include <progress.hpp>

#include "ais.h"
#include "openmp.hpp"
#include "proto_msg_dfs.hpp"
#include "stream.hpp"

// inline MSG_TYPE get_msg_type2(const Payload& payload) {
//   switch (payload.data[0]) {
//     case '1':  // class A position
//     case '2':
//     case '3':
//       return MSG_TYPE::msg_1_2_3;

//     case '4':  // 4: basestation report
//     case ';':  // 11: UTC date response
//       return MSG_TYPE::msg_4_11;

//     case '5':  // 5: ship and cargo
//       return MSG_TYPE::msg_5;

//     case '6':  // 6 - Addressed binary message
//       return MSG_TYPE::msg_6;

//     case '7':  // FALLTHROUGH - 7 - ACK for addressed binary message
//     case '=':  // 13 - ASRM Ack  (safety message)
//       return MSG_TYPE::msg_7_13;

//     case '8':  // 8 - Binary broadcast message (BBM)
//       return MSG_TYPE::msg_8;

//     case '9':  // 9 - SAR Position
//       return MSG_TYPE::msg_9;

//     case ':':  // 10 - UTC Query
//       return MSG_TYPE::msg_10;

//       // ';' 11 - See 4

//     case '<':  // 12 - ASRM
//       return MSG_TYPE::msg_12;

//       // 13 - See 7

//     case '>':  // 14 - SRBM - Safety broadcast
//       return MSG_TYPE::msg_14;

//     case '?':  // 15 - Interrogation
//       return MSG_TYPE::msg_15;

//     case '@':  // 16 - Assigned mode command
//       return MSG_TYPE::msg_16;

//     case 'A':  // 17 - GNSS broadcast
//       return MSG_TYPE::msg_17;

//     case 'B':  // 18 - Position, Class B
//       return MSG_TYPE::msg_18;

//     case 'C':  // 19 - Position and ship, Class B
//       return MSG_TYPE::msg_19;

//     case 'D':  // 20 - Data link management
//       return MSG_TYPE::msg_20;

//     case 'E':  // 21 - Aids to navigation report
//       return MSG_TYPE::msg_21;

//     case 'F':  // 22 - Channel Management
//       return MSG_TYPE::msg_22;

//     case 'G':  // 23 - Group Assignment Command
//       return MSG_TYPE::msg_23;

//     case 'H':  // 24 - Static data report
//       return MSG_TYPE::msg_24;

//     case 'I':  // 25 - Single slot binary message - addressed or broadcast
//       return MSG_TYPE::msg_25;

//     case 'J':  // 26 - Multi slot binary message with comm state
//       return MSG_TYPE::msg_26;

//     case 'K':  // 27 - Long-range AIS broadcast message
//       return MSG_TYPE::msg_27;

//       // case 'L':  // 28 - UNKNOWN
//       //   return MSG_TYPE::unknown;
//       //   break;

//     default:
//       return MSG_TYPE::unknown;
//   }
// }

// inline MSG_TYPE get_msg_6_type(const Payload& payload) {

// }

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
    std::vector<NMEA_w_time>&& nmeas                //
) {
  std::vector<NMEA_atom<libais_T>> out(nmeas.size());
#pragma omp parallel for simd
  for (std::size_t i = 0; i < nmeas.size(); ++i) {
    out[i] = NMEA_atom<libais_T>(std::move(nmeas[i]));
  }

  return out;
}

template <class df_T, class libaais_T>
inline SEXP _build_df(std::vector<NMEA_atom<libaais_T>>&& atoms) {
  df_T out(atoms.size());
  for (std::size_t i = 0; i < atoms.size(); ++i) {
    out.push(std::move(atoms[i].msg), atoms[i].line_number, atoms[i].time);
  }
  return as_df(std::move(out));
}

inline SEXP build_df(NMEA_Stream&& nmea_stream) {
  // const auto total_messages = nmeas.size();
  // std::vector<NMEA_w_time> m_1_2_3;
  // std::vector<NMEA_w_time> m_4_11;
  // std::vector<NMEA_w_time> m_5;
  // // std::vector<NMEA_w_time> m_6;
  // std::vector<NMEA_w_time> m_7_13;
  // // std::vector<NMEA_w_time> m_8;
  // std::vector<NMEA_w_time> m_9;
  // std::vector<NMEA_w_time> m_10;
  // std::vector<NMEA_w_time> m_12;
  // std::vector<NMEA_w_time> m_14;
  // std::vector<NMEA_w_time> m_15;
  // std::vector<NMEA_w_time> m_16;
  // std::vector<NMEA_w_time> m_17;
  // std::vector<NMEA_w_time> m_18;
  // std::vector<NMEA_w_time> m_19;
  // std::vector<NMEA_w_time> m_20;
  // std::vector<NMEA_w_time> m_21;
  // std::vector<NMEA_w_time> m_22;
  // std::vector<NMEA_w_time> m_23;
  // std::vector<NMEA_w_time> m_24;
  // std::vector<NMEA_w_time> m_25;
  // std::vector<NMEA_w_time> m_26;
  // std::vector<NMEA_w_time> m_27;

  // for (std::size_t i = 0; i < total_messages; ++i) {
  //   const auto nmea = nmeas[i];

  //   switch (get_msg_type2(nmea.payload)) {
  //     case MSG_TYPE::msg_1_2_3:
  //       m_1_2_3.push_back(std::move(nmea));
  //       break;

  //     case MSG_TYPE::msg_4_11:
  //       m_4_11.push_back(std::move(nmea));
  //       break;

  //     case MSG_TYPE::msg_5:
  //       m_5.push_back(std::move(nmea));
  //       break;

  //       // case MSG_TYPE::msg_6:
  //       //   m_6.push_back(std::move(nmea));
  //       //   break;

  //     case MSG_TYPE::msg_7_13:
  //       m_7_13.push_back(std::move(nmea));
  //       break;

  //       // case MSG_TYPE::msg_8:
  //       //   m_8.push_back(std::move(nmea));
  //       //   break;

  //     case MSG_TYPE::msg_9:
  //       m_9.push_back(std::move(nmea));
  //       break;

  //     case MSG_TYPE::msg_10:
  //       m_10.push_back(std::move(nmea));
  //       break;

  //     case MSG_TYPE::msg_12:
  //       m_12.push_back(std::move(nmea));
  //       break;

  //     case MSG_TYPE::msg_14:
  //       m_14.push_back(std::move(nmea));
  //       break;

  //     case MSG_TYPE::msg_15:
  //       m_15.push_back(std::move(nmea));
  //       break;

  //     case MSG_TYPE::msg_16:
  //       m_16.push_back(std::move(nmea));
  //       break;

  //     case MSG_TYPE::msg_17:
  //       m_17.push_back(std::move(nmea));
  //       break;

  //     case MSG_TYPE::msg_18:
  //       m_18.push_back(std::move(nmea));
  //       break;

  //     case MSG_TYPE::msg_19:
  //       m_19.push_back(std::move(nmea));
  //       break;

  //     case MSG_TYPE::msg_20:
  //       m_20.push_back(std::move(nmea));
  //       break;

  //     case MSG_TYPE::msg_21:
  //       m_21.push_back(std::move(nmea));
  //       break;

  //     case MSG_TYPE::msg_22:
  //       m_22.push_back(std::move(nmea));
  //       break;

  //     case MSG_TYPE::msg_23:
  //       m_23.push_back(std::move(nmea));
  //       break;

  //     case MSG_TYPE::msg_24:
  //       m_24.push_back(std::move(nmea));
  //       break;

  //     case MSG_TYPE::msg_25:
  //       m_25.push_back(std::move(nmea));
  //       break;

  //     case MSG_TYPE::msg_26:
  //       m_26.push_back(std::move(nmea));
  //       break;

  //     case MSG_TYPE::msg_27:
  //       m_27.push_back(std::move(nmea));
  //       break;

  //     default:
  //       break;
  //   }
  // }

  // Progress progress(14, true);

  Rcpp::List out;
  out["msgs_1_2_3"] = _build_df<Msgs_1_2_3, libais::Ais1_2_3>(  //
      vectorize<libais::Ais1_2_3>(std::move(nmea_stream.m_1_2_3))           //
  );

  // progress.increment();

  out["msgs_4_11"] = _build_df<Msgs_4_11, libais::Ais4_11>(  //
      vectorize<libais::Ais4_11>(std::move(nmea_stream.m_4_11))          //
  );

  // progress.increment();

  out["msgs_5"] = _build_df<Msgs_5, libais::Ais5>(  //
      vectorize<libais::Ais5>(std::move(nmea_stream.m_5))       //
  );
  // progress.increment();

  out["msgs_7_13"] = _build_df<Msgs_7_13, libais::Ais7_13>(  //
      vectorize<libais::Ais7_13>(std::move(nmea_stream.m_7_13))          //
  );
  // progress.increment();

  out["msgs_9"] = _build_df<Msgs_9, libais::Ais9>(  //
      vectorize<libais::Ais9>(std::move(nmea_stream.m_9))       //
  );
  // progress.increment();

  out["msgs_10"] = _build_df<Msgs_10, libais::Ais10>(  //
      vectorize<libais::Ais10>(std::move(nmea_stream.m_10))        //
  );
  // progress.increment();

  out["msgs_12"] = _build_df<Msgs_12, libais::Ais12>(  //
      vectorize<libais::Ais12>(std::move(nmea_stream.m_12))        //
  );
  // progress.increment();

  out["msgs_14"] = _build_df<Msgs_14, libais::Ais14>(  //
      vectorize<libais::Ais14>(std::move(nmea_stream.m_14))        //
  );
  // progress.increment();

  out["msgs_15"] = _build_df<Msgs_15, libais::Ais15>(  //
      vectorize<libais::Ais15>(std::move(nmea_stream.m_15))        //
  );
  // progress.increment();

  out["msgs_16"] = _build_df<Msgs_16, libais::Ais16>(  //
      vectorize<libais::Ais16>(std::move(nmea_stream.m_16))        //
  );
  // progress.increment();

  out["msgs_17"] = _build_df<Msgs_17, libais::Ais17>(  //
      vectorize<libais::Ais17>(std::move(nmea_stream.m_17))        //
  );
  // progress.increment();

  out["msgs_18"] = _build_df<Msgs_18, libais::Ais18>(  //
      vectorize<libais::Ais18>(std::move(nmea_stream.m_18))        //
  );
  // progress.increment();

  out["msgs_19"] = _build_df<Msgs_19, libais::Ais19>(  //
      vectorize<libais::Ais19>(std::move(nmea_stream.m_19))        //
  );
  // progress.increment();

  out["msgs_20"] = _build_df<Msgs_20, libais::Ais20>(  //
      vectorize<libais::Ais20>(std::move(nmea_stream.m_20))        //
  );
  // progress.increment();

  out["msgs_21"] = _build_df<Msgs_21, libais::Ais21>(  //
      vectorize<libais::Ais21>(std::move(nmea_stream.m_21))        //
  );
  // progress.increment();

  out["msgs_22"] = _build_df<Msgs_22, libais::Ais22>(  //
      vectorize<libais::Ais22>(std::move(nmea_stream.m_22))        //
  );
  // progress.increment();

  out["msgs_23"] = _build_df<Msgs_23, libais::Ais23>(  //
      vectorize<libais::Ais23>(std::move(nmea_stream.m_23))        //
  );
  // progress.increment();

  out["msgs_24"] = _build_df<Msgs_24, libais::Ais24>(  //
      vectorize<libais::Ais24>(std::move(nmea_stream.m_24))        //
  );
  // progress.increment();

  out["msgs_25"] = _build_df<Msgs_25, libais::Ais25>(  //
      vectorize<libais::Ais25>(std::move(nmea_stream.m_25))        //
  );
  // progress.increment();

  out["msgs_26"] = _build_df<Msgs_26, libais::Ais26>(  //
      vectorize<libais::Ais26>(std::move(nmea_stream.m_26))        //
  );
  // progress.increment();

  out["msgs_27"] = _build_df<Msgs_27, libais::Ais27>(  //
      vectorize<libais::Ais27>(std::move(nmea_stream.m_26))        //
  );
  // progress.increment();

  Rcpp::DataFrame x;

  return out;
  return R_NilValue;
};

#endif
