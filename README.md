# zipfs-rw

zipfs-rw is a FUSE filesystem that mounts a ZIP file to a directory and provide transparent access

This project is under the pre-alpha stage.

## Build from source

### Dependencies

The following dependencies needs to be setup before building with Meson.

*   Development dependencies
    *   Meson or Muon
    *   Ninja, Samurai, or other Meson backends
    *   Pkg-Config
*   Test dependencies
    *   Bash
    *   FindUtils (for the `find` command)
    *   ShellCheck
    *   InfoZip Unzip (the `unzip` command)
    *   InfoZip Zip (the `zip` command)
*   Run-time dependencies
    *   [libfuse](https://github.com/libfuse/libfuse)
    *   [libzip](https://github.com/nih-at/libzip)

### Build with Meson

This project uses Meson as a packaging-independent configuration generator.
It supports several builders ("backends") such as Ninja, but Make is not supported by design.

Build as

```sh
meson setup build.tmp
cd build.tmp
meson compile
```

To build with Ninja explicitly, replace `meson compile` with

```sh
ninja
```

### Build with Nix

This project provide Nix expression for packaging and environment setup.
All the dependencies will be automatically prepared during build.

Build as

```sh
nix build .?submodules=1
```

## Development

Contributions and feedbacks are welcome.

### Coding style

This project borrows the coding style from the Linux Kernel. The guide can be found below:

https://www.kernel.org/doc/html/v6.0/process/coding-style.html

To ease the maintenance, please run `fetch-clang-format` to fetch the `.clang-format` file from the Linux Kernel project and place it at the project root.
The fetched `.clang-format` is excluded from the source tree for license compatibility.

### Nix-based development environment

This project uses Nix as a project manager.
To enter a shell with the build environment (and all the dependencies) set up, run

```sh
nix develop
```

or, for non-flake workflow,

```sh
nix-shell
```

Type `exit` or press <kbd>Ctrl-d</kbd> to exit the development shell.

### Tests

The tests can be found in the `test` directory.

Run with

```sh
meson setup build.tmp
cd build.tmp
meson test
```

To run specific tests, replace the last line with

```sh
meson test <test-id> [<test-id2> <test-id3>]
```

The test cases inside `tests/libfuse-examples` and `tests/libzip-examples` are not about the project source itself, but the libraries (`libfuse` and `libzip`).
The original purpose of these test cases are to get ourselves familiar with the libraries when developing this project.
We keep it here in the hope to provide a quick impression about how these libraries can be called.

The sample ZIP archives can be generated at `build.tmp/test/samples/sample-<name>.zip` with

```sh
meson compile sample-<name>
```

Here is the list of available samples:
*   sample-hello: It contains text files and directories
*   sample-special: It is made by having `zip` read from a FIFO file.
*   sample-symlinks: It contains a bunch of symbolic links
