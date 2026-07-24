# Rust C Interop
This repository provides a clear, end‑to‑end example that demonstrates how Rust can interoperate with pre-built C library.

Note: This document is in progress. Feel free to ask questions in Discussions. Use Issues only for bugs/improvements to the code.

## Directory structure

This repository has the following directory tree:

```
   - .
  87 ├── .gitignore
  85 ├── Cargo.toml
2.1k ├── README.md
   - ├── c-lib-example
1.0k │   ├── CMakeLists.txt
 624 │   ├── meson.build
   - │   ├── include
1.2k │   │   └── sample_clib.h
   - │   ├── src
2.0k │   │   └── sample_clib.c
   - │   └── test
1.0k │       └── test.c
   - ├── examples
  51 │   ├── shared_main.rs
 149 │   └── static_main.rs
   - └── src
9.7k     ├── bindgen_output.rs
 239     └── lib.rs

```

## Build the C library

The following example covers a C library in the directory `c-lib-example` as shown

```
   - c-lib-example
1.0k ├── CMakeLists.txt
 624 ├── meson.build
   - ├── include
1.2k │   └── sample_clib.h
   - ├── src
2.0k │   └── sample_clib.c
   - └── test
1.0k     └── test.c
```

Here, the source files include the header file `include/sample_clib.h`, the implementation `src/sample_clib.c`, and a test file `test/test.c`

Since we are going to link pre-built library to rust, we should know how to compile it. There are a number of ways to go about this.

### Manually building with C compiler

There are no shortages of C compilers: [GNU GCC](https://gcc.gnu.org/), [Clang](https://clang.llvm.org/), [TCC](https://bellard.org/tcc/), [MingW](https://www.mingw-w64.org/), [MSVC](https://visualstudio.microsoft.com/vs/features/cplusplus/), and so on. Although this document shows usage with GCC, the flags are quite similar across all the compilers.

For this example, we will build a shared library, and a static library. First we create the following folder directory

```
mkdir out out/lib out/include
```

The following command would create an object file

```
gcc -c -I ./c-lib-example/include ./c-lib-example/src/sample_clib.c -o ./out/lib/sample_clib.o
```

Then use the `ar` tool to combine a given set of object files into a single static library. 

```
ar rcs <final_lib.a> <obj_file.o>, ... <obj_file.o>
```

In this example, there is only one object file, which would be processed as

```
ar rcs ./out/lib/libsample_clib.a ./out/lib/sample_clib.o
```

Note that we have named the static library as `libsample_lib.a`, attaching the prefix "lib". This is due to the standard for C library.

Making a shared library is similar, we start by creating an object file. This time, we add the `-fPIC` flag as shown

```
gcc -c -I ./c-lib-example/include ./c-lib-example/src/sample_clib.c -fPIC -o ./out/lib/sample_clib.o
```

Use gcc again to create a shared library as shown

```
gcc -shared ./out/lib/sample_clib.o -o ./out/lib/libsample_clib.so
```


### Using build tools

It is easy to see that these commands can get troublesome to memorise and use. Furthermore, the standards/protocols change with compilers(obviously), but also with operating systems. To address this issue, modern build tools for C and C++ exist to offer cross-platform and cross-compiler build tools. This repository showcases two popular build tools, namely CMake and Meson. These build tools are [Meta-Build tools](https://en.wikipedia.org/wiki/List_of_build_automation_software#Meta_build), which means that they first create intermediate files and folders to prepare configuration of the project (we will refer to it as the "build directory"), and then build the project. 

#### CMake

CMake is a popular build tool for building C and C++ projects. To prepare the build directory, the command is as follows

```
cmake -S <source-dir> -B <build-dir>
```

For this example, the following command will do. Note that the current working directory (CWD) is the root of this repository for all scripts being executed.

```
cmake -S ./c-lib-example -B ./cmake-build
```

Thus, this command creates the intermediate build directory `cmake-build`. Next we can build the library by using the `--build` flag, and specifying the build directory.

```
cmake --build ./cmake-build --config RELEASE
```

Finally, we can install it using the `cmake --install` command. For this example, we can install the library in a custom folder using --prefix as shown.

```
cmake --install ./cmake-build --config RELEASE --prefix ./out
```


#### Meson

Similar to CMake, we begin with first creating a build directory. We can do that in Meson using the following

```
meson setup meson-build ./c-lib-example --buildtype release
```

And finally, we can create a release by using

```
meson install -C meson-build --destdir ./out
```

However, this value of `--destdir` is relative to the build directory, with prefix like `/usr/local`. On my machine, the directory tree of this folder is as follows

```
meson-build/out/
└── usr
    └── local
        ├── include
        │   └── sample_clib.h
        └── lib
            ├── libsample_clib.a
            └── libsample_clib.so
```

To make it consistent with previous examples, we can just move the `./meson-build/out/usr/local` folder as `./out`

```
mv ./meson-build/out/usr/local ./out
```


## Link the C library to the rust program.

We can use the link attribute to mark the unsafe extern functions to be linked with the given library (in this example, `sample_clib`).

```rust
#[link(name = "sample_clib", kind = "static")]
unsafe extern "C" {
    pub fn get_libtype() -> u8;

    pub fn sum_of_least_two(val_a: u16, val_b: u16, val_c: u16) -> u32;
}
```

As for an example, we can create a simple file as shown:

```rust
fn main() -> Result<(), ()> {
    let value = unsafe { wrapper_rust::get_libtype() };
    println!("Obtained value : {}", value);
    let least_two = unsafe {
        wrapper_rust::sum_of_least_two(10, 20, 40)
    };
    println!("sum_of_least_two(10, 20, 40) = {}", least_two);
    return Ok(());
}
```

Running cargo build will result in an error.

```
$ cargo run --example simple

error: could not find native static library `sample_clib`, perhaps an -L flag is missing?

error: could not compile `wrapper-rust` (lib) due to 1 previous error
```

We can see we need to indicate the location of the library. We can pass it as environment variables as shown

```
$ RUSTFLAGS="-L native=./out/lib" cargo run --example simple
Obtained value : 1
sum_of_least_two(10, 20, 40) = 30
```