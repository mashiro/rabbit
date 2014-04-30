// The MIT License (MIT)
//
// Copyright (c) 2013-2014 mashiro
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
// the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#ifndef RABBIT_HPP_INCLUDED
#define RABBIT_HPP_INCLUDED

#ifndef RABBIT_NAMESPACE
#define RABBIT_NAMESPACE rabbit
#endif

#include <string>
#include <stdexcept>
#include <iterator>
#include <algorithm>
#include <sstream>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

namespace RABBIT_NAMESPACE {

#define RABBIT_TAG_DEF(_type, _N) \
  struct _type { static const int value; }; \
  const int _type::value = _N; \
/**/
RABBIT_TAG_DEF(null_t, rapidjson::kNullType)
RABBIT_TAG_DEF(false_t, rapidjson::kFalseType)
RABBIT_TAG_DEF(true_t, rapidjson::kTrueType)
RABBIT_TAG_DEF(object_t, rapidjson::kObjectType)
RABBIT_TAG_DEF(array_t, rapidjson::kArrayType)
RABBIT_TAG_DEF(string_t, rapidjson::kStringType)
RABBIT_TAG_DEF(number_t, rapidjson::kNumberType)
#undef RABBIT_TAG_DEF

class type_mismatch : public std::runtime_error
{
public:
  type_mismatch(const std::string& msg)
    : std::runtime_error(msg)
  {}
};

class parse_error : public std::runtime_error
{
public:
  parse_error(const std::string& msg)
    : std::runtime_error(msg)
  {}
};

namespace details {

  struct none_t {};

  template <typename T>
  struct tag_info {};

