# S.O.S
Simply an "S.O.S" distress signal originated from my heart while I write this bunch of code

### Instructions
In order to build successfully, there should be a `i686` cross-compiler ready before you copying and pasting the commands into your terminal. I have not write the system checking routines yet (although I should) so please just manually check the requirements before running the makefile.

#### Requirements:
- A computer (running on Linux would be preferable)
- A cross-compiler for `i686` architecture
- `binutils` for the above architecture
- GRUB2
- QEMU
- GNU Make

#### Compile and Run in QEMU
* To build, simply type this (at top level):
```
make
```

* To create a disk img:
```
make create-img
```

* To test the disk img in qemu:
```
make run
```

* clean up:
```
make clean
```

### Current Progress
Just finish setting up the GDT. Nothing fancy.
