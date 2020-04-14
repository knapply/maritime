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

`{maritime}` is a toolkit for maritime data.

Initial focus is *performant* and correct AIS decoding routines for R by
building on [Kurt Schwehr](https://twitter.com/kurtschwehr)’s
[**libais**](https://github.com/schwehr/libais).

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
nmea_file <- "inst/example-data/big-files/20181210.log"
paste(round(file.size(nmea_file) / 1e9, 2L), "GB")
```

    #> [1] "1.24 GB"

``` r
readLines(nmea_file, n = 20) # real world data, in all its terrible glory
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
    #> [11] "!SAVDM,1,1,3,A,H5NWU?TU653hhhi00000001H;330,0*73,1544400000,1544400000"                     
    #> [12] "!ABVDM,1,1,0,B,33uB8eU000Q7F2NP8NcBch1n0DbJ,0*42,1544400000,1544400000"                     
    #> [13] "!SAVDM,1,1,9,B,B52`F8000=qpmg4cW8PWOwu5oP06,0*25,1544400000,1544400000"                     
    #> [14] "!SAVDM,1,1,4,B,B5NQqW000=ijOF60tMv3Cwu5oP06,0*75,1544400000,1544400000"                     
    #> [15] "!SAVDM,1,1,5,A,B5MHR>000=ijQ0V0tI2N?wu5oP06,0*6E,1544400000,1544400000"                     
    #> [16] "!ABVDM,2,1,2,A,53u=I?41r>s5<`uV22084i@T<62222222222221J4hC6674EN:3SlTRp42CQ,0*27,1544400000"
    #> [17] "!ABVDM,2,2,2,A,p8888888880,2*65,1544400000,1544400000"                                      
    #> [18] "!AIVDM,2,1,0,A,53b7IP81mbF908=`000@Dv0Lhu8T40000000000Q78?7773E06@hDQ2A,0*60,1544400000"    
    #> [19] "!AIVDM,2,2,0,A,Q`0000000000000,2*15,1544400000,1544400000"                                  
    #> [20] "!BSVDM,2,1,2,A,53mFpH01@<V4h5AG<00pu8A=@`E8pDp0000000152Hu<173>0<2lRDm2@CTm,0*16,1544400000"

``` r
ais_decode_filter(msgs = nmea_file, msg_type = ais_msgs$msg_1_2_3)
```

    #> # A tibble: 5,117,490 x 29
    #>    time                first_line_numb… message_id repeat_indicator   mmsi nav_status rot_over_range   rot    sog position_accura… lng_deg lat_deg
    #>    <dttm>                         <int>      <int>            <int>  <int>      <int> <lgl>          <dbl>  <dbl>            <int>   <dbl>   <dbl>
    #>  1 2018-12-10 00:00:00                3          1                0 3.10e8          0 FALSE             0  11.2                  1  -82.9     27.6
    #>  2 2018-12-10 00:00:00                8          1                0 2.58e8          0 FALSE             0   0.100                0   30.0     69.7
    #>  3 2018-12-10 00:00:00                9          3                0 2.66e8          5 FALSE             0   0                    1   17.9     59.3
    #>  4 2018-12-10 00:00:00               12          3                0 2.66e8          5 FALSE             0   0                    1   15.6     56.2
    #>  5 2018-12-10 00:00:00               25          1                0 3.67e8          3 FALSE             0   2.90                 1  -88.9     30.2
    #>  6 2018-12-10 00:00:00               28          1                0 3.05e8          0 FALSE             0  13.7                  1  -79.4     26.6
    #>  7 2018-12-10 00:00:00               30          1                0 2.65e8          0 FALSE             0   0                    0   11.0     58.9
    #>  8 2018-12-10 00:00:00               34          1                0 2.57e8          0 TRUE           -731.  0                    1    7.60    63.1
    #>  9 2018-12-10 00:00:00               35          3                0 2.73e8          5 FALSE             0   0                    0   19.0     69.7
    #> 10 2018-12-10 00:00:00               39          1                0 3.67e8         15 TRUE           -731.  0                    0  -89.6     40.7
    #> # … with 5,117,480 more rows, and 17 more variables: cog <dbl>, true_heading <int>, timestamp <int>, special_manoeuvre <int>, spare <int>,
    #> #   raim <lgl>, sync_state <int>, slot_timeout <int>, received_stations <int>, slot_number <int>, utc_hour <int>, utc_min <int>, utc_spare <int>,
    #> #   slot_offset <int>, slot_increment <int>, slots_to_allocate <int>, keep_flag <lgl>

``` r
ais_decode_list(msgs = nmea_file)
```

    #> $msgs_1_2_3
    #> # A tibble: 5,117,490 x 29
    #>    time                first_line_numb… message_id repeat_indicator   mmsi nav_status rot_over_range   rot    sog position_accura… lng_deg lat_deg
    #>    <dttm>                         <int>      <int>            <int>  <int>      <int> <lgl>          <dbl>  <dbl>            <int>   <dbl>   <dbl>
    #>  1 2018-12-10 00:00:00                3          1                0 3.10e8          0 FALSE             0  11.2                  1  -82.9     27.6
    #>  2 2018-12-10 00:00:00                8          1                0 2.58e8          0 FALSE             0   0.100                0   30.0     69.7
    #>  3 2018-12-10 00:00:00                9          3                0 2.66e8          5 FALSE             0   0                    1   17.9     59.3
    #>  4 2018-12-10 00:00:00               12          3                0 2.66e8          5 FALSE             0   0                    1   15.6     56.2
    #>  5 2018-12-10 00:00:00               25          1                0 3.67e8          3 FALSE             0   2.90                 1  -88.9     30.2
    #>  6 2018-12-10 00:00:00               28          1                0 3.05e8          0 FALSE             0  13.7                  1  -79.4     26.6
    #>  7 2018-12-10 00:00:00               30          1                0 2.65e8          0 FALSE             0   0                    0   11.0     58.9
    #>  8 2018-12-10 00:00:00               34          1                0 2.57e8          0 TRUE           -731.  0                    1    7.60    63.1
    #>  9 2018-12-10 00:00:00               35          3                0 2.73e8          5 FALSE             0   0                    0   19.0     69.7
    #> 10 2018-12-10 00:00:00               39          1                0 3.67e8         15 TRUE           -731.  0                    0  -89.6     40.7
    #> # … with 5,117,480 more rows, and 17 more variables: cog <dbl>, true_heading <int>, timestamp <int>, special_manoeuvre <int>, spare <int>,
    #> #   raim <lgl>, sync_state <int>, slot_timeout <int>, received_stations <int>, slot_number <int>, utc_hour <int>, utc_min <int>, utc_spare <int>,
    #> #   slot_offset <int>, slot_increment <int>, slots_to_allocate <int>, keep_flag <lgl>
    #> 
    #> $msgs_4_11
    #> # A tibble: 160,877 x 26
    #>    time                first_line_numb… message_id repeat_indicator   mmsi  year month   day  hour minute second position_accura… lng_deg lat_deg
    #>    <dttm>                         <int>      <int>            <int>  <int> <int> <int> <int> <int>  <int>  <int>            <int>   <dbl>   <dbl>
    #>  1 2018-12-09 23:59:59              130          4                3 2.01e6  2018    12     9     0      0      0                1    19.4    41.3
    #>  2 2018-12-10 00:00:01              142          4                0 2.66e6  2018    12     9    23     59     59                0    22.1    65.6
    #>  3 2018-12-10 00:00:01              276          4                3 3.16e6  2018    12    10     0      0      0                1   -79.2    42.9
    #>  4 2018-12-10 00:00:01              277          4                3 3.16e6  2018    12    10     0      0      0                1   -78.1    44.1
    #>  5 2018-12-10 00:00:01              320          4                0 3.67e6  2018    12    10     0      0      0                1   -93.8    29.7
    #>  6 2018-12-10 00:00:02              428          4                0 3.67e6  2018    12    10     0      0      0                1   -89.8    29.6
    #>  7 2018-12-10 00:00:03              493          4                0 2.47e6  2018    12    10     0      0      2                0    10.2    42.8
    #>  8 2018-12-10 00:00:03              515          4                1 2.62e6  2018    12     9     0      0      0                0    18.2    55.5
    #>  9 2018-12-10 00:00:03              628          4                0 3.67e6  2018    12    10     0      0      0                1   -95.3    29.7
    #> 10 2018-12-10 00:00:03              680          4                0 3.67e6  2018    12    10     0      0      1                1   -80.5    25.5
    #> # … with 160,867 more rows, and 12 more variables: fix_type <int>, transmission_ctl <int>, spare <int>, raim <lgl>, sync_state <int>,
    #> #   slot_timeout <int>, received_stations <int>, slot_number <int>, utc_hour <int>, utc_min <int>, utc_spare <int>, slot_offset <int>
    #> 
    #> $msgs_5
    #> # A tibble: 3,723,202 x 23
    #>    time                first_line_numb… message_id repeat_indicator   mmsi ais_version imo_num callsign name  type_and_cargo dim_a dim_b dim_c dim_d
    #>    <dttm>                         <int>      <int>            <int>  <int>       <int>   <int> <chr>    <chr>          <int> <int> <int> <int> <int>
    #>  1 NA                                 4          5                0 3.70e8           0 9550436 3FEA2    GLOB…             70   144    26    19     8
    #>  2 NA                                16          5                0 2.66e8           1 8010673 SJOY     BALT…             90    38    19     6     6
    #>  3 NA                                18          5                0 2.45e8           2 7711074 PBCZ@@@  DEO …             33    57    15     7     7
    #>  4 NA                                20          5                0 2.57e8           0 5255777 LATU3@@  NORD…             69    19    61    12     1
    #>  5 NA                                26          5                0 2.66e8           1       0 SCFR@@@  VADD…             60     8    29     4     4
    #>  6 NA                                32          5                0 3.67e8           0     220 WDF6506  COUN…             52     7     9     4     3
    #>  7 NA                                42          5                0 2.58e8           0 9417830 LFFE     SKAN…             52    20    67    10    11
    #>  8 NA                                48          5                0 3.67e8           0 8635863 WDC2804  RAY …             31     8    12     2     6
    #>  9 NA                                50          5                0 3.67e8           0       0 WCZ4561  DOUG…              0     5    20     5     2
    #> 10 NA                                58          5                0 2.15e8           0 9431006 9HA2628  WILS…             70   105    18     3    13
    #> # … with 3,723,192 more rows, and 9 more variables: fix_type <int>, eta_month <int>, eta_day <int>, eta_hour <int>, eta_minute <int>, draught <dbl>,
    #> #   destination <chr>, dte <int>, spare <int>
    #> 
    #> $msgs_7_13
    #> # A tibble: 0 x 0
    #> 
    #> $msgs_9
    #> # A tibble: 701 x 29
    #>    time                first_line_numb… message_id repeat_indicator   mmsi   alt   sog position_accura… lng_deg lat_deg   cog timestamp alt_sensor
    #>    <dttm>                         <int>      <int>            <int>  <int> <int> <int>            <int>   <dbl>   <dbl> <int>     <int>      <int>
    #>  1 2018-12-10 00:06:20            71926          9                0 1.11e8   111     0                1    5.23    60.3   360        18          0
    #>  2 2018-12-10 00:15:56           176939          9                0 1.11e8    59     0                0    5.23    60.3   360        54          0
    #>  3 2018-12-10 00:42:12           472425          9                0 1.11e8  1407   172                0  -13.8     29.6   228        13          0
    #>  4 2018-12-10 01:19:32           890251          9                0 1.11e8   802   200                0  -15.0     28.2   214        33          0
    #>  5 2018-12-10 01:22:19           921020          9                2 9.07e8  3149   193                1  220.      28.4   131         0          0
    #>  6 2018-12-10 01:24:53           948208          9                0 1.11e8   311   183                0  -15.2     28.0   239        54          0
    #>  7 2018-12-10 01:26:46           970814          9                0 1.11e8   777   142                1  128.      34.9     0        43          0
    #>  8 2018-12-10 01:32:15          1031057          9                0 1.11e8  2303   145                1  128.      35.1   309        12          0
    #>  9 2018-12-10 01:37:24          1088324          9                0 1.11e8  2376   166                1  127.      35.1   208        22          0
    #> 10 2018-12-10 01:42:25          1143960          9                0 1.11e8  2374   157                1  127.      34.9   240        22          0
    #> # … with 691 more rows, and 16 more variables: spare <int>, dte <int>, spare2 <int>, assigned_mode <int>, raim <lgl>, sync_state <int>,
    #> #   slot_timeout <int>, received_stations <int>, slot_number <int>, utc_hour <int>, utc_min <int>, utc_spare <int>, slot_offset <int>,
    #> #   slot_increment <int>, slots_to_allocate <int>, keep_flag <lgl>
    #> 
    #> $msgs_10
    #> # A tibble: 0 x 0
    #> 
    #> $msgs_12
    #> # A tibble: 149 x 10
    #>    time                first_line_number message_id repeat_indicator      mmsi seq_num dest_mmsi retransmitted spare text                            
    #>    <dttm>                          <int>      <int>            <int>     <int>   <int>     <int> <lgl>         <int> <chr>                           
    #>  1 2018-12-10 00:15:12            168933         12                0 366938510       0 374335000 FALSE             0 RECIEVED                        
    #>  2 2018-12-10 00:16:01            177887         12                0 366938510       1 374335000 FALSE             0 RECIEVED                        
    #>  3 2018-12-10 00:16:42            185395         12                0 366938510       2 374335000 FALSE             0 RECIEVED                        
    #>  4 2018-12-10 00:16:47            186473         12                0 366938510       2 374335000 TRUE              0 RECIEVED                        
    #>  5 2018-12-10 00:17:41            196782         12                0 366938510       3 374335000 FALSE             0 RECIEVED                        
    #>  6 2018-12-10 00:19:21            215311         12                0 366938510       1  37433500 FALSE             0 RECIEVED                        
    #>  7 2018-12-10 01:39:17           1110135         12                0 209011000       1 636017419 TRUE              0 TEST ACK OK                     
    #>  8 2018-12-10 01:49:03           1218664         12                0 366938510       2 374335000 FALSE             0 RECIEVED HAD PROBLEMN WITH REPLY
    #>  9 2018-12-10 01:58:01           1318409         12                0 366938510       3 356352000 FALSE             0 MONTHLY TEST PLEASE REPLY       
    #> 10 2018-12-10 02:10:55           1461361         12                0 314029000       1 244301000 FALSE             0 TEST*OK*GOOD*WATCH              
    #> # … with 139 more rows
    #> 
    #> $msgs_14
    #> # A tibble: 62 x 8
    #>    time                first_line_number message_id repeat_indicator      mmsi spare text                                                       spare2
    #>    <dttm>                          <int>      <int>            <int>     <int> <int> <chr>                                                       <int>
    #>  1 2018-12-10 00:10:00            111755         14                0 374335000     0 TX TEST PLS ACK                                                 0
    #>  2 2018-12-10 00:20:24            226974         14                0 367483860     0 DIVE OPS REQ HALF MILE CPA                                      0
    #>  3 2018-12-10 01:31:17           1020180         14                0 367483860     0 DIVE OPS REQ HALF MILE CPA                                      0
    #>  4 NA                            1353239         14                0   4310704     0 <INFORMATION> 11:00JST TIDAL CURRENT IS W GOING 8 KNOTS I…      0
    #>  5 NA                            1379656         14                0 244301000     0 AIS TEST MSG  PLEASE CONFIRM  THANK YOU  HAVE A GOOD WATC…      0
    #>  6 NA                            3019339         14                0   2633030     0 FROM ROCA CTRL: IMO MRS REPORTS TO ROCA CONTROL SHOULD BE…      0
    #>  7 2018-12-10 07:57:58           5365817         14                0 970014447     0 SART TEST                                                       0
    #>  8 2018-12-10 08:28:56           5728109         14                0 370377000     0 TEST OK                                                         0
    #>  9 2018-12-10 08:33:36           5783916         14                0 368926095     0 MSG FROM 368926095                                              0
    #> 10 2018-12-10 08:37:20           5828212         14                0 368926095     0 DO U KNOW DA WAY                                                0
    #> # … with 52 more rows
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
    #> # A tibble: 1,631,655 x 33
    #>    time                first_line_numb… message_id repeat_indicator   mmsi spare   sog position_accura… lng_deg lat_deg   cog true_heading timestamp
    #>    <dttm>                         <int>      <int>            <int>  <int> <int> <dbl>            <int>   <dbl>   <dbl> <dbl>        <int>     <int>
    #>  1 2018-12-10 00:00:00                6         18                0 2.52e8     0 0                    0  -23.7     64.9 164.           511        58
    #>  2 2018-12-10 00:00:00               13         18                0 3.38e8     0 0                    1 -117.      32.7  63.1          511        58
    #>  3 2018-12-10 00:00:00               14         18                0 3.68e8     0 0                    1 -124.      42.0 210            511        58
    #>  4 2018-12-10 00:00:00               15         18                0 3.66e8     0 0                    1 -124.      42.0 253.           511        58
    #>  5 2018-12-10 00:00:00               23         18                0 2.57e8     0 0                    1   26.0     71.0 340.           511        58
    #>  6 2018-12-10 00:00:00               24         18                0 2.66e8     0 0                    0   18.1     59.1   0            511        59
    #>  7 2018-12-10 00:00:00               38         18                0 3.38e8     0 0                    0  -74.1     40.1 192.           511        59
    #>  8 2018-12-10 00:00:00               53         18                0 2.58e8     0 0                    1    5.74    59.8 235.           511        59
    #>  9 2018-12-10 00:00:00               70         18                0 3.38e8     0 0                    0 -122.      47.6 263            511        58
    #> 10 2018-12-09 23:59:58              100         18                0 7.10e8     0 0.100                1  -46.3    -24.0 284.           511        13
    #> # … with 1,631,645 more rows, and 20 more variables: spare2 <int>, unit_flag <int>, display_flag <int>, dsc_flag <int>, band_flag <int>,
    #> #   m22_flag <int>, mode_flag <int>, raim <lgl>, commstate_flag <int>, slot_timeout <int>, slot_offset <int>, utc_hour <int>, utc_min <int>,
    #> #   utc_spare <int>, slot_number <int>, received_stations <int>, slot_increment <int>, slots_to_allocate <int>, keep_flag <int>,
    #> #   commstate_cs_fill <int>
    #> 
    #> $msgs_19
    #> # A tibble: 5,628 x 25
    #>    time                first_line_numb… message_id repeat_indicator   mmsi spare   sog position_accura… lng_deg lat_deg   cog true_heading timestamp
    #>    <dttm>                         <int>      <int>            <int>  <int> <int> <dbl>            <int>   <dbl>   <dbl> <dbl>        <int>     <int>
    #>  1 2018-12-10 00:00:14             2816         19                0 3.16e8     0 0                    1  -52.7    47.6    0              0        60
    #>  2 2018-12-10 00:00:18             4101         19                0 3.68e8     0 0.100                0  -44.3   -23.0  214.           214         0
    #>  3 2018-12-10 00:00:22             4349         19                0 2.19e8     0 0.100                0   12.5    56.0  203.           202         0
    #>  4 2018-12-10 00:00:41             7874         19                0 9.41e8     0 0.5                  1   30.2    71.1   89.7          511        60
    #>  5 2018-12-10 00:00:43             8195         19                0 2.57e8     0 0                    0    5.90   62.3  178.             0        60
    #>  6 2018-12-10 00:01:19            14866         19                0 9.93e8     0 2.20                 0  -13.9    64.4  205.           511        60
    #>  7 NA                             18509         19                0 1.69e8     0 0.300                0  -21.9     9.71 343              0         0
    #>  8 2018-12-10 00:02:13            24853         19                0 9.41e8     0 0.100                1   13.5    68.1  135.           511        60
    #>  9 NA                             27859         19                0 1.69e8     0 0.200                0  -21.8     9.85 355              0         0
    #> 10 2018-12-10 00:02:42            30445         19                0 9.93e8     0 1.20                 0  -14.2    64.4  277.           511        60
    #> # … with 5,618 more rows, and 12 more variables: spare2 <int>, name <chr>, type_and_cargo <int>, dim_a <int>, dim_b <int>, dim_c <int>, dim_d <int>,
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
    #> # A tibble: 0 x 0
    #> 
    #> $msgs_25
    #> # A tibble: 0 x 0
    #> 
    #> $msgs_26
    #> # A tibble: 0 x 0
    #> 
    #> $msgs_27
    #> # A tibble: 0 x 0

``` r
ais_decode_df(msgs = nmea_file)
```

    #> # A tibble: 10,639,764 x 70
    #>    time                first_line_numb… message_id repeat_indicator   mmsi nav_status rot_over_range   rot    sog position_accura… lng_deg lat_deg
    #>    <dttm>                         <int>      <int>            <int>  <int>      <int> <lgl>          <dbl>  <dbl>            <int>   <dbl>   <dbl>
    #>  1 2018-12-10 00:00:00                3          1                0 3.10e8          0 FALSE              0 11.2                  1   -82.9    27.6
    #>  2 NA                                 4          5                0 3.70e8         NA NA                NA NA                   NA    NA      NA  
    #>  3 2018-12-10 00:00:00                6         18                0 2.52e8         NA NA                NA  0                    0   -23.7    64.9
    #>  4 2018-12-10 00:00:00                8          1                0 2.58e8          0 FALSE              0  0.100                0    30.0    69.7
    #>  5 2018-12-10 00:00:00                9          3                0 2.66e8          5 FALSE              0  0                    1    17.9    59.3
    #>  6 2018-12-10 00:00:00               12          3                0 2.66e8          5 FALSE              0  0                    1    15.6    56.2
    #>  7 2018-12-10 00:00:00               13         18                0 3.38e8         NA NA                NA  0                    1  -117.     32.7
    #>  8 2018-12-10 00:00:00               14         18                0 3.68e8         NA NA                NA  0                    1  -124.     42.0
    #>  9 2018-12-10 00:00:00               15         18                0 3.66e8         NA NA                NA  0                    1  -124.     42.0
    #> 10 NA                                16          5                0 2.66e8         NA NA                NA NA                   NA    NA      NA  
    #> # … with 10,639,754 more rows, and 58 more variables: cog <dbl>, true_heading <int>, timestamp <int>, special_manoeuvre <int>, spare <int>,
    #> #   raim <lgl>, sync_state <int>, slot_timeout <int>, received_stations <int>, slot_number <int>, utc_hour <int>, utc_min <int>, utc_spare <int>,
    #> #   slot_offset <int>, slot_increment <int>, slots_to_allocate <int>, keep_flag <int>, year <int>, month <int>, day <int>, hour <int>, minute <int>,
    #> #   second <int>, fix_type <int>, transmission_ctl <int>, ais_version <int>, imo_num <int>, callsign <chr>, name <chr>, type_and_cargo <int>,
    #> #   dim_a <int>, dim_b <int>, dim_c <int>, dim_d <int>, eta_month <int>, eta_day <int>, eta_hour <int>, eta_minute <int>, draught <dbl>,
    #> #   destination <chr>, dte <int>, alt <int>, alt_sensor <int>, spare2 <int>, assigned_mode <int>, seq_num <int>, dest_mmsi <int>,
    #> #   retransmitted <lgl>, text <chr>, unit_flag <int>, display_flag <int>, dsc_flag <int>, band_flag <int>, m22_flag <int>, mode_flag <int>,
    #> #   commstate_flag <int>, commstate_cs_fill <int>, spare3 <int>

## Performance

``` r
bench::mark(
  `ais_decode_list()` = decoded <- ais_decode_list(
    nmea_file, as_tibble = FALSE, as_sf = FALSE, verbose = FALSE
  )
)
```

    #> # A tibble: 1 x 6
    #>   expression             min   median `itr/sec` mem_alloc `gc/sec`
    #>   <bch:expr>        <bch:tm> <bch:tm>     <dbl> <bch:byt>    <dbl>
    #> 1 ais_decode_list()      16s      16s    0.0627    3.96GB   0.0627

# Credits

  - AIS decoding routines are built on top of [Kurt
    Schwehr](https://twitter.com/kurtschwehr)’s
    [**libais**](https://github.com/schwehr/libais).
