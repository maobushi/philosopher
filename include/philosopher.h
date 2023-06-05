#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

#include<libc.h>
#include<stdbool.h>
#include <pthread.h>
#include <sys/time.h>
#define NUM_OF_THREAD 4


typedef struct{
	
	pthread_mutex_t	*forks;
	pthread_mutex_t	fork;
}t_philo_env;


typedef struct{
	t_philo_env	philo;
	size_t	number_of_philosophers;
	size_t	index;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	size_t	number_of_times_each_philosopher_must_eat;
	long	initial_time;
	pthread_mutex_t mutex_id[NUM_OF_THREAD];
	pthread_t	thread_id[NUM_OF_THREAD];
}t_env;


struct timeval current_time;

void init_philosophers(t_env * env);
void end_philosophers(t_env *env);
int ft_atoi(const char *str);
bool check_argv(char **argv);
bool check_input_format(int argc, char **argv);
void end_philosophers(t_env *env);

void write_input_env(t_env *env, int argc, char **argv);
#endif
