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

$ ./benchmark-this-repository
my,insert,1000000,13658
my,search,1000000,905260
my,delete,1000000,760527

$ ./benchmark-linux-kernel-rbtree
linux,insert,1000000,12692
linux,search,1000000,789695
linux,delete,1000000,522311
```
