/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2012
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <boost/test/unit_test.hpp>
#include <complex>

#include <round/common/ConsistentHash.h>

using namespace std;
using namespace Round;

class TestConsistentHashObject : public ConsistentHashObject {
public:
  std::string id;
  
public:
  TestConsistentHashObject(int idValue) {
    stringstream oss;
    oss << idValue;
    this->id = oss.str();
  }
  
  const char *getHashSeed(std::string *seedString) const {
    *seedString = "";
    return seedString->c_str();
  }
  
  bool getHashCode(std::string *hashCode) const {
    *hashCode = this->id;
    return true;
  }
};

class TestConsistentHashNode : public ConsistentHashNode {
 public:
  std::string id;

 public:
  TestConsistentHashNode(int idValue) {
    ostringstream oss;
    oss << idValue;
    this->id = oss.str();
  }

  const char *getHashSeed(std::string *seedString) const {
    *seedString = "";
    return seedString->c_str();
  }

  bool getHashCode(std::string *hashCode) const {
    *hashCode = this->id;
    return true;
  }
};

class TestConsistentHashGraph : public ConsistentHashGraph {
 public:
  TestConsistentHashGraph() {
  }

  ConsistentHashNode *getHandleNode(int idValue) {
    TestConsistentHashObject hashObject(idValue);
    return ConsistentHashGraph::getHandleNode(hashObject);
  }
};

BOOST_AUTO_TEST_CASE(RoundConsistentHashGraphAddSameNodeTest) {
  TestConsistentHashGraph coHashGraph;
  BOOST_CHECK_EQUAL(coHashGraph.size(), 0);
  
  TestConsistentHashNode *cosNode = new TestConsistentHashNode(0);
  
  BOOST_CHECK_EQUAL(coHashGraph.hasNode(cosNode), false);
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(cosNode), -1);
  BOOST_CHECK_EQUAL(coHashGraph.size(), 0);
  
  BOOST_CHECK_EQUAL(coHashGraph.addNode(cosNode), true);
  BOOST_CHECK_EQUAL(coHashGraph.hasNode(cosNode), true);
  BOOST_CHECK_EQUAL(coHashGraph.size(), 1);

  BOOST_CHECK_EQUAL(coHashGraph.addNode(cosNode), false);
  BOOST_CHECK_EQUAL(coHashGraph.hasNode(cosNode), true);
  BOOST_CHECK_EQUAL(coHashGraph.size(), 1);
  
  delete cosNode;
}

BOOST_AUTO_TEST_CASE(RoundConsistentHashGraphAddTest) {
  const int conNodeCount = 9;
  TestConsistentHashGraph coHashGraph;
  TestConsistentHashNode *cosNodes[conNodeCount];
  
  for (int n = 0; n < conNodeCount; n++) {
    cosNodes[n] = new TestConsistentHashNode(n+1);
  }

  BOOST_CHECK_EQUAL(coHashGraph.size(), 0);
  for (int n = 0; n < conNodeCount; n++) {
    BOOST_CHECK_EQUAL(coHashGraph.hasNode(cosNodes[n]), false);
    BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(cosNodes[n]), -1);
    
    BOOST_CHECK(coHashGraph.addNode(cosNodes[n]));
    BOOST_CHECK_EQUAL(coHashGraph.hasNode(cosNodes[n]), true);
    BOOST_CHECK_EQUAL(coHashGraph.size(), (n+1));
    BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(cosNodes[n]), n);
  }

  coHashGraph.clear();
  BOOST_CHECK_EQUAL(coHashGraph.size(), 0);
  for (int n=(conNodeCount-1); 0<=n; n--) {
    BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(cosNodes[n]), -1);
    coHashGraph.addNode(cosNodes[n]);
  }
  BOOST_CHECK_EQUAL(coHashGraph.size(), conNodeCount);
  for (int n = 0; n < conNodeCount; n++) {
    BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(cosNodes[n]), n);
  }

  coHashGraph.clear();
  BOOST_CHECK_EQUAL(coHashGraph.size(), 0);

  for (int n = 0; n < conNodeCount; n++) {
    delete cosNodes[n];
  }
}

