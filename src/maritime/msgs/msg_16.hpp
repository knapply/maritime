#ifndef MARITIME_MSG_16_HPP
#define MARITIME_MSG_16_HPP

#include "msg.hpp"

class Msgs_16 : public AIS_Msgs<libais::Ais16> {
  vec_int spare;
  vec_int dest_mmsi_a;
  vec_int offset_a;
  vec_int inc_a;
  vec_int spare2;
  vec_int dest_mmsi_b;
  vec_int offset_b;
  vec_int inc_b;

 public:
  Msgs_16(const int n)
      : AIS_Msgs::AIS_Msgs(n),
        spare(n, NA_INTEGER),
        dest_mmsi_a(n, NA_INTEGER),
        offset_a(n, NA_INTEGER),
        inc_a(n, NA_INTEGER),
        spare2(n, NA_INTEGER),
        dest_mmsi_b(n, NA_INTEGER),
        offset_b(n, NA_INTEGER),
        inc_b(n, NA_INTEGER){};

  void push(libais::Ais16&& msg,
            const std::size_t _line_number,
            const double _time) {
    if (msg.had_error()) {
      return;
    }
    const auto row_index = AIS_Msgs::common_row_index;
    AIS_Msgs::init_push(msg.message_id, msg.repeat_indicator, msg.mmsi,
                        _line_number, _time);

    spare[row_index] = msg.spare;
    dest_mmsi_a[row_index] = msg.dest_mmsi_a;
    offset_a[row_index] = msg.offset_a;
    inc_a[row_index] = msg.inc_a;

    if (-1 != msg.spare2) {
      spare2[row_index] = msg.spare2;
    }
    if (-1 != msg.dest_mmsi_b) {
      dest_mmsi_b[row_index] = msg.dest_mmsi_b;
      offset_b[row_index] = msg.offset_b;
      inc_b[row_index] = msg.inc_b;
    }
  };

  Rcpp::List as_list() const {
    auto out = AIS_Msgs::init_as_list();
    const auto seq_out = Rcpp::seq(0, AIS_Msgs::common_row_index - 1);

    out["spare"] = spare[seq_out];
    out["dest_mmsi_a"] = dest_mmsi_a[seq_out];
    out["offset_a"] = offset_a[seq_out];
    out["inc_a"] = inc_a[seq_out];
    out["spare2"] = spare2[seq_out];
    out["dest_mmsi_b"] = dest_mmsi_b[seq_out];
    out["offset_b"] = offset_b[seq_out];
    out["inc_b"] = inc_b[seq_out];

    return out;
  };
};

#endif