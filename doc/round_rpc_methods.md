![round_logo](./img/round_logo.png)

# Round RPC Methods

## Overview

Node can communicate to other nodes in the same cluster using [RPC (remote procedure call)](http://en.wikipedia.org/wiki/Remote_procedure_call) over HTTP or HTTPU.

## Parameters

## Methods

### Basic Methods

Method names that begin with the word followed by a underscore character (_) are reserved for Round to implement the internal system methods.

| Method Name | Perpose | Params |
|-|-|-|
| _set_method | Set a script method | {"language" : "js", "name" : (value), "script" : (value)} |

#### Supprted Programming Languages

In JavaScript JSON encode

In Java, Base64

### Dynamic Methods

Round prepares the following default dynamic methods. Developers can override the default functions using '_set_method'.

| Method Name | Perpose | Params | Outputs | Default |
|-|-|-|-| - |
| _get_node_name | Get a node name | - | - | - |
| _get_node_hashseed | Get a prefix and seed string to generate a hash | - | - | - |
| _get_node_hashalgorithm | Get a shared key for HMAC | (none) | SHA2, SHA1, MD5 | - |
| _get_node_sharedkey | Set a shared key for HMAC | - | - | - |
| _get_node_digest | Set a shared key for HMAC | - | - | - |
| _notify_node_added | - | - | - | - |
| _notify_node_removed | - | - | - | - |
| _notify_node_suspected | - | - | - | - |
| _echo| For test purpose | - | - | - |

The methods are executed ......

#### Static Methods

The following methods is defined in Round using the native programming language statically. Developers can't override the static methods.

| Method Name | Perpose | Params |
|-|-|-|
| _get_node_info | Get a node name | - |
| _get_node_stats | Get a node name | - |

### User Methods

```
{"jsonrpc": "2.0", "method": "subtract",
{
  "language":"js",
  "method":"echo",
  "script":"function echo(params) {return params;}"
}
```

#### Predefined Methods

```
function _get_node_hashseed(params) {
  local_name =
  local_address =
  local_port =

  outParams["prefix"] = "";
  outParams["seed"] = local_address + ":" + local_port;

  return outParams;
}
```

does not recognize data center or rack information.

like  [SimpleSnitch](http://www.datastax.com/documentation/cassandra/2.0/cassandra/architecture/architectureSnitchSimple_c.html) in Cassandra.

a single region.

```
function node_get_hashseeds(params) {
  local_name =
  local_address =
  local_port =

  outParams["prefix"] = local_address.substr(0, local_address.lastIndexOf("."));
  outParams["seed"] = local_address + ":" + local_port;

  return outParams;
}
```

[RackInferringSnitch](http://www.datastax.com/documentation/cassandra/2.0/cassandra/architecture/architectureSnitchRackInf_c.html)

multiple regions [EC2MultiRegionSnitch](http://www.datastax.com/documentation/cassandra/2.0/cassandra/architecture/architectureSnitchesAbout_c.html)

[Dynamic snitching in Cassandra: past, present, and future](http://www.datastax.com/dev/blog/dynamic-snitching-in-cassandra-past-present-and-future)

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
