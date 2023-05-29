#include "../include/philosopher.h"


void philosopher_eating(long time,size_t index)
{
	printf("%ld %zu is eating\n",time,index);
}

void philosopher_thinking(long time,size_t index)
{
	printf("%ld %zu is sleeping\n",time,index);
}

void philosopher_sleeping(long time,size_t index)
{
	printf("%ld %zu is thinking\n",time,index);
}


void do_philosopher(void *input)
{
	t_input_env *env = (t_input_env *)input;
	gettimeofday(&current_time,NULL);

	pthread_mutex_lock(&env->fork);
	if(env->index % 2 == 1)
		usleep(100);
	philosopher_eating(current_time.tv_sec,env->index);
	philosopher_thinking(current_time.tv_sec,env->index);
	philosopher_sleeping(current_time.tv_sec,env->index);
	pthread_mutex_unlock(&env->fork);
}

void init_philosophers(t_input_env * env)
{
	size_t i;
	i = 0;

	while(i < env->number_of_philosophers)
	{
		env->index = i;
		env->fork = env->forks[i];
		pthread_mutex_init(&env->forks[i], NULL);
		pthread_create(&env->forks[i],NULL,do_philosopher,&env);
		i++;
	}

	

}
