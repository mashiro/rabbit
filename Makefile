
all: test

clean:
	$(RM) -rf thirdparty test bench

rapidjson:
	svn co http://rapidjson.googlecode.com/svn/trunk/include/rapidjson thirdparty/rapidjson

picojson:
	wget https://raw.githubusercontent.com/kazuho/picojson/master/picojson.h -O thirdparty/picojson.h

test: rapidjson
	$(CXX) -I. -Ithirdparty -O2 -o test test.cpp
	./test

bench: rapidjson picojson
	$(CXX) -I. -Ithirdparty -O2 -o bench bench.cpp
	./bench 2> dev/null

