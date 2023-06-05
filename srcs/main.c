#include "../include/philosopher.h"

int main(int argc, char **argv)
{
    t_env env;
    //you should use initialize function here

    if (check_input_format(argc, argv))
    {
        printf("your arg is correct\n");
        write_input_env(&env, argc, argv);    
		printf("argv[1]:%zu\n", env.number_of_philosophers);
        printf("argv[2]:%zu\n", env.time_to_die);
        printf("argv[3]:%zu\n", env.time_to_eat);
        printf("argv[4]:%zu\n", env.time_to_sleep); 
        printf("argv[5]:%zu\n", env.number_of_times_each_philosopher_must_eat);
       // moving_philosophers(env,forks,forks_status);

        //error handling
        //error handling
        init_philosophers(&env);
        end_philosophers(&env);

    }
		else
    {
        printf("your input is incorrect\n");
        return 1;
    }
    return 0;
}

