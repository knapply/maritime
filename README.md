`{maritime}` ⚓ 🚢 ⛵ 🛥️
================

  - [Introduction](#introduction)
  - [Installation](#installation)
  - [Status](#status)
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

`{maritime}` is a toolkit for maritime data.

Initial focus is building *performant* and correct AIS decoding routines
for R by building on [Kurt Schwehr](https://twitter.com/kurtschwehr)’s
[**libais**](https://github.com/schwehr/libais).

# Installation

You’ll need a C++ compiler. If you’re using Windows, that means
[Rtools](https://cran.r-project.org/bin/windows/Rtools/).

``` r
if (!requireNamespace("remotes", quietly = TRUE)) install.packages("remotes")
remotes::install_github("knapply/maritime")
```

# Status

What’s implemented so far?

  - *Fast* preprocessing and line normalization.
      - Multi-line messages are reconciled and merged *automatically*.
  - Message Types:
      - `ais_msgs$msg_1_2_3`
      - `ais_msgs$msg_4_11`
      - `ais_msgs$msg_5`
      - `ais_msgs$msg_7_13`
      - `ais_msgs$msg_9`
      - `ais_msgs$msg_10`

# Usage

``` r
library(maritime)
```

``` r
nmea_file <- "inst/example-data/big-files/20181210.log"
paste(round(file.size(nmea_file) / 1e9, 2L), "GB")
```

    #> [1] "1.24 GB"

``` r
readLines(nmea_file, n = 10) # quick peak at the data
```

    #>  [1] ",1544400000"                                                                            
    #>  [2] ",1544400000"                                                                            
    #>  [3] "!SAVDM,1,1,7,A,14WCf2001hr4dE<?joPbHpGh88RM,0*4C,1544400000,1544400000"                 
    #>  [4] "!AIVDM,2,1,6,B,55Q>TD02AfVC<HD7:20Lht84j055D58UE>222216B0JC871l0>4381i3,0*75,1544400000"
    #>  [5] "!AIVDM,2,2,6,B,`88888888888880,2*79,1544400000,1544400000"                              
    #>  [6] "!AIVDM,1,1,,A,B3gsP70007Topd9B8lmVKwu5kP06,0*59,1544400000,1544400000"                  
    #>  [7] "!SAVDM,1,1,3,A,H52ONqlUCBD6llD00000000h6220,0*50,1544400000,1544400000"                 
    #>  [8] "!BSVDM,1,1,,A,13n;to000129MwVWqNmm?:Kl0@RJ,0*37,1544400000,1544400000"                  
    #>  [9] "!ABVDM,1,1,1,B,33u=NqU000QAtkdQsKdN42;n0De:,0*5D,1544400000,1544400000"                 
    #> [10] "!AIVDM,1,1,,B,H3gi=84N0000000B5elii00P7110,0*36,1544400000,1544400000"

``` r
ais_decode_filter(msgs = nmea_file, msg_type = ais_msgs$msg_1_2_3)
```

    #> # A tibble: 5,117,490 x 29
    #>    time_start          time_end            message_id repeat_indicator   mmsi nav_status rot_over_range   rot    sog position_accura… lng_deg lat_deg
    #>    <dttm>              <dttm>                   <int>            <int>  <int>      <int> <lgl>          <dbl>  <dbl>            <int>   <dbl>   <dbl>
    #>  1 2018-12-10 00:00:00 2018-12-10 00:00:00          1                0 3.10e8          0 FALSE             0  11.2                  1  -82.9     27.6
    #>  2 2018-12-10 00:00:00 2018-12-10 00:00:00          1                0 2.58e8          0 FALSE             0   0.100                0   30.0     69.7
    #>  3 2018-12-10 00:00:00 2018-12-10 00:00:00          3                0 2.66e8          5 FALSE             0   0                    1   17.9     59.3
    #>  4 2018-12-10 00:00:00 2018-12-10 00:00:00          3                0 2.66e8          5 FALSE             0   0                    1   15.6     56.2
    #>  5 2018-12-10 00:00:00 2018-12-10 00:00:00          1                0 3.67e8          3 FALSE             0   2.90                 1  -88.9     30.2
    #>  6 2018-12-10 00:00:00 2018-12-10 00:00:00          1                0 3.05e8          0 FALSE             0  13.7                  1  -79.4     26.6
    #>  7 2018-12-10 00:00:00 2018-12-10 00:00:00          1                0 2.65e8          0 FALSE             0   0                    0   11.0     58.9
    #>  8 2018-12-10 00:00:00 2018-12-10 00:00:00          1                0 2.57e8          0 TRUE           -731.  0                    1    7.60    63.1
    #>  9 2018-12-10 00:00:00 2018-12-10 00:00:00          3                0 2.73e8          5 FALSE             0   0                    0   19.0     69.7
    #> 10 2018-12-10 00:00:00 2018-12-10 00:00:00          1                0 3.67e8         15 TRUE           -731.  0                    0  -89.6     40.7
    #> # … with 5,117,480 more rows, and 17 more variables: cog <dbl>, true_heading <int>, timestamp <int>, special_manoeuvre <int>, spare <int>,
    #> #   raim <lgl>, sync_state <int>, slot_timeout <int>, received_stations <int>, slot_number <int>, utc_hour <int>, utc_min <int>, utc_spare <int>,
    #> #   slot_offset <int>, slot_increment <int>, slots_to_allocate <int>, keep_flag <lgl>

``` r
ais_decode_filter(msgs = nmea_file, msg_type = ais_msgs$msg_5)
```

    #> # A tibble: 3,723,201 x 23
    #>    time_start          time_end            message_id repeat_indicator   mmsi ais_version imo_num callsign name  type_and_cargo dim_a dim_b dim_c
    #>    <dttm>              <dttm>                   <int>            <int>  <int>       <int>   <int> <chr>    <chr>          <int> <int> <int> <int>
    #>  1 2018-12-10 00:00:00 2018-12-10 00:00:00          5                0 3.70e8           0 9550436 "3FEA2 … "GLO…             70   144    26    19
    #>  2 2018-12-10 00:00:00 2018-12-10 00:00:00          5                0 2.66e8           1 8010673 "SJOY  … "BAL…             90    38    19     6
    #>  3 2018-12-10 00:00:00 2018-12-10 00:00:00          5                0 2.45e8           2 7711074 "PBCZ@@… "DEO…             33    57    15     7
    #>  4 2018-12-10 00:00:00 2018-12-10 00:00:00          5                0 2.57e8           0 5255777 "LATU3@… "NOR…             69    19    61    12
    #>  5 2018-12-10 00:00:00 2018-12-10 00:00:00          5                0 2.66e8           1       0 "SCFR@@… "VAD…             60     8    29     4
    #>  6 2018-12-10 00:00:00 2018-12-10 00:00:00          5                0 3.67e8           0     220 "WDF650… "COU…             52     7     9     4
    #>  7 2018-12-10 00:00:00 2018-12-10 00:00:00          5                0 2.58e8           0 9417830 "LFFE  … "SKA…             52    20    67    10
    #>  8 2018-12-10 00:00:00 2018-12-10 00:00:00          5                0 3.67e8           0 8635863 "WDC280… "RAY…             31     8    12     2
    #>  9 2018-12-10 00:00:00 2018-12-10 00:00:00          5                0 3.67e8           0       0 "WCZ456… "DOU…              0     5    20     5
    #> 10 2018-12-10 00:00:00 2018-12-10 00:00:00          5                0 2.15e8           0 9431006 "9HA262… "WIL…             70   105    18     3
    #> # … with 3,723,191 more rows, and 10 more variables: dim_d <int>, fix_type <int>, eta_month <int>, eta_day <int>, eta_hour <int>, eta_minute <int>,
    #> #   draught <dbl>, destination <chr>, dte <int>, spare <int>

# Performance

``` r
bench_mark <- bench::mark(
  file = decoded <- ais_decode_list(nmea_file, as_tibble = FALSE, verbose = FALSE),
  iterations = 1,
  check = FALSE
)

bench_mark
```

    #> # A tibble: 1 x 6
    #>   expression      min   median `itr/sec` mem_alloc `gc/sec`
    #>   <bch:expr> <bch:tm> <bch:tm>     <dbl> <bch:byt>    <dbl>
    #> 1 file          25.2s    25.2s    0.0396    3.03GB    0.278

``` r
lapply(decoded, tibble::as_tibble)
```

    #> $msgs_1_2_3
    #> # A tibble: 5,117,490 x 29
    #>    time_start          time_end            message_id repeat_indicator   mmsi nav_status rot_over_range   rot    sog position_accura… lng_deg lat_deg
    #>    <dttm>              <dttm>                   <int>            <int>  <int>      <int> <lgl>          <dbl>  <dbl>            <int>   <dbl>   <dbl>
    #>  1 2018-12-10 00:00:00 2018-12-10 00:00:00          1                0 3.10e8          0 FALSE             0  11.2                  1  -82.9     27.6
    #>  2 2018-12-10 00:00:00 2018-12-10 00:00:00          1                0 2.58e8          0 FALSE             0   0.100                0   30.0     69.7
    #>  3 2018-12-10 00:00:00 2018-12-10 00:00:00          3                0 2.66e8          5 FALSE             0   0                    1   17.9     59.3
    #>  4 2018-12-10 00:00:00 2018-12-10 00:00:00          3                0 2.66e8          5 FALSE             0   0                    1   15.6     56.2
    #>  5 2018-12-10 00:00:00 2018-12-10 00:00:00          1                0 3.67e8          3 FALSE             0   2.90                 1  -88.9     30.2
    #>  6 2018-12-10 00:00:00 2018-12-10 00:00:00          1                0 3.05e8          0 FALSE             0  13.7                  1  -79.4     26.6
    #>  7 2018-12-10 00:00:00 2018-12-10 00:00:00          1                0 2.65e8          0 FALSE             0   0                    0   11.0     58.9
    #>  8 2018-12-10 00:00:00 2018-12-10 00:00:00          1                0 2.57e8          0 TRUE           -731.  0                    1    7.60    63.1
    #>  9 2018-12-10 00:00:00 2018-12-10 00:00:00          3                0 2.73e8          5 FALSE             0   0                    0   19.0     69.7
    #> 10 2018-12-10 00:00:00 2018-12-10 00:00:00          1                0 3.67e8         15 TRUE           -731.  0                    0  -89.6     40.7
    #> # … with 5,117,480 more rows, and 17 more variables: cog <dbl>, true_heading <int>, timestamp <int>, special_manoeuvre <int>, spare <int>,
    #> #   raim <lgl>, sync_state <int>, slot_timeout <int>, received_stations <int>, slot_number <int>, utc_hour <int>, utc_min <int>, utc_spare <int>,
    #> #   slot_offset <int>, slot_increment <int>, slots_to_allocate <int>, keep_flag <lgl>
    #> 
    #> $msgs_4_11
    #> # A tibble: 160,877 x 26
    #>    time_start          time_end            message_id repeat_indicator   mmsi  year month   day  hour minute second position_accura… lng_deg lat_deg
    #>    <dttm>              <dttm>                   <int>            <int>  <int> <int> <int> <int> <int>  <int>  <int>            <int>   <dbl>   <dbl>
    #>  1 2018-12-09 23:59:59 2018-12-10 00:00:00          4                3 2.01e6  2018    12     9     0      0      0                1    19.4    41.3
    #>  2 2018-12-10 00:00:01 2018-12-10 00:00:00          4                0 2.66e6  2018    12     9    23     59     59                0    22.1    65.6
    #>  3 2018-12-10 00:00:01 2018-12-10 00:00:02          4                3 3.16e6  2018    12    10     0      0      0                1   -79.2    42.9
    #>  4 2018-12-10 00:00:01 2018-12-10 00:00:02          4                3 3.16e6  2018    12    10     0      0      0                1   -78.1    44.1
    #>  5 2018-12-10 00:00:01 2018-12-10 00:00:02          4                0 3.67e6  2018    12    10     0      0      0                1   -93.8    29.7
    #>  6 2018-12-10 00:00:02 2018-12-10 00:00:02          4                0 3.67e6  2018    12    10     0      0      0                1   -89.8    29.6
    #>  7 2018-12-10 00:00:03 2018-12-10 00:00:02          4                0 2.47e6  2018    12    10     0      0      2                0    10.2    42.8
    #>  8 2018-12-10 00:00:03 2018-12-10 00:00:02          4                1 2.62e6  2018    12     9     0      0      0                0    18.2    55.5
    #>  9 2018-12-10 00:00:03 2018-12-10 00:00:02          4                0 3.67e6  2018    12    10     0      0      0                1   -95.3    29.7
    #> 10 2018-12-10 00:00:03 2018-12-10 00:00:02          4                0 3.67e6  2018    12    10     0      0      1                1   -80.5    25.5
    #> # … with 160,867 more rows, and 12 more variables: fix_type <int>, transmission_ctl <int>, spare <int>, raim <lgl>, sync_state <int>,
    #> #   slot_timeout <int>, received_stations <int>, slot_number <int>, utc_hour <int>, utc_min <int>, utc_spare <int>, slot_offset <int>
    #> 
    #> $msgs_5
    #> # A tibble: 3,723,201 x 23
    #>    time_start          time_end            message_id repeat_indicator   mmsi ais_version imo_num callsign name  type_and_cargo dim_a dim_b dim_c
    #>    <dttm>              <dttm>                   <int>            <int>  <int>       <int>   <int> <chr>    <chr>          <int> <int> <int> <int>
    #>  1 2018-12-10 00:00:00 2018-12-10 00:00:00          5                0 3.70e8           0 9550436 "3FEA2 … "GLO…             70   144    26    19
    #>  2 2018-12-10 00:00:00 2018-12-10 00:00:00          5                0 2.66e8           1 8010673 "SJOY  … "BAL…             90    38    19     6
    #>  3 2018-12-10 00:00:00 2018-12-10 00:00:00          5                0 2.45e8           2 7711074 "PBCZ@@… "DEO…             33    57    15     7
    #>  4 2018-12-10 00:00:00 2018-12-10 00:00:00          5                0 2.57e8           0 5255777 "LATU3@… "NOR…             69    19    61    12
    #>  5 2018-12-10 00:00:00 2018-12-10 00:00:00          5                0 2.66e8           1       0 "SCFR@@… "VAD…             60     8    29     4
    #>  6 2018-12-10 00:00:00 2018-12-10 00:00:00          5                0 3.67e8           0     220 "WDF650… "COU…             52     7     9     4
    #>  7 2018-12-10 00:00:00 2018-12-10 00:00:00          5                0 2.58e8           0 9417830 "LFFE  … "SKA…             52    20    67    10
    #>  8 2018-12-10 00:00:00 2018-12-10 00:00:00          5                0 3.67e8           0 8635863 "WDC280… "RAY…             31     8    12     2
    #>  9 2018-12-10 00:00:00 2018-12-10 00:00:00          5                0 3.67e8           0       0 "WCZ456… "DOU…              0     5    20     5
    #> 10 2018-12-10 00:00:00 2018-12-10 00:00:00          5                0 2.15e8           0 9431006 "9HA262… "WIL…             70   105    18     3
    #> # … with 3,723,191 more rows, and 10 more variables: dim_d <int>, fix_type <int>, eta_month <int>, eta_day <int>, eta_hour <int>, eta_minute <int>,
    #> #   draught <dbl>, destination <chr>, dte <int>, spare <int>
    #> 
    #> $msgs_7_13
    #> # A tibble: 0 x 0
    #> 
    #> $msgs_9
    #> # A tibble: 701 x 29
    #>    time_start          time_end            message_id repeat_indicator   mmsi   alt   sog position_accura… lng_deg lat_deg   cog timestamp alt_sensor
    #>    <dttm>              <dttm>                   <int>            <int>  <int> <int> <int>            <int>   <dbl>   <dbl> <int>     <int>      <int>
    #>  1 2018-12-10 00:06:20 2018-12-10 00:06:58          9                0 1.11e8   111     0                1    5.23    60.3   360        18          0
    #>  2 2018-12-10 00:15:56 2018-12-10 00:16:06          9                0 1.11e8    59     0                0    5.23    60.3   360        54          0
    #>  3 2018-12-10 00:42:12 2018-12-10 00:42:14          9                0 1.11e8  1407   172                0  -13.8     29.6   228        13          0
    #>  4 2018-12-10 01:19:32 2018-12-10 01:19:35          9                0 1.11e8   802   200                0  -15.0     28.2   214        33          0
    #>  5 2018-12-10 01:22:19 2018-12-10 01:22:18          9                2 9.07e8  3149   193                1  220.      28.4   131         0          0
    #>  6 2018-12-10 01:24:53 2018-12-10 01:24:59          9                0 1.11e8   311   183                0  -15.2     28.0   239        54          0
    #>  7 2018-12-10 01:26:46 2018-12-10 01:26:59          9                0 1.11e8   777   142                1  128.      34.9     0        43          0
    #>  8 2018-12-10 01:32:15 2018-12-10 01:32:16          9                0 1.11e8  2303   145                1  128.      35.1   309        12          0
    #>  9 2018-12-10 01:37:24 2018-12-10 01:37:22          9                0 1.11e8  2376   166                1  127.      35.1   208        22          0
    #> 10 2018-12-10 01:42:25 2018-12-10 01:42:24          9                0 1.11e8  2374   157                1  127.      34.9   240        22          0
    #> # … with 691 more rows, and 16 more variables: spare <int>, dte <int>, spare2 <int>, assigned_mode <int>, raim <lgl>, sync_state <int>,
    #> #   slot_timeout <int>, received_stations <int>, slot_number <int>, utc_hour <int>, utc_min <int>, utc_spare <int>, slot_offset <int>,
    #> #   slot_increment <int>, slots_to_allocate <int>, keep_flag <lgl>
    #> 
    #> $msgs_10
    #> # A tibble: 0 x 0

# Credits

  - AIS decoding routines are built on top of [Kurt
    Schwehr](https://twitter.com/kurtschwehr)’s
    [**libais**](https://github.com/schwehr/libais).
