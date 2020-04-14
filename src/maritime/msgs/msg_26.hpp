#ifndef MARITIME_MSG_26_HPP
#define MARITIME_MSG_26_HPP

#include "msg.hpp"

class Msgs_26 : public AIS_Msgs<libais::Ais26> {
  vec_int dest_mmsi;
  vec_int dac;
  vec_int fi;
  vec_int sync_state;
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
  Msgs_26(const int n)
      : AIS_Msgs::AIS_Msgs(n),
        dest_mmsi(n, NA_INTEGER),
        dac(n, NA_INTEGER),
        fi(n, NA_INTEGER),
        sync_state(n, NA_INTEGER),
        received_stations(n, NA_INTEGER),
        slot_number(n, NA_INTEGER),
        utc_hour(n, NA_INTEGER),
        utc_min(n, NA_INTEGER),
        utc_spare(n, NA_INTEGER),
        slot_offset(n, NA_INTEGER),
        slot_increment(n, NA_INTEGER),
        slots_to_allocate(n, NA_INTEGER),
        keep_flag(n, NA_LOGICAL){};

  void push(libais::Ais26&& msg,
            const std::size_t _line_number,
            const double _time) {
    if (msg.had_error()) {
      return;
    }
    const auto row_index = AIS_Msgs::common_row_index;
    AIS_Msgs::init_push(msg.message_id, msg.repeat_indicator, msg.mmsi,
                        _line_number, _time);

    if (msg.dest_mmsi_valid) {
      dest_mmsi[row_index] = msg.dest_mmsi;
    }
    if (msg.use_app_id) {
      dac[row_index] = msg.dac;
      fi[row_index] = msg.fi;
    }

    sync_state[row_index] = msg.sync_state;

    if (0 == msg.commstate_flag) {
      if (msg.received_stations_valid) {
        received_stations[row_index] = msg.received_stations;
      }
      if (msg.slot_number_valid) {
        slot_number[row_index] = msg.slot_number;
      }
      if (msg.utc_valid) {
        utc_hour[row_index] = msg.utc_hour;
        utc_min[row_index] = msg.utc_min;
        utc_spare[row_index] = msg.utc_spare;
      }
      if (msg.slot_offset_valid) {
        slot_offset[row_index] = msg.slot_offset;
      }
    } else {
      slot_increment[row_index] = msg.slot_increment;
      slots_to_allocate[row_index] = msg.slots_to_allocate;
      keep_flag[row_index] = msg.keep_flag;
    }
  };

  Rcpp::List as_list() const {
    auto out = AIS_Msgs::init_as_list();
    const auto seq_out = Rcpp::seq(0, AIS_Msgs::common_row_index - 1);

    out["dest_mmsi"] = dest_mmsi[seq_out];
    out["dac"] = dac[seq_out];
    out["fi"] = fi[seq_out];
    out["sync_state"] = sync_state[seq_out];
    out["received_stations"] = received_stations[seq_out];
    out["slot_number"] = slot_number[seq_out];
    out["utc_hour"] = utc_hour[seq_out];
    out["utc_min"] = utc_min[seq_out];
    out["utc_spare"] = utc_spare[seq_out];
    out["slot_offset"] = slot_offset[seq_out];
    out["slot_increment"] = slot_increment[seq_out];
    out["slots_to_allocate"] = slots_to_allocate[seq_out];
    out["keep_flag"] = keep_flag[seq_out];

    return out;
  };
};

#endif