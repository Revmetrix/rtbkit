/* lightweight_hash_test.cc
   Jeremy Barnes, 10 December 2009
   Copyright (c) 2009 Jeremy Barnes.  All rights reserved.

   Test program for lightweight hash.
*/

#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include "utils/lightweight_hash.h"
#include "utils/string_functions.h"
#include <boost/test/unit_test.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <boost/tuple/tuple.hpp>
#include "arch/exception_handler.h"
#include "arch/demangle.h"
#include <set>
#include "live_counting_obj.h"

using namespace ML;
using namespace std;

BOOST_AUTO_TEST_CASE(test1)
{
    Lightweight_Hash<int, int> h;
    const Lightweight_Hash<int, int> & ch = h;

    BOOST_CHECK_EQUAL(h.empty(), true);
    BOOST_CHECK_EQUAL(h.size(), 0);
    BOOST_CHECK_EQUAL(h.begin(), h.end());
    BOOST_CHECK_EQUAL(ch.begin(), ch.end());
    BOOST_CHECK_EQUAL(h.begin(), ch.end());

    h.reserve(16);
    BOOST_CHECK_EQUAL(h.capacity(), 16);
    BOOST_CHECK_EQUAL(h.size(), 0);
    BOOST_CHECK_EQUAL(h.begin(), h.end());
    BOOST_CHECK_EQUAL(ch.begin(), ch.end());
    BOOST_CHECK_EQUAL(h.begin(), ch.end());

    h[1] = 1;

    BOOST_CHECK_EQUAL(h[1], 1);
    BOOST_CHECK_EQUAL(h.size(), 1);
    BOOST_CHECK(h.begin() != h.end());
    BOOST_CHECK_EQUAL(h.begin()->first, 1);
    BOOST_CHECK_EQUAL(h.begin()->second, 1);
    BOOST_CHECK_EQUAL(boost::next(h.begin()), ch.end());
    BOOST_CHECK_EQUAL(h.begin(), boost::prior(ch.end()));

    h[2] = 2;

    BOOST_CHECK_EQUAL(h[1], 1);
    BOOST_CHECK_EQUAL(h[2], 2);
    BOOST_CHECK_EQUAL(h.size(), 2);
    BOOST_CHECK(h.capacity() >= 2);

    h.reserve(1024);
    BOOST_CHECK_EQUAL(h[1], 1);
    BOOST_CHECK_EQUAL(h[2], 2);
    BOOST_CHECK_EQUAL(h.size(), 2);
    BOOST_CHECK(h.capacity() >= 2);

    BOOST_CHECK_EQUAL(++++h.begin(), h.end());
}
