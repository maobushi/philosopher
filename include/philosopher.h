#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

#include<libc.h>
#include<stdbool.h>
#include <pthread.h>
#include <sys/time.h>
#define NUM_OF_THREAD 3
#define ERROR_ARG "Invalid Argument!"

struct s_env;

typedef struct{
	size_t	index;
	long	initial_time;
	pthread_mutex_t lock;
	struct s_env	*env;
	
}t_philo;


typedef struct s_env{
	t_philo			*philo_id;
	pthread_mutex_t	*fork_id;
	pthread_t		*thread_id;
	pthread_mutex_t	write;
	pthread_mutex_t lock;
	size_t			number_of_philosophers;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int			number_of_must_eat;
	long			initial_time;

}t_env;


struct timeval current_time;

void init_philosophers(t_env * env);
void end_philosophers(t_env *env);
int ft_atoi(const char *str);
bool check_argv(char **argv);
bool check_input_format(int argc, char **argv);
void end_philosophers(t_env *env);

void alloc_input_env(t_env *env, int argc, char **argv);
#endif
