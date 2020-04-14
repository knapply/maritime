`{maritime}` ⚓ 🚢 ⛵ 🛥️
================

  - [Introduction](#introduction)
  - [Installation](#installation)
  - [Usage](#usage)
  - [AIS Sentence (AIVDM/AIVDO)
    Decoding](#ais-sentence-aivdmaivdo-decoding)
      - [Status](#status)
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

Tools and routines for `{maritime}` data.

  - [ ] High-performance AIS decoding routines.
      - built on [Kurt Schwehr](https://twitter.com/kurtschwehr)’s
        [**libais**](https://github.com/schwehr/libais)
  - [ ] Seavision API wrapper
  - [ ] ?

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

# AIS Sentence (AIVDM/AIVDO) Decoding

## Status

  - [x] Automatic sentence validation and line normalization
  - Message Types:
      - [x] `ais_msgs$msg_1_2_3`
      - [x] `ais_msgs$msg_4_11`
      - [x] `ais_msgs$msg_5`
      - [ ] `ais_msgs$msg_6`
      - [x] `ais_msgs$msg_7_13`
      - [ ] `ais_msgs$msg_8`
      - [x] `ais_msgs$msg_9`
      - [x] `ais_msgs$msg_10`
      - [x] `ais_msgs$msg_11`
      - [x] `ais_msgs$msg_12`
      - [x] `ais_msgs$msg_14`
      - [x] `ais_msgs$msg_15`
      - [x] `ais_msgs$msg_16`
      - [x] `ais_msgs$msg_17`
      - [x] `ais_msgs$msg_18`
      - [x] `ais_msgs$msg_19`
      - [x] `ais_msgs$msg_20`
      - [x] `ais_msgs$msg_21`
      - [x] `ais_msgs$msg_22`
      - [x] `ais_msgs$msg_23`
      - [x] `ais_msgs$msg_24`
      - [x] `ais_msgs$msg_25`
      - [x] `ais_msgs$msg_26`
      - [x] `ais_msgs$msg_27`

<!-- end list -->

``` r
nmea_file <- "inst/example-data/big-files/20200131.log"
paste(round(file.size(nmea_file) / 1e9, 2L), "GB")
```

    #> [1] "1.38 GB"

``` r
readLines(nmea_file, n = 20) # real world data, in all its terrible glory
```

    #>  [1] ",1580428800"                                                                                
    #>  [2] ",1580428800"                                                                                
    #>  [3] "!AIVDM,1,1,,B,33P9gc5000OiLfLP2CuP3TUU0P00,0*0E,1580428800,1580428800"                      
    #>  [4] "!AIVDM,1,1,,A,33P>Erm000OTjJtOtb`jMlen1lg:,0*14,1580428800,1580428800"                      
    #>  [5] "!AIVDM,2,1,5,A,53FDrl02<u;pD4th000p5E@TiE<000000000001J38i6:7?40;j5C300,0*6F,1580428800"    
    #>  [6] "!AIVDM,2,2,5,A,000000000000000,2*21,1580428800,1580428800"                                  
    #>  [7] "!AIVDM,1,1,,B,33n>C@1002OnlS`PfbRM4WOnP000,0*62,1580428800,1580428800"                      
    #>  [8] "!AIVDM,2,1,3,A,55Thhp82DVT;<Hi?F20p5HTu>1=0PE8622222216H@R;I4K?>SQT`12j,0*18,1580428800"    
    #>  [9] "!AIVDM,2,2,3,A,p88888888888880,2*6F,1580428800,1580428800"                                  
    #> [10] "!AIVDM,1,1,,B,13@2I6001RPCas8MdPqD1k?n0DB7,0*36,1580428800,1580428800"                      
    #> [11] "!AIVDM,1,1,,A,13gTve0P00ve;htUUf7>4?v02L0U,0*69,1580428801,1580428800"                      
    #> [12] "!AIVDM,1,1,,A,B3h;a2P00?U7kkaK7JVNKwP5oP06,0*75,1580428801,1580428800"                      
    #> [13] "!AIVDM,1,1,,A,H3h;0kQ<DTME:0TT00000000000,2*18,1580428801,1580428800"                       
    #> [14] "!AIVDM,1,1,,A,1Cgda=g001Nc<MhUguL@`@L00400,0*7A,1580428801,1580428800"                      
    #> [15] "!AIVDM,2,1,9,B,53gkbKT00001@HHt000d4H58V20000000000000R18923t00d0P0000@,0*4F,1580428801"    
    #> [16] "!AIVDM,2,2,9,B,00P0000p0000000,2*0E,1580428801,1580428800"                                  
    #> [17] "!BSVDM,1,1,,B,B3m?0t000HMaR>::Mufa7wuUoP06,0*05,1580428801,1580428800"                      
    #> [18] "!BSVDM,2,1,5,A,53m`ni026Hl8h4l:220dDU0pE>2222222222220N0PA254B00<fNM<ev<v88,0*4B,1580428801"
    #> [19] "!BSVDM,2,2,5,A,88888888880,2*38,1580428801,1580428800"                                      
    #> [20] "!BSVDM,2,1,3,B,53o=mb02?7A8aLhR221<eDh858Dr22222222220N3H;4440Ht?1RDj2CQp0j,0*0A,1580428801"

``` r
ais_decode_filter(msgs = nmea_file, msg_type = ais_msgs$msg_1_2_3)
```

    #> # A tibble: 5,542,768 x 29
    #>    time                first_line_numb… message_id repeat_indicator   mmsi nav_status rot_over_range    rot   sog position_accura… lng_deg lat_deg
    #>    <dttm>                         <int>      <int>            <int>  <int>      <int> <lgl>           <dbl> <dbl>            <int>   <dbl>   <dbl>
    #>  1 2020-01-31 00:00:00                3          3                0 2.35e8          5 FALSE             0   0                    0   -3.18    56.0
    #>  2 2020-01-31 00:00:00                4          3                0 2.35e8          5 FALSE             0   0                    0   -5.94    55.8
    #>  3 2020-01-31 00:00:00                7          3                0 2.58e8          1 FALSE             0   0.200                0   -2.01    57.2
    #>  4 2020-01-31 00:00:00               10          1                0 2.18e8          0 FALSE             0   9.80                 1    4.29    51.9
    #>  5 2020-01-31 00:00:01               11          1                0 2.51e8          0 TRUE           -731.  0                    1  -18.1     65.7
    #>  6 2020-01-31 00:00:01               14          1                1 2.51e8         15 FALSE             0   0.100                0  -18.5     66.0
    #>  7 2020-01-31 00:00:01               24          1                0 2.74e8          5 TRUE           -731.  0.100                0   18.9     69.6
    #>  8 2020-01-31 00:00:01               25          3                0 2.57e8          5 FALSE           -35.0 0.100                0   24.7     71.0
    #>  9 2020-01-31 00:00:01               27          1                0 2.57e8          0 TRUE           -731.  0                    0   12.6     66.0
    #> 10 2020-01-31 00:00:01               33          1                0 2.57e8          0 TRUE           -731.  0                    0    8.65    63.8
    #> # … with 5,542,758 more rows, and 17 more variables: cog <dbl>, true_heading <int>, timestamp <int>, special_manoeuvre <int>, spare <int>,
    #> #   raim <lgl>, sync_state <int>, slot_timeout <int>, received_stations <int>, slot_number <int>, utc_hour <int>, utc_min <int>, utc_spare <int>,
    #> #   slot_offset <int>, slot_increment <int>, slots_to_allocate <int>, keep_flag <lgl>

``` r
ais_decode_df(msgs = nmea_file)
```

    #> # A tibble: 14,817,325 x 71
    #>    time                first_line_numb… message_id repeat_indicator   mmsi nav_status rot_over_range   rot    sog position_accura… lng_deg lat_deg
    #>    <dttm>                         <int>      <int>            <int>  <int>      <int> <lgl>          <dbl>  <dbl>            <int>   <dbl>   <dbl>
    #>  1 2020-01-31 00:00:00                3          3                0 2.35e8          5 FALSE             0   0                    0   -3.18    56.0
    #>  2 2020-01-31 00:00:00                4          3                0 2.35e8          5 FALSE             0   0                    0   -5.94    55.8
    #>  3 2020-01-31 00:00:00                5          5                0 2.25e8         NA NA               NA  NA                   NA   NA       NA  
    #>  4 2020-01-31 00:00:00                7          3                0 2.58e8          1 FALSE             0   0.200                0   -2.01    57.2
    #>  5 2020-01-31 00:00:00                8          5                0 3.74e8         NA NA               NA  NA                   NA   NA       NA  
    #>  6 2020-01-31 00:00:00               10          1                0 2.18e8          0 FALSE             0   9.80                 1    4.29    51.9
    #>  7 2020-01-31 00:00:01               11          1                0 2.51e8          0 TRUE           -731.  0                    1  -18.1     65.7
    #>  8 2020-01-31 00:00:01               12         18                0 2.52e8         NA NA               NA   0                    1  -23.5     65.9
    #>  9 2020-01-31 00:00:01               13         24                0 2.52e8         NA NA               NA  NA                   NA   NA       NA  
    #> 10 2020-01-31 00:00:01               14          1                1 2.51e8         15 FALSE             0   0.100                0  -18.5     66.0
    #> # … with 14,817,315 more rows, and 59 more variables: cog <dbl>, true_heading <int>, timestamp <int>, special_manoeuvre <int>, spare <int>,
    #> #   raim <lgl>, sync_state <int>, slot_timeout <int>, received_stations <int>, slot_number <int>, utc_hour <int>, utc_min <int>, utc_spare <int>,
    #> #   slot_offset <int>, slot_increment <int>, slots_to_allocate <int>, keep_flag <int>, year <int>, month <int>, day <int>, hour <int>, minute <int>,
    #> #   second <int>, fix_type <int>, transmission_ctl <int>, ais_version <int>, imo_num <int>, callsign <chr>, name <chr>, type_and_cargo <int>,
    #> #   dim_a <int>, dim_b <int>, dim_c <int>, dim_d <int>, eta_month <int>, eta_day <int>, eta_hour <int>, eta_minute <int>, draught <dbl>,
    #> #   destination <chr>, dte <int>, alt <int>, alt_sensor <int>, spare2 <int>, assigned_mode <int>, seq_num <int>, dest_mmsi <int>,
    #> #   retransmitted <lgl>, text <chr>, unit_flag <int>, display_flag <int>, dsc_flag <int>, band_flag <int>, m22_flag <int>, mode_flag <int>,
    #> #   commstate_flag <int>, commstate_cs_fill <int>, spare3 <int>, vendor_id <chr>

## Performance

``` r
bench::mark(
  `ais_decode_list()` = decoded_list <- ais_decode_list(
    nmea_file, as_tibble = FALSE, as_sf = FALSE, verbose = FALSE
  )
)
```

    #> # A tibble: 1 x 6
    #>   expression             min   median `itr/sec` mem_alloc `gc/sec`
    #>   <bch:expr>        <bch:tm> <bch:tm>     <dbl> <bch:byt>    <dbl>
    #> 1 ais_decode_list()    17.7s    17.7s    0.0564    4.76GB   0.0564

``` r
lapply(decoded_list, tibble::as_tibble)
```

    #> $msgs_1_2_3
    #> # A tibble: 5,542,768 x 29
    #>    time                first_line_numb… message_id repeat_indicator   mmsi nav_status rot_over_range    rot   sog position_accura… lng_deg lat_deg
    #>    <dttm>                         <int>      <int>            <int>  <int>      <int> <lgl>           <dbl> <dbl>            <int>   <dbl>   <dbl>
    #>  1 2020-01-31 00:00:00                3          3                0 2.35e8          5 FALSE             0   0                    0   -3.18    56.0
    #>  2 2020-01-31 00:00:00                4          3                0 2.35e8          5 FALSE             0   0                    0   -5.94    55.8
    #>  3 2020-01-31 00:00:00                7          3                0 2.58e8          1 FALSE             0   0.200                0   -2.01    57.2
    #>  4 2020-01-31 00:00:00               10          1                0 2.18e8          0 FALSE             0   9.80                 1    4.29    51.9
    #>  5 2020-01-31 00:00:01               11          1                0 2.51e8          0 TRUE           -731.  0                    1  -18.1     65.7
    #>  6 2020-01-31 00:00:01               14          1                1 2.51e8         15 FALSE             0   0.100                0  -18.5     66.0
    #>  7 2020-01-31 00:00:01               24          1                0 2.74e8          5 TRUE           -731.  0.100                0   18.9     69.6
    #>  8 2020-01-31 00:00:01               25          3                0 2.57e8          5 FALSE           -35.0 0.100                0   24.7     71.0
    #>  9 2020-01-31 00:00:01               27          1                0 2.57e8          0 TRUE           -731.  0                    0   12.6     66.0
    #> 10 2020-01-31 00:00:01               33          1                0 2.57e8          0 TRUE           -731.  0                    0    8.65    63.8
    #> # … with 5,542,758 more rows, and 17 more variables: cog <dbl>, true_heading <int>, timestamp <int>, special_manoeuvre <int>, spare <int>,
    #> #   raim <lgl>, sync_state <int>, slot_timeout <int>, received_stations <int>, slot_number <int>, utc_hour <int>, utc_min <int>, utc_spare <int>,
    #> #   slot_offset <int>, slot_increment <int>, slots_to_allocate <int>, keep_flag <lgl>
    #> 
    #> $msgs_4_11
    #> # A tibble: 187,845 x 26
    #>    time                first_line_numb… message_id repeat_indicator   mmsi  year month   day  hour minute second position_accura… lng_deg lat_deg
    #>    <dttm>                         <int>      <int>            <int>  <int> <int> <int> <int> <int>  <int>  <int>            <int>   <dbl>   <dbl>
    #>  1 2020-01-31 00:00:01              130          4                0 2.73e6  2020     1    31     0      0      0                0    27.0    60.0
    #>  2 2020-01-31 00:00:01              134          4                1 2.66e6  2020     1    31     0      0      0                0    18.2    59.3
    #>  3 2020-01-31 00:00:01              136          4                1 2.77e6  2020     1    31     0      0      0                1    27.4    59.4
    #>  4 2020-01-31 00:00:01              137          4                1 2.73e6  2020     1    31     0      0      1                0    28.7    60.3
    #>  5 2020-01-31 00:00:01              181          4                0 3.16e6  2020     1    31     0      0      0                1   -81.7    44.1
    #>  6 2020-01-31 00:00:01              183          4                0 3.16e6  2020     1    31     0      0      0                1   -76.7    44.3
    #>  7 2020-01-31 00:00:01              188          4                0 3.67e6  2020     1    31     0      0      0                1   -89.8    29.6
    #>  8 2020-01-31 00:00:01              203          4                0 3.67e6  2020     1    31     0      0      0                1   -85.3    29.8
    #>  9 2020-01-31 00:00:02              317          4                0 3.67e6  2020     1    31     0      0      0                1  -124.     41.1
    #> 10 2020-01-31 00:00:03              520          4                0 3.67e6  2020     1    31     0      0      2                1  -122.     45.7
    #> # … with 187,835 more rows, and 12 more variables: fix_type <int>, transmission_ctl <int>, spare <int>, raim <lgl>, sync_state <int>,
    #> #   slot_timeout <int>, received_stations <int>, slot_number <int>, utc_hour <int>, utc_min <int>, utc_spare <int>, slot_offset <int>
    #> 
    #> $msgs_5
    #> # A tibble: 4,177,583 x 23
    #>    time                first_line_numb… message_id repeat_indicator   mmsi ais_version imo_num callsign name  type_and_cargo dim_a dim_b dim_c dim_d
    #>    <dttm>                         <int>      <int>            <int>  <int>       <int>   <int> <chr>    <chr>          <int> <int> <int> <int> <int>
    #>  1 2020-01-31 00:00:00                5          5                0 2.25e8           0 9237694 EAOL@@@  NAUT…             90    25    49     6    10
    #>  2 2020-01-31 00:00:00                8          5                0 3.74e8           2 9738818 3FLS5    NAVI…             70   194    34    11    25
    #>  3 2020-01-31 00:00:01               15          5                0 2.51e8           1       0 TFFO@@@  KAFA…             34     9     9     2     3
    #>  4 2020-01-31 00:00:01               18          5                0 2.58e8           0 8807234 LAMB     KEIP…             30     4    17     2     5
    #>  5 2020-01-31 00:00:01               20          5                0 2.59e8           0 9379090 JWLH     SKUL…             30    27    11     4     4
    #>  6 2020-01-31 00:00:01               22          5                0 2.58e8           0 9237981 LLKV     HIDR…             60    25    25     7     7
    #>  7 2020-01-31 00:00:01               29          5                0 2.57e8           0       0 LK5895   ISBJ…             30     4     7     2     2
    #>  8 2020-01-31 00:00:01               31          5                0 2.57e8           2       0 LM6281@  HILM…             30     2     8     1     3
    #>  9 2020-01-31 00:00:01               44          5                0 2.50e8           0 9327712 EITN     RONA              30     0     0     0     0
    #> 10 2020-01-31 00:00:02               47          5                0 3.12e8           1       0 V3OM6@@  JOAN…             99    35    45     7     5
    #> # … with 4,177,573 more rows, and 9 more variables: fix_type <int>, eta_month <int>, eta_day <int>, eta_hour <int>, eta_minute <int>, draught <dbl>,
    #> #   destination <chr>, dte <int>, spare <int>
    #> 
    #> $msgs_7_13
    #> # A tibble: 0 x 0
    #> 
    #> $msgs_9
    #> # A tibble: 1,412 x 29
    #>    time                first_line_numb… message_id repeat_indicator   mmsi   alt   sog position_accura… lng_deg lat_deg   cog timestamp alt_sensor
    #>    <dttm>                         <int>      <int>            <int>  <int> <int> <int>            <int>   <dbl>   <dbl> <int>     <int>      <int>
    #>  1 2020-01-31 00:09:12           121025          9                0 1.11e8    73     0                0   -15.4    28.2   330        44          0
    #>  2 2020-01-31 00:14:14           187566          9                0 1.11e8   237    78                0   -15.5    28.2   278        45          0
    #>  3 2020-01-31 00:19:17           254727          9                0 1.11e8   103    43                0   -15.4    28.2    11        45          0
    #>  4 2020-01-31 00:24:30           322875          9                0 1.11e8    70     2                0   -15.4    28.2   348        56          0
    #>  5 2020-01-31 00:34:43           457540          9                0 1.11e8    76     0                0   -15.4    28.2     0         4          0
    #>  6 2020-01-31 00:39:45           523440          9                0 1.11e8   326    81                0   -15.5    28.2    45         4          0
    #>  7 2020-01-31 00:44:56           591595          9                0 1.11e8   526   122                0   -15.4    28.1   182        15          0
    #>  8 2020-01-31 01:57:43          1548581          9                0 1.11e8   619   105                1   128.     35.0   170        39          0
    #>  9 2020-01-31 02:03:33          1625095          9                0 1.11e8   941   106                1   128.     34.8   167        29          0
    #> 10 2020-01-31 02:08:43          1692764          9                0 1.11e8  1498    99                1   128.     34.7   249        39          0
    #> # … with 1,402 more rows, and 16 more variables: spare <int>, dte <int>, spare2 <int>, assigned_mode <int>, raim <lgl>, sync_state <int>,
    #> #   slot_timeout <int>, received_stations <int>, slot_number <int>, utc_hour <int>, utc_min <int>, utc_spare <int>, slot_offset <int>,
    #> #   slot_increment <int>, slots_to_allocate <int>, keep_flag <lgl>
    #> 
    #> $msgs_10
    #> # A tibble: 0 x 0
    #> 
    #> $msgs_12
    #> # A tibble: 369 x 10
    #>    time                first_line_number message_id repeat_indicator    mmsi seq_num dest_mmsi retransmitted spare text                               
    #>    <dttm>                          <int>      <int>            <int>   <int>   <int>     <int> <lgl>         <int> <chr>                              
    #>  1 2020-01-31 00:11:08            146585         12                1  2.24e6       0 215375000 FALSE             0 ANCHORAGE AND DRIFTING ARE NOT ALL…
    #>  2 2020-01-31 00:11:10            147170         12                1  2.24e6       0 215375000 FALSE             0 ANCHORAGE AND DRIFTING ARE NOT ALL…
    #>  3 2020-01-31 00:18:25            242526         12                0  2.35e8       0 563083300 FALSE             0 SIR ANY UPDATE ABOUT UR ETB?       
    #>  4 2020-01-31 00:18:27            243124         12                0  2.35e8       0 563083300 FALSE             0 SIR ANY UPDATE ABOUT UR ETB?       
    #>  5 2020-01-31 00:31:11            411238         12                0  5.63e8       3 205602000 FALSE             0 DOOG EVENING,SIR , DISCH PORT CHIN…
    #>  6 2020-01-31 00:31:14            412141         12                0  5.63e8       3 205602000 FALSE             0 DOOG EVENING,SIR , DISCH PORT CHIN…
    #>  7 2020-01-31 00:36:02            474763         12                0  6.36e8       1 248659000 FALSE             0 AIS TEST PLS ACK GOOD WATCH MSC MI…
    #>  8 2020-01-31 00:36:03            475012         12                0  6.36e8       1 248659000 FALSE             0 AIS TEST PLS ACK GOOD WATCH MSC MI…
    #>  9 2020-01-31 00:36:04            475276         12                0  6.36e8       1 248659000 FALSE             0 AIS TEST PLS ACK GOOD WATCH MSC MI…
    #> 10 2020-01-31 00:36:32            480994         12                0  6.36e8       2 241008000 FALSE             0 AIS TEST PLS ACK GOOD WATCH MSC MI…
    #> # … with 359 more rows
    #> 
    #> $msgs_14
    #> # A tibble: 99 x 8
    #>    time                first_line_number message_id repeat_indicator      mmsi spare text                spare2
    #>    <dttm>                          <int>      <int>            <int>     <int> <int> <chr>                <int>
    #>  1 2020-01-31 00:15:43            206734         14                0 970226163     0 SART ACTIVE@@@@@         0
    #>  2 2020-01-31 01:05:13            858311         14                0 255805824     0 AIS TEST PLS ACK BQ      0
    #>  3 2020-01-31 01:05:14            858572         14                0 255805824     0 AIS TEST PLS ACK BQ      0
    #>  4 2020-01-31 01:59:44           1574937         14                0 970226163     0 SART ACTIVE@@@@@         0
    #>  5 2020-01-31 01:59:47           1575615         14                0 970226163     0 SART ACTIVE@@@@@         0
    #>  6 2020-01-31 02:03:44           1627493         14                0 970226163     0 SART ACTIVE@@@@@         0
    #>  7 2020-01-31 02:15:44           1784003         14                0 970226163     0 SART ACTIVE@@@@@         0
    #>  8 2020-01-31 02:33:18           2015329         14                0 636018898     0 PLEASE ACKN SEND         0
    #>  9 2020-01-31 02:33:19           2015540         14                0 636018898     0 PLEASE ACKN SEND         0
    #> 10 2020-01-31 02:43:42           2151333         14                0 970226163     0 SART ACTIVE@@@@@         0
    #> # … with 89 more rows
    #> 
    #> $msgs_15
    #> # A tibble: 0 x 0
    #> 
    #> $msgs_16
    #> # A tibble: 0 x 0
    #> 
    #> $msgs_17
    #> # A tibble: 0 x 0
    #> 
    #> $msgs_18
    #> # A tibble: 1,815,577 x 33
    #>    time                first_line_numb… message_id repeat_indicator   mmsi spare   sog position_accura…  lng_deg lat_deg   cog true_heading timestamp
    #>    <dttm>                         <int>      <int>            <int>  <int> <int> <dbl>            <int>    <dbl>   <dbl> <dbl>        <int>     <int>
    #>  1 2020-01-31 00:00:01               12         18                0 2.52e8     0 0                    1  -23.5      65.9 253.           511         0
    #>  2 2020-01-31 00:00:01               17         18                0 2.57e8     0 0.100                1   25.9      71.0 270.           511        59
    #>  3 2020-01-31 00:00:01               40         18                0 2.57e8     0 5.5                  0   16.2      69.3 318.           511         0
    #>  4 2020-01-31 00:00:02               54         18                0 2.61e8     0 0                    1   16.9      54.6 240.           511         1
    #>  5 2020-01-31 00:00:02               80         18                0 2.19e8     0 0                    1   10.1      55.6 360            511         1
    #>  6 2020-01-31 00:00:01              118         18                0 3.78e8     0 0                    1   14.5      35.9 241.           511        59
    #>  7 2020-01-31 00:00:01              119         18                0 2.24e8     0 0                    1   -0.315    39.5 101.           511        21
    #>  8 2020-01-31 00:00:01              140         18                0 2.45e8     0 0                    1   -6.28     36.5 360            511         0
    #>  9 2020-01-31 00:00:01              167         18                0 3.38e8     0 0.100                1 -118.       33.7 316.           511        59
    #> 10 2020-01-31 00:00:01              170         18                0 3.38e8     0 0                    0 -122.       38.1  26.2          511        59
    #> # … with 1,815,567 more rows, and 20 more variables: spare2 <int>, unit_flag <int>, display_flag <int>, dsc_flag <int>, band_flag <int>,
    #> #   m22_flag <int>, mode_flag <int>, raim <lgl>, commstate_flag <int>, slot_timeout <int>, slot_offset <int>, utc_hour <int>, utc_min <int>,
    #> #   utc_spare <int>, slot_number <int>, received_stations <int>, slot_increment <int>, slots_to_allocate <int>, keep_flag <int>,
    #> #   commstate_cs_fill <int>
    #> 
    #> $msgs_19
    #> # A tibble: 9,415 x 25
    #>    time                first_line_numb… message_id repeat_indicator   mmsi spare   sog position_accura… lng_deg lat_deg   cog true_heading timestamp
    #>    <dttm>                         <int>      <int>            <int>  <int> <int> <dbl>            <int>   <dbl>   <dbl> <dbl>        <int>     <int>
    #>  1 2020-01-31 00:00:14             2924         19                0 5.14e8     0 0.300                1  103.      10.9 360.           511        11
    #>  2 2020-01-31 00:00:14             2933         19                0 5.67e8     0 1.70                 1  102.      12.2   6              6        60
    #>  3 2020-01-31 00:00:22             4691         19                0 5.67e8     0 4.70                 1  102.      12.1  80.3          511        20
    #>  4 2020-01-31 00:00:24             5126         19                0 9.41e8     0 1                    1   14.7     69.1 350.           511        60
    #>  5 2020-01-31 00:00:27             5574         19                0 2.19e8     0 0                    0   10.7     54.8 171.           171         0
    #>  6 2020-01-31 00:01:01            13366         19                0 9.42e8     0 0.900                1   29.7     70.6 360            511        60
    #>  7 2020-01-31 00:01:04            14295         19                0 9.41e8     0 0.700                1   13.2     67.9 218.           511        60
    #>  8 2020-01-31 00:01:11            15810         19                0 2.58e8     0 0                    0    8.00    58.1 249.           248         0
    #>  9 2020-01-31 00:01:14            16467         19                0 9.41e8     0 0.400                1   19.7     70.4 266.           511        60
    #> 10 2020-01-31 00:01:16            17009         19                0 2.58e8     0 0                    1    5.23    59.4   0              0        60
    #> # … with 9,405 more rows, and 12 more variables: spare2 <int>, name <chr>, type_and_cargo <int>, dim_a <int>, dim_b <int>, dim_c <int>, dim_d <int>,
    #> #   fix_type <int>, raim <lgl>, dte <int>, assigned_mode <int>, spare3 <int>
    #> 
    #> $msgs_20
    #> # A tibble: 0 x 0
    #> 
    #> $msgs_21
    #> # A tibble: 0 x 0
    #> 
    #> $msgs_22
    #> # A tibble: 0 x 0
    #> 
    #> $msgs_23
    #> # A tibble: 0 x 0
    #> 
    #> $msgs_24
    #> # A tibble: 3,082,257 x 14
    #>    time                first_line_number message_id repeat_indicator    mmsi name      type_and_cargo vendor_id callsign dim_a dim_b dim_c dim_d spare
    #>    <dttm>                          <int>      <int>            <int>   <int> <chr>              <int> <chr>     <chr>    <int> <int> <int> <int> <int>
    #>  1 2020-01-31 00:00:01                13         24                0  2.52e8 SEIGUR I…             NA <NA>      <NA>        NA    NA    NA    NA    NA
    #>  2 2020-01-31 00:00:01                26         24                0  2.58e8 BANGSUND…             NA <NA>      <NA>        NA    NA    NA    NA    NA
    #>  3 2020-01-31 00:00:01                28         24                0  2.57e8 EMIL@@@@…             NA <NA>      <NA>        NA    NA    NA    NA    NA
    #>  4 2020-01-31 00:00:01                34         24                0  2.57e8 <NA>                  30 SRTEC&*   LF4079@      3     7     2     2     0
    #>  5 2020-01-31 00:00:01                38         24                0  2.58e8 <NA>                  52 @@@@@@@   LCXV@@@     10    15     3     3     0
    #>  6 2020-01-31 00:00:01                39         24                0  2.57e8 TRISTEIN…             NA <NA>      <NA>        NA    NA    NA    NA    NA
    #>  7 2020-01-31 00:00:01                41         24                0  2.57e8 <NA>                  30 SMTFW19   LD2557@      2     8     1     1     0
    #>  8 2020-01-31 00:00:01                42         24                0  2.57e8 <NA>                  30 @@@@@@@   LM9428@      3     7     1     2     0
    #>  9 2020-01-31 00:00:02                50         24                0  2.64e8 <NA>                  37 SMTD/MY   CRA7692      5     3     1     2     0
    #> 10 2020-01-31 00:00:02                56         24                0  2.61e8 <NA>                  37 SMTF`&L   SPS2540     17    10     4     2     0
    #> # … with 3,082,247 more rows
    #> 
    #> $msgs_25
    #> # A tibble: 0 x 0
    #> 
    #> $msgs_26
    #> # A tibble: 0 x 0
    #> 
    #> $msgs_27
    #> # A tibble: 0 x 0

# Credits

  - AIS decoding routines are built on top of [Kurt
    Schwehr](https://twitter.com/kurtschwehr)’s
    [**libais**](https://github.com/schwehr/libais).
