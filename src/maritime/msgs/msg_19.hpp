#ifndef MARITIME_MSG_19_HPP
#define MARITIME_MSG_19_HPP

#include "msg.hpp"

class Msgs_19 : public AIS_Msgs<libais::Ais19> {
  vec_int spare;
  vec_dbl sog;
  vec_int position_accuracy;
  vec_dbl lng_deg;
  vec_dbl lat_deg;
  vec_dbl cog;
  vec_int true_heading;
  vec_int timestamp;
  vec_int spare2;
  vec_chr name;
  vec_int type_and_cargo;
  vec_int dim_a;
  vec_int dim_b;
  vec_int dim_c;
  vec_int dim_d;
  vec_int fix_type;
  vec_lgl raim;
  vec_int dte;
  vec_int assigned_mode;
  vec_int spare3;

 public:
  Msgs_19(const int n)
      : AIS_Msgs::AIS_Msgs(n),
        spare(n, NA_INTEGER),
        sog(n, NA_REAL),
        position_accuracy(n, NA_INTEGER),
        lng_deg(n, NA_REAL),
        lat_deg(n, NA_REAL),
        cog(n, NA_REAL),
        true_heading(n, NA_INTEGER),
        timestamp(n, NA_INTEGER),
        spare2(n, NA_INTEGER),
        name(n, NA_STRING),
        type_and_cargo(n, NA_INTEGER),
        dim_a(n, NA_INTEGER),
        dim_b(n, NA_INTEGER),
        dim_c(n, NA_INTEGER),
        dim_d(n, NA_INTEGER),
        fix_type(n, NA_INTEGER),
        raim(n, NA_LOGICAL),
        dte(n, NA_INTEGER),
        assigned_mode(n, NA_INTEGER),
        spare3(n, NA_INTEGER){};

  void push(libais::Ais19&& msg,
            const std::size_t _line_number,
            const double _time) {
    if (msg.had_error()) {
      return;
    }
    const auto row_index = AIS_Msgs::common_row_index;
    AIS_Msgs::init_push(msg.message_id, msg.repeat_indicator, msg.mmsi,
                        _line_number, _time);

    spare[row_index] = msg.spare;
    sog[row_index] = msg.sog;
    position_accuracy[row_index] = msg.position_accuracy;
    lng_deg[row_index] = msg.position.lng_deg;
    lat_deg[row_index] = msg.position.lat_deg;
    cog[row_index] = msg.cog;
    true_heading[row_index] = msg.true_heading;
    timestamp[row_index] = msg.timestamp;
    spare2[row_index] = msg.spare2;
    name[row_index] = msg.name;
    type_and_cargo[row_index] = msg.type_and_cargo;
    dim_a[row_index] = msg.dim_a;
    dim_b[row_index] = msg.dim_b;
    dim_c[row_index] = msg.dim_c;
    dim_d[row_index] = msg.dim_d;
    fix_type[row_index] = msg.fix_type;
    raim[row_index] = msg.raim;
    dte[row_index] = msg.dte;
    assigned_mode[row_index] = msg.assigned_mode;
    spare3[row_index] = msg.spare3;
  };

  Rcpp::List as_list() const {
    auto out = AIS_Msgs::init_as_list();
    const auto seq_out = Rcpp::seq(0, AIS_Msgs::common_row_index - 1);
    
    out["spare"] = spare[seq_out];
    out["sog"] = sog[seq_out];
    out["position_accuracy"] = position_accuracy[seq_out];
    out["lng_deg"] = lng_deg[seq_out];
    out["lat_deg"] = lat_deg[seq_out];
    out["cog"] = cog[seq_out];
    out["true_heading"] = true_heading[seq_out];
    out["timestamp"] = timestamp[seq_out];
    out["spare2"] = spare2[seq_out];
    out["name"] = name[seq_out];
    out["type_and_cargo"] = type_and_cargo[seq_out];
    out["dim_a"] = dim_a[seq_out];
    out["dim_b"] = dim_b[seq_out];
    out["dim_c"] = dim_c[seq_out];
    out["dim_d"] = dim_d[seq_out];
    out["fix_type"] = fix_type[seq_out];
    out["raim"] = raim[seq_out];
    out["dte"] = dte[seq_out];
    out["assigned_mode"] = assigned_mode[seq_out];
    out["spare3"] = spare3[seq_out];

    return out;
  };
};

#endif
