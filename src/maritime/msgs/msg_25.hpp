#ifndef MARITIME_MSG_25_HPP
#define MARITIME_MSG_25_HPP

#include "msg.hpp"

class Msgs_25 : public AIS_Msgs<libais::Ais25> {
  vec_int dest_mmsi;
  vec_int dac;
  vec_int fi;

 public:
  Msgs_25(const int n)
      : AIS_Msgs::AIS_Msgs(n),
        dest_mmsi(n, NA_INTEGER),
        dac(n, NA_INTEGER),
        fi(n, NA_INTEGER){};

  void push(libais::Ais25&& msg,
            const std::size_t _line_number,
            const double _time) {
    if (msg.had_error()) {
      return;
    }
    const auto row_index = AIS_Msgs::common_row_index;
    AIS_Msgs::init_push(msg.message_id, msg.repeat_indicator, msg.mmsi,
                        _line_number, _time);

    if (msg.dest_mmsi_valid) {
      dest_mmsi[row_index] = msg.dest_mmsi;
    }
    if (msg.use_app_id) {
      dac[row_index] = msg.dac;
      fi[row_index] = msg.fi;
    }
  };

  Rcpp::List as_list() const {
    auto out = AIS_Msgs::init_as_list();
    const auto seq_out = Rcpp::seq(0, AIS_Msgs::common_row_index - 1);
    
    out["dest_mmsi"] = dest_mmsi[seq_out];
    out["dac"] = dac[seq_out];
    out["fi"] = fi[seq_out];

    return out;
  };
};

#endif