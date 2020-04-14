#include "ais.h"
#include "maritime/stream.hpp"

// [[Rcpp::export(.ais_decode_filter_file)]]
SEXP cpp_ais_decode_filter_file(const std::string& file_path,
                                const int msg_type,
                                const bool verbose) {
  if (msg_type < 1 || msg_type > 27) {
    Rcpp::stop("bad msg_type");
  }
  auto enum_msg_type = static_cast<MSG_TYPE>(msg_type);

  auto nmea_stream = NMEA_Stream::from_file(file_path);
  Progress progress(nmea_stream.count_msgs(enum_msg_type) * 2, verbose);

  return nmea_stream.build_df_impl(enum_msg_type, progress);
}

// [[Rcpp::export(.ais_decode_list_file)]]
SEXP cpp_ais_decode_list_file(const std::string& file_path,
                              const bool verbose) {
  auto nmea_stream = NMEA_Stream::from_file(file_path);
  Progress progress(nmea_stream.n_total_messages() * 2, verbose);

  return nmea_stream.build_df_list(progress);
}

//
//
//
//
//
//
//

/*** R
library(data.table)
file_path <- "inst/example-data/big-files/20200131.log"
file_path <- "inst/example-data/20181101.log"
# .ais_decode_list(file_path, TRUE)

bench_mark <- bench::mark(
  # big_df = res1 <- rbindlist(.ais_decode_list2(file_path, TRUE),
                             # fill = TRUE, use.names = TRUE),
  # df_list = res <- .ais_decode_list2(file_path, TRUE)
  res <- .ais_decode_list(file_path, TRUE)

  ,
  iterations = 1,
  check = FALSE,
  filter_gc = FALSE
); bench_mark


res <- .ais_decode_filter(file_path, 1, verbose = TRUE)
tibble::as_tibble(res)

tibble::as_tibble(data.table::rbindlist(res, use.names = TRUE, fill =
TRUE)[order(first_line_number)]) lapply(res, tibble::as_tibble) all <-
data.table::rbindlist(res, idcol = "msg_type", fill = TRUE, use.names = TRUE)
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
