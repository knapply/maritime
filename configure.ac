# autoconf --force --verbose
AC_PREREQ([2.69])

AC_INIT(maritime, m4_esyscmd_s([awk -e '/^Version:/ {print $2}' DESCRIPTION]))

AC_COPYRIGHT(Copyright (C) 2020 Brendan Knapp)
AC_CONFIG_SRCDIR([src])

# ALL_SOURCES="$(cd src/ && ls ../inst/include/libais/src/libais/*.cpp | grep -v ais_decode_normed | grep -v ais_py | tr '\n' ' ')"
ALL_SOURCES="$(cd src/ && ls ../inst/include/libais/src/libais/*.cpp | grep -v ais_decode_normed | grep -v ais_py | tr '\n' ' ')"
AC_SUBST(ALL_SOURCES)

AC_OUTPUT(src/Makevars)
AC_OUTPUT(src/Makevars.win)

 