![round_logo](./img/round_logo.png)

# Round Internals

## Simplify

### Open Architecture

Round consists only some open standard network protocols such as [UPnP][upnp] and [JSON-RPC][json-rpc] with standard script engines such as [Java][java] and [JavaScript][v8].

![round_protocol](./img/round_protocol.svg)

[java]: https://java.com/
[js]: http://www.ecma-international.org/publications/standards/Ecma-262.htm
[v8]: https://developers.google.com/v8/

## Zeroconf

Round is designed based on [Zeroconf](http://www.zeroconf.org/) concept to achieve automatically scalable distributed systems. Specifically, Round uses [UPnP][upnp], Universal Plug and Play, as [Zeroconf](http://www.zeroconf.org/) protocol.

Using the [Zeroconf](http://www.zeroconf.org/) protocol,  

[upnp]: http://upnp.org

## Dynamics

Dynamic Configuration

## Structured Network

Round is based on Chord, and Chord is based on [consistent hasing](http://en.wikipedia.org/wiki/Consistent_hashing).

Developers can change the algorithm

Round will support other structues .....

## Messaging

Node can communicate to other nodes in the same cluster using [RPC (remote procedure call)][rpc] over HTTP, HTTPU and HTTPMU.

<<<<<<< HEAD
### Protocol

Round is based on [JSON-RPC 2.0][json-rpc], and Round extends the specification for distributed system applications.

#### ts (timestamp)

Round adds a timestamp parameter based on [Lamport timestamps][lamport-timestamps] to know the operation causality.

In Round, the timestamp parameter is added and controlled automatically.

##### Request object

The parameter has a logical timestamp number of the client. If it is not included it is assumed to be a non-casual request, the logical clock of the requested remote node is not updated.

##### Response object

The all response object has the parameter. The parameter has a logical timestamp number of the remote node.

When the request object has the parameter, the remote node updates the local logical timestamp using the request logical timestamp, and the remote node returns the updated logical timestamp in the response object.

When the request object hasn't the parameter, the remote node does't update the local logical timestamp, and the remote node returns the current timestamp in the response object.

[lamport-timestamps]: http://en.wikipedia.org/wiki/Lamport_timestamps

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
| 500 | Internal Server Error | - |

Round doesn't check the request message in more detail. Thus all JSON-RPC errors such as 'Parser Error' are returns into the specified location asynchronously.

The 'result' member is required on success in [JSON-RPC 2.0][json-rpc]. However, Round does't include the result member in the immediate response for asynchronous request because the operation is not executed yet.


[rpc]: http://en.wikipedia.org/wiki/Remote_procedure_call
[json-rpc]: http://www.jsonrpc.org/specification
[json-rpc-http]: http://jsonrpc.org/historical/json-rpc-over-http.html


=======
>>>>>>> 18164205b2034aa008207c95898f31a6322fd774
### Clock

Round supports some logical clock algorithm such as [Lamport clock](http://en.wikipedia.org/wiki/Lamport_timestamps) and [vector clock](http://en.wikipedia.org/wiki/Vector_clock), and developers can select the clock algorithm.

Round updates the logical clock in any node every a messaging, and the parameter is added into the messaging automatically.

### Methods

Check [Round RPC Methods](./round_rpc_methods.md)

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
