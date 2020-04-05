#ifndef MARITIME_PROTO_MSG_DFS_HPP
#define MARITIME_PROTO_MSG_DFS_HPP

#include "ais.h"
#include "utils.hpp"

//
//
//

template <class msg_T>
class AIS_Msgs {
 public:
  std::size_t common_row_index;
  vec_int time_start;
  vec_int time_end;
  vec_int message_id;
  vec_int repeat_indicator;
  vec_int mmsi;

 public:
  explicit AIS_Msgs(const std::size_t n)
      : common_row_index(0),
        time_start(n, NA_REAL),
        time_end(n, NA_REAL),
        message_id(n, NA_INTEGER),
        repeat_indicator(n, NA_INTEGER),
        mmsi(n, NA_INTEGER) {
    time_start.attr("class") = vec_chr{"POSIXct", "POSIXt"};
    time_start.attr("tzone") = "UTC";

    time_end.attr("class") = vec_chr{"POSIXct", "POSIXt"};
    time_end.attr("tzone") = "UTC";
  };

  bool init_push(const msg_T& msg,
                 const double _time_start,
                 const double _time_end) {
    const auto success = !msg.had_error();

    if (success) {
      this->time_start[common_row_index] = _time_start;
      this->time_end[common_row_index] = _time_end;
      this->message_id[common_row_index] = msg.message_id;
      this->repeat_indicator[common_row_index] = msg.repeat_indicator;
      this->mmsi[common_row_index] = msg.mmsi;

      this->common_row_index++;
    }

    return success;
  };

  Rcpp::List init_as_list() const {
    const auto seq_out = Rcpp::seq(0, this->common_row_index - 1);

    Rcpp::List out;
    out["time_start"] = this->time_start[seq_out];
    out["time_end"] = this->time_end[seq_out];
    out["message_id"] = this->message_id[seq_out];
    out["repeat_indicator"] = this->repeat_indicator[seq_out];
    out["mmsi"] = this->mmsi[seq_out];

    return out;
  };
};

// class Nest_1_2_3 : public AIS_Msgs<libais::Ais1_2_3> {
//   Rcpp::List nest;

//  public:
//   explicit Nest_1_2_3(const std::size_t n) : AIS_Msgs::AIS_Msgs(n), nest(n){};

//   void push(const libais::Ais1_2_3& msg,
//             const double _time_start,
//             const double _time_end) {
//     const auto row_index = AIS_Msgs::common_row_index;
//     const auto push_success = AIS_Msgs::init_push(msg, _time_start, _time_end);

//     if (!push_success) {
//       return;
//     }

//     Rcpp::List this_row(24, NA_INTEGER);

//     this_row[0] = msg.nav_status;
//     this_row[1] = msg.rot_over_range;
//     this_row[2] = msg.rot;
//     this_row[3] = msg.sog;
//     this_row[4] = msg.position_accuracy;
//     this_row[5] = msg.position.lng_deg;
//     this_row[6] = msg.position.lat_deg;
//     this_row[7] = msg.cog;
//     this_row[8] = msg.true_heading;
//     this_row[9] = msg.timestamp;
//     this_row[10] = msg.special_manoeuvre;
//     this_row[11] = msg.spare;
//     this_row[12] = msg.raim;
//     this_row[13] = msg.sync_state;
//     this_row[14] = msg.slot_timeout;
//     if (msg.received_stations_valid) {
//       this_row[15] = msg.received_stations;
//     }
//     if (msg.slot_number_valid) {
//       this_row[16] = msg.slot_number;
//     }
//     if (msg.utc_valid) {
//       this_row[17] = msg.utc_hour;
//       this_row[18] = msg.utc_min;
//       this_row[19] = msg.utc_spare;
//     }
//     if (msg.slot_offset_valid) {
//       this_row[20] = msg.slot_offset;
//     }
//     if (msg.slot_increment_valid) {
//       this_row[21] = msg.slot_increment;
//       this_row[22] = msg.slots_to_allocate;
//       this_row[23] = msg.keep_flag;
//     }

//     this->nest[row_index] = this_row;
//   };

//   Rcpp::List as_list() const {
//     auto out = AIS_Msgs::init_as_list();
//     const auto seq_out = Rcpp::seq(0, this->common_row_index - 1);

//     out["msg_specific_values"] = this->nest[seq_out];

