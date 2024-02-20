# With `gcc`

```
g++ -S simple_struct.cpp -fverbose-asm -masm=intel -Os -o -
```

**Note**: If you don't see some statements, remove `-Os` flag

## `gcc` parameters

### `-masm=intel`

[Intel syntax](https://en.wikipedia.org/wiki/X86_assembly_language#Syntax) is chosen.

### `-Og`

Optimize for size

### `-fverbose-asm`

Put extra commentary information in the generated assembly code to make it more readable

### `-S`

Stop after the stage of compilation proper; do not assemble. The output is in the form of an assembler code file for each non-assembler input file specifies

**Note**: file `simple_struct.s` is generated

# With `objdump`

First we should create object file:

```
g++ -gc simple_struct.cpp 
```
Then we can use

```
objdump -d -M intel -S simple_struct.o
```

## `gcc` parameters

### `-g`

Debug symbols

### `-c`

Compile or assemble the source files, but do not link. The linking stage simply is not done. The ultimate output is in the form of an object file for each source file.

**Note**: file `simple_struct.o` is generated

# With `CMake`

At present only `gcc` is supported.
```
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "-masm=intel -fverbose-asm")
endif()
``` 


## How to compile

Let's say yo want to run `CMake` for the first time:

```
mkdir build
cd build
cmake ..
cd src/cpp17/assembly/
```
Then to generate assembly files:

```
make src/simple_struct.s
vim CMakeFiles/simple_struct.dir/src/simple_struct.cpp.s
```

For preprocessor files:

```
make src/simple_struct.i
vim CMakeFiles/simple_struct.dir/src/simple_struct.cpp.i
```
