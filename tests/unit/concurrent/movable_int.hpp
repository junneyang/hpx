//  Copyright (c) 2016 John Biddiscombe
//  Copyright (c) 2016 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// (C) Copyright Ion Gaztanaga 2004-2013.

#ifndef HPX_CONTAINER_TEST_MOVABLE_INT_HEADER
#define HPX_CONTAINER_TEST_MOVABLE_INT_HEADER

#include <hpx/config.hpp>
#include <hpx/util/assert.hpp>

// #include <boost/container/detail/config_begin.hpp>
// #include <boost/container/detail/workaround.hpp>
// #include <boost/move/utility_core.hpp>
// #include <ostream>
// #include <climits>
// #include <boost/assert.hpp>

namespace test {

template <class T>
struct is_copyable;

template <>
struct is_copyable<int>
{
    static const bool value = true;
};

class movable_int
{
    HPX_MOVABLE_ONLY(movable_int);

public:
    static unsigned int count;

    movable_int()
      : m_int(0)
    {
        ++count;
    }

    explicit movable_int(int a)
      : m_int(a)
    {
        //Disallow INT_MIN
        HPX_ASSERT(this->m_int != INT_MIN);
        ++count;
    }

    movable_int(movable_int && mmi)
      : m_int(mmi.m_int)
    {
        mmi.m_int = 0;
        ++count;
    }

    movable_int &operator=(movable_int && mmi)
    {
        this->m_int = mmi.m_int;
        mmi.m_int = 0;
        return *this;
    }

    movable_int &operator=(int i)
    {
        this->m_int = i;
        HPX_ASSERT(this->m_int != INT_MIN);
        return *this;
    }

    ~movable_int()
    {
        //Double destructor called
        HPX_ASSERT(this->m_int != INT_MIN);
        this->m_int = INT_MIN;
        --count;
    }

    friend bool operator==(const movable_int &l, const movable_int &r)
    {
        return l.m_int == r.m_int;
    }

    friend bool operator!=(const movable_int &l, const movable_int &r)
    {
        return l.m_int != r.m_int;
    }

    friend bool operator<(const movable_int &l, const movable_int &r)
    {
        return l.m_int < r.m_int;
    }

    friend bool operator<=(const movable_int &l, const movable_int &r)
    {
        return l.m_int <= r.m_int;
    }

    friend bool operator>=(const movable_int &l, const movable_int &r)
    {
        return l.m_int >= r.m_int;
    }

    friend bool operator>(const movable_int &l, const movable_int &r)
    {
        return l.m_int > r.m_int;
    }

    int get_int() const
    {
        return m_int;
    }

    friend bool operator==(const movable_int &l, int r)
    {
        return l.get_int() == r;
    }

    friend bool operator==(int l, const movable_int &r)
    {
        return l == r.get_int();
    }

private:
    int m_int;
};

unsigned int movable_int::count = 0;

inline movable_int produce_movable_int()
{
    return movable_int();
}

template <class E, class T>
std::basic_ostream<E, T> &operator<<(
    std::basic_ostream<E, T> &os, movable_int const &p)

{
    os << p.get_int();
    return os;
}

template <>
struct is_copyable<movable_int>
{
    static const bool value = false;
};

class movable_and_copyable_int
{
public:
    static unsigned int count;

    movable_and_copyable_int()
      : m_int(0)
    {
        ++count;
    }

    explicit movable_and_copyable_int(int a)
      : m_int(a)
    {
        //Disallow INT_MIN
        HPX_ASSERT(this->m_int != INT_MIN);
        ++count;
    }

    movable_and_copyable_int(const movable_and_copyable_int &mmi)
      : m_int(mmi.m_int)
    {
        ++count;
    }

    movable_and_copyable_int(movable_and_copyable_int && mmi)
      : m_int(mmi.m_int)
    {
        mmi.m_int = 0;
        ++count;
    }

    ~movable_and_copyable_int()
    {
        //Double destructor called
        HPX_ASSERT(this->m_int != INT_MIN);
        this->m_int = INT_MIN;
        --count;
    }

    movable_and_copyable_int &operator=(movable_and_copyable_int const& mi)
    {
        this->m_int = mi.m_int;
        return *this;
    }

    movable_and_copyable_int &operator=(
        movable_and_copyable_int && mmi)
    {
        this->m_int = mmi.m_int;
        mmi.m_int = 0;
        return *this;
    }

    movable_and_copyable_int &operator=(int i)
    {
        this->m_int = i;
        HPX_ASSERT(this->m_int != INT_MIN);
        return *this;
    }

    friend bool operator==(
        const movable_and_copyable_int &l, const movable_and_copyable_int &r)
    {
        return l.m_int == r.m_int;
    }

    friend bool operator!=(
        const movable_and_copyable_int &l, const movable_and_copyable_int &r)
    {
        return l.m_int != r.m_int;
    }

    friend bool operator<(
        const movable_and_copyable_int &l, const movable_and_copyable_int &r)
    {
        return l.m_int < r.m_int;
    }

    friend bool operator<=(
        const movable_and_copyable_int &l, const movable_and_copyable_int &r)
    {
        return l.m_int <= r.m_int;
    }

    friend bool operator>=(
        const movable_and_copyable_int &l, const movable_and_copyable_int &r)
    {
        return l.m_int >= r.m_int;
    }

