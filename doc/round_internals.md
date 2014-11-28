![round_logo](./img/round_logo.png)

# Round Internals

## Zeroconf

Round is designed based on [Zeroconf](http://www.zeroconf.org/) concept to achieve automatically scalable distributed systems. Specifically, Round uses [UPnP](http://upnp.org), Universal Plug and Play, as [Zeroconf](http://www.zeroconf.org/) protocol.

Using the [Zeroconf](http://www.zeroconf.org/) protocol,  

## Dynamics

Dynamic Configuration

## Overview

## Structured Network

Round is based on Chord, and Chord is based on [consistent hasing](http://en.wikipedia.org/wiki/Consistent_hashing).

Developers can change the algorithm

Round will support other structues .....

## Messaging

Node can communicate to other nodes in the same cluster using [RPC (remote procedure call)](http://en.wikipedia.org/wiki/Remote_procedure_call) over HTTP or HTTPU.

### Protocol

Round uses [JSON-RPC 2.0](http://www.jsonrpc.org/specification) over HTTP to execute [RPC](http://en.wikipedia.org/wiki/Remote_procedure_call). For efficient communication for between the nodes, we will support more efficient remote procedure call like  [BSON](http://bsonspec.org) in the future release.

### Clock

Round supports some logical clock algorithm such as [Lamport clock](http://en.wikipedia.org/wiki/Lamport_timestamps) and [vector clock](http://en.wikipedia.org/wiki/Vector_clock), and developers can select the clock algorithm.

Round updates the logical clock in any node every a messaging, and the parameter is added into the messaging automatically.

### Methods

Check [Round RPC Methods](./round_rpc_methods.md)

## Consensus Protocol

Round uses a traditional consensus protocol, [Paxos](http://en.wikipedia.org/wiki/Paxos_(computer_science), to provide consistency. Each node acts in three roles; Proposer, Acceptor and Learner in Paxos to reduces the message complexity significantly.

![round_internal_paxos](/img/round_internal_paxos.svg)

## Failure Detection

Any node can vote a failure suspicion into other nodes in the same cluster when the voted node suspects failure to other node or itself.

The algorithm of failure detection is programmable.

## Interface

### JSON-RPC

Node includes a local HTTP server to handle requests form other node or client. The HTTP server has [RESTful](http://en.wikipedia.org/wiki/Representational_state_transfer) interfaces using [JSON-RPC 2.0](http://www.jsonrpc.org/specification), so you can request ..... , For efficient communication for between the nodes, we will support more efficient remote procedure call like  [BSON](http://bsonspec.org) in the future release.

### Dynamic Interface

Round

Round has a JavaScrpit engine based on [V8](http://en.wikipedia.org/wiki/V8_\(JavaScript_engine\) to define basic strategies such as structured network and failure detection.

### Native Interface

## Security

Round supports a security model based on [HMAC](https://tools.ietf.org/html/rfc2104) to reject unreliable messages from evil users.

The node
a session key.