BOOST_AUTO_TEST_CASE(RoundConsistentHashGraphEqualsTest) {
  const int conNodeCount = 9;
  TestConsistentHashGraph coHashGraph;
  TestConsistentHashNode *cosNodes[conNodeCount];
  
  for (int n = 0; n < conNodeCount; n++) {
    cosNodes[n] = new TestConsistentHashNode(n+1);
    BOOST_CHECK(coHashGraph.addNode(cosNodes[n]));
  }
  
  for (int i = 0; i < conNodeCount; i++) {
    for (int j = 0; j < conNodeCount; j++) {
      BOOST_CHECK_EQUAL(cosNodes[i]->equals(cosNodes[j]), ((i == j) ? true : false));
    }
  }
  
  for (int n = 0; n < conNodeCount; n++) {
    delete cosNodes[n];
  }
}

BOOST_AUTO_TEST_CASE(RoundConsistentHashGraphHandleTest) {
  const int conNodeCount = 4;
  TestConsistentHashGraph coHashGraph;
  TestConsistentHashNode *cosNodes[conNodeCount];

  TestConsistentHashNode *cosNode2 = cosNodes[0] = new TestConsistentHashNode(2);
  TestConsistentHashNode *cosNode4 = cosNodes[1] = new TestConsistentHashNode(4);
  TestConsistentHashNode *cosNode6 = cosNodes[2] = new TestConsistentHashNode(6);
  TestConsistentHashNode *cosNode8 = cosNodes[3] = new TestConsistentHashNode(8);

  for (int n = 0; n < conNodeCount; n++)
    coHashGraph.addNode(cosNodes[n]);

  // 2-4-6-8
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(0)), coHashGraph.getNodeIndex(cosNode8));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(1)), coHashGraph.getNodeIndex(cosNode8));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(2)), coHashGraph.getNodeIndex(cosNode2));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(3)), coHashGraph.getNodeIndex(cosNode2));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(4)), coHashGraph.getNodeIndex(cosNode4));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(5)), coHashGraph.getNodeIndex(cosNode4));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(6)), coHashGraph.getNodeIndex(cosNode6));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(7)), coHashGraph.getNodeIndex(cosNode6));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(8)), coHashGraph.getNodeIndex(cosNode8));

  // 4-6-8
  coHashGraph.removeNode(cosNode2);
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(0)), coHashGraph.getNodeIndex(cosNode8));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(1)), coHashGraph.getNodeIndex(cosNode8));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(2)), coHashGraph.getNodeIndex(cosNode8));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(3)), coHashGraph.getNodeIndex(cosNode8));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(4)), coHashGraph.getNodeIndex(cosNode4));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(5)), coHashGraph.getNodeIndex(cosNode4));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(6)), coHashGraph.getNodeIndex(cosNode6));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(7)), coHashGraph.getNodeIndex(cosNode6));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(8)), coHashGraph.getNodeIndex(cosNode8));

  // 2-4-6-8
  coHashGraph.addNode(cosNode2);
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(0)), coHashGraph.getNodeIndex(cosNode8));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(1)), coHashGraph.getNodeIndex(cosNode8));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(2)), coHashGraph.getNodeIndex(cosNode2));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(3)), coHashGraph.getNodeIndex(cosNode2));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(4)), coHashGraph.getNodeIndex(cosNode4));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(5)), coHashGraph.getNodeIndex(cosNode4));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(6)), coHashGraph.getNodeIndex(cosNode6));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(7)), coHashGraph.getNodeIndex(cosNode6));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(8)), coHashGraph.getNodeIndex(cosNode8));
  
  // 2-6-8
  coHashGraph.removeNode(cosNode4);
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(0)), coHashGraph.getNodeIndex(cosNode8));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(1)), coHashGraph.getNodeIndex(cosNode8));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(2)), coHashGraph.getNodeIndex(cosNode2));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(3)), coHashGraph.getNodeIndex(cosNode2));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(4)), coHashGraph.getNodeIndex(cosNode2));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(5)), coHashGraph.getNodeIndex(cosNode2));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(6)), coHashGraph.getNodeIndex(cosNode6));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(7)), coHashGraph.getNodeIndex(cosNode6));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(8)), coHashGraph.getNodeIndex(cosNode8));

  // 2-4-6-8
  coHashGraph.addNode(cosNode4);
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(0)), coHashGraph.getNodeIndex(cosNode8));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(1)), coHashGraph.getNodeIndex(cosNode8));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(2)), coHashGraph.getNodeIndex(cosNode2));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(3)), coHashGraph.getNodeIndex(cosNode2));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(4)), coHashGraph.getNodeIndex(cosNode4));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(5)), coHashGraph.getNodeIndex(cosNode4));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(6)), coHashGraph.getNodeIndex(cosNode6));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(7)), coHashGraph.getNodeIndex(cosNode6));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(8)), coHashGraph.getNodeIndex(cosNode8));

  // 2-4-8
  coHashGraph.removeNode(cosNode6);
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(0)), coHashGraph.getNodeIndex(cosNode8));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(1)), coHashGraph.getNodeIndex(cosNode8));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(2)), coHashGraph.getNodeIndex(cosNode2));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(3)), coHashGraph.getNodeIndex(cosNode2));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(4)), coHashGraph.getNodeIndex(cosNode4));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(5)), coHashGraph.getNodeIndex(cosNode4));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(6)), coHashGraph.getNodeIndex(cosNode4));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(7)), coHashGraph.getNodeIndex(cosNode4));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(8)), coHashGraph.getNodeIndex(cosNode8));

  // 2-4-6-8
  coHashGraph.addNode(cosNode6);
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(0)), coHashGraph.getNodeIndex(cosNode8));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(1)), coHashGraph.getNodeIndex(cosNode8));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(2)), coHashGraph.getNodeIndex(cosNode2));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(3)), coHashGraph.getNodeIndex(cosNode2));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(4)), coHashGraph.getNodeIndex(cosNode4));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(5)), coHashGraph.getNodeIndex(cosNode4));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(6)), coHashGraph.getNodeIndex(cosNode6));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(7)), coHashGraph.getNodeIndex(cosNode6));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(8)), coHashGraph.getNodeIndex(cosNode8));

  // 2-4-6
  coHashGraph.removeNode(cosNode8);
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(0)), coHashGraph.getNodeIndex(cosNode6));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(1)), coHashGraph.getNodeIndex(cosNode6));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(2)), coHashGraph.getNodeIndex(cosNode2));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(3)), coHashGraph.getNodeIndex(cosNode2));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(4)), coHashGraph.getNodeIndex(cosNode4));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(5)), coHashGraph.getNodeIndex(cosNode4));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(6)), coHashGraph.getNodeIndex(cosNode6));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(7)), coHashGraph.getNodeIndex(cosNode6));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(8)), coHashGraph.getNodeIndex(cosNode6));

  // 2-4-6-8
  coHashGraph.addNode(cosNode8);
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(0)), coHashGraph.getNodeIndex(cosNode8));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(1)), coHashGraph.getNodeIndex(cosNode8));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(2)), coHashGraph.getNodeIndex(cosNode2));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(3)), coHashGraph.getNodeIndex(cosNode2));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(4)), coHashGraph.getNodeIndex(cosNode4));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(5)), coHashGraph.getNodeIndex(cosNode4));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(6)), coHashGraph.getNodeIndex(cosNode6));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(7)), coHashGraph.getNodeIndex(cosNode6));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(8)), coHashGraph.getNodeIndex(cosNode8));

  // 2-6
  coHashGraph.removeNode(cosNode4);
  coHashGraph.removeNode(cosNode8);
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(0)), coHashGraph.getNodeIndex(cosNode6));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(1)), coHashGraph.getNodeIndex(cosNode6));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(2)), coHashGraph.getNodeIndex(cosNode2));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(3)), coHashGraph.getNodeIndex(cosNode2));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(4)), coHashGraph.getNodeIndex(cosNode2));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(5)), coHashGraph.getNodeIndex(cosNode2));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(6)), coHashGraph.getNodeIndex(cosNode6));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(7)), coHashGraph.getNodeIndex(cosNode6));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(8)), coHashGraph.getNodeIndex(cosNode6));

  // 2-4-6-8
  coHashGraph.addNode(cosNode4);
  coHashGraph.addNode(cosNode8);
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(0)), coHashGraph.getNodeIndex(cosNode8));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(1)), coHashGraph.getNodeIndex(cosNode8));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(2)), coHashGraph.getNodeIndex(cosNode2));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(3)), coHashGraph.getNodeIndex(cosNode2));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(4)), coHashGraph.getNodeIndex(cosNode4));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(5)), coHashGraph.getNodeIndex(cosNode4));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(6)), coHashGraph.getNodeIndex(cosNode6));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(7)), coHashGraph.getNodeIndex(cosNode6));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(8)), coHashGraph.getNodeIndex(cosNode8));

  // 4-8
  coHashGraph.removeNode(cosNode2);
  coHashGraph.removeNode(cosNode6);
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(0)), coHashGraph.getNodeIndex(cosNode8));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(1)), coHashGraph.getNodeIndex(cosNode8));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(2)), coHashGraph.getNodeIndex(cosNode8));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(3)), coHashGraph.getNodeIndex(cosNode8));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(4)), coHashGraph.getNodeIndex(cosNode4));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(5)), coHashGraph.getNodeIndex(cosNode4));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(6)), coHashGraph.getNodeIndex(cosNode4));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(7)), coHashGraph.getNodeIndex(cosNode4));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(8)), coHashGraph.getNodeIndex(cosNode8));

  // 2-4-6-8
  coHashGraph.addNode(cosNode2);
  coHashGraph.addNode(cosNode6);
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(0)), coHashGraph.getNodeIndex(cosNode8));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(1)), coHashGraph.getNodeIndex(cosNode8));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(2)), coHashGraph.getNodeIndex(cosNode2));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(3)), coHashGraph.getNodeIndex(cosNode2));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(4)), coHashGraph.getNodeIndex(cosNode4));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(5)), coHashGraph.getNodeIndex(cosNode4));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(6)), coHashGraph.getNodeIndex(cosNode6));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(7)), coHashGraph.getNodeIndex(cosNode6));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(8)), coHashGraph.getNodeIndex(cosNode8));


  // 2
  coHashGraph.removeNode(cosNode4);
  coHashGraph.removeNode(cosNode6);
  coHashGraph.removeNode(cosNode8);
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(0)), coHashGraph.getNodeIndex(cosNode2));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(1)), coHashGraph.getNodeIndex(cosNode2));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(2)), coHashGraph.getNodeIndex(cosNode2));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(3)), coHashGraph.getNodeIndex(cosNode2));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(4)), coHashGraph.getNodeIndex(cosNode2));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(5)), coHashGraph.getNodeIndex(cosNode2));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(6)), coHashGraph.getNodeIndex(cosNode2));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(7)), coHashGraph.getNodeIndex(cosNode2));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(8)), coHashGraph.getNodeIndex(cosNode2));

  // 2-4-6-8
  coHashGraph.addNode(cosNode4);
  coHashGraph.addNode(cosNode6);
  coHashGraph.addNode(cosNode8);
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(0)), coHashGraph.getNodeIndex(cosNode8));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(1)), coHashGraph.getNodeIndex(cosNode8));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(2)), coHashGraph.getNodeIndex(cosNode2));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(3)), coHashGraph.getNodeIndex(cosNode2));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(4)), coHashGraph.getNodeIndex(cosNode4));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(5)), coHashGraph.getNodeIndex(cosNode4));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(6)), coHashGraph.getNodeIndex(cosNode6));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(7)), coHashGraph.getNodeIndex(cosNode6));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(8)), coHashGraph.getNodeIndex(cosNode8));

  // 8
  coHashGraph.removeNode(cosNode2);
  coHashGraph.removeNode(cosNode4);
  coHashGraph.removeNode(cosNode6);
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(0)), coHashGraph.getNodeIndex(cosNode8));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(1)), coHashGraph.getNodeIndex(cosNode8));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(2)), coHashGraph.getNodeIndex(cosNode8));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(3)), coHashGraph.getNodeIndex(cosNode8));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(4)), coHashGraph.getNodeIndex(cosNode8));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(5)), coHashGraph.getNodeIndex(cosNode8));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(6)), coHashGraph.getNodeIndex(cosNode8));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(7)), coHashGraph.getNodeIndex(cosNode8));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(8)), coHashGraph.getNodeIndex(cosNode8));

  // 2-4-6-8
  coHashGraph.addNode(cosNode2);
  coHashGraph.addNode(cosNode4);
  coHashGraph.addNode(cosNode6);
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(0)), coHashGraph.getNodeIndex(cosNode8));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(1)), coHashGraph.getNodeIndex(cosNode8));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(2)), coHashGraph.getNodeIndex(cosNode2));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(3)), coHashGraph.getNodeIndex(cosNode2));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(4)), coHashGraph.getNodeIndex(cosNode4));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(5)), coHashGraph.getNodeIndex(cosNode4));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(6)), coHashGraph.getNodeIndex(cosNode6));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(7)), coHashGraph.getNodeIndex(cosNode6));
  BOOST_CHECK_EQUAL(coHashGraph.getNodeIndex(coHashGraph.getHandleNode(8)), coHashGraph.getNodeIndex(cosNode8));

  for (int n = 0; n < conNodeCount; n++) {
    delete cosNodes[n];
  }
}

