# zipfs-rw

zipfs-rw is a FUSE filesystem that mounts a ZIP file to a directory and provide transparent access

This project is under the pre-alpha stage.

## Development

Contributions and feedbacks are welcome.

### Coding style

This project borrows the coding style from the Linux Kernel. The guide can be found below:

https://www.kernel.org/doc/html/v6.0/process/coding-style.html

To ease the maintenance, please run `fetch-clang-format` to fetch the `.clang-format` file from the Linux Kernel project and place it at the project root.
The fetched `.clang-format` is excluded from the source tree for license compatibility.
