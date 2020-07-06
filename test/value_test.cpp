#define BOOST_TEST_MODULE value_test
#include <boost/test/unit_test.hpp>
#include <rabbit.hpp>

BOOST_AUTO_TEST_SUITE(is_test) // {{{
  BOOST_AUTO_TEST_CASE(null_test)
  {
    rabbit::value v;

    BOOST_CHECK(v.is_null());
    BOOST_CHECK(v.is<rabbit::null_tag>());

    BOOST_CHECK(!v.is_bool());
    BOOST_CHECK(!v.is<bool>());
    BOOST_CHECK(!v.is_false());
    BOOST_CHECK(!v.is<rabbit::false_tag>());
    BOOST_CHECK(!v.is_true());
    BOOST_CHECK(!v.is<rabbit::true_tag>());

    BOOST_CHECK(!v.is_string());
    BOOST_CHECK(!v.is<rabbit::string_tag>());
    BOOST_CHECK(!v.is<std::string>());

    BOOST_CHECK(!v.is_int());
    BOOST_CHECK(!v.is_number());
    BOOST_CHECK(!v.is<rabbit::number_tag>());
    BOOST_CHECK(!v.is<int>());

    BOOST_CHECK(!v.is_object());
    BOOST_CHECK(!v.is<rabbit::object_tag>());
    BOOST_CHECK(!v.is<rabbit::object>());

    BOOST_CHECK(!v.is_array());
    BOOST_CHECK(!v.is<rabbit::array_tag>());
    BOOST_CHECK(!v.is<rabbit::array>());
  }

  BOOST_AUTO_TEST_CASE(false_test)
  {
    rabbit::value v(false);

    BOOST_CHECK(!v.is_null());
    BOOST_CHECK(!v.is<rabbit::null_tag>());

    BOOST_CHECK(v.is_bool());
    BOOST_CHECK(v.is<bool>());
    BOOST_CHECK(v.is_false());
    BOOST_CHECK(v.is<rabbit::false_tag>());
    BOOST_CHECK(!v.is_true());
    BOOST_CHECK(!v.is<rabbit::true_tag>());

    BOOST_CHECK(!v.is_string());
    BOOST_CHECK(!v.is<rabbit::string_tag>());
    BOOST_CHECK(!v.is<std::string>());

    BOOST_CHECK(!v.is_int());
    BOOST_CHECK(!v.is_number());
    BOOST_CHECK(!v.is<rabbit::number_tag>());
    BOOST_CHECK(!v.is<int>());

    BOOST_CHECK(!v.is_object());
    BOOST_CHECK(!v.is<rabbit::object_tag>());
    BOOST_CHECK(!v.is<rabbit::object>());

    BOOST_CHECK(!v.is_array());
    BOOST_CHECK(!v.is<rabbit::array_tag>());
    BOOST_CHECK(!v.is<rabbit::array>());
  }

  BOOST_AUTO_TEST_CASE(true_test)
  {
    rabbit::value v(true);

    BOOST_CHECK(!v.is_null());
    BOOST_CHECK(!v.is<rabbit::null_tag>());

    BOOST_CHECK(v.is_bool());
    BOOST_CHECK(v.is<bool>());
    BOOST_CHECK(!v.is_false());
    BOOST_CHECK(!v.is<rabbit::false_tag>());
    BOOST_CHECK(v.is_true());
    BOOST_CHECK(v.is<rabbit::true_tag>());

    BOOST_CHECK(!v.is_string());
    BOOST_CHECK(!v.is<rabbit::string_tag>());
    BOOST_CHECK(!v.is<std::string>());

    BOOST_CHECK(!v.is_int());
    BOOST_CHECK(!v.is_number());
    BOOST_CHECK(!v.is<rabbit::number_tag>());
    BOOST_CHECK(!v.is<int>());

    BOOST_CHECK(!v.is_object());
    BOOST_CHECK(!v.is<rabbit::object_tag>());
    BOOST_CHECK(!v.is<rabbit::object>());

    BOOST_CHECK(!v.is_array());
    BOOST_CHECK(!v.is<rabbit::array_tag>());
    BOOST_CHECK(!v.is<rabbit::array>());
  }

  BOOST_AUTO_TEST_CASE(string_test)
  {
    rabbit::value v("str");

    BOOST_CHECK(!v.is_null());
    BOOST_CHECK(!v.is<rabbit::null_tag>());

    BOOST_CHECK(!v.is_bool());
    BOOST_CHECK(!v.is<bool>());
    BOOST_CHECK(!v.is_false());
    BOOST_CHECK(!v.is<rabbit::false_tag>());
    BOOST_CHECK(!v.is_true());
    BOOST_CHECK(!v.is<rabbit::true_tag>());

    BOOST_CHECK(v.is_string());
    BOOST_CHECK(v.is<rabbit::string_tag>());
    BOOST_CHECK(v.is<std::string>());

    BOOST_CHECK(!v.is_int());
    BOOST_CHECK(!v.is_number());
    BOOST_CHECK(!v.is<rabbit::number_tag>());
    BOOST_CHECK(!v.is<int>());

    BOOST_CHECK(!v.is_object());
    BOOST_CHECK(!v.is<rabbit::object_tag>());
    BOOST_CHECK(!v.is<rabbit::object>());

    BOOST_CHECK(!v.is_array());
    BOOST_CHECK(!v.is<rabbit::array_tag>());
    BOOST_CHECK(!v.is<rabbit::array>());
  }

  BOOST_AUTO_TEST_CASE(number_test)
  {
    rabbit::value v(123);

    BOOST_CHECK(!v.is_null());
    BOOST_CHECK(!v.is<rabbit::null_tag>());

    BOOST_CHECK(!v.is_bool());
    BOOST_CHECK(!v.is<bool>());
    BOOST_CHECK(!v.is_false());
    BOOST_CHECK(!v.is<rabbit::false_tag>());
    BOOST_CHECK(!v.is_true());
    BOOST_CHECK(!v.is<rabbit::true_tag>());

    BOOST_CHECK(!v.is_string());
    BOOST_CHECK(!v.is<rabbit::string_tag>());
    BOOST_CHECK(!v.is<std::string>());

    BOOST_CHECK(v.is_int());
    BOOST_CHECK(v.is_number());
    BOOST_CHECK(v.is<rabbit::number_tag>());
    BOOST_CHECK(v.is<int>());

    BOOST_CHECK(!v.is_object());
    BOOST_CHECK(!v.is<rabbit::object_tag>());
    BOOST_CHECK(!v.is<rabbit::object>());

    BOOST_CHECK(!v.is_array());
    BOOST_CHECK(!v.is<rabbit::array_tag>());
    BOOST_CHECK(!v.is<rabbit::array>());
  }

  BOOST_AUTO_TEST_CASE(object_test)
  {
    rabbit::object v;

    BOOST_CHECK(!v.is_null());
    BOOST_CHECK(!v.is<rabbit::null_tag>());

    BOOST_CHECK(!v.is_bool());
    BOOST_CHECK(!v.is<bool>());
    BOOST_CHECK(!v.is_false());
    BOOST_CHECK(!v.is<rabbit::false_tag>());
    BOOST_CHECK(!v.is_true());
    BOOST_CHECK(!v.is<rabbit::true_tag>());

    BOOST_CHECK(!v.is_string());
    BOOST_CHECK(!v.is<rabbit::string_tag>());
    BOOST_CHECK(!v.is<std::string>());

    BOOST_CHECK(!v.is_int());
    BOOST_CHECK(!v.is_number());
    BOOST_CHECK(!v.is<rabbit::number_tag>());
    BOOST_CHECK(!v.is<int>());

    BOOST_CHECK(v.is_object());
    BOOST_CHECK(v.is<rabbit::object_tag>());
    BOOST_CHECK(v.is<rabbit::object>());

    BOOST_CHECK(!v.is_array());
    BOOST_CHECK(!v.is<rabbit::array_tag>());
    BOOST_CHECK(!v.is<rabbit::array>());
  }

  BOOST_AUTO_TEST_CASE(array_test)
  {
    rabbit::array v;

    BOOST_CHECK(!v.is_null());
    BOOST_CHECK(!v.is<rabbit::null_tag>());

    BOOST_CHECK(!v.is_bool());
    BOOST_CHECK(!v.is<bool>());
    BOOST_CHECK(!v.is_false());
    BOOST_CHECK(!v.is<rabbit::false_tag>());
    BOOST_CHECK(!v.is_true());
    BOOST_CHECK(!v.is<rabbit::true_tag>());

    BOOST_CHECK(!v.is_string());
    BOOST_CHECK(!v.is<rabbit::string_tag>());
    BOOST_CHECK(!v.is<std::string>());

    BOOST_CHECK(!v.is_int());
    BOOST_CHECK(!v.is_number());
    BOOST_CHECK(!v.is<rabbit::number_tag>());
    BOOST_CHECK(!v.is<int>());

    BOOST_CHECK(!v.is_object());
    BOOST_CHECK(!v.is<rabbit::object_tag>());
    BOOST_CHECK(!v.is<rabbit::object>());

    BOOST_CHECK(v.is_array());
    BOOST_CHECK(v.is<rabbit::array_tag>());
    BOOST_CHECK(v.is<rabbit::array>());
  }

