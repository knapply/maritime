#ifndef MARITIME_MSG_HPP
#define MARITIME_MSG_HPP

#include "../../ais.h"
#include "../utils.hpp"

template <class msg_T>
class AIS_Msgs {
 public:
  std::size_t common_row_index;
  vec_int time_start;
  vec_int time_end;
  vec_int message_id;
  vec_int repeat_indicator;
  vec_int mmsi;

 public:
  explicit AIS_Msgs(const std::size_t n)
      : common_row_index(0),
        time_start(n, NA_REAL),
        time_end(n, NA_REAL),
        message_id(n, NA_INTEGER),
        repeat_indicator(n, NA_INTEGER),
        mmsi(n, NA_INTEGER) {
    time_start.attr("class") = vec_chr{"POSIXct", "POSIXt"};
    time_start.attr("tzone") = "UTC";

    time_end.attr("class") = vec_chr{"POSIXct", "POSIXt"};
    time_end.attr("tzone") = "UTC";
  };

  bool init_push(const msg_T& msg,
                 const double _time_start,
                 const double _time_end) {
    const auto success = !msg.had_error();

    if (success) {
      this->time_start[common_row_index] = _time_start;
      this->time_end[common_row_index] = _time_end;
      this->message_id[common_row_index] = msg.message_id;
      this->repeat_indicator[common_row_index] = msg.repeat_indicator;
      this->mmsi[common_row_index] = msg.mmsi;

      this->common_row_index++;
    }

    return success;
  };

  Rcpp::List init_as_list() const {
    const auto seq_out = Rcpp::seq(0, this->common_row_index - 1);

    Rcpp::List out;
    out["time_start"] = this->time_start[seq_out];
    out["time_end"] = this->time_end[seq_out];
    out["message_id"] = this->message_id[seq_out];
    out["repeat_indicator"] = this->repeat_indicator[seq_out];
    out["mmsi"] = this->mmsi[seq_out];

    return out;
  };
};

template <typename T, typename... Args>
std::unique_ptr<T> MakeUnique(Args &&... args) {
  return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

// template<>
inline Rcpp::XPtr<libais::AisMsg> as_ais_ptr(libais::AisMsg x) {
    // auto cloned = Rcpp::clone(x);
  //   static funcPtr timesTwo{ [](NumericVector x) -> NumericVector { return x
  //   * 2; }
//   Rcpp::XPtr<libais::AisMsg> ptr(&x, true);
//   ptr = x;
  //   ptr = *x;
//   Rcpp::as<Rcpp::XPtr<libais::AisMsg>>(x);

  return Rcpp::XPtr<libais::AisMsg>(&x, true);
}

// // template<MSG_TYPE msg_T>
// SEXP deref_ais_ptr(Rcpp::XPtr<libais::AisMsg> ais_ptr) {
//   if (ais_ptr.isNULL()) {
//     return R_NilValue;
//   }

//   switch ((*ais_ptr).message_id) {
//     case 1:
//     case 2:
//     case 3:
//       return Rcpp::wrap(reinterpret_cast<libais::Ais1_2_3*>(ais_ptr.get()));

//     default:
//       return R_NilValue;
//   }
// }

#endif