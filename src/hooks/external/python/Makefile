#KEASRC = /tmp/kea/src/lib

# Kea includes and boost
CPPFLAGS = -I../../.. -I$(KEASRC) -I/usr/local/include
# python
CPPFLAGS += -I/usr/local/Cellar/python3/3.5.1/Frameworks/Python.framework/Versions/3.5/include/python3.5m

CXXFLAGS = -DBOOST_ERROR_CODE_HEADER_ONLY -DBOOST_SYSTEM_NO_DEPRECATED
CXXFLAGS += -g -fPIC -dynamic -DNDEBUG -fwrapv -Wall -Wextra

# Kea dhcp library
LIBS = -lkea-dhcp++ -lkea-hooks -lkea-exceptions
# python
LIBS += -lpython3.5m -ldl -framework CoreFoundation

# Kea dependencies
LDFLAGS = -L/usr/local/Cellar/botan/1.10.12/lib
LDFLAGS += -L$(KEASRC)/dhcp/.libs
LDFLAGS += -L$(KEASRC)/hooks/.libs
LDFLAGS += -L$(KEASRC)/exceptions/.libs
# python
LDFLAGS += -L/usr/local/Cellar/python3/3.5.1/Frameworks/Python.framework/Versions/3.5/lib/python3.5/config-3.5m -lpython3.5m

SRCS = dso.cc module.h module.cc poption.h poption.cc ppkt4.h ppkt4.cc

OBJS = dso.o module.o poption.o ppkt4.o

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
