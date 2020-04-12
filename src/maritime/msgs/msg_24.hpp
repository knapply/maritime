#ifndef MARITIME_MSG_24_HPP
#define MARITIME_MSG_24_HPP

#include "msg.hpp"

class Msgs_24 : public AIS_Msgs<libais::Ais24> {
  vec_chr name;
  vec_int type_and_cargo;
  vec_chr vendor_id;
  vec_chr callsign;
  vec_int dim_a;
  vec_int dim_b;
  vec_int dim_c;
  vec_int dim_d;
  vec_int spare;

 public:
  Msgs_24(const int n)
      : AIS_Msgs::AIS_Msgs(n),
        name(n, NA_STRING),
        type_and_cargo(n, NA_INTEGER),
        vendor_id(n, NA_STRING),
        callsign(n, NA_STRING),
        dim_a(n, NA_INTEGER),
        dim_b(n, NA_INTEGER),
        dim_c(n, NA_INTEGER),
        dim_d(n, NA_INTEGER),
        spare(n, NA_INTEGER){};

  void push(libais::Ais24&& msg,
            const std::size_t _line_number,
            const double _time) {
    if (msg.had_error()) {
      return;
    }

    if (msg.part_num != 0 || msg.part_num != 1) {
      return;
    }

    const auto row_index = AIS_Msgs::common_row_index;
    AIS_Msgs::init_push(msg.message_id, msg.repeat_indicator, msg.mmsi,
                        _line_number, _time);

    if (msg.part_num == 0) {
      name[row_index] = msg.name;
    } else if (msg.part_num == 1) {
      type_and_cargo[row_index] = msg.type_and_cargo;
      vendor_id[row_index] = msg.vendor_id;
      callsign[row_index] = msg.callsign;
      dim_a[row_index] = msg.dim_a;
      dim_b[row_index] = msg.dim_b;
      dim_c[row_index] = msg.dim_c;
      dim_d[row_index] = msg.dim_d;
      spare[row_index] = msg.spare;
    }
  };

  Rcpp::List as_list() const {
    auto out = AIS_Msgs::init_as_list();
    const auto seq_out = Rcpp::seq(0, AIS_Msgs::common_row_index - 1);

    out["name"] = out[seq_out];
    out["type_and_cargo"] = out[seq_out];
    out["vendor_id"] = out[seq_out];
    out["callsign"] = out[seq_out];
    out["dim_a"] = out[seq_out];
    out["dim_b"] = out[seq_out];
    out["dim_c"] = out[seq_out];
    out["dim_d"] = out[seq_out];
    out["spare"] = out[seq_out];

    return out;
  };
};

#endif