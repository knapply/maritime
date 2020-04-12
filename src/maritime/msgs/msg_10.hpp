#ifndef MARITIME_MSG_10_HPP
#define MARITIME_MSG_10_HPP

#include "msg.hpp"

class Msgs_10 : public AIS_Msgs<libais::Ais10> {
  vec_int spare;
  vec_int dest_mmsi;
  vec_int spare2;

 public:
  Msgs_10(const int n)
      : AIS_Msgs::AIS_Msgs(n),  //
        spare(n, NA_INTEGER),
        dest_mmsi(n, NA_INTEGER),
        spare2(n, NA_INTEGER){};

  void push(libais::Ais10&& msg,
            const std::size_t _line_number,
            const double _time) {
    if (msg.had_error()) {
      return;
    }
    const auto row_index = AIS_Msgs::common_row_index;
    AIS_Msgs::init_push(msg.message_id, msg.repeat_indicator, msg.mmsi,
                        _line_number, _time);

    this->spare[row_index] = msg.spare;
    this->dest_mmsi[row_index] = msg.dest_mmsi;
    this->spare2[row_index] = msg.spare2;

    //
  };

  Rcpp::List as_list() const {
    auto out = AIS_Msgs::init_as_list();
    const auto seq_out = Rcpp::seq(0, this->common_row_index - 1);

    out["spare"] = this->spare[seq_out];
    out["dest_mmsi"] = this->dest_mmsi[seq_out];
    out["spare2"] = this->spare2[seq_out];

    return out;
  };
};

#endif