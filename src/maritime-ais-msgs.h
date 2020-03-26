#ifndef MARITIME_AIS_MSGS_HPP
#define MARITIME_AIS_MSGS_HPP

#include "maritime.h"

namespace maritime {
namespace ais {

template <class msg_T>
class AIS_Msgs {
 public:
  int common_row_index = 0;
  vec_int seq_out;

  const vec_chr common_field_names{
      "message_id",
      "repeat_indicator",
      "mmsi",
  };

  vec_int message_id;
  vec_int repeat_indicator;
  vec_int mmsi;

 public:
  // AIS_Msgs(){};

  AIS_Msgs(const int n)
      : message_id(n, NA_INTEGER),
        repeat_indicator(n, NA_INTEGER),
        mmsi(n, NA_INTEGER){};

  bool push(const msg_T& msg) {
    const auto success = !msg.had_error();

    if (success) {
      this->message_id[common_row_index] = msg.message_id;
      this->repeat_indicator[common_row_index] = msg.repeat_indicator;
      this->mmsi[common_row_index] = msg.mmsi;

      this->common_row_index++;
    }

    return success;
  };

  void set_seq_out() {
    std::vector<int> seq_out(this->common_row_index);
    for (int i = 0; i < this->common_row_index; ++i) {
      seq_out[i] = i;
    }
    this->seq_out = seq_out;
  }

  Rcpp::List as_list() {
    this->set_seq_out();

    Rcpp::List out(common_field_names.size());
    out.attr("names") = common_field_names;

    out["message_id"] = this->message_id[this->seq_out];
    out["repeat_indicator"] = this->repeat_indicator[this->seq_out];
    out["mmsi"] = this->mmsi[this->seq_out];

    return out;
  };
};

class Msgs_1_2_3 : public AIS_Msgs<libais::Ais1_2_3> {
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
  Msgs_1_2_3(const int n)
      : AIS_Msgs::AIS_Msgs(n),
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

  static Msgs_1_2_3 from_nmea(const std::string& nmea) {
    auto out = Msgs_1_2_3(1);
    const libais::Ais1_2_3 msg(nmea.c_str(), 0);
    out.push(msg);
    return out;
  };

  void push(const libais::Ais1_2_3& msg) {
    const auto row_index = AIS_Msgs::common_row_index;
    const auto push_success = AIS_Msgs::push(msg);

    if (!push_success) {
      return;
    }

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
    this->slot_timeout[row_index] = msg.slot_timeout;
    this->received_stations[row_index] = msg.received_stations;
    this->slot_number[row_index] = msg.slot_number;
    this->utc_hour[row_index] = msg.utc_hour;
    this->utc_min[row_index] = msg.utc_min;
    this->utc_spare[row_index] = msg.utc_spare;
    this->slot_offset[row_index] = msg.slot_offset;
    this->slot_increment[row_index] = msg.slot_increment;
    this->slots_to_allocate[row_index] = msg.slots_to_allocate;
    this->keep_flag[row_index] = msg.keep_flag;
  };

  Rcpp::List as_list() {
    auto out = AIS_Msgs::as_list();

    out["rot_over_range"] = this->rot_over_range[this->seq_out];
    out["rot"] = this->rot[this->seq_out];
    out["sog"] = this->sog[this->seq_out];
    out["position_accuracy"] = this->position_accuracy[this->seq_out];
    out["lng_deg"] = this->lng_deg[this->seq_out];
    out["lat_deg"] = this->lat_deg[this->seq_out];
    out["cog"] = this->cog[this->seq_out];
    out["true_heading"] = this->true_heading[this->seq_out];
    out["timestamp"] = this->timestamp[this->seq_out];
    out["special_manoeuvre"] = this->special_manoeuvre[this->seq_out];
    out["spare"] = this->spare[this->seq_out];
    out["raim"] = this->raim[this->seq_out];
    out["sync_state"] = this->sync_state[this->seq_out];
    out["slot_timeout"] = this->slot_timeout[this->seq_out];
    out["received_stations"] = this->received_stations[this->seq_out];
    out["slot_number"] = this->slot_number[this->seq_out];
    out["utc_hour"] = this->utc_hour[this->seq_out];
    out["utc_min"] = this->utc_min[this->seq_out];
    out["utc_spare"] = this->utc_spare[this->seq_out];
    out["slot_offset"] = this->slot_offset[this->seq_out];
    out["slot_increment"] = this->slot_increment[this->seq_out];
    out["slots_to_allocate"] = this->slots_to_allocate[this->seq_out];
    out["keep_flag"] = this->keep_flag[this->seq_out];

    return out;
  };

