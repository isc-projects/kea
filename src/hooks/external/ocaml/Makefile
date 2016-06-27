#KEASRC = /tmp/kea/src/lib

# Kea includes and boost
CCOPT = -ccopt -I../../.. -ccopt -I$(KEASRC) -ccopt -I/usr/local/include
CCOPT += -ccopt -DBOOST_ERROR_CODE_HEADER_ONLY
CCOPT += -ccopt -DBOOST_SYSTEM_NO_DEPRECATED
CCOPT += -ccopt -g -ccopt -fPIC -ccopt -dynamic -ccopt -Wall -ccopt -Wextra

OCAMLCC = ocamlc -cc g++ -ccopt -x -ccopt c++
BOCAMLCC = ocamlc -cc g++ -ccopt -x -ccopt c++ -ccopt -DOCAML_CODE_BYTECODE
NOCAMLCC = ocamlopt -cc g++ -ccopt -x -ccopt c++ -ccopt -DOCAML_CODE_NATIVE

# Kea dhcp library
LIBS = -lkea-dhcp++ -lkea-hooks -lkea-exceptions
# ocaml
BLIBS = $(LIBS) -lcamlrun -lcurses
NLIBS = $(LIBS) -lasmrun -lcurses

# Kea dependencies
LDFLAGS += -L/usr/local/Cellar/botan/1.10.12/lib
LDFLAGS += -L$(KEASRC)/dhcp/.libs
LDFLAGS += -L$(KEASRC)/hooks/.libs
LDFLAGS += -L$(KEASRC)/exceptions/.libs
# ocaml
LDFLAGS += -L/usr/local/lib/ocaml

SRCS = dso.c opt.h opt.c pkt4.h pkt4.c

OBJS = dso.o opt.o pkt4.o

all: bytecode native

bytecode: bhook.so btests

native: nhook.so ntests

.c.o:
	$(OCAMLCC) $(CCOPT) -verbose -c $<

hook.cmi: hook.mli
	ocamlc -c hook.mli

hook.cmo: hook.ml hook.cmi
	ocamlc -c hook.ml

hook.cmx: hook.ml hook.cmi
	ocamlopt -c hook.ml

bcamlcode.o: hook.cmo
	ocamlc -output-obj -o bcamlcode.o hook.cmo

ncamlcode.o: hook.cmx
	ocamlopt -output-obj -o ncamlcode.o hook.cmx

bhook.so: bcamlcode.o $(OBJS)
	g++ -shared bcamlcode.o $(OBJS) $(LDFLAGS) $(BLIBS) -o bhook.so

nhook.so: ncamlcode.o $(OBJS)
	g++ -shared ncamlcode.o $(OBJS) $(LDFLAGS) $(NLIBS) -o nhook.so

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

btests.o: tests.c
	$(BOCAMLCC) $(CCOPT) -verbose -c tests.c
	mv tests.o btests.o

ntests.o: tests.c
	$(NOCAMLCC) $(CCOPT) -verbose -c tests.c
	mv tests.o ntests.o

btests: btests.o
	g++ btests.o $(TESTLDFLAGS) $(TESTLIBS) -o btests

ntests: ntests.o
	g++ ntests.o $(TESTLDFLAGS) $(TESTLIBS) -o ntests

clean:
	rm -f *.[oa] *.so *.cm[ixoa] *.cmxa [bn]tests

.PHONY: all bytecode native
