#ifndef MARITIME_AIS_STREAM_H
#define MARITIME_AIS_STREAM_H

#include <boost/algorithm/string.hpp>

#include "maritime.h"

namespace maritime {
namespace ais {

typedef std::shared_ptr<mio::basic_mmap<mio::access_mode::read, char>> mmap_ptr;

class AIS_Stream {
  std::vector<std::string> lines;
  std::vector<MSG_TYPE> msg_types;

 public:
  static constexpr char delim = '\n';
  // static constexpr std::size_t max_line_size = 82; max body size?
  static constexpr std::size_t max_line_size = 112;

  AIS_Stream(const std::vector<std::string> file_path, const bool verbose = true) {
    const std::size_t n_files = file_path.size();
    std::vector<mmap_ptr> mmaps(n_files);
    std::vector<std::size_t> file_sizes(n_files, 0);
    std::size_t total_size = 0;

    for (std::size_t i_file = 0; i_file < n_files; ++i_file) {
      std::error_code error;

      mio::shared_mmap_source mmap;
      mmap.map(file_path[i_file], error);
      if (error) {
        handle_error("error mapping file: %s, exiting...\n", error);
      }
      const std::size_t file_size = mmap.size();
      mmaps[i_file] = mmap.get_shared_ptr();
      file_sizes[i_file] = file_size;
      total_size += file_size;
    }

    std::vector<std::vector<std::size_t>> offsets(n_files);
    for (std::size_t i_file = 0; i_file < n_files; ++i_file) {
      offsets[i_file].push_back(0);
      offsets[i_file].reserve(file_sizes[i_file] / max_line_size);
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

    std::vector<std::size_t> file_starts(n_files + 1);
    std::partial_sum(n_lines.begin(), n_lines.end(), file_starts.begin() + 1);

    Progress progress(total_lines);
    this->lines.resize(total_lines);
    this->msg_types.resize(total_lines);

    for (std::size_t i_file = 0; i_file < n_files; ++i_file) {
#pragma omp parallel for
      for (std::size_t j_line = 0; j_line < n_lines[i_file]; ++j_line) {
        progress.increment();

        const std::string line(
            mmaps[i_file]->begin() + offsets[i_file][j_line],
            mmaps[i_file]->begin() + offsets[i_file][j_line + 1] - 2);

        const auto body = maritime::ais::get_body(line);

        this->lines[file_starts[i_file] + j_line] = line;
        this->msg_types[file_starts[i_file] + j_line] =
            maritime::ais::get_msg_type(body);
      }
      mmaps[i_file]->unmap();
    };
  };

  std::vector<std::string> get_lines() { return this->lines; };
};

}  // namespace ais
}  // namespace maritime

#endif