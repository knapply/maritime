test_that("ais_decoder_*() don't segfault", {
  expect_error(
    lapply(ais_msgs, function(.x) {
      ais_decode_filter(example_nmea_file(),
        msg_type = .x,
        verbose = FALSE
      )
    }),
    NA
  )

  expect_error(
    ais_decode_list(example_nmea_file(), verbose = FALSE),
    NA
  )

  expect_error(
    ais_decode_df(example_nmea_file(), verbose = FALSE),
    NA
  )

})
