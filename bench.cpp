#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <ctime>

#include <rapidjson/document.h>
#include <picojson.h>
#include <rabbit.hpp>

void print(int score, const std::string& title, const std::string& url)
{
  std::cerr << "(" << score << ") " << title << " - " << url << std::endl;
}

template <typename Bench>
struct runner
{
  Bench bench;
  std::string json;
  int score;
  int try_count;

  runner(const std::string& json)
    : json(json)
    , score(0)
    , try_count(0)
  {}

  void run(int n)
  {
    try
    {
      std::clock_t t = std::clock();

      while (n-- > 0)
        bench(json);

      score += (std::clock() - t);
    }
    catch (std::exception& e)
    {
      std::cout << e.what() << std::endl;
    }

    ++try_count;
  }

  void disp() const
  {
    std::cout << bench.name() << " " << "score: " << (score / try_count) << std::endl;
  }
};

struct rapidjson_bench
{
  std::string name() const { return "rapidjson"; }
  void operator()(const std::string& json) const
  {
    rapidjson::Document doc;
    if (doc.Parse<0>(json.c_str()).HasParseError())
      throw std::runtime_error("parse_error");

    const rapidjson::Value& children = doc["data"]["children"];
    for (rapidjson::Value::ConstValueIterator it = children.Begin(); it != children.End(); ++it)
    {
      const rapidjson::Value& data = (*it)["data"];
      print(data["score"].GetInt(), data["title"].GetString(), data["url"].GetString());
    }
  }
};

struct picojson_bench
{
  std::string name() const { return "picojson "; }
  void operator()(const std::string& json) const
  {
    picojson::value v;
    std::string error;
    std::string::const_iterator it = json.begin();
    picojson::parse(v, it, json.end(), &error);
    if (!error.empty())
      throw std::runtime_error(error);

    const picojson::array& children = v.get("data").get("children").get<picojson::array>();
    for (picojson::array::const_iterator it = children.begin(); it != children.end(); ++it)
    {
      const picojson::value& data = it->get("data");
      print(data.get("score").get<double>(), data.get("title").get<std::string>(), data.get("url").get<std::string>());
    }
  }
};

struct rabbit_bench
{
  std::string name() const { return "rabbit   "; }
  void operator()(const std::string& json) const
  {
    rabbit::document doc;
    try { doc.parse(json); } catch (...) { throw; }

    rabbit::const_array children = doc["data"]["children"];
    for (rabbit::array::const_iterator it = children.begin(); it != children.end(); ++it)
    {
      rabbit::const_object data = it->cat("data");
      print(data["score"].as(), data["title"].as(), data["url"].as());
    }
  }
};

int main(int argc, char** argv)
{
  int n = 1000;
  if (argc >= 2) n = std::atoi(argv[1]);

  std::ifstream ifs("hot.json");
  std::istreambuf_iterator<char> it(ifs), last;
  std::string json = std::string(it, last);

  runner<rapidjson_bench> r1(json);
  runner<picojson_bench> r2(json);
  runner<rabbit_bench> r3(json);

  int i = 1;
  while (true)
  {
    std::cout << i << " trying...";
    r1.run(n);
    r2.run(n);
    r3.run(n);
    std::cout << "OK" << std::endl;

    r1.disp();
    r2.disp();
    r3.disp();

    std::cout << "---" << std::endl;
    ++i;
  }
}

