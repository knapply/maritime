// #ifndef MARITIME_MSG_6_HPP
// #define MARITIME_MSG_6_HPP

// #include "msg.hpp"

// // libais::AIS_DAC_1_INTERNATIONAL;

// struct Msg6_Pack {
//   int seq;
//   int mmsi_dest;
//   bool retransmit;
//   int spare;
//   int dac;
//   int fi;
// };

// template <class libais_T>
// class Msgs_6 : public AIS_Msgs<libais::Ais6> {
//   vec_int seq;
//   vec_int mmsi_dest;
//   vec_lgl retransmit;
//   vec_int spare;
//   vec_int dac;
//   vec_int fi;

//  public:
//   Msgs_6(const int n)
//       : AIS_Msgs::AIS_Msgs(n),
//         seq(n, NA_INTEGER),
//         mmsi_dest(n, NA_INTEGER),
//         retransmit(n, NA_LOGICAL),
//         spare(n, NA_INTEGER),
//         dac(n, NA_INTEGER),
//         fi(n, NA_INTEGER){};

//   void push6(Msg_Pack&& msg_pack, Msg6_Pack&& msg_6_pack) {
//     if (msg.had_error()) {
//       return;
//     }

//     const auto row_index = AIS_Msgs::common_row_index;
//     AIS_Msgs::init_push(msg_pack);

//     seq[row_index] = msg6.seq;
//     mmsi_dest[row_index] = msg6.mmsi_dest;
//     retransmit[row_index] = msg6.retransmit;
//     spare[row_index] = msg6.spare;
//     dac[row_index] = msg6.dac;
//     fi[row_index] = msg6.fi;
//   };

//   Rcpp::List as_list6() const {
//     auto out = AIS_Msgs::init_as_list();
//     const auto seq_out = Rcpp::seq(0, AIS_Msgs::common_row_index - 1);

//     out["seq"] = seq[seq_along];
//     out["mmsi_dest"] = mmsi_dest[seq_along];
//     out["retransmit"] = retransmit[seq_along];
//     out["spare"] = spare[seq_along];
//     out["dac"] = dac[seq_along];
//     out["fi"] = fi[seq_along];

//     return out;
//   };
// };

// ////
// class Msgs_6_1_0 : public Msgs_6<libais::Ais6_1_0> {
//   vec_lgl ack_required;
//   vec_int msg_seq;
//   vec_chr text;
//   vec_int spare2;

//  public:
//   Msgs_6_1_0(const int n)
//       : Msgs_6::Msgs_6(n),
//         ack_required(n, NA_LOGICAL),
//         msg_seq(n, NA_INTEGER),
//         text(n, NA_STRING),
//         spare2(n, NA_INTEGER){};

//   void push(libais::Ais6_1_0&& msg,
//              const std::size_t _line_number,
//              const double _time,
//              Msg6_Pack&& msg_6_pack) {
//     if (msg.had_error()) {
//       return;
//     }

//     const auto row_index = AIS_Msgs::common_row_index;
//     Msgs_6::push6(  //
//         Msg_Pack{msg.message_id, msg.repeat_indicator, msg.mmsi, _line_number,
//                  _time},
//         Msg6_Pack{msg.seq, msg.mmsi_dest, msg.retransmit, msg.spare, msg.dac,
//                   msg.fi}  //
//     );

//     ack_required[row_index] = msg.ack_required;
//     msg_seq[row_index] = msg.msg_seq;
//     text[row_index] = msg.text;
//     spare2[row_index] = msg.spare2;
//   };

//   Rcpp::List as_list() const {
//     auto out = Msgs_6::as_list6();
//     const auto seq_out = Rcpp::seq(0, AIS_Msgs::common_row_index - 1);

//     out["ack_required"] = ack_required[seq_out];
//     out["msg_seq"] = msg_seq[seq_out];
//     out["text"] = text[seq_out];
//     out["spare2"] = spare2[seq_out];

//     return out;
//   };
// };



// // get_msg6_type

// #endif
