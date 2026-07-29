# C & C++ Programming Projects

This repository contains coursework and programming exercises completed while studying Computer Information Systems at Okanagan College.

The projects demonstrate knowledge of:

- C programming
- C++
- Object-oriented programming
- Threads
- Concurrent processes
- Matrix operations
- Algorithms
- String manipulation
- Memory management
- Header files

  ## Algorithms

  ### Student Number Validation (Constant Space)

This program reads student numbers from a text file and determines whether each student number contains only unique digits.

Algorithm:

1. Counts the number of lines in the input file.
2. Returns to the beginning of the file.
3. Reads each student number one at a time.
4. Compares it with the remaining student numbers using nested loops.
5. Checks whether each student number contains unique digits.

Characteristics:

- Time Complexity: **O(N² × M)**
- Space Complexity: **O(1)** (constant space)

This approach minimizes memory usage by processing the file directly instead of storing all records in memory. The trade-off is slower execution because each student number is compared multiple times.

  ### Student Number Validation (Optimized)

This program reads student numbers from a text file and determines whether each student number contains only unique digits.

Algorithm:

1. Counts the number of lines in the input file.
2. Returns to the beginning of the file.
3. Stores every student number in memory.
4. Sorts the data using the C standard library `qsort()` function.
5. Iterates through the sorted list and checks each student number for unique digits.

Characteristics:

- Time Complexity: **O(N log N × M)**
- Space Complexity: **O(N)**

This implementation is significantly faster because sorting reduces the number of comparisons required. The trade-off is increased memory usage since all student numbers must be stored before processing.
 
  ## Matrix Operations (C++)

Implemented matrix operations using multiple header files.

Features:

- Matrix addition
- Matrix subtraction
- Matrix multiplication
- Modular project structure

  ## Multithreading (C)

Implemented thread creation and synchronization using C.

## Concurrent Processes

Implemented process creation and communication concepts.

