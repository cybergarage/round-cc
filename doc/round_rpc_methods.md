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
| set_route | Set a new route |
| set_timer | Set a new timer |

#### set_method

```
set_method := "{" name language code encoding "}"

name     = "name" ":" TOKEN
language = "language" ":" supported-language
code     = "code" ":" TOKEN
encoding = "code" ":" ("none" | "base64")

supported-language = ("js" | "java" | "tcl")
```

If the code parameter isn't specified, the method is removed.

#### set_route

```
set_route := "{" name source destnation [params] [type] [cond]"}"

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

#### set_timer

```
set_timer := "{" name [start_time] [stop_time] [cycle_interval] [loop] "}"

name           = "name" ":" TOKEN
start_time     = "start_time" ":" INTEGER
stop_time      = "stop_time" ":" INTEGER
cycle_interval = "cycle_interval" ":" INTEGER
loop           = "loop" ":" BOOL
```

### Native Methods

Round adds the following default native methods. The methods are implemented using the native programming language, but developers can override the default methods using '_set_method'.

| Method Name | Description | Params | Outputs | Default |
| --- | --- | --- | --- | --- |
| get_node_info | Get a node infomation | (none) | {"name" : (string), "ip" : (address), "port" : (number),  "hash" : (string) } | - |
| get_cluster_info | Gat a cluster information which the specified node is belong | - | - | - |
| get_network_info | Gat a cluster list which the spcecified node knows | - | - | - |
| get_node_sharedkey | Set a shared key for HMAC | - | - | - |
| get_node_msg_digest | Set a shared key for HMAC | - | - | - |
| get_log_level | Get the current log level | (none) | "TRACE", "LOG", "WARN", "ERR" "FATAL" | "LOG" |
| echo | System Echo | - | - | - |

## Trigger

| Trigger Name | Perpose | Params | Outputs | Default |
| --- | --- | --- | --- | --- |
| pre_activate | - | - | - | - |
| post_activated | - | - | - | - |
| pre_closed | - | - | - | - |
| post_closed | - | - | - | - |
| method_added | - | - | - | - |
| method_removed | - | - | - | - |
| method_updated | - | - | - | - |
| message_received | - | - | - | - |
| message_executed | - | - | - | - |
| log_occurred | - | - | - | - |
| node_added | - | - | - | - |
| node_removed | - | - | - | - |
| node_suspected | - | - | - | - |
