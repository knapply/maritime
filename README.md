`{maritime}`
================

  - [Introduction](#introduction)
  - [Installation](#installation)
  - [Usage](#usage)
  - [Shout Outs](#shout-outs)

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

# Shout Outs

  - The AIS decoding routines rely on [Kurt
    Schwehr](http://schwehr.org/blog)’s
    [**libais**](https://github.com/schwehr/libais) and its richly
    detailed comments.
