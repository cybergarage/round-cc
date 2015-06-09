############################################################################
#
# Round for C++
#
############################################################################

AC_INIT([round++], [0.1])
AM_CONFIG_HEADER(config.h)
AC_CONFIG_AUX_DIR(config)
AC_CONFIG_SRCDIR([include/round/Round.h])
AM_INIT_AUTOMAKE

##############################
# Constants
##############################

BOOST_VERSION=1.46
EXPAT_VERSION=1.95
LIBXML2_VERSION=2.6.20
JANSSON_VERSION=2.2.1
JNI_VERSION=1.6.0
V8_VERSION=3.14
JS_VERSION=1.8.5
TCL_VERSION=8.5.0
LUA_VERSION=5.2.0

UHTTP_VERSION=0.6.0
MUPNPCC_VERSION=3.0.0

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

AC_CHECK_LIB([boost_system-mt],[main],,
	[AC_CHECK_LIB([boost_system],[main],,[AC_MSG_ERROR(Round for C++ needs boost::system-mt)])])

AC_CHECK_LIB([boost_filesystem-mt],[main],,
	[AC_CHECK_LIB([boost_filesystem],[main],,[AC_MSG_ERROR(Round for C++ needs boost::filesystem-mt)])])

AC_CHECK_LIB([boost_thread-mt],[main],,
	[AC_CHECK_LIB([boost_thread],[main],,[AC_MSG_ERROR(Round for C++ needs boost::thread-mt)])])

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
                        ROUND_USE_EXPAT=yes
                else
                        ROUND_USE_EXPAT=no
                fi
        ],[
                ROUND_USE_EXPAT=no
        ]
)

if [ test $ROUND_USE_EXPAT = yes ]; then
        AC_CHECK_HEADERS([expat.h],,[AC_MSG_ERROR(CyberLink needs Expat $EXPAT_VERSION later)])
        AC_CHECK_LIB([expat],[main])
        AC_DEFINE([USE_XMLPARSER_EXPAT],1,[Expat])
fi

##############################
# Checks for libxml2 libraries.
##############################

AC_ARG_ENABLE(libxml2,
	[  --enable-libxml2	enable Libxml2 support [default=no]],
	[
		if test $enableval = yes; then
			ROUND_USE_LIBXML2=yes
		else
			ROUND_USE_LIBXML2=no
		fi
	],[
		ROUND_USE_LIBXML2=no
	]
)

if [ test $ROUND_USE_LIBXML2 = yes ]; then
	AC_CHECK_PROG(XML2_CONFIG, xml2-config, yes, no)
	if [ test $XML2_CONFIG = yes ]; then
		AC_DEFINE([USE_XMLPARSER_LIBXML2],1,[libxml2])
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

if [ test $ROUND_USE_LIBXML2 != yes ]; then
if [ test $ROUND_USE_EXPAT != yes ]; then
	AC_CHECK_PROG(XML2_CONFIG, xml2-config, yes, no)
	if [ test $XML2_CONFIG = yes ]; then
		AC_DEFINE([ROUND_USE_XMLPARSER_LIBXML2],1,[libxml2])
		XML_CFLAGS=`xml2-config --cflags`
		XML_LIBS=`xml2-config --libs`
		AC_SUBST(XML_CFLAGS)
		AC_SUBST(XML_LIBS)
	else
		AC_CHECK_HEADERS([expat.h],,[AC_MSG_ERROR(CyberLink needs Expat $EXPAT_VERSION later)])
		AC_CHECK_LIB([expat],[main])
		AC_DEFINE([ROUND_USE_XMLPARSER_EXPAT],1,[Expat])
	fi
fi
fi

##############################
# Checks for script options.
##############################

# JavaScript

AC_ARG_ENABLE(
	[script-js-sm],
	[  --enable-script-js-sm    enable JavaScript support (SpiderMonkey) [default=yes]],
	[
		if test $enableval = yes; then
			ROUND_SUPPORT_JS_SM=yes
		else
			ROUND_SUPPORT_JS_SM=no
		fi
	],[
		ROUND_SUPPORT_JS_SM=yes
		ROUND_SUPPORT_JS_V8=no
	]
)
AC_ARG_ENABLE(
	[script-js-v8],
	[  --enable-script-js-v8    enable JavaScript support (V8) [default=yes]],
	[
		if test $enableval = yes; then
			ROUND_SUPPORT_JS_V8=yes
		else
			ROUND_SUPPORT_JS_V8=no
		fi
	],[]
)
if [ test $ROUND_SUPPORT_JS_SM = yes ]; then
	AC_CHECK_LIB([mozjs185],[main],,[AC_MSG_ERROR(Round for C++ needs V8 $JS_VERSION later)])
	AC_DEFINE([ROUND_SUPPORT_JS_SM],1,[SpiderMonkey])
fi
if [ test $ROUND_SUPPORT_JS_V8 = yes ]; then
	AC_CHECK_LIB([v8],[main],,[AC_MSG_ERROR(Round for C++ needs V8 $V8_VERSION later)])
	AC_DEFINE([ROUND_SUPPORT_JS_V8],1,[V8])]
fi

# Java

