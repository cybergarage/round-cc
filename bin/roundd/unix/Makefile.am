bin_PROGRAMS = roundd

AM_CPPFLAGS = \
	../ \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/src \
	@XML_CFLAGS@

AUTOMAKE_OPTIONS = \
        subdir-objects

roundd_SOURCES = \
	../roundd.cpp

roundd_LDADD = \
	../../../lib/unix/libround++.a \
	-lclink++ \
	-luhttp++ \
	@XML_LIBS@
