// Copyright 2019, University of Maryland and the MANGO development team.
//
// This file is part of MANGO.
//
// MANGO is free software: you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// MANGO is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with MANGO.  If not, see
// <https://www.gnu.org/licenses/>.


#ifndef MANGO_H
#define MANGO_H

#include <mpi.h>
#include <string>

//! This C++ namespace contains everything related to MANGO.
namespace mango {

  //! The list of packages, i.e. libraries that MANGO can call to perform optimization.
  /**
   * Note that all packages are enumerated here even if MANGO is built
   * without support for all of them. This list of packages is
   * generated by the update_algorithms script from the master table
   * of algorithms in algorithms.dat.
   */
  typedef enum {
    // <packages>
    // This section was automatically generated by ./update_algorithms
    PACKAGE_PETSC,
    PACKAGE_MANGO,
    PACKAGE_HOPSPACK,
    PACKAGE_NLOPT,
    PACKAGE_GSL,
    // </packages>
    NUM_PACKAGES //!< Not an actual package, just counting.
  } package_type;

  //! A large finite number
  /** 
   * This number is not yet used in the code.
   */
  const double NUMBER_FOR_FAILED = 1.0e+12;

  //////////////////////////////////////////////////////////////////////////////////////
  // Items related to algorithms:

  //! Some properties of each algorithm that MANGO is aware of.
  typedef struct {
    std::string name; //!< A short string with the algorithm's name, e.g. 'petsc_pounders' or 'hopspack'.
    package_type package; //!< The optimization library that the algorithm belongs to.
    bool least_squares; //!< Whether or not the algorithm assumes the objective function has least-squares form.
    bool uses_derivatives; //!< Whether the algorithm requires derivatives of the objective function or residuals to be supplied.
    bool parallel; //!< Whether the algorithm can support concurrent evaluations of the objective function. Any algorithm that uses derivatives is parallel in this sense, because finite difference derivatives can be computed using concurrent function evaluations.
    bool allows_bound_constraints; //!< Whether the algorithm allows maximum and minimum values (a.k.a. box constraints) to be imposed on the independent variables.
    bool requires_bound_constraints; //!< Whether the algorithm requires maximum and minimum values (a.k.a. box constraints) to be imposed on the independent variables.
  } algorithm_properties;

  //! A list of the algorithms that MANGO can potentially use.
  /** 
   * Each algorithm in this list is only actually available if MANGO is built
   * with the corresponding package.  This list of packages is
   * generated by the update_algorithms script from the master table
   * of algorithms in algorithms.dat.
   */
  typedef enum {
    // <enum>
    // This section was automatically generated by ./update_algorithms
    MANGO_LEVENBERG_MARQUARDT,
    MANGO_IMFIL,
    PETSC_NM,
    PETSC_POUNDERS,
    PETSC_BRGN,
    NLOPT_GN_DIRECT,
    NLOPT_GN_DIRECT_L,
    NLOPT_GN_DIRECT_L_RAND,
    NLOPT_GN_DIRECT_NOSCAL,
    NLOPT_GN_DIRECT_L_NOSCAL,
    NLOPT_GN_DIRECT_L_RAND_NOSCAL,
    NLOPT_GN_ORIG_DIRECT,
    NLOPT_GN_ORIG_DIRECT_L,
    NLOPT_GN_CRS2_LM,
    NLOPT_LN_COBYLA,
    NLOPT_LN_BOBYQA,
    NLOPT_LN_PRAXIS,
    NLOPT_LN_NELDERMEAD,
    NLOPT_LN_SBPLX,
    NLOPT_LD_MMA,
    NLOPT_LD_CCSAQ,
    NLOPT_LD_SLSQP,
    NLOPT_LD_LBFGS,
    NLOPT_LD_TNEWTON_PRECOND_RESTART,
    NLOPT_LD_TNEWTON_PRECOND,
    NLOPT_LD_TNEWTON_RESTART,
    NLOPT_LD_TNEWTON,
    NLOPT_LD_VAR1,
    NLOPT_LD_VAR2,
    HOPSPACK,
    GSL_LM,
    GSL_DOGLEG,
    GSL_DDOGLEG,
    GSL_SUBSPACE2D,
    GSL_CONJUGATE_FR,
    GSL_CONJUGATE_PR,
    GSL_BFGS,
    GSL_NM,
    // </enum>
    NUM_ALGORITHMS  //!< Not an actual algorithm, just counting.
  } algorithm_type;
  
