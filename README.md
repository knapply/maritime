`{maritime}` ⚓ 🚢 ⛵ 🛥️
================

  - [Introduction](#introduction)
  - [Installation](#installation)
  - [Usage](#usage)
  - [Performance](#performance)
  - [Credits](#credits)

<!-- README.Rmd generates README.md. -->

<!-- badges: start -->

[![R build
status](https://github.com/knapply/maritime/workflows/R-CMD-check/badge.svg)](https://github.com/knapply/maritime/actions?workflow=R-CMD-check)
[![AppVeyor build
status](https://ci.appveyor.com/api/projects/status/github/knapply/maritime?branch=master&svg=true)](https://ci.appveyor.com/project/knapply/maritime)
[![Travis-CI Build
Status](https://travis-ci.org/knapply/maritime.svg?branch=master)](https://travis-ci.org/knapply/maritime)
[![Codecov test
coverage](https://codecov.io/gh/knapply/maritime/branch/master/graph/badge.svg)](https://codecov.io/gh/knapply/maritime?branch=master)
[![Lifecycle](https://img.shields.io/badge/lifecycle-experimental-orange.svg)](https://www.tidyverse.org/lifecycle/#experimental)
[![GitHub last
commit](https://img.shields.io/github/last-commit/knapply/maritime.svg)](https://github.com/knapply/maritime/commits/master)
[![License: GPL
v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
[![Depends](https://img.shields.io/badge/Depends-GNU_R%3E=3.6-blue.svg)](https://www.r-project.org/)
[![GitHub code size in
bytes](https://img.shields.io/github/languages/code-size/knapply/maritime.svg)](https://github.com/knapply/maritime)
[![Gitter](https://badges.gitter.im/maritime/community.svg)](https://gitter.im/maritime/community?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge)
[![HitCount](http://hits.dwyl.io/knapply/maritime.svg)](http://hits.dwyl.io/knapply/maritime)
<!-- [![CRAN status](https://www.r-pkg.org/badges/version/maritime)](https://cran.r-project.org/package=maritime) -->
<!-- badges: end -->

# Introduction

# Installation

You’ll need a C++ compiler. If you’re using Windows, that means
[Rtools](https://cran.r-project.org/bin/windows/Rtools/).

``` r
if (!requireNamespace("remotes", quietly = TRUE)) install.packages("remotes")
remotes::install_github("knapply/maritime")
```

# Usage

``` r
library(maritime)
```

# Performance

``` r
nmea_file <- "inst/example-data/big-files/20181210.log"
paste(round(file.size(nmea_file) / 1e9, 2L), "GB")
```

    #> [1] "1.24 GB"

``` r
bench_mark <- bench::mark(
  file = decoded <- ais_decode_nmea(nmea_file, as_tibble = FALSE, as_sf = FALSE),
  iterations = 1,
  check = FALSE
)

bench_mark
```

    #> # A tibble: 1 x 6
    #>   expression      min   median `itr/sec` mem_alloc `gc/sec`
    #>   <bch:expr> <bch:tm> <bch:tm>     <dbl> <bch:byt>    <dbl>
    #> 1 file          6.86s    6.86s     0.146    1.29GB    0.292

``` r
tibble::as_tibble(decoded)
```

    #> # A tibble: 5,139,027 x 26
    #>    message_id repeat_indicator   mmsi rot_over_range   rot    sog position_accura… lng_deg lat_deg   cog true_heading timestamp special_manoeuv… spare
    #>         <int>            <int>  <int> <lgl>          <dbl>  <dbl>            <int>   <dbl>   <dbl> <dbl>        <int>     <int>            <int> <int>
    #>  1          1                0 3.10e8 FALSE             0  11.2                  1  -82.9     27.6 266.           267        56                0     2
    #>  2          1                0 2.58e8 FALSE             0   0.100                0   30.0     69.7 134            333        58                0     0
    #>  3          3                0 2.66e8 FALSE             0   0                    1   17.9     59.3 360             69        59                0     0
    #>  4          3                0 2.66e8 FALSE             0   0                    1   15.6     56.2  68.7            0        59                0     0
    #>  5          1                0 3.67e8 FALSE             0   2.90                 1  -88.9     30.2 307.           317        59                0     0
    #>  6          1                0 3.05e8 FALSE             0  13.7                  1  -79.4     26.6  95.2          104        59                0     0
    #>  7          1                0 2.65e8 FALSE             0   0                    0   11.0     58.9  37.9           35        59                0     0
    #>  8          1                0 2.57e8 TRUE           -731.  0                    1    7.60    63.1 360            511        58                0     0
    #>  9          3                0 2.73e8 FALSE             0   0                    0   19.0     69.7  63.1          230        57                0     0
    #> 10          1                0 3.67e8 TRUE           -731.  0                    0  -89.6     40.7 222.           511        58                0     0
    #> # … with 5,139,017 more rows, and 12 more variables: raim <lgl>, sync_state <int>, slot_timeout <int>, received_stations <int>, slot_number <int>,
    #> #   utc_hour <int>, utc_min <int>, utc_spare <int>, slot_offset <int>, slot_increment <int>, slots_to_allocate <int>, keep_flag <lgl>

# Credits

  - AIS decoding routines are built on top of [Kurt
    Schwehr](https://twitter.com/kurtschwehr)’s
    [**libais**](https://github.com/schwehr/libais).
