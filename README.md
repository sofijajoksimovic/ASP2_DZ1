# ASP2 - DZ1: Algorithms and Data Structures 2 - AVL tree and Lozanic Triangle

## Overview

This repository contains the solution to the first homework assignment (DZ1) from the *Algorithms and Data Structures 2* course (ASP2). The assignment focuses on two main problems that test the implementation and optimization of data structures, particularly binary trees and search algorithms.

## Problem 1: Linear Data Structure Search [45 points]

In this problem, the task was to implement a program that compares the performance of different search techniques for a given Lozanić Triangle. 

### Lozanić Triangle

The Lozanić Triangle is a mathematical structure similar to Pascal's Triangle, where the edge values are always 1, and the internal values follow specific rules based on their positions. The triangle allows for several types of searches, such as binary search, ternary search, and interpolation search, to find specific elements.

The program implemented:
- **Binary and interpolation search**
- **Ternary and interpolation search**
- **Binary and ternary search**

The user can input a row number and search for specific values using these techniques. The program compares the performance of each search method in terms of execution time and search steps.

## Problem 2: Set Implementation Using AVL Tree [55 points]

This part of the assignment required the implementation of integer sets using an AVL tree. The AVL tree ensures that the tree is balanced, providing efficient set operations.

Operations included in the AVL tree implementation:
- **Insert**: Add an element to the set.
- **Membership check**: Determine if an element is present in the set.
- **Tree print**: Display the current elements in the tree in a formatted manner.
- **Delete**: Remove an element from the set.

Additionally, the following set operations were implemented:
- **Union**: Combine two sets (all elements from both sets).
- **Intersection**: Find the common elements between two sets.
- **Difference**: Get elements that are in one set but not the other.
- **Symmetric difference**: Get elements that are in exactly one of the sets.

The AVL tree ensures that the operations are efficient, with logarithmic time complexity for insertions, deletions, and lookups.

## Menu System

A menu-driven system was implemented to allow users to interact with the program. Through the menu, users can:
- Input parameters for operations.
- Execute different operations such as searching in the Lozanić Triangle or performing set operations with AVL trees.
- Compare the performance of search techniques.

## Requirements

The program is written in C or C++ and implements both recursive and iterative techniques as specified in the problem description. The use of recursive solutions for AVL trees was avoided to adhere to performance requirements, focusing on iterative techniques instead.

