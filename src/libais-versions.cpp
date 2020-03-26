#include "maritime.h"


//' `libais` Version Information
//'
//' Version info for [libais](https://github.com/schwehr/libais).
//'
//' @examples
//' ais_version()
//'
//' @export
// [[Rcpp::export]]
Rcpp::List ais_version() {
  auto out = Rcpp::List::create(
      Rcpp::IntegerVector({LIBAIS_VERSION_MAJOR, LIBAIS_VERSION_MINOR}));
  out.attr("class") = "numeric_version";
  return out;
}




// // void handle_error(const std::error_code& error) {
// //   const auto& errmsg = error.message();
// //   Rcpp::stop("error mapping file: %s, exiting...\n", errmsg.c_str());
// // }

////ffff [[Rcpp::export(.ais_decode_strings)]]
// Rcpp::List ais_decode_strings(const Rcpp::CharacterVector& x,
//                               const bool as_df,
//                               const bool verbose) {
//   const std::size_t n(x.size());
//   std::vector<std::string> bodies(n);
//   std::vector<maritime::ais::MSG_TYPE> msg_types(n);

// #pragma omp parallel for
//   for (std::size_t i = 0; i < n; ++i) {
//     bodies[i] = maritime::ais::get_body((char*)x[i]);
//     msg_types[i] = maritime::ais::get_msg_type(bodies[i]);
//   }

//   Progress progress(n, verbose);
//   Rcpp::List out(n);
//   for (std::size_t i = 0; i < n; ++i) {
//     progress.increment();
//     switch (msg_types[i]) {
//       case maritime::ais::MSG_TYPE::msg_1_2_3:
//         out[i] =
//             as_df ? maritime::ais::Msgs_1_2_3::from_nmea(bodies[i]).as_df()
//                   : maritime::ais::Msgs_1_2_3::from_nmea(bodies[i]).as_list();
//         break;

//       default:
//         break;
//     }
//   }

//   return out;
// }

// fff// [[Rcpp::export(.ais_decode_file)]]
// SEXP ais_decode_file(const std::string& file_path,
//                      const bool as_df,
//                      const bool verbose) {
//   constexpr char delim = '\n';
//   //   constexpr int pad = 0;
//   constexpr int init_line_size = 70;

//   std::error_code error;
//   mio::mmap_source mmap;
//   mmap.map(file_path, error);
//   if (error) {
//     handle_error(error);
//   }

//   const auto file_size = mmap.size();

//   std::vector<std::size_t> offsets{0};
//   offsets.reserve(file_size / init_line_size);
//   for (std::size_t i = 0; i < file_size; ++i) {
//     if (mmap[i] == delim) {
//       offsets.push_back(i + 1);
//     }
//   }

//   const auto n_lines = offsets.size() - 1;
//   std::vector<std::string> bodies(n_lines);
//   std::vector<maritime::ais::MSG_TYPE> msg_types(n_lines);

// #pragma omp parallel for
//   for (std::size_t i = 0; i < n_lines; ++i) {
//     const std::string line(mmap.begin() + offsets[i],
//                            mmap.begin() + offsets[i + 1] - 1);
//     auto body = maritime::ais::get_body(line);

//     maritime::rstrip(body);
//     bodies[i] = body;
//     msg_types[i] = maritime::ais::get_msg_type(body);
//   }

//   mmap.unmap();

//   std::size_t n_msgs_1_2_3 = 0;
// #pragma omp parallel for reduction(+ : n_msgs_1_2_3)
//   for (std::size_t i = 0; i < n_lines; ++i) {
//     switch (msg_types[i]) {
//       case maritime::ais::MSG_TYPE::msg_1_2_3:
//         n_msgs_1_2_3++;
//         break;

//       default:
//         break;
//     }
//   }

//   Progress progress(n_lines, verbose);
//   maritime::ais::Msgs_1_2_3 out_1_2_3(n_msgs_1_2_3);
//   for (std::size_t i = 0; i < n_lines; ++i) {
//     progress.increment();

//     switch (msg_types[i]) {
//       case maritime::ais::MSG_TYPE::msg_1_2_3:
//         out_1_2_3.push(libais::Ais1_2_3(bodies[i].c_str(), 0));
//         break;

//       default:
//         break;
//     }
//   }

//   return as_df ? maritime::as_df(out_1_2_3) : out_1_2_3.as_list();
// }
