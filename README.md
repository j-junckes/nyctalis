# Nyctalis

Nyctalis is a (for now) x86_64 kernel written in C++

## Building

1. **Create the `build` directory**:
```bash
mkdir build && cd build
```

2. **Prepare the project**:
```bash
cmake .. -G ninja
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