BOOST_AUTO_TEST_CASE(RoundConsistentHashGraphOffsetNodeTest) {
  const int conNodeCount = 9;
  TestConsistentHashGraph coHashGraph;
  TestConsistentHashNode *cosNodes[conNodeCount];

  for (int n = 0; n < conNodeCount; n++) {
    cosNodes[n] = new TestConsistentHashNode(n+1);
    coHashGraph.addNode(cosNodes[n]);
  }

  for (int baseOffset = 0; baseOffset <= conNodeCount; baseOffset+=conNodeCount) {
    // +1
    for (int n = 0; n < (conNodeCount-1); n++) {
      BOOST_CHECK_EQUAL(coHashGraph.getNextNode(cosNodes[n]), cosNodes[n+1]);
      BOOST_CHECK_EQUAL(coHashGraph.getOffsetNode(cosNodes[n], (+1 + baseOffset)), cosNodes[n+1]);
    }
    BOOST_CHECK_EQUAL(coHashGraph.getNextNode(cosNodes[conNodeCount -1]), cosNodes[0]);
    BOOST_CHECK_EQUAL(coHashGraph.getOffsetNode(cosNodes[conNodeCount -1], (+1 + baseOffset)), cosNodes[0]);

    // (+2 +  baseOffset)
    for (int n = 0; n < (conNodeCount -2); n++) {
      BOOST_CHECK_EQUAL(coHashGraph.getOffsetNode(cosNodes[n], (+2 +  baseOffset)), cosNodes[n+2]);
    }
    BOOST_CHECK_EQUAL(coHashGraph.getOffsetNode(cosNodes[conNodeCount-2], (+2 +  baseOffset)), cosNodes[0]);
    BOOST_CHECK_EQUAL(coHashGraph.getOffsetNode(cosNodes[conNodeCount-1], (+2 +  baseOffset)), cosNodes[1]);

    // (+3+  baseOffset)
    for (int n = 0; n < (conNodeCount -3); n++) {
      BOOST_CHECK_EQUAL(coHashGraph.getOffsetNode(cosNodes[n], (+3 +  baseOffset)), cosNodes[n+3]);
    }
    BOOST_CHECK_EQUAL(coHashGraph.getOffsetNode(cosNodes[conNodeCount - 3], (+3+  baseOffset)), cosNodes[0]);
    BOOST_CHECK_EQUAL(coHashGraph.getOffsetNode(cosNodes[conNodeCount - 2], (+3+  baseOffset)), cosNodes[1]);
    BOOST_CHECK_EQUAL(coHashGraph.getOffsetNode(cosNodes[conNodeCount - 1], (+3+  baseOffset)), cosNodes[2]);
    
    // (-1 -  baseOffset)
    BOOST_CHECK_EQUAL(coHashGraph.getPrevNode(cosNodes[0]), cosNodes[conNodeCount -1]);
    BOOST_CHECK_EQUAL(coHashGraph.getOffsetNode(cosNodes[0], (-1 -  baseOffset)), cosNodes[conNodeCount-1]);
    for (int n=1; n < conNodeCount; n++) {
      BOOST_CHECK_EQUAL(coHashGraph.getPrevNode(cosNodes[n]), cosNodes[n-1]);
      BOOST_CHECK_EQUAL(coHashGraph.getOffsetNode(cosNodes[n], (-1 -  baseOffset)), cosNodes[n-1]);
    }

    // (-2 -  baseOffset)
    BOOST_CHECK_EQUAL(coHashGraph.getOffsetNode(cosNodes[0], (-2 -  baseOffset)), cosNodes[conNodeCount-2]);
    BOOST_CHECK_EQUAL(coHashGraph.getOffsetNode(cosNodes[1], (-2 -  baseOffset)), cosNodes[conNodeCount-1]);
    for (int n=2; n < conNodeCount; n++) {
      BOOST_CHECK_EQUAL(coHashGraph.getOffsetNode(cosNodes[n], (-2 -  baseOffset)), cosNodes[n-2]);
    }

    // (-3 -  baseOffset)
    BOOST_CHECK_EQUAL(coHashGraph.getOffsetNode(cosNodes[0], (-3 -  baseOffset)), cosNodes[conNodeCount-3]);
    BOOST_CHECK_EQUAL(coHashGraph.getOffsetNode(cosNodes[1], (-3 -  baseOffset)), cosNodes[conNodeCount-2]);
    BOOST_CHECK_EQUAL(coHashGraph.getOffsetNode(cosNodes[2], (-3 -  baseOffset)), cosNodes[conNodeCount-1]);
    for (int n=3; n < conNodeCount; n++) {
      BOOST_CHECK_EQUAL(coHashGraph.getOffsetNode(cosNodes[n], (-3 -  baseOffset)), cosNodes[n-3]);
    }
  }

  for (int n = 0; n < conNodeCount; n++) {
    delete cosNodes[n];
  }
}