  template <template <class T> class Value, typename Traits>
  struct tag_info< Value<Traits> >
  {
    typedef typename Value<Traits>::tag type;
    static const char* tag_name() { return tag_info<type>::tag_name(); }
    static const char* type_name() { return tag_info<type>::type_name(); }
  };

#define RABBIT_TAG_INFO_DEF_1(_T, _type1, _type2, _tag_name, _type_name) \
  template <_T> \
  struct tag_info<_type1> \
  { \
    typedef _type2 type; \
    static const char* tag_name() { return #_tag_name; } \
    static const char* type_name() { return #_type_name; } \
  }; \
/**/
#define RABBIT_TAG_INFO_DEF(_type, _tag_name, _type_name) \
  RABBIT_TAG_INFO_DEF_1(, _type, _type, _tag_name, _type_name) \
/**/
  RABBIT_TAG_INFO_DEF(null_t, null, null_t)
  RABBIT_TAG_INFO_DEF(false_t, false, false_t)
  RABBIT_TAG_INFO_DEF(true_t, true, true_t)
  RABBIT_TAG_INFO_DEF(object_t, object, object_t)
  RABBIT_TAG_INFO_DEF(array_t, array, array_t)
  RABBIT_TAG_INFO_DEF(string_t, string, string_t)
  RABBIT_TAG_INFO_DEF(number_t, number, number_t)

  RABBIT_TAG_INFO_DEF(bool, bool, bool)
  RABBIT_TAG_INFO_DEF(int, number, int)
  RABBIT_TAG_INFO_DEF(unsigned, number, unsigned)
  RABBIT_TAG_INFO_DEF(int64_t, number, int64_t)
  RABBIT_TAG_INFO_DEF(uint64_t, number, uint64_t)
  RABBIT_TAG_INFO_DEF(double, number, double)
  RABBIT_TAG_INFO_DEF(std::string, string, string)
  RABBIT_TAG_INFO_DEF(std::wstring, string, wstring)
  RABBIT_TAG_INFO_DEF_1(std::size_t N, char[N], char*, string, char[])
  RABBIT_TAG_INFO_DEF_1(std::size_t N, wchar_t[N], wchar_t*, string, wchar_t[])
  RABBIT_TAG_INFO_DEF_1(std::size_t N, const char[N], const char*, string, const char[])
  RABBIT_TAG_INFO_DEF_1(std::size_t N, const wchar_t[N], const wchar_t*, string, const wchar_t[])
#undef RABBIT_TAG_INFO_DEF
#undef RABBIT_TAG_INFO_DEF_1


  template <bool C, typename T = void>
  struct enable_if_c
  {
    typedef T type;
  };

  template <typename T>
  struct enable_if_c<false, T>
  {};

  template <typename Cond, typename T = void>
  struct enable_if : enable_if_c<Cond::value, T>
  {};

  template <typename Cond, typename T = void>
  struct disable_if : enable_if_c<!Cond::value, T>
  {};

  template <bool C>
  struct bool_
  {
    static const bool value = C;
  };

  typedef bool_<true> true_;
  typedef bool_<false> false_;


#define RABBIT_IS_META_FUNC_DEF(_name, _type) \
  template <typename T> \
  struct is_##_name##_impl : false_ {}; \
  \
  template <> \
  struct is_##_name##_impl<_type> : true_ {}; \
  \
  template <typename T> \
  struct is_##_name \
    : is_##_name##_impl< typename tag_info<T>::type > \
  {}; \
/**/
  RABBIT_IS_META_FUNC_DEF(null, null_t)
  RABBIT_IS_META_FUNC_DEF(false, false_t)
  RABBIT_IS_META_FUNC_DEF(true, true_t)
  RABBIT_IS_META_FUNC_DEF(object, object_t)
  RABBIT_IS_META_FUNC_DEF(array, array_t)
  RABBIT_IS_META_FUNC_DEF(string, string_t)
  RABBIT_IS_META_FUNC_DEF(number, number_t)
  RABBIT_IS_META_FUNC_DEF(bool, bool)
  RABBIT_IS_META_FUNC_DEF(int, int)
  RABBIT_IS_META_FUNC_DEF(unsigned, unsigned)
  RABBIT_IS_META_FUNC_DEF(int64_t, int64_t)
  RABBIT_IS_META_FUNC_DEF(uint64_t, uint64_t)
  RABBIT_IS_META_FUNC_DEF(double, double)
#undef RABBIT_IS_META_FUNC_DEF

  // std::basic_string specialization
  template <typename Char>
  struct is_string_impl< std::basic_string<Char> > : true_ {};

  template <typename T>
  struct is_value : bool_<
                  is_object<T>::value ||
                  is_array<T>::value> {};


  template <typename T>
  struct remove_reference { typedef T type; };

  template <typename T>
  struct remove_reference<T&> { typedef T type; };


  template <typename PseudoReference>
  struct operator_arrow_proxy
  {
    mutable PseudoReference value_;
    operator_arrow_proxy(const PseudoReference& value) : value_(value) {}
    PseudoReference* operator->() const { return &value_; }
  };

  template <typename T>
  struct operator_arrow_proxy<T&>
  {
    T& value_;
    operator_arrow_proxy(T& value) : value_(value) {}
    T* operator->() const { return &value_; }
  };


  template <typename Function, typename Iterator>
  class transform_iterator
  {
    typedef std::iterator_traits<Iterator> traits_type;

  public:
    typedef transform_iterator this_type;
    typedef Function function_type;

    typedef Iterator iterator_type;
    typedef typename traits_type::iterator_category iterator_category;
    typedef typename traits_type::difference_type difference_type;

    typedef typename Function::result_type result_type;
    typedef typename remove_reference<result_type>::type value_type;
    typedef operator_arrow_proxy<result_type> operator_arrow_proxy_type;
    typedef operator_arrow_proxy_type pointer;
    typedef result_type reference;

  private:
    iterator_type it_;
    function_type func_;

  public:
    transform_iterator()
    {}

    explicit transform_iterator(const iterator_type& it)
      : it_(it)
    {}

    transform_iterator(const iterator_type& it, const function_type& func)
      : it_(it)
      , func_(func)
    {}

    template <typename OtherFunction, typename OtherIterator>
    transform_iterator(const transform_iterator<OtherFunction, OtherIterator>& other)
      : it_(other.base())
      , func_(other.functor())
    {}

    iterator_type& base() { return it_; }
    const iterator_type& base() const { return it_; }

    function_type& functor() { return func_; }
    const function_type& functor() const { return func_; }

    result_type dereference() const { return func_(*it_); }

    result_type operator*() const { return dereference(); }
    operator_arrow_proxy_type operator->() const { return operator_arrow_proxy_type(dereference()); }

    this_type& operator++() { ++it_; return *this; }
    this_type operator++(int) { return this_type(it_++, func_); }
    this_type& operator--() { --it_; return *this; }
    this_type operator--(int) { return this_type(it_--, func_); }

    this_type operator+(difference_type n) const { return this_type(it_ + n, func_); }
    this_type& operator+=(difference_type n) { it_ += n; return *this; }
    this_type operator-(difference_type n) const { return this_type(it_ - n, func_); }
    this_type& operator-=(difference_type n) { it_ -= n; return *this; }

    result_type operator[](difference_type n) const { return func_(it_[n]); }

    template <typename OtherFunction, typename OtherIterator>
    bool operator==(const transform_iterator<OtherFunction, OtherIterator>& other) const { return base() == other.base(); }

    template <typename OtherFunction, typename OtherIterator>
    bool operator!=(const transform_iterator<OtherFunction, OtherIterator>& other) const { return base() != other.base(); }

    template <typename OtherFunction, typename OtherIterator>
    bool operator<(const transform_iterator<OtherFunction, OtherIterator>& other) const { return base() < other.base(); }

    template <typename OtherFunction, typename OtherIterator>
    bool operator>(const transform_iterator<OtherFunction, OtherIterator>& other) const { return base() > other.base(); }

    template <typename OtherFunction, typename OtherIterator>
    bool operator<=(const transform_iterator<OtherFunction, OtherIterator>& other) const { return base() <= other.base(); }

    template <typename OtherFunction, typename OtherIterator>
    bool operator>=(const transform_iterator<OtherFunction, OtherIterator>& other) const { return base() >= other.base(); }
  };

  template <typename Function, typename Iterator>
  transform_iterator<Function, Iterator> make_transform_iterator(Iterator it, Function func = Function())
  {
    return transform_iterator<Function, Iterator>(it, func);
  }


  template <typename Member, typename ValueRef>
  class member_wrapper
  {
  public:
    typedef Member wrapped_type;
    typedef ValueRef value_ref_type;
    typedef typename ValueRef::string_type string_type;
    typedef typename ValueRef::allocator_type allocator_type;

    class proxy
    {
      wrapped_type& member_;
      allocator_type& alloc_;

    public:
      proxy(wrapped_type& member, allocator_type& alloc)
        : member_(member)
        , alloc_(alloc)
      {}

      string_type name() const { return value_ref_type(member_.name, alloc_).template as<string_type>(); }
      value_ref_type value() const { return value_ref_type(member_.value, alloc_); }
    };

  private:
    allocator_type& alloc_;

  public:
    member_wrapper(allocator_type& alloc)
      : alloc_(alloc)
    {}

    template <typename OtherMember, typename OtherValueRef>
    member_wrapper(const member_wrapper<OtherMember, OtherValueRef>& other)
      : alloc_(other.get_allocator())
    {}

    typedef proxy result_type;
    result_type operator()(wrapped_type& member) const
    {
      return result_type(member, alloc_);
    }

    allocator_type& get_allocator() const { return alloc_; }
  };

  template <typename Value, typename ValueRef>
  class value_wrapper
  {
  public:
    typedef Value wrapped_type;
    typedef ValueRef value_ref_type;
    typedef typename ValueRef::string_type string_type;
    typedef typename ValueRef::allocator_type allocator_type;

  private:
    allocator_type& alloc_;

  public:
    value_wrapper(allocator_type& alloc)
      : alloc_(alloc)
    {}

    template <typename OtherValue, typename OtherValueRef>
    value_wrapper(const value_wrapper<OtherValue, OtherValueRef>& other)
      : alloc_(other.get_allocator())
    {}

    typedef value_ref_type result_type;
    result_type operator()(wrapped_type& value) const
    {
      return result_type(value, alloc_);
    }

    allocator_type& get_allocator() const { return alloc_; }
  };

  template <typename Encoding>
  struct value_ref_traits
  {
    typedef Encoding encoding_type;
    typedef rapidjson::GenericDocument<Encoding> document_type;
    typedef rapidjson::GenericValue<Encoding> value_type;
    typedef typename document_type::AllocatorType allocator_type;

    template <typename ValueRef, typename Tag>
    static void set(ValueRef& ref, Tag tag)
    {
      ref.set(tag);
    }
  };

  template <typename Encoding>
  struct const_value_ref_traits
  {
    typedef Encoding encoding_type;
    typedef const rapidjson::GenericDocument<Encoding> document_type;
    typedef const rapidjson::GenericValue<Encoding> value_type;
    typedef const typename document_type::AllocatorType allocator_type;

    template <typename ValueRef, typename Tag>
    static void set(const ValueRef&, Tag)
    {}
  };

  template <typename T>
  class scoped_ptr
  {
  private:
    T* p_;

  private:
    scoped_ptr(const scoped_ptr& other);
    scoped_ptr& operator=(const scoped_ptr& other);

  public:
    explicit scoped_ptr(T* p = 0)
      : p_(p)
    {}

    ~scoped_ptr()
    {
      delete p_;
    }

    T* operator->() { return p_; }
    const T* operator->() const { return p_; }

    T& operator*() { return *p_; }
    const T& operator*() const { return *p_; }

    T& get() { return *p_; }
    const T& get() const { return *p_; }

    void swap(scoped_ptr& other)
    {
      std::swap(p_, other.p_);
    }
  };

} // details

template <typename Traits>
class basic_value_ref
{
  typedef Traits traits_type;

public:
  typedef typename traits_type::encoding_type   encoding_type;
  typedef typename traits_type::document_type   native_document_type;
  typedef typename traits_type::value_type      native_value_type;
  typedef typename traits_type::allocator_type  allocator_type;

