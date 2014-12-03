![round_logo](./img/round_logo.png)

# Other Consensus Services

## Conversion

| - | Round | ZooKeeper | Consul | etcd |
|-|-|-|-|-|
| Implementation | C++ | Java | Go | Go |
| Notification | Asynchronous | Synchronous | Synchronous | Synchronous |
| Consensus Protocol | Paxos | ZAB | [Raft](http://www.consul.io/docs/internals/consensus.html) | Raft |
| Membership | Multicast | (none) | [gossip](http://www.consul.io/docs/internals/gossip.html) | (?) |
