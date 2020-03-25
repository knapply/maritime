// #include <Rcpp.h>

// #include <maritime/libais.hpp>

// #include "ais.h"
#include "maritime-ais-msgs.h"
#include "maritime-ais.h"

#include <fstream>

#include <mio/mmap.hpp>

#include <progress.hpp>

#ifdef _OPENMP
#include <omp.h>
#endif

//' `libais` Version Information
//'
//' @examples
//' libais_version()
//'
//' @export
// [[Rcpp::export]]
Rcpp::List libais_version() {
  auto out = Rcpp::List::create(
      Rcpp::IntegerVector({LIBAIS_VERSION_MAJOR, LIBAIS_VERSION_MINOR}));
  out.attr("class") = "numeric_version";
  return out;
}

void handle_error(const std::error_code& error) {
  const auto& errmsg = error.message();
  Rcpp::stop("error mapping file: %s, exiting...\n", errmsg.c_str());
}

// [[Rcpp::export]]
SEXP msg_test(const std::string& file_path, const bool verbose = true) {
  constexpr char delim = '\n';
  //   constexpr int pad = 0;
  constexpr int init_line_size = 70;

  std::error_code error;
  mio::mmap_source mmap;
  mmap.map(file_path, error);
  if (error) {
    handle_error(error);
  }

  const auto file_size = mmap.size();

  std::vector<std::size_t> offsets;
  offsets.reserve(file_size / init_line_size);
  offsets.push_back(0);
  for (std::size_t i = 0; i < file_size; ++i) {
    if (mmap[i] == delim) {
      offsets.push_back(i + 1);
    }
  }

  const auto n_lines = offsets.size() - 1;

  //   std::string line_template;
  //   line_template.reserve(init_line_size);
  //   std::vector<std::string> lines(n_lines);
  std::vector<std::string> bodies(n_lines);
  std::vector<maritime::ais::MSG_TYPE> msg_types(n_lines);

#ifdef _OPENMP
#pragma omp parallel for simd
#endif
  for (std::size_t i = 0; i < n_lines; ++i) {
    const std::string line(mmap.begin() + offsets[i],
                           mmap.begin() + offsets[i + 1] - 1);
    auto body = maritime::ais::get_body(line);

    maritime::rstrip(body);
    // lines[i] = line;
    bodies[i] = body;
    msg_types[i] = maritime::ais::get_msg_type(body);
  }

  mmap.unmap();

  std::size_t n_msgs_1_2_3 = 0;
#ifdef _OPENMP
#pragma omp parallel for simd reduction(+ : n_msgs_1_2_3)
#endif
  for (std::size_t i = 0; i < n_lines; ++i) {
    switch (msg_types[i]) {
      case maritime::ais::MSG_TYPE::msg_1_2_3:
        n_msgs_1_2_3++;
        break;

      default:
        break;
    }
  }

  Progress progress(n_lines, verbose);
  maritime::ais::Msgs_1_2_3 out_1_2_3(n_msgs_1_2_3);
  for (std::size_t i = 0; i < n_lines; ++i) {
    progress.increment();

    switch (msg_types[i]) {
      case maritime::ais::MSG_TYPE::msg_1_2_3:
        out_1_2_3.push(  // lines[i], bodies[i],
            libais::Ais1_2_3(bodies[i].c_str(), 0));
        break;

      default:
        break;
    }
  }

  return maritime::as_df(out_1_2_3);
}