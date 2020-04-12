#ifndef MARITIME_MSG_17_HPP
#define MARITIME_MSG_17_HPP

#include "msg.hpp"

class Msgs_17 : public AIS_Msgs<libais::Ais17> {
  vec_int spare;
  vec_dbl lng_deg;
  vec_dbl lat_deg;

 public:
  Msgs_17(const int n)
      : AIS_Msgs::AIS_Msgs(n),
        spare(n, NA_INTEGER),
        lng_deg(n, NA_REAL),
        lat_deg(n, NA_REAL){};

  void push(libais::Ais17&& msg,
            const std::size_t _line_number,
            const double _time) {
    if (msg.had_error()) {
      return;
    }
    const auto row_index = AIS_Msgs::common_row_index;
    AIS_Msgs::init_push(msg.message_id, msg.repeat_indicator, msg.mmsi,
                        _line_number, _time);

    spare[row_index] = msg.spare;
    lng_deg[row_index] = msg.position.lng_deg;
    lat_deg[row_index] = msg.position.lat_deg;
  };

  Rcpp::List as_list() const {
    auto out = AIS_Msgs::init_as_list();
    const auto seq_out = Rcpp::seq(0, AIS_Msgs::common_row_index - 1);

    out["spare"] = spare[seq_out];
    out["lng_deg"] = lng_deg[seq_out];
    out["lat_deg"] = lat_deg[seq_out];

    return out;
  };
};

#endif