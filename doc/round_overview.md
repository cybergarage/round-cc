![round_logo](./img/round_logo.png)

# Overview

## What is Round ?

Round is a new consensus service framework to develop distributed applications. The name 'Round' derives from '[Knights of the Round Table](http://en.wikipedia.org/wiki/Round_Table)', every nodes in a cluster has equal roll, the cluster has no master node.

## Design Principles

Round is desined based on the following characteristics.

### Zeroconf

In typical cloud systems, some configurations such as the ip address and the service port are needed to add a new node manually, but the manual configurations are obstacle for auto scale distributed systems. In Round, all new nodes are added into a cluster without special configuration and the nodes are available soon automatically.

![round_overview_zeroconf](/img/round_overview_zeroconf.svg)

In Round, some noficication events are defined for the node statues. When a node status is changed, the notification message is sent to all other nodes  in the same cluster. For example, each existing node is recieved a notirication message when a new node is added or removed.

### Decentralized

Round is a decentralized and distributed system, every nodes in a cluster has equal roll, the cluster has no master node. In typical distributed systems are centric, they has a master node. Round manages all nodes in the cluster using a structured networking base on based on [distributed hash table](http://en.wikipedia.org/wiki/Distributed_hash_table) as default.

![round_overview_zeroconf](/img/round_overview_decentralized.svg)

However, Round can support other networking structure too because every nodes can manage networking structure of the cluster in accordance with a specified strategy. To manage the networking structure in Round, see the related section in [Round Internals](./round_internals.md).

### Autonomous

Each node run as an autonomous agent in the cluster, a node communicate to other nodes based on the specified behaviors using the message protocol synchronously or asynchronously.

![round_overview_autonomous](/img/round_overview_autonomous.svg)

The some basic behaviors are defined as default, and developers can add new behaviors using a dynamic programming language script.

### Dynamics

The behaviors of node are defined using a dynamic programming language script, so the distributed strategies and algorithms are configurable dynamically. To send a script, developers can change the strategy and algorithm of all nodes in the cluster dynamically.

![round_overview_dynamics](/img/round_overview_dynamics.svg)

### Immutable

When a node is suspected of failing by other nodes in the cluster, the node will be removed and disposed. Once a node is disposed, the node will not be able to become active because the suspected node will might occur unexpected problems such as [Byzantine generals problem](http://en.wikipedia.org/wiki/Byzantine_fault_tolerance).

![round_overview_immutable](/img/round_overview_immutable.svg)

To add a node instead of the disposed node into the cluster, developers should create a new node and add the node newly into the cluster.

## Support Functions

Round supports the following functions for distrubted systems.

### Auto Configuration

To add a new node into a cluster.

### Service Discovery

### Dynamic Configuration

### Messaging

Node can communicate to other nodes in the same cluster using [RPC (remote procedure call)](http://en.wikipedia.org/wiki/Remote_procedure_call).

### Security

Monochrome iconset by [Danny Allen](http://dannya.org).