BOOST_AUTO_TEST_CASE(RoundConsistentHashGraphFowardDistanceTest) {
  const int conNodeCount = 9;
  TestConsistentHashGraph coHashGraph;
  TestConsistentHashNode *cosNodes[conNodeCount];
  
  for (int n = 0; n < conNodeCount; n++) {
    cosNodes[n] = new TestConsistentHashNode(n+1);
    coHashGraph.addNode(cosNodes[n]);
  }
  
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[0], cosNodes[0]),  0);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[0], cosNodes[1]),  1);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[0], cosNodes[2]),  2);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[0], cosNodes[3]),  3);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[0], cosNodes[4]),  4);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[0], cosNodes[5]),  5);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[0], cosNodes[6]),  6);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[0], cosNodes[7]),  7);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[0], cosNodes[8]),  8);
  
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[1], cosNodes[0]),  8);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[1], cosNodes[1]),  0);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[1], cosNodes[2]),  1);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[1], cosNodes[3]),  2);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[1], cosNodes[4]),  3);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[1], cosNodes[5]),  4);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[1], cosNodes[6]),  5);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[1], cosNodes[7]),  6);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[1], cosNodes[8]),  7);
  
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[2], cosNodes[0]),  7);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[2], cosNodes[1]),  8);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[2], cosNodes[2]),  0);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[2], cosNodes[3]),  1);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[2], cosNodes[4]),  2);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[2], cosNodes[5]),  3);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[2], cosNodes[6]),  4);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[2], cosNodes[7]),  5);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[2], cosNodes[8]),  6);
  
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[3], cosNodes[0]),  6);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[3], cosNodes[1]),  7);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[3], cosNodes[2]),  8);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[3], cosNodes[3]),  0);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[3], cosNodes[4]),  1);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[3], cosNodes[5]),  2);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[3], cosNodes[6]),  3);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[3], cosNodes[7]),  4);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[3], cosNodes[8]),  5);
  
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[4], cosNodes[0]),  5);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[4], cosNodes[1]),  6);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[4], cosNodes[2]),  7);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[4], cosNodes[3]),  8);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[4], cosNodes[4]),  0);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[4], cosNodes[5]),  1);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[4], cosNodes[6]),  2);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[4], cosNodes[7]),  3);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[4], cosNodes[8]),  4);
  
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[5], cosNodes[0]),  4);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[5], cosNodes[1]),  5);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[5], cosNodes[2]),  6);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[5], cosNodes[3]),  7);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[5], cosNodes[4]),  8);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[5], cosNodes[5]),  0);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[5], cosNodes[6]),  1);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[5], cosNodes[7]),  2);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[5], cosNodes[8]),  3);
  
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[6], cosNodes[0]),  3);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[6], cosNodes[1]),  4);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[6], cosNodes[2]),  5);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[6], cosNodes[3]),  6);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[6], cosNodes[4]),  7);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[6], cosNodes[5]),  8);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[6], cosNodes[6]),  0);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[6], cosNodes[7]),  1);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[6], cosNodes[8]),  2);
  
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[7], cosNodes[0]),  2);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[7], cosNodes[1]),  3);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[7], cosNodes[2]),  4);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[7], cosNodes[3]),  5);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[7], cosNodes[4]),  6);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[7], cosNodes[5]),  7);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[7], cosNodes[6]),  8);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[7], cosNodes[7]),  0);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[7], cosNodes[8]),  1);
  
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[8], cosNodes[0]),  1);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[8], cosNodes[1]),  2);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[8], cosNodes[2]),  3);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[8], cosNodes[3]),  4);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[8], cosNodes[4]),  5);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[8], cosNodes[5]),  6);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[8], cosNodes[6]),  7);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[8], cosNodes[7]),  8);
  BOOST_CHECK_EQUAL(coHashGraph.getForwardNodeDistance(cosNodes[8], cosNodes[8]),  0);
  
  for (int n = 0; n < conNodeCount; n++) {
    delete cosNodes[n];
  }
}

