# C++ Module 06 — C++ casts

Scalar type conversion, pointer serialization and runtime type identification with the four C++ casts (C++98).

*This project was created as part of the 42 curriculum by jpflegha.*

## Exercises

| Exercise | Program | What it does |
|:---|:---|:---|
| `ex00` | `convert` | `ScalarConverter::convert` detects whether the input is a char, int, float or double literal (including `nan`, `+inf`, `-inff`, …) and prints it as all four types, with `impossible` / `Non displayable` where needed. Uses `static_cast`. |
| `ex01` | `serializer` | `Serializer::serialize` turns a `Data*` into a `uintptr_t` and `deserialize` turns it back, using `reinterpret_cast`; the test checks that the pointer and the data are the same. The class can't be instantiated. |
| `ex02` | `identify` | `generate()` randomly creates an `A`, `B` or `C` behind a `Base*`. `identify(Base*)` finds the real type with `dynamic_cast` on pointers (NULL on failure), `identify(Base&)` with `dynamic_cast` on references (throws on failure). |

## Key concepts

- `static_cast`, `reinterpret_cast`, `dynamic_cast` (and when to use which)
- Parsing and validating numeric literals, limits and special float values
- Classes with only static members
- Runtime type identification with polymorphic base classes

## Build and run

```bash
git clone https://github.com/jpfleghaar/CPP06.git
cd CPP06/ex00 && make
./convert 42.0f
char: '*'
int: 42
float: 42.0f
double: 42.0
./convert nan
char: impossible
int: impossible
float: nanf
double: nan
./convert "'a'"
char: 'a'
int: 97
float: 97.0f
double: 97.0
```

Each exercise has its own Makefile (`c++ -Wall -Wextra -Werror -std=c++98`).

## Project structure

```
ex00/  ScalarConverter.{hpp,cpp}, main.cpp
ex01/  Serializer.{hpp,cpp}, Data.hpp, main.cpp
ex02/  Base.{hpp,cpp}, A.hpp, B.hpp, C.hpp, main.cpp
```

## What I learned

- Each C++ cast states the intent clearly, unlike a C-style cast that can do anything.
- `dynamic_cast` needs a polymorphic base class and reports failure differently for pointers and references.
- Detecting the type of a literal correctly is mostly about careful edge cases (overflow, `inf`, `nan`, precision).
