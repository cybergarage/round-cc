![round_logo](./img/round_logo.png)

# Tour of Round

The tour explains main functions of Round using a client utility command, `round`.

To use the utility, start a single node of Round at first:

```
roundd
```

Next, let's start the client utility command:

```
round shell
```

To show all commands of `round`, use `help` command:

```
round> help
```

## Nodes

To check nodes in the clusters, use `list` command:

```
round> list
[round]                   # --> cluster name
  [0] 192.168.100.26:7476 # --> node ipaddr:port
```

## Methods

In this section, add a simple `echo` method which returns the given parameters as it is using JavaScript.

Each node of Round is a programmable node using some programming languages such JavaScript and Lua. To create the `echo` method, use `set_method` as the following:

```
round> set_method(0, { "lang":"js", "code":"function echo(params) {return params;}" })
round> OK
```

The `set_method` is a embedded method to add new methods by developers. To confirm whether the `echo` method is added, use `get_config` method:
