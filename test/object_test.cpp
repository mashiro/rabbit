#define BOOST_TEST_MODULE object_test
#include <boost/test/unit_test.hpp>
#include <rabbit.hpp>

BOOST_AUTO_TEST_CASE(has_test)
{
  rabbit::value v;
  BOOST_CHECK_THROW(v.has("foo"), rabbit::type_mismatch);

  rabbit::object o;
  o["foo"] = 123;
  BOOST_CHECK(o.has("foo"));
  BOOST_CHECK(!o.has("bar"));
}

BOOST_AUTO_TEST_CASE(insert_test)
{
  rabbit::value v;
  BOOST_CHECK_THROW(v.insert("foo", 123), rabbit::type_mismatch);

  rabbit::object o;
  rabbit::value s("str");
  o.insert("foo", 123);
  o.insert("bar", s);
  BOOST_CHECK(o.has("foo"));
  BOOST_CHECK(o.has("bar"));
  BOOST_CHECK(!o.has("buzz"));
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
  o.erase(o.begin());
  BOOST_CHECK(!o.has("foo"));
  BOOST_CHECK(!o.erase("foo"));
}

BOOST_AUTO_TEST_CASE(erase_const_itr)
{
  rabbit::value v;
  BOOST_CHECK_THROW(v.erase("foo"), rabbit::type_mismatch);

  rabbit::object o;
  o["foo"] = 123;
  BOOST_CHECK(o.has("foo"));
  o.erase(o.cbegin());
  BOOST_CHECK(!o.has("foo"));
  BOOST_CHECK(!o.erase("foo"));
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
