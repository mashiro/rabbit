#include "rabbit.hpp"
#include <stdio.h>
#include <algorithm>

int ok_count = 0;
int ng_count = 0;

void ok(bool b, const char* file, int line, const char* msg)
{
  static int n = 0;
  const char* ret;
  if (b)
  {
    ++ok_count;
    ret = "OK";
  }
  else
  {
    ++ng_count;
    ret = "NG";
  }

  printf("%s %d - %s:%d : %s\n", ret, n++, file, line, msg);
}

template <typename A, typename B>
void is(const A& a, const B& b, const char* file, int line, const char* msg)
{
  bool ret = (a == b);
  ok(ret, file, line, msg);
}

void finish()
{
  printf("\nOK: %d, NG: %d\n", ok_count, ng_count);
}

#define OK(c) ok((c), __FUNCTION__, __LINE__, #c)
#define IS(a, b) is((a), (b), __FUNCTION__, __LINE__, #a " is " #b)

template <typename It>
inline int count(It first, It last)
{
  int n = 0;
  while (first != last)
  {
    ++n;
    ++first;
  }
  return n;
}

void type_check_test()
{
  rabbit::allocator alloc;
  rabbit::value v(alloc);

  OK(v.is<rabbit::null_t>());
  IS(v.which(), rabbit::null_t::value);

  v = false;
  OK(v.is<rabbit::false_t>());
  OK(v.is<bool>());
  IS(v.which(), rabbit::false_t::value);

  v = true;
  OK(v.is<rabbit::true_t>());
  OK(v.is<bool>());
  IS(v.which(), rabbit::true_t::value);

  v = rabbit::object_t();
  OK(v.is<rabbit::object_t>());
  OK(v.is<rabbit::object>());
  IS(v.which(), rabbit::object_t::value);

  v = rabbit::array_t();
  OK(v.is<rabbit::array_t>());
  OK(v.is<rabbit::array>());
  IS(v.which(), rabbit::array_t::value);

  v = "123";
  OK(v.is<rabbit::string_t>());
  OK(v.is<std::string>());
  IS(v.which(), rabbit::string_t::value);

  v = 123;
  OK(v.is<rabbit::number_t>());
  OK(v.is<int>());
  IS(v.which(), rabbit::number_t::value);

  v.set(rabbit::object_t());
  OK(v.is<rabbit::object_t>());

  v.set(rabbit::array_t());
  OK(v.is<rabbit::array_t>());

  rabbit::object o(alloc);
  OK(o.is<rabbit::object_t>());

  rabbit::array a(alloc);
  OK(a.is<rabbit::array_t>());
}

void swap_test()
{
  rabbit::allocator alloc;
  rabbit::value a(alloc);
  rabbit::value b(alloc);

  a = 123;
  b = "str";

  OK(a.is<int>());
  IS(a.as<int>(), 123);
  OK(b.is<std::string>());
  IS(b.as<std::string>(), "str");

  a.swap(b);

  OK(a.is<std::string>());
  IS(a.as<std::string>(), "str");
  OK(b.is<int>());
  IS(b.as<int>(), 123);
}

void object_test()
{
  rabbit::allocator alloc;
  {
    rabbit::object o(alloc);
    rabbit::object u = o["user"];
    u["name"] = "yui";
    u["age"] = 18;

    OK(o.is<rabbit::object>());
    OK(o.has("user"));
    OK(o["user"].is<rabbit::object>());
    OK(u.is<rabbit::object>());
    IS(o["user"]["name"].as<std::string>(), "yui");
    IS(o["user"]["age"].as<int>(), 18);
    IS(u["name"].as<std::string>(), "yui");
    IS(u["age"].as<int>(), 18);
  }
  {
    rabbit::object o(alloc);
    rabbit::object u(alloc);
    u.insert("name", "yui");
    u.insert("age", 18);

    //u["user"] = u; // not support operator[]
    o.insert("user", u); // u is destroyed!
    OK(u.is<rabbit::null_t>());

    OK(o.is<rabbit::object>());
    OK(o.has("user"));
    OK(o["user"].is<rabbit::object>());
    IS(o["user"]["name"].as<std::string>(), "yui");
    IS(o["user"]["age"].as<int>(), 18);
  }
  {
    rabbit::object o(alloc);
    o["a"] = 123;
    o["b"] = 1.0;
    o["c"] = "str";

    IS(count(o.begin(), o.end()), 3);
    IS(count(o.cbegin(), o.cend()), 3);
    OK(o.has("a"));
    OK(o.has("b"));
    OK(o.has("c"));
    OK(o.erase("b"));
    OK(o.has("a"));
    OK(!o.has("b"));
    OK(o.has("c"));
    IS(count(o.begin(), o.end()), 2);
    IS(count(o.cbegin(), o.cend()), 2);
    o.clear();
    OK(o.is<rabbit::object>());
    IS(count(o.begin(), o.end()), 0);
  }
}

void array_test()
{
  rabbit::allocator alloc;
  {
    rabbit::array a(alloc);
    OK(a.is<rabbit::array>());
    IS(a.size(), 0);
    a.push_back(123);
    IS(a.size(), 1);
    a.push_back(1.2);
    IS(a.size(), 2);
    a.push_back("str");
    IS(a.size(), 3);

    OK(a[0].is<int>());
    IS(a[0].as<int>(), 123);
    OK(a[1].is<double>());
    IS(a[1].as<double>(), 1.2);
    OK(a[2].is<std::string>());
    IS(a[2].as<std::string>(), "str");
    a.pop_back();
    IS(a.size(), 2);
    a.clear();
    OK(a.is<rabbit::array>());
    IS(a.size(), 0);

    IS(count(a.begin(), a.end()), 0);
    IS(count(a.cbegin(), a.cend()), 0);
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    IS(count(a.begin(), a.end()), 3);
    IS(count(a.cbegin(), a.cend()), 3);
  }
}

void parse_test()
{
  {
    rabbit::document doc;
    doc.parse("{\"value\": 123}");
    OK(doc.is<rabbit::object>());
    OK(doc.has("value"));
    IS(doc["value"].as<int>(), 123);
  }
  {
    rabbit::document doc;
    bool throw_exception = false;
    try { doc.parse("invalid json string"); } catch (...) { throw_exception = true; }
    OK(throw_exception);
  }
  {
    rabbit::allocator alloc;
    rabbit::object v(alloc);
    v["name"] = "yui";
    v["age"] = 18;
    std::string ss = v["name"].as();
    std::string s = v.str();
    rabbit::document doc;
    doc.parse(s);
    IS(v["name"].as<std::string>(), doc["name"].as<std::string>());
    IS(v["age"].as<int>(), doc["age"].as<int>());
  }
}

int main()
{
  type_check_test();
  swap_test();
  object_test();
  array_test();
  parse_test();

  finish();
}
