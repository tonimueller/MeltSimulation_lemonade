# LeMonADE - Melt  simulation

Test to create and simulate a melt of linear chains. 

## Compilation 
This project needs the [LeMonADE-library](https://github.com/LeMonADE-project/LeMonADE/) installed. The configure file helps to set the correct path and options. Execute in a shell 
```shell 
./configure -DLEMONADE_DIR=/path/to/installation/lemonade_install -DBUILDDIR=./build -DLEMONADE_TESTS=OFF/ON -DCMAKE_BUILD_TYPE=Release/Debug
```
This will run `cmake` and create the `build` directory. Now type in `make` which compiles the executables and runs the test if this option was given.

