// #ifndef MARITIME_NESTED_MSGS_HPP
// #define MARITIME_NESTED_MSGS_HPP

// #include "../decoder.hpp"
// #include "ais.h"
// #include "msg.hpp"
// // Nest
// // ========================================================================================
// // typedef Rcpp::Xptr<libais::AisMsg> aisptr;

// // class Nest2 {
// //  public:
// //   std::size_t n_messages;
// //   vec_dbl time_start;
// //   vec_dbl time_end;
// //   vec_int message_id;
// //   vec_int mmsi;
// //   Rcpp::List msg_data;
// //   Rcpp::List geometry;

// //  public:
// //   // template <class decoder_T>
// //   Nest2(const Decoder& decoder) {
// //     const auto n = decoder.nmea_stream.complete.size();

// //     this->n_messages = n;
// //     this->time_start = vec_dbl(n, NA_REAL);
// //     this->time_end = vec_dbl(n, NA_REAL);
// //     this->message_id = vec_int(n, NA_REAL);
// //     this->mmsi = vec_int(n, NA_REAL);
// //     this->msg_data = Rcpp::List(n);
// //     this->geometry = Rcpp::List(n, vec_dbl(2, NA_REAL));
// //     // geometry.resize(n, std::vector<double>(2, DBL_MIN));
// //     // const auto total_msgs = decoder.nmea_stream.complete.size();

// //     Progress progress(n, true);

// //     for (std::size_t i = 0; i < n; ++i) {
// //       progress.increment();
// //       auto nmea = decoder.nmea_stream.complete[i];

// //       // libais::Ais1_2_3 msg(std::begin(nmea.payload.data), nmea.fill_bits);

// //       const auto msg = Rcpp::XPtr<libais::Ais1_2_3>(           //
// //           new libais::Ais1_2_3(std::begin(nmea.payload.data),  //
// //                                nmea.fill_bits),                //
// //           true                                                 //
// //       );
// //       if (msg->had_error()) {
// //         continue;
// //       }

// //       msg_data[i] = msg;

// //       time_start[i] = nmea.time_start;
// //       time_end[i] = nmea.time_end;
// //       message_id[i] = nmea.message_id;

// //       mmsi[i] = msg->mmsi;
// //       geometry[i] = vec_dbl::create(                    //
// //           msg->position.lng_deg, msg->position.lat_deg  //
// //       );
// //     }
// //   };

// //   SEXP as_list() const {
// //     // const auto seq_out = Rcpp::seq(0, this->n_messages - 1);

// //     Rcpp::List out;
// //     out["time_start"] = this->time_start;
// //     out["time_end"] = this->time_end;
// //     out["message_id"] = this->message_id;
// //     out["mmsi"] = this->mmsi;
// //     out["msg"] = this->msg_data;
// //     out["geometry"] = this->geometry;

// //     return out;
// //   }
// // };

// template <class libais_T>
// inline SEXP get_geometry(const libais_T& msg) {
//   return Rcpp::List::create(NA_REAL, NA_REAL);
// }

// template <>
// inline SEXP get_geometry<Rcpp::XPtr<libais::Ais1_2_3>>(
//     const Rcpp::XPtr<libais::Ais1_2_3>& msg) {
//   return Rcpp::List::create(msg->position.lng_deg, msg->position.lat_deg);
// }

// class Nest {
//  public:
//   std::size_t common_row_index;
//   vec_int time_start;
//   vec_int time_end;
//   vec_int message_id;
//   vec_int mmsi;
//   Rcpp::List msg_data;
//   Rcpp::List geometry;

//  public:
//   explicit Nest(const std::size_t n)
//       : common_row_index(0),
//         time_start(n),
//         time_end(n),
//         message_id(n),
//         mmsi(n),
//         msg_data(n),
//         geometry(n, vec_dbl(2, NA_REAL)) {
//     time_start.attr("class") = vec_chr{"POSIXct", "POSIXt"};
//     time_start.attr("tzone") = "UTC";

//     time_end.attr("class") = vec_chr{"POSIXct", "POSIXt"};
//     time_end.attr("tzone") = "UTC";
//   };

//   // template <class libais_T>
//   void push(Rcpp::XPtr<libais::AisMsg> msg,
//             const double _time_start,
//             const double _time_end) {
//     //
//     if (msg->had_error()) {
//       return;
//     }

