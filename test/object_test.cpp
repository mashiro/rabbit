#define BOOST_TEST_MODULE object_test
#include <boost/test/unit_test.hpp>
#include <rabbit.hpp>
#include <map>
#include <string>

BOOST_AUTO_TEST_CASE(has_test)
{
  rabbit::value v;
  BOOST_CHECK_THROW(v.has("foo"), rabbit::type_mismatch);

  rabbit::object o;
  o["foo"] = 123;
  BOOST_CHECK(o.has("foo"));
  BOOST_CHECK(!o.has("bar"));
}

BOOST_AUTO_TEST_CASE(insert_no_copy_test)
{
  rabbit::value v;
  BOOST_CHECK_THROW(v.insert("foo", 123, false), rabbit::type_mismatch);

  rabbit::object o;
  rabbit::value s("str");
  o.insert("foo", 123, false);
  o.insert("bar", s, false);
  BOOST_CHECK(o.has("foo"));
  BOOST_CHECK(o.has("bar"));
  BOOST_CHECK(!o.has("buzz"));
}

BOOST_AUTO_TEST_CASE(insert_with_copy_test){
  rabbit::object o;
  std::map<std::string, int> key_vals;
  key_vals.insert(std::make_pair("a", 0));
  key_vals.insert(std::make_pair("b", 1));
  key_vals.insert(std::make_pair("c", 2));

  std::string tmp;
  for(std::map<std::string, int>::const_iterator itr = key_vals.begin(), end = key_vals.end(); itr != end; ++itr){
    tmp = itr->first + "-test";
    o.insert(tmp, itr->second, true);
  }

  BOOST_CHECK(o.size() == 3);
  BOOST_CHECK(o.has("a-test"));
  BOOST_CHECK(o.has("b-test"));
  BOOST_CHECK(o.has("c-test"));
  BOOST_CHECK(o["a-test"].is_int());
  BOOST_CHECK(o["a-test"].as_int() == 0);
  BOOST_CHECK(o["b-test"].is_int());
  BOOST_CHECK(o["b-test"].as_int() == 1);
  BOOST_CHECK(o["c-test"].is_int());
  BOOST_CHECK(o["c-test"].as_int() == 2);
}


BOOST_AUTO_TEST_CASE(op_bracket_with_copy_test){
  rabbit::object o;
  std::map<std::string, int> key_vals;
  key_vals.insert(std::make_pair("a", 0));
  key_vals.insert(std::make_pair("b", 1));
  key_vals.insert(std::make_pair("c", 2));

  std::string tmp;
  for(std::map<std::string, int>::const_iterator itr = key_vals.begin(), end = key_vals.end(); itr != end; ++itr){
    tmp = itr->first + "-test";
    o[tmp] = itr->second;
  }

  BOOST_CHECK(o.size() == 3);
  BOOST_CHECK(o.has("a-test"));
  BOOST_CHECK(o.has("b-test"));
  BOOST_CHECK(o.has("c-test"));
  BOOST_CHECK(o["a-test"].is_int());
  BOOST_CHECK(o["a-test"].as_int() == 0);
  BOOST_CHECK(o["b-test"].is_int());
  BOOST_CHECK(o["b-test"].as_int() == 1);
  BOOST_CHECK(o["c-test"].is_int());
  BOOST_CHECK(o["c-test"].as_int() == 2);
}



BOOST_AUTO_TEST_CASE(erase_test)
{
  rabbit::value v;
  BOOST_CHECK_THROW(v.erase("foo"), rabbit::type_mismatch);

  rabbit::object o;
  o["foo"] = 123;
  BOOST_CHECK(o.has("foo"));
  BOOST_CHECK(o.erase("foo"));
  BOOST_CHECK(!o.has("foo"));
  BOOST_CHECK(!o.erase("foo"));
}

BOOST_AUTO_TEST_CASE(erase_itr)
{
  rabbit::value v;
  BOOST_CHECK_THROW(v.erase("foo"), rabbit::type_mismatch);

  rabbit::object o;
  o["foo"] = 123;
  BOOST_CHECK(o.has("foo"));
  rabbit::object::member_iterator itr = o.erase(o.begin());
  BOOST_CHECK(!o.has("foo"));
  BOOST_CHECK(!o.erase("foo"));
  BOOST_CHECK(itr == o.end());
}

