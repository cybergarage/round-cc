![overview_design_zeroconf](./img/round_logo.png)

# Overview

## What is Round ?

Round is a new consensus service framework to develop distributed applications. The name 'Round' derives from '[Knights of the Round Table](http://en.wikipedia.org/wiki/Round_Table)', every nodes in a cluster has equal roll, the cluster has no master node.

## Design Principles

Round is desined based on the following characteristics.

### Zeroconf

In typical cloud systems, some configurations such as the ip address and the service port are needed to add a new node manually, but the manual configurations are obstacle for auto scale distributed systems. In Round, all new nodes are added into a cluster without special configuration and the nodes are available soon automatically.

![overview_design_zeroconf](/img/overview_design_zeroconf.svg)

In Round, some noficication events are defined for the node statues. When a node status is changed, the notification message is sent to all other nodes  in the same cluster. For example, each existing node is recieved a notirication message when a new node is added or removed.

### Decentralized

Round is a decentralized and distributed system, every nodes in a cluster has equal roll, the cluster has no master node. In typical distributed systems are centric, they has a master node. Round manages all nodes in the cluster using a structured networking base on based on [distributed hash table](http://en.wikipedia.org/wiki/Distributed_hash_table) as default.

![overview_design_zeroconf](/img/overview_design_decentralized.svg)

However, Round can support other networking structure too because every nodes can manage networking structure of the cluster in accordance with a specified strategy. To manage the networking structure in Round, see the related section in [Round Internals](./round_internals.md).

### Autonomous

Each node run as an autonomous agent in the cluster, a node communicate to other nodes based on the specified behaviors using the message protocol synchronously or asynchronously.

![overview_design_autonomous](/img/overview_design_autonomous.svg)

The some basic behaviors are defined as default, and developers can add new behaviors using programming language script dynamically.

### Dynamics

The distributed functions of Round are defined using programming language script, so the distributed strategies and algorithms are configurable dynamically. To send a script, developers can change the strategy and algorithm of all nodes in the cluster dynamically.

![overview_design_dynamics](/img/overview_design_dynamics.svg)

### Immutable

![overview_design_immutable](/img/overview_design_immutable.svg)

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
