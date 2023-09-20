# Nyctalis
Nyctalis is a (for now) x86_64 kernel written in C++

## Prerequisites
You'll need the following to build Nyctalis:

### Tools
- [CMake](https://cmake.org/)
- [Ninja](https://ninja-build.org/)
- [QEMU](https://www.qemu.org/)
- [Xorriso](https://www.gnu.org/software/xorriso/)
- [Mtools](https://www.gnu.org/software/mtools/)

### Compiler
You'll need a cross-compiler for x86_64-elf. You can find instructions on how to build one [here](https://wiki.osdev.org/GCC_Cross-Compiler).

It is recommended to build the libgcc with no red zone support. This can be done by following the instructions [here](https://wiki.osdev.org/Libgcc_without_red_zone).

## Building
1. **Create the `build` directory**:
```bash
mkdir build && cd build
```

2. **Prepare the project**:
```bash
CC=<path_to_your_c_compiler> CXX=<path_to_your_cpp_compiler> cmake -G ninja ..
```

3. **Build the project**:
```bash
ninja
```

4. **Run the project**:

You need to be in the root directory of the project to run Nyctalis.
```bash
qemu-system-x86_64 -cdrom dist/x86_64/nyctalis.iso
```
