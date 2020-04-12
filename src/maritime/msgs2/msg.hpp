#ifndef MARITIME_MSG2_HPP
#define MARITIME_MSG2_HPP

#include "../../ais.h"
#include "../utils.hpp"

inline Rcpp::List init_out() {
  int i = 0;
  vec_chr names(56);
  names[i++] = "time_start";
  names[i++] = "time_end";
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
  names[i++] = "year";
  names[i++] = "month";
  names[i++] = "day";
  names[i++] = "hour";
  names[i++] = "minute";
  names[i++] = "second";
  names[i++] = "fix_type";
  names[i++] = "transmission_ctl";
  names[i++] = "ais_version";
  names[i++] = "imo_num";
  names[i++] = "callsign";
  names[i++] = "name";
  names[i++] = "type_and_cargo";
  names[i++] = "dim_a";
  names[i++] = "dim_b";
  names[i++] = "dim_c";
  names[i++] = "dim_d";
  names[i++] = "eta_month";
  names[i++] = "eta_day";
  names[i++] = "eta_hour";
  names[i++] = "eta_minute";
  names[i++] = "draught";
  names[i++] = "destination";
  names[i++] = "dte";
  names[i++] = "dest_mmsi";
  names[i++] = "seq_num";
  names[i++] = "alt";
  names[i++] = "alt_sensor";
  names[i++] = "spare2";
  names[i++] = "assigned_mode";

  Rcpp::List out(56);
  out.attr("names") = names;

//   Rcpp::Rcout << "face" << std::endl;

  return out;
}

// template <class libais_T>
class AIS_df {
 public:
  std::size_t row_index;

  vec_dbl time_start;
  vec_dbl time_end;
  vec_int message_id;
  vec_int repeat_indicator;
  vec_int mmsi;

  // 1_2_3 =====================================================================
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

  // 4_11 ================================================================
  vec_int year;
  vec_int month;
  vec_int day;
  vec_int hour;
  vec_int minute;
  vec_int second;
  //   vec_int position_accuracy;
  //   vec_dbl lng_deg;
  //   vec_dbl lat_deg;
  vec_int fix_type;
  vec_int transmission_ctl;
  //   vec_int spare;
  //   vec_lgl raim;
  //   vec_int sync_state;
  //   vec_int slot_timeout;
  //   vec_int received_stations;
  //   vec_int slot_number;
  //   vec_int utc_hour;
  //   vec_int utc_min;
  //   vec_int utc_spare;
  //   vec_int slot_offset;

  // 5 =========================================================================
  vec_int ais_version;
  vec_int imo_num;
  vec_chr callsign;
  vec_chr name;
  vec_int type_and_cargo;
  vec_int dim_a;
  vec_int dim_b;
  vec_int dim_c;
  vec_int dim_d;
  //   vec_int fix_type;
  vec_int eta_month;
  vec_int eta_day;
  vec_int eta_hour;
  vec_int eta_minute;
  vec_dbl draught;
  vec_chr destination;
  vec_int dte;
  //   vec_int spare;

  // 6 =========================================================================

  // 7_13 ======================================================================
  Rcpp::List dest_mmsi;
  Rcpp::List seq_num;

  // 8 =========================================================================

  // 9 =========================================================================
  vec_int alt;
  //   vec_int sog;
  //   vec_int position_accuracy;
  //   vec_dbl lng_deg;
  //   vec_dbl lat_deg;
  //   vec_int cog;
  //   vec_int timestamp;
  vec_int alt_sensor;
  //   vec_int spare;
  //   vec_int dte;
  vec_int spare2;
  vec_int assigned_mode;
  //   vec_lgl raim;
  //   vec_int sync_state;
  //   vec_int slot_timeout;
  //   vec_int received_stations;
  //   vec_int slot_number;
  //   vec_int utc_hour;
  //   vec_int utc_min;
  //   vec_int utc_spare;
  //   vec_int slot_offset;
  //   vec_int slot_increment;
  //   vec_int slots_to_allocate;
  //   vec_lgl keep_flag;

