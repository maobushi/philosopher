#include "../include/philosopher.h"

int main(int argc, char **argv)
{
    t_input_env *env;
    pthread_mutex_t *forks;
    bool *forks_status;

    if (check_input_format(argc, argv))
    {
        printf("your arg is correct\n");
        env = malloc(sizeof(t_input_env));
        if (env == NULL) 
        {
            printf("Failed to allocate memory for env\n");
           return 1;
        }
        write_input_env(env, argc, argv);    
		printf("argv[1]:%zu\n", env->number_of_philosophers);
        printf("argv[2]:%zu\n", env->time_to_die);
        printf("argv[3]:%zu\n", env->time_to_eat);
        printf("argv[4]:%zu\n", env->time_to_sleep); 
        printf("argv[5]:%zu\n", env->number_of_times_each_philosopher_must_eat);
       // moving_philosophers(env,forks,forks_status);


        forks = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t) * env->number_of_philosophers);
        //error handling
        forks_status = (bool*)malloc(sizeof(bool) * env->number_of_philosophers);
        //error handling
        init_philosophers(env,forks,forks_status);  
       printf("forks_status[0]:%d\n",forks_status[0]);
       pthread_mutex_destroy(forks);
       free(forks);
        free(env);
    }
		else
    {
        printf("your input is incorrect\n");
        return 1;
    }
    return 0;
}

