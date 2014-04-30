rabbit [![Build Status](https://drone.io/github.com/mashiro/rabbit/status.png)](https://drone.io/github.com/mashiro/rabbit/latest)
======

rabbit is a very handy rapidjson wrapper library.


## dependencies

* [rapidjson](http://code.google.com/p/rapidjson/)


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
cmake ..
make
make test
```


## benchmark

* require: [picojson](https://github.com/kazuho/picojson)

```bash
wget "http://api.reddit.com/hot" -O hot.json
g++ -I. -O2 -o bench bench.cpp
./bench 1000 2> /dev/null
```

### score

```
30 trying...OK
rapidjson score: 370425
picojson  score: 2590521
rabbit    score: 385049
```

