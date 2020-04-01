#ifndef MARITIME_AIS_STREAM_H
#define MARITIME_AIS_STREAM_H

#include "maritime-ais.h"
#include <progress.hpp>

#include <Rcpp.h>
#include <mio/shared_mmap.hpp>

namespace maritime {
  namespace ais {

    typedef std::shared_ptr<mio::basic_mmap<mio::access_mode::read, char>> mmap_ptr;

    class AIS_Stream {
    public:
      std::vector<std::string> lines;
      std::vector<std::string> bodies;
      std::vector<MSG_TYPE> msg_types;
      std::size_t n_msgs;

      static constexpr char delim = '\n';
      // static constexpr std::size_t max_line_size = 82; max body size?
      static constexpr std::size_t max_line_size = 112;

      explicit AIS_Stream(const std::vector<std::string> &file_path) {
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

        this->lines.resize(total_lines);
        this->msg_types.resize(total_lines);
        this->bodies.resize(total_lines);
        this->n_msgs = total_lines;

        for (std::size_t i_file = 0; i_file < n_files; ++i_file) {
#pragma omp parallel for
          for (std::size_t j_line = 0; j_line < n_lines[i_file]; ++j_line) {
            std::string line(mmaps[i_file]->begin() + offsets[i_file][j_line],
                             mmaps[i_file]->begin() + offsets[i_file][j_line + 1]);

            const auto body = maritime::ais::get_body(line);

            this->lines[file_starts[i_file] + j_line] = line;
            this->msg_types[file_starts[i_file] + j_line] =
                    maritime::ais::get_msg_type(body);
            this->bodies[file_starts[i_file] + j_line] = body;
          }
          mmaps[i_file]->unmap();
        }

        //
      };  // AIS_Stream()

      template<MSG_TYPE msg_type_T,
              class libais_msg_T,
              class msg_df_T,
              std::size_t PAD>
      msg_df_T to_db(const bool verbose = false) {
        Progress progress(n_msgs, verbose);

        std::size_t n_targets = 0;
#pragma omp parallel for reduction(+ : n_targets)
        for (std::size_t i = 0; i < this->n_msgs; ++i) {
          if (this->msg_types[i] == msg_type_T) {
            n_targets++;
          }
        }

        msg_df_T out(n_targets);
        for (std::size_t i = 0; i < this->n_msgs; ++i) {
          progress.increment();
          if (msg_types[i] == msg_type_T) {
            const libais_msg_T msg(bodies[i].c_str(), PAD);
            out.push(msg);
          }
        }

        return out;

        // return out;
      };  // build_filtered_db()
    };

  }  // namespace ais
}  // namespace maritime

#endif