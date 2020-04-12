#ifndef MARITIME_MSG_9_HPP
#define MARITIME_MSG_9_HPP

#include "msg.hpp"

class Msgs_9 : public AIS_Msgs<libais::Ais9> {
  vec_int alt;
  vec_int sog;
  vec_int position_accuracy;
  vec_dbl lng_deg;
  vec_dbl lat_deg;
  vec_int cog;
  vec_int timestamp;
  vec_int alt_sensor;
  vec_int spare;
  vec_int dte;
  vec_int spare2;
  vec_int assigned_mode;
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
  Msgs_9(const int n)
      : AIS_Msgs::AIS_Msgs(n),  //
        alt(n, NA_INTEGER),
        sog(n, NA_INTEGER),
        position_accuracy(n, NA_INTEGER),
        lng_deg(n, NA_REAL),
        lat_deg(n, NA_REAL),
        cog(n, NA_INTEGER),
        timestamp(n, NA_INTEGER),
        alt_sensor(n, NA_INTEGER),
        spare(n, NA_INTEGER),
        dte(n, NA_INTEGER),
        spare2(n, NA_INTEGER),
        assigned_mode(n, NA_INTEGER),
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

  void push(libais::Ais9&& msg,
            const std::size_t _line_number,
            const double _time) {
    if (msg.had_error()) {
      return;
    }
    const auto row_index = AIS_Msgs::common_row_index;
    AIS_Msgs::init_push(msg.message_id, msg.repeat_indicator, msg.mmsi,
                        _line_number, _time);

    this->alt[row_index] = msg.alt;
    this->sog[row_index] = msg.sog;
    this->position_accuracy[row_index] = msg.position_accuracy;
    this->lng_deg[row_index] = msg.position.lng_deg;
    this->lat_deg[row_index] = msg.position.lat_deg;
    this->cog[row_index] = msg.cog;
    this->timestamp[row_index] = msg.timestamp;
    this->alt_sensor[row_index] = msg.alt_sensor;
    this->spare[row_index] = msg.spare;
    this->dte[row_index] = msg.dte;
    this->spare2[row_index] = msg.spare2;
    this->assigned_mode[row_index] = msg.assigned_mode;
    this->raim[row_index] = msg.raim;
    this->sync_state[row_index] = msg.sync_state;

    if (0 == msg.commstate_flag) {
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
    } else {
      this->slot_increment[row_index] = msg.slot_increment;
      this->slots_to_allocate[row_index] = msg.slots_to_allocate;
      this->keep_flag[row_index] = msg.keep_flag;
    }

    //
  };

  Rcpp::List as_list() const {
    auto out = AIS_Msgs::init_as_list();
    const auto seq_out = Rcpp::seq(0, this->common_row_index - 1);

    out["alt"] = this->alt[seq_out];
    out["sog"] = this->sog[seq_out];
    out["position_accuracy"] = this->position_accuracy[seq_out];
    out["lng_deg"] = this->lng_deg[seq_out];
    out["lat_deg"] = this->lat_deg[seq_out];
    out["cog"] = this->cog[seq_out];
    out["timestamp"] = this->timestamp[seq_out];
    out["alt_sensor"] = this->alt_sensor[seq_out];
    out["spare"] = this->spare[seq_out];
    out["dte"] = this->dte[seq_out];
    out["spare2"] = this->spare2[seq_out];
    out["assigned_mode"] = this->assigned_mode[seq_out];
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