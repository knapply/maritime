#include "ais.h"
// #include "maritime/decoder.hpp"
#include "maritime/decoder2.hpp"
// #include "maritime/msgs2/msg.hpp"
#include "maritime/proto_msg_dfs.hpp"

// inline SEXP as_df2(const AIS_df& ais_df) {
//   if (ais_df.row_index == 0) {
//     return R_NilValue;
//   }
//   auto out = ais_df.as_list();
//   finalize_df(out, ais_df.row_index);
//   return out;
// }

// 333// [[Rcpp::export(.ais_full_df)]]
// SEXP ais_full_df(const std::string& file_path) {
//   Decoder decoder(NMEA_Stream::from_file2(file_path));

//   auto n = decoder.nmea_stream.complete.size();

//   Progress progress(n, true);
//   AIS_df out(n);

//   for (std::size_t i = 0; i < n; ++i) {
//     progress.increment();

//     const auto nmea = std::move(decoder.nmea_stream.complete[i]);
//     // Rcpp::Rcout << nmea.payload.to_string << std::endl;

//     switch (get_msg_type(nmea.payload)) {
//       case MSG_TYPE::msg_1_2_3:
//         out.push(libais::Ais1_2_3(std::begin(nmea.payload.data),  //
//                                   nmea.fill_bits),                //
//                  nmea.time_start, nmea.time_end                   //
//         );                                                        //
//         break;

//         // Rcpp::Rcout << "b" << std::endl;

//       case MSG_TYPE::msg_4_11:
//         out.push(libais::Ais4_11(std::begin(nmea.payload.data),  //
//                                  nmea.fill_bits),                //
//                  nmea.time_start, nmea.time_end                  //
//         );                                                       //
//         break;

//         // Rcpp::Rcout << "c" << std::endl;

//       case MSG_TYPE::msg_5:
//         out.push(libais::Ais5(std::begin(nmea.payload.data),  //
//                               nmea.fill_bits),                //
//                  nmea.time_start, nmea.time_end               //
//         );                                                    //
//         break;

//         //   // Rcpp::Rcout << "d" << std::endl;

//       case MSG_TYPE::msg_7_13:
//         out.push(libais::Ais7_13(std::begin(nmea.payload.data),  //
//                                  nmea.fill_bits),                //
//                  nmea.time_start, nmea.time_end                  //
//         );                                                       //
//         break;

//       case MSG_TYPE::msg_9:
//         out.push(libais::Ais9(std::begin(nmea.payload.data),  //
//                               nmea.fill_bits),                //
//                  nmea.time_start, nmea.time_end               //
//         );                                                    //
//         break;

//       case MSG_TYPE::msg_10:
//         out.push(libais::Ais10(std::begin(nmea.payload.data),  //
//                                nmea.fill_bits),                //
//                  nmea.time_start, nmea.time_end                //
//         );                                                     //
//         break;

//       default:
//         continue;
//     }
//   }

//   return as_df2(out);
// }

//  44[[Rcpp::export(.nmea_df)]]
// SEXP nmea_df(const std::string& file_path, const int n_max) {
//   const auto nmea_stream = NMEA_Stream::from_file2(file_path);
//   return nmea_stream.as_df(n_max);
// }

// SEXP decode_filter_file_switch(const std::string& file_path,
//                                const int msg_type,
//                                const bool verbose) {
//   const auto enum_msg_type = static_cast<MSG_TYPE>(msg_type);

//   switch (enum_msg_type) {
//     case MSG_TYPE::msg_1_2_3:
//       return decode_filter_file<MSG_TYPE::msg_1_2_3, Msgs_1_2_3,  //
//                                 libais::Ais1_2_3>(file_path, verbose);

//     case MSG_TYPE::msg_4_11:
//       return decode_filter_file<MSG_TYPE::msg_4_11, Msgs_4_11,  //
//                                 libais::Ais4_11>(file_path, verbose);

//     case MSG_TYPE::msg_5:
//       return decode_filter_file<MSG_TYPE::msg_5, Msgs_5,  //
//                                 libais::Ais5>(file_path, verbose);
//       // 6
//       // case MSG_TYPE:::
//       //   return decode_filter_file<MSG_TYPE::, ,  //
//       //                             libais::>(file_path);

//     case MSG_TYPE::msg_7_13:
//       return decode_filter_file<MSG_TYPE::msg_7_13, Msgs_7_13,  //
//                                 libais::Ais7_13>(file_path, verbose);

//       // 8
//       // case MSG_TYPE:::
//       //   return decode_filter_file<MSG_TYPE::, ,  //
//       //                             libais::>(file_path);

//     case MSG_TYPE::msg_9:
//       return decode_filter_file<MSG_TYPE::msg_9, Msgs_9,  //
//                                 libais::Ais9>(file_path, verbose);