//     return out;
//   };
// };

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

  void push(const libais::Ais1_2_3& msg,
            const double _time_start,
            const double _time_end) {
    const auto row_index = AIS_Msgs::common_row_index;
    const auto push_success = AIS_Msgs::init_push(msg, _time_start, _time_end);

    if (!push_success) {
      return;
    }

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

  // Rcpp::List as_nest() const {
  //   auto out = AIS_Msgs::init_as_list();
  //   // const auto seq_out = Rcpp::seq(0, this->common_row_index - 1);

  //   Rcpp::List nest(this->common_row_index);
  //   for (std::size_t i = 0; i < this->common_row_index; ++i) {
  //     Rcpp::List this_row;

  //     this_row["nav_status"] = this->nav_status[i];
  //     this_row["rot_over_range"] = this->rot_over_range[i];
  //     this_row["rot"] = this->rot[i];
  //     this_row["sog"] = this->sog[i];
  //     this_row["position_accuracy"] = this->position_accuracy[i];
  //     this_row["lng_deg"] = this->lng_deg[i];
  //     this_row["lat_deg"] = this->lat_deg[i];
  //     this_row["cog"] = this->cog[i];
  //     this_row["true_heading"] = this->true_heading[i];
  //     this_row["timestamp"] = this->timestamp[i];
  //     this_row["special_manoeuvre"] = this->special_manoeuvre[i];
  //     this_row["spare"] = this->spare[i];
  //     this_row["raim"] = this->raim[i];
  //     this_row["sync_state"] = this->sync_state[i];
  //     this_row["slot_timeout"] = this->slot_timeout[i];
  //     this_row["received_stations"] = this->received_stations[i];
  //     this_row["slot_number"] = this->slot_number[i];
  //     this_row["utc_hour"] = this->utc_hour[i];
  //     this_row["utc_min"] = this->utc_min[i];
  //     this_row["utc_spare"] = this->utc_spare[i];
  //     this_row["slot_offset"] = this->slot_offset[i];
  //     this_row["slot_increment"] = this->slot_increment[i];
  //     this_row["slots_to_allocate"] = this->slots_to_allocate[i];
  //     this_row["keep_flag"] = this->keep_flag[i];

  //     this_row.attr("class") = "data.frame";
  //     this_row.attr("row.names") = "1";

  //     nest[i] = this_row;
  //   }

  //   out["msg_specific_values"] = nest;
  //   return out;
  // }
};

//
//
// 4_11 =================================================================

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

//
//
// 5 =================================================================

class Msgs_5 : public AIS_Msgs<libais::Ais5> {
  vec_int ais_version;
  vec_int imo_num;
  vec_chr callsign;
  vec_chr name;
  vec_int type_and_cargo;
  vec_int dim_a;
  vec_int dim_b;
  vec_int dim_c;
  vec_int dim_d;
  vec_int fix_type;
  vec_int eta_month;
  vec_int eta_day;
  vec_int eta_hour;
  vec_int eta_minute;
  vec_dbl draught;
  vec_chr destination;
  vec_int dte;
  vec_int spare;

 public:
  Msgs_5(const int n)
      : AIS_Msgs::AIS_Msgs(n),
        ais_version(n, NA_INTEGER),
        imo_num(n, NA_INTEGER),
        callsign(n, NA_STRING),
        name(n, NA_STRING),
        type_and_cargo(n, NA_INTEGER),
        dim_a(n, NA_INTEGER),
        dim_b(n, NA_INTEGER),
        dim_c(n, NA_INTEGER),
        dim_d(n, NA_INTEGER),
        fix_type(n, NA_INTEGER),
        eta_month(n, NA_INTEGER),
        eta_day(n, NA_INTEGER),
        eta_hour(n, NA_INTEGER),
        eta_minute(n, NA_INTEGER),
        draught(n, NA_REAL),
        destination(n, NA_STRING),
        dte(n, NA_INTEGER),
        spare(n, NA_INTEGER){};

  void push(const libais::Ais5& msg,
            const double _time_start,
            const double _time_end) {
    const auto row_index = AIS_Msgs::common_row_index;
    const auto push_success = AIS_Msgs::init_push(msg, _time_start, _time_end);

    if (!push_success) {
      return;
    }

    this->ais_version[row_index] = msg.ais_version;
    this->imo_num[row_index] = msg.imo_num;
    this->callsign[row_index] = msg.callsign;
    this->name[row_index] = msg.name;
    this->type_and_cargo[row_index] = msg.type_and_cargo;
    this->dim_a[row_index] = msg.dim_a;
    this->dim_b[row_index] = msg.dim_b;
    this->dim_c[row_index] = msg.dim_c;
    this->dim_d[row_index] = msg.dim_d;
    this->fix_type[row_index] = msg.fix_type;
    this->eta_month[row_index] = msg.eta_month;
    this->eta_day[row_index] = msg.eta_day;
    this->eta_hour[row_index] = msg.eta_hour;
    this->eta_minute[row_index] = msg.eta_minute;
    this->draught[row_index] = msg.draught;
    this->destination[row_index] = msg.destination;
    this->dte[row_index] = msg.dte;
    this->spare[row_index] = msg.spare;
  }

