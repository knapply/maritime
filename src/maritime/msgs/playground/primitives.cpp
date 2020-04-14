#include <Rcpp.h>

enum class MSG_TYPE {
  unknown = 0,
  msg_1_2_3 = 1,
  msg_4_11 = 2,
  msg_5 = 3,
  msg_6 = 4,
  msg_7_13 = 5,
  msg_8 = 6,
  msg_9 = 7,
  msg_10 = 8,
  msg_11 = 9,
  msg_12 = 10,
  msg_14 = 11,
  msg_15 = 12,
  msg_16 = 13,
  msg_17 = 14,
  msg_18 = 15,
  msg_19 = 16,
  msg_20 = 17,
  msg_21 = 18,
  msg_22 = 19,
  msg_23 = 20,
  msg_24 = 21,
  msg_25 = 22,
  msg_26 = 23,
  msg_27 = 24
};

enum class MSG_LEN : std::size_t { msg_1_2_3 = 28 };

template <std::size_t msg_T>
class NMEA_primitive : std::string {
  std::array<char, msg_T> data;

 public:
  //   NMEA_primitive() = default;

  template <typename It>
  constexpr NMEA_primitive<msg_T>(It begin, It end) {
    std::copy(begin, end, std::begin(data));
  };

  // NMEA_primitive<msg_T>(const char* x) : data(std::begin(x), std::end(x){};

  //   NMEA_primitive<msg_T>(std::string x){
  //   NMEA_primitive<msg_T>(std::begin(x), std::end(x));
  //   };

  std::string to_string() const {
    return std::string(std::begin(data), std::end(data));
  };
};

// [[Rcpp::export]]
SEXP test() {
  const std::string face = "off";
    const NMEA_primitive<3> out(face.begin(), face.end());
//   std::array<char, 24> off;

//   std::copy(face.begin(), face.end(), std::begin(off));

  //   Rcpp::Rcout << out.to_string() << std::endl;

  return R_NilValue;
}

/*** R



test()



 */
