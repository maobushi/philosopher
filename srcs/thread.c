/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobushi <mobushi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 19:46:43 by mobushi           #+#    #+#             */
/*   Updated: 2023/07/02 22:46:21 by mobushi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	*waiter(void *arg)
{
	t_philo	*input;

	input = (t_philo *)arg;
	while (input->env->is_everyone_dead == 0 && input->is_finished_flag == 1)
	{
		pthread_mutex_lock(&input->plock);
		if ((ft_get_time(input->ideal_death_time * 1000) / 1000) > 0
			&& input->eat_status == 0)
		{
			pthread_mutex_lock(&input->env->lock);
			if (input->env->is_everyone_dead == 0)
				printf("%lld %zu died\n",
					ft_get_time(input->env->start_thread_time * 1000)
					/ 1000, input->index + 1);
			input->env->is_everyone_dead++;
			pthread_mutex_unlock(&input->env->lock);
			pthread_mutex_unlock(&input->plock);
			return ((void *)0);
		}
		pthread_mutex_unlock(&input->plock);
		usleep(200);
	}
	return ((void *)0);
}

void	*routine(void *arg)
{
	t_philo	*input;

	input = (t_philo *) arg;
	if (input->index % 2 == 1)
		ft_usleep(input->env->time_to_eat * 1000);
	input->ideal_death_time = ft_get_time(0) / 1000 + input->env->time_to_die;
	pthread_create(&input->waiter_id, NULL, waiter, input);
	while (input->env->is_everyone_dead == 0)
	{
		philo_eat(input);
		philo_sleep(input);
		philo_think(input);
	}
	if (pthread_join(input->waiter_id, NULL))
		return ((void *)1);
	return ((void *)0);
}

void	*monitor(void *arg)
{
	t_philo	*input;

	input = (t_philo *)arg;
	while (input->env->is_everyone_dead == 0)
	{
		pthread_mutex_lock(&input->env->lock);
		if (input->env->is_finished >= input->env->num_of_ph)
			input->env->is_everyone_dead++;
		pthread_mutex_unlock(&input->env->lock);
	}
	return ((void *)0);
}

int	init_thread(t_env *env)
{
	int			i;
	pthread_t	monitor_id;

	i = 0;
	if (env->num_of_ph == 1)
	{
		one_case(&env->philo_id[0]);
		return (0);
	}
	if (env->number_of_must_eat > 0)
		pthread_create(&monitor_id, NULL, monitor, env);
	env->start_thread_time = ft_get_time(0) / 1000;
	while (i < env->num_of_ph) {
		pthread_create(&env->thread_id[i], NULL, routine, &env->philo_id[i]);
		i++;
	}

	i = -1;
	if (0 < env->number_of_must_eat)
		pthread_join(monitor_id, NULL);
	while (++i < env->num_of_ph)
		pthread_join(env->thread_id[i], NULL);
	return (0);
}
