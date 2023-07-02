/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobushi <mobushi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 19:49:26 by mobushi           #+#    #+#             */
/*   Updated: 2023/07/02 22:37:38 by mobushi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	get_fork(t_philo *input)
{
	pthread_mutex_lock(input->right_fork);
	pthread_mutex_lock(&input->env->lock);
	if (input->env->is_everyone_dead == 0 && input->is_finished_flag == 1)
	{
		printf("%lld %zu has taken a fork\n",
			ft_get_time(input->env->start_thread_time * 1000) / 1000,
			input->index + 1);
	}
	pthread_mutex_unlock(&input->env->lock);
	pthread_mutex_lock(input->left_fork);
	pthread_mutex_lock(&input->env->lock);
	if (input->env->is_everyone_dead == 0 && input->is_finished_flag == 1)
	{
		printf("%lld %zu has taken a fork\n",
			ft_get_time(input->env->start_thread_time * 1000) / 1000,
			input->index + 1);
	}
	pthread_mutex_unlock(&input->env->lock);
}

void	drop_fork(t_philo *input)
{
	pthread_mutex_unlock(input->right_fork);
	pthread_mutex_unlock(input->left_fork);
}

void	philo_sleep(t_philo *input)
{
	pthread_mutex_lock(&input->env->lock);
	if (input->env->is_everyone_dead == 0 && input->is_finished_flag == 1)
	{
		printf("%lld %zu is sleeping\n",
			ft_get_time(input->env->start_thread_time * 1000) / 1000,
			input->index + 1);
	}
	if (input->eat_count >= input->env->number_of_must_eat
		&& input->env->number_of_must_eat != -1)
	{
		input->is_finished_flag = 0;
		input->env->is_finished++;
	}
	pthread_mutex_unlock(&input->env->lock);
	ft_usleep(input->env->time_to_sleep * 1000);
}

void	philo_think(t_philo *input)
{
	pthread_mutex_lock(&input->env->lock);
	if (input->env->is_everyone_dead == 0 && input->is_finished_flag == 1)
		printf("%lld %zu is thinking\n",
			ft_get_time(input->env->start_thread_time * 1000) / 1000,
			input->index + 1);
	pthread_mutex_unlock(&input->env->lock);
}

void	philo_eat(t_philo *input)
{
	get_fork(input);
	pthread_mutex_lock(&input->plock);
	input->eat_status = 1;
	input->eat_count++;
	input->ideal_death_time = ft_get_time(0) / 1000 + input->env->time_to_die;
	input->eat_status = 0;
	if (input->env->is_everyone_dead == 0 && input->is_finished_flag == 1)
		printf("%lld %zu is eating\n",
			ft_get_time(input->env->start_thread_time * 1000) / 1000,
			input->index + 1);
	pthread_mutex_unlock(&input->plock);
	ft_usleep(input->env->time_to_eat * 1000);
	drop_fork(input);
}