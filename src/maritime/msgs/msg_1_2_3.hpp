#ifndef MARITIME_MSG_1_2_3_HPP
#define MARITIME_MSG_1_2_3_HPP

#include "msg.hpp"

// wrap
// ========================================================================================
inline SEXP ais_wrap(const libais::Ais1_2_3& msg) {
  constexpr std::size_t n = 27;
  Rcpp::List out(n);
  vec_chr names(n);

  std::size_t i = 0;
  names[i++] = "message_id";
  names[i++] = "repeat_indicator";
  names[i++] = "mmsi";
  names[i++] = "nav_status";
  names[i++] = "rot_over_range";
  names[i++] = "rot";
  names[i++] = "sog";
  names[i++] = "position_accuracy";
  names[i++] = "lng_deg";
  names[i++] = "lat_deg";
  names[i++] = "cog";
  names[i++] = "true_heading";
  names[i++] = "timestamp";
  names[i++] = "special_manoeuvre";
  names[i++] = "spare";
  names[i++] = "raim";
  names[i++] = "sync_state";
  names[i++] = "slot_timeout";
  names[i++] = "received_stations";
  names[i++] = "slot_number";
  names[i++] = "utc_hour";
  names[i++] = "utc_min";
  names[i++] = "utc_spare";
  names[i++] = "slot_offset";
  names[i++] = "slot_increment";
  names[i++] = "slots_to_allocate";
  names[i++] = "keep_flag";

  out.attr("names") = names;

  out["message_id"] = msg.message_id;
  out["repeat_indicator"] = msg.repeat_indicator;
  out["mmsi"] = msg.mmsi;
  out["nav_status"] = msg.nav_status;
  out["rot_over_range"] = msg.rot_over_range;
  out["rot"] = msg.rot;
  out["sog"] = msg.sog;
  out["position_accuracy"] = msg.position_accuracy;
  out["lng_deg"] = msg.position.lng_deg;
  out["lat_deg"] = msg.position.lat_deg;
  out["cog"] = msg.cog;
  out["true_heading"] = msg.true_heading;
  out["timestamp"] = msg.timestamp;
  out["special_manoeuvre"] = msg.special_manoeuvre;
  out["spare"] = msg.spare;
  out["raim"] = msg.raim;
  out["sync_state"] = msg.sync_state;
  out["slot_timeout"] = msg.slot_timeout;

  out["received_stations"] =
      msg.received_stations_valid ? msg.received_stations : NA_INTEGER;
  out["slot_number"] = msg.slot_number_valid ? msg.slot_number : NA_INTEGER;

  if (msg.utc_valid) {
    out["utc_hour"] = msg.utc_hour;
    out["utc_min"] = msg.utc_min;
    out["utc_spare"] = msg.utc_spare;
  } else {
    out["utc_hour"] = NA_INTEGER;
    out["utc_min"] = NA_INTEGER;
    out["utc_spare"] = NA_INTEGER;
  }

  out["slot_offset"] = msg.slot_offset_valid ? msg.slot_offset : NA_INTEGER;

  if (msg.slot_increment_valid) {
    out["slot_increment"] = msg.slot_increment;
    out["slots_to_allocate"] = msg.slots_to_allocate;
    out["keep_flag"] = msg.keep_flag;
  } else {
    out["slot_increment"] = NA_INTEGER;
    out["slots_to_allocate"] = NA_INTEGER;
    out["keep_flag"] = NA_LOGICAL;
  }

  out.attr("class") = "data.frame";
  out.attr("row.names") = "1";

  return out;
};

// Msgs_1_2_3
// ========================================================================================
class Msgs_1_2_3 : public AIS_Msgs<libais::Ais1_2_3> {
  vec_int nav_status;
  vec_lgl rot_over_range;
  vec_dbl rot;
  vec_dbl sog;
  vec_int position_accuracy;
  vec_dbl lng_deg;
  vec_dbl lat_deg;
  vec_dbl cog;
  vec_int true_heading;
  vec_int timestamp;
  vec_int special_manoeuvre;
  vec_int spare;
  vec_lgl raim;
  vec_int sync_state;
  vec_int slot_timeout;
  vec_int received_stations;
  vec_int slot_number;
  vec_int utc_hour;
  vec_int utc_min;
  vec_int utc_spare;
  vec_int slot_offset;
  vec_int slot_increment;
  vec_int slots_to_allocate;
  vec_lgl keep_flag;

