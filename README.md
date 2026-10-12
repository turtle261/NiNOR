## NiNOR

A finite, directed cyclic graph (DCG) of N-input NOR (NiNOR) gates can, given a starting state, perform any computation that a Turing Machine with finite memory can execute. 

This project aims to develop an emulator thereof, and act as a library for building such emulators.

The idea comes from [James Bowery](https://github.com/jabowery): https://groups.google.com/g/ait0/c/D1wd2fV6Ax4 

## Usage

This essentially works currently as an emulator of Turing's A-type Machines, though using NOR rather than NAND. You can invert the input bits and the output bits of the graphs and get equivalent results to a NAND A-type machine.

You can write a graph file as per the examples in ./graphs/, and run them and compute them to any arbitrary tick(in this example 999 steps) like this:

```bash
./dcg graphs/complex.txt 999
```
