#include <Rcpp.h>
using namespace Rcpp;

#include <regex>

#include "maritime-omp.h"

std::vector<std::string> str_split(const std::string& line, char delim) {
  std::vector<std::string> result;
  std::stringstream ss(line);
  while (!ss.eof()) {
    std::string next;
    std::getline(ss, next, delim);
    result.push_back(next);
  }
  return result;
}

class VDM {
  // const char pat_parse_vdm[100] =
  // R"(!([A-Z][A-Z])(VD[MO]),(\d),(\d),([\d])?,([AB])?,([;:=@a-zA-Z0-9<>\?\'\`]*),(\d)\*([0-9A-F][0-9A-F]))";
  std::string vdm;
  std::string talker;
  std::string vdm_type;
  int sen_tot;
  int sen_num;
  int seq_id;
  std::string chan;
  std::string body;
  int fill_bits;
  std::string checksum;

 public:
  VDM(std::string _vdm,
      std::string _talker,
      std::string _vdm_type,
      std::string _sen_tot,
      std::string _sen_num,
      std::string _seq_id,
      std::string _chan,
      std::string _body,
      std::string _fill_bits,
      std::string _checksum)
      : vdm(_vdm),
        talker(_talker),
        vdm_type(_vdm_type),
        chan(_chan),
        body(_body),
        checksum(_checksum) {
    if (!_sen_tot.empty()) {
      this->sen_tot = std::stoi(_sen_tot);
    }
    if (!_sen_num.empty()) {
      this->sen_num = std::stoi(_sen_num);
    }
    if (!_seq_id.empty()) {
      this->seq_id = std::stoi(_seq_id);
    }
    if (!_fill_bits.empty()) {
      this->fill_bits = std::stoi(_fill_bits);
    }
  };

  SEXP as_list() const {
    using Rcpp::_;
    return Rcpp::List::create(             //
        _["talker"] = this->talker,        //
        _["vdm_type"] = this->vdm_type,    //
        _["sen_tot"] = this->sen_tot,      //
        _["sen_num"] = this->sen_num,      //
        _["seq_id"] = this->seq_id,        //
        _["chan"] = this->chan,            //
        _["body"] = this->body,            //
        _["fill_bits"] = this->fill_bits,  //
        _["checksum"] = this->checksum     //
    );
  }
};

class AIS_Utils {
  // RcppModules can't find these if they're `static constexpr`
  // and `inline static constexpr const char` seems to just be >= C++17
  const char pat_CHECKSUM[20] = R"(\*([0-9A-Fa-f]{2})$)";
  const char pat_SENTENCE_START[8] = R"(^[\\$!])";

  const char pat_ID_BARE[37] = R"([!$][A-Z]{4}[^*!$]*\*[0-9A-Fa-f]{2}$)";
  const char pat_ID_UCSG[45] =
      R"([!$][A-Z]{4}[^*!$]*\*[0-9A-Fa-f]{2},[^*!$]+$)";
  const char pat_ID_TAGB[51] =
      R"(\\([a-zA-Z]:[^*,\\]*[,]?)+\*[0-9A-Fa-f]{2}(\\.*)?$)";
  const char pat_ID_BARE_VDM[42] =
      R"([!$][A-Z]{2}VD[MO][^*!$]*\*[0-9A-Fa-f]{2})";
  // const char pat_NMEA_HEADER[42] = R"([$!]([A-Z][A-Z]))";
  // const char pat_NMEA_SENTENCE[31] = R"([$!]([A-Z][A-Z])([A-Z]{3,4}),))";
  const char pat_NMEA_CHECKSUM[17] = R"([0-9A-F][0-9A-F])";

  const char pat_parse_vdm[101] =
      R"(!([A-Z][A-Z])(VD[MO]),(\d),(\d),(\d)?,([AB])?,([;:=@a-zA-Z0-9<>\?\'\`]*),(\d)\*([0-9A-F][0-9A-F]))";

  const char TEXT[5] = "TEXT";
  const char BARE[5] = "BARE";
  const char TAGB[5] = "TAGB";
  const char USCG[5] = "USCG";

  std::regex CHECKSUM_RE;
  std::regex SENTENCE_START_RE;

  std::regex ID_BARE_RE;
  std::regex ID_USCG_RE;
  std::regex ID_TAGB_RE;
  std::regex ID_BARE_VDM_RE;

