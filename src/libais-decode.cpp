#include <Rcpp.h>

#include "ais.h"
#include "decode_body.h"

#include <fstream>

enum class MSG_TYPE { msg_1_2_3, msg_4_11, msg_5 };

std::size_t count_lines(const std::string& file_path) {
  std::ifstream in_file;
  in_file.open(file_path.c_str());

  std::string line_string;
  std::size_t out = 0;
  while (std::getline(in_file, line_string)) {
    if (!line_string.empty()) {
      out++;
    }
  }
  in_file.close();

  return out;
}

template <MSG_TYPE>
SEXP decode_msg(const std::string& nmea_payload, const std::size_t pad);

template <>
SEXP decode_msg<MSG_TYPE::msg_1_2_3>(const std::string& nmea_payload,
                                     const std::size_t pad) {
  libais::Ais1_2_3 msg(nmea_payload.c_str(), pad);

  if (msg.had_error()) {
    return R_NilValue;
  }

  Rcpp::List out;

  out["nav_status"] = msg.nav_status;
  out["rot_over_range"] = msg.rot_over_range;
  out["rot"] = msg.rot;
  out["sog"] = msg.sog;
  out["position_accuracy"] = msg.position_accuracy;
  out["x"] = msg.position.lng_deg;
  out["y"] = msg.position.lat_deg;
  out["cog"] = msg.cog;
  out["true_heading"] = msg.true_heading;
  out["timestamp"] = msg.timestamp;
  out["special_manoeuvre"] = msg.special_manoeuvre;
  out["spare"] = msg.spare;
  out["raim"] = msg.raim;

  out["sync_state"] = msg.sync_state;

  // SOTDMA
  if (msg.message_id == 1 || msg.message_id == 2) {
    if (msg.slot_timeout_valid) {
      out["slot_timeout"] = msg.slot_timeout;
    }
    if (msg.received_stations_valid) {
      out["received_stations"] = msg.received_stations;
    }
    if (msg.slot_number_valid) {
      out["slot_number"] = msg.slot_number;
    }
    if (msg.utc_valid) {
      out["utc_hour"] = msg.utc_hour;
      out["utc_min"] = msg.utc_min;
      out["utc_space"] = msg.utc_spare;
    }
    if (msg.slot_offset_valid) {
      out["slot_offset"] = msg.slot_offset;
    }
  }

  // ITDMA
  if (msg.slot_increment_valid) {
    out["slot_increment"] = msg.slot_increment;
    out["slots_to_allocate"] = msg.slots_to_allocate;
    out["keep_flag"] = msg.keep_flag;
  }

  return out;
}

template <>
SEXP decode_msg<MSG_TYPE::msg_4_11>(const std::string& nmea_payload,
                                    const std::size_t pad) {
  libais::Ais4_11 msg(nmea_payload.c_str(), pad);

  if (msg.had_error()) {
    return R_NilValue;
  }

  Rcpp::List out;

  out["year"] = msg.year;
  out["month"] = msg.month;
  out["day"] = msg.day;
  out["hour"] = msg.hour;
  out["minute"] = msg.minute;
  out["second"] = msg.second;

  out["position_accuracy"] = msg.position_accuracy;
  out["x"] = msg.position.lng_deg;
  out["y"] = msg.position.lat_deg;

  out["fix_type"] = msg.fix_type;
  out["transmission_ctl"] = msg.transmission_ctl;
  out["spare"] = msg.spare;
  out["raim"] = msg.raim;
  // SOTDMA
  out["sync_state"] = msg.sync_state;
  out["slot_timeout"] = msg.slot_timeout;

  if (msg.received_stations_valid) {
    out["received_stations"] = msg.received_stations;
  }
  if (msg.slot_number_valid) {
    out["slot_number"] = msg.slot_number;
  }
  if (msg.utc_valid) {
    out["utc_hour"] = msg.utc_hour;
    out["utc_min"] = msg.utc_min;
    out["utc_spare"] = msg.utc_spare;
  }

  if (msg.slot_offset_valid) {
    out["slot_offset"] = msg.slot_offset;
  }

  return out;
}

template <>
SEXP decode_msg<MSG_TYPE::msg_5>(const std::string& nmea_payload,
                                 const std::size_t pad) {
  libais::Ais5 msg(nmea_payload.c_str(), pad);

  if (msg.had_error()) {
    return R_NilValue;
  }

  Rcpp::List out;

  out["ais_version"] = msg.ais_version;
  out["imo_num"] = msg.imo_num;
  out["callsign"] = msg.callsign;
  out["name"] = msg.name;
  out["type_and_cargo"] = msg.type_and_cargo;
  out["dim_a"] = msg.dim_a;
  out["dim_b"] = msg.dim_b;
  out["dim_c"] = msg.dim_c;
  out["dim_d"] = msg.dim_d;
  out["fix_type"] = msg.fix_type;
  out["eta_month"] = msg.eta_month;
  out["eta_day"] = msg.eta_day;
  out["eta_hour"] = msg.eta_hour;
  out["eta_minute"] = msg.eta_minute;
  out["draught"] = msg.draught;
  out["destination"] = msg.destination;
  out["dte"] = msg.dte;
  out["spare"] = msg.spare;

  return out;
}

SEXP decode_line(const char* line, const std::size_t pad = 0) {
  const auto bod = libais::GetBody(line);
  // const auto msg = libais::CreateAisMsg(bod, 0);

  // if (!msg || msg->had_error()) {
  // return R_NilValue;
  // }

  // Rcpp::Rcout << bod << std::endl;
  // Rcpp::Rcout << msg.get() << std::endl;

  switch (bod[0]) {
    case '1':  // class A position
    case '2':
    case '3':
      return decode_msg<MSG_TYPE::msg_1_2_3>(bod, pad);

    case '4':  // 4: basestation report
    case ';':  // 11: UTC date response
      return decode_msg<MSG_TYPE::msg_4_11>(bod, pad);

    case '5':  // 5: ship and cargo
      return decode_msg<MSG_TYPE::msg_5>(bod, pad);

    default:
      return R_NilValue;
  }
}

// [[Rcpp::export]]
SEXP decode_file(const std::string& file_path) {
  const auto n_lines = count_lines(file_path);

  Rcpp::List out(n_lines);

  std::ifstream in_file;
  in_file.open(file_path.c_str());
  std::string line_string;

  int i = 0;
  while (std::getline(in_file, line_string)) {
    if (line_string.empty()) {
      continue;
    }

    out[i] = decode_line(line_string.c_str());

    i++;
  }

  Rcpp::Rcout << "hooray!" << std::endl;

  return out;
}

/*** R
decode_file("inst/example-data/20181101.log")
*/