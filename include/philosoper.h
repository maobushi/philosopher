#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

#include<libc.h>

typedef struct{
	size_t	number_of_philosophers;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	size_t	number_of_times_each_philosopher_must_eat;
}input_env;

#endif
