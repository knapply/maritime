context("cpp")

test_that("ais_version() works", {
  # .ais_full_df(example_nmea_file())

  expect_error(
    .ais_decode_file_list(example_nmea_file(), verbose = FALSE),
    NA
  )
})