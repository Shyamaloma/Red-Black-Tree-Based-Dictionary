# Red-Black Tree Dictionary (C++)

## Overview

This project implements a **Dictionary Abstract Data Type (ADT)** using a **Red-Black Tree** in C++. The dictionary stores key-value pairs where keys are strings and values are integers, maintaining balanced tree properties to ensure efficient operations.

The project also includes two client programs:

* `Words.cpp`: extracts unique words and preserves insertion order
* `WordsFrequency.cpp`: counts word frequencies from an input file

This project demonstrates core concepts in:

* Data structures (balanced binary search trees)
* Object-oriented programming in C++
* File I/O and string processing
* Iterators and ordered traversal

---

## Features

### Red-Black Tree Implementation

* Self-balancing binary search tree

* Maintains **O(log n)** time complexity for:

  * insertion
  * deletion
  * search

* Includes:

  * Left and right rotations
  * Insert and delete fix-up procedures
  * Node coloring (RED / BLACK)

Example implementation detail:

> The tree maintains balance using rotations and recoloring during insertion and deletion

---

### Dictionary ADT

* Stores `(key, value)` pairs

* Keys are **strings**, values are **integers**

* Supports:

  * insertion and update (`setValue`)
  * deletion (`remove`)
  * lookup (`contains`, `getValue`)
  * traversal via iterator (`begin`, `next`, `prev`)

* Maintains a **current iterator** for ordered traversal:

> The iterator allows forward and reverse traversal over keys

---

### Ordered Traversals

* In-order traversal (sorted output)
* Pre-order traversal (with color indication)
* Custom word-only traversal

Example:

> In-order traversal outputs key-value pairs in sorted order

---

## Client Programs

### 1. Words.cpp

Extracts **unique words** from an input file.

* Removes punctuation using delimiters
* Stores words in the dictionary
* Assigns each word an **insertion order index**
* Outputs:

  * ordered indices
  * list of words

Example usage:

```bash
./Words input.txt output.txt
```

> Words are parsed and inserted only if they do not already exist

---

### 2. WordsFrequency.cpp

Counts **frequency of each word** in a file.

* Converts words to lowercase
* Tracks occurrences using dictionary values
* Outputs sorted `(word : frequency)` pairs

Example usage:

```bash
./WordsFrequency input.txt output.txt
```

> Existing words have their frequency incremented dynamically

---

## Project Structure

```bash
.
├── Dictionary.h        # Header file for Dictionary ADT
├── Dictionary.cpp      # Red-Black Tree implementation
├── Words.cpp           # Unique word extraction program
├── WordsFrequency.cpp  # Word frequency counter
├── Makefile            # Build configuration
```

---

## Build Instructions

Compile the project using the Makefile:

```bash
make
```

This will generate the executables:

* `Words`
* `WordsFrequency`

---

## Usage

### Run Words Program

```bash
./Words <input file> <output file>
```

### Run Word Frequency Program

```bash
./WordsFrequency <input file> <output file>
```

---

## Key Implementation Details

### Red-Black Tree Properties

* Every node is either red or black
* Root is always black
* No two consecutive red nodes
* Every path has the same number of black nodes

### Tree Operations

* **Insertion**

  * Standard BST insert followed by fix-up
* **Deletion**

  * Uses transplant + fix-up procedure
* **Balancing**

  * Achieved via rotations and recoloring

---

## What This Project Demonstrates

* Implementation of a complex data structure from scratch
* Efficient memory management using dynamic allocation
* Recursive tree traversal techniques
* Use of iterators for ordered data access
* Real-world application of trees in text processing

---

## Possible Improvements

* Add support for generic value types (templates)
* Improve tokenizer for better text parsing
* Add unit tests
* Benchmark performance vs STL `map`

---

## Author

Shyam Kishan