  typedef typename encoding_type::Ch            char_type;
  typedef std::basic_string<char_type>          string_type;
  typedef basic_value_ref                       value_ref_type;
  typedef basic_value_ref< details::const_value_ref_traits<encoding_type> > const_value_ref_type;

private:
  typedef details::member_wrapper<
    typename native_value_type::Member, value_ref_type> member_wrapper_type;
  typedef details::member_wrapper<
    const typename native_value_type::Member, const_value_ref_type> const_member_wrapper_type;
  typedef details::value_wrapper<
    native_value_type, value_ref_type> value_wrapper_type;
  typedef details::value_wrapper<
    const native_value_type, const_value_ref_type> const_value_wrapper_type;

public:
  typedef details::transform_iterator<
    member_wrapper_type, typename native_value_type::MemberIterator> member_iterator;
  typedef details::transform_iterator<
    const_member_wrapper_type, typename native_value_type::ConstMemberIterator> const_member_iterator;
  typedef details::transform_iterator<
    value_wrapper_type, typename native_value_type::ValueIterator> value_iterator;
  typedef details::transform_iterator<
    const_value_wrapper_type, typename native_value_type::ConstValueIterator> const_value_iterator;

private:
  native_value_type* value_;
  allocator_type* alloc_;

protected:
  void set_implements(native_value_type& value, allocator_type& alloc)
  {
    value_ = &value;
    alloc_ = &alloc;
  }

