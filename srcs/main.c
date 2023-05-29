#include "../include/philosopher.h"

int main(int argc, char **argv)
{
    t_input_env *env;
	
	
	env = malloc(sizeof(t_input_env));
    if (env == NULL) {
        printf("Failed to allocate memory for env\n");
        return 1;
    }

    if (check_input_format(argc, argv))
    {
        printf("your arg is correct\n");
        write_input_env(env, argc, argv);    
		printf("argv[1]:%zu\n", env->number_of_philosophers);
        printf("argv[2]:%zu\n", env->time_to_die);
        printf("argv[3]:%zu\n", env->time_to_eat);
        printf("argv[4]:%zu\n", env->time_to_sleep); 
        printf("argv[5]:%zu\n", env->number_of_times_each_philosopher_must_eat);
		init_philosophers(env)
    }
		else
    {
        printf("your input is incorrect\n");
        free(env);
        return 1;
    }

    free(env);
    return 0;
}

