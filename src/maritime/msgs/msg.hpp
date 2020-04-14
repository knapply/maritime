#ifndef MARITIME_MSG_HPP
#define MARITIME_MSG_HPP

#include "../../ais.h"
#include "../utils.hpp"

struct Msg_Pack {
  double time;
  std::size_t line_number;
  int message_id;
  int repeat_indicator;
  int mmsi;
};

template <class libais_T>
class AIS_Msgs {
 public:
  std::size_t common_row_index;
  vec_dbl time;
  vec_int line_number;
  vec_int message_id;
  vec_int repeat_indicator;
  vec_int mmsi;

 public:
  explicit AIS_Msgs(const std::size_t n)
      : common_row_index(0),
        time(n, NA_REAL),
        line_number(n, NA_INTEGER),
        message_id(n, NA_INTEGER),
        repeat_indicator(n, NA_INTEGER),
        mmsi(n, NA_INTEGER) {
    time.attr("class") = vec_chr::create("POSIXct", "POSIXt");
    time.attr("tzone") = "UTC";
  };

  void init_push(const int _message_id,
                 const int _repeat_indicator,
                 const int _mmsi,
                 const std::size_t _line_number,
                 const double _time) {
    // if (_time_start != 0) {
    this->line_number[common_row_index] = _line_number + 1;
    this->time[common_row_index] = _time != 0 ? _time : NA_REAL;
    // }
    // if (_time_end != 0) {
    // this->time_end[common_row_index] = _time_end;
    // }

    this->message_id[common_row_index] = _message_id;
    this->repeat_indicator[common_row_index] = _repeat_indicator;
    this->mmsi[common_row_index] = _mmsi;

    this->common_row_index++;
  };

  void init_push(Msg_Pack&& msg_pack) {
    this->line_number[common_row_index] = msg_pack.line_number + 1;
    this->time[common_row_index] = msg_pack.time != 0 ? msg_pack.time : NA_REAL;
    this->message_id[common_row_index] = msg_pack.message_id;
    this->repeat_indicator[common_row_index] = msg_pack.repeat_indicator;
    this->mmsi[common_row_index] = msg_pack.mmsi;

    this->common_row_index++;
  };

  Rcpp::List init_as_list() const {
    const auto seq_out = Rcpp::seq(0, this->common_row_index - 1);
    Rcpp::List out;

    out["time"] = std::move(this->time[seq_out]);
    out["first_line_number"] = std::move(this->line_number[seq_out]);
    out["message_id"] = std::move(this->message_id[seq_out]);
    out["repeat_indicator"] = std::move(this->repeat_indicator[seq_out]);
    out["mmsi"] = std::move(this->mmsi[seq_out]);

    return out;
  };
};

#endif