#include "ais.h"
#include "maritime/decoder.hpp"

// [[Rcpp::export(.nmea_df)]]
SEXP nmea_df(const std::string& file_path, const int n_max) {
  const auto nmea_stream = NMEA_Stream::from_file(file_path);
  return nmea_stream.as_df(n_max);
}

// //ff [[Rcpp::export(.nest_test)]]
// SEXP nest_test(const std::string& file_path) {
//   const auto nmea_stream = NMEA_Stream::from_file(file_path);
//   const Decoder decoder(nmea_stream);

//   const auto n_msgs = decoder.msg_counts.at(MSG_TYPE::msg_1_2_3);
//   const auto total_msgs = decoder.nmea_stream.complete.size();

//   Progress progress(total_msgs, true);

//   Nest_1_2_3 res(n_msgs);
//   for (std::size_t i = 0; i < total_msgs; ++i) {
//     progress.increment();
//     const auto nmea = decoder.nmea_stream.complete[i];

//     if (get_msg_type(nmea.payload) == MSG_TYPE::msg_1_2_3) {
//       res.push(libais::Ais1_2_3(nmea.payload.data.c_str(), nmea.fill_bits),
//       //
//                nmea.time_start, nmea.time_end);
//     }
//   }
//   const auto out = res.as_list();
//   return as_df(res);
// }

SEXP decode_filter_file_switch(const std::string& file_path,
                               const int msg_type,
                               const bool verbose) {
  const auto enum_msg_type = static_cast<MSG_TYPE>(msg_type);

  switch (enum_msg_type) {
    case MSG_TYPE::msg_1_2_3:
      return decode_filter_file<MSG_TYPE::msg_1_2_3, Msgs_1_2_3,  //
                                libais::Ais1_2_3>(file_path, verbose);

    case MSG_TYPE::msg_4_11:
      return decode_filter_file<MSG_TYPE::msg_4_11, Msgs_4_11,  //
                                libais::Ais4_11>(file_path, verbose);

    case MSG_TYPE::msg_5:
      return decode_filter_file<MSG_TYPE::msg_5, Msgs_5,  //
                                libais::Ais5>(file_path, verbose);
      // 6
      // case MSG_TYPE:::
      //   return decode_filter_file<MSG_TYPE::, ,  //
      //                             libais::>(file_path);

    case MSG_TYPE::msg_7_13:
      return decode_filter_file<MSG_TYPE::msg_7_13, Msgs_7_13,  //
                                libais::Ais7_13>(file_path, verbose);

      // 8
      // case MSG_TYPE:::
      //   return decode_filter_file<MSG_TYPE::, ,  //
      //                             libais::>(file_path);

    case MSG_TYPE::msg_9:
      return decode_filter_file<MSG_TYPE::msg_9, Msgs_9,  //
                                libais::Ais9>(file_path, verbose);

    case MSG_TYPE::msg_10:
      return decode_filter_file<MSG_TYPE::msg_10, Msgs_10,  //
                                libais::Ais10>(file_path, verbose);

    default:
      return R_NilValue;
  }
}

// [[Rcpp::export(.ais_decode_file_filter)]]
SEXP decode_filter_file_impl(const std::string& file_path,
                             const int msg_type,
                             const bool verbose) {
  return decode_filter_file_switch(file_path, msg_type, verbose);
}

// [[Rcpp::export(.ais_decode_file_list)]]
SEXP decode_list_file_impl(const std::string& file_path, const bool verbose) {
  return decode_list_file(file_path, verbose);
}

//
//
//

/*** R
file_path <- "inst/example-data/big-files/20181210.log"
# file_path <- "inst/example-data/20181101.log"
test_lines <- readr::read_lines(file_path, n_max = 10)
# test_text <- readr::read_file(file_path)
# test_lines[1:10]
mat <- stringr::str_split(test_lines[1:20], ",",simplify = TRUE)

test <- tibble::as_tibble(.nest_test(file_path))
# lapply(test$msg_specific_values, tibble::as_tibble)
# nchar(mat[,8])
# nchar(mat[,9])
test1 <- .nmea_df(file_path, n_max = -1)
tibble::as_tibble(test1)
tibble::as_tibble(test1[test1$message_id == 7, ])
tibble::as_tibble(test1[test1$message_id == 10, ])
# test2 <-
# bench::mark(
  test2 <- .ais_decode_file_filter(file_path = file_path, 8)
# )
tibble::as_tibble(test2)

test3 <- .ais_decode_file_list(file_path)
res <- bench::mark(
  test3 <- .ais_decode_file_list(file_path)
); res
lapply(test3, tibble::as_tibble)

decode_all <- function(file_path, msgs = c(1, 2, 3, 5, 7, 8)) {
  lapply(msgs, function(.x) {
    .ais_decode_filter_file_impl(file_path, .x)
  })
}

res <- lapply(
  msgs,
  function(.x) tibble::as_tibble(.ais_decode_filter_file_impl(file_path, .x))
)

res
*/
