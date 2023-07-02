/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobushi <mobushi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 18:49:59 by mobushi           #+#    #+#             */
/*   Updated: 2023/07/02 21:32:03 by mobushi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

int	ft_atoi(const char *str)
{
	long long	ln;
	size_t		n;
	int			sign;

	sign = 1;
	ln = 0;
	n = 0;
	while (str[n] == 32 || (9 <= str[n] && str[n] <= 13))
		n++;
	if (str[n] == '-')
		sign *= -1;
	if (str[n] == '+' || str[n] == '-')
		n++;
	while ('0' <= str[n] && str[n] <= '9')
	{
		if (ln != ((ln * 10) + (str[n] - '0') * sign) / 10 && sign > 0)
			return ((int)LONG_MAX);
		if (ln != ((ln * 10) + (str[n] - '0') * sign) / 10 && sign < 0)
			return ((int)LONG_MIN);
		ln = (ln * 10) + (str[n] - '0') * sign;
		n++;
	}
	return ((int)ln);
}

bool	check_argv(char **argv, int argc)
{
	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[2]) < 0
		|| ft_atoi(argv[3]) < 0 || ft_atoi(argv[4]) < 0)
	{
		return (false);
	}
	else if (argc == 6)
	{
		if (ft_atoi(argv[5]) <= 0)
			return (false);
	}
	return (true);
}

bool	check_input_format(int argc, char **argv)
{
	size_t	i;
	size_t	j;

	i = 1;
	if (!(argc == 5 || argc == 6))
	{
		printf(ERROR_ARG);
		return (false);
	}
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!('0' <= argv[i][j] && argv[i][j] <= '9'))
				return (false);
			j++;
		}
		i++;
	}
	return (check_argv(argv, argc));
}

void	alloc_input_env(t_env *env, int argc, char **argv)
{
	env->num_of_ph = ft_atoi(argv[1]);
	env->time_to_die = ft_atoi(argv[2]);
	env->time_to_eat = ft_atoi(argv[3]);
	env->time_to_sleep = ft_atoi(argv[4]);
	env->is_finished = 0;
	if (argc == 6)
		env->number_of_must_eat = ft_atoi(argv[5]);
	else
		env->number_of_must_eat = -1;
	env->start_thread_time = ft_get_time(0) / 1000;
}
