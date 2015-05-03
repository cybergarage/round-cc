![round_logo](./img/round_logo.png)

# RPC Methods

Round node has some embedded system methods which are added using native or dynamic programming languages as default.

## System Methods

In the system methods, there are two kind of types: the static and dynamic. The static method can't be overriden by developers, but the dynamic method can can be overriden using 'set_method'.

### Static Methods

Round has the following static methods as default. The methods are implemented using the native programming language, developers can't redefine the static methods.

| Method Name | Description |
| --- | --- |
| set_method | Set a new script method |
| post_job | Post a job |
| set_route | Set a new route |
| set_timer | Set a new timer |
| set_alias | Set a alias for the other method |

#### set_method

The set_method method sets a new method into the local node.

##### Parameters

```
set_method = "{" name language code encoding "}"

name     = "name" ":" TOKEN
language = "language" ":" supported-language
code     = "code" ":" TOKEN
encoding = "encoding" ":" ("none" | "base64")

supported-language = ("js" | "java" | "tcl" | "lua")
```

If the code parameter isn't specified, the method is removed.

##### Return values

The set_method method doesn't return anything when the method is success, otherwise a error object.

#### post_job

The post_job method exec the specified code in the local node, and returns a result.

##### Parameters

```
post_job = "{" language code encoding "}"

language = "language" ":" supported-language
code     = "code" ":" TOKEN
encoding = "encoding" ":" ("none" | "base64")

supported-language = ("js" | "java" | "tcl" | "lua")
```

##### Return values

The post_job method returns a job result, otherwise a error object.

#### set_route

The set_route method sets a new route into the local node.

##### Parameters

```
set_route = "{" name source destnation  [type] [cond] [params] "}"

name       = "name"   ":" TOKEN
source     = "src"    ":" source-object
destnation = "dest"   ":" destnation-object
type       = "type"   ":" ("pipe" | "event")
cond       = "cond"   ":" JS_SCRIPT
params     = "params" ":" "{" *(param) "}"

source-object     = [cluster "."] [node "."] (trigger-name | method-name)
destnation-object = [cluster "."] [node "."] (method-name)
cluster           = ("local" | cluster-name)
node              = ("local" | "all" | "*" | hash-code)
cluster-name      = TOKEN
hash-code         = NODE_HASH
trigger-name      = TOKEN
method-name       = TOKEN

param                      = dest-in-param-name ":" dest-in-param-value-script
dest-in-param-name         = TOKEN
dest-in-param-value-script = JS_SCRIPT
```

##### Return values

The set_route method doesn't return anything when the method is success, otherwise a error object.

#### set_timer

The set_timer method sets a new timer into the local node.

##### Parameters

```
set_timer = "{" name [start_time] [stop_time] [cycle_interval] [loop] "}"

name           = "name" ":" TOKEN
start_time     = "start_time" ":" INTEGER
stop_time      = "stop_time" ":" INTEGER
cycle_interval = "cycle_interval" ":" INTEGER
loop           = "loop" ":" BOOL
```

##### Return values

The set_timer method doesn't return anything when the method is success, otherwise a error object.

#### set_alias

The set_alias method sets a new alias of a local method of the local node.

##### Parameters

```
set_alias = "{" name [method] [defaults]"}"

name     = "name" ":" TOKEN
method   = "method" ":" TOKEN
defaults = (json-rpc-default | json-rpc-params-default)*

json-rpc-default        = ("dest" | "quorum" | "cond" | "type") ":" TOKEN
json-rpc-params-default = "params".TOKEN ":" TOKEN
```

If the code method isn't specified, the alias is removed.

##### Return values

The set_alias method doesn't return anything when the method is success, otherwise a error object.

### Native Methods

Round adds the following default native methods. The methods are implemented using the native programming language, but developers can override the default methods using 'set_method'.

| Method Name | Description |
| --- | --- |
| set_registry | Set a new registry into the local node |
| get_registry | Get a registory from the local node |
| get_network_state | Get a cluster list which the specified node knows |
| get_cluster_state | Get a node list which the specified node is belong |
| get_node_state | Get a node information |
| get_node_config | Get the node configuration |
| get_node_stats | Get the node statistics |

#### set_registry

The set_registry method sets the specified key and value into the local node registry.

##### Parameters

```
set_registry = "{" key value "}"

key   = "key" ":" TOKEN
value = "value" ":" TOKEN
```

##### Return values

The set_registry method doesn't return anything when the method is success, otherwise a error object.

#### get_registry

The get_registry method returns a registry by the specified key from the local node registry.

##### Parameters

```
get_registry = "{" key "}"

key = "key" ":" TOKEN
```

##### Return values

The get_registry method a following JSON string, otherwise a error object.

```
result = "{" key value timestamp logical_timestamp"}"

key               = "key"   ":" TOKEN
value             = "value" ":" TOKEN
timestamp         = "ts"    ":" NUMBER
logical_timestamp = "lts"   ":" NUMBER
```

#### get_network_state

The get_network_state method returns a cluster list which the local node knows.

##### Parameters

This method has no parameter.

##### Return values

The get_network_state method returns a following JSON string, otherwise a error object.

```
result = { network-state }

network-state = "clusters" ":" (cluster-state)*

cluster-state = "cluster" ":" name nodes

name  = "name"  ":" TOKEN
nodes = "nodes" ":" (node-state)*

node-state = "{" cluster hash ip port state "}"

cluster = "cluster" ":" TOKEN
hash    = "hash"    ":" TOKEN
addr    = "addr"    ":" IPADDR
port    = "port"    ":" NUMBER
state   = "state    ":" ("active" | "stop")
```

#### get_cluster_state

The get_cluster_state method returns all nodes which the local node knows in the same cluster.

##### Parameters

This method has no parameter.

##### Return values

The get_cluster_state method returns a following JSON string, otherwise a error object.

```
result = { cluster-state }

cluster-state = "cluster" ":" name nodes

name  = "name"  ":" TOKEN
nodes = "nodes" ":" (node-state)*

node-state = "{" cluster hash ip port state "}"

cluster = "cluster" ":" TOKEN
hash    = "hash"    ":" TOKEN
addr    = "addr"    ":" IPADDR
port    = "port"    ":" NUMBER
state   = "state    ":" ("active" | "stop")
```

#### get_node_state

The get_node_state method returns the local node status.

##### Parameters

This method has no parameter.

##### Return values

The get_node_state method returns a following JSON string, otherwise a error object.

```
result = "{" cluster hash ip port state "}"

cluster = "cluster" ":" TOKEN
hash    = "hash"    ":" TOKEN
addr    = "addr"    ":" IPADDR
port    = "port"    ":" NUMBER
state   = "state    ":" ("active" | "stop")
```

## Trigger

| Trigger Name | Perpose | Params | Outputs | Default |
| --- | --- | --- | --- | --- |
| pre_activate | - | - | - | - |
| post_activated | - | - | - | - |
| pre_deactivate | - | - | - | - |
| post_activated | - | - | - | - |
| method_added | - | - | - | - |
| method_removed | - | - | - | - |
| method_updated | - | - | - | - |
| message_received | - | - | - | - |
| message_executed | - | - | - | - |
| log_occurred | - | - | - | - |
| node_added | - | - | - | - |
| node_removed | - | - | - | - |
| node_suspected | - | - | - | - |
