#include "../include/philosopher.h"

long ft_gettime(void)
{
	gettimeofday(&current_time,NULL);
	return (current_time.tv_sec);	
}

void eat(t_env *env)
{
	pthread_mutex_lock(&(env->mutex_id[env->index]));
	printf("this thread number is:%zu\n",env->index);
	printf("initial_time:%ld\n",env->initial_time);
	printf("current_time:%ld\n",ft_gettime());
	pthread_mutex_unlock(&(env->mutex_id[env->index]));

}



void *thread_function(void *input)
{
	t_env * env;
	env = (t_env *)input;

	printf("thread_function!\n");
	eat(env);
	// sleep(input);

	return NULL;
}

void init_philosophers(t_env *env)
{
	// pthread_t mutex[100];
	printf("hello:%ld\n",env->time_to_die);
	env->initial_time = ft_gettime();

	printf("your current time is:%ld\n",env->initial_time);
	size_t i = 0;

	while(i < NUM_OF_THREAD)
	{
		env->index = i;
		pthread_mutex_init(&(env->mutex_id[i]),NULL);
		pthread_create(&(env->thread_id[i]),NULL,thread_function,env);
		i++;
	}

	//init each philosopher info
	// size_t i;
	// i = 0;
	// while(i < env->number_of_philosophers)
	// {
	// 	env->philo.
	// 	i++;
	// }
}

void end_philosophers(t_env *env)
{
	usleep(100);
	size_t i = 0;
	printf("end_philosophers\n");
	while(i < NUM_OF_THREAD)
	{
		pthread_mutex_destroy(&(env->mutex_id[i]));
		pthread_join((env->thread_id[i]),NULL);
		i++;
	}
}