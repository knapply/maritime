#ifndef MARITIME_MSG_5_HPP
#define MARITIME_MSG_5_HPP

#include "msg.hpp"

class Msgs_5 : public AIS_Msgs<libais::Ais5> {
  vec_int ais_version;
  vec_int imo_num;
  vec_chr callsign;
  vec_chr name;
  vec_int type_and_cargo;
  vec_int dim_a;
  vec_int dim_b;
  vec_int dim_c;
  vec_int dim_d;
  vec_int fix_type;
  vec_int eta_month;
  vec_int eta_day;
  vec_int eta_hour;
  vec_int eta_minute;
  vec_dbl draught;
  vec_chr destination;
  vec_int dte;
  vec_int spare;

 public:
  Msgs_5(const int n)
      : AIS_Msgs::AIS_Msgs(n),
        ais_version(n, NA_INTEGER),
        imo_num(n, NA_INTEGER),
        callsign(n, NA_STRING),
        name(n, NA_STRING),
        type_and_cargo(n, NA_INTEGER),
        dim_a(n, NA_INTEGER),
        dim_b(n, NA_INTEGER),
        dim_c(n, NA_INTEGER),
        dim_d(n, NA_INTEGER),
        fix_type(n, NA_INTEGER),
        eta_month(n, NA_INTEGER),
        eta_day(n, NA_INTEGER),
        eta_hour(n, NA_INTEGER),
        eta_minute(n, NA_INTEGER),
        draught(n, NA_REAL),
        destination(n, NA_STRING),
        dte(n, NA_INTEGER),
        spare(n, NA_INTEGER){};

  void push(libais::Ais5&& msg,
            const std::size_t _line_number,
            const double _time) {
    const auto row_index = AIS_Msgs::common_row_index;
    if (msg.had_error()) {
      return;
    }
    AIS_Msgs::init_push(msg.message_id, msg.repeat_indicator, msg.mmsi,
                        _line_number, _time);

    this->ais_version[row_index] = msg.ais_version;
    this->imo_num[row_index] = msg.imo_num;
    this->callsign[row_index] = msg.callsign;
    this->name[row_index] = msg.name;
    this->type_and_cargo[row_index] = msg.type_and_cargo;
    this->dim_a[row_index] = msg.dim_a;
    this->dim_b[row_index] = msg.dim_b;
    this->dim_c[row_index] = msg.dim_c;
    this->dim_d[row_index] = msg.dim_d;
    this->fix_type[row_index] = msg.fix_type;
    this->eta_month[row_index] = msg.eta_month;
    this->eta_day[row_index] = msg.eta_day;
    this->eta_hour[row_index] = msg.eta_hour;
    this->eta_minute[row_index] = msg.eta_minute;
    this->draught[row_index] = msg.draught;
    this->destination[row_index] = msg.destination;
    this->dte[row_index] = msg.dte;
    this->spare[row_index] = msg.spare;
  }

  Rcpp::List as_list() const {
    auto out = AIS_Msgs::init_as_list();
    const auto seq_out = Rcpp::seq(0, this->common_row_index - 1);

    out["ais_version"] = this->ais_version[seq_out];
    out["imo_num"] = this->imo_num[seq_out];
    out["callsign"] = this->callsign[seq_out];
    out["name"] = this->name[seq_out];
    out["type_and_cargo"] = this->type_and_cargo[seq_out];
    out["dim_a"] = this->dim_a[seq_out];
    out["dim_b"] = this->dim_b[seq_out];
    out["dim_c"] = this->dim_c[seq_out];
    out["dim_d"] = this->dim_d[seq_out];
    out["fix_type"] = this->fix_type[seq_out];
    out["eta_month"] = this->eta_month[seq_out];
    out["eta_day"] = this->eta_day[seq_out];
    out["eta_hour"] = this->eta_hour[seq_out];
    out["eta_minute"] = this->eta_minute[seq_out];
    out["draught"] = this->draught[seq_out];
    out["destination"] = this->destination[seq_out];
    out["dte"] = this->dte[seq_out];
    out["spare"] = this->spare[seq_out];

    return out;
  };
};

#endif
