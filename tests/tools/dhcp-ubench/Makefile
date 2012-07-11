MYSQL_CFLAGS=`mysql_config --cflags`
MYSQL_LDFLAGS=`mysql_config --libs`

all: mysql_ubench

mysql_ubench: mysql_ubench.cc
	$(CXX) $< -o mysql_ubench $(MYSQL_CFLAGS) $(MYSQL_LDFLAGS)
