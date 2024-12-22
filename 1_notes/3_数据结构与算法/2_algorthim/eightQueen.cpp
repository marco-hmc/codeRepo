#include <iostream>
#include <thread>
#include <vector>

const int N = 8;

std::vector<std::vector<int>> solutions;

bool isSafe(const std::vector<int> &board, int row, int col) {

  for (int i = 0; i < row; i++) {
    if (board[i] == col) {
      return false;
    }
  }

  for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
    if (board[i] == j) {
      return false;
    }
  }

  for (int i = row, j = col; i >= 0 && j < N; i--, j++) {
    if (board[i] == j) {
      return false;
    }
  }

  return true;
}

void solveNQueens(std::vector<int> &board, int row) {
  if (row == N) {
    solutions.push_back(board);
    return;
  }

  for (int col = 0; col < N; col++) {
    if (isSafe(board, row, col)) {
      board[row] = col;
      solveNQueens(board, row + 1);
    }
  }
}

int main() {
  std::vector<std::thread> threads;

  for (int i = 0; i < N; i++) {
    std::vector<int> board(N, -1);
    board[0] = i;
    threads.push_back(std::thread(solveNQueens, std::ref(board), 1));
  }

  for (auto &thread : threads) {
    thread.join();
  }

  for (const auto &solution : solutions) {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        if (solution[i] == j) {
          std::cout << "Q ";
        } else {
          std::cout << ". ";
        }
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }

  return 0;
}