  Rcpp::List as_df(const bool as_tibble, const bool as_sf) {
    auto out = this->as_list();
    finalize_df(out, this->seq_out, as_tibble, as_sf);
    return out;
  };
};

class Msgs_4_11 : public AIS_Msgs<libais::Ais4_11> {
  vec_int year;
  vec_int month;
  vec_int day;
  vec_int hour;
  vec_int minute;
  vec_int second;
  vec_int position_accuracy;
  vec_dbl lng_deg;
  vec_dbl lat_deg;
  vec_int fix_type;
  vec_int transmission_ctl;
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

 public:
  Msgs_4_11(const int n)
      : AIS_Msgs::AIS_Msgs(n),
        year(n, NA_INTEGER),
        month(n, NA_INTEGER),
        day(n, NA_INTEGER),
        hour(n, NA_INTEGER),
        minute(n, NA_INTEGER),
        second(n, NA_INTEGER),
        position_accuracy(n, NA_INTEGER),
        lng_deg(n, NA_REAL),
        lat_deg(n, NA_REAL),
        fix_type(n, NA_INTEGER),
        transmission_ctl(n, NA_INTEGER),
        spare(n, NA_INTEGER),
        raim(n, NA_LOGICAL),
        sync_state(n, NA_INTEGER),
        slot_timeout(n, NA_INTEGER),
        received_stations(n, NA_INTEGER),
        slot_number(n, NA_INTEGER),
        utc_hour(n, NA_INTEGER),
        utc_min(n, NA_INTEGER),
        utc_spare(n, NA_INTEGER),
        slot_offset(n, NA_INTEGER){};

  void push(const libais::Ais4_11& msg) {
    const auto row_index = AIS_Msgs::common_row_index;
    const auto push_success = AIS_Msgs::push(msg);

    if (!push_success) {
      return;
    }

    this->year[row_index] = msg.year;
    this->month[row_index] = msg.month;
    this->day[row_index] = msg.day;
    this->hour[row_index] = msg.hour;
    this->minute[row_index] = msg.minute;
    this->second[row_index] = msg.second;
    this->position_accuracy[row_index] = msg.position_accuracy;
    this->lng_deg[row_index] = msg.position.lng_deg;
    this->lat_deg[row_index] = msg.position.lat_deg;
    this->fix_type[row_index] = msg.fix_type;
    this->transmission_ctl[row_index] = msg.transmission_ctl;
    this->spare[row_index] = msg.spare;
    this->raim[row_index] = msg.raim;
    this->sync_state[row_index] = msg.sync_state;
    this->slot_timeout[row_index] = msg.slot_timeout;
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
  };

  Rcpp::List as_list() {
    auto out = AIS_Msgs::as_list();

    out["year"] = this->year[this->seq_out];
    out["month"] = this->month[this->seq_out];
    out["day"] = this->day[this->seq_out];
    out["hour"] = this->hour[this->seq_out];
    out["minute"] = this->minute[this->seq_out];
    out["second"] = this->second[this->seq_out];
    out["position_accuracy"] = this->position_accuracy[this->seq_out];
    out["lng_deg"] = this->lng_deg[this->seq_out];
    out["lat_deg"] = this->lat_deg[this->seq_out];
    out["fix_type"] = this->fix_type[this->seq_out];
    out["transmission_ctl"] = this->transmission_ctl[this->seq_out];
    out["spare"] = this->spare[this->seq_out];
    out["raim"] = this->raim[this->seq_out];
    out["sync_state"] = this->sync_state[this->seq_out];
    out["slot_timeout"] = this->slot_timeout[this->seq_out];
    out["received_stations"] = this->received_stations[this->seq_out];
    out["slot_number"] = this->slot_number[this->seq_out];
    out["utc_hour"] = this->utc_hour[this->seq_out];
    out["utc_min"] = this->utc_min[this->seq_out];
    out["utc_spare"] = this->utc_spare[this->seq_out];
    out["slot_offset"] = this->slot_offset[this->seq_out];

    return out;
  };

  Rcpp::List as_df(const bool as_tibble, const bool as_sf) {
    auto out = this->as_list();
    finalize_df(out, this->seq_out, as_tibble, as_sf);
    return out;
  };
};

}  // namespace ais
}  // namespace maritime

#endif