  Rcpp::List as_list() const {
    auto out = AIS_Msgs::init_as_list();
    const auto seq_out = Rcpp::seq(0, this->common_row_index - 1);

    out["ais_version"] = this->ais_version[seq_out];
    out["imo_num"] = this->imo_num[seq_out];
    out["callsign"] = this->callsign[seq_out];
    out["name"] = this->name[seq_out];
    out["type_and_cargo"] = this->type_and_cargo[seq_out];
    out["dim_a"] = this->dim_a[seq_out];
    out["dim_b"] = this->dim_b[seq_out];
    out["dim_c"] = this->dim_c[seq_out];
    out["dim_d"] = this->dim_d[seq_out];
    out["fix_type"] = this->fix_type[seq_out];
    out["eta_month"] = this->eta_month[seq_out];
    out["eta_day"] = this->eta_day[seq_out];
    out["eta_hour"] = this->eta_hour[seq_out];
    out["eta_minute"] = this->eta_minute[seq_out];
    out["draught"] = this->draught[seq_out];
    out["destination"] = this->destination[seq_out];
    out["dte"] = this->dte[seq_out];
    out["spare"] = this->spare[seq_out];

    return out;
  };
};

//
//
// 6
//

//
//
// 7_13

class Msgs_7_13 : public AIS_Msgs<libais::Ais7_13> {
  Rcpp::List dest_mmsi;
  Rcpp::List seq_num;

 public:
  Msgs_7_13(const int n)
      : AIS_Msgs::AIS_Msgs(n),     //
        dest_mmsi(n, vec_int(0)),  //
        seq_num(n, vec_int(0))     //
        {};

  void push(const libais::Ais7_13& msg,
            const double _time_start,
            const double _time_end) {
    const auto row_index = AIS_Msgs::common_row_index;
    const auto push_success = AIS_Msgs::init_push(msg, _time_start, _time_end);

    if (!push_success) {
      return;
    }

    const auto n_dest_mmsi = msg.dest_mmsi.size();
    if (n_dest_mmsi > 0) {
      vec_int _dest_mmsi(n_dest_mmsi, NA_INTEGER);
      vec_int _seq_num(n_dest_mmsi, NA_INTEGER);

      for (std::size_t i = 0; i < n_dest_mmsi; ++i) {
        _dest_mmsi[i] = msg.dest_mmsi[i];
        _seq_num[i] = msg.seq_num[i];
      }

      this->dest_mmsi[row_index] = _dest_mmsi;
      this->seq_num[row_index] = _seq_num;
    }
    //
  };

  Rcpp::List as_list() const {
    auto out = AIS_Msgs::init_as_list();
    const auto seq_out = Rcpp::seq(0, this->common_row_index - 1);

    out["dest_mmsi"] = this->dest_mmsi[seq_out];
    out["seq_num"] = this->seq_num[seq_out];

    return out;
  };
};

//
//
// 8
//

//
//
// 9
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

  void push(const libais::Ais9& msg,
            const double _time_start,
            const double _time_end) {
    const auto row_index = AIS_Msgs::common_row_index;
    const auto push_success = AIS_Msgs::init_push(msg, _time_start, _time_end);

    if (!push_success) {
      return;
    }

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

//
//
// 10

class Msgs_10 : public AIS_Msgs<libais::Ais10> {
  vec_int spare;
  vec_int dest_mmsi;
  vec_int spare2;

 public:
  Msgs_10(const int n)
      : AIS_Msgs::AIS_Msgs(n),  //
        spare(n),
        dest_mmsi(n),
        spare2(n){};

  void push(const libais::Ais10& msg,
            const double _time_start,
            const double _time_end) {
    const auto row_index = AIS_Msgs::common_row_index;
    const auto push_success = AIS_Msgs::init_push(msg, _time_start, _time_end);

    if (!push_success) {
      return;
    }

    this->spare[row_index] = msg.spare;
    this->dest_mmsi[row_index] = msg.dest_mmsi;
    this->spare2[row_index] = msg.spare2;

    //
  };

  Rcpp::List as_list() const {
    auto out = AIS_Msgs::init_as_list();
    const auto seq_out = Rcpp::seq(0, this->common_row_index - 1);

    out["spare"] = this->spare[seq_out];
    out["dest_mmsi"] = this->dest_mmsi[seq_out];
    out["spare2"] = this->spare2[seq_out];

    return out;
  };
};

//
//
#endif