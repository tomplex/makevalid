AC_INIT([makevalid], [0.1], [carusot42@gmail.com])

AM_INIT_AUTOMAKE

AC_PROG_CC

AC_CHECK_HEADERS([string])

AC_ARG_VAR(GEOS_CONFIG, geos-config of GEOS >3.8.0 to build against)

AC_SEARCH_LIBS([GEOSMakeValid], [geos_c], [], [
  AC_MSG_ERROR([unable to find GEOS > 3.8.0])
])

AC_CHECK_HEADER(geos_c.h,
  [],
  [AC_MSG_FAILURE([cannot find geos_c header])])

AC_CONFIG_FILES([Makefile])

AC_OUTPUT