  // 10 ========================================================================

 public:
  explicit AIS_df(const std::size_t n)
      : row_index(0),
        time_start(n, NA_REAL),
        time_end(n, NA_REAL),
        message_id(n, NA_INTEGER),
        repeat_indicator(n, NA_INTEGER),
        mmsi(n, NA_INTEGER),
        // 1_2_3 ===============================================================
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
        keep_flag(n, NA_LOGICAL),

        // 4_11 ================================================================
        year(n, NA_INTEGER),
        month(n, NA_INTEGER),
        day(n, NA_INTEGER),
        hour(n, NA_INTEGER),
        minute(n, NA_INTEGER),
        second(n, NA_INTEGER),
        // position_accuracy(n, NA_INTEGER),
        // lng_deg(n, NA_REAL),
        // lat_deg(n, NA_REAL),
        fix_type(n, NA_INTEGER),
        transmission_ctl(n, NA_INTEGER),
        // spare(n, NA_INTEGER),
        // raim(n, NA_LOGICAL),
        // sync_state(n, NA_INTEGER),
        // slot_timeout(n, NA_INTEGER),
        // received_stations(n, NA_INTEGER),
        // slot_number(n, NA_INTEGER),
        // utc_hour(n, NA_INTEGER),
        // utc_min(n, NA_INTEGER),
        // utc_spare(n, NA_INTEGER),
        // slot_offset(n, NA_INTEGER),

        // 5 ===================================================================
        ais_version(n, NA_INTEGER),
        imo_num(n, NA_INTEGER),
        callsign(n, NA_STRING),
        name(n, NA_STRING),
        type_and_cargo(n, NA_INTEGER),
        dim_a(n, NA_INTEGER),
        dim_b(n, NA_INTEGER),
        dim_c(n, NA_INTEGER),
        dim_d(n, NA_INTEGER),
        // fix_type(n, NA_INTEGER),
        eta_month(n, NA_INTEGER),
        eta_day(n, NA_INTEGER),
        eta_hour(n, NA_INTEGER),
        eta_minute(n, NA_INTEGER),
        draught(n, NA_REAL),
        destination(n, NA_STRING),
        dte(n, NA_INTEGER),
        // spare(n, NA_INTEGER),

        // 6 ===================================================================

        // 7_13 ================================================================
        dest_mmsi(n, vec_int(1, NA_INTEGER)),
        seq_num(n, vec_int(1, NA_INTEGER)),

        // 8 ===================================================================

        // 9 ===================================================================
        alt(n, NA_INTEGER),
        // sog(n, NA_INTEGER),
        // position_accuracy(n, NA_INTEGER),
        // lng_deg(n, NA_REAL),
        // lat_deg(n, NA_REAL),
        // cog(n, NA_INTEGER),
        // timestamp(n, NA_INTEGER),
        alt_sensor(n, NA_INTEGER),
        // spare(n, NA_INTEGER),
        // dte(n, NA_INTEGER),
        spare2(n, NA_INTEGER),
        assigned_mode(n, NA_INTEGER)
//   raim(n, NA_LOGICAL),
//   sync_state(n, NA_INTEGER),
//   slot_timeout(n, NA_INTEGER),
//   received_stations(n, NA_INTEGER),
//   slot_number(n, NA_INTEGER),
//   utc_hour(n, NA_INTEGER),
//   utc_min(n, NA_INTEGER),
//   utc_spare(n, NA_INTEGER),
//   slot_offset(n, NA_INTEGER),
//   slot_increment(n, NA_INTEGER),
//   slots_to_allocate(n, NA_INTEGER),
//   keep_flag(n, NA_LOGICAL)

  // 10 ==================================================================

  {
    time_start.attr("class") = vec_chr{"POSIXct", "POSIXt"};
    time_start.attr("tzone") = "UTC";

    time_end.attr("class") = vec_chr{"POSIXct", "POSIXt"};
    time_end.attr("tzone") = "UTC";
  };

  template <class libais_T>
  void push(const libais_T&& payload,
            const double _time_start,
            const double _time_end);