  //! A database of the algorithms that MANGO is aware of, including various properties of each algorithm.
  /**
   * This databse is automatically generated from the master database algorithms.dat by the update_algorithms script.
   */
  const algorithm_properties algorithms[NUM_ALGORITHMS] = {
    // <database>
    // This section was automatically generated by ./update_algorithms
    // name,                            package,         least_squares, uses_derivatives, parallel, allows_bound_constraints, requires_bound_constraints
    {"mango_levenberg_marquardt",       PACKAGE_MANGO,   true,          true,             true,     false,                    false},
    {"mango_imfil",                     PACKAGE_MANGO,   false,         false,            true,     true,                     true },
    {"petsc_nm",                        PACKAGE_PETSC,   false,         false,            false,    false,                    false},
    {"petsc_pounders",                  PACKAGE_PETSC,   true,          false,            false,    true,                     false},
    {"petsc_brgn",                      PACKAGE_PETSC,   true,          true,             true,     true,                     false},
    {"nlopt_gn_direct",                 PACKAGE_NLOPT,   false,         false,            false,    true,                     true },
    {"nlopt_gn_direct_l",               PACKAGE_NLOPT,   false,         false,            false,    true,                     true },
    {"nlopt_gn_direct_l_rand",          PACKAGE_NLOPT,   false,         false,            false,    true,                     true },
    {"nlopt_gn_direct_noscal",          PACKAGE_NLOPT,   false,         false,            false,    true,                     true },
    {"nlopt_gn_direct_l_noscal",        PACKAGE_NLOPT,   false,         false,            false,    true,                     true },
    {"nlopt_gn_direct_l_rand_noscal",   PACKAGE_NLOPT,   false,         false,            false,    true,                     true },
    {"nlopt_gn_orig_direct",            PACKAGE_NLOPT,   false,         false,            false,    true,                     true },
    {"nlopt_gn_orig_direct_l",          PACKAGE_NLOPT,   false,         false,            false,    true,                     true },
    {"nlopt_gn_crs2_lm",                PACKAGE_NLOPT,   false,         false,            false,    true,                     true },
    {"nlopt_ln_cobyla",                 PACKAGE_NLOPT,   false,         false,            false,    true,                     false},
    {"nlopt_ln_bobyqa",                 PACKAGE_NLOPT,   false,         false,            false,    true,                     false},
    {"nlopt_ln_praxis",                 PACKAGE_NLOPT,   false,         false,            false,    true,                     false},
    {"nlopt_ln_neldermead",             PACKAGE_NLOPT,   false,         false,            false,    true,                     false},
    {"nlopt_ln_sbplx",                  PACKAGE_NLOPT,   false,         false,            false,    true,                     false},
    {"nlopt_ld_mma",                    PACKAGE_NLOPT,   false,         true,             true,     true,                     false},
    {"nlopt_ld_ccsaq",                  PACKAGE_NLOPT,   false,         true,             true,     true,                     false},
    {"nlopt_ld_slsqp",                  PACKAGE_NLOPT,   false,         true,             true,     true,                     false},
    {"nlopt_ld_lbfgs",                  PACKAGE_NLOPT,   false,         true,             true,     true,                     false},
    {"nlopt_ld_tnewton_precond_restart",PACKAGE_NLOPT,   false,         true,             true,     true,                     false},
    {"nlopt_ld_tnewton_precond",        PACKAGE_NLOPT,   false,         true,             true,     true,                     false},
    {"nlopt_ld_tnewton_restart",        PACKAGE_NLOPT,   false,         true,             true,     true,                     false},
    {"nlopt_ld_tnewton",                PACKAGE_NLOPT,   false,         true,             true,     true,                     false},
    {"nlopt_ld_var1",                   PACKAGE_NLOPT,   false,         true,             true,     true,                     false},
    {"nlopt_ld_var2",                   PACKAGE_NLOPT,   false,         true,             true,     true,                     false},
    {"hopspack",                        PACKAGE_HOPSPACK,false,         false,            true,     true,                     false},
    {"gsl_lm",                          PACKAGE_GSL,     true,          true,             true,     false,                    false},
    {"gsl_dogleg",                      PACKAGE_GSL,     true,          true,             true,     false,                    false},
    {"gsl_ddogleg",                     PACKAGE_GSL,     true,          true,             true,     false,                    false},
    {"gsl_subspace2d",                  PACKAGE_GSL,     true,          true,             true,     false,                    false},
    {"gsl_conjugate_fr",                PACKAGE_GSL,     false,         true,             true,     false,                    false},
    {"gsl_conjugate_pr",                PACKAGE_GSL,     false,         true,             true,     false,                    false},
    {"gsl_bfgs",                        PACKAGE_GSL,     false,         true,             true,     false,                    false},
    {"gsl_nm",                          PACKAGE_GSL,     false,         false,            false,    false,                    false}
    // </database>
  };

