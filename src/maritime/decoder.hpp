// #ifndef MARITIME_DECODER_HPP
// #define MARITIME_DECODER_HPP

// #include <progress.hpp>

// #include "ais.h"
// #include "proto_msg_dfs.hpp"
// #include "stream.hpp"

// inline MSG_TYPE get_msg_type(const Payload& payload) {
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

// class Decoder {
//  public:
//   NMEA_Stream nmea_stream;
//   std::map<MSG_TYPE, std::size_t> msg_counts{
//       {MSG_TYPE::unknown, 0}, {MSG_TYPE::msg_1_2_3, 0}, {MSG_TYPE::msg_4_11, 0},
//       {MSG_TYPE::msg_5, 0},   {MSG_TYPE::msg_6, 0},     {MSG_TYPE::msg_7_13, 0},
//       {MSG_TYPE::msg_8, 0},   {MSG_TYPE::msg_9, 0},     {MSG_TYPE::msg_10, 0},
//       {MSG_TYPE::msg_11, 0},  {MSG_TYPE::msg_12, 0},    {MSG_TYPE::msg_14, 0},
//       {MSG_TYPE::msg_15, 0},  {MSG_TYPE::msg_16, 0},    {MSG_TYPE::msg_17, 0},
//       {MSG_TYPE::msg_18, 0},  {MSG_TYPE::msg_19, 0},    {MSG_TYPE::msg_20, 0},
//       {MSG_TYPE::msg_21, 0},  {MSG_TYPE::msg_22, 0},    {MSG_TYPE::msg_23, 0},
//       {MSG_TYPE::msg_24, 0},  {MSG_TYPE::msg_25, 0},    {MSG_TYPE::msg_26, 0},
//       {MSG_TYPE::msg_27, 0}  //
//   };

//  public:
//   Decoder() = default;

//   Decoder(const NMEA_Stream&& _nmea_stream) : nmea_stream(_nmea_stream) {
//     for (std::size_t i = 0; i < _nmea_stream.complete.size(); ++i) {
//       this->msg_counts[get_msg_type(_nmea_stream.complete[i].payload)]++;
//     }
//   };

//   static Decoder from_file(const std::string& file_path) {
//     return Decoder(NMEA_Stream::from_file2(file_path));
//   };

//   SEXP as_df(const int n_max) const { return this->nmea_stream.as_df(n_max); };
// };

// //
// //
// //

// template <MSG_TYPE msg_T, class Msg_DF_T, class libais_T>
// inline SEXP decode_filter_file(const std::string& file_path,
//                                const bool verbose) {
//   const auto decoder = Decoder::from_file(file_path);
//   const auto n = decoder.msg_counts.at(msg_T);

//   Msg_DF_T out(n);

//   if (n == 0) {
//     return R_NilValue;
//   }

//   const auto total_messages = decoder.nmea_stream.complete.size();
//   // Progress progress(total_messages, true);

//   for (std::size_t i = 0; i < total_messages; ++i) {
//     // progress.increment();
//     const auto nmea = decoder.nmea_stream.complete[i];

//     if (msg_T != get_msg_type(nmea.payload)) {
//       continue;
//     }

//     const libais_T msg(nmea.payload.c_str(), nmea.fill_bits);
//     out.push(std::move(msg), nmea.time_start, nmea.time_end);
//   }

//   return as_df(out);
// };

// inline SEXP decode_list_file(const std::string& file_path, const bool verbose) {
//   const auto decoder = Decoder::from_file(file_path);

//   Msgs_1_2_3 msgs_1_2_3(decoder.msg_counts.at(MSG_TYPE::msg_1_2_3));
//   Msgs_4_11 msgs_4_11(decoder.msg_counts.at(MSG_TYPE::msg_4_11));
//   Msgs_5 msgs_5(decoder.msg_counts.at(MSG_TYPE::msg_5));
//   // 6
//   Msgs_7_13 msgs_7_13(decoder.msg_counts.at(MSG_TYPE::msg_7_13));
//   Msgs_9 msgs_9(decoder.msg_counts.at(MSG_TYPE::msg_9));
//   Msgs_10 msgs_10(decoder.msg_counts.at(MSG_TYPE::msg_10));

//   const auto total_messages = decoder.nmea_stream.complete.size();
//   Progress progress(total_messages, verbose);

//   for (std::size_t i = 0; i < total_messages; ++i) {
//     progress.increment();
//     const auto nmea = decoder.nmea_stream.complete[i];

//     switch (get_msg_type(nmea.payload)) {
//       case MSG_TYPE::msg_1_2_3:
//         msgs_1_2_3.push(                                       //
//             libais::Ais1_2_3(std::move(nmea.payload).c_str(),  //
//                              nmea.fill_bits),                  //
//             nmea.time_start, nmea.time_end                     //
//         );
//         break;

//       case MSG_TYPE::msg_4_11:
//         msgs_4_11.push(                                       //
//             libais::Ais4_11(std::move(nmea.payload).c_str(),  //
//                             nmea.fill_bits),                  //
//             nmea.time_start, nmea.time_end                    //
//         );
//         break;

//       case MSG_TYPE::msg_5:
//         msgs_5.push(                                       //
//             libais::Ais5(std::move(nmea.payload).c_str(),  //
//                          nmea.fill_bits),                  //
//             nmea.time_start, nmea.time_end                 //
//         );
//         break;

//         // 6

//       case MSG_TYPE::msg_7_13:
//         msgs_7_13.push(                                       //
//             libais::Ais7_13(std::move(nmea.payload).c_str(),  //
//                             nmea.fill_bits),                  //
//             nmea.time_start, nmea.time_end                    //
//         );
//         break;

//         // 8

//       case MSG_TYPE::msg_9:
//         msgs_9.push(                                       //
//             libais::Ais9(std::move(nmea.payload).c_str(),  //
//                          nmea.fill_bits),                  //
//             nmea.time_start, nmea.time_end                 //
//         );
//         break;

//       case MSG_TYPE::msg_10:
//         msgs_10.push(                                       //
//             libais::Ais10(std::move(nmea.payload).c_str(),  //
//                           nmea.fill_bits),                  //
//             nmea.time_start, nmea.time_end                  //
//         );
//         break;

//         //
//         //
//         //
//         //
//         //

//       default:
//         continue;
//     }
//   }

//   Rcpp::List out;
//   out["msgs_1_2_3"] = as_df(msgs_1_2_3);
//   out["msgs_4_11"] = as_df(msgs_4_11);
//   out["msgs_5"] = as_df(msgs_5);
//   // 6
//   out["msgs_7_13"] = as_df(msgs_7_13);
//   // 8
//   out["msgs_9"] = as_df(msgs_9);
//   out["msgs_10"] = as_df(msgs_10);

//   return out;
// }







// #endif