//     case MSG_TYPE::msg_10:
//       return decode_filter_file<MSG_TYPE::msg_10, Msgs_10,  //
//                                 libais::Ais10>(file_path, verbose);

//     default:
//       return R_NilValue;
//   }
// }

//ff [[Rcpp::export(.ais_decode_file_filter)]]
// SEXP decode_filter_file_impl(const std::string& file_path,
//                              const int msg_type,
//                              const bool verbose) {
//   return decode_filter_file_switch(file_path, msg_type, verbose);
// }

//ff [[Rcpp::export(.ais_decode_file_list)]]
// SEXP decode_list_file_impl(const std::string& file_path, const bool verbose) {
//   return decode_list_file(file_path, verbose);
// }

// [[Rcpp::export(.ais_decode_list2)]]
SEXP decode_list2(const std::string& file_path, const bool verbose) {
  // return Decoder2::from_file(file_path).build_df();
  return build_df(NMEA_Stream::from_file2(file_path));

  // return decoder.build_df();
  // return R_NilValue;
}

/*** R
library(data.table)
file_path <- "inst/example-data/big-files/20200131.log"
file_path <- "inst/example-data/20181101.log"

bench_mark <- bench::mark(
  # big_df = res1 <- rbindlist(.ais_decode_list2(file_path, TRUE),
                             # fill = TRUE, use.names = TRUE),
  df_list = res <- .ais_decode_list2(file_path, TRUE)
  
  ,
  iterations = 1,
  check = FALSE,
  filter_gc = FALSE
); bench_mark



tibble::as_tibble(data.table::rbindlist(res, use.names = TRUE, fill = TRUE)[order(first_line_number)])
lapply(res, tibble::as_tibble)
all <- data.table::rbindlist(res, idcol = "msg_type", fill = TRUE, use.names = TRUE)
tibble::as_tibble(res)

tibble::as_tibble(all[, .N, by = msg_type][, N := N / sum(N)])



all[!is.na(all$time_end), ]
res <- .ais_full_df(file_path); tibble::as_tibble(res)
str(res)
tibble::as_tibble(res)
tibble::as_tibble(.nmea_df(file_path, -1))




res$msgs_5$name



res <- .ais_decode_file_list(file_path, verbose = T)
tibble::as_tibble(data.table::rbindlist(res, fill = TRUE, use.names = TRUE))
# tibble::as_tibble(dplyr::bind_rows(res))
# tibble::as_tibble(do.call(rbind.data.frame, res))
ais_rbind_list <- function(file_path) {
  data.table::rbindlist(.ais_decode_file_list(file_path, verbose = T),
                        fill = TRUE, use.names = TRUE)
}




bench_mark <- bench::mark(
  # `.ais_decode_file_list()` = .ais_decode_file_list(file_path, verbose = F),
  `.ais_full_df()` = res1 <-  .ais_full_df(file_path),
  `rbindlist()` = res2 <- data.table::rbindlist(.ais_decode_file_list(file_path,
verbose = F), fill = TRUE, use.names = TRUE)
  ,
  iterations = 1,
  filter_gc = FALSE,
  check = FALSE
  # times = 10
); bench_mark















res <- bench::mark(
  # test <- .ais_full_df(file_path),
  test <- rbindlist(ais_decode_file_list(file_path, verbose = FALSE),
            use.names = TRUE, fill = TRUE)
  ,
  iterations = 1L,
  filter_gc = FALSE
); res
tibble::as_tibble(test)

# res <- .nest_test2(file_path); res

res <- tibble::as_tibble(.nest_test2(file_path)); res

# test_lines <- readr::read_lines(file_path, n_max = 10)
# test_text <- readr::read_file(file_path)
# test_lines[1:10]
# mat <- stringr::str_split(test_lines[1:20], ",",simplify = TRUE)

# test <- tibble::as_tibble(.nmea_df(file_path, n_max = -1)); test
res <- bench::mark(
  .nmea_df(file_path, n_max = 0)
  , iterations = 3
); res

test <- tibble::as_tibble(.nest_test(file_path))

test


bench::mark(
  .nest_test(file_path)
)


.ais_unwrap_msg(test$msg[[1]])
dplyr::bind_rows(lapply(lapply(test$msg, .ais_unwrap_msg),tibble::as_tibble))

dt <- data.table::setDT(data.table::copy(test))
# test[, "msg_specific_values"]
# lapply(test$msg_specific_values, tibble::as_tibble)
# nchar(mat[,8])
# nchar(mat[,9])
test1 <- .nmea_df(file_path, n_max = -1)
tibble::as_tibble(test1)
tibble::as_tibble(test1[test1$message_id == 7, ])
tibble::as_tibble(test1[test1$message_id == 10, ])
# test2 <-
# bench::mark(
  test2 <- .ais_decode_file_filter(file_path = file_path, 1, verbose = T)
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