  Rcpp::List as_list() const {
    const auto seq_out = Rcpp::seq(0, this->row_index - 1);
    auto out = init_out();
    // int i = 0;

    out["time_start"] = this->time_start[seq_out];
    out["time_end"] = this->time_end[seq_out];
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
    out["year"] = this->year[seq_out];
    out["month"] = this->month[seq_out];
    out["day"] = this->day[seq_out];
    out["hour"] = this->hour[seq_out];
    out["minute"] = this->minute[seq_out];
    out["second"] = this->second[seq_out];
    out["fix_type"] = this->fix_type[seq_out];
    out["transmission_ctl"] = this->transmission_ctl[seq_out];
    out["ais_version"] = this->ais_version[seq_out];
    out["imo_num"] = this->imo_num[seq_out];
    out["callsign"] = this->callsign[seq_out];
    out["name"] = this->name[seq_out];
    out["type_and_cargo"] = this->type_and_cargo[seq_out];
    out["dim_a"] = this->dim_a[seq_out];
    out["dim_b"] = this->dim_b[seq_out];
    out["dim_c"] = this->dim_c[seq_out];
    out["dim_d"] = this->dim_d[seq_out];
    out["eta_month"] = this->eta_month[seq_out];
    out["eta_day"] = this->eta_day[seq_out];
    out["eta_hour"] = this->eta_hour[seq_out];
    out["eta_minute"] = this->eta_minute[seq_out];
    out["draught"] = this->draught[seq_out];
    out["destination"] = this->destination[seq_out];
    out["dte"] = this->dte[seq_out];
    out["dest_mmsi"] = this->dest_mmsi[seq_out];
    out["seq_num"] = this->seq_num[seq_out];
    out["alt"] = this->alt[seq_out];
    out["alt_sensor"] = this->alt_sensor[seq_out];
    out["spare2"] = this->spare2[seq_out];
    out["assigned_mode"] = this->assigned_mode[seq_out];

    return out;
  };
};

template <>
inline void AIS_df::push<libais::Ais1_2_3>(const libais::Ais1_2_3&& msg,
                                           const double _time_start,
                                           const double _time_end) {
  //   Rcpp::Rcout << "1_2_3" << std::endl;
  if (msg.had_error()) {
    return;
  }

  this->time_start[this->row_index] = _time_start;
  this->time_end[this->row_index] = _time_end;
  this->message_id[this->row_index] = msg.message_id;
  this->repeat_indicator[this->row_index] = msg.repeat_indicator;
  this->mmsi[this->row_index] = msg.mmsi;

  this->nav_status[this->row_index] = msg.nav_status;
  this->rot_over_range[this->row_index] = msg.rot_over_range;
  this->rot[this->row_index] = msg.rot;
  this->sog[this->row_index] = msg.sog;
  this->position_accuracy[this->row_index] = msg.position_accuracy;
  this->lng_deg[this->row_index] = msg.position.lng_deg;
  this->lat_deg[this->row_index] = msg.position.lat_deg;
  this->cog[this->row_index] = msg.cog;
  this->true_heading[this->row_index] = msg.true_heading;
  this->timestamp[this->row_index] = msg.timestamp;
  this->special_manoeuvre[this->row_index] = msg.special_manoeuvre;
  this->spare[this->row_index] = msg.spare;
  this->raim[this->row_index] = msg.raim;

  this->sync_state[this->row_index] = msg.sync_state;

  if (msg.message_id == 1 || msg.message_id == 2) {
    this->slot_timeout[this->row_index] = msg.slot_timeout;
  }
  if (msg.received_stations_valid) {
    this->received_stations[this->row_index] = msg.received_stations;
  }
  if (msg.slot_number_valid) {
    this->slot_number[this->row_index] = msg.slot_number;
  }
  if (msg.utc_valid) {
    this->utc_hour[this->row_index] = msg.utc_hour;
    this->utc_min[this->row_index] = msg.utc_min;
    this->utc_spare[this->row_index] = msg.utc_spare;
  }
  if (msg.slot_offset_valid) {
    this->slot_offset[this->row_index] = msg.slot_offset;
  }
  if (msg.slot_increment_valid) {
    this->slot_increment[this->row_index] = msg.slot_increment;
    this->slots_to_allocate[this->row_index] = msg.slots_to_allocate;
    this->keep_flag[this->row_index] = msg.keep_flag;
  }

  this->row_index++;
}

