#define BOOST_TEST_MODULE MyUnitTest

#include <boost/test/included/unit_test.hpp>

#include "hungarian.hpp"

BOOST_AUTO_TEST_CASE(test_3x3) {
  std::vector<std::vector<double>> cost_matrix = {
      {1, 2, 3}, {3, 1, 2}, {2, 3, 1}};

  TaskAssignment<double> t1(cost_matrix);
  std::vector<std::vector<int>> assignment = t1.hungarian();
  std::vector<std::vector<int>> expected_assignment = {
      {1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
  for (int i = 0; i < cost_matrix.size(); i++) {
    for (int j = 0; j < cost_matrix[0].size(); j++) {
      BOOST_REQUIRE_MESSAGE(assignment[i][j] == expected_assignment[i][j],
                            "Fail " << i << " " << j);
    }
  }
}

BOOST_AUTO_TEST_CASE(test_templating) {
  // double
  {
    std::vector<std::vector<double>> cost_matrix = {
        {1.0, 2.0, 3.0}, {3.0, 1.0, 2.0}, {2.0, 3.0, 1.0}};

    TaskAssignment<double> t1(cost_matrix);
    std::vector<std::vector<int>> assignment = t1.hungarian();
    std::vector<std::vector<int>> expected_assignment = {
        {1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    for (int i = 0; i < cost_matrix.size(); i++) {
      for (int j = 0; j < cost_matrix[0].size(); j++) {
        BOOST_REQUIRE_MESSAGE(assignment[i][j] == expected_assignment[i][j],
                              "Fail " << i << " " << j);
      }
    }
  }

  // float
  {
    std::vector<std::vector<float>> cost_matrix = {
        {1.0, 2.0, 3.0}, {3.0, 1.0, 2.0}, {2.0, 3.0, 1.0}};

    TaskAssignment<float> t1(cost_matrix);
    std::vector<std::vector<int>> assignment = t1.hungarian();
    std::vector<std::vector<int>> expected_assignment = {
        {1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    for (int i = 0; i < cost_matrix.size(); i++) {
      for (int j = 0; j < cost_matrix[0].size(); j++) {
        BOOST_REQUIRE_MESSAGE(assignment[i][j] == expected_assignment[i][j],
                              "Fail " << i << " " << j);
      }
    }
  }

  // int
  {
    std::vector<std::vector<int>> cost_matrix = {
        {1, 2, 3}, {3, 1, 2}, {2, 3, 1}};

    TaskAssignment<int> t1(cost_matrix);
    std::vector<std::vector<int>> assignment = t1.hungarian();
    std::vector<std::vector<int>> expected_assignment = {
        {1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    for (int i = 0; i < cost_matrix.size(); i++) {
      for (int j = 0; j < cost_matrix[0].size(); j++) {
        BOOST_REQUIRE_MESSAGE(assignment[i][j] == expected_assignment[i][j],
                              "Fail " << i << " " << j);
      }
    }
  }
}