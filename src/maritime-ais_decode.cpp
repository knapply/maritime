
#include <mio/shared_mmap.hpp>

#include "maritime.h"

typedef std::shared_ptr<mio::basic_mmap<mio::access_mode::read, char>> mmap_ptr;

template <maritime::ais::MSG_TYPE msg_type_T,
          class libais_msg_T,
          class msg_df_T,
          int pad>
SEXP ais_decode_filter_file(const std::vector<std::string> file_path,
                            const bool as_tibble,
                            const bool as_sf,
                            const bool verbose) {
  constexpr char delim = '\n';
  constexpr int init_line_size = 70;

  const std::size_t n_files = file_path.size();
  std::vector<mmap_ptr> mmaps(n_files);
  std::vector<std::size_t> file_sizes(n_files, 0);
  std::size_t total_size = 0;

  for (std::size_t i_file = 0; i_file < n_files; ++i_file) {
    std::error_code error;

    mio::shared_mmap_source mmap;
    mmap.map(file_path[i_file], error);
    if (error) {
      Rcpp::stop("mmap error");
      // maritime::handle_mmap_error(error);
    }
    const std::size_t file_size = mmap.size();
    mmaps[i_file] = mmap.get_shared_ptr();
    file_sizes[i_file] = file_size;
    total_size += file_size;
  }

  std::vector<std::vector<std::size_t>> offsets(n_files);
  for (std::size_t i_file = 0; i_file < n_files; ++i_file) {
    offsets[i_file].push_back(0);
    offsets[i_file].reserve(file_sizes[i_file] / init_line_size);
  }
  std::vector<std::size_t> n_lines(n_files);
  std::size_t total_lines = 0;

  for (std::size_t i_file = 0; i_file < n_files; ++i_file) {
    for (std::size_t j_line = 0; j_line < file_sizes[i_file]; ++j_line) {
      if ((*mmaps[i_file])[j_line] == delim) {
        offsets[i_file].push_back(j_line + 1);
        n_lines[i_file]++;
      }
    }
    n_lines[i_file] = offsets[i_file].size() - 1;
    total_lines += n_lines[i_file];
  }

  std::vector<std::string> bodies(total_lines);
  std::vector<maritime::ais::MSG_TYPE> msg_types(total_lines);

  std::vector<std::size_t> file_starts(n_files + 1);
  std::partial_sum(n_lines.begin(), n_lines.end(), file_starts.begin() + 1);

#pragma omp_parallel for
  for (std::size_t i_file = 0; i_file < n_files; ++i_file) {
#pragma omp parallel for
    for (std::size_t j_line = 0; j_line < n_lines[i_file]; ++j_line) {
      const std::string line(
          mmaps[i_file]->begin() + offsets[i_file][j_line],
          mmaps[i_file]->begin() + offsets[i_file][j_line + 1] - 1);

      const auto body = maritime::ais::get_body(line);
      bodies[file_starts[i_file] + j_line] = body;
      msg_types[file_starts[i_file] + j_line] =
          maritime::ais::get_msg_type(body);
    }
    mmaps[i_file]->unmap();
  }

  std::size_t n_msgs = 0;
#pragma omp parallel for reduction(+ : n_msgs)
  for (std::size_t i = 0; i < total_lines; ++i) {
    if (msg_types[i] == msg_type_T) {
      n_msgs++;
    }
  }

  msg_df_T out(n_msgs);
  Progress progress(total_lines, verbose);
  for (std::size_t i = 0; i < total_lines; ++i) {
    progress.increment();

    if (msg_types[i] == msg_type_T) {
      out.push(libais_msg_T(bodies[i].c_str(), 0));
    }
  }

  return maritime::as_df(out, as_tibble, as_sf);
}

// [[Rcpp::export(.ais_decode_filter_file_impl)]]
SEXP ais_decode_filter_file_impl(const std::vector<std::string>& file_path,
                                 const int msg_type,
                                 const bool as_tibble,
                                 const bool as_sf,
                                 const bool verbose) {
  using namespace maritime::ais;
  const auto enum_msg_type = static_cast<MSG_TYPE>(msg_type);

  switch (enum_msg_type) {
    case MSG_TYPE::msg_1_2_3:
      return ais_decode_filter_file<MSG_TYPE::msg_1_2_3, libais::Ais1_2_3,
                                    Msgs_1_2_3, 0>(file_path, as_tibble, as_sf,
                                                   verbose);

    case MSG_TYPE::msg_4_11:
      return ais_decode_filter_file<MSG_TYPE::msg_4_11, libais::Ais4_11,
                                    Msgs_4_11, 0>(file_path, as_tibble, as_sf,
                                                  verbose);

    default:
      return R_NilValue;
  }
}

// [[Rcpp::export(.ais_stream_test)]]
std::vector<std::string> ais_stream_test(
    const std::vector<std::string>& file_path) {
  auto test = maritime::ais::AIS_Stream(file_path);
  return test.get_lines();
}
