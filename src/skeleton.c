/**
 * \file skeleton.c
 * \brief Basic parsing options skeleton.
 * \author Pierre L. <pierre1.leroy@orange.com>
 * \version 0.1
 * \date 10 septembre 2016
 *
 * Basic parsing options skeleton exemple c file.
 */

#include "skeleton.h"

/**
 * Procedure which displays binary usage
 * by printing on stdout all available options
 *
 * \return void
 */
void print_usage(char* bin_name)
{
  dprintf(1, "USAGE: %s %s\n\n%s\n", bin_name, USAGE_SYNTAX, USAGE_PARAMS);
}

/** 
 * Print method to display information in the console in blue color
 * \param message the message to display
 * \param ... list of args
 * \return void
*/
void print_info(const char* message, ...)
{
  va_list args;
  va_start(args, message);
  printf("\033[1;34m");
  vprintf(message, args);
  printf("\033[0m");
  va_end(args);  
}

/**
 * Procedure checks if variable must be free
 * (check: ptr != NULL)
 *
 * \param void* to_free pointer to an allocated mem
 * \see man 3 free
 * \return void
 */
void free_if_needed(void* to_free)
{
  if (to_free != NULL) free(to_free);  
}


/**
 *
 * \see man 3 strndup
 * \see man 3 perror
 * \return
 */
char* dup_optarg_str()
{
  char* str = NULL;

  if (optarg != NULL)
  {
    str = strndup(optarg, MAX_PATH_LENGTH);
    
    // Checking if ERRNO is set
    if (str == NULL) 
      perror(strerror(errno));
  }

  return str;
}

/**
 * Binary main loop
 *
 * \return 1 if it exit successfully 
 */
int main(int argc, char** argv)
{
  /**
   * Binary variables
   * (could be defined in a structure)
   */
  char* bin_command = argv[1];
  short int is_verbose_mode = 0;
  char* bin_input_param = NULL;
  char* bin_output_param = NULL;

  // Parsing options
  int opt = -1;
  int opt_idx = -1;

  while ((opt = getopt_long(argc, argv, binary_optstr, binary_opts, &opt_idx)) != -1)
  {
    switch (opt)
    {
      case 'i':
        //input param
        if (optarg)
        {
          bin_input_param = dup_optarg_str();         
        }
        break;
      case 'o':
        //output param
        if (optarg)
        {
          bin_output_param = dup_optarg_str();
        }
        break;
      case 'v':
        //verbose mode
        is_verbose_mode = 1;
        break;
      case 'h':
        print_usage(argv[0]);

        free_if_needed(bin_input_param);
        free_if_needed(bin_output_param);
 
        exit(EXIT_SUCCESS);
      default :
        break;
    }
  } 

  /**
   * Checking binary requirements
   * (could defined in a separate function)
   */
  if (bin_input_param == NULL || bin_output_param == NULL)
  {
    dprintf(STDERR, "Bad usage! See HELP [--help|-h]\n");

    // Freeing allocated data
    free_if_needed(bin_input_param);
    free_if_needed(bin_output_param);
    // Exiting with a failure ERROR CODE (== 1)
    exit(EXIT_FAILURE);
  }

  // Printing params
  dprintf(1, "** PARAMS **\n%-8s: %s\n%-8s: %s\n%-8s: %d\n", 
          "input",   bin_input_param, 
          "output",  bin_output_param, 
          "verbose", is_verbose_mode);

  printf("** COMMAND **\nmethod  : %s\n", bin_command);

  int result = 0;
  if(strcmp(bin_command, "copy") == 0)
  {
    result = copy_file(bin_input_param, bin_output_param);
  }
  else if(strcmp(bin_command, "reverse") == 0)
  {
    result = reverse_file(bin_input_param);
  }
  else if(strcmp(bin_command, "ls") == 0)
  {
    result = ls_command(bin_input_param);
  }
  else
  {
    printf("Unknown command\n");
    free_if_needed(bin_input_param);
    free_if_needed(bin_output_param);
    exit(EXIT_FAILURE);
  }

  if(result != 0)
  {
    printf("Error while executing command\n");
    free_if_needed(bin_input_param);
    free_if_needed(bin_output_param);
    exit(EXIT_FAILURE);
  }

  // Freeing allocated data
  free_if_needed(bin_input_param);
  free_if_needed(bin_output_param);

  return EXIT_SUCCESS;
}