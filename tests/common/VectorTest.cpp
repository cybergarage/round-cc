/******************************************************************
*
* uHTTP for C++
*
* Copyright (C) Satoshi Konno 2002-2013
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <boost/test/unit_test.hpp>

#include <round/common/Vector.h>

using namespace Round;

BOOST_AUTO_TEST_SUITE(common)

class TestVectorObject {
public:
  TestVectorObject() {
  }
};

class TestVectorList : public Vector<TestVectorObject>  {
public:
  TestVectorList() {
  }
};

BOOST_AUTO_TEST_CASE(VectorTest)
{
  const size_t TEST_VECTOR_OBJECT_NUM = 10;
  
  TestVectorList vectorObjectList;
  BOOST_CHECK_EQUAL(vectorObjectList.size(), 0);

  BOOST_CHECK_EQUAL(vectorObjectList.add(NULL), false);
  BOOST_CHECK_EQUAL(vectorObjectList.remove(NULL), false);
  BOOST_CHECK_EQUAL(vectorObjectList.insertAt(NULL, 0), false);
  BOOST_CHECK_EQUAL(vectorObjectList.indexOf(NULL), -1);
  
  TestVectorObject *vectorObject[TEST_VECTOR_OBJECT_NUM];
  for (size_t n=0; n<TEST_VECTOR_OBJECT_NUM; n++) {
    vectorObject[n] = new TestVectorObject();
  }

  for (size_t n=0; n<TEST_VECTOR_OBJECT_NUM; n++) {
    BOOST_CHECK_EQUAL(vectorObjectList.size(), n);
    BOOST_CHECK_EQUAL(vectorObjectList.indexOf(vectorObject[n]), -1);
    BOOST_CHECK_EQUAL(vectorObjectList.exists(vectorObject[n]), false);
    vectorObjectList.add(vectorObject[n]);
    BOOST_CHECK_EQUAL(vectorObjectList.size(), (n+1));
    BOOST_CHECK_EQUAL(vectorObjectList.indexOf(vectorObject[n]), n);
    BOOST_CHECK_EQUAL(vectorObjectList.exists(vectorObject[n]), true);
  }

  for (size_t n=0; n<TEST_VECTOR_OBJECT_NUM; n++) {
    BOOST_CHECK_EQUAL(vectorObjectList.size(), (TEST_VECTOR_OBJECT_NUM - n));
    BOOST_CHECK_EQUAL(vectorObjectList.indexOf(vectorObject[n]), 0);
    BOOST_CHECK_EQUAL(vectorObjectList.exists(vectorObject[n]), true);
    vectorObjectList.remove(vectorObject[n]);
    BOOST_CHECK_EQUAL(vectorObjectList.size(), (TEST_VECTOR_OBJECT_NUM - (n+1)));
    BOOST_CHECK_EQUAL(vectorObjectList.indexOf(vectorObject[n]), -1);
    BOOST_CHECK_EQUAL(vectorObjectList.exists(vectorObject[n]), false);
  }

  BOOST_CHECK_EQUAL(vectorObjectList.size(), 0);
}

BOOST_AUTO_TEST_SUITE_END()
