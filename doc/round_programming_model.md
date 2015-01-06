![round_logo](./img/round_logo.png)

# Programming Model

Round is based on some programming model such as [actor model](http://en.wikipedia.org/wiki/Actor_model) and [dataflow programming](http://en.wikipedia.org/wiki/Dataflow_programming).

Each node of Round is an actor which has a message queue for [RPC](http://en.wikipedia.org/wiki/Remote_procedure_call) and can send messages to other nodes.

The each node can propagate a received message from clients or other nodes to other nodes or local methods using 'route'. The route can chain like pipelien of Unix.
