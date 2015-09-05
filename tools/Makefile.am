AM_CPPFLAGS = $(BOOST_INCLUDES)

AM_CXXFLAGS = $(KEA_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES = *.gcno *.gcda

if GENERATE_DOCS

noinst_PROGRAMS = system_messages
system_messages_SOURCES = system_messages.cc

endif
