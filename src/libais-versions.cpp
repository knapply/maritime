#include <Rcpp.h>

#include "ais.h"

//' `libais` Version Information
//'
//' @examples
//' libais_version()
//' libais_version_major()
//' libais_version_minor()
//'
//' @export
// [[Rcpp::export]]
Rcpp::List libais_version() {
    auto out = Rcpp::List::create(
        Rcpp::IntegerVector({LIBAIS_VERSION_MAJOR, LIBAIS_VERSION_MINOR})
    );
    out.attr("class") = "numeric_version";
    return out;
}


//' @rdname libais_version
//'
//' @export
// [[Rcpp::export]]
int libais_version_major() {
    return LIBAIS_VERSION_MAJOR;
}


//' @rdname libais_version
//'
//' @export
// [[Rcpp::export]]
int libais_version_minor() {
    return LIBAIS_VERSION_MINOR;
}