BOOST_AUTO_TEST_CASE(RoundConsistentHashGraphBackfowardDistanceTest) {
  const int conNodeCount = 9;
  TestConsistentHashGraph coHashGraph;
  TestConsistentHashNode *cosNodes[conNodeCount];
  
  for (int n = 0; n < conNodeCount; n++) {
    cosNodes[n] = new TestConsistentHashNode(n+1);
    coHashGraph.addNode(cosNodes[n]);
  }
  
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[0], cosNodes[0]),  0);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[0], cosNodes[1]), -8);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[0], cosNodes[2]), -7);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[0], cosNodes[3]), -6);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[0], cosNodes[4]), -5);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[0], cosNodes[5]), -4);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[0], cosNodes[6]), -3);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[0], cosNodes[7]), -2);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[0], cosNodes[8]), -1);
  
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[1], cosNodes[0]), -1);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[1], cosNodes[1]),  0);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[1], cosNodes[2]), -8);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[1], cosNodes[3]), -7);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[1], cosNodes[4]), -6);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[1], cosNodes[5]), -5);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[1], cosNodes[6]), -4);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[1], cosNodes[7]), -3);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[1], cosNodes[8]), -2);
  
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[2], cosNodes[0]), -2);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[2], cosNodes[1]), -1);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[2], cosNodes[2]),  0);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[2], cosNodes[3]), -8);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[2], cosNodes[4]), -7);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[2], cosNodes[5]), -6);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[2], cosNodes[6]), -5);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[2], cosNodes[7]), -4);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[2], cosNodes[8]), -3);
  
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[3], cosNodes[0]), -3);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[3], cosNodes[1]), -2);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[3], cosNodes[2]), -1);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[3], cosNodes[3]),  0);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[3], cosNodes[4]), -8);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[3], cosNodes[5]), -7);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[3], cosNodes[6]), -6);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[3], cosNodes[7]), -5);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[3], cosNodes[8]), -4);
  
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[4], cosNodes[0]), -4);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[4], cosNodes[1]), -3);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[4], cosNodes[2]), -2);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[4], cosNodes[3]), -1);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[4], cosNodes[4]),  0);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[4], cosNodes[5]), -8);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[4], cosNodes[6]), -7);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[4], cosNodes[7]), -6);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[4], cosNodes[8]), -5);
  
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[5], cosNodes[0]), -5);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[5], cosNodes[1]), -4);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[5], cosNodes[2]), -3);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[5], cosNodes[3]), -2);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[5], cosNodes[4]), -1);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[5], cosNodes[5]),  0);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[5], cosNodes[6]), -8);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[5], cosNodes[7]), -7);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[5], cosNodes[8]), -6);
  
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[6], cosNodes[0]), -6);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[6], cosNodes[1]), -5);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[6], cosNodes[2]), -4);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[6], cosNodes[3]), -3);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[6], cosNodes[4]), -2);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[6], cosNodes[5]), -1);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[6], cosNodes[6]),  0);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[6], cosNodes[7]), -8);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[6], cosNodes[8]), -7);
  
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[7], cosNodes[0]), -7);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[7], cosNodes[1]), -6);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[7], cosNodes[2]), -5);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[7], cosNodes[3]), -4);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[7], cosNodes[4]), -3);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[7], cosNodes[5]), -2);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[7], cosNodes[6]), -1);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[7], cosNodes[7]),  0);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[7], cosNodes[8]), -8);
  
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[8], cosNodes[0]), -8);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[8], cosNodes[1]), -7);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[8], cosNodes[2]), -6);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[8], cosNodes[3]), -5);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[8], cosNodes[4]), -4);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[8], cosNodes[5]), -3);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[8], cosNodes[6]), -2);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[8], cosNodes[7]), -1);
  BOOST_CHECK_EQUAL(coHashGraph.getBackwardNodeDistance(cosNodes[8], cosNodes[8]),  0);
  
  for (int n = 0; n < conNodeCount; n++) {
    delete cosNodes[n];
  }
}

