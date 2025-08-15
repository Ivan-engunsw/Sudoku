# 🔢 Sudoku Solver – C++ Implementation  

A command-line **Sudoku solver** that supports both **9×9** and **16×16** puzzles.  
The program takes an input grid, processes it, and outputs the completed solution.  

---

## 🛠 Features  
- Solves **standard 9×9 Sudokus**.  
- Solves **larger 16×16 Sudokus**.  
- Accepts `0` as the placeholder for empty cells.  
- Displays the solved grid neatly in the terminal.  

---

## 📥 Input Format  
- Enter the Sudoku grid row by row.  
- Separate each value with a **space**.  
- Use `0` for empty cells.  

Example for a **9×9 Sudoku**:  
5 3 0 0 7 0 0 0 0  
6 0 0 1 9 5 0 0 0  
0 9 8 0 0 0 0 6 0  
8 0 0 0 6 0 0 0 3  
4 0 0 8 0 3 0 0 1  
7 0 0 0 2 0 0 0 6  
0 6 0 0 0 0 2 8 0  
0 0 0 4 1 9 0 0 5  
0 0 0 0 8 0 0 7 9  


---

## 🚀 How to Run  
1. Compile the program:  
   ```
   g++ sudoku_solver.cpp -o sudoku_solver
   ```
2. Then run the program:
   ```
   ./sudoku_solver
   ```
