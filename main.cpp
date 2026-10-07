#include <iostream>
#include <vector>
#include <string>

void printBoard(std::vector<std::vector<std::string>>& solutions, int n) {
    for (int j = 0; j < n; j++) {
        for (int k = 0; k < n; k++) {
            std::cout << solutions[solutions.size() - 1][j][k] << " ";
        }
        std::cout << std::endl;
    }
    
    for (int i = 0; i < n; i++) {
        std::cout << "--";
    }
    std::cout << std::endl;
}

std::vector<std::string> convert(std::vector<std::vector<int>>& queens) {
    int n = queens.size();
    std::vector<std::vector<std::string>> board(n, std::vector<std::string>(n, "."));
    std::vector<std::string> result;

    for (std::vector<int> position : queens)
        board[position[0]][position[1]] = "Q";
    
    for (int i = 0; i < n; i++) {
        std::string temp = "";
        for (int j = 0; j < n; j++) {
            temp += board[i][j];
        }
        
        result.push_back(temp);
    }

    return result;
}

    bool findSolutions(std::vector<std::vector<int>>& queens, int col,
                       std::vector<std::vector<std::string>>& result) {
        int n = queens.size();

        // If queens is full, we filled the board successfully
        // Thus, we add a solution
        if (col == n) {
            std::vector<std::string> solution = convert(queens);
            result.push_back(solution);
            printBoard(result, n);
            return true;
        }

        // Brute forces all posibilities
        for (int i = 0; i < n; i++) {
            bool isInCheck = false;
            for (std::vector<int> position : queens) {
                if (position[0] == -1 && position[1] == -1)
                    continue;
                
                if (i == position[0] || col == position[1] ||
                    abs(i - position[0]) == abs(col - position[1])) {
                    isInCheck = true;
                    break;
                }
            }

            if (isInCheck)
                continue;
            
            // Backtracking step
            queens[col][0] = i;
            queens[col][1] = col;
            findSolutions(queens, col + 1, result);
            queens[col][0] = -1;
            queens[col][1] = -1;
        }

        return false;
    }
    
std::vector<std::vector<std::string>> solveNQueens(int n) {
    if (n == 2 || n == 3)
        return {};

    std::vector<std::vector<int>> queens;
    for (int i = 0; i < n; i++)
        queens.push_back({-1, -1});
    
    std::vector<std::vector<std::string>> result;
    findSolutions(queens, 0, result);
    
    return result;
}

int main() {
    int n = 15;
    std::vector<std::vector<std::string>> solutions;
    solutions = solveNQueens(n);
    
    return 0;
}
