SUBDIRS = .

AM_CXXFLAGS = $(B10_CXXFLAGS)

AM_LDFLAGS = -lm
if USE_STATIC_LINK
AM_LDFLAGS += -static
endif

if OS_LINUX
AM_LDFLAGS += -lrt
endif

pkglibexec_PROGRAMS  = perfdhcp
perfdhcp_SOURCES  = perfdhcp.c
