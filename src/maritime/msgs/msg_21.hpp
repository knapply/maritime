#ifndef MARITIME_MSG_21_HPP
#define MARITIME_MSG_21_HPP

#include "msg.hpp"

class Msgs_21 : public AIS_Msgs<libais::Ais21> {
  vec_int spare;
  vec_int aton_type;
  vec_chr name;
  vec_int position_accuracy;
  vec_dbl lng_deg;
  vec_dbl lat_deg;
  vec_int dim_a;
  vec_int dim_b;
  vec_int dim_c;
  vec_int dim_d;
  vec_int fix_type;
  vec_int timestamp;
  vec_lgl off_pos;
  vec_int aton_status;
  vec_lgl raim;
  vec_lgl virtual_aton;
  vec_lgl assigned_mode;

 public:
  Msgs_21(const int n)
      : AIS_Msgs::AIS_Msgs(n),
        spare(n, NA_INTEGER),
        aton_type(n, NA_INTEGER),
        name(n, NA_STRING),
        position_accuracy(n, NA_INTEGER),
        lng_deg(n, NA_REAL),
        lat_deg(n, NA_REAL),
        dim_a(n, NA_INTEGER),
        dim_b(n, NA_INTEGER),
        dim_c(n, NA_INTEGER),
        dim_d(n, NA_INTEGER),
        fix_type(n, NA_INTEGER),
        timestamp(n, NA_INTEGER),
        off_pos(n, NA_LOGICAL),
        aton_status(n, NA_INTEGER),
        raim(n, NA_LOGICAL),
        virtual_aton(n, NA_LOGICAL),
        assigned_mode(n, NA_LOGICAL){};

  void push(libais::Ais21&& msg,
            const std::size_t _line_number,
            const double _time) {
    if (msg.had_error()) {
      return;
    }
    const auto row_index = AIS_Msgs::common_row_index;
    AIS_Msgs::init_push(msg.message_id, msg.repeat_indicator, msg.mmsi,
                        _line_number, _time);

    spare[row_index] = msg.spare;
    aton_type[row_index] = msg.aton_type;
    name[row_index] = msg.name;
    position_accuracy[row_index] = msg.position_accuracy;
    lng_deg[row_index] = msg.position.lng_deg;
    lat_deg[row_index] = msg.position.lat_deg;
    dim_a[row_index] = msg.dim_a;
    dim_b[row_index] = msg.dim_b;
    dim_c[row_index] = msg.dim_c;
    dim_d[row_index] = msg.dim_d;
    fix_type[row_index] = msg.fix_type;
    timestamp[row_index] = msg.timestamp;
    off_pos[row_index] = msg.off_pos;
    aton_status[row_index] = msg.aton_status;
    raim[row_index] = msg.raim;
    virtual_aton[row_index] = msg.virtual_aton;
    assigned_mode[row_index] = msg.assigned_mode;
  };

  Rcpp::List as_list() const {
    auto out = AIS_Msgs::init_as_list();
    const auto seq_out = Rcpp::seq(0, AIS_Msgs::common_row_index - 1);

    out["spare"] = spare[seq_out];
    out["aton_type"] = aton_type[seq_out];
    out["name"] = name[seq_out];
    out["position_accuracy"] = position_accuracy[seq_out];
    out["lng_deg"] = lng_deg[seq_out];
    out["lat_deg"] = lat_deg[seq_out];
    out["dim_a"] = dim_a[seq_out];
    out["dim_b"] = dim_b[seq_out];
    out["dim_c"] = dim_c[seq_out];
    out["dim_d"] = dim_d[seq_out];
    out["fix_type"] = fix_type[seq_out];
    out["timestamp"] = timestamp[seq_out];
    out["off_pos"] = off_pos[seq_out];
    out["aton_status"] = aton_status[seq_out];
    out["raim"] = raim[seq_out];
    out["virtual_aton"] = virtual_aton[seq_out];
    out["assigned_mode"] = assigned_mode[seq_out];

    return out;
  };
};

#endif