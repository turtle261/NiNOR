## NiNOR

A finite, directed cyclic graph (DCG) of N-input NOR (NiNOR) gates can, given a starting state, perform any computation that a Turing Machine with finite memory can execute. 

This project aims to develop an emulator thereof, and act as a library for building such emulators.

The idea comes from [James Bowery](https://github.com/jabowery): https://groups.google.com/g/ait0/c/D1wd2fV6Ax4 

## Usage

This essentially works currently as an emulator of [Turing's A-type Machines](https://weightagnostic.github.io/papers/turing1948.pdf), though using NOR rather than NAND.

You can invert the input bits and the output bits of the graphs and get equivalent results to a NAND A-type machine.

You can write a graph file as per the examples in ./graphs/, and run them and compute them to any arbitrary tick(in this example 999 steps) like this:

```bash
./dcg graphs/complex.txt 999
```
This will print to stdout the graph in the same format as the input format, except stepped 999 times.

A graph file is a text file with newline seperated node declarations and node pointer definitions.
For example:
```
node a 1
node b 0
a->b
```
line 1: This defines a node as a(which it interprets as hexadecimal), with an initial output of 1.

line 2: It defines a second node with an initial output of 0.

line 3: It makes node a point to node b

Right now a maximum of 65535 nodes may be used, until I optimize things further. 
Each node must have a unique hexadecimal value as its identifier.

if you run `./dcg graphs/complex.txt` or equivalently `./dcg graphs/complex.txt 0` -- it will interpret the graph internally and print it back out equivalently, though perhaps with ordering differences.

Likewise, if you run `./dcg graphs/complex.txt 1 > complex_after_1_step.txt` and then do `./dcg complex_after_step_1.txt 1` -- the result printed to stdout will be equivalent to the output of `./dcg graphs/complex.txt 2`  

## License
This is Free Software available under the terms of the (brief) ISC license, visible in this repository as the file LICENSE.