template <>
inline void AIS_df::push<libais::Ais4_11>(const libais::Ais4_11&& msg,
                                          const double _time_start,
                                          const double _time_end) {
  //   Rcpp::Rcout << "4_11" << std::endl;
  if (msg.had_error()) {
    return;
  }

  this->year[this->row_index] = msg.year;
  this->month[this->row_index] = msg.month;
  this->day[this->row_index] = msg.day;
  this->hour[this->row_index] = msg.hour;
  this->minute[this->row_index] = msg.minute;
  this->second[this->row_index] = msg.second;
  this->position_accuracy[this->row_index] = msg.position_accuracy;
  this->lng_deg[this->row_index] = msg.position.lng_deg;
  this->lat_deg[this->row_index] = msg.position.lat_deg;
  this->fix_type[this->row_index] = msg.fix_type;
  this->transmission_ctl[this->row_index] = msg.transmission_ctl;
  this->spare[this->row_index] = msg.spare;
  this->raim[this->row_index] = msg.raim;
  this->sync_state[this->row_index] = msg.sync_state;
  this->slot_timeout[this->row_index] = msg.slot_timeout;
  if (msg.received_stations_valid) {
    this->received_stations[this->row_index] = msg.received_stations;
  }
  if (msg.slot_number_valid) {
    this->slot_number[this->row_index] = msg.slot_number;
  }
  if (msg.utc_valid) {
    this->utc_hour[this->row_index] = msg.utc_hour;
    this->utc_min[this->row_index] = msg.utc_min;
    this->utc_spare[this->row_index] = msg.utc_spare;
  }
  if (msg.slot_offset_valid) {
    this->slot_offset[this->row_index] = msg.slot_offset;
  }

  this->row_index++;
}

template <>
inline void AIS_df::push<libais::Ais5>(const libais::Ais5&& msg,
                                       const double _time_start,
                                       const double _time_end) {
  if (msg.had_error()) {
    return;
  }

  this->time_start[this->row_index] = _time_start;
  this->time_end[this->row_index] = _time_end;
  this->message_id[this->row_index] = msg.message_id;
  this->repeat_indicator[this->row_index] = msg.repeat_indicator;
  this->mmsi[this->row_index] = msg.mmsi;

  this->ais_version[this->row_index] = msg.ais_version;
  this->imo_num[this->row_index] = msg.imo_num;
  this->callsign[this->row_index] = msg.callsign;
  this->name[this->row_index] = msg.name;
  this->type_and_cargo[this->row_index] = msg.type_and_cargo;
  this->dim_a[this->row_index] = msg.dim_a;
  this->dim_b[this->row_index] = msg.dim_b;
  this->dim_c[this->row_index] = msg.dim_c;
  this->dim_d[this->row_index] = msg.dim_d;
  this->fix_type[this->row_index] = msg.fix_type;
  this->eta_month[this->row_index] = msg.eta_month;
  this->eta_day[this->row_index] = msg.eta_day;
  this->eta_hour[this->row_index] = msg.eta_hour;
  this->eta_minute[this->row_index] = msg.eta_minute;
  this->draught[this->row_index] = msg.draught;
  this->destination[this->row_index] = msg.destination;
  this->dte[this->row_index] = msg.dte;
  this->spare[this->row_index] = msg.spare;

  this->row_index++;
}

