#ifndef MARITIME_UTILS_HPP
#define MARITIME_UTILS_HPP

namespace maritime {

inline void handle_mmap_error(const std::error_code& error) {
  const auto& errmsg = error.message();
  Rcpp::stop("error mapping file: %s, exiting...\n", errmsg.c_str());
}

inline void rstrip(std::string& s) {
  s.erase(std::find_if(s.rbegin(), s.rend(),
                       std::not1(std::ptr_fun<int, int>(std::isspace)))
              .base(),
          s.end());
}

inline int count_digits(const int x) {
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
  // constexpr R_xlen_t x10 = 1e10;
  // constexpr R_xlen_t x11 = 1e11;
  // constexpr R_xlen_t x12 = 1e12;
  // constexpr R_xlen_t x13 = 1e13;
  // constexpr R_xlen_t x14 = 1e14;
  // constexpr R_xlen_t x15 = 1e15;
  // constexpr R_xlen_t x16 = 1e16;
  // constexpr R_xlen_t x17 = 1e17;
  // constexpr R_xlen_t x18 = 1e18;

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
  // else if (x < x10) {
  //   return 10;
  // } else if (x < x11) {
  //   return 11;
  // } else if (x < x12) {
  //   return 12;
  // } else if (x < x13) {
  //   return 13;
  // } else if (x < x14) {
  //   return 14;
  // } else if (x < x15) {
  //   return 15;
  // } else if (x < x16) {
  //   return 16;
  // } else if (x < x17) {
  //   return 17;
  // } else if (x < x18) {
  //   return 18;
  // } else {
  //   return 19;
  // }
}

inline void _as_sf(Rcpp::List& x) {
  const vec_dbl lng = x["lng_deg"];
  const vec_dbl lat = x["lat_deg"];
  const std::size_t n_rows = lng.size();

  using Rcpp::_;
  auto crs = Rcpp::List::create(
      _["epsg"] = 4326,
      _["proj4string"] = "+proj=longlat +datum=WGS84 +no_defs");
  crs.attr("class") = "crs";

  const auto sf_point_class = vec_chr{"XY", "POINT", "sfg"};
  auto sfc = Rcpp::List(lng.size(), vec_dbl{NA_REAL, NA_REAL});
  vec_int bbox = {-180, -90, 180, 90};
  bbox.attr("names") = vec_chr{"xmin", "ymin", "xmax", "ymax"};

#pragma omp for simd
  for (std::size_t i = 0; i < n_rows; ++i) {
    const auto longitude = lng[i];
    const auto latitude = lat[i];

    bbox[0] = bbox[0] < longitude ? bbox[0] : longitude;
    bbox[1] = bbox[1] > longitude ? bbox[1] : longitude;
    bbox[2] = bbox[2] < latitude ? bbox[2] : latitude;
    bbox[3] = bbox[3] > latitude ? bbox[3] : latitude;

    auto sf_point = vec_dbl{longitude, latitude};
    sf_point.attr("class") = sf_point_class;

    sfc[i] = sf_point;
  }

  sfc.attr("n_empty") = 0;
  sfc.attr("precision") = 0;
  sfc.attr("crs") = crs;
  sfc.attr("bbox") = bbox;
  sfc.attr("class") = vec_chr{"sfc_POINT", "sfc"};

  // vec_chr col_names = x.attr("names");
  // col_names.push_back("geometry");
  // x.attr("names") = col_names;
  // x.push_back(geometry);
  auto agr_attr= vec_int(x.size(), NA_INTEGER);
  agr_attr.attr(".Label") = vec_chr{"constant", "aggregate", "identity"};
  agr_attr.attr("class") = "factor";
  x.attr("agr") = agr_attr;

  x["geometry"] = sfc;
  x.attr("sf_column") = "geometry";


  // const vec_chr old_class = x.attr("class");
  // vec_chr new_class(old_class.size() + 1);
  // new_class[0] = "sf";
  // for (int i = 1; i < old_class.size(); ++i) {
  //   new_class[i] = old_class[i - 1];
  // }

  // x.attr("class") = new_class;
}

inline void finalize_df(Rcpp::List& x,
                        // const int n_rows,
                        const vec_int seq_out,
                        const bool as_tibble,
                        const bool as_sf = false) {
  // const int n_digits = count_digits(n_rows);

  // vec_chr row_names(n_rows);
  // if (n_rows > 0) {
  //   for (int i = 0; i < n_rows; ++i) {
  //     char name[n_digits];
  //     sprintf(&(name[0]), "%d", i);
  //     row_names[i] = name;
  //   }
  // }

  if (as_sf) {
    _as_sf(x);
    if (as_tibble) {
      x.attr("class") = vec_chr{"sf", "tbl_df", "tbl", "data.frame"};
    } else {
      x.attr("class") = vec_chr{"sf", "data.frame"};
    }
  } else if (as_tibble) {
    x.attr("class") = vec_chr{"tbl_df", "tbl", "data.frame"};
  } else {
    x.attr("class") = "data.frame";
  }

  x.attr("row.names") = seq_out;
}

template <class msg_T>
inline Rcpp::List as_df(msg_T& ais_msg,
                        const bool as_tibble,
                        const bool as_sf) {
  auto out = ais_msg.as_list();
  finalize_df(out, ais_msg.common_row_index, as_tibble, as_sf);
  return out;
}

// void finalize_df2(Rcpp::List& x, const int& n_rows) {
//   const int n_digits = count_digits(n_rows);

//   vec_chr row_names(n_rows);
//   for (int i = 0; i < n_rows; ++i) {
//     char name[n_digits];
//     sprintf(&(name[0]), "%d", i);
//     row_names[i] = name;
//   }

//   x.attr("row.names") = row_names;
//   x.attr("class") = vec_chr{"data.frame"};
// }

}  // namespace maritime

#endif
