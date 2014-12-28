![round_logo](img/round_logo.png)

# Overview

## What is Round ?

Round is a new consensus service framework to create distributed applications for developers and researchers. The name 'Round' derives from '[Knights of the Round Table](http://en.wikipedia.org/wiki/Round_Table)', every nodes in a cluster has equal roll, the cluster has no master node.

## Design Principles

### Simplify

In Round, simplify is a most important principle. The core module is simple, and it has only minimum functions. Just like simplify, orthogonality too is a most important principle. Based on the principles, redundant functions aren't implemented to keep the core module simplify.

### Clarify

Technical specifications of the core module are defined clarify and released free for developers. Basically, The specifications are defined based on some open standard network protocols as the following.

We are implementing the preview version of Round using C++, but the core module can be implemented using other programming languages such as Java and Go.

## Design Features

### Zeroconf

In typical cloud systems, some configurations such as the ip address and the service port are needed to add a new node manually, but the manual configurations are obstacle for auto scale distributed systems. In Round, all new nodes are added into a cluster without special configuration and the nodes are available soon automatically.

![round_overview_zeroconf](img/round_overview_zeroconf.png)

In Round, some noficication events are defined for the node statues. When a node status is changed, the notification message is sent to all other nodes  in the same cluster. For example, each existing node is recieved a notirication message when a new node is added or removed.

### Decentralized

Round is a decentralized and distributed system, every nodes in a cluster has equal roll, the cluster has no master node. In typical distributed systems are centric, they has a master node.

![round_overview_zeroconf](img/round_overview_decentralized.png)

### Autonomous

Each node run as an autonomous agent in the cluster, a node communicate to other nodes based on the specified behaviors using the message protocol synchronously or asynchronously.

![round_overview_autonomous](img/round_overview_autonomous.png)

The some basic behaviors are defined as default, and developers can override the default behaviors or add new behaviors using some programming languages such as JavaScript or Java.

### Dynamics

The behaviors of node are defined using a dynamic programming language script, so the distributed strategies and algorithms are configurable dynamically. To send a script, developers can change the strategy and algorithm of all nodes in the cluster dynamically.

![round_overview_dynamics](img/round_overview_dynamics.png)

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
