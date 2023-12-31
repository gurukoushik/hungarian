// Derived from the implementation in
// https://users.cs.duke.edu/~brd/Teaching/Bio/asmb/current/Handouts/munkres.html

#include <algorithm>
#include <iostream>
#include <limits>
#include <list>
#include <queue>
#include <set>
#include <unordered_map>
#include <unordered_set>

template <typename P>
class TaskAssignment {
 private:
  std::vector<std::vector<P>> cost_matrix;
  int n;

  std::vector<std::vector<int>> mask;
  std::vector<int> rowcover;
  std::vector<int> colcover;

  int saved_row;
  int saved_col;
  int path_count;

  std::vector<std::vector<int>> path;
  int step;

 public:
  TaskAssignment(std::vector<std::vector<P>> cost_matrix) {
    this->cost_matrix = cost_matrix;
    this->n = cost_matrix.size();

    std::vector<std::vector<int>> mask(n, std::vector<int>(n, 0));
    std::vector<int> rowcover(n, 0);
    std::vector<int> colcover(n, 0);

    this->mask = mask;
    this->rowcover = rowcover;
    this->colcover = colcover;
    saved_row = -1;
    saved_col = -1;
    path_count = 0;

    std::vector<std::vector<int>> path(2 * n + 1, std::vector<int>(2, 0));
    this->path = path;
    step = 0;
  }

  void rowminsubtract() {
    // Row minimum subtraction
    std::vector<P> rowmin(n, std::numeric_limits<P>::infinity());
    for (int i = 0; i < n; i++)
      rowmin[i] = *min_element(cost_matrix[i].begin(), cost_matrix[i].end());

    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        cost_matrix[i][j] = cost_matrix[i][j] - rowmin[i];

    step = 2;
  }

  int numofrowzeros(int row_index) {
    // Row zeros count
    int count = 0;

    for (int j = 0; j < n; j++)
      if (cost_matrix[row_index][j] == 0) count++;

    return count;
  }

  int numofcolzeros(int col_index) {
    // Row zeros count
    int count = 0;

    for (int i = 0; i < n; i++)
      if (cost_matrix[i][col_index] == 0) count++;

    return count;
  }

  void starzeros() {
    // Row-wise star zeros
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (cost_matrix[i][j] == 0 && rowcover[j] == 0 && colcover[i] == 0) {
          mask[i][j] = 1;
          rowcover[j] = 1;
          colcover[i] = 1;
        }
      }
    }

    for (int i = 0; i < n; i++) rowcover[i] = 0;
    for (int i = 0; i < n; i++) colcover[i] = 0;

    step = 3;
  }

  void coverstarcols() {
    bool done = false;
    // Row-wise star zeros
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        if (mask[i][j] == 1) colcover[j] = 1;

    int columncount = 0;
    for (int j = 0; j < n; j++)
      if (colcover[j] == 1) columncount++;
    if (columncount >= n)
      step = 7;
    else
      step = 4;
  }

  bool starinrow(int row) {
    bool found = false;
    for (int j = 0; j < n; j++)
      if (mask[row][j] == 1) found = true;
    return found;
  }

  void findstarinrow(int row, int &col) {
    col = -1;
    for (int j = 0; j < n; j++)
      if (mask[row][j] == 1) col = j;
  }

  void findzero(int &row, int &col) {
    int r = 0;
    int c;
    bool done = false;
    row = -1;
    col = -1;

    for (int i = 0; i < n; i++) {
      if (!done) {
        for (int j = 0; j < n; j++) {
          if (cost_matrix[i][j] == 0 && rowcover[i] == 0 && colcover[j] == 0) {
            row = i;
            col = j;
            done = true;
          }
        }
      }
    }
  }

  void primeuncoveredzeros() {
    int row = -1;
    int col = -1;
    bool done = false;

    while (!done) {
      findzero(row, col);
      if (row == -1) {
        done = true;
        step = 6;
      } else {
        mask[row][col] = 2;
        if (starinrow(row)) {
          findstarinrow(row, col);
          rowcover[row] = 1;
          colcover[col] = 0;
        } else {
          done = true;
          step = 5;
          saved_row = row;
          saved_col = col;
        }
      }
    }
  }

  void findstarincol(int &row, int col) {
    row = -1;
    for (int i = 0; i < n; i++)
      if (mask[i][col] == 1) row = i;
  }

  void findprimeinrow(int row, int &col) {
    for (int j = 0; j < n; j++)
      if (mask[row][j] == 2) col = j;
  }

  void clearcovers() {
    for (int j = 0; j < n; j++) rowcover[j] = 0;
    for (int j = 0; j < n; j++) colcover[j] = 0;
  }

  void clearprimes() {
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        if (mask[i][j] == 2) mask[i][j] = 0;
  }

  void augpath() {
    for (int p = 0; p < path_count; p++) {
      if (mask[path[p][0]][path[p][1]] == 1)
        mask[path[p][0]][path[p][1]] = 0;
      else
        mask[path[p][0]][path[p][1]] = 1;
    }
  }

  void alternateprimestar() {
    bool done = false;
    int r = -1;
    int c = -1;
    path_count = 1;
    path[path_count - 1][0] = saved_row;
    path[path_count - 1][1] = saved_col;
    while (!done) {
      findstarincol(r, path[path_count - 1][1]);
      if (r > -1) {
        path_count++;
        path[path_count - 1][0] = r;
        path[path_count - 1][1] = path[path_count - 2][1];
      } else
        done = true;

      if (!done) {
        findprimeinrow(path[path_count - 1][0], c);
        path_count++;
        path[path_count - 1][0] = path[path_count - 2][0];
        path[path_count - 1][1] = c;
      }
    }
    augpath();
    clearcovers();
    clearprimes();
    step = 3;
  }

  void findsmallest(P &minim) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (rowcover[i] == 0 && colcover[j] == 0) {
          if (minim > cost_matrix[i][j]) {
            minim = cost_matrix[i][j];
          }
        }
      }
    }
  }

  void altercoveredrow() {
    P minim = std::numeric_limits<P>::infinity();
    findsmallest(minim);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++) {
        if (rowcover[i] == 1) cost_matrix[i][j] += minim;
        if (colcover[j] == 0) cost_matrix[i][j] -= minim;
      }
    step = 4;
  }

  template <typename T>
  void print_matrix(std::vector<std::vector<T>> matrix) {
    // Print matrix
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        std::cout << matrix[i][j] << " ";
      }
      std::cout << std::endl;
    }
  }

  std::vector<std::vector<int>> run() {
    bool done = false;
    step = 1;

    while (!done) {
      switch (step) {
        case 1:
          rowminsubtract();
          break;
        case 2:
          starzeros();
          break;
        case 3:
          coverstarcols();
          break;
        case 4:
          primeuncoveredzeros();
          break;
        case 5:
          alternateprimestar();
          break;
        case 6:
          altercoveredrow();
          break;
        case 7:
          done = true;
          break;
      }
    }

    if (!done) {
      std::vector<std::vector<int>> nullassignment(n, std::vector<int>(n, -1));
      return nullassignment;
    }

    return mask;
  }
};