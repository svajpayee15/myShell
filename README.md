# 🐚 Simple C++ Shell — v1

A minimal Unix-like shell written in C++.

> **Version:** v1  
> This is the first version of the project and implements a basic REPL with a small set of built-in commands and external command execution via `PATH`.

---

## 📌 Overview

This project implements a simple **Read–Eval–Print Loop (REPL)** shell that:

- Displays a `$ ` prompt
- Accepts user input
- Supports basic built-in commands
- Searches for executables in the system `PATH`
- Executes external programs

It is designed for learning purposes and to demonstrate how shells resolve and execute commands.

---

## 🚀 Features (v1)

### ✅ Built-in Commands

#### `exit`
Exits the shell.

```bash
$ exit
```

---

#### `echo`
Prints text to standard output.

```bash
$ echo Hello World
Hello World
```

---

#### `type`
Identifies whether a command is:
- A shell builtin
- An executable in `PATH`
- Not found

```bash
$ type echo
echo is a shell builtin

$ type ls
ls is /bin/ls

$ type fakecmd
fakecmd: not found
```

---

### ✅ External Command Execution

If the command is not a builtin, the shell:

1. Extracts the program name
2. Searches each directory in `$PATH`
3. Checks if the file:
   - Exists
   - Has execute permission
4. Executes it using `system()`

Example:

```bash
$ ls
$ pwd
$ whoami
```

---

## 🛠 Requirements

- C++17 or newer (uses `std::filesystem`)
- Unix-like operating system (uses `unistd.h` and `access()`)

---

## 💻 Build & Run

### Compile

```bash
g++ -std=c++17 shell.cpp -o shell
```

### Run

```bash
./shell
```

---

## 🧱 Architecture

The program consists of:

- `main()`  
  Runs the infinite REPL loop.

- `repl()`  
  Handles input parsing and built-in command dispatch.

- `exe()`  
  Searches the `PATH` and executes external programs.

---

## ⚠️ Limitations (v1)

This version does **not** support:

- Pipes (`|`)
- Input/output redirection (`>`, `<`)
- Background processes (`&`)
- Quoted argument parsing
- Command history
- Signal handling
- Advanced parsing

Additional notes:

- Uses `system()` instead of `fork()`/`execvp()`
- Splits program name using simple space parsing
- Minimal error handling

---

## 📚 Example Session

```bash
$ echo Welcome to v1
Welcome to v1

$ type echo
echo is a shell builtin

$ type ls
ls is /bin/ls

$ ls
main.cpp  shell

$ exit
```

---

## 🎯 Purpose

This project is intended for:

- Learning how shells work
- Understanding `PATH` resolution
- Practicing C++17 features.
- Building a foundation for a more advanced shell

---

## 🔮 Future Improvements (v2+ Ideas)

- Replace `system()` with `fork()` + `execvp()`
- Add pipe support
- Implement redirection
- Add command history
- Improve argument parsing
- Add cross-platform support

---
