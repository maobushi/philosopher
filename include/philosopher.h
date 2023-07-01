#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

#include<libc.h>
#include<stdbool.h>
#include <pthread.h>
#include <sys/time.h>
#define NUM_OF_THREAD 3
#define ERROR_ARG "Invalid Argument!"
#define MAX_PHILO_NUM 500

struct s_env;

typedef struct{
	size_t				index;
	int					eat_status;
	int					eat_count;
	long long			ideal_death_time;
	long long			start_time_meal;
	long long			end_time_meal;
	pthread_t    		 monitor_id;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t 	plock;
	struct s_env	*env; // is it possible to remove "struct"?
	
}t_philo;


typedef struct s_env{
	t_philo				philo_id[MAX_PHILO_NUM];
	pthread_mutex_t		fork_id[MAX_PHILO_NUM];
	pthread_t			thread_id[MAX_PHILO_NUM];
	pthread_mutex_t		write;
	pthread_mutex_t 	lock;
	int					number_of_philosophers;
	long long			time_to_die;
	long long			time_to_eat;
	long long			time_to_sleep;
	int					is_finished;
	int					number_of_must_eat; //
	int					num_of_eat; //everyone has 1 increment 
	int					is_everyone_dead;
	long long			start_thread_time;

}t_env;


struct timeval current_time;

void init_philosophers(t_env * env);
void end_philosophers(t_env *env);
int ft_atoi(const char *str);
bool check_argv(char **argv);
bool check_input_format(int argc, char **argv);
void end_philosophers(t_env *env);
long long ft_get_time(long long input);
int	ft_usleep(useconds_t time);
void alloc_input_env(t_env *env, int argc, char **argv);
#endif
