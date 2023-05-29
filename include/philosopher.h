#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

#include<libc.h>
#include<stdbool.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct{
	size_t	number_of_philosophers;
	size_t	index;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	size_t	number_of_times_each_philosopher_must_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	fork;
}t_input_env;

struct timeval current_time;

void init_philosophers(t_input_env * env);
int ft_atoi(const char *str);
bool check_argv(char **argv);
bool check_input_format(int argc, char **argv);


void write_input_env(t_input_env *env, int argc, char **argv);
#endif