BOOST_AUTO_TEST_SUITE_END() // }}}

BOOST_AUTO_TEST_SUITE(as_test) // {{{
  BOOST_AUTO_TEST_CASE(null_test)
  {
    rabbit::value v;

    BOOST_CHECK_THROW(v.as_bool(), rabbit::type_mismatch);
    BOOST_CHECK_THROW(v.as<bool>(), rabbit::type_mismatch);
    BOOST_CHECK_THROW(v.as_int(), rabbit::type_mismatch);
    BOOST_CHECK_THROW(v.as<int>(), rabbit::type_mismatch);
    BOOST_CHECK_THROW(v.as_uint(), rabbit::type_mismatch);
    BOOST_CHECK_THROW(v.as<unsigned>(), rabbit::type_mismatch);
    BOOST_CHECK_THROW(v.as_int64(), rabbit::type_mismatch);
    BOOST_CHECK_THROW(v.as<int64_t>(), rabbit::type_mismatch);
    BOOST_CHECK_THROW(v.as_uint64(), rabbit::type_mismatch);
    BOOST_CHECK_THROW(v.as<uint64_t>(), rabbit::type_mismatch);
    BOOST_CHECK_THROW(v.as_double(), rabbit::type_mismatch);
    BOOST_CHECK_THROW(v.as<double>(), rabbit::type_mismatch);
    BOOST_CHECK_THROW(v.as_string(), rabbit::type_mismatch);
    BOOST_CHECK_THROW(v.as<std::string>(), rabbit::type_mismatch);
  }

  BOOST_AUTO_TEST_CASE(bool_test)
  {
    rabbit::value v(false);

    BOOST_CHECK_EQUAL(v.as_bool(), false);
    BOOST_CHECK_EQUAL(v.as<bool>(), false);
    BOOST_CHECK_THROW(v.as_int(), rabbit::type_mismatch);
    BOOST_CHECK_THROW(v.as<int>(), rabbit::type_mismatch);
    BOOST_CHECK_THROW(v.as_uint(), rabbit::type_mismatch);
    BOOST_CHECK_THROW(v.as<unsigned>(), rabbit::type_mismatch);
    BOOST_CHECK_THROW(v.as_int64(), rabbit::type_mismatch);
    BOOST_CHECK_THROW(v.as<int64_t>(), rabbit::type_mismatch);
    BOOST_CHECK_THROW(v.as_uint64(), rabbit::type_mismatch);
    BOOST_CHECK_THROW(v.as<uint64_t>(), rabbit::type_mismatch);
    BOOST_CHECK_THROW(v.as_double(), rabbit::type_mismatch);
    BOOST_CHECK_THROW(v.as<double>(), rabbit::type_mismatch);
    BOOST_CHECK_THROW(v.as_string(), rabbit::type_mismatch);
    BOOST_CHECK_THROW(v.as<std::string>(), rabbit::type_mismatch);
  }

  BOOST_AUTO_TEST_CASE(int_test)
  {
    rabbit::value v(123);

    BOOST_CHECK_THROW(v.as_bool(), rabbit::type_mismatch);
    BOOST_CHECK_THROW(v.as<bool>(), rabbit::type_mismatch);
    BOOST_CHECK_EQUAL(v.as_int(), 123);
    BOOST_CHECK_EQUAL(v.as<int>(), 123);
    BOOST_CHECK_EQUAL(v.as_uint(), 123);
    BOOST_CHECK_EQUAL(v.as<unsigned>(), 123);
    BOOST_CHECK_EQUAL(v.as_int64(), 123);
    BOOST_CHECK_EQUAL(v.as<int64_t>(), 123);
    BOOST_CHECK_EQUAL(v.as_uint64(), 123);
    BOOST_CHECK_EQUAL(v.as<uint64_t>(), 123);
    BOOST_CHECK_THROW(v.as_double(), rabbit::type_mismatch);
    BOOST_CHECK_THROW(v.as<double>(), rabbit::type_mismatch);
    BOOST_CHECK_THROW(v.as_string(), rabbit::type_mismatch);
    BOOST_CHECK_THROW(v.as<std::string>(), rabbit::type_mismatch);
  }

  BOOST_AUTO_TEST_CASE(double_test)
  {
    rabbit::value v(123.0);

    BOOST_CHECK_THROW(v.as_bool(), rabbit::type_mismatch);
    BOOST_CHECK_THROW(v.as<bool>(), rabbit::type_mismatch);
    BOOST_CHECK_THROW(v.as_int(), rabbit::type_mismatch);
    BOOST_CHECK_THROW(v.as<int>(), rabbit::type_mismatch);
    BOOST_CHECK_THROW(v.as_uint(), rabbit::type_mismatch);
    BOOST_CHECK_THROW(v.as<unsigned>(), rabbit::type_mismatch);
    BOOST_CHECK_THROW(v.as_int64(), rabbit::type_mismatch);
    BOOST_CHECK_THROW(v.as<int64_t>(), rabbit::type_mismatch);
    BOOST_CHECK_THROW(v.as_uint64(), rabbit::type_mismatch);
    BOOST_CHECK_THROW(v.as<uint64_t>(), rabbit::type_mismatch);
    BOOST_CHECK_CLOSE(v.as_double(), 123.0, 0.00001);
    BOOST_CHECK_CLOSE(v.as<double>(), 123.0, 0.00001);
    BOOST_CHECK_THROW(v.as_string(), rabbit::type_mismatch);
    BOOST_CHECK_THROW(v.as<std::string>(), rabbit::type_mismatch);
  }

  BOOST_AUTO_TEST_CASE(string_test)
  {
    rabbit::value v("str");

    BOOST_CHECK_THROW(v.as_bool(), rabbit::type_mismatch);
    BOOST_CHECK_THROW(v.as<bool>(), rabbit::type_mismatch);
    BOOST_CHECK_THROW(v.as_int(), rabbit::type_mismatch);
    BOOST_CHECK_THROW(v.as<int>(), rabbit::type_mismatch);
    BOOST_CHECK_THROW(v.as_uint(), rabbit::type_mismatch);
    BOOST_CHECK_THROW(v.as<unsigned>(), rabbit::type_mismatch);
    BOOST_CHECK_THROW(v.as_int64(), rabbit::type_mismatch);
    BOOST_CHECK_THROW(v.as<int64_t>(), rabbit::type_mismatch);
    BOOST_CHECK_THROW(v.as_uint64(), rabbit::type_mismatch);
    BOOST_CHECK_THROW(v.as<uint64_t>(), rabbit::type_mismatch);
    BOOST_CHECK_THROW(v.as_double(), rabbit::type_mismatch);
    BOOST_CHECK_THROW(v.as<double>(), rabbit::type_mismatch);
    BOOST_CHECK_EQUAL(v.as_string(), "str");
    BOOST_CHECK_EQUAL(v.as<std::string>(), "str");
  }

  BOOST_AUTO_TEST_CASE(result_type)
  {
    rabbit::value v1(123);
    int r1 = v1.as();

    rabbit::value v2("str");
    std::string r2 = v2.as();
  }
