#include <Rcpp.h>
using namespace Rcpp;

#include "decode_body.h"

#include "ais.h"

// [[Rcpp::export]]
Rcpp::NumericVector timesTwo(Rcpp::NumericVector x) {
  return x * 2;
}

// [[Rcpp::export]]
int body_to_mmsi(const std::string& bod = "K8VSqb9LdU28WP7h") {
  auto msg = libais::CreateAisMsg(bod, 0);
  return msg->mmsi;
}

/*** R
timesTwo(42)
*/
