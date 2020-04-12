#ifndef MARITIME_MSG_12_HPP
#define MARITIME_MSG_12_HPP

#include "msg.hpp"

class Msgs_12 : public AIS_Msgs<libais::Ais12> {
  vec_int seq_num;
  vec_int dest_mmsi;
  vec_lgl retransmitted;
  vec_int spare;
  vec_chr text;

 public:
  Msgs_12(const int n)
      : AIS_Msgs::AIS_Msgs(n),
        seq_num(n, NA_INTEGER),
        dest_mmsi(n, NA_INTEGER),
        retransmitted(n, NA_LOGICAL),
        spare(n, NA_INTEGER),
        text(n, NA_STRING){};

  void push(libais::Ais12&& msg,
            const std::size_t _line_number,
            const double _time) {
    if (msg.had_error()) {
      return;
    }
    const auto row_index = AIS_Msgs::common_row_index;
    AIS_Msgs::init_push(msg.message_id, msg.repeat_indicator, msg.mmsi,
                        _line_number, _time);
    seq_num[row_index] = msg.seq_num;
    dest_mmsi[row_index] = msg.dest_mmsi;
    retransmitted[row_index] = msg.retransmitted;
    spare[row_index] = msg.spare;
    text[row_index] = msg.text;
  };

  Rcpp::List as_list() const {
    auto out = AIS_Msgs::init_as_list();
    const auto seq_out = Rcpp::seq(0, AIS_Msgs::common_row_index - 1);

    out["seq_num"] = seq_num[seq_out];
    out["dest_mmsi"] = dest_mmsi[seq_out];
    out["retransmitted"] = retransmitted[seq_out];
    out["spare"] = spare[seq_out];
    out["text"] = text[seq_out];

    return out;
  };
};

#endif