top_level = [
  {
    'nmea': [ '!AIVDM,1,1,,B,181:Kjh01ewHFRPDK1s3IRcn06sd,0*08,raishub,1342569600' ],
    'result': {'cog': 87.0,
             'id': 1,
             'mmsi': 538090443,
             'nav_status': 0,
             'position_accuracy': 1,
             'raim': False,
             'repeat_indicator': 0,
             'rot': 0.0,
             'rot_over_range': False,
             'slot_timeout': 1,
             'sog': 10.899999618530273,
             'spare': 0,
             'special_manoeuvre': 0,
             'sync_state': 0,
             'timestamp': 59,
             'true_heading': 85,
             'utc_hour': 23,
             'utc_min': 59,
             'utc_spare': 0,
             'x': -8.6612,
             'y': 35.69063333333333}
  },

  {
    'nmea': [ '!AIVDM,1,1,,1,23aIk2?P0JPADNVMA`9ItOw>R0S2,0*13,raishub,1342569600' ],
    'result': {'cog': 254.5,
             'id': 2,
             'mmsi': 244740872,
             'nav_status': 15,
             'position_accuracy': 1,
             'raim': True,
             'repeat_indicator': 0,
             'rot': -731.386474609375,
             'rot_over_range': True,
             'slot_offset': 2242,
             'slot_timeout': 0,
             'sog': 2.5999999046325684,
             'spare': 0,
             'special_manoeuvre': 1,
             'sync_state': 0,
             'timestamp': 39,
             'true_heading': 511,
             'x': 3.783605,
             'y': 51.162515}
  },

  {
    'nmea': [ '!AIVDM,1,1,,B,33sOto0P08lQCKA:>143I1ms0000,0*4A,raishub,1342583221' ],
    'result': {'cog': 86.80000305175781,
             'id': 3,
             'keep_flag': False,
             'mmsi': 263716060,
             'nav_status': 0,
             'position_accuracy': 1,
             'raim': False,
             'repeat_indicator': 0,
             'rot': -731.386474609375,
             'rot_over_range': True,
             'slot_increment': 0,
             'slots_to_allocate': 0,
             'sog': 0.800000011920929,
             'spare': 0,
             'special_manoeuvre': 2,
             'sync_state': 0,
             'timestamp': 61,
             'true_heading': 58,
             'x': -160.49689333333333,
             'y': -93.98909333333333}
  },

  {
    'nmea': [ '!AIVDM,1,1,,B,4h2E3MQuiq3ILeUjqVMd@sG004IT,0*73,raishub,1342581930' ],
    'result': {'day': 18,
             'fix_type': 7,
             'hour': 3,
             'id': 4,
             'minute': 25,
             'mmsi': 2442102,
             'month': 7,
             'position_accuracy': 1,
             'raim': False,
             'repeat_indicator': 3,
             'second': 28,
             'slot_timeout': 1,
             'spare': 0,
             'sync_state': 0,
             'transmission_ctl': 0,
             'utc_hour': 3,
             'utc_min': 25,
             'utc_spare': 0,
             'x': 190.009685,
             'y': 51.88988833333333,
             'year': 2012}
  },

  {
    'nmea': [
      '!AIVDM,2,1,9,B,533uwnT00000uCCSS00MD5@Dl4h400000080001c8h<25uAn00Q1C1VRBS00,0*07,raishub,1342579715',
      '!AIVDM,2,2,9,B,00000000000,2*2E,raishub,1342579715',
    ],
    'result': {'ais_version': 1,
             'callsign': 'OT4880@',
             'destination': 'DELFZIJL@@@@@@@@@@@@',
             'dim_a': 70,
             'dim_b': 12,
             'dim_c': 2,
             'dim_d': 5,
             'draught': 0.20000000298023224,
             'dte': 0,
             'eta_day': 3,
             'eta_hour': 22,
             'eta_minute': 0,
             'eta_month': 5,
             'fix_type': 15,
             'id': 5,
             'imo_num': 0,
             'mmsi': 205488090,
             'name': 'GUATEMALA@@@@@@B@@@@',
             'repeat_indicator': 0,
             'spare': 0,
             'type_and_cargo': 107}
  },

  {
    'nmea': [
      '!AIVDM,3,1,6,A,60475rJ0BVfb04003hu<4d60P588uE:1;C;pTpHu8l5@Ttsb1LTpB1N3,0*49,raishub,1342577131',
      '!AIVDM,3,2,6,A,@nu>05B0u<4d60P588uE:184@5:S?Bo?Vo78r37?Fo;FoG0FV373c;Da,0*16,raishub,1342577131',
      '!AIVDM,3,3,6,A,=Bp,2*1D,raishub,1342577131',
    ],
    'result': {'ack_required': False,
             'dac': 1,
             'fi': 0,
             'id': 6,
             'mmsi': 4310505,
             'mmsi_dest': 538090218,
             'msg_seq': 0,
             'repeat_indicator': 0,
             'retransmit': False,
             'seq': 2,
             'spare': 0,
             'spare2': 0,
             'text': '<OSAKA HARBOUR R42>INFORMATION: WIND W 4M/S AT OSAKA HARBOUR RADAR(34-39-12N 135-25-50E) 10:25JST.'}
  },

    {
        'nmea': ['!AIVDM,1,1,,A,63m95T8uBK:0044@00P,2*7A'],
        'result': {
            'id': 6,
            'repeat_indicator': 0,
            'mmsi': 257050000,
            'seq': 2,
            'mmsi_dest': 257060000,
            'retransmit': True,
            'spare': 0,
            'dac': 1,
            'fi': 1,
            'ack_dac': 64,
            'msg_seq': 1,
            'spare2': 0}},
    {
        'nmea': ['!AIVDM,1,1,,B,65@<;:1inW@h0480J0,4*60'],
        'result': {
            'id': 6,
            'repeat_indicator': 0,
            'mmsi': 352521000,
            'seq': 0,
            'mmsi_dest': 477535500,
            'retransmit': True,
            'spare': 0,
            'dac': 1,
            'fi': 2,
            'req_dac': 1,
            'req_fi': 40}},
    {
        'nmea': ['!AIVDM,1,1,,A,601uEQ8i02s:04<0@00000000000,0*12'],
        'result': {
            'dac': 1,
            'fi': 3,
            'id': 6,
            'mmsi': 2053508,
            'mmsi_dest': 205523890,
            'repeat_indicator': 0,
            'req_dac': 1,
            'retransmit': False,
            'seq': 2,
            'spare': 0,
            'spare2': 0,
            'spare3': 0,
            'spare4': 0}},
    {
        'nmea': ['!AIVDM,1,1,,A,633krv00OEGl04@0Hb000200000000000000000000'
                 '00000000000000000,2*30'],
        'result': {
            'ack_dac': 1,
            'capabilities': [
                1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0],
            'cap_reserved': [
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0],
            'dac': 1,
            'fi': 4,
            'id': 6,
            'mmsi': 205323000,
            'mmsi_dest': 2053501,
            'repeat_indicator': 0,
            'retransmit': True,
            'seq': 0,
            'spare': 0,
            'spare2': 0,
            'spare3': 0,
            'spare4': 0,
            'spare5': 0}},
  {
    'nmea': [ '!AIVDM,1,1,,B,7l9B8LhP00PDLCvMdkg00?vD2D7w,0*3A,raishub,1342574351' ],
    'result': {'acks': [(134218245, 0),
           (474998636, 3),
           (250609727, 3),
           (620908671, 3)],
             'id': 7,
             'mmsi': 278169715,
             'repeat_indicator': 3}
  },

  {
    'nmea': [ '!AIVDM,1,1,,B,804<o3@0Bj96WSWjHlPa321i=a58GwdtwwwwwwwwwwwwwwwwwwwwwCwwwt0,2*2F,raishub,1342574307' ],
    'result': {'air_pres': 1007.0,
             'air_pres_trend': 0,
             'air_temp': -32.400001525878906,
             'cur_depth_2': 31,
             'cur_depth_3': 31,
             'cur_dir_2': 511,
             'cur_dir_3': 511,
             'cur_speed_2': 25.5,
             'cur_speed_3': 25.5,
             'dac': 1,
             'dew_point': 82.30000305175781,
             'ext_water_level': 0,
             'fi': 11,
             'horz_vis': 25.5,
             'ice': 3,
             'id': 8,
             'mmsi': 4405005,
             'precip_type': 7,
             'rel_humid': 66,
             'repeat_indicator': 0,
             'sea_state': 4,
             'spare': 0,
             'spare2': 0,
             'surf_cur_dir': 511,
             'surf_cur_speed': 25.5,
             'swell_dir': 511,
             'swell_height': 25.5,
             'swell_period': 63,
             'water_level': 41.099998474121094,
             'water_level_trend': 3,
             'water_temp': 92.30000305175781,
             'wave_dir': 511,
             'wave_height': 25.5,
             'wave_period': 63,
             'wind_ave': 12,
             'wind_dir': 113,
             'wind_gust': 16,
             'wind_gust_dir': 16,
             'x': 126.58676666666666,
             'y': 37.43836666666667}
  },

    {
        # 8:200:24 EU River Information System (RIS) Water level
        # https://github.com/schwehr/libais/issues/162
        'nmea': ['!AIVDM,1,1,,A,801tME0j60E04QJp1hhL10G20DH1,0*11'],
        'result': {
            'id': 8,
            'repeat_indicator': 0,
            'mmsi': 2039124,
            'spare': 0,
            'dac': 200,
            'fi': 24,
            'country': 'AT',
            'gauge_ids': [9, 7, 8, 5],
            'levels': [4294966528.0, 4294966528.0, 4294966528.0, 4294965760.0]}
    },

  {
    'nmea': [ '!AIVDM,1,1,,B,9oVAuAI5;rRRv2OqTi?1uoP?=a@1,0*74,raishub,1342572824' ],
    'result': {'alt': 2324,
               'alt_sensor': 0,
               'assigned_mode': 1,
               'cog': 50.29999923706055,
               'dte': 1,
               'id': 9,
               'mmsi': 509902149,
               'position_accuracy': 1,
               'raim': True,
               'repeat_indicator': 3,
               'slot_number': 5121,
               'slot_timeout': 2,
               'sog': 762,
               'spare': 3,
               'spare2': 4,
               'sync_state': 3,
               'timestamp': 30,
               'x': 35.601198333333336,
               'y': -11.22934}
  },

  {
    'nmea': [ '!AIVDM,1,1,,A,:4`bLl0p3;Qd,0*77,raishub,1342569642' ],
    'result': {'dest_mmsi': 235089435,
             'id': 10,
             'mmsi': 311074000,
             'repeat_indicator': 0,
             'spare': 0,
             'spare2': 0}
  },

  {
    'nmea': [ '!AIVDM,1,1,,A,;3P<f6iuiq00aOUu8DOD@j100000,0*44,raishub,1342569642' ],
    'result': {'day': 18,
             'fix_type': 1,
             'hour': 0,
             'id': 11,
             'minute': 0,
             'mmsi': 235089435,
             'month': 7,
             'position_accuracy': 0,
             'raim': False,
             'repeat_indicator': 0,
             'second': 41,
             'slot_offset': 0,
             'slot_timeout': 0,
             'spare': 0,
             'sync_state': 0,
             'transmission_ctl': 0,
             'x': -5.689583333333333,
             'y': 54.72972,
             'year': 2012}
  },

  {
    'nmea': [
      '!AIVDM,2,1,1,A,<02PeAPpIkF06B?=PB?31P3?>DB?<rP@<51C5P3?>D13DPB?31P3?>DB,0*13,raishub,1342580936',
      '!AIVDM,2,2,1,A,?<P?>PF86P381>>5<PoqP6?BP=1>41D?BIPB5@?BD@,4*66,raishub,1342580936',
    ],
    'result': {'dest_mmsi': 236572000,
             'id': 12,
             'mmsi': 2633030,
             'repeat_indicator': 0,
             'retransmitted': False,
             'seq_num': 0,
             'spare': 0,
             'text': 'FROM ROCA CONTROL: PLEASE CONTACT ROCA CONTROL ON VHF CHANNEL 79 FOR MANDATORY REPORT'}
  },

  {
    'nmea': [ '!AIVDM,1,1,,A,=3aDpM@pa=RmutjMeIojmgvLR0SE,0*28,raishub,1342582454' ],
    'result': {'acks': [(237581869, 1),
           (1039345517, 1),
           (662484415, 3),
           (656540213, 1)],
             'id': 13,
             'mmsi': 244660341,
             'repeat_indicator': 0}
  },

  {
    'nmea': [ '!AIVDM,1,1,,A,>>M@rl1<59B1@E=@0000000,2*0D,raishub,1342621530' ],
    'result': {'id': 14,
             'mmsi': 970210000,
             'repeat_indicator': 0,
             'spare': 0,
             'text': 'SART TEST@@@@@@@',
             'spare2': 0}
  },

  {
    'nmea': [ '!AIVDM,1,1,,B,?@0TcgRG`gmLD00000000000000,2*4F,raishub,1342570506' ],
    'result': {'dest_msg_1_2': 0,
             'id': 15,
             'mmsi': 601022,
             'mmsi_1': 636010327,
             'mmsi_2': 0,
             'msg_1_1': 5,
             'msg_2': 0,
             'repeat_indicator': 1,
             'slot_offset_1_1': 0,
             'slot_offset_1_2': 0,
             'slot_offset_2': 0,
             'spare': 0,
             'spare2': 0,
             'spare3': 0,
             'spare4': 0}
  },

  {
    'nmea': [ '!AIVDM,1,1,,B,@bQBNdhP010Fh<LMb;:GLOvJP4@d,0*7F,raishub,1342577474' ],
    'result': {'dest_mmsi_a': 134218757,
             'dest_mmsi_b': 916638301,
             'id': 16,
             'inc_a': 113,
             'inc_b': 922,
             'mmsi': 705994419,
             'offset_a': 2819,
             'offset_b': 3199,
             'repeat_indicator': 2,
             'spare': 0}
  },

  {
    'nmea': [ '!AIVDM,1,1,,A,A6WWW6gP00a3PDlEKLrarOwUr8Mg,0*03,raishub,1342580511' ],
    'result': {'id': 17,
             'mmsi': 444196634,
             'repeat_indicator': 0,
             'spare': 3,
             'spare2': 1,
             'x': -54.61333333333334,
             'y': 35.03333333333333}
  },

  {
    'nmea': [ '!AIVDM,1,1,,B,B6:VU2P0<:;2r84N5obLOwR2P0S9,0*23,raishub,1342581125' ],
    'result': {'band_flag': 1,
             'cog': 250.3000030517578,
             'commstate_flag': 0,
             'display_flag': 1,
             'dsc_flag': 0,
             'id': 18,
             'm22_flag': 0,
             'mmsi': 413771018,
             'mode_flag': 0,
             'position_accuracy': 1,
             'raim': False,
             'repeat_indicator': 0,
             'slot_offset': 2249,
             'slot_timeout': 0,
             'sog': 4.800000190734863,
             'spare': 0,
             'spare2': 0,
             'timestamp': 4,
             'true_heading': 511,
             'unit_flag': 0,
             'x': 121.49976,
             'y': 31.248843333333333}
  },

  {
    'nmea': [ '!AIVDM,1,1,,A,C7ldHCOH01nmtFP;UNuwQ6mTD2V30V:`B20000000000S0`WW320,0*27,raishub,1342581703' ],
    'result': {'assigned_mode': 0,
             'cog': 204.0,
             'dim_a': 10,
             'dim_b': 79,
             'dim_c': 14,
             'dim_d': 6,
             'dte': 0,
             'fix_type': 1,
             'id': 19,
             'mmsi': 525015117,
             'name': 'JASA SETIA@@@@@@@@@@',
             'position_accuracy': 0,
             'raim': False,
             'repeat_indicator': 0,
             'sog': 0.0,
             'spare': 246,
             'spare2': 2,
             'spare3': 0,
             'timestamp': 43,
             'true_heading': 141,
             'type_and_cargo': 70,
             'x': 103.846475,
             'y': 1.265465}
  },

  {
    'nmea': [ '!AIVDM,1,1,,B,D09RFOhupNfq6DO6DgMJ>4giK6D,2*17,raishub,1351298504' ],
    'result': {'id': 20,
               'mmsi': 9999999,
               'repeat_indicator': 0,
               'reservations': [{'incr': 750, 'num_slots': 1, 'offset': 990, 'timeout': 7},
                                {'incr': 1125, 'num_slots': 1, 'offset': 1125, 'timeout': 7},
                                {'incr': 225, 'num_slots': 5, 'offset': 759, 'timeout': 5},
                                {'incr': 1125, 'num_slots': 5, 'offset': 764, 'timeout': 5}],
               'spare': 0}
    },

  {
    'nmea': [ '!AIVDM,1,1,,B,D02E35iqlg6D,0*41' ],
    'result': {'id': 20,
                'mmsi': 2442007,
                'repeat_indicator': 0,
                'reservations': [{'incr': 1125,
                                  'num_slots': 2,
                                  'offset': 1949,
                                  'timeout': 7}],
                'spare': 0}
    },

  {
    'nmea': [ '!AIVDM,1,1,,A,D00FEd@04V0@0ET0L0,4*0E,rFakeByKurt,1351557493.0' ],
    'result': {'id': 20,
                'mmsi': 366001,
                'repeat_indicator': 0,
                'reservations': [{'incr': 4,
                                  'num_slots': 2,
                                  'offset': 1,
                                  'timeout': 3},
                                 {'incr': 7, 'num_slots': 6, 'offset': 5, 'timeout': 2}],
                'spare': 0}
    },

  {
    'nmea': [ '!AIVDM,1,1,,A,D00FEd@04V0@0ET0L0Pp0T,2*4C,rFakeByKurt,1351557873.89' ],
    'result': {'id': 20,
               'mmsi': 366001,
               'repeat_indicator': 0,
               'reservations': [{'incr': 4, 'num_slots': 2, 'offset': 1, 'timeout': 3},
                                {'incr': 7, 'num_slots': 6, 'offset': 5, 'timeout': 2},
                                {'incr': 9, 'num_slots': 3, 'offset': 8, 'timeout': 4},
                                ],
               'spare': 0}
      },


  {
    'nmea': [ '!AIVDM,1,1,,B,E>jHC:k9Wbb4;WV2@6400000000@3nCL>v8t030HHKnf00,4*1C,raishub,1332547247' ],
    'result': {'assigned_mode': False,
               'aton_status': 224,
               'aton_type': 6,
               'dim_a': 3,
               'dim_b': 3,
               'dim_c': 3,
               'dim_d': 3,
               'fix_type': 7,
               'id': 21,
               'mmsi': 992351019,
               'name': 'SOUTHWOLD LH@@@@@@@@',
               'off_pos': False,
               'position_accuracy': 1,
               'raim': False,
               'repeat_indicator': 0,
               'spare': 0,
               'timestamp': 45,
               'virtual_aton': False,
               'x': 1.6814333333333333,
               'y': 52.3272}
  },

  {
    'nmea': [ '!AIVDM,1,1,,B,F6@2lUP0<0010W@OoK8<@oPE`02`,0*03,raishub,1332549829' ],
    'result': {'chan_a': 3,
               'chan_a_bandwidth': 0,
               'chan_b': 0,
               'chan_b_bandwidth': 1,
               'dest_mmsi_1': 135504126,
               'dest_mmsi_2': 746787038,
               'id': 22,
               'mmsi': 419476630,
               'power_low': False,
               'repeat_indicator': 0,
               'spare': 0,
               'spare2': 2097320,
               'txrx_mode': 0,
               'zone_size': 3}
  },

  {
    'nmea': [ '!AIVDM,1,1,,B,G02:KpP1R`sn@291njF00000900,2*1C,raishub,1335089672' ],
    'result': {'id': 23,
               'interval_raw': 9,
               'mmsi': 2268130,
               'quiet': 0,
               'repeat_indicator': 0,
               'spare': 0,
               'spare2': 0,
               'spare3': 0,
               'station_type': 6,
               'txrx_mode': 0,
               'type_and_cargo': 0,
               'x1': 2.63,
               'x2': 1.8266666666666667,
               'y1': 51.07,
               'y2': 50.681666666666665}
    },

  {
    'nmea': [ '!AIVDM,1,1,,B,H3pro:4q3?=1B0000000000P7220,0*59,raishub,1332550009' ],
    'result': {'callsign': '@@@@@@@',
               'dim_a': 4,
               'dim_b': 7,
               'dim_c': 2,
               'dim_d': 2,
               'id': 24,
               'mmsi': 261011240,
               'part_num': 1,
               'repeat_indicator': 0,
               'spare': 0,
               'type_and_cargo': 57,
               'vendor_id': 'COMAR@@'}
  },

  {
    'nmea': [ '!AIVDM,1,1,,B,ICa:3=`700>q6o;;fgBPqqwSP>1n,0*3D,raishub,1332550366' ],
    'result': {'dest_mmsi': 29360366,
               'id': 25,
               'mmsi': 244482870,
               'repeat_indicator': 1}
  },

  {
    'nmea': [ '!AIVDM,1,1,,B,I6S`3Tg@T0a3REBEsjJcT?wSi0fM,0*02,raishub,1342654370' ],
    'result': {'dac': 905,
             'dest_mmsi': 874775184,
             'fi': 21,
             'id': 25,
             'mmsi': 440009618,
             'repeat_indicator': 0}
  },

  # TODO(schwehr): Confirm if these expected values are correct.
  {
    'nmea': [ '!AIVDM,1,1,,B,J3`gb9@P8w8CC8TMeGBU<TH>0L@u,0*24,raishub,1342588508' ],
    'result': {'id': 26,
               'mmsi': 244050469,
               'repeat_indicator': 0,
               'received_stations': 1085,
               'sync_state': 0}
               # 'slot_number': 2170,
               # 'sync_state': 1}
  },

  # TODO(schwehr): Confirm if these expected values are correct.
  {
    'nmea': [
      '!AIVDM,2,1,2,B,JfgwlGvNwts9?wUfQswQ<gv9Ow7wCl?nwv0wOi=mwd?,0*03,raishub,1342585126',
      '!AIVDM,2,2,2,B,oW8uwNg3wNS3tV,5*71,raishub,1342585126',
    ],
    'result': {'dac': 319,
               'dest_mmsi': 666891186,
               'fi': 62,
               'id': 26,
               'mmsi': 989852767,
               'repeat_indicator': 2,
               'sync_state': 2,
               'utc_hour': 16,
               'utc_min': 126,
               'utc_spare': 1}
               # 'keep_flag': False,
               # 'slot_increment': 3135,
               # 'slots_to_allocate': 1,
               # 'sync_state': 0}
  },

  {
    'nmea': [ '!AIVDM,1,1,,A,KrJN9vb@0?wl20RH,0*7A,raishub,1342653118' ],
    'result': {'cog': 38,
             'gnss': True,
             'id': 27,
             'mmsi': 698845690,
             'nav_status': 9,
             'position_accuracy': 1,
             'raim': False,
             'repeat_indicator': 3,
             'sog': 1,
             'spare': 0,
             'x': 0.105,
             'y': -2.5533333333333332}
  },

]