  //! Checks whether or not a string corresponds to the name of one of the optimization algorithms known by MANGO.
  /**
   * @param[in] algorithm_name A candidate name for an optimization algorithm. These names correspond to the 
   *     <span class="paramname">name</span> field of the \ref algorithm_properties type.
   * @return true if an algorithm exists in MANGO's database with the corresponding name, false otherwise.
  */
  bool does_algorithm_exist(std::string algorithm_name);

  //! Returns the integer (enum) for an optimization algorithm associated with its string name.
  /**
   * @param[in] name A name of an optimization algorithm, e.g. "petsc_pounders" or "nlopt_ln_neldermead"
   * @param[out] algorithm_int The integer code for the algorithm with name specified by <span class="paramname">name</span>.
   *   If no matching algorithm is found, the value pointed to by <span class="paramname">algorithm_int</span> will not be changed from its input value.
   * @return true if an algorithm exists with a name equal to the specified <span class="paramname">name</span>, false otherwise.
   */
  bool get_algorithm(std::string name, algorithm_type* algorithm_int);

  //////////////////////////////////////////////////////////////////////////////////////
  // Items related to partitioning the processors into worker groups:

  /** \brief A class for dividing the set of MPI processes into worker groups.
   *
   * Each group works together on evaluations of the objective function.
   * For more information, see @ref concepts.
   */

  class MPI_Partition {
  private:
    MPI_Comm comm_world;
    MPI_Comm comm_worker_groups;
    MPI_Comm comm_group_leaders;
    int N_procs_world;
    int rank_world;
    int N_procs_worker_groups;
    int rank_worker_groups;
    int N_procs_group_leaders;
    int rank_group_leaders;
    int worker_group;
    bool proc0_world;
    bool proc0_worker_groups;
    int N_worker_groups;
    bool initialized;

    void verify_initialized();
    void print();
    void write_line(std::ofstream&, int, std::string[], int[]);

  public:

    //! If true, information is printed to stdout that may be useful for debugging.
    int verbose;

    //! Constructor
    MPI_Partition();

    //! Destructor
    ~MPI_Partition();

    //! Divide up a given "world" communicator into worker groups.
    /**
     * Normally this function is not called directly. Instead it is preferable to call
     * mango::Problem::mpi_init(), since it sets the number of worker groups to 1 for optimization algorithms that
     * do not support multiple worker groups.
     *
     * This subroutine creates the "worker groups" and "group leaders" communicators.
     * @param[in] comm_world An MPI communicator consisting of all the processors that will be divided up into worker groups.
     */
    void init(MPI_Comm comm_world);

