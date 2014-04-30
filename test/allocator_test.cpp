#define BOOST_TEST_MODULE allocator_test
#include <boost/test/unit_test.hpp>
#include <rabbit.hpp>

BOOST_AUTO_TEST_CASE(compare)
{
  rabbit::allocator alloc;
  rabbit::value a(1, alloc);
  rabbit::value b(2, alloc);
  rabbit::value c;

  BOOST_CHECK(a.get_allocator_pointer() != 0);
  BOOST_CHECK(b.get_allocator_pointer() != 0);
  BOOST_CHECK(c.get_allocator_pointer() != 0);
  BOOST_CHECK(a.get_allocator_pointer() == b.get_allocator_pointer());
  BOOST_CHECK(a.get_allocator_pointer() != c.get_allocator_pointer());
}
