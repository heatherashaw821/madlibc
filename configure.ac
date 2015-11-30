#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT(MadLib, version-0.1, aaronryool@gmail.com)
AM_INIT_AUTOMAKE(pippo, 2.6)

AM_PROG_LIBTOOL([shared])
AM_ENABLE_SHARED

AC_CANONICAL_SYSTEM
AC_CANONICAL_TARGET

AC_CONFIG_SRCDIR([src/])
AC_CONFIG_HEADERS([config.h])


AC_PROG_CC
AC_LANG(C)

# Checks for header files.
AC_CHECK_HEADERS([limits.h elf.h unistd.h])


AC_PROG_RANLIB
AC_OUTPUT(Makefile src/Makefile include/Makefile doc/Makefile examples/Makefile)
