![round_logo](./img/round_logo.png)

# Round RPC Methods

## Overview

Node can communicate to other nodes in the same cluster using [RPC (remote procedure call)](http://en.wikipedia.org/wiki/Remote_procedure_call) over HTTP or HTTPU.

## Methods

### Basic Methods

Method names that begin with the word followed by a underscore character (_) are reserved for Round to implement the internal system methods.

| Name | Perpose | Params |
|-|-|-|
| _set_method | Set a script method | {"language" : "js", "method" : (value), "encode": <EncodeType>, "script" : (value)} |

### Dynamic Methods

Round prepares the following default dynamic methods. Developers can override the default functions using '_set_method'.

| Method Name | Perpose | Params | Outputs | Default |
|-|-|-|-| - |
| _get_node_name | Get a node name | - | - | - |
| _get_log_level | Get the current log level | (none) | "TRACE", "LOG", "WARN", "ERR"  | "LOG" |
| _get_node_hashseed | Get a prefix and seed string to generate a hash | - | - | - |
| _get_node_hashalgorithm | Get a shared key for HMAC | (none) | "SHA2", "SHA1", "MD5" | - |
| _get_node_sharedkey | Set a shared key for HMAC | - | - | - |
| _get_node_digest | Set a shared key for HMAC | - | - | - |
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

## Parameters

| Parameter | M/U | Detail | Default | Constants |
|-|-|-|-|-|
| Method | M | Operation Method | - | GET, PUT |
| Sync | O | URI | Sync | Async,Sync |
| Destination | O | URI | Random | Random, ConsistentHash |
| Resouse | O | URI | (NULL) | - |
| Quarum | O | Operation Method | NONE | NONE, ALL, Number |
| Target | O | Operation Target | DEST | DEST, ALL, Number |
| Data | O | Operation data | (NULL) | - |

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