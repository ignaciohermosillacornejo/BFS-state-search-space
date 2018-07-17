# Assignment N3
Course IIC2133 @ PUC (2018-1) - Data structures and algorithms 

A C implementation of a BFS aproach to a State search space problem utilizing a zobrist hash. It still run's slow do to errors in the handling of collisions on my hash table so only tests 0, 1 and 2 complete in a reasonable time

To run, first execute move into "Programa" folder

```bash
cd Programa
```

and then execute the Makefile

```bash
make
```

If you are on a windows machine or ubuntu, you may need to change line 10 of the Makefile to target your instalation of GCC.
\
To run the program, execute the following code. In this example we are running the code on test 0

```bash
./solver tests/test0.txt

To see a graphical representation, go to

https://iic2133-puc.github.io/