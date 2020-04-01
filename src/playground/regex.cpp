// [[Rcpp::plugins(openmp)]]
#include <Rcpp.h>
#include <omp.h>
using namespace Rcpp;

#include <regex>

// [[Rcpp::export]]
std::vector<std::string> str_split_at_char(const std::string& x,
                                           const char& pattern) {
  const auto n_out =
      std::count_if(x.begin(), x.end(),
                    [&pattern](const char& chr) { return chr == pattern; });

  std::vector<std::string> out;
  out.reserve(n_out + 1);

  std::string element;
  std::stringstream sstream(x);
  while (std::getline(sstream, element, pattern)) {
    out.push_back(element);
  }

  return out;
}


// [[Rcpp::export]]
void str_vec_split_at_char(const std::vector<std::string>& x) {
  // const char& pattern) {
  const auto n_out = x.size();
  std::vector<std::vector<std::string>> out(n_out);

#pragma omp parallel for simd
  for (std::size_t i = 0; i < n_out; ++i) {
    out[i] = str_split_at_char(x[i], ',');
  }
  //   return out;
}

// [[Rcpp::export]]
std::vector<std::string> str_split_at_commas(const std::string& x) {
  return str_split_at_char(x, ',');
}

// [[Rcpp::export()]]
bool checksum(const std::string& x) {
  if (x.size() < 3 || x[0] != '!') {
    return false;
  }



  const auto asterisk = std::find(x.begin(), x.end(), '*');
  if (asterisk == x.end()) {
    return false;
  }

  const uint8_t target_int =
      std::accumulate(x.begin() + 1, asterisk, 0, std::bit_xor<uint8_t>());

  std::stringstream target;
  target << std::hex << target_int;
  const std::string checksum_string(asterisk + 1, asterisk + 3);

  return target_int == strtol(checksum_string.c_str(), NULL, 16);
}

// 33[[Rcpp::export]]
// std::vector<bool> is_valid_checksum2(const std::vector<std::string>& x) {
//   const auto n = x.size();
//   std::vector<bool> out(n);

// #pragma omp parallel for simd
//   for (std::size_t i = 0; i < n; ++i) {
// #pragma omp ordered simd
//     out[i] = is_valid_checksum(x[i]);
//   }

//   return out;
// }

//ff [[Rcpp::export]]
// void split_if_valid_checksum(
//     const std::vector<std::string>& x) {
//   const auto valid_checksums = is_valid_checksum2(x);

// //   std::string mold;
// //   mold.reserve(100);
//   std::vector<std::vector<std::string>> out(x.size());
//   out.reserve(x.size());

//   for (std::size_t i = 0; i < x.size(); ++i) {
//     if (valid_checksums[i]) {
//       out.push_back(str_split_at_commas(x[i]));
//     }
//   }

// //   return out;
// }

/*** R
# lines <- readr::read_lines("inst/example-data/big-files/20181219.log")
# test <- split_if_valid_checksum(lines)
# target <- sapply(lines, is_valid_checksum_, USE.NAMES = FALSE) # # # #
# bench::mark(test <- is_valid_checksum2(lines)) # identical(target, test) #
test <- bench::mark(split_if_valid_checksum(lines))
# b = #
# stringi::stri_split_fixed(lines, ","), check = FALSE # )
*/