 public:
  explicit Msgs_1_2_3(const int n)
      : AIS_Msgs::AIS_Msgs(n),
        nav_status(n, NA_INTEGER),
        rot_over_range(n, NA_INTEGER),
        rot(n, NA_REAL),
        sog(n, NA_REAL),
        position_accuracy(n, NA_INTEGER),
        lng_deg(n, NA_REAL),
        lat_deg(n, NA_REAL),
        cog(n, NA_REAL),
        true_heading(n, NA_INTEGER),
        timestamp(n, NA_INTEGER),
        special_manoeuvre(n, NA_INTEGER),
        spare(n, NA_INTEGER),
        raim(n, NA_LOGICAL),
        sync_state(n, NA_INTEGER),
        slot_timeout(n, NA_INTEGER),
        received_stations(n, NA_INTEGER),
        slot_number(n, NA_INTEGER),
        utc_hour(n, NA_INTEGER),
        utc_min(n, NA_INTEGER),
        utc_spare(n, NA_INTEGER),
        slot_offset(n, NA_INTEGER),
        slot_increment(n, NA_INTEGER),
        slots_to_allocate(n, NA_INTEGER),
        keep_flag(n, NA_LOGICAL){};

  void push(libais::Ais1_2_3&& msg,
            const std::size_t _line_number,
            const double _time) {
    if (msg.had_error()) {
      return;
    }
    const auto row_index = AIS_Msgs::common_row_index;
    AIS_Msgs::init_push(msg.message_id, msg.repeat_indicator, msg.mmsi,
                        _line_number, _time);

    this->nav_status[row_index] = msg.nav_status;
    this->rot_over_range[row_index] = msg.rot_over_range;
    this->rot[row_index] = msg.rot;
    this->sog[row_index] = msg.sog;
    this->position_accuracy[row_index] = msg.position_accuracy;
    this->lng_deg[row_index] = msg.position.lng_deg;
    this->lat_deg[row_index] = msg.position.lat_deg;
    this->cog[row_index] = msg.cog;
    this->true_heading[row_index] = msg.true_heading;
    this->timestamp[row_index] = msg.timestamp;
    this->special_manoeuvre[row_index] = msg.special_manoeuvre;
    this->spare[row_index] = msg.spare;
    this->raim[row_index] = msg.raim;

    this->sync_state[row_index] = msg.sync_state;

    if (msg.message_id == 1 || msg.message_id == 2) {
      this->slot_timeout[row_index] = msg.slot_timeout;
    }
    if (msg.received_stations_valid) {
      this->received_stations[row_index] = msg.received_stations;
    }
    if (msg.slot_number_valid) {
      this->slot_number[row_index] = msg.slot_number;
    }
    if (msg.utc_valid) {
      this->utc_hour[row_index] = msg.utc_hour;
      this->utc_min[row_index] = msg.utc_min;
      this->utc_spare[row_index] = msg.utc_spare;
    }
    if (msg.slot_offset_valid) {
      this->slot_offset[row_index] = msg.slot_offset;
    }
    if (msg.slot_increment_valid) {
      this->slot_increment[row_index] = msg.slot_increment;
      this->slots_to_allocate[row_index] = msg.slots_to_allocate;
      this->keep_flag[row_index] = msg.keep_flag;
    }
  };

  Rcpp::List as_list() const {
    auto out = AIS_Msgs::init_as_list();
    const auto seq_out = Rcpp::seq(0, this->common_row_index - 1);

    out["nav_status"] = this->nav_status[seq_out];
    out["rot_over_range"] = this->rot_over_range[seq_out];
    out["rot"] = this->rot[seq_out];
    out["sog"] = this->sog[seq_out];
    out["position_accuracy"] = this->position_accuracy[seq_out];
    out["lng_deg"] = this->lng_deg[seq_out];
    out["lat_deg"] = this->lat_deg[seq_out];
    out["cog"] = this->cog[seq_out];
    out["true_heading"] = this->true_heading[seq_out];
    out["timestamp"] = this->timestamp[seq_out];
    out["special_manoeuvre"] = this->special_manoeuvre[seq_out];
    out["spare"] = this->spare[seq_out];
    out["raim"] = this->raim[seq_out];
    out["sync_state"] = this->sync_state[seq_out];
    out["slot_timeout"] = this->slot_timeout[seq_out];
    out["received_stations"] = this->received_stations[seq_out];
    out["slot_number"] = this->slot_number[seq_out];
    out["utc_hour"] = this->utc_hour[seq_out];
    out["utc_min"] = this->utc_min[seq_out];
    out["utc_spare"] = this->utc_spare[seq_out];
    out["slot_offset"] = this->slot_offset[seq_out];
    out["slot_increment"] = this->slot_increment[seq_out];
    out["slots_to_allocate"] = this->slots_to_allocate[seq_out];
    out["keep_flag"] = this->keep_flag[seq_out];

    return out;
  };
};

#endif