![round_logo](./img/round_logo.png)

# Tour of Round

The tour explains main functions of Round using the the client utility command.

First, start a single node of round:

```
roundd
```

Next, let's start the client utility command:

```
round shell
```
## Basic Commands

To check nodes in the clusters, use 'list' command as the following:

```
list
```

To show all commands, use 'help' command as sthe following.

```
help
```

## Methods

Each node of Round is a programmable node using some programming languages. In this tour, set a simple 'echo' method which returns the given parameters as it is using JavaScript.

```
set_method(*, {"lang":"js", "code"="function _echo(params) {return params;}"})
```