BOOST_AUTO_TEST_SUITE_END() // }}}


BOOST_AUTO_TEST_CASE(value_construct_by_value_test){
  {
    rabbit::value v1(123);
    BOOST_CHECK(v1.is_int());

    rabbit::value::allocator_type a;
    rabbit::value v2(123, a);
    BOOST_CHECK(v2.is_int());
  }

  {
    rabbit::value v1("abc");
    BOOST_CHECK(v1.is_string());

    rabbit::value::allocator_type a;
    rabbit::value v2("abc", a);
    BOOST_CHECK(v2.is_string());
  }

  {
    rabbit::value v1(123.5);
    BOOST_CHECK(v1.is_double());

    rabbit::value::allocator_type a;
    rabbit::value v2(123.5, a);
    BOOST_CHECK(v2.is_double());
  }


}




BOOST_AUTO_TEST_CASE(value_construct_by_tag_test){
  rabbit::value v1((rabbit::object_tag())); //Extra parens for most vexing parse
  BOOST_CHECK(v1.is_object());

  rabbit::value::allocator_type a;
  rabbit::value v2((rabbit::object_tag()), a);
  BOOST_CHECK(v2.is_object());
}



BOOST_AUTO_TEST_CASE(clear_test)
{
  rabbit::value v(123);
  BOOST_CHECK(v.is_int());
  v.clear();
  BOOST_CHECK(v.is_null());
}

