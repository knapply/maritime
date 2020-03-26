#include "maritime.h"

template <maritime::ais::MSG_TYPE msg_type_T,
          class libais_msg_T,
          class msg_df_T,
          int pad>
SEXP ais_decode_filter_file(const std::string& file_path,
                            const bool as_tibble,
                            const bool as_sf,
                            const bool verbose) {
  constexpr char delim = '\n';
  constexpr int init_line_size = 70;

  std::error_code error;
  mio::mmap_source mmap;
  mmap.map(file_path, error);
  if (error) {
    maritime::handle_mmap_error(error);
  }

  const auto file_size = mmap.size();

  std::vector<std::size_t> offsets{0};
  offsets.reserve(file_size / init_line_size);
  for (std::size_t i = 0; i < file_size; ++i) {
    if (mmap[i] == delim) {
      offsets.push_back(i + 1);
    }
  }

  const auto n_lines = offsets.size() - 1;
  std::vector<std::string> bodies(n_lines);
  std::vector<maritime::ais::MSG_TYPE> msg_types(n_lines);

#pragma omp parallel for
  for (std::size_t i = 0; i < n_lines; ++i) {
    const std::string line(mmap.begin() + offsets[i],
                           mmap.begin() + offsets[i + 1] - 1);
    auto body = maritime::ais::get_body(line);

    maritime::rstrip(body);
    bodies[i] = body;
    msg_types[i] = maritime::ais::get_msg_type(body);
  }

  mmap.unmap();

  std::size_t n_msgs = 0;
#pragma omp parallel for reduction(+ : n_msgs)
  for (std::size_t i = 0; i < n_lines; ++i) {
    if (msg_types[i] == msg_type_T) {
      n_msgs++;
    }
  }

  maritime::Progress progress(n_lines, verbose);
  msg_df_T out(n_msgs);
  for (std::size_t i = 0; i < n_lines; ++i) {
    progress.increment();

    if (msg_types[i] == msg_type_T) {
      out.push(libais_msg_T(bodies[i].c_str(), 0));
    }
  }

  return maritime::as_df(out, as_tibble, as_sf);
}

// [[Rcpp::export(.ais_decode_filter_file_impl)]]
SEXP ais_decode_filter_file_impl(const std::string& file_path,
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