template <>
inline void AIS_df::push<libais::Ais7_13>(const libais::Ais7_13&& msg,
                                          const double _time_start,
                                          const double _time_end) {
  //   Rcpp::Rcout << "7_13" << std::endl;
  if (msg.had_error()) {
    return;
  }

  this->time_start[this->row_index] = _time_start;
  this->time_end[this->row_index] = _time_end;
  this->message_id[this->row_index] = msg.message_id;
  this->repeat_indicator[this->row_index] = msg.repeat_indicator;
  this->mmsi[this->row_index] = msg.mmsi;

  const auto n_dest_mmsi = msg.dest_mmsi.size();
  if (n_dest_mmsi > 0) {
    vec_int _dest_mmsi(n_dest_mmsi, NA_INTEGER);
    vec_int _seq_num(n_dest_mmsi, NA_INTEGER);

    for (std::size_t i = 0; i < n_dest_mmsi; ++i) {
      _dest_mmsi[i] = msg.dest_mmsi[i];
      _seq_num[i] = msg.seq_num[i];
    }

    this->dest_mmsi[this->row_index] = _dest_mmsi;
    this->seq_num[this->row_index] = _seq_num;
  }

  this->row_index++;
}

template <>
inline void AIS_df::push<libais::Ais9>(const libais::Ais9&& msg,
                                       const double _time_start,
                                       const double _time_end) {
  //   Rcpp::Rcout << "9" << std::endl;
  if (msg.had_error()) {
    return;
  }

  this->time_start[this->row_index] = _time_start;
  this->time_end[this->row_index] = _time_end;
  this->message_id[this->row_index] = msg.message_id;
  this->repeat_indicator[this->row_index] = msg.repeat_indicator;
  this->mmsi[this->row_index] = msg.mmsi;

  this->alt[this->row_index] = msg.alt;
  this->sog[this->row_index] = msg.sog;
  this->position_accuracy[this->row_index] = msg.position_accuracy;
  this->lng_deg[this->row_index] = msg.position.lng_deg;
  this->lat_deg[this->row_index] = msg.position.lat_deg;
  this->cog[this->row_index] = msg.cog;
  this->timestamp[this->row_index] = msg.timestamp;
  this->alt_sensor[this->row_index] = msg.alt_sensor;
  this->spare[this->row_index] = msg.spare;
  this->dte[this->row_index] = msg.dte;
  this->spare2[this->row_index] = msg.spare2;
  this->assigned_mode[this->row_index] = msg.assigned_mode;
  this->raim[this->row_index] = msg.raim;
  this->sync_state[this->row_index] = msg.sync_state;

  if (0 == msg.commstate_flag) {
    this->slot_timeout[this->row_index] = msg.slot_timeout;

    if (msg.received_stations_valid) {
      this->received_stations[this->row_index] = msg.received_stations;
    }
    if (msg.slot_number_valid) {
      this->slot_number[this->row_index] = msg.slot_number;
    }
    if (msg.utc_valid) {
      this->utc_hour[this->row_index] = msg.utc_hour;
      this->utc_min[this->row_index] = msg.utc_min;
      this->utc_spare[this->row_index] = msg.utc_spare;
    }
    if (msg.slot_offset_valid) {
      this->slot_offset[this->row_index] = msg.slot_offset;
    }
  } else {
    this->slot_increment[this->row_index] = msg.slot_increment;
    this->slots_to_allocate[this->row_index] = msg.slots_to_allocate;
    this->keep_flag[this->row_index] = msg.keep_flag;
  }

  this->row_index++;
}

template <>
inline void AIS_df::push<libais::Ais10>(const libais::Ais10&& msg,
                                        const double _time_start,
                                        const double _time_end) {
  //   Rcpp::Rcout << "10" << std::endl;
  if (msg.had_error()) {
    return;
  }

  this->time_start[this->row_index] = _time_start;
  this->time_end[this->row_index] = _time_end;
  this->message_id[this->row_index] = msg.message_id;
  this->repeat_indicator[this->row_index] = msg.repeat_indicator;
  this->mmsi[this->row_index] = msg.mmsi;

  this->spare[this->row_index] = msg.spare;
  this->dest_mmsi[this->row_index] = msg.dest_mmsi;
  this->spare2[this->row_index] = msg.spare2;

  this->row_index++;
}

#endif