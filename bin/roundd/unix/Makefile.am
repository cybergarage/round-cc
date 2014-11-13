bin_PROGRAMS = fractald

AM_CPPFLAGS = \
	../ \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/src \
	@XML_CFLAGS@

fractald_SOURCES = \
	../fractald.cpp

fractald_LDADD = \
	../../../lib/unix/libfractal++.a \
	@XML_LIBS@
