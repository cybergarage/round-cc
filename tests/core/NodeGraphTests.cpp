/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <boost/test/unit_test.hpp>

#include <round/Round.h>

using namespace std;
using namespace Round;

const static size_t FRACTAL_TEST_NODEGRAPH_MAXSIZE = 9;

BOOST_AUTO_TEST_SUITE(node)

class TestOrderdObject : public ConsistentHashObject {
public:
  std::string id;
  
public:
  TestOrderdObject(size_t idValue) {
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

class TestOrderdNode : public LocalNode {
 public:
  std::string id;

 public:
  TestOrderdNode(size_t idValue) {
    ostringstream oss;
    oss << idValue;
    this->id = oss.str();
  }

  bool getHashCode(std::string *hashCode) const {
    *hashCode = this->id;
    return true;
  }

  bool getRequestAddress(std::string *address, Error *error) const {
    return true;
  }
  bool getRequestPort(int *port, Error *error) const {
    return true;
  }

  bool getClusterName(std::string *name, Error *error) {
    return true;
  }

  void setWeakFlag(bool flag) {
    Node::setWeakFlag(flag);
  }
};

class TestOrderdNodeGraph : public NodeGraph {
 public:
  std::string id;

 public:
  TestOrderdNodeGraph() {
  }

};

BOOST_AUTO_TEST_CASE(RoundNodGraphAddTest) {
  const size_t nodeCount = FRACTAL_TEST_NODEGRAPH_MAXSIZE;
  TestOrderdNodeGraph *nodeGraph = new TestOrderdNodeGraph();
  TestOrderdNode *nodes[nodeCount];

  for (size_t n = 0; n < nodeCount; n++) {
    nodes[n] = new TestOrderdNode(n+1);
    nodes[n]->setWeakFlag(true);
    BOOST_CHECK(nodes[n]);
  }

  for (size_t n = 0; n < nodeCount; n++) {
    Node *thisNode = nodes[n];
    BOOST_CHECK(nodeGraph->addNode(thisNode));
    Node *prevNode = nodeGraph->getPrevNode(nodes[n]);
    Node *nextNode = nodeGraph->getNextNode(nodes[n]);
    if (n == 0) {
      BOOST_CHECK_EQUAL(thisNode, prevNode);
      BOOST_CHECK_EQUAL(thisNode, nextNode);
    }
    else {
      size_t prevNodeIdx = n-1;
      BOOST_CHECK_EQUAL(nodes[prevNodeIdx], prevNode);
      size_t nextNodeIdx = (n+1) % nodeGraph->size();
      BOOST_CHECK_EQUAL(nodes[nextNodeIdx], nextNode);
    }
  }
  BOOST_CHECK_EQUAL(nodeGraph->size(), nodeCount);

  delete nodeGraph;
  
  for (size_t n = 0; n < nodeCount; n++)
    delete nodes[n];  
}

BOOST_AUTO_TEST_CASE(RoundNodGraphReAddTest) {
  const size_t nodeCount = FRACTAL_TEST_NODEGRAPH_MAXSIZE;
  TestOrderdNodeGraph *nodeGraph = new TestOrderdNodeGraph();
  TestOrderdNode *nodes[nodeCount];

  for (size_t n = 0; n < nodeCount; n++) {
    nodes[n] = new TestOrderdNode(n+1);
    nodes[n]->setWeakFlag(true);
    BOOST_CHECK(nodes[n]);
  }

  for (size_t n = 0; n < nodeCount; n++) {
    BOOST_CHECK(nodeGraph->addNode(nodes[n]));
  }
  BOOST_CHECK_EQUAL(nodeGraph->size(), nodeCount);

  for (size_t n = 0; n < nodeCount; n++)
    nodeGraph->addNode(nodes[n]);
  BOOST_CHECK_EQUAL(nodeGraph->size(), nodeCount);

  delete nodeGraph;
  
  for (size_t n = 0; n < nodeCount; n++)
    delete nodes[n];
}

BOOST_AUTO_TEST_CASE(RoundNodGraphReplicaTest) {
  const size_t nodeCount = FRACTAL_TEST_NODEGRAPH_MAXSIZE;
  TestOrderdNodeGraph nodeGraph;
  TestOrderdNode *nodes[nodeCount];

  for (size_t n = 0; n < nodeCount; n++) {
    nodes[n] = new TestOrderdNode(n+1);
    nodes[n]->setWeakFlag(false);
    BOOST_CHECK(nodes[n]);
    BOOST_CHECK(nodeGraph.addNode(nodes[n]));
    //std::cout << "[" << n << "] = " << nodes[n] << std::endl; 
  }
  BOOST_CHECK_EQUAL(nodeGraph.size(), nodeCount);
}

BOOST_AUTO_TEST_CASE(RoundNodGraphReplicaMinTest) {
  const size_t nodeCount = FRACTAL_TEST_NODEGRAPH_MAXSIZE;
  TestOrderdNodeGraph nodeGraph;
  TestOrderdNode *nodes[nodeCount];

  for (size_t n = 0; n < nodeCount; n++) {
    nodes[n] = new TestOrderdNode(n+1);
    BOOST_CHECK(nodes[n]);
    nodes[n]->setWeakFlag(false);
    BOOST_CHECK(nodeGraph.addNode(nodes[n]));

    NodeList nodeList;
    nodeList.clear();
  }
}

BOOST_AUTO_TEST_CASE(RoundNodGraphSetTest) {
  const int nodeCount = FRACTAL_TEST_NODEGRAPH_MAXSIZE;

  NodeGraph nodeGraph1;
  NodeGraph nodeGraph2;

  BOOST_CHECK_EQUAL(nodeGraph1.size(), 0);
  BOOST_CHECK_EQUAL(nodeGraph1.size(), 0);
  
  for (int n=0; n<nodeCount; n++) {
    nodeGraph1.addNode(new RemoteNode("", n));
  }
  BOOST_CHECK_EQUAL(nodeGraph1.size(), nodeCount);

  BOOST_CHECK(nodeGraph2.set(nodeGraph1));
  BOOST_CHECK_EQUAL(nodeGraph1.size(), nodeCount);
  BOOST_CHECK_EQUAL(nodeGraph2.size(), nodeCount);
  BOOST_CHECK_EQUAL(nodeGraph1.size(), nodeGraph2.size());

  BOOST_CHECK(nodeGraph2.set(nodeGraph1));
  BOOST_CHECK_EQUAL(nodeGraph1.size(), nodeCount);
  BOOST_CHECK_EQUAL(nodeGraph2.size(), nodeCount);
  BOOST_CHECK_EQUAL(nodeGraph1.size(), nodeGraph2.size());
}

BOOST_AUTO_TEST_CASE(RoundNodGraphGetRandomTest) {
  const size_t nodeCount = FRACTAL_TEST_NODEGRAPH_MAXSIZE;
  TestOrderdNodeGraph nodeGraph;
  TestOrderdNode *nodes[nodeCount];
  
  for (size_t n = 0; n < nodeCount; n++) {
    nodes[n] = new TestOrderdNode(n+1);
    nodes[n]->setWeakFlag(false);
    BOOST_CHECK(nodes[n]);
    BOOST_CHECK(nodeGraph.addNode(nodes[n]));
  }
  BOOST_CHECK_EQUAL(nodeGraph.size(), nodeCount);

  for (size_t n = 0; n < (nodeCount * 10); n++) {
    BOOST_CHECK(nodeGraph.getRandomNode());
  }
}

BOOST_AUTO_TEST_SUITE_END()

