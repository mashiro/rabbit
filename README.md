rabbit [![Build Status](https://cloud.drone.io/api/badges/mashiro/rabbit/status.svg)](https://cloud.drone.io/mashiro/rabbit)
======

rabbit is a very handy rapidjson wrapper library.


## dependencies

* [rapidjson](https://github.com/Tencent/rapidjson)


## how to use


### load

```cpp
std::string json = "{\"value\": 123}";

rabbit::document doc;
doc.parse(json);

int value = doc["value"].as_int();
std::cout << value << std::endl; // 123
```


### dump

```cpp
rabbit::object root;

rabbit::object user = root["user"];
user["name"] = "yui";
user["age"] = 18;

std::cout << root.str() << std::endl; // {"user":{"name":"yui","age":18}}
```


## test

* require : boost.test

```bash
mkdir build
cd build
cmake ..
make
make test
```


## benchmark

* require: [picojson](https://github.com/kazuho/picojson)

```bash
wget "http://api.reddit.com/hot" -O hot.json
g++ -I. -I./thirdparty/picojson/ -I./thirdparty/rapidjson/include/ -O2 -o bench bench.cpp
./bench 1000 2> /dev/null
```

### score

```
rapidjson time: 834330
rabbit    time: 837909
picojson  time: 3418777
```

