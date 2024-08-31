AM_CPPFLAGS = $(BOOST_INCLUDES)

AM_CXXFLAGS = $(KEA_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

EXTRA_DIST  =
EXTRA_DIST += check-messages.py
EXTRA_DIST += mk_cfgrpt.sh
EXTRA_DIST += path_replacer.sh

CLEANFILES = *.gcno *.gcda
DISTCLEANFILES = path_replacer.sh
