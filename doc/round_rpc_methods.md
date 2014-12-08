![round_logo](./img/round_logo.png)

# Round RPC Methods

## Overview

Round is based on [JSON-RPC][json-rpc] and [JSON-RPC over HTTP][json-rpc-http] to communicate to the node from client or other nodes.

## Protocol

Round uses [JSON-RPC][json-rpc] as [RPC][rpc] protocol

# HTTP, HTTPMU and HTTPU

Round is based on [JSON-RPC over HTTP][json-rpc-http], and Round extends the specification.

the specification to support asynchronous [RPC][rpc].

over HTTP, HTTPU and HTTPMU.

[rpc]: http://en.wikipedia.org/wiki/Remote_procedure_call
[json-rpc]: http://www.jsonrpc.org/specification
[json-rpc-http]: http://jsonrpc.org/historical/json-rpc-over-http.html

### ENDPOINT

###

### POST

| Parameter | Value |
|-|-|
| ENDPOINT | /rpc/do |
| | application/json-rpc |

### System parameters

| Parameter | M/U | Detail | Default | Constants |
|-|-|-|-|-|
| Method | M | Operation Method | - | GET, PUT |

### Client parameters

| Parameter | M/U | Detail | Default | Constants |
|-|-|-|-|-|
| Destination | O | URI | Random | Random, ConsistentHash |
| Quarum | O | Operation Method | NONE | NONE, ALL, Number |
| Target | O | Operation Target | DEST | DEST, ALL, Number |

### Application parameters

| Parameter | M/U | Detail | Default | Constants |
|-|-|-|-|-|
| Resouse | O | URI | (NULL) | - |
| Data | O | Operation data | (NULL) | - |

## RPC Methods

### System Methods

Method names that begin with the word followed by a underscore character (_) are reserved for Round to implement the internal system methods.

### Static Methods

Round prepares the following default static methods. The methods are implemented using the native programming language as default, and developers can't modify the static methods.

| Name | Perpose | Params |
|-|-|-|
| _set_method | Set a script method | {"language" : "js", "method" : (value), "encode": (encodeType), "code" : (value)} |

If the code parameter isn't specified, the method is removed.

### Dynamic Methods

Round prepares the following default dynamic methods. The methods are implemented using the native programming language as default, but developers can override the default functions using '_set_method'.

| Method Name | Perpose | Params | Outputs | Default |
|-|-|-|-| - |
| _get_node_info | Get a node name | - | - | - |
| _get_node_hash | Get a prefix and seed string to generate a hash | - | - | - |
| _get_node_sharedkey | Set a shared key for HMAC | - | - | - |
| _get_node_msg_digest | Set a shared key for HMAC | - | - | - |
| _get_log_level | Get the current log level | (none) | "TRACE", "LOG", "WARN", "ERR" "FATAL" | "LOG" |

### System Notification Methods

| Method Name | Perpose | Params | Outputs | Default |
|-|-|-|-| - |
| _notify_method_added | - | - | - | - |
| _notify_method_removed | - | - | - | - |
| _notify_method_updated | - | - | - | - |
| _notify_node_added | - | - | - | - |
| _notify_node_removed | - | - | - | - |
| _notify_node_suspected | - | - | - | - |

The methods are executed ......

#### Static Methods

The following methods is defined in Round using the native programming language statically. Developers can't override the static methods.

| Method Name | Perpose | Params |
|-|-|-|
| _get_node_info | Get a node name | - |
| _get_node_stats | Get a node name | - |

## Supprted Programming Languages

You can combined .....

##### JavaScript

In JavaScript JSON encode

##### Java

In Java, Base64

Camelcase

| Method | Java Class |
|-|-|
| _get_node_name | _GetNodeName |

```
public class _GetNodeName {
  public _GetNodeName() {
  }
  public String run(String params) {
    .....
    return results;
  }
}
```

## Examples

### Add NewMethods

#### Echo

```
{
  "jsonrpc": "2.0",
  "method": "subtract",
  "encode": "none",
  "params":
    {
      "language": "js",
      "method": "echo",
      "script": "function echo(params) {return params;}"
    }
}
```

### Override default methods

#### Log Level

```
{
  "jsonrpc": "2.0",
  "method": "_set_method",
  "encode": "none",
  "params":
    {
      "language": "js",
      "method": "_get_log_level",
      "script": "function _get_log_level() {return "trace";}"
    }
}
```

#### _get_node_hashseed

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
