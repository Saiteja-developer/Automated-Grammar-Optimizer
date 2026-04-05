# Automated Grammar Optimizer (C + Docker)

##  Project Overview

The **Automated Grammar Optimizer** is a command-line tool developed in **C** that transforms a Context-Free Grammar (CFG) into a form suitable for **top-down parsers** such as LL(1) and recursive-descent parsers.

It detects and eliminates:

* Left Recursion
* Common prefixes (Left Factoring)

---

##  Objectives

* Prevent infinite recursion in parsers
* Reduce ambiguity in grammar
* Convert CFG into parser-friendly format

---

##  Technologies Used

* C Programming Language
* Docker (lightweight Alpine container)
* GCC Compiler

---

##  Project Structure

```
grammar-optimizer/
│
├── main.c
├── input.txt
├── Dockerfile
└── README.md
```

---

##  How to Run

### 1. Build Docker Image

```
docker build -t grammar .
```

### 2. Run Program

```
docker run -it grammar
```

---

##  Input Methods

###  Option 1: Manual Input

* Add grammar using menu
* Suitable for small examples and demo

###  Option 2: File Input

* Load grammar from `input.txt`

Example:

```
E->E+T|T
T->T*F|F
F->(E)|i
```

---

##  Sample Output

### Input:

```
E -> E+T | T
T -> T*F | F
```

### Output:

```
E -> T E'
E' -> +T E' | e
T -> F T'
T' -> *F T' | e
```

---

##  Features

✔ Menu-driven interface
✔ Runtime grammar input
✔ File-based input support
✔ Left Recursion elimination
✔ Left Factoring
✔ Validation (duplicate rules, invalid symbols)
✔ Dockerized execution (no local setup)
✔ Lightweight container

---

##  Limitations

* Supports only direct left recursion
* Basic left factoring (single prefix level)
* Limited grammar size (fixed arrays)

---

##  Concepts Used

* Context-Free Grammar (CFG)
* Compiler Design
* LL(1) Parsing Concepts
* Left Recursion Removal
* Left Factoring

---

##  Future Enhancements

* Indirect left recursion removal
* Multi-character symbol support
* GUI / Web interface
* Step-by-step transformation visualization

---


##  Author

* [Sai Teja](https://github.com/Saiteja-developer)
* [Aditya](https://github.com/Aditya0265)
* [Veeraj](https://github.com/vijay12968)
* [Rajshekar](https://github.com/Chinnajadi)

---

##  License

This project is for educational purposes.
