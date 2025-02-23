#ifndef MARITIME_AIS_MSGS_HPP
#define MARITIME_AIS_MSGS_HPP

#include "ais.h"
#include "maritime-typedefs.h"
#include "maritime-utils.h"

namespace maritime {
namespace ais {

template <class msg_T>
class AIS_Msgs {
 public:
  int common_row_index = 0;
  vec_int seq_out;

  const vec_chr common_field_names{//"line",
                                   "message_id", "repeat_indicator", "mmsi"};

  // vec_chr line;
  vec_int message_id;
  vec_int repeat_indicator;
  vec_int mmsi;

 public:
  AIS_Msgs(){};

  AIS_Msgs(const int n)
      :  // line(n, NA_STRING),
        message_id(n, NA_INTEGER),
        repeat_indicator(n, NA_INTEGER),
        mmsi(n, NA_INTEGER){};

  bool push(  // const std::string& line_string,
              // const std::string& body,
      const msg_T& msg) {
    const auto success = !msg.had_error();

    if (success) {
      // this->line[common_row_index] = line_string;
      this->message_id[common_row_index] = msg.message_id;
      this->repeat_indicator[common_row_index] = msg.repeat_indicator;
      this->mmsi[common_row_index] = msg.mmsi;

      this->common_row_index++;
    }

    return success;
  };

  void set_seq_out() {
    // vec_int seq_out(this->common_row_index);
    std::vector<int> seq_out(this->common_row_index);
    for (int i = 0; i < this->common_row_index; ++i) {
      seq_out[i] = i;
    }
    // std::iota(std::begin(seq_out), std::end(seq_out), 0);
    this->seq_out = seq_out;
  }

  Rcpp::List as_list() {
    this->set_seq_out();

    Rcpp::List out(common_field_names.size());
    out.attr("names") = common_field_names;

    // out["line"] = this->line[this->seq_out];
    out["message_id"] = this->message_id[this->seq_out];
    out["repeat_indicator"] = this->repeat_indicator[this->seq_out];
    out["mmsi"] = this->mmsi[this->seq_out];

    return out;
  };
};

class Msgs_1_2_3 : public AIS_Msgs<libais::Ais1_2_3> {
  const vec_chr field_names{"rot_over_range",
                            "rot",
                            "sog",
                            "position_accuracy",
                            "lng_deg",
                            "lat_deg",
                            "cog",
                            "true_heading",
                            "timestamp",
                            "special_manoeuvre",
                            "spare",
                            "raim",
                            "sync_state",
                            "slot_timeout",
                            "received_stations",
                            "slot_number",
                            "utc_hour",
                            "utc_min",
                            "utc_spare",
                            "slot_offset",
                            "slot_increment",
                            "slots_to_allocate",
                            "keep_flag"};

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
  Msgs_1_2_3(){};

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

  void push(  // const std::string& line_string,
              // const std::string& body,
      const libais::Ais1_2_3& msg) {
    const auto row_index = AIS_Msgs::common_row_index;
    const auto push_success = AIS_Msgs::push(  // line_string, body,
        msg);

    if (push_success) {
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
    }
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

  Rcpp::List as_df() {
    auto out = this->as_list();
    finalize_df(out, this->common_row_index);
    return out;
  };
};

}  // namespace ais
}  // namespace maritime

#endif
