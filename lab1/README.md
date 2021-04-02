# Two-Way Partition

## Build & Run

```sh
make
./lab1 [INPUT]
./verifier [INPUT] output.txt
```

## Method

- 跑 80 秒。
- 使用 openMP 開 16 個 thread。
- 使用 Fiduccia–Mattheyses algorithm
    - 隨機產生 balanced partition
    - 將 FM 的結果跑到 cut 數量收斂，再重新回到上一步。