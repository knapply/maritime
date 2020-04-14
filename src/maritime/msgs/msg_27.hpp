#ifndef MARITIME_MSG_27_HPP
#define MARITIME_MSG_27_HPP

#include "msg.hpp"

class Msgs_27 : public AIS_Msgs<libais::Ais27> {
  vec_int position_accuracy;
  vec_int raim;
  vec_int nav_status;
  vec_dbl lng_deg;
  vec_dbl lat_deg;
  vec_dbl sog;
  vec_dbl cog;
  vec_lgl gnss;
  vec_int spare;

 public:
  Msgs_27(const int n)
      : AIS_Msgs::AIS_Msgs(n),
        position_accuracy(n, NA_INTEGER),
        raim(n, NA_LOGICAL),
        nav_status(n, NA_INTEGER),
        lng_deg(n, NA_REAL),
        lat_deg(n, NA_REAL),
        sog(n, NA_REAL),
        cog(n, NA_REAL),
        gnss(n, NA_LOGICAL),
        spare(n, NA_INTEGER){};

  void push(libais::Ais27&& msg,
            const std::size_t _line_number,
            const double _time) {
    if (msg.had_error()) {
      return;
    }
    const auto row_index = AIS_Msgs::common_row_index;
    AIS_Msgs::init_push(msg.message_id, msg.repeat_indicator, msg.mmsi,
                        _line_number, _time);
    position_accuracy[row_index] = msg.position_accuracy;
    raim[row_index] = msg.raim;
    nav_status[row_index] = msg.nav_status;
    lng_deg[row_index] = msg.position.lng_deg;
    lat_deg[row_index] = msg.position.lat_deg;
    sog[row_index] = msg.sog;
    cog[row_index] = msg.cog;
    gnss[row_index] = msg.gnss;
    spare[row_index] = msg.spare;
  };

  Rcpp::List as_list() const {
    auto out = AIS_Msgs::init_as_list();
    const auto seq_out = Rcpp::seq(0, AIS_Msgs::common_row_index - 1);

    out["position_accuracy"] = position_accuracy[seq_out];
    out["raim"] = raim[seq_out];
    out["nav_status"] = nav_status[seq_out];
    out["lng_deg"] = lng_deg[seq_out];
    out["lat_deg"] = lat_deg[seq_out];
    out["sog"] = sog[seq_out];
    out["cog"] = cog[seq_out];
    out["gnss"] = gnss[seq_out];
    out["spare"] = spare[seq_out];

    return out;
  };
};

#endif