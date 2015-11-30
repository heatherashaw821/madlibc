
AM_CFLAGS  = -Wall -Werror -nodefaultlibs -I$(top_srcdir)/include

bin_PROGRAMS = basic automata time random

basic_SOURCES = basic.c
basic_LDADD = ../src/libmc.a

time_SOURCES = time.c
time_LDADD = ../src/libmc.a

random_SOURCES = random.c
random_LDADD = ../src/libmc.a ../src/libtime.la

automata_SOURCES = automata.c
automata_LDADD = ../src/libmc.a

