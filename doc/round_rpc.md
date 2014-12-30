![round_logo](./img/round_logo.png)

# Round RPC Specfication

Round is based on [JSON-RPC 2.0][json-rpc], and Round extends the specification to develop distributed system applications as the following.

## Object Field Extentions

Round adds the following original fields to [JSON-RPC 2.0][json-rpc] specification.

| Field | Descripton | Default | Detail |
| - | - | - | - |
| hash | - | (node) | |
| dest | one, all, quorum | one | |
| ts | - | - | The field is handled automatically by Round |
| type | accept | (none) | - |
| digest | - | (none) | - |

### hash

The hash field specifies a target node of the request object. The node which is received the request object checks the hash code whether the node should execute the request object.  

#### Request object

The hash code specifies a destination node of the message. In the current version, the hash code must be genarated using [SHA-256](http://en.wikipedia.org/wiki/SHA-2). If the hash field is not specified, the message is executed by the received node.

```
--> {"jsonrpc": "2.0", "method": "increment_counter", "params": 1, "hash": "xxxxxxxxxxxxxxxx", ....}
```

#### Response object

The message is executed if the specified hash code is handled by the received node, otherwise the node doen't executed the message and returns a error object including the detail error code as the following.

```
<-- {"jsonrpc": "2.0", "error": {"code": -32002, "message": "Moved Permanently"}, ....}
```

If the node returns the error object, the cluster might be updated because of adding or removing nodes. To update the current cluster information, Use '[_get_cluster_info](./round_rpc_methods.md)' method for the node to get the latest cluster information.

### dest (destination) + hash

### ts (timestamp)

Round adds a timestamp parameter based on [Lamport timestamps][lamport-timestamps] to know the operation causality.

In Round, the timestamp parameter is added and controlled automatically.

##### Request object

The parameter has a logical timestamp number of the client. If it is not included it is assumed to be a non-casual request, the logical clock of the requested remote node is not updated.

##### Response object

The all response object has the parameter. The parameter has a logical timestamp number of the remote node.

When the request object has the parameter, the remote node updates the local logical timestamp using the request logical timestamp, and the remote node returns the updated logical timestamp in the response object.

When the request object hasn't the parameter, the remote node does't update the local logical timestamp, and the remote node returns the current timestamp in the response object.

[lamport-timestamps]: http://en.wikipedia.org/wiki/Lamport_timestamps

#### hash

##### Request object


#### digest

##### Request object

##### Examples

###### RPC call with timestamp
```
--> {"jsonrpc": "2.0", "method": "increment_counter", "params": 1, "id": 1, "ts": 1}
<-- {"jsonrpc": "2.0", "result": 102, "id": 1, ts:3}
--> {"jsonrpc": "2.0", "method": "increment_counter", "params": 1, "id": 1, "ts": 5}
<-- {"jsonrpc": "2.0", "result": 103, "id": 1, ts:7}
```

###### RPC call without timestamp
```
--> {"jsonrpc": "2.0", "method": "increment_counter", "params": 1, "id": 1}
<-- {"jsonrpc": "2.0", "result": 102, "id": 1, ts:2}
--> {"jsonrpc": "2.0", "method": "increment_counter", "params": 1, "id": 1}
<-- {"jsonrpc": "2.0", "result": 103, "id": 1, ts:2}
```

#### Error code

Round added the folloinwg error codes in the  implementation defined range [JSON-RPC][json-rpc]. Round returns the following error code when the specified method couldn't be executed.

| code | message | data |
|-|-|-|
| -32000 | Bad Hash Length | { "cluster" : } |
| -32001 | Moved Permanently | { "cluster" : } |
| -32010 | Internal Script Engine Error | (none) |
| -32011 | Invalid Script Language | (none) |
| -32012 | Invalid Script Code | (none) |
| -32013 | Script Runtime Error  | (none) |

#### Future

For efficient communication for between the nodes, we will support more efficient remote procedure call like  [BSON](http://bsonspec.org) in the future release.

### Asynchronous Request

Round is based on [JSON-RPC over HTTP][json-rpc-http], but Round extends the specification to support asynchronous [RPC][rpc].

#### HTTP Header

In addition to standard headers of [JSON-RPC over HTTP][json-rpc-http], Round supports the following extra headers.

##### X-Async-Location

```
X-Aync-Location = locationURI
locationURI = protocol "://" host ":" port
prorocol = "http" | "httpu"
```

The request over HTTPU or HTTPMU SHOULD has this header to receive the result response. If the header is not included in a request message over HTTPU or HTTPMU, the request is recognized as a notification request even if the request has a 'id' member.

#### Response Code

For the asynchronous request, Round returns the following HTTP status code immediately.

| Code | Status | Description |
| - | - | - |
| 202 | Accepted | 'result' member is not inclued |
| 302 | Moved Permanently | - |
| 500 | Internal Server Error | - |

Round doesn't check the request message in more detail. Thus all JSON-RPC errors such as 'Parser Error' are returns into the specified location asynchronously.

The 'result' member is required on success in [JSON-RPC 2.0][json-rpc]. However, Round does't include the result member in the immediate response for asynchronous request because the operation is not executed yet.


[rpc]: http://en.wikipedia.org/wiki/Remote_procedure_call
[json-rpc]: http://www.jsonrpc.org/specification
[json-rpc-http]: http://jsonrpc.org/historical/json-rpc-over-http.html

### Staging

The received message is split into multiple stages similar to the SEDA [[??]][seda] architecture.

[??] [Welsh, M., Culler, D., and Brewer, E. 2001. SEDA: an architecture for well-conditioned, scalable internet services][seda].

[seda]: http://dl.acm.org/citation.cfm?id=502057

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
