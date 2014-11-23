![round_logo](./img/round_logo.png)

# Round APIs

## APIs

| Parameter | M/U | Detail | Default | Constants |
|-|-|-|-|-|
| Method | M | Operation Method | - | GET, PUT |
| Sync | O | URI | Sync | Async,Sync |
| Destination | O | URI | Random | Random, ConsistentHash |
| Resouse | O | URI | (NULL) | - |
| Quarum | O | Operation Method | NONE | NONE, ALL, Number |
| Target | O | Operation Target | DEST | DEST, ALL, Number |
| Data | O | Operation data | (NULL) | - |

## Notifications

| Type |
|-|
| Cluster Changed |
| Node Added |
| Node Removed (Failed) |
| Node Suspected |
| Node Remained |
