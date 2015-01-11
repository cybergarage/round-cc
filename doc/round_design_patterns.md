![round_logo](img/round_logo.png)

# Design Patterns

## Default

### Default Parameters

### Configuration

## Execution

### Pipeline

### Quorum

![Quorum  Pattern](img/round_dp_quorum.png)

```
{
  methods : [
    {jsonrpc : "2.0", "method":"exec_method", ....}
    {jsonrpc : "2.0", "method":"filter_method", ....}
  ]

  routes : [
    {src : "exec_method", dest : "filter_method"}
  ]
}
```

### Transaction

### Client Centric Consistency

such as eventual consistency.

### Mult Cluster

Map Reduce Pattern

### Transaction

JSON-RPC batch

## Decide

### Vote

### Election

## Failer Detection

### Node Repair

### Failer Detection

### Immutable

In distributed system
