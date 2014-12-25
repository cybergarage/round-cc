############################################################################
#
# Round for C++
#
############################################################################

AC_INIT([roundcc], [0.1])
AM_CONFIG_HEADER(config.h)
AC_CONFIG_AUX_DIR(config)
AC_CONFIG_SRCDIR([include/round/Round.h])
AM_INIT_AUTOMAKE

##############################
# Constants
##############################

EXPAT_VERSION=1.95
LIBXML2_VERSION=2.6.20
JANSSON_VERSION=2.6
JNI_VERSION=1.7.0
V8_VERSION=3.14
UHTTP_VERSION=0.6
CLINKCC_VERSION=2.0

##############################
# Checks for programs.
##############################

AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_RANLIB
AC_LANG_CPLUSPLUS

##############################
# Checks for header files.
##############################

AC_HEADER_STDC

##############################
# Checks for libtool.
##############################

AC_ARG_WITH(libtool,
	AS_HELP_STRING([--with-libtool],
		       [use libtool to build the library (default = yes)]),
		       [],
		       [with_libtool=yes])
AM_CONDITIONAL(HAVE_LIBTOOL, test $with_libtool = yes)

##############################
# Checks for BOOST 
##############################

#AC_CHECK_LIB([boost_system-mt],[main],,[AC_MSG_ERROR(Round for C++ needs boost::system-mt)])
#AC_CHECK_LIB([boost_filesystem-mt],[main],,[AC_MSG_ERROR(Round for C++ needs boost::filesystem-mt)])
#AC_CHECK_LIB([boost_thread-mt],[main],,[AC_MSG_ERROR(Round for C++ needs boost::thread-mt)])

##############################
# Checks for Basic Libraries
##############################

AC_CHECK_LIB([pthread],[main],,[AC_MSG_ERROR(Round for C++ needs POSIX thread library)]) 
AC_CHECK_LIB([crypto],[main],,[AC_MSG_ERROR(Round for C++ needs OpenSSL)])
AC_CHECK_LIB([edit],[main],,[AC_MSG_ERROR(Round for C++ needs libedit)])

##############################
# Checks for Expat libraries.
##############################

AC_ARG_ENABLE(expat,
        [  --enable-expat       enable Expat support [default=no]],
        [
                if test $enableval = yes; then
                        USE_EXPAT=yes
                else
                        USE_EXPAT=no
                fi
        ],[
                USE_EXPAT=no
        ]
)

if [ test $USE_EXPAT = yes ]; then
        AC_CHECK_HEADERS([expat.h],,[AC_MSG_ERROR(CyberLink needs Expat $EXPAT_VERSION later)])
        AC_CHECK_LIB([expat],[main])
        AC_DEFINE([USE_XMLPARSER_EXPAT],1,[EXPAT])
fi

##############################
# Checks for libxml2 libraries.
##############################

AC_ARG_ENABLE(libxml2,
	[  --enable-libxml2	enable Libxml2 support [default=no]],
	[
		if test $enableval = yes; then
			USE_LIBXML2=yes
		else
			USE_LIBXML2=no
		fi
	],[
		USE_LIBXML2=no
	]
)

if [ test $USE_LIBXML2 = yes ]; then
	AC_CHECK_PROG(XML2_CONFIG, xml2-config, yes, no)
	if [ test $XML2_CONFIG = yes ]; then
		AC_DEFINE([USE_XMLPARSER_LIBXML2],1,[LIBXML2])
		XML_CFLAGS=`xml2-config --cflags`
		XML_LIBS=`xml2-config --libs`
		AC_SUBST(XML_CFLAGS)
		AC_SUBST(XML_LIBS)
	else
		AC_MSG_ERROR(CyberLink needs libxml2 $LIBXML2_VERSION later)
	fi
fi

##############################
# Checks for default XML parser
##############################

if [ test $USE_LIBXML2 != yes ]; then
if [ test $USE_EXPAT != yes ]; then
	AC_CHECK_PROG(XML2_CONFIG, xml2-config, yes, no)
	if [ test $XML2_CONFIG = yes ]; then
		AC_DEFINE([USE_XMLPARSER_LIBXML2],1,[LIBXML2])
		XML_CFLAGS=`xml2-config --cflags`
		XML_LIBS=`xml2-config --libs`
		AC_SUBST(XML_CFLAGS)
		AC_SUBST(XML_LIBS)
	else
		AC_CHECK_HEADERS([expat.h],,[AC_MSG_ERROR(CyberLink needs Expat $EXPAT_VERSION later)])
		AC_CHECK_LIB([expat],[main])
		AC_DEFINE([USE_XMLPARSER_EXPAT],1,[EXPAT])
	fi
fi
fi

##############################
# Checks for Other Libraries
##############################

AC_CHECK_LIB([jansson],[main],,[AC_MSG_ERROR(Round for C++ needs Jansson $JANSSON_VERSION later)])
#AC_CHECK_LIB([jni],[main],,[AC_MSG_ERROR(Round for C++ needs JNI $JNI_VERSION later)])
AC_CHECK_LIB([v8],[main],,[AC_MSG_ERROR(Round for C++ needs V8 $V8_VERSION later)])

##############################
# Checks for Cyber Garage Libraries
##############################

AC_CHECK_LIB([uhttp++],[main],,[AC_MSG_ERROR(Round for C++ needs libuhttp++ $UHTTP_VERSION later)])
AC_CHECK_LIB([clink++],[main],,[AC_MSG_ERROR(Round for C++ needs libclink++ $CLINKCC_VERSION later)])

##############################
# Checks for other functions.
##############################

### boost::random ####
AC_MSG_CHECKING(for boost::random)
AC_TRY_COMPILE([
#include <algorithm>
#include <boost/random.hpp>
void func()
{
  boost::random::mt19937 rndEngine;
  boost::random::uniform_int_distribution<> rndDist(1, 10);
}
],
[],
[AC_MSG_RESULT(yes)
AC_DEFINE([HAVE_BOOST_RANDOM],1,[BOOST_RANDOM])],
[AC_MSG_RESULT(no)]
)

##############################
# Checks for enable options.
##############################

AC_ARG_ENABLE([tests], AC_HELP_STRING([--enable-tests], [ build tests (default = no) ]), [build_tests="yes"], [])
AM_CONDITIONAL(UNITTESTS,test "$build_tests" = yes)
if [ test "$build_tests" = yes ]; then
	AC_CHECK_LIB([boost_unit_test_framework-mt],[main],,[AC_MSG_ERROR(Round unittests need boost::unit_test_framework-mt)])
fi

##############################
# Makefiles
##############################

AC_OUTPUT([
Makefile
include/Makefile
lib/Makefile
lib/unix/Makefile
bin/Makefile
bin/round/Makefile
bin/round/unix/Makefile
bin/roundd/Makefile
bin/roundd/unix/Makefile
tests/Makefile
tests/unix/Makefile
])