    friend bool operator>(
        const movable_and_copyable_int &l, const movable_and_copyable_int &r)
    {
        return l.m_int > r.m_int;
    }

    int get_int() const
    {
        return m_int;
    }

    friend bool operator==(const movable_and_copyable_int &l, int r)
    {
        return l.get_int() == r;
    }

    friend bool operator==(int l, const movable_and_copyable_int &r)
    {
        return l == r.get_int();
    }

private:
    int m_int;
};

unsigned int movable_and_copyable_int::count = 0;

inline movable_and_copyable_int produce_movable_and_copyable_int()
{
    return movable_and_copyable_int();
}

template <class E, class T>
std::basic_ostream<E, T> &operator<<(
    std::basic_ostream<E, T> &os, movable_and_copyable_int const &p)

{
    os << p.get_int();
    return os;
}

template <>
struct is_copyable<movable_and_copyable_int>
{
    static const bool value = true;
};

class copyable_int
{
public:
    static unsigned int count;

    copyable_int()
      : m_int(0)
    {
        ++count;
    }

    explicit copyable_int(int a)
      : m_int(a)
    {
        //Disallow INT_MIN
        HPX_ASSERT(this->m_int != INT_MIN);
        ++count;
    }

    copyable_int(const copyable_int &mmi)
      : m_int(mmi.m_int)
    {
        ++count;
    }

    copyable_int &operator=(int i)
    {
        this->m_int = i;
        HPX_ASSERT(this->m_int != INT_MIN);
        return *this;
    }

    copyable_int &operator=(const copyable_int &ci)
    {
        this->m_int = ci.m_int;
        HPX_ASSERT(this->m_int != INT_MIN);
        return *this;
    }

    ~copyable_int()
    {
        //Double destructor called
        HPX_ASSERT(this->m_int != INT_MIN);
        this->m_int = INT_MIN;
        --count;
    }

    friend bool operator==(const copyable_int &l, const copyable_int &r)
    {
        return l.m_int == r.m_int;
    }

    friend bool operator!=(const copyable_int &l, const copyable_int &r)
    {
        return l.m_int != r.m_int;
    }

    friend bool operator<(const copyable_int &l, const copyable_int &r)
    {
        return l.m_int < r.m_int;
    }

    friend bool operator<=(const copyable_int &l, const copyable_int &r)
    {
        return l.m_int <= r.m_int;
    }

    friend bool operator>=(const copyable_int &l, const copyable_int &r)
    {
        return l.m_int >= r.m_int;
    }

    friend bool operator>(const copyable_int &l, const copyable_int &r)
    {
        return l.m_int > r.m_int;
    }

    int get_int() const
    {
        return m_int;
    }

    friend bool operator==(const copyable_int &l, int r)
    {
        return l.get_int() == r;
    }

    friend bool operator==(int l, const copyable_int &r)
    {
        return l == r.get_int();
    }

private:
    int m_int;
};

unsigned int copyable_int::count = 0;

inline copyable_int produce_copyable_int()
{
    return copyable_int();
}

template <class E, class T>
std::basic_ostream<E, T> &operator<<(
    std::basic_ostream<E, T> &os, copyable_int const &p)

{
    os << p.get_int();
    return os;
}

template <>
struct is_copyable<copyable_int>
{
    static const bool value = true;
};

class non_copymovable_int
{
    HPX_NON_COPYABLE(non_copymovable_int);

public:
    static unsigned int count;

    non_copymovable_int()
      : m_int(0)
    {
        ++count;
    }

    explicit non_copymovable_int(int a)
      : m_int(a)
    {
        ++count;
    }

    ~non_copymovable_int()
    {
        m_int = 0;
        --count;
    }

    bool operator==(const non_copymovable_int &mi) const
    {
        return this->m_int == mi.m_int;
    }

    bool operator!=(const non_copymovable_int &mi) const
    {
        return this->m_int != mi.m_int;
    }

    bool operator<(const non_copymovable_int &mi) const
    {
        return this->m_int < mi.m_int;
    }

    bool operator<=(const non_copymovable_int &mi) const
    {
        return this->m_int <= mi.m_int;
    }

    bool operator>=(const non_copymovable_int &mi) const
    {
        return this->m_int >= mi.m_int;
    }

    bool operator>(const non_copymovable_int &mi) const
    {
        return this->m_int > mi.m_int;
    }

    int get_int() const
    {
        return m_int;
    }

    friend bool operator==(const non_copymovable_int &l, int r)
    {
        return l.get_int() == r;
    }

    friend bool operator==(int l, const non_copymovable_int &r)
    {
        return l == r.get_int();
    }

private:
    int m_int;
};

unsigned int non_copymovable_int::count = 0;

template <class T>
struct life_count
{
    static unsigned check(unsigned)
    {
        return true;
    }
};

template <>
struct life_count<movable_int>
{
    static unsigned check(unsigned c)
    {
        return c == movable_int::count;
    }
};

template <>
struct life_count<copyable_int>
{
    static unsigned check(unsigned c)
    {
        return c == copyable_int::count;
    }
};

template <>
struct life_count<movable_and_copyable_int>
{
    static unsigned check(unsigned c)
    {
        return c == movable_and_copyable_int::count;
    }
};

template <>
struct life_count<non_copymovable_int>
{
    static unsigned check(unsigned c)
    {
        return c == non_copymovable_int::count;
    }
};

}

// #include <boost/container/detail/config_end.hpp>

#endif
