# C Data Structures

This repository contains a **low-level implementation** of all **basic data structures** using `C` programming language implemented completely from Scratch to **understand how they work internally**.

## Core Design and Architecture

- **Standalone Files**: Every file in this repository is a completely independent, self contained program. 
- **No Header or Dependencies**: There are no external header files or shared helper files. Each file includes its main() function.
- **Built from Scratch**: Implemented using low-level memory management and pointer operations without relying on any external libraries.  
 
This design makes it extremely **easy to compile** and read any **specific data structure implementation** on its own.

## Implemented Data Structures
The repository covers **fundamental structures** ranging from **basic arrays** to **BST** and **hash tables**.

1. **Array**: Linear data storage, basic **index-based** operations and **dynamic implementations using pointers**, featuring searching and sorting algorithms.
2. **Linked List**: Pointer-based dynamic lists including **(singly, doubly, circular)** implementations with advanced features such as (insert_in_order, searching and sorting).
3. **Stack**: **LIFO** (Last In, First Out) structures implemented **using arrays and linked lists**.
4. **QUEUE**: **FIFO** (First In, First Out) structures implemented **using arrays and linked lists**.
5. **BST (Binary Search Tree)**: Hierarchical tree structures with insertion, deletion and advanced features (such as rebalance, traversal algorithms).
6. **Hash Table**: Key-value mapping implemented with core hash table function and collision handling.

## How to Compile and Run

As every file is a standalone program, you can compile and run any individual file directly using `gcc` compiler from its specific folder:
1. Navigate to the desired data structure folder (e.g., Linked_list):
    ```
        cd Linked_list
    ```
2. Compile the specific file:
    ```
        gcc -o circular_list circular_list.c
    ```
3. Run the executable file:
    ```
        ./circular_list
    ```
