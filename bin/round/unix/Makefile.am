bin_PROGRAMS = round

AM_CPPFLAGS = \
	../ \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/src \
	@XML_CFLAGS@

AUTOMAKE_OPTIONS = \
        subdir-objects

round_SOURCES = \
	../round.cpp

round_LDADD = \
	../../../lib/unix/libround++.a \
	-lclink++ \
	-luhttp++ \
	@XML_LIBS@
