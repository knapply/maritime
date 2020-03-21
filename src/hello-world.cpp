#include <Rcpp.h>
using namespace Rcpp;

#include <libais/src/libais/decode_body.h>

// [[Rcpp::export]]
NumericVector timesTwo(NumericVector x) {
  return x * 2;
}

// [[Rcpp::export]]
void test() {
    auto msg = libais::CreateAisMsg("K8VSqb9LdU28WP7h", 0);
}

/*** R
timesTwo(42)
*/