BOOST_AUTO_TEST_CASE(RoundConsistentHashGraphMinDistanceTest) {
  const int conNodeCount = 9;
  TestConsistentHashGraph coHashGraph;
  TestConsistentHashNode *cosNodes[conNodeCount];
  
  for (int n = 0; n < conNodeCount; n++) {
    cosNodes[n] = new TestConsistentHashNode(n+1);
    coHashGraph.addNode(cosNodes[n]);
  }

  for (int i = 0; i < conNodeCount; i++) {
    for (int j = 0; j < conNodeCount; j++) {
      off_t distance = coHashGraph.getMinNodeDistance(cosNodes[i], cosNodes[j]);
      BOOST_CHECK(distance <= (conNodeCount/2));
    }
  }
  
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[0], cosNodes[0]),  0);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[0], cosNodes[1]),  1);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[0], cosNodes[2]),  2);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[0], cosNodes[3]),  3);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[0], cosNodes[4]),  4);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[0], cosNodes[5]), -4);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[0], cosNodes[6]), -3);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[0], cosNodes[7]), -2);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[0], cosNodes[8]), -1);

  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[1], cosNodes[0]), -1);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[1], cosNodes[1]),  0);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[1], cosNodes[2]),  1);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[1], cosNodes[3]),  2);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[1], cosNodes[4]),  3);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[1], cosNodes[5]),  4);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[1], cosNodes[6]), -4);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[1], cosNodes[7]), -3);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[1], cosNodes[8]), -2);

  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[2], cosNodes[0]), -2);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[2], cosNodes[1]), -1);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[2], cosNodes[2]),  0);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[2], cosNodes[3]),  1);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[2], cosNodes[4]),  2);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[2], cosNodes[5]),  3);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[2], cosNodes[6]),  4);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[2], cosNodes[7]), -4);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[2], cosNodes[8]), -3);

  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[3], cosNodes[0]), -3);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[3], cosNodes[1]), -2);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[3], cosNodes[2]), -1);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[3], cosNodes[3]),  0);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[3], cosNodes[4]),  1);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[3], cosNodes[5]),  2);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[3], cosNodes[6]),  3);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[3], cosNodes[7]),  4);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[3], cosNodes[8]), -4);

  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[4], cosNodes[0]), -4);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[4], cosNodes[1]), -3);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[4], cosNodes[2]), -2);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[4], cosNodes[3]), -1);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[4], cosNodes[4]),  0);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[4], cosNodes[5]),  1);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[4], cosNodes[6]),  2);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[4], cosNodes[7]),  3);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[4], cosNodes[8]),  4);

  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[5], cosNodes[0]),  4);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[5], cosNodes[1]), -4);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[5], cosNodes[2]), -3);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[5], cosNodes[3]), -2);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[5], cosNodes[4]), -1);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[5], cosNodes[5]),  0);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[5], cosNodes[6]),  1);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[5], cosNodes[7]),  2);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[5], cosNodes[8]),  3);

  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[6], cosNodes[0]),  3);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[6], cosNodes[1]),  4);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[6], cosNodes[2]), -4);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[6], cosNodes[3]), -3);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[6], cosNodes[4]), -2);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[6], cosNodes[5]), -1);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[6], cosNodes[6]),  0);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[6], cosNodes[7]),  1);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[6], cosNodes[8]),  2);

  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[7], cosNodes[0]),  2);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[7], cosNodes[1]),  3);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[7], cosNodes[2]),  4);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[7], cosNodes[3]), -4);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[7], cosNodes[4]), -3);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[7], cosNodes[5]), -2);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[7], cosNodes[6]), -1);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[7], cosNodes[7]),  0);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[7], cosNodes[8]),  1);

  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[8], cosNodes[0]),  1);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[8], cosNodes[1]),  2);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[8], cosNodes[2]),  3);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[8], cosNodes[3]),  4);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[8], cosNodes[4]), -4);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[8], cosNodes[5]), -3);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[8], cosNodes[6]), -2);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[8], cosNodes[7]), -1);
  BOOST_CHECK_EQUAL(coHashGraph.getMinNodeDistance(cosNodes[8], cosNodes[8]),  0);
  
  for (int n = 0; n < conNodeCount; n++) {
    delete cosNodes[n];
  }
}
