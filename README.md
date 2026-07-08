# InternGrow Intelligent Sudoku Solver & Generator

Sudoku Solver and Puzzle Generator built in C++ as part of the **InternGrow C++ Programming Track (Task 3)**.

## 📋 Overview
This console-based application represents a Sudoku grid as a 9x9 2D array and uses a **recursive backtracking algorithm** to solve puzzles with empty cells. It also includes an integrated **puzzle generator engine** that creates unique, unsolved Sudoku configurations based on selectable difficulty levels.

## ✨ Features
- **2D Grid Representation**: Sudoku board stored as a 9x9 array
- **Recursive Backtracking Solver**: Automatically fills empty cells by trying valid numbers and backtracking when a dead end is reached
- **Validation Logic**: Checks row, column, and 3x3 sub-box constraints before placing any number
- **Manual Puzzle Input**: Users can enter their own puzzle (using 0 for empty cells) and have it solved
- **Formatted Board Display**: Clean grid printout with sub-box separators

### 🚀 Upgrade Feature: Puzzle Generator Engine
Generates unique, unsolved Sudoku puzzles at three difficulty levels:
- **Easy** – 46 clues remaining (35 cells removed)
- **Medium** – 36 clues remaining (45 cells removed)
- **Hard** – 27 clues remaining (54 cells removed)

The generator works by:
1. Filling a complete, valid Sudoku solution using randomized backtracking
2. Removing cells one at a time based on the selected difficulty
3. Verifying after each removal that the puzzle still has a **unique solution** (using a solution-counting check), ensuring every generated puzzle is solvable in exactly one way

## 💻 How to Run

### Compile
```bash
g++ -std=c++17 InternGrow_SudokuSolver.cpp -o sudoku_solver
```

### Run
```bash
./sudoku_solver
```
(On Windows: `sudoku_solver.exe`)

## 📖 Usage
1. **Enter Your Own Puzzle & Solve** – Input a 9x9 grid (0 for blanks) and get the solved solution
2. **Generate a New Puzzle** – Choose Easy, Medium, or Hard difficulty to get a fresh unsolved puzzle
3. **Solve the Currently Generated Puzzle** – Solve the puzzle generated in option 2

## 🧩 Tech Stack
- **Language**: C++ (C++17)
- **Concepts Used**: 2D Arrays, Recursion, Backtracking Algorithms, STL (vector), `<random>` for shuffling, Object-Oriented Design

## 📌 Built For
**InternGrow C++ Programming Track** — Module 1, Task 3
Contact: interngrow.official@gmail.com

## 👤 Author
Samreen Javeed

## 📄 License
This project was built for educational purposes as part of the InternGrow internship program.