BOOST_AUTO_TEST_CASE(erase_const_itr)
{
  rabbit::value v;
  BOOST_CHECK_THROW(v.erase("foo"), rabbit::type_mismatch);

  rabbit::object o;
  o["foo"] = 123;
  BOOST_CHECK(o.has("foo"));
  rabbit::object::const_member_iterator itr = o.erase(o.cbegin());
  BOOST_CHECK(!o.has("foo"));
  BOOST_CHECK(!o.erase("foo"));
  BOOST_CHECK(itr == o.end());
}

BOOST_AUTO_TEST_CASE(at_test)
{
  rabbit::object o;
  rabbit::value v("str");
  o["foo"] = 123;
  o["bar"] = v;
  BOOST_CHECK(o.at("foo").as_int() == 123);
  BOOST_CHECK(o.at("bar").as_string() == "str");
  BOOST_CHECK(o.at("buzz").is_null());

  rabbit::const_object co;
  BOOST_CHECK_THROW(co.at("foo"), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(iterator_test)
{
  rabbit::object o;
  o["int"] = 123;
  o["double"] = 1.0;
  o["string"] = "str";
  rabbit::object o2 = o["object"];
  o2["value"] = 123;

  typedef rabbit::object::iterator iter_t;
  for (iter_t it = o.begin(); it != o.end(); ++it)
  {
    if      (it->name() == "int") BOOST_CHECK_EQUAL(it->value().as_int(), 123);
    else if (it->name() == "double") BOOST_CHECK_CLOSE(it->value().as_double(), 1.0, 0.000001);
    else if (it->name() == "string") BOOST_CHECK_EQUAL(it->value().as_string(), "str");
    else if (it->name() == "object")
    {
      BOOST_CHECK(it->value().is_object());
      BOOST_CHECK_EQUAL(it->value().at("value").as_int(), 123);
      it->value().at("value") = "str";
      BOOST_CHECK_EQUAL(it->value().at("value").as_string(), "str");
    }
    else BOOST_ERROR("unknown member");
  }
}

BOOST_AUTO_TEST_CASE(const_iterator_test)
{
  rabbit::object o;
  o["int"] = 123;
  o["double"] = 1.0;
  o["string"] = "str";
  rabbit::object o2 = o["object"];
  o2["value"] = 123;

  typedef rabbit::object::const_iterator iter_t;
  for (iter_t it = o.cbegin(); it != o.cend(); ++it)
  {
    if      (it->name() == "int") BOOST_CHECK_EQUAL(it->value().as_int(), 123);
    else if (it->name() == "double") BOOST_CHECK_CLOSE(it->value().as_double(), 1.0, 0.000001);
    else if (it->name() == "string") BOOST_CHECK_EQUAL(it->value().as_string(), "str");
    else if (it->name() == "object")
    {
      BOOST_CHECK(it->value().is_object());
      BOOST_CHECK_EQUAL(it->value().at("value").as_int(), 123);
      // it->value().at("value") = "str"; // ERROR!
    }
    else BOOST_ERROR("illegal member");
  }
}

BOOST_AUTO_TEST_CASE(assign_test)
{
  rabbit::object o;
  rabbit::object u = o["user"];

  u["name"] = "yui";
  u["age"] = 18;

  BOOST_CHECK(o.is_object());
  BOOST_CHECK(o.has("user"));
  BOOST_CHECK(o["user"].is_object());
  BOOST_CHECK(u.is_object());
  BOOST_CHECK_EQUAL(o["user"]["name"].as_string(), "yui");
  BOOST_CHECK_EQUAL(o["user"]["age"].as_int(), 18);
  BOOST_CHECK_EQUAL(u["name"].as_string(), "yui");
  BOOST_CHECK_EQUAL(u["age"].as_int(), 18);
  BOOST_CHECK_EQUAL(o["user"]["name"].get_native_value_pointer(), u["name"].get_native_value_pointer());
  BOOST_CHECK_EQUAL(o["user"]["age"].get_native_value_pointer(), u["age"].get_native_value_pointer());
  BOOST_CHECK_EQUAL(o["user"]["name"].get_allocator_pointer(), u["name"].get_allocator_pointer());
  BOOST_CHECK_EQUAL(o["user"]["age"].get_allocator_pointer(), u["age"].get_allocator_pointer());
}

BOOST_AUTO_TEST_CASE(member_size_test){
  rabbit::object v;
  v["test"] = 1;
  v["abc"] = 2;


  BOOST_CHECK(v.size() == 2);
  v["qqq"] = 3;
  BOOST_CHECK(v.size() == 3);
  v.erase("abc");
  BOOST_CHECK(v.size() == 2);
}


