#include <iostream>
#include "mango.hpp"
#include "Problem_data.hpp"
#include "Package_nlopt.hpp"

#ifdef MANGO_NLOPT_AVAILABLE
#include "nlopt.hpp"
#endif

//double nlopt_objective_function(unsigned, const double*, double*, void*); 


void mango::Package_nlopt::optimize(Problem_data* problem_data) {
#ifdef MANGO_NLOPT_AVAILABLE

  /*  int* f_data = NULL;
      nlopt::opt opt_instance(nlopt::LN_NELDERMEAD, N_parameters); */

  /*  opt_instance.set_min_objective(&nlopt_objective_function, (void*)this);  */
  /*   opt_instance.set_min_objective(&nlopt_objective_function, NULL); */

  /* double f;
     std::vector<double> vectorized_state_vector = std::vector<double>(state_vector, &state_vector[N_parameters]); */
  /* std::cout << "Here comes vectorized_state_vector:" << vectorized_state_vector; */
  /*  nlopt::result nlopt_result = opt_instance.optimize(vectorized_state_vector, &f);  */
  /*  nlopt::result nlopt_result = opt_instance.optimize(state_vector, &f); */

  nlopt::algorithm mango_nlopt_algorithm;
  switch (problem_data->algorithm) {
    // <nlopt_algorithms>
    // This section was automatically generated by ./update_algorithms
  case mango::NLOPT_GN_DIRECT:
    mango_nlopt_algorithm = nlopt::GN_DIRECT;
    break;
  case mango::NLOPT_GN_DIRECT_L:
    mango_nlopt_algorithm = nlopt::GN_DIRECT_L;
    break;
  case mango::NLOPT_GN_DIRECT_L_RAND:
    mango_nlopt_algorithm = nlopt::GN_DIRECT_L_RAND;
    break;
  case mango::NLOPT_GN_DIRECT_NOSCAL:
    mango_nlopt_algorithm = nlopt::GN_DIRECT_NOSCAL;
    break;
  case mango::NLOPT_GN_DIRECT_L_NOSCAL:
    mango_nlopt_algorithm = nlopt::GN_DIRECT_L_NOSCAL;
    break;
  case mango::NLOPT_GN_DIRECT_L_RAND_NOSCAL:
    mango_nlopt_algorithm = nlopt::GN_DIRECT_L_RAND_NOSCAL;
    break;
  case mango::NLOPT_GN_ORIG_DIRECT:
    mango_nlopt_algorithm = nlopt::GN_ORIG_DIRECT;
    break;
  case mango::NLOPT_GN_ORIG_DIRECT_L:
    mango_nlopt_algorithm = nlopt::GN_ORIG_DIRECT_L;
    break;
  case mango::NLOPT_GN_CRS2_LM:
    mango_nlopt_algorithm = nlopt::GN_CRS2_LM;
    break;
  case mango::NLOPT_LN_COBYLA:
    mango_nlopt_algorithm = nlopt::LN_COBYLA;
    break;
  case mango::NLOPT_LN_BOBYQA:
    mango_nlopt_algorithm = nlopt::LN_BOBYQA;
    break;
  case mango::NLOPT_LN_PRAXIS:
    mango_nlopt_algorithm = nlopt::LN_PRAXIS;
    break;
  case mango::NLOPT_LN_NELDERMEAD:
    mango_nlopt_algorithm = nlopt::LN_NELDERMEAD;
    break;
  case mango::NLOPT_LN_SBPLX:
    mango_nlopt_algorithm = nlopt::LN_SBPLX;
    break;
  case mango::NLOPT_LD_MMA:
    mango_nlopt_algorithm = nlopt::LD_MMA;
    break;
  case mango::NLOPT_LD_CCSAQ:
    mango_nlopt_algorithm = nlopt::LD_CCSAQ;
    break;
  case mango::NLOPT_LD_SLSQP:
    mango_nlopt_algorithm = nlopt::LD_SLSQP;
    break;
  case mango::NLOPT_LD_LBFGS:
    mango_nlopt_algorithm = nlopt::LD_LBFGS;
    break;
  case mango::NLOPT_LD_TNEWTON_PRECOND_RESTART:
    mango_nlopt_algorithm = nlopt::LD_TNEWTON_PRECOND_RESTART;
    break;
  case mango::NLOPT_LD_TNEWTON_PRECOND:
    mango_nlopt_algorithm = nlopt::LD_TNEWTON_PRECOND;
    break;
  case mango::NLOPT_LD_TNEWTON_RESTART:
    mango_nlopt_algorithm = nlopt::LD_TNEWTON_RESTART;
    break;
  case mango::NLOPT_LD_TNEWTON:
    mango_nlopt_algorithm = nlopt::LD_TNEWTON;
    break;
  case mango::NLOPT_LD_VAR1:
    mango_nlopt_algorithm = nlopt::LD_VAR1;
    break;
  case mango::NLOPT_LD_VAR2:
    mango_nlopt_algorithm = nlopt::LD_VAR2;
    break;
    // </nlopt_algorithms>

  default:
    throw std::runtime_error("Error in optimize_nlopt. Unexpected algorithm!");
  }

  // I'll use the C interface of nlopt rather than the C++ interface, because the C++ interface requires 
  // converting things back and forth between double[] and std::vector<double>.
  // However, some nlopt constants like NLOPT_LN_NELDERMEAD conflict with mango's constants. 
  // We can get around the latter issue by using the C++ nlopt:: constants and casting them
  // from nlopt::algorithm to nlopt_algorithm. 
  nlopt_opt opt = nlopt_create((nlopt_algorithm)mango_nlopt_algorithm, problem_data->N_parameters);
  //  nlopt_set_min_objective(opt, (nlopt_func) &mango::problem::nlopt_objective_function, (void*)this);
  nlopt_set_min_objective(opt, (nlopt_func) &mango::Package_nlopt::nlopt_objective_function, (void*)problem_data);

  nlopt_set_maxeval(opt, problem_data->max_function_and_gradient_evaluations);

  if (problem_data->bound_constraints_set) {
    nlopt_set_lower_bounds(opt, problem_data->lower_bounds);
    nlopt_set_upper_bounds(opt, problem_data->upper_bounds);
  }

  double final_objective_function;
  nlopt_result result = nlopt_optimize(opt, problem_data->state_vector, &final_objective_function);

  switch (result) {
  case nlopt::SUCCESS:
    if (problem_data->verbose > 0) std::cout << "nlopt generic success" << std::endl;
    break;
  case nlopt::STOPVAL_REACHED:
    if (problem_data->verbose > 0) std::cout << "nlopt success: stopval reached." << std::endl;
    break;
  case nlopt::FTOL_REACHED:
    if (problem_data->verbose > 0) std::cout << "nlopt success: ftol reached." << std::endl;
    break;
  case nlopt::XTOL_REACHED:
    if (problem_data->verbose > 0) std::cout << "nlopt success: xtol reached." << std::endl;
    break;
  case nlopt::MAXEVAL_REACHED:
    if (problem_data->verbose > 0) std::cout << "nlopt: maxeval reached" << std::endl;
    break;
  case nlopt::MAXTIME_REACHED:
    if (problem_data->verbose > 0) std::cout << "nlopt: maxtime reached." << std::endl;
    break;
  case nlopt::FAILURE:
    if (problem_data->verbose > 0) std::cerr << "WARNING!!! NLOPT reported a generic failure. Results may or may not make sense." << std::endl;
    break;
  case nlopt::INVALID_ARGS:
    throw std::runtime_error("nlopt failure: invalid arguments!");
    break;
  case nlopt::OUT_OF_MEMORY:
    throw std::runtime_error("nlopt out of memory!");
    break;
  case nlopt::ROUNDOFF_LIMITED:
    if (problem_data->verbose > 0) std::cerr << "nlopt: WARNING! Limited by roundoff. Results may or may not make sense." << std::endl;
    break;
  case nlopt::FORCED_STOP:
    throw std::runtime_error("nlopt forced stop!");
    break;
  default:
    throw std::runtime_error("nlopt unexpected return value!");
  }

  nlopt_destroy(opt);

#else
  throw std::runtime_error("Error! A NLOPT algorithm was requested, but Mango was compiled without NLOPT support.");
#endif
}


double mango::Package_nlopt::nlopt_objective_function(unsigned n, const double* x, double* grad, void* f_data) { 
  mango::Problem_data* problem_data = (mango::Problem_data*) f_data; 
  bool failed;
  double f;

  if (problem_data->verbose > 0) std::cout << "Hello from nlopt_objective_function" << std::endl << std::flush;

  if (grad == NULL) {
    // Gradient is not required.
    problem_data->objective_function_wrapper(x, &f, &failed);
  } else {
    // Gradient is required.
    problem_data->finite_difference_gradient(x, &f, grad);
  }

  if (failed) f = mango::NUMBER_FOR_FAILED;

  if (problem_data->verbose > 0) std::cout << "Good-bye from nlopt_objective_function" << std::endl << std::flush;

  return f;
}

