#ifndef MARITIME_H
#define MARITIME_H

#include <Rcpp.h>
typedef Rcpp::CharacterVector vec_chr;
typedef Rcpp::IntegerVector vec_int;
typedef Rcpp::LogicalVector vec_lgl;
typedef Rcpp::DoubleVector vec_dbl;

#include <mio/mmap.hpp>
namespace maritime {
#include <progress.hpp>
}

#include "maritime-utils.h"


#include "ais.h"

#include "maritime-ais-msgs.h"
#include "maritime-ais.h"
#include "maritime-omp.h"

#endif
