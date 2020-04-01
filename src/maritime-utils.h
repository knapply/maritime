#ifndef MARITIME_UTILS_H
#define MARITIME_UTILS_H

#include <Rcpp.h>

typedef Rcpp::CharacterVector vec_chr;
typedef Rcpp::IntegerVector vec_int;
typedef Rcpp::LogicalVector vec_lgl;
typedef Rcpp::DoubleVector vec_dbl;

namespace maritime {

inline void handle_error(const std::string& message,
                         const std::error_code& error) {
  const auto& errmsg = error.message();
  Rcpp::stop(message.c_str(), errmsg.c_str());
}

inline void rstrip(std::string& s) {
  s.erase(std::find_if(s.rbegin(), s.rend(),
                       std::not1(std::ptr_fun<int, int>(std::isspace)))
              .base(),
          s.end());
}

inline void finalize_df(Rcpp::List& x, const int& n_rows) {
  vec_chr row_names(n_rows);
  for (int i = 0; i < n_rows; ++i) {
    char name[10];
    sprintf(&(name[0]), "%d", i);
    row_names[i] = name;
  }

  x.attr("class") = "data.frame";
  x.attr("row.names") = row_names;
}


template <class msg_T>
inline Rcpp::List as_df(msg_T& ais_msg) {
  auto out = ais_msg.as_list();
  finalize_df(out, ais_msg.common_row_index);
  return out;
}

}  // namespace maritime

#endif
