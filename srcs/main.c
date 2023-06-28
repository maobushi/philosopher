#include "../include/philosopher.h"

void * routine(void *arg){
	t_philo *input;
	input = (t_philo *)arg;

	while(input->env->is_finished)
	{
		//時間制限が来ていないか、最後に食べた時からの時間が指定時間を超えていないかを例外処理する
		// eat(&arg);
		// sleep(&arg);
		// think(&arg);
	}

	return((void*)0);
}

int init_thread(t_env *env)
{
	size_t  i;
	i=0;
	while(i < env->number_of_philosophers)
	{
		pthread_create(&env->thread_id[i],NULL,routine,&env);
		i++;
	}
	// if(env->number_of_must_eat > 0)
	// {
	// 	while()
	// 	{
	// 		while
	// 	}
	// }
	printf("can u see me?");
	usleep(100);
	i=0;
	while(i < env->number_of_philosophers)
	{
		pthread_join(env->thread_id[i],NULL);
		i++;
	}
	return 0;
}

int init_alloc(t_env *env)
{
	size_t i;

	i=0;
	while(i< env->number_of_philosophers)
	{
		if(i == 0)
		{
			env->philo_id[0].left_fork = &env->fork_id[0];
			env->philo_id[0].right_fork = &env->fork_id[env->number_of_philosophers - 1];
		}
		env->philo_id[i].left_fork = &env->fork_id[i];
		env->philo_id[i].right_fork = &env->fork_id[i-1];
		i++;
	}
	return 0;
}


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
		if(init_alloc(&env))
			return 1;
		if(init_thread(&env))
			return 1;
	}
		else
	{
		printf("your input is incorrect\n");
		return 1;
	}
	return 0;
}

