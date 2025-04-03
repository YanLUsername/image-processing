# image-processing
A Linux-based program written in C. It was developed as part of a university course on systems programming to demonstrate the use of intermediate data structures in C for image manipulation tasks.

Note: This is a simplified version of a project developed for EECS22 at the University of California, Irvine. Some files have been omitted.

### Project Versions
Each version uses a different data structure approach for handling image data:
- [Version 1 – Static Arrays](./version1-arrays)
  - Stores image data using fixed-size 2D arrays
  - Demonstrates basic pixel manipulation and menu-driven interaction
  - Introduces modular programming and Makefile usage

- [Version 2 – Dynamic Memory Allocation](./version2-dynamic)
  - Uses `malloc()` to allocate image data dynamically at runtime
  - Supports flexible image sizes and more scalable memory usage
  - Emphasizes pointer arithmetic and dynamic resizing

- [Version 3 – Doubly Linked List](./version3-linked-list)
  - Stores image pixels in a custom doubly linked list structure
  - Enables efficient traversal and modifications across pixels
  - Highlights advanced data structures and memory management

### Tools & Environment
- Language: C (Standard: C11)
- OS: Linux
- Compiler: gcc
- Build: Makefile based
