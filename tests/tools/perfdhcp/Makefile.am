SUBDIRS = .

AM_CXXFLAGS = $(B10_CXXFLAGS)

AM_LDFLAGS = $(CLOCK_GETTIME_LDFLAGS)
AM_LDFLAGS += -lm
if USE_STATIC_LINK
AM_LDFLAGS += -static
endif

pkglibexec_PROGRAMS  = perfdhcp
perfdhcp_SOURCES  = perfdhcp.c
