#ifndef MARITIME_NESTED_MSGS_HPP
#define MARITIME_NESTED_MSGS_HPP

#include "msg.hpp"

template <class libais_T>
inline SEXP get_geometry(const libais_T& msg) {
  return Rcpp::List::create(NA_REAL, NA_REAL);
}

template <>
inline SEXP get_geometry<Rcpp::XPtr<libais::Ais1_2_3>>(
    const Rcpp::XPtr<libais::Ais1_2_3>& msg) {
  return Rcpp::List::create(msg->position.lng_deg, msg->position.lat_deg);
}

// Nest
// ========================================================================================
// typedef Rcpp::Xptr<libais::AisMsg> aisptr;

class Nest {
 public:
  std::size_t common_row_index;
  vec_int time_start;
  vec_int time_end;
  vec_int message_id;
  vec_int mmsi;
  Rcpp::List msg_data;
  Rcpp::List geometry;

 public:
  explicit Nest(const std::size_t n)
      : common_row_index(0),
        time_start(n),
        time_end(n),
        message_id(n),
        mmsi(n),
        msg_data(n),
        geometry(n, vec_dbl(2, NA_REAL)) {
    time_start.attr("class") = vec_chr{"POSIXct", "POSIXt"};
    time_start.attr("tzone") = "UTC";

    time_end.attr("class") = vec_chr{"POSIXct", "POSIXt"};
    time_end.attr("tzone") = "UTC";
  };

  // template <class libais_T>
  void push(Rcpp::XPtr<libais::AisMsg> msg,
            const double _time_start,
            const double _time_end) {
    //
    if (msg->had_error()) {
      return;
    }

    // this->ais_pointers[this->common_row_index] =
    // Rcpp::XPtr<libais::AisMsg>(new libais::AisMsg, true),         //
    // true                                      //
    // );
    // new libais::AisMsg(msg), false                                         //
    // );

    this->time_start[common_row_index] = _time_start;
    this->time_end[common_row_index] = _time_end;

    this->message_id[common_row_index] = msg->message_id;
    this->mmsi[common_row_index] = msg->mmsi;

    this->msg_data[common_row_index] = msg;

    this->geometry[this->common_row_index] = get_geometry(msg);

    this->common_row_index++;
  };

  Rcpp::List as_list() const {
    const auto seq_out = Rcpp::seq(0, this->common_row_index - 1);

    Rcpp::List out;
    out["time_start"] = this->time_start[seq_out];
    out["time_end"] = this->time_end[seq_out];
    out["message_id"] = this->message_id[seq_out];
    out["mmsi"] = this->mmsi[seq_out];
    out["msg"] = this->msg_data[seq_out];
    out["geometry"] = this->geometry[seq_out];

    return out;
  };
};

#endif