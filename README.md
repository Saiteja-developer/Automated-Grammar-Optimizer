# Automated Grammar Optimizer (C + Docker)

##  Project Overview

The **Automated Grammar Optimizer** is a command-line tool written in **C** that transforms a Context-Free Grammar (CFG) into a form suitable for **top-down parsers** such as LL(1) and recursive-descent parsers.

It automatically:

* Eliminates **Direct Left Recursion**
* Applies **Left Factoring**
* Converts grammar into a **parser-friendly format**

---

##  Objectives

* Avoid infinite recursion in parsers
* Reduce ambiguity in grammar
* Provide a clean and optimized CFG

---

##  Technologies Used

* **C Programming Language**
* **Docker** (for containerized execution)
* **GCC Compiler (inside container)**

---

##  Project Structure

```
grammar-optimizer/
│
├── main.c              # Core implementation
├── Dockerfile          # Container setup
├── docker-compose.yml  # Optional container orchestration
└── README.md           # Project documentation
```

---

##  How to Run (Using Docker)

### 1. Build the Docker Image

```
docker build -t grammar .
```

### 2. Run the Program (Interactive Mode)

```
docker run -it grammar
```

---

##  Sample Input

```
Enter number of rules:
1

Enter Non-Terminal (e.g., E):
E

Enter number of productions:
2

Production 1:
E+T

Production 2:
T
```

---

##  Sample Output

```
--- Original Grammar ---
E -> E+T | T

--- Optimized Grammar ---
E -> TF
F -> +TF | e
```

---

##  Features (Current Version)

* Accepts grammar input at runtime
* Eliminates **Direct Left Recursion**
* Performs **Basic Left Factoring**
* Runs inside Docker (no local setup required)
* Lightweight container using Alpine Linux

---

##  Limitations

* Supports only **single-character non-terminals**
* Handles only **direct left recursion**
* Left factoring is basic (common prefix detection)
* Naming of new variables is simplified (not using primes like E')

---

##  Concepts Used

* Context-Free Grammar (CFG)
* Left Recursion Removal Algorithm
* Left Factoring Technique
* Compiler Design (Top-down parsing)

---

##  Future Enhancements

* Menu-driven interface
* File input support
* Better naming conventions (E → E')
* Indirect left recursion removal
* Grammar validation

---

##  Author

* [Sai Teja](https://github.com/Saiteja-developer)
* [Aditya](https://github.com/Aditya0265)
* [Veeraj](https://github.com/vijay12968)
* [Rajshekar](https://github.com/Chinnajadi)

---

##  License

This project is for educational purposes.
