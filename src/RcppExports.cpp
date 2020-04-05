// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// ais_version
Rcpp::List ais_version();
RcppExport SEXP _maritime_ais_version() {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    rcpp_result_gen = Rcpp::wrap(ais_version());
    return rcpp_result_gen;
END_RCPP
}
// ais_decode_strings
Rcpp::List ais_decode_strings(const Rcpp::CharacterVector& x, const bool as_df, const bool verbose);
RcppExport SEXP _maritime_ais_decode_strings(SEXP xSEXP, SEXP as_dfSEXP, SEXP verboseSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const Rcpp::CharacterVector& >::type x(xSEXP);
    Rcpp::traits::input_parameter< const bool >::type as_df(as_dfSEXP);
    Rcpp::traits::input_parameter< const bool >::type verbose(verboseSEXP);
    rcpp_result_gen = Rcpp::wrap(ais_decode_strings(x, as_df, verbose));
    return rcpp_result_gen;
END_RCPP
}
// ais_decode_file
SEXP ais_decode_file(const std::string& file_path, const bool as_df, const bool verbose);
RcppExport SEXP _maritime_ais_decode_file(SEXP file_pathSEXP, SEXP as_dfSEXP, SEXP verboseSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::string& >::type file_path(file_pathSEXP);
    Rcpp::traits::input_parameter< const bool >::type as_df(as_dfSEXP);
    Rcpp::traits::input_parameter< const bool >::type verbose(verboseSEXP);
    rcpp_result_gen = Rcpp::wrap(ais_decode_file(file_path, as_df, verbose));
    return rcpp_result_gen;
END_RCPP
}
// nmea_df
SEXP nmea_df(const std::string& file_path, const int n_max);
RcppExport SEXP _maritime_nmea_df(SEXP file_pathSEXP, SEXP n_maxSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::string& >::type file_path(file_pathSEXP);
    Rcpp::traits::input_parameter< const int >::type n_max(n_maxSEXP);
    rcpp_result_gen = Rcpp::wrap(nmea_df(file_path, n_max));
    return rcpp_result_gen;
END_RCPP
}
// nest_test
SEXP nest_test(const std::string& file_path);
RcppExport SEXP _maritime_nest_test(SEXP file_pathSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::string& >::type file_path(file_pathSEXP);
    rcpp_result_gen = Rcpp::wrap(nest_test(file_path));
    return rcpp_result_gen;
END_RCPP
}
// decode_filter_file_impl
SEXP decode_filter_file_impl(const std::string& file_path, const int msg_type, const bool verbose);
RcppExport SEXP _maritime_decode_filter_file_impl(SEXP file_pathSEXP, SEXP msg_typeSEXP, SEXP verboseSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::string& >::type file_path(file_pathSEXP);
    Rcpp::traits::input_parameter< const int >::type msg_type(msg_typeSEXP);
    Rcpp::traits::input_parameter< const bool >::type verbose(verboseSEXP);
    rcpp_result_gen = Rcpp::wrap(decode_filter_file_impl(file_path, msg_type, verbose));
    return rcpp_result_gen;
END_RCPP
}
// decode_list_file_impl
SEXP decode_list_file_impl(const std::string& file_path, const bool verbose);
RcppExport SEXP _maritime_decode_list_file_impl(SEXP file_pathSEXP, SEXP verboseSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::string& >::type file_path(file_pathSEXP);
    Rcpp::traits::input_parameter< const bool >::type verbose(verboseSEXP);
    rcpp_result_gen = Rcpp::wrap(decode_list_file_impl(file_path, verbose));
    return rcpp_result_gen;
END_RCPP
}
// unwrap_ais_ptr
SEXP unwrap_ais_ptr(const SEXP ais_ptr);
RcppExport SEXP _maritime_unwrap_ais_ptr(SEXP ais_ptrSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const SEXP >::type ais_ptr(ais_ptrSEXP);
    rcpp_result_gen = Rcpp::wrap(unwrap_ais_ptr(ais_ptr));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_maritime_ais_version", (DL_FUNC) &_maritime_ais_version, 0},
    {"_maritime_ais_decode_strings", (DL_FUNC) &_maritime_ais_decode_strings, 3},
    {"_maritime_ais_decode_file", (DL_FUNC) &_maritime_ais_decode_file, 3},
    {"_maritime_nmea_df", (DL_FUNC) &_maritime_nmea_df, 2},
    {"_maritime_nest_test", (DL_FUNC) &_maritime_nest_test, 1},
    {"_maritime_decode_filter_file_impl", (DL_FUNC) &_maritime_decode_filter_file_impl, 3},
    {"_maritime_decode_list_file_impl", (DL_FUNC) &_maritime_decode_list_file_impl, 2},
    {"_maritime_unwrap_ais_ptr", (DL_FUNC) &_maritime_unwrap_ais_ptr, 1},
    {NULL, NULL, 0}
};

RcppExport void R_init_maritime(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
