#include "../include/philosopher.h"

void init_philosophers(t_input_env * env,pthread_mutex_t * forks,bool *forks_status)
{
	size_t i;
	i = 0;
	while(i < env->number_of_philosophers)
	{
		forks_status[i] = false;
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}

}

void eating_philosophers(t_input_env * env, pthread_mutex_t *forks,size_t index)
{
	pthread_mutex_lock(&forks[index]);
	printf("philosopher[%zu] is eating\n",index);

	
}

void moving_philosophers(t_input_env * env, pthread_mutex_t *forks, bool *forks_status)
{
	size_t	i;
	i = 0;

	while(i < env->number_of_philosophers)
	{
		while(1)
		{
		if (forks_status[i] == false)
		{
			pthread_mutex_lock(&forks[i]);
			forks_status[i] = true;
			printf("philosopher[%zu] is eating\n",i);
			pthread_mutex_unlock(&forks[i]);
		}
		i++;
		}
	}

}