    //! Use a user-supplied partitioning of the MPI processes into worker groups.
    /**
     * Use either this subroutine or mango::MPI_Partition::init(), not both.
     * @param[in] comm_world  An MPI communicator consisting of all the processors that will be divided up into worker groups.
     * @param[in] comm_group_leaders  An MPI communicator consisting only of the group leaders.
     * @param[in] comm_worker_groups  An MPI communicator containing all the processors of comm_world, 
     *   but with a separate "color" for each worker group. The processes with rank 0 in this communicator 
     *   must be the same as the processes in <span class="paramname">comm_group_leaders</span>.
     */
    void set_custom(MPI_Comm comm_world, MPI_Comm comm_group_leaders, MPI_Comm comm_worker_groups);

    //! Get the MPI communicator for MANGO's world communicator.
    /**
     * For more information about MPI communicators, see @ref concepts.
     * This function can only be called after calling mango::Problem::mpi_init(), mango::MPI_Partition::init(), or
     * mango::MPI_Partition::set_custom(). Otherwise a C++ exception will be thrown.
     * @return The MPI communicator for MANGO's world communicator.
     */
    MPI_Comm get_comm_world();

    //! Get the MPI communicator for MANGO's "worker groups" communicator.
    /**
     * For more information about MPI communicators, see @ref concepts.
     * This function can only be called after calling mango::Problem::mpi_init(), mango::MPI_Partition::init(), or
     * mango::MPI_Partition::set_custom(). Otherwise a C++ exception will be thrown.
     * @return The MPI communicator for MANGO's "worker groups" communicator.
     */
    MPI_Comm get_comm_worker_groups();

    //! Get the MPI communicator for MANGO's "group leaders" communicator.
    /**
     * For more information about MPI communicators, see @ref concepts.
     * This function can only be called after calling mango::Problem::mpi_init(), mango::MPI_Partition::init(), or
     * mango::MPI_Partition::set_custom(). Otherwise a C++ exception will be thrown.
     * @return The MPI communicator for MANGO's "group leaders" communicator.
     */
    MPI_Comm get_comm_group_leaders();

    //! Determine whether this MPI processor has rank 0 in MANGO's world communicator.
    /**
     * This function can only be called after calling mango::Problem::mpi_init(), mango::MPI_Partition::init(), or
     * mango::MPI_Partition::set_custom(). Otherwise a C++ exception will be thrown.
     * @return True if this MPI processor has rank 0 in MANGO's world communicator, false otherwise.
     */
    bool get_proc0_world();

    //! Determine whether this MPI processor has rank 0 in MANGO's "worker groups" communicator.
    /**
     * Equivalently, this function determines whether this MPI processor is a group leader.
     *
     * This function can only be called after calling mango::Problem::mpi_init(), mango::MPI_Partition::init(), or
     * mango::MPI_Partition::set_custom(). Otherwise a C++ exception will be thrown.
     * @return True if this MPI processor has rank 0 in MANGO's "worker groups" communicator, false otherwise.
     */
    bool get_proc0_worker_groups();

    //! Get the MPI rank of this processor in MANGO's world communicator.
    /**
     * For more information about MPI communicators, see @ref concepts.
     * This function can only be called after calling mango::Problem::mpi_init(), mango::MPI_Partition::init(), or
     * mango::MPI_Partition::set_custom(). Otherwise a C++ exception will be thrown.
     * @return The MPI rank of this processor in MANGO's world communicator.
     */
    int get_rank_world();

    //! Get the MPI rank of this processor in MANGO's "worker groups" communicator.
    /**
     * For more information about MPI communicators, see @ref concepts.
     * This function can only be called after calling mango::Problem::mpi_init(), mango::MPI_Partition::init(), or
     * mango::MPI_Partition::set_custom(). Otherwise a C++ exception will be thrown.
     * @return The MPI rank of this processor in MANGO's "worker groups" communicator.
     */
    int get_rank_worker_groups();

    //! Get the MPI rank of this processor in MANGO's "group leaders" communicator.
    /**
     * For more information about MPI communicators, see @ref concepts.
     * This function can only be called after calling mango::Problem::mpi_init(), mango::MPI_Partition::init(), or
     * mango::MPI_Partition::set_custom(). Otherwise a C++ exception will be thrown.
     * @return The MPI rank of this processor in MANGO's "group leaders" communicator.
     */
    int get_rank_group_leaders();