  template <typename OtherTraits>
  void set_implements(const basic_value_ref<OtherTraits>& ref)
  {
    value_ = ref.get_native_value_pointer();
    alloc_ = ref.get_allocator_pointer();
  }

public:
  basic_value_ref()
    : value_(0)
    , alloc_(0)
  {}

  basic_value_ref(native_value_type& value, allocator_type& alloc)
    : value_(0)
    , alloc_(0)
  {
    set_implements(value, alloc);
  }

  template <typename OtherTraits>
  basic_value_ref(const basic_value_ref<OtherTraits>& other)
    : value_(other.get_native_value_pointer())
    , alloc_(other.get_allocator_pointer())
  {}

  native_value_type* get_native_value_pointer() const { return value_; }
  allocator_type* get_allocator_pointer() const { return alloc_; }
  allocator_type& get_allocator() const { return *alloc_; }

  void set(details::none_t)           {}
  void set(null_t)                    { value_->SetNull(); }
  void set(object_t)                  { value_->SetObject(); }
  void set(array_t)                   { value_->SetArray(); }
  void set(bool value)                { value_->SetBool(value); }
  void set(int value)                 { value_->SetInt(value); }
  void set(unsigned value)            { value_->SetUint(value); }
  void set(int64_t value)             { value_->SetInt64(value); }
  void set(uint64_t value)            { value_->SetUint64(value); }
  void set(double value)              { value_->SetDouble(value); }
  void set(const char_type* value)    { value_->SetString(value, *alloc_); }
  void set(const string_type& value)  { value_->SetString(value.c_str(), value.size(), *alloc_); }

