/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobushi <mobushi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 18:50:09 by mobushi           #+#    #+#             */
/*   Updated: 2023/07/02 22:00:58 by mobushi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	one_case(t_philo *input)
{
	pthread_mutex_lock(input->left_fork);
	printf("%lld %zu has taken a fork\n",
		ft_get_time(input->env->start_thread_time * 1000) / 1000,
		input->index + 1);
	ft_usleep(input->env->time_to_die * 1000);
	printf("%lld %zu died\n",
		ft_get_time(input->env->start_thread_time * 1000) / 1000,
		input->index + 1);
	pthread_mutex_unlock(input->left_fork);
}

void	init_thread_alloc(t_env *env, int i)
{
	pthread_mutex_init(&env->philo_id[i].plock, NULL);
	env->philo_id[i].index = i;
	env->philo_id[i].eat_count = 0;
	env->philo_id[i].env = env;
	env->philo_id[i].eat_status = 0;
	env->philo_id[i].end_time_meal = env->time_to_eat;
	env->philo_id[i].is_finished_flag = 1;
}

int	init_alloc(t_env *env)
{
	int	i;

	i = 0;
	env->start_thread_time = ft_get_time(0) / 1000;
	env->is_everyone_dead = 0;
	env->is_finished = 0;
	while (i < env->num_of_ph)
	{
		if (pthread_mutex_init(&env->fork_id[i], NULL) != 0
			|| pthread_mutex_init(&env->lock, NULL) != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < env->num_of_ph)
	{
		if (i == 0)
		{
			env->philo_id[0].left_fork = &env->fork_id[0];
			env->philo_id[0].right_fork = &env->fork_id[env->num_of_ph - 1];
		}
		else
		{
			env->philo_id[i].left_fork = &env->fork_id[i];
			env->philo_id[i].right_fork = &env->fork_id[i - 1];
		}
			 init_thread_alloc(env, i);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_env	env;

	if (check_input_format(argc, argv))
	{
		alloc_input_env(&env, argc, argv);
		if (init_alloc(&env) != 0)
			return (1);
		if (init_thread(&env) != 0)
			return (1);
	}
	else
	{
		printf("your input is incorrect\n");
		return (1);
	}
	return (0);
}
