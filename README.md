rabbit
======

rabbit is a very handy rapidjson wrapper library.


## dependencies

* [rapidjson](http://code.google.com/p/rapidjson/)


## how to use


### deserialize

```cpp
std::string json = "{\"value\": 123}";

rabbit::document doc;
doc.parse(json);

int value = doc["value"].as();
std::cout << value << std::endl; // 123
```


### serialize

```cpp
rabbit::allocator alloc;
rabbit::object root(alloc);

rabbit::object user = root["user"];
user["name"] = "yui";
user["age"] = 18;

std::cout << root.str() << std::endl; // {"user":{"name":"yui","age":18}}
```


## test

```bash
g++ -I. -o test test.cpp
./test
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
rapidjson score: 246666
picojson score: 1883333
rabbit score: 266666
```

