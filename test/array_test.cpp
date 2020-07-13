#define BOOST_TEST_MODULE array_test
#include <boost/test/unit_test.hpp>
#include <rabbit.hpp>

BOOST_AUTO_TEST_CASE(size_test)
{
  rabbit::value v;
  BOOST_CHECK_THROW(v.size(), rabbit::type_mismatch);

  rabbit::array a;
  BOOST_CHECK_EQUAL(a.size(), 0);
  a.push_back(1);
  BOOST_CHECK_EQUAL(a.size(), 1);
  a.push_back(2);
  BOOST_CHECK_EQUAL(a.size(), 2);
}

BOOST_AUTO_TEST_CASE(empty_test)
{
  rabbit::value v;
  BOOST_CHECK_THROW(v.empty(), rabbit::type_mismatch);

  rabbit::array a;
  BOOST_CHECK(a.empty());
  a.push_back(1);
  BOOST_CHECK(!a.empty());
}

BOOST_AUTO_TEST_CASE(at_test)
{
  rabbit::value v;
  BOOST_CHECK_THROW(v.at(0), rabbit::type_mismatch);

  rabbit::array a;
  BOOST_CHECK_THROW(a.at(0), std::out_of_range);
  a.push_back(1);
  a.push_back(2);
  a.push_back(3);
  BOOST_CHECK(a.at(0).is_int());
  BOOST_CHECK(a.at(1).is_int());
  BOOST_CHECK(a.at(2).is_int());
  BOOST_CHECK_EQUAL(a.at(0).as_int(), 1);
  BOOST_CHECK_EQUAL(a.at(1).as_int(), 2);
  BOOST_CHECK_EQUAL(a.at(2).as_int(), 3);
}

BOOST_AUTO_TEST_CASE(push_back_test)
{
  rabbit::value v;
  BOOST_CHECK_THROW(v.size(), rabbit::type_mismatch);

  rabbit::object o;
  o["foo"] = 456;

  rabbit::array a;
  a.push_back(123);
  a.push_back(1.0);
  a.push_back("str");
  a.push_back(o);
  BOOST_CHECK_EQUAL(a.size(), 4);
  BOOST_CHECK_EQUAL(a[0].as_int(), 123);
  BOOST_CHECK_CLOSE(a[1].as_double(), 1.0, 0.000001);
  BOOST_CHECK_EQUAL(a[2].as_string(), "str");
  BOOST_CHECK_EQUAL(a[3]["foo"].as_int(), 456);
}

BOOST_AUTO_TEST_CASE(pop_back_test)
{
  rabbit::value v;
  BOOST_CHECK_THROW(v.pop_back(), rabbit::type_mismatch);

  rabbit::array a;
  a.push_back(1);
  a.push_back(2);
  a.push_back(3);
  BOOST_CHECK_EQUAL(a.size(), 3);
  BOOST_CHECK_EQUAL(a.at(a.size() - 1).as_int(), 3);
  a.pop_back();
  BOOST_CHECK_EQUAL(a.size(), 2);
  BOOST_CHECK_EQUAL(a.at(a.size() - 1).as_int(), 2);
  a.pop_back();
  BOOST_CHECK_EQUAL(a.size(), 1);
  BOOST_CHECK_EQUAL(a.at(a.size() - 1).as_int(), 1);
}

BOOST_AUTO_TEST_CASE(iterator_test)
{
  rabbit::array a;
  a.push_back(123);
  a.push_back(1.0);
  a.push_back("str");

  int n = 0;
  typedef rabbit::array::iterator iter_t;
  for (iter_t it = a.begin(); it != a.end(); ++it, ++n)
  {
    if      (n == 0) BOOST_CHECK_EQUAL(it->as_int(), 123);
    else if (n == 1) BOOST_CHECK_CLOSE(it->as_double(), 1.0, 0.000001);
    else if (n == 2) BOOST_CHECK_EQUAL(it->as_string(), "str");
    else BOOST_ERROR("illegal value");
  }
}

BOOST_AUTO_TEST_CASE(const_iterator_test)
{
  rabbit::array a;
  a.push_back(123);
  a.push_back(1.0);
  a.push_back("str");

  int n = 0;
  typedef rabbit::array::const_iterator iter_t;
  for (iter_t it = a.begin(); it != a.end(); ++it, ++n)
  {
    if      (n == 0) BOOST_CHECK_EQUAL(it->as_int(), 123);
    else if (n == 1) BOOST_CHECK_CLOSE(it->as_double(), 1.0, 0.000001);
    else if (n == 2) BOOST_CHECK_EQUAL(it->as_string(), "str");
    else BOOST_ERROR("illegal value");
  }
}