  template <typename T>
  value_ref_type& operator=(const T& value)
  {
    set(value);
    return *this;
  }

  int which() const
  {
    return static_cast<int>(value_->GetType());
  }

#define RABBIT_IS_DEF(_func_name, _base_name) \
  template <typename T> \
  bool is(typename details::enable_if< details::is_##_func_name<T> >::type* = 0) const \
  { \
    return value_->Is##_base_name(); \
  } \
/**/
#define RABBIT_AS_DEF(_func_name, _base_name) \
  template <typename T> \
  T as(typename details::enable_if< details::is_##_func_name<T> >::type* = 0) const \
  { \
    type_check<T>(); \
    return value_->Get##_base_name(); \
  } \
/**/
#define RABBIT_IS_AS_DEF(_func_name, _base_name) \
  RABBIT_IS_DEF(_func_name, _base_name) \
  RABBIT_AS_DEF(_func_name, _base_name) \
/**/
  RABBIT_IS_DEF(null, Null)
  RABBIT_IS_DEF(false, False)
  RABBIT_IS_DEF(true, True)
  RABBIT_IS_DEF(object, Object)
  RABBIT_IS_DEF(array, Array)
  RABBIT_IS_DEF(number, Number)
  RABBIT_IS_AS_DEF(bool, Bool)
  RABBIT_IS_AS_DEF(int, Int)
  RABBIT_IS_AS_DEF(unsigned, Uint)
  RABBIT_IS_AS_DEF(int64_t, Int64)
  RABBIT_IS_AS_DEF(uint64_t, Uint64)
  RABBIT_IS_AS_DEF(double, Double)
  RABBIT_IS_AS_DEF(string, String)
#undef RABBIT_AS_DEF
#undef RABBIT_IS_DEF

  struct as_t
  {
    const value_ref_type& ref_;
    as_t(const value_ref_type& ref) : ref_(ref) {}

    template <typename Result>
    operator Result() const { return ref_.as<Result>(); }
  };

  as_t as() const { return as_t(*this); }

  bool has(const string_type& name) const
  {
    type_check<object_t>();
    return value_->HasMember(name.c_str());
  }

  template <typename T>
  void insert(const string_type& name, const T& value, typename details::disable_if< details::is_value<T> >::type* = 0)
  {
    type_check<object_t>();
    native_value_type v(value);
    value_->AddMember(name.c_str(), *alloc_, v, *alloc_);
  }

  template <typename T>
  void insert(const string_type& name, const T& value, typename details::enable_if< details::is_value<T> >::type* = 0)
  {
    type_check<object_t>();
    value_->AddMember(name.c_str(), *alloc_, *value.get_native_value_pointer(), *alloc_);
  }

  bool erase(const string_type& name)
  {
    type_check<object_t>();
    return value_->RemoveMember(name.c_str());
  }

  value_ref_type at(const string_type& name)
  {
    type_check<object_t>();

    if (!has(name))
    {
      native_value_type null;
      value_->AddMember(name.c_str(), *alloc_, null, *alloc_);
    }

    return value_ref_type((*value_)[name.c_str()], *alloc_);
  }

  const_value_ref_type at(const string_type& name) const
  {
    type_check<object_t>();
    if (!has(name))
      throw std::out_of_range("not found");
    return const_value_ref_type((*value_)[name.c_str()], *alloc_);
  }

  const_value_ref_type cat(const string_type& name) const { return at(name); }

  value_ref_type operator[](const string_type& name) { return at(name); }
  const_value_ref_type operator[](const string_type& name) const { return at(name); }

  member_iterator member_begin()
  {
    type_check<object_t>();
    return details::make_transform_iterator(value_->MemberBegin(), member_wrapper_type(*alloc_));
  }

  member_iterator member_end()
  {
    type_check<object_t>();
    return details::make_transform_iterator(value_->MemberEnd(), member_wrapper_type(*alloc_));
  }

  const_member_iterator member_begin() const
  {
    type_check<object_t>();
    return details::make_transform_iterator(value_->MemberBegin(), const_member_wrapper_type(*alloc_));
  }

  const_member_iterator member_end() const
  {
    type_check<object_t>();
    return details::make_transform_iterator(value_->MemberEnd(), const_member_wrapper_type(*alloc_));
  }

  const_member_iterator member_cbegin() const { return member_begin(); }
  const_member_iterator member_cend() const { return member_end(); }


  std::size_t size() const
  {
    type_check<array_t>();
    return value_->Size();
  }

  std::size_t capacity() const
  {
    type_check<array_t>();
    return value_->Capacity();
  }

  bool empty() const
  {
    type_check<array_t>();
    return value_->Empty();
  }

  value_ref_type at(std::size_t index)
  {
    type_check<array_t>();
    range_check(index);
    return value_ref_type((*value_)[index], *alloc_);
  }

  const_value_ref_type at(std::size_t index) const
  {
    type_check<array_t>();
    range_check(index);
    return const_value_ref_type((*value_)[index], *alloc_);
  }

  const_value_ref_type cat(std::size_t index) const { return at(index); }

  value_ref_type operator[](std::size_t index) { return at(index); }
  const_value_ref_type operator[](std::size_t index) const { return at(index); }

  template <typename T>
  void push_back(const T& value)
  {
    type_check<array_t>();
    value_->PushBack(value, *alloc_);
  }

  void pop_back()
  {
    type_check<array_t>();
    value_->PopBack();
  }

  value_iterator value_begin()
  {
    type_check<array_t>();
    return details::make_transform_iterator(value_->Begin(), value_wrapper_type(*alloc_));
  }

  value_iterator value_end()
  {
    type_check<array_t>();
    return details::make_transform_iterator(value_->End(), value_wrapper_type(*alloc_));
  }

  const_value_iterator value_begin() const
  {
    type_check<array_t>();
    return details::make_transform_iterator(value_->Begin(), const_value_wrapper_type(*alloc_));
  }

  const_value_iterator value_end() const
  {
    type_check<array_t>();
    return details::make_transform_iterator(value_->End(), const_value_wrapper_type(*alloc_));
  }

  const_value_iterator value_cbegin() const { return value_begin(); }
  const_value_iterator value_cend() const { return value_end(); }


  void swap(value_ref_type& other)
  {
    std::swap(value_, other.value_);
    std::swap(alloc_, other.alloc_);
  }

  string_type str() const
  {
    typedef rapidjson::GenericStringBuffer<encoding_type> buffer_t;
    typedef rapidjson::Writer<buffer_t, encoding_type> writer_t;
    buffer_t buffer;
    writer_t writer(buffer);
    value_->Accept(writer);
    return buffer.GetString();
  }

private:
  template <typename T>
  void type_check() const
  {
    if (!is<T>())
    {
      std::stringstream ss;
      ss << "value is not ";
      ss << details::tag_info<T>::tag_name();
      ss << " (which is " << which() << ")";
      throw type_mismatch(ss.str());
    }
  }

  void range_check(std::size_t index) const
  {
    if (index >= size())
    {
      std::stringstream ss;
      ss << "index (which is " << index << ") >= size() (which is " << size() << ")";
      throw std::out_of_range(ss.str());
    }
  }
};

template <typename Traits, typename Tag = details::none_t>
class basic_value : public basic_value_ref<Traits>
{
public:
  typedef basic_value_ref<Traits>                   base_type;
  typedef typename base_type::value_ref_type        value_ref_type;
  typedef typename base_type::const_value_ref_type  const_value_ref_type;
  typedef typename base_type::char_type             char_type;
  typedef typename base_type::string_type           string_type;
  typedef typename base_type::native_document_type  native_document_type;
  typedef typename base_type::native_value_type     native_value_type;
  typedef typename base_type::allocator_type        allocator_type;

  typedef typename base_type::member_iterator       member_iterator;
  typedef typename base_type::const_member_iterator const_member_iterator;
  typedef typename base_type::value_iterator        value_iterator;
  typedef typename base_type::const_value_iterator  const_value_iterator;

  typedef Tag tag;

private:
  details::scoped_ptr<allocator_type> alloc_impl_;
  details::scoped_ptr<native_value_type> value_impl_;

public:
  basic_value()
    : base_type()
    , alloc_impl_(new allocator_type())
    , value_impl_(new native_value_type())
  {
    base_type::set_implements(*value_impl_, *alloc_impl_);
    Traits::set(*this, tag());
  }

  basic_value(allocator_type& alloc)
    : base_type()
    , value_impl_(new native_value_type())
  {
    base_type::set_implements(*value_impl_, alloc);
    Traits::set(*this, tag());
  }

  template <typename OtherTraits>
  basic_value(basic_value_ref<OtherTraits> ref)
    : base_type()
  {
    base_type::set_implements(ref);
    if (base_type::template is<null_t>())
      Traits::set(*this, tag());
  }

  basic_value(basic_value& other)
    : base_type()
  {
    other.swap(*this);
  }

  basic_value& operator=(basic_value other)
  {
    other.swap(*this);
    return *this;
  }

  template <typename T>
  basic_value& operator=(const T& value)
  {
    base_type::operator=(value);
    return *this;
  }

  void clear()
  {
    base_type::set(tag());
  }

  void swap(basic_value& other)
  {
    base_type::swap(other);
    alloc_impl_.swap(other.alloc_impl_);
    value_impl_.swap(other.value_impl_);
  }
};

template <typename Traits>
class basic_object : public basic_value<Traits, object_t>
{
public:
  typedef basic_value<Traits, object_t>             base_type;
  typedef typename base_type::value_ref_type        value_ref_type;
  typedef typename base_type::const_value_ref_type  const_value_ref_type;
  typedef typename base_type::char_type             char_type;
  typedef typename base_type::string_type           string_type;
  typedef typename base_type::native_document_type  native_document_type;
  typedef typename base_type::native_value_type     native_value_type;
  typedef typename base_type::allocator_type        allocator_type;

  typedef typename base_type::member_iterator       iterator;
  typedef typename base_type::const_member_iterator const_iterator;

public:
  basic_object()
    : base_type()
  {}

  basic_object(allocator_type& alloc)
    : base_type(alloc)
  {}

  template <typename OtherTraits>
  basic_object(basic_value_ref<OtherTraits> ref)
    : base_type(ref)
  {}

  iterator begin()                { return base_type::member_begin(); }
  iterator end()                  { return base_type::member_end(); }
  const_iterator begin() const    { return base_type::member_begin(); }
  const_iterator end() const      { return base_type::member_end(); }
  const_iterator cbegin() const   { return base_type::member_begin(); }
  const_iterator cend() const     { return base_type::member_end(); }
};

template <typename Traits>
class basic_array : public basic_value<Traits, array_t>
{
public:
  typedef basic_value<Traits, array_t>              base_type;
  typedef typename base_type::value_ref_type        value_ref_type;
  typedef typename base_type::const_value_ref_type  const_value_ref_type;
  typedef typename base_type::char_type             char_type;
  typedef typename base_type::string_type           string_type;
  typedef typename base_type::native_document_type  native_document_type;
  typedef typename base_type::native_value_type     native_value_type;
  typedef typename base_type::allocator_type        allocator_type;

  typedef typename base_type::value_iterator        iterator;
  typedef typename base_type::const_value_iterator  const_iterator;

public:
  basic_array()
    : base_type()
  {}

  basic_array(allocator_type& alloc)
    : base_type(alloc)
  {}

  template <typename OtherTraits>
  basic_array(basic_value_ref<OtherTraits> ref)
    : base_type(ref)
  {}

  iterator begin()                { return base_type::value_begin(); }
  iterator end()                  { return base_type::value_end(); }
  const_iterator begin() const    { return base_type::value_begin(); }
  const_iterator end() const      { return base_type::value_end(); }
  const_iterator cbegin() const   { return base_type::value_begin(); }
  const_iterator cend() const     { return base_type::value_end(); }
};


template <typename Traits>
class basic_document : public basic_value_ref<Traits>
{
public:
  typedef basic_value_ref<Traits>                   base_type;
  typedef typename base_type::value_ref_type        value_ref_type;
  typedef typename base_type::const_value_ref_type  const_value_ref_type;
  typedef typename base_type::char_type             char_type;
  typedef typename base_type::string_type           string_type;
  typedef typename base_type::native_document_type  native_document_type;
  typedef typename base_type::native_value_type     native_value_type;
  typedef typename base_type::allocator_type        allocator_type;

private:
  details::scoped_ptr<native_document_type> document_impl_;

public:
  basic_document()
    : base_type()
    , document_impl_(new native_document_type())
  {
    base_type::set_implements(*document_impl_, document_impl_->GetAllocator());
  }

  basic_document& operator=(basic_document other)
  {
    other.swap(*this);
    return *this;
  }

  void swap(basic_document& other)
  {
    base_type::swap(other);
    document_impl_.swap(other.document_impl_);
  }

  void parse(const string_type& str)
  {
    parse<0>(str.c_str());
  }

  void parse(const char_type* str)
  {
    parse<0>(str);
  }

  template <unsigned ParseFlags>
  void parse(const string_type& str)
  {
    parse<ParseFlags>(str.c_str());
  }

  template <unsigned ParseFlags>
  void parse(const char_type* str)
  {
    document_impl_->template Parse<ParseFlags>(str);
    if (document_impl_->HasParseError())
      throw parse_error(document_impl_->GetParseError());
  }
};


template <typename Traits>
void swap(basic_value<Traits>& a, basic_value<Traits>& b)
{
  a.swap(b);
}

template <typename Traits>
void swap(basic_object<Traits>& a, basic_object<Traits>& b)
{
  a.swap(b);
}

template <typename Traits>
void swap(basic_array<Traits>& a, basic_array<Traits>& b)
{
  a.swap(b);
}

template <typename Traits>
void swap(basic_document<Traits>& a, basic_document<Traits>& b)
{
  a.swap(b);
}


typedef rapidjson::UTF8<> default_encoding;

template <typename Encoding = default_encoding>
struct types
{
  typedef Encoding encoding;

  typedef details::value_ref_traits<encoding>                     default_value_ref_traits;
  typedef details::const_value_ref_traits<encoding>               default_const_value_ref_traits;

  typedef basic_value_ref<default_value_ref_traits>               value_ref;
  typedef const basic_value_ref<default_const_value_ref_traits>   const_value_ref;

  typedef basic_value<default_value_ref_traits>                   value;
  typedef const basic_value<default_const_value_ref_traits>       const_value;

  typedef basic_object<default_value_ref_traits>                  object;
  typedef const basic_object<default_const_value_ref_traits>      const_object;

  typedef basic_array<default_value_ref_traits>                   array;
  typedef const basic_array<default_const_value_ref_traits>       const_array;

  typedef basic_document<default_value_ref_traits>                document;
  typedef const basic_document<default_const_value_ref_traits>    const_document;

  typedef typename document::allocator_type                       allocator;
};

typedef types<>::value_ref          value_ref;
typedef types<>::const_value_ref    const_value_ref;
typedef types<>::value              value;
typedef types<>::const_value        const_value;
typedef types<>::object             object;
typedef types<>::const_object       const_object;
typedef types<>::array              array;
typedef types<>::const_array        const_array;
typedef types<>::document           document;
typedef types<>::const_document     const_document;
typedef types<>::allocator          allocator;

}

#endif
