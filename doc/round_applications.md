![round_logo](./img/round_logo.png)

# Applications

## Echo

The sample is a simple only to echo the specified parameters.

### Script

```
{
  methods : [
    {
      "name": "echo",
      "language": "js",
      "code": "function echo(params) {return params;}"",
    }
  ]
}

```


## Chubby

The sample is a simple distributed key value store to small data such as configuration data like Google's chubby [1]. The sample is based on [Quorum Pattern](./round_design_pattern.md).

![chubby](./img/round_app_chubby.png)

## Key Value Store

The sample is a simple distributed key value store which is based on [eventual consistency](http://en.wikipedia.org/wiki/Eventual_consistency) such as Dynamo[2] and Cassandra[3]. The sample is based on [Quorum Pattern](./round_design_pattern.md).

![kvs](./img/round_app_kvs.png)

## CDN (Contents Delivery Network)

## Search Engine

## Dynamic DNS

## DNS Server

## Time Server

# References

[1] :  M. Burrows, “The Chubby lock service for loosely-coupled distributed
systems,” in OSDI ’06: Proceedings of the 7th symposium on Operating
systems design and implementation, 2006, pp. 335–350.

[2] : DeCandia, G., et al. 2007. Dynamo: Amazon’s highly available key-value store. In Proceedings of the 21st ACM Symposium on Operating Systems Principles: 205-220.

[3] : Lakshman, A., Malik, P. 2009. Cassandra—a decentralized structured storage system. In the 3rd ACM SIGOPS International Workshop on Large-scale Distributed Systems and Middleware.
