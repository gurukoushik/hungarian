#include "hungarian.hpp"

int main() {
  std::cout << "\nHungarian Method for nxn optimal assignment\n\n";

  std::vector<std::vector<double>> cost_matrix = {{11, 7, 10, 17, 10},
                                                  {13, 21, 7, 11, 13},
                                                  {13, 13, 15, 13, 14},
                                                  {18, 10, 13, 16, 14},
                                                  {12, 8, 16, 19, 10}};
  taskassignment t1(cost_matrix, 5);
  std::vector<std::vector<int>> assignment = t1.hungarian();

  std::cout << "The optimal assignment is: \n\n";
  t1.print_matrix(assignment);
  std::cout << std::endl;

  return 0;
}
