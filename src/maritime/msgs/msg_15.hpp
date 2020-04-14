#ifndef MARITIME_MSG_15_HPP
#define MARITIME_MSG_15_HPP

#include "msg.hpp"

class Msgs_15 : public AIS_Msgs<libais::Ais15> {
  vec_int spare;
  vec_int mmsi_1;
  vec_int msg_1_1;
  vec_int slot_offset_1_1;
  vec_int spare2;
  vec_int dest_msg_1_2;
  vec_int slot_offset_1_2;
  vec_int spare3;
  vec_int mmsi_2;
  vec_int msg_2;
  vec_int slot_offset_2;
  vec_int spare4;

 public:
  Msgs_15(const int n)
      : AIS_Msgs::AIS_Msgs(n),
        spare(n, NA_INTEGER),
        mmsi_1(n, NA_INTEGER),
        msg_1_1(n, NA_INTEGER),
        slot_offset_1_1(n, NA_INTEGER),
        spare2(n, NA_INTEGER),
        dest_msg_1_2(n, NA_INTEGER),
        slot_offset_1_2(n, NA_INTEGER),
        spare3(n, NA_INTEGER),
        mmsi_2(n, NA_INTEGER),
        msg_2(n, NA_INTEGER),
        slot_offset_2(n, NA_INTEGER),
        spare4(n, NA_INTEGER){};

  void push(libais::Ais15&& msg,
            const std::size_t _line_number,
            const double _time) {
    if (msg.had_error()) {
      return;
    }
    const auto row_index = AIS_Msgs::common_row_index;
    AIS_Msgs::init_push(msg.message_id, msg.repeat_indicator, msg.mmsi,
                        _line_number, _time);

    spare[row_index] = msg.spare;
    mmsi_1[row_index] = msg.mmsi_1;
    msg_1_1[row_index] = msg.msg_1_1;
    slot_offset_1_1[row_index] = msg.slot_offset_1_1;
    spare2[row_index] = msg.spare2;
    dest_msg_1_2[row_index] = msg.dest_msg_1_2;
    slot_offset_1_2[row_index] = msg.slot_offset_1_2;
    spare3[row_index] = msg.spare3;
    mmsi_2[row_index] = msg.mmsi_2;
    msg_2[row_index] = msg.msg_2;
    slot_offset_2[row_index] = msg.slot_offset_2;
    spare4[row_index] = msg.spare4;
  };

  Rcpp::List as_list() const {
    auto out = AIS_Msgs::init_as_list();
    const auto seq_out = Rcpp::seq(0, AIS_Msgs::common_row_index - 1);

    out["spare"] = spare[seq_out];
    out["mmsi_1"] = mmsi_1[seq_out];
    out["msg_1_1"] = msg_1_1[seq_out];
    out["slot_offset_1_1"] = slot_offset_1_1[seq_out];
    out["spare2"] = spare2[seq_out];
    out["dest_msg_1_2"] = dest_msg_1_2[seq_out];
    out["slot_offset_1_2"] = slot_offset_1_2[seq_out];
    out["spare3"] = spare3[seq_out];
    out["mmsi_2"] = mmsi_2[seq_out];
    out["msg_2"] = msg_2[seq_out];
    out["slot_offset_2"] = slot_offset_2[seq_out];
    out["spare4"] = spare4[seq_out];

    return out;
  };
};

#endif