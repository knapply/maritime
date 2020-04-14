#ifndef MARITIME_MSG_23_HPP
#define MARITIME_MSG_23_HPP

#include "msg.hpp"

class Msgs_23 : public AIS_Msgs<libais::Ais23> {
  vec_int spare;
  vec_dbl lng_deg_1;
  vec_dbl lat_deg_1;
  vec_dbl lng_deg_2;
  vec_dbl lat_deg_2;
  vec_int station_type;
  vec_int type_and_cargo;
  vec_int spare2;
  vec_int txrx_mode;
  vec_int interval_raw;
  vec_int quiet;
  vec_int spare3;

 public:
  Msgs_23(const int n)
      : AIS_Msgs::AIS_Msgs(n),
        spare(n, NA_INTEGER),
        lng_deg_1(n, NA_REAL),
        lat_deg_1(n, NA_REAL),
        lng_deg_2(n, NA_REAL),
        lat_deg_2(n, NA_REAL),
        station_type(n, NA_INTEGER),
        type_and_cargo(n, NA_INTEGER),
        spare2(n, NA_INTEGER),
        txrx_mode(n, NA_INTEGER),
        interval_raw(n, NA_INTEGER),
        quiet(n, NA_INTEGER),
        spare3(n, NA_INTEGER)
        {};

  void push(libais::Ais23&& msg,
            const std::size_t _line_number,
            const double _time) {
    if (msg.had_error()) {
      return;
    }
    const auto row_index = AIS_Msgs::common_row_index;
    AIS_Msgs::init_push(msg.message_id, msg.repeat_indicator, msg.mmsi,
                        _line_number, _time);

    spare[row_index] = msg.spare;
    lng_deg_1[row_index] = msg.position1.lng_deg;
    lat_deg_1[row_index] = msg.position1.lat_deg;
    lng_deg_2[row_index] = msg.position2.lng_deg;
    lat_deg_2[row_index] = msg.position2.lat_deg;
    station_type[row_index] = msg.station_type;
    type_and_cargo[row_index] = msg.type_and_cargo;
    spare2[row_index] = msg.spare2;
    txrx_mode[row_index] = msg.txrx_mode;
    interval_raw[row_index] = msg.interval_raw;
    quiet[row_index] = msg.quiet;
    spare3[row_index] = msg.spare3;
  };

  Rcpp::List as_list() const {
    auto out = AIS_Msgs::init_as_list();
    const auto seq_out = Rcpp::seq(0, AIS_Msgs::common_row_index - 1);

    out["spare"] = spare[seq_out];
    out["lng_deg_1"] = lng_deg_1[seq_out];
    out["lat_deg_1"] = lat_deg_1[seq_out];
    out["lng_deg_2"] = lng_deg_2[seq_out];
    out["lat_deg_2"] = lat_deg_2[seq_out];
    out["station_type"] = station_type[seq_out];
    out["type_and_cargo"] = type_and_cargo[seq_out];
    out["spare2"] = spare2[seq_out];
    out["txrx_mode"] = txrx_mode[seq_out];
    out["interval_raw"] = interval_raw[seq_out];
    out["quiet"] = quiet[seq_out];
    out["spare3"] = spare3[seq_out];

    return out;
  };
};

#endif
