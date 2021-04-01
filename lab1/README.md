# Two-Way Partition

## Build

```sh
make
./lab1 [INPUT]
./verifier [INPUT] output.txt
```

## Method

- Fiduccia–Mattheyses algorithm
    - Generate initial partition randomly
    - Use OpneMP run $\min(10^5, \displaystyle\frac{5 \times 10^8}{P})$ times F-M algorithm, where $P$ is the sum of degrees.