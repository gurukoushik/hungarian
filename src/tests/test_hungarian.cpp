#define BOOST_TEST_MODULE MyUnitTest

#include <boost/test/included/unit_test.hpp>

#include "hungarian.hpp"

BOOST_AUTO_TEST_CASE(test_3x3) {
  std::vector<std::vector<double>> cost_matrix = {
      {1, 2, 3}, {3, 1, 2}, {2, 3, 1}};

  taskassignment t1(cost_matrix, 3);
  std::vector<std::vector<int>> assignment = t1.hungarian();
  std::vector<std::vector<double>> expected_assignment = {
      {1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
  for (int i = 0; i < cost_matrix.size(); i++) {
    for (int j = 0; j < cost_matrix[0].size(); j++) {
      BOOST_REQUIRE_MESSAGE(assignment[i][j] == expected_assignment[i][j],
                            "Fail " << i << " " << j);
    }
  }
}