#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

#include<libc.h>
#include<stdbool.h>
#include <pthread.h>
#include <sys/time.h>
#define NUM_OF_THREAD 3


typedef struct{
	size_t	index;
	size_t	thread_index;
	long	initial_time;
	bool	fork_status;
	pthread_mutex_t mutex_id;
	pthread_t	thread_id;
	struct s_env	*env;
}t_philo_env;


typedef struct s_env{
	t_philo_env	philo[NUM_OF_THREAD ];
	size_t	number_of_philosophers;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	size_t	number_of_times_each_philosopher_must_eat;
	long	initial_time;
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
