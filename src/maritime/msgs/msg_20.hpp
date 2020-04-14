#ifndef MARITIME_MSG_20_HPP
#define MARITIME_MSG_20_HPP

#include "msg.hpp"

class Msgs_20 : public AIS_Msgs<libais::Ais20> {
  Rcpp::List msg_20;

 public:
  Msgs_20(const int n) : AIS_Msgs::AIS_Msgs(n), msg_20(n){};

  void push(libais::Ais20&& msg,
            const std::size_t _line_number,
            const double _time) {
    if (msg.had_error()) {
      return;
    }
    const auto row_index = AIS_Msgs::common_row_index;
    AIS_Msgs::init_push(msg.message_id, msg.repeat_indicator, msg.mmsi,
                        _line_number, _time);

    Rcpp::IntegerMatrix temp(4, 4);
    temp.fill(NA_INTEGER);

    temp(0, 0) = msg.offset_1;
    temp(1, 0) = msg.num_slots_1;
    temp(2, 0) = msg.timeout_1;
    temp(3, 0) = msg.incr_1;

    if (msg.group_valid_2) {
      temp(0, 1) = msg.offset_2;
      temp(1, 1) = msg.num_slots_2;
      temp(2, 1) = msg.timeout_2;
      temp(3, 1) = msg.incr_2;
    }
    if (msg.group_valid_3) {
      temp(0, 2) = msg.offset_3;
      temp(1, 2) = msg.num_slots_3;
      temp(2, 2) = msg.timeout_3;
      temp(3, 2) = msg.incr_3;
    }
    if (msg.group_valid_4) {
      temp(0, 3) = msg.offset_4;
      temp(1, 3) = msg.num_slots_4;
      temp(2, 3) = msg.timeout_4;
      temp(3, 3) = msg.incr_4;
    }

    msg_20[row_index] = temp;
  };

  Rcpp::List as_list() const {
    auto out = AIS_Msgs::init_as_list();
    const auto seq_out = Rcpp::seq(0, AIS_Msgs::common_row_index - 1);

    out["msg_20"] = msg_20[seq_out];

    return out;
  };
};

#endif