    //! Get the number of processors in MANGO's world communicator.
    /**
     * For more information about MPI communicators, see @ref concepts.
     * This function can only be called after calling mango::Problem::mpi_init(), mango::MPI_Partition::init(), or
     * mango::MPI_Partition::set_custom(). Otherwise a C++ exception will be thrown.
     * @return The number of processors in MANGO's world communicator.
     */
    int get_N_procs_world();

    //! Get the number of processors in MANGO's "worker groups" communicator.
    /**
     * For more information about MPI communicators, see @ref concepts.
     * This function can only be called after calling mango::Problem::mpi_init(), mango::MPI_Partition::init(), or
     * mango::MPI_Partition::set_custom(). Otherwise a C++ exception will be thrown.
     * @return The number of processors in MANGO's "worker groups" communicator.
     */
    int get_N_procs_worker_groups();

    //! Get the number of processors in MANGO's "group leaders" communicator.
    /**
     * For more information about MPI communicators, see @ref concepts.
     * This function can only be called after calling mango::Problem::mpi_init(), mango::MPI_Partition::init(), or
     * mango::MPI_Partition::set_custom(). Otherwise a C++ exception will be thrown.
     * @return The number of processors in MANGO's "group leaders" communicator.
     *    This number is the same as the number of worker groups.
     */
    int get_N_procs_group_leaders();

    //! Returns an integer indicating the worker group to which this MPI process belongs.
    /**
     * This function can only be called after calling mango::Problem::mpi_init(), mango::MPI_Partition::init(), or
     * mango::MPI_Partition::set_custom(). Otherwise a C++ exception will be thrown.
     * @return An integer indicating the worker group to which this MPI process belongs.
     */
    int get_worker_group();

    //! Returns the number of worker groups.
    /**
     * @return The number of worker groups.
     */
    int get_N_worker_groups();
    
    //! Set the number of worker groups to the given integer. 
    /**
     * Except when using a custom partition, this method must be
     * called before any of the 'get' methods or before using the
     * MPI_Partition for an optimization. This method does not need to
     * be called when using a custom partition.
     * @param[in] N_worker_groups The desired number of worker groups
     */
    void set_N_worker_groups(int N_worker_groups);

    //! Write a file with the given filename, showing the worker group assignments and rank of each process in each communicator.
    /**
     * @param[in] filename The name of the file in which to write the MPI data. If the file already exists, it will be over-written.
     */
    void write(std::string filename);

    //! Tell the worker MPI processes (i.e. those that are not group leaders) that the optimization problem is complete.
    /**
     * This subroutine should only be called by group leaders.
     * This subroutine is typically called immediately after mango::Problem::optimize().
     * You can see typical usage of this subroutine in the examples. However you are also free to
     * use your own approach to stopping the worker processes instead of this subroutine.
     */
    void stop_workers();

    //! Tell the worker MPI processes (i.e. those that are not group leaders) to begin an evaluation of the objective function.
    /**
     * This subroutine should only be called by group leaders.
     * This subroutine is typically called at the beginning of the user-supplied subroutine for the objective function.
     * You can see typical usage of this subroutine in the examples. However you are also free to
     * use your own approach to controlling the worker processes instead of this subroutine.
     */
    void mobilize_workers();

    //! For an MPI worker, determine whether to carry out another evaluation of the objective function or exit.
    /**
     * This subroutine should only be called on MPI processors that are not group leaders.
     * You can see typical usage of this subroutine in the examples. However you are also free to
     * use your own approach to controlling the worker processes instead of this subroutine.
     * @return If true, this processor should help to evaluate the objective function. If false, the optimization has been completed,
     *   so this processor can move on.
     */
    bool continue_worker_loop();
  };

  //////////////////////////////////////////////////////////////////////////////////////
  // Items specific to an optimization problem

  class Problem;
  typedef void (*objective_function_type)(int*, const double*, double*, int*, mango::Problem*, void*);
  typedef void (*residual_function_type)(int*, const double*, int*, double*, int*, mango::Problem*, void*);

