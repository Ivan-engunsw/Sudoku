#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <stack>
#include <cmath>
#include <stdio.h>
#include <time.h>

using namespace std;

// A class that stores the position in which the move has placed a number and the set of values remaining
class Move
{
public:
    int row;
    int column;
    set<char> allValues;

    Move(int rowParam, int columnParam, set<char> allValuesParam) {
        row = rowParam;
        column = columnParam;
        allValues = allValues;
    }
};

class Sudoku
{
public:
    size_t size;

    Sudoku(size_t size1) {
        size = size1;
    };

    void print(vector<vector<char>> grid) {
        for (size_t i = 0; i < size; ++i) {
            cout << grid[i][0];

            for (size_t j = 1; j < size; ++j) {
                cout  << " " << grid[i][j];
            }

            cout << endl;
        }
    };

    set<char> possibleValues(int row, int column, vector<vector<char>> grid) {
        set<char> all;

        // fills the set with all possible values
        for (size_t m = 1; m <= size; ++m) {
            if (m < 10) {
                all.insert(m + '0');
            } else {
                all.insert(m + 7 + '0');
            }
        }

        //removes values that are currently in row and column
        for (size_t i = 0; i < size; ++i) {
            all.erase(grid[i][column]);
            all.erase(grid[row][i]);
        }

        //removes values that are in the current block
        size_t blockSize = pow(size,0.5);
        size_t blockRowBegin = (row / blockSize) * blockSize;
        size_t blockColumnBegin = (column / blockSize) * blockSize;

        for (size_t k = 0; k < blockSize; ++k) {
            for (size_t l = 0; l < blockSize; ++l) {
                all.erase(grid[blockRowBegin + k][blockColumnBegin + l]);
            }
        }

        return all;
    };

    // looks for the next empty cell which has the least possible values to add a value to
    bool findMinEmptyCell(int* row, int* column, set<char>* allValues, vector<vector<char>> grid) {
        size_t minimum = size;

        for (size_t i = 0; i < size; ++i) {
            for (size_t j = 0; j < size; ++j) {
                if (grid[i][j] == '0') {
                    set<char> values = possibleValues(i,j,grid);
                    if (values.size() < minimum) {
                        minimum = values.size();
                        *allValues = values;
                        *row = i;
                        *column = j;

                        if (values.size() == 0) {
                            return true;
                        }
                    }
                }
            }
        }
        
        // if there is an empty cell
        if (minimum != size) {
            return true;
        } else {
            return false;
        }
    };

    char inspection(int* row, int* column, vector<vector<char>> grid) {
        size_t blockSize = pow(size,0.5);

        for (size_t i = 0; i < size; i = i + blockSize) {
            set<char> prev = {};
            set<char> curr;
            int rowPrev, columnPrev;

            for (size_t j = 0; j < blockSize; j++){
                for (size_t k = 0; k < blockSize; k++){
                    int row1 = i + j;
                    int column1 = i + k;
                    if (grid[row1][column1] == '0') {
                        curr = possibleValues(row1, column1, grid);
                        set<char>::iterator t;
                        set<char> temp = prev;
                        
                        // checking if the previous set of possible values have values that are not in this set
                        for (t = prev.begin(); t != prev.end(); ++t) {
                            if (curr.find(*t) != curr.end()) {
                                temp.erase(*t);
                            }
                        }

                        if (temp.size() == 0) {
                            prev = curr;
                            rowPrev = row1;
                            columnPrev = column1;
                        } else {
                            prev = temp;
                        }
                    }
                }
            }

            // there is only one option for this specific position
            if (prev.size() == 1) {
                *row = rowPrev;
                *column = columnPrev;
                return grid[rowPrev][columnPrev];
            }
        }

        return '0';
    }

    //using probability
    char mostProbableValue(set<char> allValues, vector<vector<char>> grid) {
        char value;
        set<char>::iterator t;
        int maximum = 0;

        for (t = allValues.begin();t != allValues.end();++t) {
            int count = 0;
            for (size_t i = 0; i < size; ++i) {
                for (size_t j = 0; j < size; ++j) {
                    if (grid[i][j] == *t) {
                        count++;
                    }
                }
            }

            if (count > maximum) {
                value = *t;
            }
        }

        return value;
    }

    vector<vector<char>> Solve(bool* solution, vector<vector<char>> grid) {
        int row = 0;
        int column = 0;
        stack<Move, vector<Move>> moves;
        set<char> allValues;

        while (findMinEmptyCell(&row, &column, &allValues, grid)) {
            int row1, column1;
            char inspectedValue = inspection(&row1, &column1, grid);

            if (inspectedValue != '0') {
                // we have worked out a value
                grid[row1][column1] = inspectedValue;
                allValues.clear();
                allValues.insert(inspectedValue);
                moves.push(Move(row1, column1, allValues));
            } else {
                if (allValues.size() == 1) {
                    grid[row][column] = *allValues.begin();
                    moves.push(Move(row, column, allValues));
                } else if (allValues.size() == 0){
                    //no possible value so we backtrack
                    row = moves.top().row;
                    column = moves.top().column;
                    moves.top().allValues.erase(grid[row][column]);

                    grid[row][column] = mostProbableValue(allValues, grid);

                    while (moves.top().allValues.empty()) {
                        row = moves.top().row;
                        column = moves.top().column;
                        grid[row][column] = '0';
                        moves.pop();

                        if (moves.empty()) {
                            *solution = false;
                            return grid;
                        } else {
                            row = moves.top().row;
                            column = moves.top().column;
                            moves.top().allValues.erase(grid[row][column]);
                            
                            if (moves.top().allValues.empty()) {
                                continue;
                            } else {
                                grid[row][column] = mostProbableValue(moves.top().allValues, grid);
                            }
                        }
                    }
                } else {
                    grid[row][column] = mostProbableValue(allValues, grid);
                    moves.push(Move(row, column, allValues));
                }
            }
        }
        return grid;
    };
};

int main() {

    string line;
    getline(cin, line);
    // removes the spaces and the nextline character
    line.erase(remove(line.begin(), line.end() ,' '), line.end());
    size_t size = line.length();
    Sudoku s = Sudoku(size);
    char value;

    vector<vector<char>> grid(size, vector<char>(size));

    for (size_t j = 0; j < size; j++) {
        grid[0][j] = line[j];
    }

    //setting up the grid
    for (size_t i = 1; i < size; ++i) {
        for (size_t j = 0; j < size; j++) {
            cin >> value;
            grid[i][j] = value;
        }
    }

    bool solutionExist = true;
    grid = s.Solve(&solutionExist, grid);

    if (solutionExist) {
        s.print(grid);
    } else {
        cout << "No Solution";
    }

}