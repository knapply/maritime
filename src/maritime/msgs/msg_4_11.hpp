#ifndef MARITIME_MSG_4_11_HPP
#define MARITIME_MSG_4_11_HPP

#include "msg.hpp"

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

  void push(const libais::Ais4_11& msg,
            const double _time_start,
            const double _time_end) {
    const auto row_index = AIS_Msgs::common_row_index;
    const auto push_success = AIS_Msgs::init_push(msg, _time_start, _time_end);

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

  Rcpp::List as_list() const {
    auto out = AIS_Msgs::init_as_list();
    const auto seq_out = Rcpp::seq(0, this->common_row_index - 1);

    out["year"] = this->year[seq_out];
    out["month"] = this->month[seq_out];
    out["day"] = this->day[seq_out];
    out["hour"] = this->hour[seq_out];
    out["minute"] = this->minute[seq_out];
    out["second"] = this->second[seq_out];
    out["position_accuracy"] = this->position_accuracy[seq_out];
    out["lng_deg"] = this->lng_deg[seq_out];
    out["lat_deg"] = this->lat_deg[seq_out];
    out["fix_type"] = this->fix_type[seq_out];
    out["transmission_ctl"] = this->transmission_ctl[seq_out];
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

    return out;
  };
};

#endif