  class Solver;
  class Problem {
  protected:
    // Many implementation details are hidden in the Solver class, so users see only the interface provided by Problem.
    Solver* solver;

  public:
    MPI_Partition mpi_partition;

    //! Constructor for a standard optimization problem
    /**
     * @param[in] N_parameters Number of independent variables.
     * @param[in] state_vector An array of size <span class="paramname">N_parameters</span>, giving the initial values of the independent variables.
     * @param[in] objective_function The objective function to minimize.
     * @param[in] argc (Optional) A number of arguments. Used to pass options to some optimization libraries. 
     * @param[in] argv (Optional) An array of arguments. Used to pass options to some optimization libraries. 
     */
    Problem(int N_parameters, double* state_vector, objective_function_type objective_function, int argc, char** argv); // For non-least-squares problems

    //! Destructor
    ~Problem();

    //! Initialize MANGO's internal MPI data that describes the partitioning of the processes into worker groups.
    /**
     * This subroutine divides up the available MPI processes into worker groups, after checking to see
     * if the selected optimization algorithm supports concurrent function evaluations.
     * Do not confuse this subroutine with MPI_Init, the routine from MPI that initializes MPI itself!
     * mango_mpi_init must be called by the driver code after the call to MPI_Init.
     * This subroutine should be called after setting N_worker_groups and setting the optimization algorithm.
     * This way, MANGO can change N_worker_groups to 1 if an algorithm is chosen that does not support concurrent function evaluations.
     * @param[in] mpi_comm  The MPI communicator to use for the optimization. Usually this is MPI_COMM_WORLD. However,
     *    if you want to run the optimization on a subset of MPI_COMM_WORLD, you can supply the appropriate communicator instead.
     */
    void mpi_init(MPI_Comm mpi_comm);

    //! Sets the optimization algorithm
    /**
     * Note the related subroutine of the same name that takes a std::string as input.
     * @param[in] algorithm One of the enumerated constants representing optimization algorithms.
     *  If this supplied integer is too large or too small, a C++ exception will be thrown.
     */
    void set_algorithm(algorithm_type algorithm);

    //! Sets the optimization algorithm
    /**
     * Note the related subroutine of the same name that takes a mango::algorithm_type as input.
     * @param[in] algorithm_str A lowercase string containing one of the available algorithms, e.g. "petsc_nm".
     * If the string supplied does not match any of the available algorithms, a C++ exception will be thrown.
    */
    void set_algorithm(std::string algorithm_str);

    //! Reads in the number of worker groups and algorithm from a file.
    /**
     * This subroutine is used in the examples, so the testing framework can vary the number of worker groups and optimization algorithm.
     * @param[in] filename The filename of the file to read.
     */
    void read_input_file(std::string filename);

    //! Sets the name of the output file that will record values of the objective function at each evaluation.
    /**
     * @param[in] filename A string giving the filename to use for the output file. If the file already exists, it will be over-written.
    */
    void set_output_filename(std::string filename);

    //! Sets bound constraints for the optimization problem.
    /**
     * @param[in] lower   An array of lower bounds, corresponding to
     *                    the vector of independent parameters. It is 
     *                    assumed that an array of size N_parameters has
     *                    been properly allocated.  
     * @param[in] upper   An array of upper bounds, corresponding to
     *                    the vector of independent parameters. It is 
     *                    assumed that an array of size N_parameters has
     *                    been properly allocated.  
    */
    void set_bound_constraints(double* lower, double* upper);

    //! Solve the optimization problem that has been set up.
    /**
     * This is the main computationally demanding step.
     * @return The minimum value found for the objective function.
     */
    double optimize();

    //! Get the number of independent variables for an optimization problem.
    /*
     * @return       The number of independent variables, i.e. the dimensionality of the parameter space.
     */
    int get_N_parameters();

    //! For an optimization problem that has already been solved, return the index of the function evaluation corresponding to the optimum.
    /**
     * @return The index of the function evaluation corresponding to the optimum.
     *  If mango::Problem::optimize() has not yet been called, a value of -1 will be returned.
     */
    int get_best_function_evaluation();

