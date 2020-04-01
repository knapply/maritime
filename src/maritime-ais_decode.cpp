#include "maritime-ais.h"
#include "maritime-ais_stream.h"

using namespace maritime::ais;

template <MSG_TYPE msg_type_T,
          class libais_msg_T,
          class msg_df_T,
          std::size_t PAD>
SEXP ais_decode_filter_file(const std::vector<std::string>& file_path,
                            const bool& verbose) {
  auto ais = AIS_Stream(file_path);
  auto proto_df = ais.to_db<msg_type_T, libais_msg_T, msg_df_T, PAD>(verbose);
  return proto_df.as_df();
}

// [[Rcpp::export(.ais_decode_filter_file_impl)]]
SEXP ais_decode_filter_file_impl(const std::vector<std::string>& file_path,
                                 const int msg_type,
                                 const bool verbose) {
  const auto enum_msg_type = static_cast<MSG_TYPE>(msg_type);

  switch (enum_msg_type) {
    case MSG_TYPE::msg_1_2_3:
      return ais_decode_filter_file<MSG_TYPE::msg_1_2_3, libais::Ais1_2_3,
                                    Msgs_1_2_3, 0>(file_path, verbose);

    case MSG_TYPE::msg_4_11:
      return ais_decode_filter_file<MSG_TYPE::msg_4_11, libais::Ais4_11,
                                    Msgs_4_11, 0>(file_path, verbose);

    default:
      return R_NilValue;
  }
}




// namespace detail {
// class Line : std::string {
//   friend std::stringstream& operator>>(mmap_ptr is, Line& line) {
//     return std::getline(is, line);
//   }
// };
// }  // namespace detail

// template <class OutIt>
// void read_lines(mmap_ptr is, OutIt dest) {
//   typedef std::istream_iterator<detail::Line> InIt;
//   std::copy(InIt(is), InIt(), dest);
// }

// //  [[Rcpp::export(.ais_decode_filter_file_impl)]]
// SEXP decode(const std::vector<std::string> file_path) {
//   const std::size_t n_files = file_path.size();
//   std::vector<mmap_ptr> mmaps(n_files);
//   std::vector<std::size_t> file_sizes(n_files, 0);
//   std::size_t total_size = 0;

//   for (std::size_t i_file = 0; i_file < n_files; ++i_file) {
//     std::error_code error;
//     mio::shared_mmap_source mmap;

//     mmap.map(file_path[i_file], error);
//     if (error) {
//       maritime::handle_error("error mapping file: %s, exiting...\n", error);
//     }

//     const std::size_t file_size = mmap.size();
//     mmaps[i_file] = mmap.get_shared_ptr();
//     file_sizes[i_file] = file_size;
//     total_size += file_size;
//   }

//   std::vector<std::string> v;
//     for (std::size_t i_file = 0; i_file < n_files; ++i_file) {
//       read_lines(mmaps[i_file], std::back_inserter(v));
//     }

//   return Rcpp::wrap(v.size());

//   // std::vector<std::string> bods(n_lines);

//   // std::vector<libais::Ais1_2_3> ais_1_2_3;
// }