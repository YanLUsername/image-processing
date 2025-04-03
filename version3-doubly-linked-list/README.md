# Version 3 – Doubly Linked Lists
This version of the image processing program uses **doubly linked lists** to store and manipulate image data. 

Instead of using RGB values, the movie will be in YUV format (http://en.wikipedia.org/wiki/YUV).
YUV is broken down into three channels, the Y, U, and V channel. Each channel for one pixel is represented by a value between 0 and 255.
Version 3 will create and modify a movie rather than an image. The movie will be at a fixed 60 frames and resolution 512 × 288 pixels/frame.  The program should also be able to handle movies of different resolution. The movie is played using a free X server, XMing.

### Features
- Uses a doubly linked list to store image pixel data
- Traversal in both directions, allowing row/column-wise operations
- More advanced image/movie manipulation techniques

### Learning Highlights
- Introduction to **doubly linked lists** in C
- Memory management through the use of `Malloc()` and **Valgrind**
- Modular program structure with **header and source files**
- Use of **makefiles** for automating compilation and managing multiple source files  

Note: This is a simplified version of a project developed for EECS22 at the University of California, Irvine. Some files have been omitted. What you see here only highlights the most important elements.
