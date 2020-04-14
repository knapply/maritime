#ifndef MARITIME_MSG_22_HPP
#define MARITIME_MSG_22_HPP

#include "msg.hpp"

class Msgs_22 : public AIS_Msgs<libais::Ais22> {
  vec_int spare;
  vec_int chan_a;
  vec_int chan_b;
  vec_int txrx_mode;
  vec_lgl power_low;
  vec_dbl lng_deg_1;
  vec_dbl lat_deg_1;
  vec_dbl lng_deg_2;
  vec_dbl lat_deg_2;
  vec_int dest_mmsi_1;
  vec_int dest_mmsi_2;
  vec_int chan_a_bandwidth;
  vec_int chan_b_bandwidth;
  vec_int zone_size;
  vec_int spare2;

 public:
  Msgs_22(const int n)
      : AIS_Msgs::AIS_Msgs(n),
        spare(n, NA_INTEGER),
        chan_a(n, NA_INTEGER),
        chan_b(n, NA_INTEGER),
        txrx_mode(n, NA_INTEGER),
        power_low(n, NA_LOGICAL),
        lng_deg_1(n, NA_REAL),
        lat_deg_1(n, NA_REAL),
        lng_deg_2(n, NA_REAL),
        lat_deg_2(n, NA_REAL),
        dest_mmsi_1(n, NA_INTEGER),
        dest_mmsi_2(n, NA_INTEGER),
        chan_a_bandwidth(n, NA_INTEGER),
        chan_b_bandwidth(n, NA_INTEGER),
        zone_size(n, NA_INTEGER),
        spare2(n, NA_INTEGER){};

  void push(libais::Ais22&& msg,
            const std::size_t _line_number,
            const double _time) {
    if (msg.had_error()) {
      return;
    }
    const auto row_index = AIS_Msgs::common_row_index;
    AIS_Msgs::init_push(msg.message_id, msg.repeat_indicator, msg.mmsi,
                        _line_number, _time);
    spare[row_index] = msg.spare;
    chan_a[row_index] = msg.chan_a;
    chan_b[row_index] = msg.chan_b;
    txrx_mode[row_index] = msg.txrx_mode;
    power_low[row_index] = msg.power_low;

    if (msg.pos_valid) {
      lng_deg_1[row_index] = msg.position1.lng_deg;
      lat_deg_1[row_index] = msg.position1.lat_deg;
      lng_deg_2[row_index] = msg.position2.lng_deg;
      lat_deg_2[row_index] = msg.position1.lat_deg;
    } else {
      dest_mmsi_1[row_index] = msg.dest_mmsi_1;
      dest_mmsi_2[row_index] = msg.dest_mmsi_2;
    }

    chan_a_bandwidth[row_index] = msg.chan_a_bandwidth;
    chan_b_bandwidth[row_index] = msg.chan_b_bandwidth;
    zone_size[row_index] = msg.zone_size;
    spare2[row_index] = msg.spare2;
  };

  Rcpp::List as_list() const {
    auto out = AIS_Msgs::init_as_list();
    const auto seq_out = Rcpp::seq(0, AIS_Msgs::common_row_index - 1);

    out["spare"] = spare[seq_out];
    out["chan_a"] = chan_a[seq_out];
    out["chan_b"] = chan_b[seq_out];
    out["txrx_mode"] = txrx_mode[seq_out];
    out["power_low"] = power_low[seq_out];
    out["lng_deg_1"] = lng_deg_1[seq_out];
    out["lat_deg_1"] = lat_deg_1[seq_out];
    out["lng_deg_2"] = lng_deg_2[seq_out];
    out["lat_deg_2"] = lat_deg_2[seq_out];
    out["dest_mmsi_1"] = dest_mmsi_1[seq_out];
    out["dest_mmsi_2"] = dest_mmsi_2[seq_out];
    out["chan_a_bandwidth"] = chan_a_bandwidth[seq_out];
    out["chan_b_bandwidth"] = chan_b_bandwidth[seq_out];
    out["zone_size"] = zone_size[seq_out];
    out["spare2"] = spare2[seq_out];

    return out;
  };
};

#endif