  // std::regex NMEA_HEADER_RE;
  // std::regex NMEA_SENTENCE_RE;
  std::regex NMEA_CHECKSUM_RE;

  std::regex parse_vdm_RE;

 public:
  AIS_Utils()
      : CHECKSUM_RE(this->pat_CHECKSUM),
        SENTENCE_START_RE(this->pat_SENTENCE_START),
        ID_BARE_RE(this->pat_ID_BARE),
        ID_USCG_RE(this->pat_ID_UCSG),
        ID_TAGB_RE(this->pat_ID_TAGB),
        ID_BARE_VDM_RE(this->pat_ID_BARE_VDM),
        // NMEA_HEADER_RE(this->pat_NMEA_HEADER),
        // NMEA_SENTENCE_RE(this->pat_NMEA_SENTENCE),
        NMEA_CHECKSUM_RE(this->pat_NMEA_CHECKSUM),
        parse_vdm_RE(this->pat_parse_vdm){};

  std::vector<std::string> split_line(const std::string& line) {
    std::vector<std::string> out;
    std::stringstream stream(line);
    while (!stream.eof()) {
      std::string next;
      std::getline(stream, next, ',');
      out.push_back(next);
    }
    return out;
  }

  std::vector<uint8_t> calc_checksum(const std::vector<std::string>& x) const {
    std::vector<uint8_t> out(x.size());

#pragma omp parallel for
    for (std::size_t i = 0; i < x.size(); ++i) {
      auto chr = x[i].c_str();
      *chr++;
      uint8_t res = 0;
      while (*chr != '*' && *chr != '\r' && *chr != '\n' && *chr != '\0') {
        res ^= (uint8_t) * (chr++);
      }
      out[i] = res;
    }

    return out;
  };

  bool is_valid_checksum(const std::string& sentence) const {
    if (sentence.size() < 3 || sentence[0] != '!') {
      return false;
    }

    uint8_t target = 0;
    auto it = sentence.begin() + 1;
    while (it != sentence.end() && *it != '*') {
      target ^= (uint8_t)*it;
      it++;
    }

    char test[3];
    test[0] = *it + 1;
    test[1] = *it + 2;

    // std::string test(it + 1, it + 2);
    Rcpp::Rcout << std::to_string(target) << std::endl;
    Rcpp::Rcout << test << std::endl;
    return target == (uint8_t)std::toupper(strtol(test, NULL, 16));
  }

  std::string linetype(const std::string& line) const {
    // return `std::string` to copy `const char[5]`
    if (line.empty()) {
      return this->TEXT;
    }

    if (line[0] == '!' || line[0] == '$') {
      if (std::regex_match(line, this->ID_BARE_RE)) {
        return this->TEXT;
      } else if (std::regex_match(line, this->ID_USCG_RE)) {
        return this->USCG;
      } else {
        return this->TEXT;
      }
    }

    if (line[0] == '\\' && std::regex_match(line, this->ID_TAGB_RE)) {
      return this->TAGB;
    }

    return this->TEXT;
  }
  

  std::vector<bool> is_bare_vdm(const std::vector<std::string>& x) const {
    const auto n = x.size();

    std::vector<bool> out(n);
#pragma omp parallel for
    for (std::size_t i = 0; i < n; ++i) {
      out[i] = std::regex_search(x[i], this->ID_BARE_VDM_RE);
    }

    return out;
  }

  SEXP parse_vdm(const std::string& x) {
    std::smatch match;
    std::regex_search(x, match, this->parse_vdm_RE);

    if (match.size() != 10) {
      return R_NilValue;
    }

    const auto out = VDM(match.str(0), match.str(1), match.str(2), match.str(3),
                         match.str(4), match.str(5), match.str(6), match.str(7),
                         match.str(8), match.str(9));

    return out.as_list();
  }
};

RCPP_MODULE(regex_module) {
  class_<AIS_Utils>("AIS_Utils")                                   //
      .constructor()                                               //
      .method("calc_checksum", &AIS_Utils::calc_checksum)          //
      .method("is_valid_checksum", &AIS_Utils::is_valid_checksum)  //
      .method("linetype", &AIS_Utils::linetype)                    //
      .method("is_bare_vdm", &AIS_Utils::is_bare_vdm)              //
      .method("parse_vdm", &AIS_Utils::parse_vdm)                  //
      ;
}