BOOST_AUTO_TEST_CASE(swap_test)
{
  rabbit::value a(123);
  rabbit::value b("str");

  BOOST_CHECK(a.is_int());
  BOOST_CHECK_EQUAL(a.as_int(), 123);
  BOOST_CHECK(b.is_string());
  BOOST_CHECK_EQUAL(b.as_string(), "str");

  a.swap(b);

  BOOST_CHECK(a.is_string());
  BOOST_CHECK_EQUAL(a.as_string(), "str");
  BOOST_CHECK(b.is_int());
  BOOST_CHECK_EQUAL(b.as_int(), 123);
}

BOOST_AUTO_TEST_CASE(compare)
{
  rabbit::value a(123);
  rabbit::value b(123);
  BOOST_CHECK(a == b);
  b = 321;
  BOOST_CHECK(a != b);
  b = "str";
  BOOST_CHECK(a != b);
}

BOOST_AUTO_TEST_CASE(root_value_test)
{
  rabbit::value v;
  v.set(rabbit::object_tag());

  BOOST_CHECK_NO_THROW(rabbit::value u1(v["foo"]));
  BOOST_CHECK_NO_THROW(rabbit::value u1 = v["foo"]);
  BOOST_CHECK_THROW(rabbit::value u2(v), std::runtime_error);
  BOOST_CHECK_THROW(rabbit::value u2 = v, std::runtime_error);
}

BOOST_AUTO_TEST_CASE(member_count){
  rabbit::object v;
  v["test"] = 1;
  v["abc"] = 2;


  BOOST_CHECK(v.member_count() == 2);
  v["qqq"] = 3;
  BOOST_CHECK(v.member_count() == 3);
  v.erase("abc");
  BOOST_CHECK(v.member_count() == 2);
}
