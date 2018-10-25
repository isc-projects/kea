AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES) $(SYSREPO_CPPFLAGS)

AM_CXXFLAGS = $(KEA_CXXFLAGS)

CLEANFILES = *.gcno *.gcda

sbin_PROGRAMS = to-yang from-yang

from_yang_SOURCES = from_yang.cc
from_yang_LDADD  = $(top_builddir)/src/lib/yang/libkea-yang.la
from_yang_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
from_yang_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
from_yang_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
from_yang_LDADD += $(top_builddir)/src/lib/util/threads/libkea-threads.la
from_yang_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
from_yang_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
from_yang_LDADD += $(LOG4CPLUS_LIBS) $(BOOST_LIBS) $(SYSREPO_LIBS)
from_yang_LDFLAGS = $(AM_LDFLAGS)

to_yang_SOURCES = to_yang.cc
to_yang_LDADD  = $(top_builddir)/src/lib/yang/libkea-yang.la
to_yang_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
to_yang_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
to_yang_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
to_yang_LDADD += $(top_builddir)/src/lib/util/threads/libkea-threads.la
to_yang_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
to_yang_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
to_yang_LDADD += $(LOG4CPLUS_LIBS) $(BOOST_LIBS) $(SYSREPO_LIBS)
to_yang_LDFLAGS = $(AM_LDFLAGS)