//     // this->ais_pointers[this->common_row_index] =
//     // Rcpp::XPtr<libais::AisMsg>(new libais::AisMsg, true),         //
//     // true                                      //
//     // );
//     // new libais::AisMsg(msg), false                                         //
//     // );

//     this->time_start[common_row_index] = _time_start;
//     this->time_end[common_row_index] = _time_end;

//     this->message_id[common_row_index] = msg->message_id;
//     this->mmsi[common_row_index] = msg->mmsi;

//     this->msg_data[common_row_index] = msg;

//     this->geometry[this->common_row_index] = get_geometry(msg);

//     this->common_row_index++;
//   };

//   Rcpp::List as_list() const {
//     const auto seq_out = Rcpp::seq(0, this->common_row_index - 1);

//     Rcpp::List out;
//     out["time_start"] = this->time_start[seq_out];
//     out["time_end"] = this->time_end[seq_out];
//     out["message_id"] = this->message_id[seq_out];
//     out["mmsi"] = this->mmsi[seq_out];
//     out["msg"] = this->msg_data[seq_out];
//     out["geometry"] = this->geometry[seq_out];

//     return out;
//   };
// };

// // template <class libais_T>

// // inline Nest2::Nest2(const Decoder decoder) {
// //   // const auto decoder = Decoder::from_file(file_path);

// //   const auto n = decoder.nmea_stream.complete.size();

// //   time_start.resize(n);
// //   time_end.resize(n);
// //   message_id.resize(n);
// //   mmsi.resize(n);
// //   msg_data.resize(n);
// //   geometry.resize(n, std::vector<double>(2, DBL_MIN));
// //   // const auto total_msgs = decoder.nmea_stream.complete.size();

// //   Progress progress(n, true);

// //   for (std::size_t i = 0; i < n; ++i) {
// //     progress.increment();
// //     auto nmea = decoder.nmea_stream.complete[i];

// //     libais::Ais1_2_3 msg(std::begin(nmea.payload.data), nmea.fill_bits);
// //     if (msg.had_error()) {
// //       continue;
// //     }

// //     time_start[i] = nmea.time_start;
// //     time_end[i] = nmea.time_end;
// //     message_id[i] = nmea.message_id;

// //     mmsi[i] = msg.mmsi;
// //     geometry[i][0] = msg.position.lng_deg;
// //     geometry[i][1] = msg.position.lat_deg;

// //     msg_data[i] = Rcpp::XPtr<libais::AisMsg>(new libais::Ais1_2_3(msg));
// //   }
// // }

// // inline SEXP Nest2::as_list() const {
// //   // const auto seq_out = Rcpp::seq(0, this->common_row_index - 1);

// //   Rcpp::List out;
// //   out["time_start"] = Rcpp::wrap(this->time_start);
// //   out["time_end"] = Rcpp::wrap(this->time_end);
// //   out["message_id"] = Rcpp::wrap(this->message_id);
// //   out["mmsi"] = Rcpp::wrap(this->mmsi);
// //   out["msg"] = Rcpp::wrap(this->msg_data);
// //   out["geometry"] = Rcpp::wrap(this->geometry);

// //   return out;
// // }

// //   //
// //   if (msg->had_error()) {
// //     return;
// //   }

// //   // this->ais_pointers[this->common_row_index] =
// //   // Rcpp::XPtr<libais::AisMsg>(new libais::AisMsg, true),         //
// //   // true                                      //
// //   // );
// //   // new libais::AisMsg(msg), false //
// //   // );

// //   this->time_start[common_row_index] = _time_start;
// //   this->time_end[common_row_index] = _time_end;

// //   this->message_id[common_row_index] = msg->message_id;
// //   this->mmsi[common_row_index] = msg->mmsi;

// //   this->msg_data[common_row_index] = msg;

// //   this->geometry[this->common_row_index] = get_geometry(msg);

// //   this->common_row_index++;
// // };

// // Rcpp::List as_list() const {
// //   const auto seq_out = Rcpp::seq(0, this->common_row_index - 1);

// //   Rcpp::List out;
// //   out["time_start"] = this->time_start[seq_out];
// //   out["time_end"] = this->time_end[seq_out];
// //   out["message_id"] = this->message_id[seq_out];
// //   out["mmsi"] = this->mmsi[seq_out];
// //   out["msg"] = this->msg_data[seq_out];
// //   out["geometry"] = this->geometry[seq_out];

// //   return out;
// // };
// // }
// // ;

// #endif