![round_logo](./img/round_logo.png)

# RPC Methods

## System Methods

Method names that begin with the word followed by a underscore character are reserved for Round to implement the internal system methods.

## Static Methods

Round prepares the following default static methods. The methods are implemented using the native programming language as default, and developers can't modify the static methods.

| Name | Perpose | Params |
| --- | --- | --- |
| _set_method | Set a script method | {"language" : "js", "name" : (value), "encode": (encodeType), "code" : (value)} |
| _set_route | Create a route | {"name" : (value), "src" : (timer or method name), "dest" : (method name), "params": (xxxx), "type" : (pipe or event)} |
| _set_timer | Create a timer | {"name" : (value), "start_time" : (value), "stop_time" : (value), "cycle_interval": (value), "loop" : (value)} |

#### _set_method

```
_set_method := "{" name language code encoding "}"

name     = "name" ":" TOKEN
language = "language" ":" supported-language
code     = "code" ":" TOKEN
encoding = "code" ":" ("none" | "base64")

supported-language = ("js" | "java" | "tcl")
```

If the code parameter isn't specified, the method is removed.

#### _set_route

```
_set_route := "{" name source destnation [params] [type] [cond]"}"

name       = "name" ":" TOKEN
source     = "src" ":" source-object
destnation = "dest" ":" destnation-object
params     = "{" *(param) "}"
type       = "type" ":" ("pipe" | "event")
cond       = "cond" ":" JS_SCRIPT

param                = (src-out-param-name | src-param-script) ":" in-param-name
src-out-param-name   = TOKEN
src-out-param-script = JS_SCRIPT
in-param-name        = TOKEN

source-object     = [cluster "."] [node "."] (trigger-name | method-name)
destnation-object = [cluster "."] [node "."] (method-name)
cluster           = ("local" | cluster-name)
node              = ("local" | "all" | hash-code)
cluster-name      = TOKEN
hash-code         = NODE_HASH
trigger-name      = TOKEN
method-name       = TOKEN
```

#### _set_timer

```
_set_timer := "{" name [start_time] [stop_time] [cycle_interval] [loop] "}"

name           = "name" ":" TOKEN
start_time     = "start_time" ":" INTEGER
stop_time      = "stop_time" ":" INTEGER
cycle_interval = "cycle_interval" ":" INTEGER
loop           = "loop" ":" BOOL
```

### Dynamic Methods

Round prepares the following default dynamic methods. The methods are implemented using the native programming language as default, but developers can override the default functions using '_set_method'.

| Method Name | Perpose | Params | Outputs | Default |
| --- | --- | --- | --- | --- |
| _get_node_info | Get a node infomation | (none) | {"name" : (string), "ip" : (address), "port" : (number),  "hash" : (string) } | - |
| _get_cluster_info | Gat a cluster information which the specified node is belong | - | - | - |
| _get_network_info | Gat a cluster list which the spcecified node knows | - | - | - |
| _get_node_hash | Set a shared key for HMAC | - | - | - |
| _get_node_sharedkey | Set a shared key for HMAC | - | - | - |
| _get_node_msg_digest | Set a shared key for HMAC | - | - | - |
| _get_log_level | Get the current log level | (none) | "TRACE", "LOG", "WARN", "ERR" "FATAL" | "LOG" |
| _echo | System Echo | - | - | - |

### Static Methods

The following methods is defined in Round using the native programming language statically. Developers can't override the static methods.

| Method Name | Perpose | Params |
|-|-|-|
| _get_node_info | Get a node name | - |
| _get_node_stats | Get a node name | - |

## Trigger

| Trigger Name | Perpose | Params | Outputs | Default |
| --- | --- | --- | --- | --- |
| _pre_activate | - | - | - | - |
| _post_activated | - | - | - | - |
| _pre_closed | - | - | - | - |
| _post_closed | - | - | - | - |
| _method_added | - | - | - | - |
| _method_removed | - | - | - | - |
| _method_updated | - | - | - | - |
| _message_received | - | - | - | - |
| _message_executed | - | - | - | - |
| _log_occurred | - | - | - | - |
| _node_added | - | - | - | - |
| _node_removed | - | - | - | - |
| _node_suspected | - | - | - | - |

## Supprted Programming Languages

You can combined .....

##### JavaScript

In JavaScript JSON encode

##### Java

In Java, Base64

| Method | Java Class |
| --- | --- |
| _get_node_name | _get_node_name |

```
public class _get_node_name {
  public _get_node_name() {
  }
  public String processEvent(String params) {
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
