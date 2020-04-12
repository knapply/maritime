#ifndef MARITIME_MSG_18_HPP
#define MARITIME_MSG_18_HPP

#include "msg.hpp"

class Msgs_18 : public AIS_Msgs<libais::Ais18> {
  vec_int spare;
  vec_dbl sog;
  vec_int position_accuracy;
  vec_dbl lng_deg;
  vec_dbl lat_deg;
  vec_dbl cog;
  vec_int true_heading;
  vec_int timestamp;
  vec_int spare2;
  vec_int unit_flag;
  vec_int display_flag;
  vec_int dsc_flag;
  vec_int band_flag;
  vec_int m22_flag;
  vec_int mode_flag;
  vec_lgl raim;
  vec_int commstate_flag;
  vec_int slot_timeout;
  vec_int slot_offset;
  vec_int utc_hour;
  vec_int utc_min;
  vec_int utc_spare;
  vec_int slot_number;
  vec_int received_stations;
  vec_int slot_increment;
  vec_int slots_to_allocate;
  vec_int keep_flag;
  vec_int commstate_cs_fill;

 public:
  Msgs_18(const int n)
      : AIS_Msgs::AIS_Msgs(n),
        spare(n, NA_INTEGER),
        sog(n, NA_REAL),
        position_accuracy(n, NA_INTEGER),
        lng_deg(n, NA_REAL),
        lat_deg(n, NA_REAL),
        cog(n, NA_REAL),
        true_heading(n, NA_INTEGER),
        timestamp(n, NA_INTEGER),
        spare2(n, NA_INTEGER),
        unit_flag(n, NA_INTEGER),
        display_flag(n, NA_INTEGER),
        dsc_flag(n, NA_INTEGER),
        band_flag(n, NA_INTEGER),
        m22_flag(n, NA_INTEGER),
        mode_flag(n, NA_INTEGER),
        raim(n, NA_LOGICAL),
        commstate_flag(n, NA_INTEGER),
        slot_timeout(n, NA_INTEGER),
        slot_offset(n, NA_INTEGER),
        utc_hour(n, NA_INTEGER),
        utc_min(n, NA_INTEGER),
        utc_spare(n, NA_INTEGER),
        slot_number(n, NA_INTEGER),
        received_stations(n, NA_INTEGER),
        slot_increment(n, NA_INTEGER),
        slots_to_allocate(n, NA_INTEGER),
        keep_flag(n, NA_INTEGER),
        commstate_cs_fill(n, NA_INTEGER){};

  void push(libais::Ais18&& msg,
            const std::size_t _line_number,
            const double _time) {
    if (msg.had_error()) {
      return;
    }
    const auto row_index = AIS_Msgs::common_row_index;
    AIS_Msgs::init_push(msg.message_id, msg.repeat_indicator, msg.mmsi,
                        _line_number, _time);

    spare[row_index] = msg.spare;
    sog[row_index] = msg.sog;
    position_accuracy[row_index] = msg.position_accuracy;
    lng_deg[row_index] = msg.position.lng_deg;
    lat_deg[row_index] = msg.position.lat_deg;
    cog[row_index] = msg.cog;
    true_heading[row_index] = msg.true_heading;
    timestamp[row_index] = msg.timestamp;
    spare2[row_index] = msg.spare2;
    unit_flag[row_index] = msg.unit_flag;
    display_flag[row_index] = msg.display_flag;
    dsc_flag[row_index] = msg.dsc_flag;
    band_flag[row_index] = msg.band_flag;
    m22_flag[row_index] = msg.m22_flag;
    mode_flag[row_index] = msg.mode_flag;
    raim[row_index] = msg.raim;
    commstate_flag[row_index] = msg.commstate_flag;

    if (msg.slot_timeout_valid) {
      slot_timeout[row_index] = msg.slot_timeout;
    }
    if (msg.slot_offset_valid) {
      slot_offset[row_index] = msg.slot_offset;
    }
    if (msg.utc_valid) {
      utc_hour[row_index] = msg.utc_hour;
      utc_min[row_index] = msg.utc_min;
      utc_spare[row_index] = msg.utc_spare;
    }
    if (msg.slot_number_valid) {
      slot_number[row_index] = msg.slot_number;
    }
    if (msg.received_stations_valid) {
      received_stations[row_index] = msg.received_stations;
    }

    if (msg.slot_increment_valid) {
      slot_increment[row_index] = msg.slot_increment;
      slots_to_allocate[row_index] = msg.slots_to_allocate;
      keep_flag[row_index] = msg.keep_flag;
    }

    if (msg.commstate_cs_fill_valid) {
      commstate_cs_fill[row_index] = msg.commstate_cs_fill;
    }
  }

  Rcpp::List as_list() const {
    auto out = AIS_Msgs::init_as_list();
    const auto seq_out = Rcpp::seq(0, AIS_Msgs::common_row_index - 1);

    out["spare"] = spare[seq_out];
    out["sog"] = sog[seq_out];
    out["position_accuracy"] = position_accuracy[seq_out];
    out["lng_deg"] = lng_deg[seq_out];
    out["lat_deg"] = lat_deg[seq_out];
    out["cog"] = cog[seq_out];
    out["true_heading"] = true_heading[seq_out];
    out["timestamp"] = timestamp[seq_out];
    out["spare2"] = spare2[seq_out];
    out["unit_flag"] = unit_flag[seq_out];
    out["display_flag"] = display_flag[seq_out];
    out["dsc_flag"] = dsc_flag[seq_out];
    out["band_flag"] = band_flag[seq_out];
    out["m22_flag"] = m22_flag[seq_out];
    out["mode_flag"] = mode_flag[seq_out];
    out["raim"] = raim[seq_out];
    out["commstate_flag"] = commstate_flag[seq_out];
    out["slot_timeout"] = slot_timeout[seq_out];
    out["slot_offset"] = slot_offset[seq_out];
    out["utc_hour"] = utc_hour[seq_out];
    out["utc_min"] = utc_min[seq_out];
    out["utc_spare"] = utc_spare[seq_out];
    out["slot_number"] = slot_number[seq_out];
    out["received_stations"] = received_stations[seq_out];
    out["slot_increment"] = slot_increment[seq_out];
    out["slots_to_allocate"] = slots_to_allocate[seq_out];
    out["keep_flag"] = keep_flag[seq_out];
    out["commstate_cs_fill"] = commstate_cs_fill[seq_out];

    return out;
  };
};

#endif