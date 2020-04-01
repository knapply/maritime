// #include <Rcpp.h>

// #include <regex>

// #include "ais.h"

// struct TagBlockBuilder {
//   const std::regex time;
//   const std::regex dest;

//   TagBlockBuilder() : time("\d{10,15}(\.\d*)?"), dest("^*,\\]{1,15}"){};
// };

// // struct TagBlock {
// //     int time;
// //     std::string dest;
// //     int group;
// //     int sentence_num;
// //     int sentence_tot;
// //     int group_id;
// //     int line_num;
// //     std::string quality;
// //     int rel_time;
// //     std::string rcvr;
// //     std::string text;
// //     std::string text_date;
// //     std::string tag_checksum;
// //     std::string payload;
// // };

// //ff [[Rcpp::export(.parse)]]
// int parse(const std::string& x) {
//   const std::regex pat(
//       R"(!([A-Z][A-Z])(VD[MO]),(\d),(\d),([\d])?,([AB])?,([;:=@a-zA-Z0-9<>\?\'\`]*),(\d)\*([0-9A-F][0-9A-F]))");

//   std::smatch match;
//   std::regex_match(x, match, pat);

//   return match.size();
// }

// bool is_bare_vdm(const std::string& x) {
//   const std::regex pat(R"([!$][A-Z]{2}VD[MO][^*!$]*\\*[0-9A-Fa-f]{2})");
//     std::smatch match;
//     return std::regex_search(x, match, pat);
// }

// // ff[[Rcpp::export(.q)]]
// // SEXP q(const std::vector<std::string>& x) {
// //   libais::NmeaSentence""
// // }