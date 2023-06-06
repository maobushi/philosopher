#include "../include/philosopher.h"

long ft_gettime(void)
{
	gettimeofday(&current_time,NULL);
	return (current_time.tv_sec);	
}

void p_eat(t_philo_env *env)
{
	pthread_mutex_lock(&(env->mutex_id));
	if(env->env->philo[env->index].index == NUM_OF_THREAD - 1)
				env->env->philo[env->index + 1].fork_status = env->env->philo[0].fork_status;
	else if(env->env->philo[env->index].index == 0)
				env->env->philo[0].fork_status = env->env->philo[env->index + 1].fork_status;
	
	if(env->fork_status == false)
	{
		printf("%ld ",ft_gettime() - env->initial_time);
		printf("%zu has taken a fork[%zu]\n",env->index,env->index);
		env->fork_status = true;
		//env->env->philo[env->index + 1].index
		if(env->fork_status == true && env->env->philo[env->index + 1].fork_status == false)
		{
			printf("%ld ",ft_gettime() - env->initial_time);
			printf("%zu has taken a fork[%zu]\n",env->index,env->env->philo[env->index + 1].index);
			env->env->philo[env->index + 1].fork_status = true;
			
			printf("%ld ",ft_gettime() - env->initial_time);
			printf("%zu is eating\n",env->index);
		}
	}
	pthread_mutex_unlock(&(env->mutex_id));
}

void p_sleep(t_philo_env *env)
{
	if(env->env->philo[env->index].fork_status == true && env->env->philo[env->index + 1].fork_status == true)
	{
		printf("%ld %zu is sleeping\n",ft_gettime() - env->initial_time,env->index);
		sleep(1);
		pthread_mutex_lock(&(env->mutex_id));
		env->env->philo[env->index].fork_status = false;
		env->env->philo[env->index + 1].fork_status = false;
		pthread_mutex_unlock(&(env->mutex_id));
		printf("%ld %zu is wake up\n",ft_gettime() - env->initial_time,env->index);
	}
}

void *thread_function(void *input)
{
	t_philo_env * env;
	env = (t_philo_env *)input;

	while(1)
	{
		if(env->index % 2 == 1)
		{
			usleep(20000);
			//printf("this thread_id is %zu\n",env->index);
			//return NULL;
		}
		p_eat(env);


		p_sleep(env);
	}
	return NULL;
}

void init_philosophers(t_env *env)
{
	env->initial_time = ft_gettime();

	//printf("your current time is:%ld\n",env->initial_time - ft_gettime());
	printf("======================\n");
	size_t i = 0;

	while(i < NUM_OF_THREAD)
	{
		env->philo[i].initial_time = env->initial_time;
		env->philo[i].index = i;
		env->philo[i].fork_status = false;
		env->philo[i].env = env;

		pthread_mutex_init(&(env->philo[i].mutex_id),NULL);
		pthread_create(&(env->philo[i].thread_id),NULL,thread_function,&env->philo[i]);
		//sleep(1);
		i++;
	}
}

void end_philosophers(t_env *env)
{
	sleep(1000);
	size_t i = 0;
	printf("end_philosophers\n");
	while(i < NUM_OF_THREAD)
	{
		pthread_mutex_destroy(&(env->philo[i].mutex_id));
		pthread_join((env->philo[i].thread_id),NULL);
		i++;
	}
}