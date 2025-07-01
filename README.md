# LexMe

**LexMe** is a custom-built lexical analyzer (lexer/tokenizer) for C source code. It is designed as the first step in building a compiler or interpreter — transforming raw C code into a stream of meaningful tokens that can be further parsed into an Abstract Syntax Tree (AST).

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

### 📄 Usage

```powershell
LexMe <your_file.c>
```

Example:
```powershell
LexMe simple.c
```

Output:
```powershell
[
  {
    "type": "keyword",
    "value": "int",
    "start": 20,
    "length": 3,
    "line": 3
  },
  ...
]
```

### 📚 Output Token Format

Each token is represented as a JSON object:

{
  "type": "identifier",   // or keyword, string, number, etc.
  "value": "main",
  "start": 24,
  "length": 4,
  "line": 3
}

Supported Types
1.identifier

2.keyword

3.number

4.string

5.punctuation

6.operator

7.ellipsis (...)

8.unknown (for invalid/unsupported characters)

9.eof (end-of-file marker)

## 🧠 Future Work
Build a parser to construct an Abstract Syntax Tree (AST)

Add support for:
Preprocessor directives (#include, #define)

Multi-character operators (==, !=, >=, etc.)

Support for multi-file projects

Token error reporting (with line/column markers)

# ✨ Author

LexMe was created by Raul.
Happy development with compiler design! 🧠⚙️