    //! For an optimization problem that has already been solved, return the number of times the objective function was evaluated.
    /**
     * @return The number of times the objective function was evaluated.
     *   If \ref mango_optimize has not yet been called, a value of 0 will be returned.
     */
    int get_function_evaluations();

    //! Get the vector of independent variables.
    /**
     * If mango::Problem::optimize() has not yet been called, this vector corresponds to the initial condition.
     * If mango::Problem::optimize() has been called, this vector corresponds to the location of the optimum that was found.
     * @return A pointer to the vector of length N_parameters storing the independent variables.
     */
    double* get_state_vector();

    //! Control whether 1-sided or centered finite differences will be used to compute derivatives of the objective function.
    /**
     * @param centered_differences If true, centered differences will be used. If false, 1-sided differences will be used.
     *   Centered differences are more accurate, but require more function evaluations (2*N_parameters) compared to
     *   1-sided differences (which require N_parameters+1 evaluations).
     */
    void set_centered_differences(bool centered_differences);

    //! Set an absolute step size for finite difference derivatives.
    /**
     * @param[in] finite_difference_step_size An absolute step size to use for finite difference derivatives.
     */
    void set_finite_difference_step_size(double finite_difference_step_size);

    //! Set the maximum number of evaluations of the objective function that will be allowed before the optimization is terminated.
    /**
     * @param[in] N The maximum number of evaluations of the objective function that will be allowed before the optimization is terminated.
     *   If this number is less than 1, a C++ exception will be thrown.
     */
    void set_max_function_evaluations(int N);

    //! Control how much diagnostic information is printed by MANGO.
    /**
     * This diagnostic information may be helpful for debugging.
     * @param[in] verbose If <= 0, no diagnostic information will be printed. If >0, diagnostic information will be printed.
     */
    void set_verbose(int verbose);

    //! Sets the name of the output file that will record values of the objective function at each evaluation.
    /**
     * @param[in] filename A string giving the filename to use for the output file. If the file already exists, it will be over-written.
     */
    void set_output_filename(std::string& filename);

    //! Pass the prescribed pointer to the objective function whenever it is called.
    /**
     * This method allows any data structure to be passed to the objective function.
     * @param[in] user_data A pointer to any data (you can cast any pointer to type void*).
     */
    void set_user_data(void* user_data);

    //! Impose bound constraints on an optimization problem, with the bounds chosen as multiples of the initial state vector.
    /**
     * To use this subroutine, you must first call mango::Problem::set_bound_constraints, so MANGO has pointers to the 
     * arrays allocted by the user for lower and upper bounds. mango::Problem::set_relative_bound_constraints will overwrite the entries of these arrays.
     *
     * There are two possible methods of determining the bound constraints using this subroutine, depending
     * on the parameter preserve_sign. 
     *
     * If preserve_sign is false, the bounds will be symmetric about 0, given by the value
     * of the initial condition multiplied by max_factor, expanded to be at least min_radius different from
     * the initial condition. Thus, for independent
     * variable \f$ x_j \f$, the bounds will be \f$ x_j \in [-R_j, R_j] \f$, where
     * \f$ R_j = \max(\mathtt{min\_radius}, |x_j| \mathtt{max\_factor})\f$. 
     * Note that the parameter min_factor is not used in this case.
     *
     * If preserve_sign is true, the lower and upper bounds for a given independent variable
     * will have the same sign as the corresponding element of state_vector (the initial condition supplied to the constructor).
     * The bounds are determined by multiplying each independent variable by min_factor and max_factor, keeping
     * both bounds at least min_radius from the initial condition (while not crossing 0).
     * Thus, if independent variable \f$ x_j \f$ is positive, the bounds will be \f$ x_j \in [L_j, R_j] \f$ where
     * \f$ L_j = \max(0, \min(x_j - \mathtt{min\_radius}, x_j \, \mathtt{min\_factor})) \f$ and
     * \f$ R_j = \max(x_j + \mathtt{min\_radius}, x_j \, \mathtt{max\_factor}) \f$.
     * If independent variable \f$ x_j \f$ is negative, the bounds will be \f$ x_j \in [L_j, R_j] \f$ where
     * \f$ L_j = \min(x_j - \mathtt{min\_radius}, x_j \, \mathtt{max\_factor}) \f$ and
     * \f$ R_j = \min(0, \max(x_j + \mathtt{min\_radius}, x_j \, \mathtt{min\_factor})) \f$.
     * For the special case \f$x_j=0\f$, then the bounds are \f$ x_j \in [-\mathtt{min\_radius}, \mathtt{min\_radius}] \f$.
     *
     * Note that not every optimization algorithm allows bound constraints. If bound constraints
     * have been turned on with this subroutine and mango::Problem::optimize is called,
     * MANGO will check whether the selected algorithm supports bound constraints. If not,
     * a warning message will be printed to stdout, and the optimization will proceed,
     * ignoring the bound constraints.
     * @param min_factor See description above. The value must lie in [0,1] or else a C++ exception will be thrown.
     * @param max_factor See description above. The value must be \f$ \ge 1 \f$, or else a C++ expection will be thrown.
     * @param min_radius See description above. The value must be \f$ \ge 0 \f$, or else a C++ exception will be thrown.
     * @param preserve_sign See description above.
     */
    void set_relative_bound_constraints(double min_factor, double max_factor, double min_radius, bool preserve_sign);

