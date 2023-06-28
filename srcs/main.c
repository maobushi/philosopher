#include "../include/philosopher.h"

int main(int argc, char **argv)
{
    t_env env;

    if (check_input_format(argc, argv))
    {
        printf("your arg is correct\n");
        alloc_input_env(&env, argc, argv);    
		printf("argv[1]:%zu\n", env.number_of_philosophers);
        printf("argv[2]:%zu\n", env.time_to_die);
        printf("argv[3]:%zu\n", env.time_to_eat);
        printf("argv[4]:%zu\n", env.time_to_sleep); 
        printf("argv[5]:%d\n", env.number_of_must_eat);
    }
		else
    {
        printf("your input is incorrect\n");
        return 1;
    }
    return 0;
}

