# what flags you want to pass to the C compiler & linker
ARFLAGS = rcs

# Static
lib_LIBRARIES = libmc.a
libmc_a_SOURCES = unistd.c stdlib.c stdio.c string.c signal.c time.c dict.c
libmc_a_CFLAGS  = -static -Wall -Werror -masm=intel -nodefaultlibs -nostartfiles -I$(top_srcdir)/include

# Shared
#lib_LTLIBRARIES   = libtime.la
#libtime_la_SOURCES = time.c
#libtime_la_CFLAGS  = -static -Wall -Werror -masm=intel -nodefaultlibs -nostartfiles -I$(top_srcdir)/include
