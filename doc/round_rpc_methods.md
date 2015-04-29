![round_logo](./img/round_logo.png)

# RPC Methods

Round node has some embedded system methods which are added using native or dynamic programming languages as default.

## System Methods

In the system methods, there are two kind of types: the static and dynamic. The static method can't be overriden by developers, but the dynamic method can can be overriden using 'set_method'.
Â
### Static Methods

Round has the following static methods as default. The methods are implemented using the native programming language, developers can't redefine the static methods.

| Method Name | Description |
| --- | --- |
| set_method | Set a new script method |
| set_route | Set a new route |
| set_timer | Set a new timer |
| set_alias | Set a alias for the other method |

#### set_method

```
set_method := "{" name language code encoding "}"

name     = "name" ":" TOKEN
language = "language" ":" supported-language
code     = "code" ":" TOKEN
encoding = "encoding" ":" ("none" | "base64")

supported-language = ("js" | "java" | "tcl" | "lua")
```

If the code parameter isn't specified, the method is removed.

#### post_job

```
post_job := "{" language code encoding "}"

language = "language" ":" supported-language
code     = "code" ":" TOKEN
encoding = "encoding" ":" ("none" | "base64")

supported-language = ("js" | "java" | "tcl" | "lua")
```

If the code parameter isn't specified, the method is removed.

#### set_route

```
set_route := "{" name source destnation  [type] [cond] [params] "}"

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

#### set_timer

```
set_timer := "{" name [start_time] [stop_time] [cycle_interval] [loop] "}"

name           = "name" ":" TOKEN
start_time     = "start_time" ":" INTEGER
stop_time      = "stop_time" ":" INTEGER
cycle_interval = "cycle_interval" ":" INTEGER
loop           = "loop" ":" BOOL
```

#### set_alias

```
set_alias := "{" name [method] [defaults]"}"

name     = "name" ":" TOKEN
method   = "method" ":" TOKEN
defaults = (json-rpc-default | json-rpc-params-default)*

json-rpc-default        = ("dest" | "quorum" | "cond" | "type") ":" TOKEN
json-rpc-params-default = "params".TOKEN ":" TOKEN
```

If the code method isn't specified, the alias is removed.

### Native Methods

Round adds the following default native methods. The methods are implemented using the native programming language, but developers can override the default methods using '_set_method'.

| Method Name | Description | Params | Outputs | Default |
| --- | --- | --- | --- | --- |
| get_clusters | Gat a cluster list which the specified node knows | - | - | - |
| get_nodes | Gat a node list which the specified node is belong | - | - | - |
| get_node_state | Get a node infomation | (none) | {"name" : (string), "ip" : (address), "port" : (number),  "hash" : (string) } | - |
| get_node_config | Get the node configuration | (none) | - | - |
| get_node_stats | Get the node statistics | (none) | - | - |


| Method Name | Description | Params | Outputs | Default |
| --- | --- | --- | --- | --- |
| get_node_sharedkey | Set a shared key for HMAC | - | - | - |
| get_node_msg_digest | Set a shared key for HMAC | - | - | - |
| get_log_level | Get the current log level | (none) | "TRACE", "LOG", "WARN", "ERR" "FATAL" | "LOG" |
| echo | System Echo | - | - | - |

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
