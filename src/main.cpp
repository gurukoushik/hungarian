#include <chrono>

#include "hungarian.hpp"

int main() {
  std::vector<std::vector<double>> cost_matrix = {{11, 7, 10, 17, 10},
                                                  {13, 21, 7, 11, 13},
                                                  {13, 13, 15, 13, 14},
                                                  {18, 10, 13, 16, 14},
                                                  {12, 8, 16, 19, 10}};

  auto timeStart = std::chrono::high_resolution_clock::now();

  TaskAssignment t1(cost_matrix);
  std::vector<std::vector<int>> assignment = t1.hungarian();

  auto timeEnd = std::chrono::high_resolution_clock::now();
  auto timeTaken = std::chrono::duration_cast<std::chrono::duration<double>>(
      timeEnd - timeStart);

  std::cout << "Cost matrix: \n\n";
  t1.print_matrix(cost_matrix);
  std::cout << std::endl;

  std::cout << "The optimal assignment is: \n\n";
  t1.print_matrix(assignment);
  std::cout << std::endl;

  std::cout << "Time taken to compute: " << timeTaken.count() << " s"
            << std::endl;

  return 0;
}
