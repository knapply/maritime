#ifndef MARITIME_MSG_14_HPP
#define MARITIME_MSG_14_HPP

#include "msg.hpp"

class Msgs_14 : public AIS_Msgs<libais::Ais14> {
  vec_int spare;
  vec_chr text;
  vec_int spare2;

 public:
  Msgs_14(const int n)
      : AIS_Msgs::AIS_Msgs(n),
        spare(n, NA_INTEGER),
        text(n, NA_STRING),
        spare2(n, NA_INTEGER){};

  void push(libais::Ais14&& msg,
            const std::size_t _line_number,
            const double _time) {

    if (msg.had_error()) {
      return;
    }
    const auto row_index = AIS_Msgs::common_row_index;

    AIS_Msgs::init_push(msg.message_id, msg.repeat_indicator, msg.mmsi,
                        _line_number, _time);

    spare[row_index] = msg.spare;
    text[row_index] = msg.text;
    spare2[row_index] = msg.spare2;
  };

  Rcpp::List as_list() const {
    auto out = AIS_Msgs::init_as_list();
    const auto seq_out = Rcpp::seq(0, AIS_Msgs::common_row_index - 1);

    out["spare"] = spare[seq_out];
    out["text"] = text[seq_out];
    out["spare2"] = spare2[seq_out];

    return out;
  };
};

#endif
