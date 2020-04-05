#ifndef MARITIME_MSG_7_23_HPP
#define MARITIME_MSG_7_13_HPP

#include "msg.hpp"

class Msgs_7_13 : public AIS_Msgs<libais::Ais7_13> {
  Rcpp::List dest_mmsi;
  Rcpp::List seq_num;

 public:
  Msgs_7_13(const int n)
      : AIS_Msgs::AIS_Msgs(n),     //
        dest_mmsi(n, vec_int(0)),  //
        seq_num(n, vec_int(0))     //
        {};

  void push(const libais::Ais7_13& msg,
            const double _time_start,
            const double _time_end) {
    const auto row_index = AIS_Msgs::common_row_index;
    const auto push_success = AIS_Msgs::init_push(msg, _time_start, _time_end);

    if (!push_success) {
      return;
    }

    const auto n_dest_mmsi = msg.dest_mmsi.size();
    if (n_dest_mmsi > 0) {
      vec_int _dest_mmsi(n_dest_mmsi, NA_INTEGER);
      vec_int _seq_num(n_dest_mmsi, NA_INTEGER);

      for (std::size_t i = 0; i < n_dest_mmsi; ++i) {
        _dest_mmsi[i] = msg.dest_mmsi[i];
        _seq_num[i] = msg.seq_num[i];
      }

      this->dest_mmsi[row_index] = _dest_mmsi;
      this->seq_num[row_index] = _seq_num;
    }
    //
  };

  Rcpp::List as_list() const {
    auto out = AIS_Msgs::init_as_list();
    const auto seq_out = Rcpp::seq(0, this->common_row_index - 1);

    out["dest_mmsi"] = this->dest_mmsi[seq_out];
    out["seq_num"] = this->seq_num[seq_out];

    return out;
  };
};

#endif