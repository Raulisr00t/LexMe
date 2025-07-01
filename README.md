# LexMe

**LexMe** is a lightweight, custom-built lexical analyzer (lexer/tokenizer) for C source code. It is designed as the first step in building a compiler or interpreter — transforming raw C code into a stream of meaningful tokens that can be further parsed into an Abstract Syntax Tree (AST).

---

## 🔍 Features

- Tokenizes C source code into:
  - Keywords (e.g. `int`, `return`, `while`, etc.)
  - Identifiers (e.g. variable and function names)
  - Numbers (integers and floats)
  - Strings (e.g. `"Hello\n"`)
  - Operators and Punctuation (e.g. `+`, `=`, `{`, `;`, etc.)
  - Comments (`// line comments` and `/* block comments */`)
  - Unknown symbols (for error reporting)
- Outputs token stream as a **JSON array**, including:
  - `type`
  - `value`
  - `start` (character offset)
  - `length` (in characters)
  - `line` (line number)
- Handles both single-line and multi-line C files

---

## 🚀 Getting Started

### 📦 Requirements

- A C compiler (e.g. `gcc`, `clang`)
- POSIX-like or Windows environment

### 🔧 Compilation

```powershell
gcc -o LexMe LexMe.c
```
