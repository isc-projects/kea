MYSQL_CFLAGS=`mysql_config --cflags`
MYSQL_LDFLAGS=`mysql_config --libs`
CFLAGS=-g -O0
LDFLAGS=-lrt

SQLITE_CFLAGS=`pkg-config sqlite3 --cflags` $(LDFLAGS)
SQLITE_LDFLAGS=`pkg-config sqlite3 --libs`

all: mysql_ubench sqlite_ubench

mysql_ubench.o: mysql_ubench.cc mysql_ubench.h
	$(CXX) $< -c $(CFLAGS) $(MYSQL_CFLAGS)

benchmark.o: benchmark.cc benchmark.h
	$(CXX) $< -c $(CFLAGS) $(MYSQL_CFLAGS)

mysql_ubench: mysql_ubench.o benchmark.o
	$(CXX) $< benchmark.o -o mysql_ubench $(CFLAGS) $(MYSQL_CFLAGS) $(MYSQL_LDFLAGS)

sqlite_ubench.o: sqlite_ubench.cc sqlite_ubench.h
	$(CXX) $< -c $(CFLAGS) $(SQLLITE_CFLAGS)

sqlite_ubench: sqlite_ubench.o benchmark.o
	$(CXX) $< benchmark.o -o sqlite_ubench $(CFLAGS) $(SQLITE_CFLAGS) $(SQLITE_LDFLAGS)

clean:
	rm -f mysql_ubench sqlite_ubench *.o
