![round_logo](./img/round_logo.png)

English [Japanese](round_conversions_jp.md)

# Conversions

## Target Layers

Round's core functions are very small like [Microkernel](http://en.wikipedia.org/wiki/Microkernel), and the all other basic functions which are need for distributed frameworks or applications are supplied as core modules. Developers can build distributed frameworks or applications using the core functions and modules as the following.

![round_design_scope](img/round_design_scope.png)

### Existing Consensus Services

The existing distributed consensus service such as [Chubby \[1\]][1], [ZooKeeper \[2\]][2] supports the only following basic functions to build distributed applications.

![Chubby Programming Model](img/chubby_distributed_programming.png)

#### Comparison Table

| Feature | Round | ZooKeeper | Consul | etcd | Chubby |
|---|---|---|---|---|
| Consensus Protocol | Dynamic | Static (ZAB) | Static (Raft) | Static (Raft) | Static (Paxos) |
| Failure Detection | Dynamic | Static | Static | Static | Static |
| Notification | Dynamic | Static | Static | Static | Static |
| Membership | Multicast, Gossip | ? | ? | Gossip | ? |

#### Functions

Consensus service provides only two simple services, registry and event. Developer have to handle other functions such as request handlers with client and other nodes.

##### Structured Registry

Consensus service provides a structured registry which developer can access atomicity. The registry has a sequential number to access atomicity, then developer can use the registry as as mutex to handle critical section.

##### Event

The event service sends only the following notifications when other node status is changed.

- Node Created
- Node Deleted
- Node Data Changed
- Node Children Changed

The events are limited and static. In contrast, Round supports more useful events, developer can add user events easily.

#### Round Functions

In constract, Round supports all basic functions to develop distributed application, then eveloper only have to write application scripts.

![Chubby Programming Model](img/round_distributed_programming.png)

## Existing General Distributed Framework

In the existing distributed framework such as [MapReduce \[2\]][2] and [Storm \[4\]][4] assumes some a specific execution model to develop distributed application easily.

[MapReduce \[2\]][2] assumes .... the programming code is static.

[Storm \[4\]][4] ....

### Comparison Table

| Feature | Round | Hadoop | HiVE | YARN | Spark | Storm |
|---|---|---|---|---|
| Programming Model | Application + DG | MapReduce | MapReduce + DAG | Application | DAG | Application + DG |
| Data Model | None | KV | KV | None | KV | KV? |
| Resource Management | O | O | O | O | X | ? |


### Round Functions

Round supports

## Existing Service Framework

..... the function is static, and it is difficult to change the algorithm.


## Existing Distributed Application

### Comparison Table

| Feature | Round | Cassandra |  |  |
|---|---|---|---|---|
| Component | Micro | Monolithic |  |  |  |

## Refrences

- \[1\] : [Mike Burrows, Chubby Distributed Lock Service, OSDI'06, 2006][1]
- \[2\] : [Apache ZooKeeper][2]
- \[3\] : [Jeffrey Dean and Sanjay Ghemawat, MapReduce: Simplified Data Processing on Large Clusters, OSDI'04, 2004][2]
- \[4\] : [Apache Storm][3]
- \[5\] : [Conway's Game of Life][5]
- \[6\] : [Pipeline (Unix)][6]

[1]: http://research.google.com/archive/chubby.html
[2]: http://zookeeper.apache.org/
[3]: http://research.google.com/archive/mapreduce.html
[4]: https://storm.apache.org/
[5]: http://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
[6]: http://en.wikipedia.org/wiki/Pipeline_%28Unix%29

[raft]: https://raftconsensus.github.io/
[raft-consul]: http://www.consul.io/docs/internals/consensus.html
[gossip-consul]: http://www.consul.io/docs/internals/gossip.html
