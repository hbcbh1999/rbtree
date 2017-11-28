_Red-black Tree Implemented in C Language._

Test
----------
```
$ cd test
$ mkdir build
$ cd build
$ cmake ../
$ make
$ ctest --verbose
```

Benchmark
----------
```
$ sysctl -n machdep.cpu.brand_string
Intel(R) Core(TM) i5-5257U CPU @ 2.70GHz

| repository | action | nodes   | time      |
| ---------- | ------ | ------- | --------- |
| my         | insert | 1000000 |   13757us |
| my         | search | 1000000 |  908781us |
| my         | delete | 1000000 | 1672743us |
| linux      | insert | 1000000 |   13341us |
| linux      | search | 1000000 |  781067us |
| linux      | delete | 1000000 | 1414877us |

CFLAGS -O2:

| repository | action | nodes   | time      |
| ---------- | ------ | ------- | --------- |
| my         | insert | 1000000 |   13937us |
| my         | search | 1000000 |  784282us |
| my         | delete | 1000000 | 1408814us |
| linux      | insert | 1000000 |   13132us |
| linux      | search | 1000000 |  626353us |
| linux      | delete | 1000000 |  626354us |
```