AC_ARG_ENABLE(
	[script-java],
	[  --enable-script-java    enable Java support [default=yes]],
	[
		if test $enableval = yes; then
			ROUND_SUPPORT_JAVA=yes
		else
			ROUND_SUPPORT_JAVA=no
		fi
	],[
		ROUND_SUPPORT_JAVA=yes
	]
)
if [ test $ROUND_SUPPORT_JAVA = yes ]; then
	AC_CHECK_HEADERS([jni.h],,[AC_MSG_ERROR(Round for C++ needs JNI $JNI_VERSION later)])
	AC_CHECK_LIB([jvm],[main],,[AC_MSG_ERROR(Round for C++ needs JNI $JNI_VERSION later)])
	AC_DEFINE([ROUND_SUPPORT_JAVA_JNI],1,[JNI])
fi

# TCL

AC_ARG_ENABLE(
	[script-tcl],
	[  --enable-script-tcl    enable Tcl support [default=yes]],
	[
		if test $enableval = yes; then
			ROUND_SUPPORT_TCL=yes
		else
			ROUND_SUPPORT_TCL=no
		fi
	],[
		ROUND_SUPPORT_TCL=yes
	]
)
if [ test $ROUND_SUPPORT_TCL = yes ]; then
AC_CHECK_HEADERS([tcl.h],,
	[AC_CHECK_HEADERS([tcl/tcl.h],,[AC_MSG_ERROR(Round for C++ needs TCL $TCL_VERSION later)])])
	AC_CHECK_LIB([tcl],[main],,[AC_MSG_ERROR(Round for C++ needs TCL $TCL_VERSION later)])
	AC_DEFINE([ROUND_SUPPORT_TCL],1,[Tcl])
fi

# Lua 

AC_ARG_ENABLE(
	[script-lua],
	[  --enable-script-lua	enable Lua support [default=yes]],
	[
		if test $enableval = yes; then
			ROUND_SUPPORT_LUA=yes
		else
			ROUND_SUPPORT_LUA=no
		fi
	],[
		ROUND_SUPPORT_LUA=no
	]
)
if [ test $ROUND_SUPPORT_LUA = yes ]; then
AC_CHECK_HEADERS([lua.h],,
	[AC_CHECK_HEADERS([lua.h],,[AC_MSG_ERROR(Round for C++ needs LUA $LUA_VERSION later)])])
	AC_CHECK_LIB([lua],[main],,[AC_MSG_ERROR(Round for C++ needs LUA $LUA_VERSION later)])
	AC_DEFINE([ROUND_SUPPORT_LUA],1,[Lua])
fi

##############################
# Checks for JSON Libraries
##############################

AC_ARG_ENABLE(
	[jansson-tcl],
	[  --enable-jansson    enable Jansson for JSON library [default=yes]],
	[
		if test $enableval = yes; then
			ROUND_USE_JSON_JANSSON=yes
		else
			ROUND_USE_JSON_JANSSON=no
		fi
	],[
		ROUND_USE_JSON_JANSSON=yes
	]
)
if [ test $ROUND_USE_JSON_JANSSON = yes ]; then
	AC_CHECK_LIB([jansson],[main],,[AC_MSG_ERROR(Round for C++ needs Jansson $JANSSON_VERSION later)])

	AC_MSG_CHECKING(json_object_foreach)
	AC_TRY_COMPILE([
	#include <jansson.h>
	void func()
	{
		json_t *jsonTDict;
		const char *jsonKey;
		json_t *jsonTObj;
		json_object_foreach(jsonTDict, jsonKey, jsonTObj) {
		}
	}
	],
	[],
	[AC_MSG_RESULT(yes)
	AC_DEFINE([ROUND_USE_JANSSON_JSON_OBJECT_FOREACH],1,[boost::random])],
	[AC_MSG_RESULT(no)]
	)

	AC_MSG_CHECKING(json_array_foreach)
	AC_TRY_COMPILE([
	#include <jansson.h>
	void func()
	{
		json_t *jsonTArray;
		size_t jsonIdx;
		json_t *jsonTObj;
		json_array_foreach(jsonTArray, jsonIdx, jsonTObj) {
		}
	}
	],
	[],
	[AC_MSG_RESULT(yes)
	AC_DEFINE([ROUND_USE_JANSSON_JSON_ARRAY_FOREACH],1,[boost::random])],
	[AC_MSG_RESULT(no)]
	)
fi

##############################
# Checks for compile
##############################

AC_MSG_CHECKING(boost::random)
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
AC_DEFINE([ROUND_HAVE_BOOST_RANDOM],1,[boost::random])],
[AC_MSG_RESULT(no)]
)

AC_MSG_CHECKING(boost::unit_test::log_level)
AC_TRY_COMPILE([
#include <boost/test/unit_test.hpp>
#include <boost/test/detail/unit_test_parameters.hpp>
void func()
{
  boost::unit_test::log_level logLevel = boost::unit_test::runtime_config::log_level();
}
],
[],
[AC_MSG_RESULT(yes)
AC_DEFINE([HAVE_BOOST_UNITTEST_LOGLEVEL],1,[boost::unit_test])],
[AC_MSG_RESULT(no)]
)

##############################
# Checks for Cyber Garage Libraries
##############################

AC_CHECK_LIB([uhttp++],[main],,[AC_MSG_ERROR(Round for C++ needs libuhttp++ $UHTTP_VERSION later)])
AC_CHECK_LIB([mupnp++],[main],,[AC_MSG_ERROR(Round for C++ needs libclink++ $MUPNPCC_VERSION later)])

##############################
# Checks for test options.
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
