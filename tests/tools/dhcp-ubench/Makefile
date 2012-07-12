MYSQL_CFLAGS=`mysql_config --cflags`
MYSQL_LDFLAGS=`mysql_config --libs`
CFLAGS=-g -O0

all: mysql_ubench

mysql_ubench.o: mysql_ubench.cc mysql_ubench.h
	$(CXX) $< -c $(CFLAGS) $(MYSQL_CFLAGS)

benchmark.o: benchmark.cc benchmark.h
	$(CXX) $< -c $(CFLAGS) $(MYSQL_CFLAGS)

mysql_ubench: mysql_ubench.o benchmark.o
	$(CXX) $< benchmark.o -o mysql_ubench $(CFLAGS) $(MYSQL_CFLAGS) $(MYSQL_LDFLAGS)

clean:
	rm -f mysql_ubench *.o
