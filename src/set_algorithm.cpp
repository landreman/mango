#include<iostream>
#include<string>
#include<stdlib.h>
#include "mango.hpp"

void mango::problem::set_algorithm(algorithm_type algorithm_in) {
  if (algorithm_in < 0) {
    std::cout << "\nAlgorithm cannot be negative.\n";
    exit(1);
  }
  if (algorithm_in >= NUM_ALGORITHMS) {
    std::cout << "\nAlgorithm is too large.\n";
    exit(1);
  }

  algorithm = algorithm_in;
  load_algorithm_properties();

  std::cout << "Algorithm set (by integer) to " << algorithm << ", a.k.a. " << algorithm_name << "\n";
}

///////////////////////////////////////////////////////////////////////////

void mango::problem::set_algorithm(std::string str) {
  bool found_match = false;

  for (int j = 0; j < NUM_ALGORITHMS; j++) {
    algorithm = (algorithm_type) j;
    load_algorithm_properties();
    if (algorithm_name.compare(str) == 0) {
      found_match = true;
      break;
    }
  }

  if (!found_match) {
    std::cout << "\nError! No match found for algorithm string: " << str << "\n";
    exit(1);
  }

  std::cout << "Algorithm set (by string) to " << algorithm << ", a.k.a. " << algorithm_name << "\n";
}

///////////////////////////////////////////////////////////////////////////

bool mango::does_algorithm_exist(std::string str) {
  bool found_match = false;
  bool algorithm_uses_derivatives, least_squares_algorithm, algorithm_requires_bound_constraints;
  package_type package;
  std::string algorithm_name;
  algorithm_type algorithm;

  for (int j = 0; j < NUM_ALGORITHMS; j++) {
    algorithm = (algorithm_type) j;
    get_algorithm_properties(algorithm, &algorithm_uses_derivatives, &least_squares_algorithm, &package, &algorithm_name, &algorithm_requires_bound_constraints);
    if (algorithm_name.compare(str) == 0) {
      found_match = true;
      break;
    }
  }

  return(found_match);
}
