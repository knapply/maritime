#ifndef MARITIME_UTILS_HPP
#define MARITIME_UTILS_HPP

#include "Rcpp_compat.hpp"

typedef Rcpp::CharacterVector vec_chr;
typedef Rcpp::IntegerVector vec_int;
typedef Rcpp::LogicalVector vec_lgl;
typedef Rcpp::DoubleVector vec_dbl;

template <typename T>
inline int count_digits(const T x) {
  if (x < 0) {
    return count_digits(-x);
  }

  constexpr T x1 = 1e1;
  constexpr T x2 = 1e2;
  constexpr T x3 = 1e3;
  constexpr T x4 = 1e4;
  constexpr T x5 = 1e5;
  constexpr T x6 = 1e6;
  constexpr T x7 = 1e7;
  constexpr T x8 = 1e8;
  constexpr T x9 = 1e9;

  return x < x1
             ? 1
             : x < x2
                   ? 2
                   : x < x3
                         ? 3
                         : x < x4
                               ? 4
                               : x < x5
                                     ? 5
                                     : x < x6
                                           ? 6
                                           : x < x7
                                                 ? 7
                                                 : x < x8 ? 8 : x < x9 ? 9 : 10;
}

inline void finalize_df(Rcpp::List& x, const int& n_rows) {
  const int n_digits = count_digits(n_rows);

  vec_chr row_names(n_rows);
  for (int i = 0; i < n_rows; ++i) {
    char name[n_digits];
    sprintf(&(name[0]), "%d", i);
    row_names[i] = name;
  }

  x.attr("class") = "data.frame";
  x.attr("row.names") = row_names;
}

template <class Msg_Proto_DF>
inline SEXP as_df(Msg_Proto_DF&& msg_proto_df) {
  if (msg_proto_df.common_row_index == 0) {
    return R_NilValue;
  }
  auto out = msg_proto_df.as_list();
  finalize_df(out, msg_proto_df.common_row_index);
  return out;
}

// template <class Msg_Proto_DF>
// SEXP as_nested_df(const Msg_Proto_DF& msg_proto_df) {
//   if (msg_proto_df.common_row_index == 0) {
//     return R_NilValue;
//   }
//   auto out = msg_proto_df.as_nest();
//   finalize_df(out, msg_proto_df.common_row_index);
//   return out;
// }

//
//
#endif
