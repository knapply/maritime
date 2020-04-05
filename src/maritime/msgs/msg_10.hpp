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
        spare(n),
        dest_mmsi(n),
        spare2(n){};

  void push(const libais::Ais10& msg,
            const double _time_start,
            const double _time_end) {
    const auto row_index = AIS_Msgs::common_row_index;
    const auto push_success = AIS_Msgs::init_push(msg, _time_start, _time_end);

    if (!push_success) {
      return;
    }

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