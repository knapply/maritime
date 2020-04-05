#ifndef MARITIME_UTILS_HPP
#define MARITIME_UTILS_HPP

#include <Rcpp.h>

typedef Rcpp::CharacterVector vec_chr;
typedef Rcpp::IntegerVector vec_int;
typedef Rcpp::LogicalVector vec_lgl;
typedef Rcpp::DoubleVector vec_dbl;

int count_digits(const int x) {
  if (x < 0) {
    return count_digits(-x);
  }

  constexpr int x1 = 1e1;
  constexpr int x2 = 1e2;
  constexpr int x3 = 1e3;
  constexpr int x4 = 1e4;
  constexpr int x5 = 1e5;
  constexpr int x6 = 1e6;
  constexpr int x7 = 1e7;
  constexpr int x8 = 1e8;
  constexpr int x9 = 1e9;

  if (x < x1) {
    return 1;
  } else if (x < x2) {
    return 2;
  } else if (x < x3) {
    return 3;
  } else if (x < x4) {
    return 4;
  } else if (x < x5) {
    return 5;
  } else if (x < x6) {
    return 6;
  } else if (x < x7) {
    return 7;
  } else if (x < x8) {
    return 8;
  } else if (x < x9) {
    return 9;
  } else {
    return 10;
  }
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
SEXP as_df(const Msg_Proto_DF& msg_proto_df) {
  if (msg_proto_df.common_row_index == 0) {
    return R_NilValue;
  }
  auto out = msg_proto_df.as_list();
  finalize_df(out, msg_proto_df.common_row_index);
  return out;
}

template <class Msg_Proto_DF>
SEXP as_nested_df(const Msg_Proto_DF& msg_proto_df) {
  if (msg_proto_df.common_row_index == 0) {
    return R_NilValue;
  }
  auto out = msg_proto_df.as_nest();
  finalize_df(out, msg_proto_df.common_row_index);
  return out;
}

//
//
#endif
