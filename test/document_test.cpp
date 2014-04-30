#define BOOST_TEST_MODULE document_test
#include <boost/test/unit_test.hpp>
#include <rabbit.hpp>

BOOST_AUTO_TEST_CASE(parse_test)
{
  rabbit::document doc;
  BOOST_CHECK_THROW(doc.parse("invalid json string"), rabbit::parse_error);
  BOOST_CHECK_NO_THROW(doc.parse("{\"value\": 123}"));
  BOOST_CHECK(doc.is_object());
  BOOST_CHECK(doc.has("value"));
  BOOST_CHECK_EQUAL(doc["value"].as_int(), 123);

  rabbit::object o;
  o["name"] = "yui";
  o["age"] = 18;
  BOOST_CHECK_NO_THROW(doc.parse(o.str()));
  BOOST_CHECK_EQUAL(doc["name"].as_string(), o["name"].as_string());
  BOOST_CHECK_EQUAL(doc["age"].as_int(), o["age"].as_int());
}

