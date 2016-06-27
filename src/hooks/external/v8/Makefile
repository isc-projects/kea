#KEASRC = /tmp/kea/src/lib

# Kea includes and boost
CPPFLAGS = -I../../.. -I$(KEASRC) -I/usr/local/include
# v8

CXXFLAGS = -DBOOST_ERROR_CODE_HEADER_ONLY -DBOOST_SYSTEM_NO_DEPRECATED
CXXFLAGS += -g -fPIC -dynamic -DNDEBUG -fwrapv
# v8
CXXFLAGS += -Wno-c++11-extensions

# Kea dhcp library
LIBS = -lkea-dhcp++ -lkea-hooks -lkea-exceptions
# v8
LIBS += -lv8_base -lv8_libbase -lv8_snapshot -lv8_libplatform -lv8

# Kea dependencies
LDFLAGS = -L/usr/local/Cellar/botan/1.10.12/lib
LDFLAGS += -L$(KEASRC)/dhcp/.libs
LDFLAGS += -L$(KEASRC)/hooks/.libs
LDFLAGS += -L$(KEASRC)/exceptions/.libs
# v8

SRCS = dso.cc globals.cc globals.h voption.h voption.cc vpkt4.h vpkt4.cc

OBJS = dso.o globals.o voption.o vpkt4.o

all: kea.so tests

kea.so: $(OBJS)
	g++ -shared $(OBJS) $(LDFLAGS) $(LIBS) -o kea.so

TESTLIBS = -lkea-dhcpsrv -lkea-dhcp++ -lkea-asiolink -lkea-cc
TESTLIBS += -lkea-hooks -lkea-log -lkea-exceptions

TESTLDFLAGS = -L/usr/local/Cellar/botan/1.10.12/lib
TESTLDFLAGS += -L$(KEASRC)/dhcpsrv/.libs
TESTLDFLAGS += -L$(KEASRC)/dhcp/.libs
TESTLDFLAGS += -L$(KEASRC)/asiolink/.libs
TESTLDFLAGS += -L$(KEASRC)/cc/.libs
TESTLDFLAGS += -L$(KEASRC)/hooks/.libs
TESTLDFLAGS += -L$(KEASRC)/log/.libs
TESTLDFLAGS += -L$(KEASRC)/exceptions/.libs

tests: tests.o
	g++ tests.o $(TESTLDFLAGS) $(TESTLIBS) -o tests

clean:
	rm -f *.o *.so tests
