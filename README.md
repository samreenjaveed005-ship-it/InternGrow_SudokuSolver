# InternGrow_SudokuSolverGenerator

## 📌 Project Title
Intelligent Sudoku Solver & Generator

## 📖 Description
A C++ console application that represents a Sudoku grid as a 2D array and
uses **recursive backtracking** to solve any valid 9x9 puzzle you provide.

### 🚀 Upgrade Feature — Puzzle Generator Engine
Generates brand-new, **unsolved Sudoku puzzles** with a **guaranteed unique
solution**, at three difficulty settings:
| Difficulty | Cells Removed | Approx. Clues Remaining |
|-----------|---------------|--------------------------|
| Easy      | 35            | ~46                      |
| Medium    | 45            | ~36                      |
| Hard      | 54            | ~27                      |

The generator builds a full valid solution first (via backtracking, seeded
by randomly filled diagonal boxes), then removes cells one at a time —
checking after each removal that the puzzle **still has exactly one
solution** — so every generated puzzle is solvable and unambiguous.

## 🛠️ Tech Stack
- Language: C++ (C++17)
- Core Algorithm: Recursive backtracking (constraint satisfaction)

## 📂 File Structure
```
InternGrow_SudokuSolverGenerator/
├── Task3_Sudoku_Solver_Generator.cpp
└── README.md
```

## ⚙️ How to Compile & Run
```bash
g++ -std=c++17 -o Sudoku Task3_Sudoku_Solver_Generator.cpp
./Sudoku
```
On Windows (MinGW):
```bash
g++ -std=c++17 -o Sudoku.exe Task3_Sudoku_Solver_Generator.cpp
Sudoku.exe
```

## ▶️ How to Use
On launch you'll see a menu:
```
1. Solve my own Sudoku puzzle
2. Generate a new puzzle (Easy/Medium/Hard)
3. Exit
```

**Option 1 — Solve**
- Enter your 9x9 grid row by row, space-separated, using `0` for empty
  cells.
- The program prints your input grid, then the fully solved grid (or a
  message if no solution exists).

**Option 2 — Generate**
- Choose a difficulty level (Easy / Medium / Hard).
- The program prints a new unsolved puzzle.
- Optionally view the full solution on demand.

## 📊 Sample Output
```
===== Intelligent Sudoku Solver & Generator =====
1. Solve my own Sudoku puzzle
2. Generate a new puzzle (Easy/Medium/Hard)
3. Exit
Choose an option: 2
Select difficulty:
1. Easy
2. Medium
3. Hard
Choice: 1

Generating a Easy puzzle...

Your new Easy Sudoku puzzle:
5 3 . | . 7 . | . . .
6 . . | 1 9 5 | . . .
. 9 8 | . . . | . 6 .
------+-------+------
8 . . | . 6 . | . . 3
4 . . | 8 . 3 | . . 1
7 . . | . 2 . | . . 6
------+-------+------
. 6 . | . . . | 2 8 .
. . . | 4 1 9 | . . 5
. . . | . 8 . | . 7 9
```

## 👤 Author
InternGrow C++ Programming Track — Module 1, Task 3

## 📄 License
This project was developed as part of the InternGrow internship program for
educational purposes.
