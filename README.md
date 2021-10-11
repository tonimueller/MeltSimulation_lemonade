# LeMonADE - Phantom Modulus

This software package calculates the Phantom modulus for the following systems: 
- linear chains mixed with cross linkers 

## Compilation 
This project needs the [LeMonADE-library](https://github.com/LeMonADE-project/LeMonADE/) installed. The configure file helps to set the correct path and options. Execute in a shell 
```shell 
./configure -DLEMONADE_DIR=/path/to/installation/lemonade_install -DBUILDDIR=./build -DLEMONADE_TESTS=OFF/ON -DCMAKE_BUILD_TYPE=Release/Debug
```
This will run `cmake` and create the `build` directory. Now type in `make` which compiles the executables and runs the test if this option was given.


## Linear chains with cross linkers 
The main [program](https://github.com/LeMonADE-project/LeMonADE_PhantomModulus/blob/master/projects/ForceEquilibrium.cpp) reads in a .bfm file and a data file. It is expected that the bfm file contains the following flags 
```
#!number_of_linear_chains=value
#!number_of_crosslinkers=value
#!chainLength=value
#!functionality=value
#!nMonomersPerCrossLink=value
!reactivity
1-1:1/2
...
```
Moreover, it is expected that in the bfm file first all chains and afterwards all crosslinks are given. 
The data file should be created during the connection process and needs to contain: 
```
Time ChainID MonID1 P1X P1Y P1Z MonID2 P2X P2Y P2Z
```
where MonID1 and MonID2 are the cross link ID starting at 0. ChainID starts at 0 as well.
For the calculations only the ChainID and MonID1 is needed. The remaining fields are arbitrary for a correct 
calculation of the positions of the cross links in a force equilibrium. 
(The format was given from a previous simulation.)