    //! Sets the number of points considered as a set for parallel line searches
    /**
     * The default value is 0.
     * If the value is \f$<=\f$0, the number will be set to the number of worker groups.
     * Normally this default makes sense.
     * @param N_line_search The number of points considered as a set for parallel line searches.
     */
    void set_N_line_search(int N_line_search);
  };

  
  //////////////////////////////////////////////////////////////////////////////////////
  // A least-squares problem is a subclass of Problem

  class Least_squares_solver;
  class Least_squares_problem : public Problem {
  private:
    // Many implementation details are hidden in the Least_squares_solver class, so users see only the interface provided by Least_squares_problem.
    Least_squares_solver* least_squares_solver;

  public:
    //! Constructor for a least-squares optimization problem
    /**
     * @param[in] N_parameters Number of independent variables.
     * @param[in] state_vector An array of size <span class="paramname">N_parameters</span>, giving the initial values of the independent variables.
     * @param[in] N_terms The number of least-squares terms that are summed to form the total objective function.
     * @param[in] targets An array of size <span class="paramname">N_terms</span>, containing the target values \f$ T_j \f$ in @ref concepts.
     * @param[in] sigmas An array of size <span class="paramname">N_terms</span>, containing the weights \f$ \sigma_j \f$ in @ref concepts.
     * @param[in] best_residual_function An array of size <span class="paramname">N_terms</span>, which will be used to store the
     *    values of the residuals \f$ R_j \f$ at the optimum.
     * @param[in] residual_function The user-supplied subroutine that computes the residuals \f$ R_j \f$.
     * @param[in] argc (Optional) A number of arguments. Used to pass options to some optimization libraries. 
     * @param[in] argv (Optional) An array of arguments. Used to pass options to some optimization libraries. 
     */
    Least_squares_problem(int N_parameters, double* state_vector, int N_terms, double* targets, double* sigmas, double* best_residual_function, residual_function_type residual_function, int argc, char** argv);

    //! Destructor
    ~Least_squares_problem();

    //! Return the number of least-squares terms that are summed to form the objective function.
    /*
     * @return The number of least-squares terms that are summed to form the objective function.
     */
    int get_N_terms();

    //! Determine whether or not to print each individual residual in the MANGO output file.
    /**
     * You may wish to print this information to see the relative magnitude of each term
     * in the objective function. On the other hand, for problems with many terms, you may
     * wish to suppress this information to make the file more readable.
     *
     * @param[in] print Whether or not to print every residual term in the output file.
     */
    void set_print_residuals_in_output_file(bool print);
  };
}

#endif
