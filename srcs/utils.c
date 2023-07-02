/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobushi <mobushi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 19:04:46 by mobushi           #+#    #+#             */
/*   Updated: 2023/07/02 19:48:35 by mobushi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

int	ft_usleep(long long time)
{
	long long	start;

	start = ft_get_time(0);
	while ((ft_get_time(0) - start) < time)
		usleep(200);
	return (0);
}

long long	ft_get_time(long long input)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (((tv.tv_sec * 1000000) + tv.tv_usec) - input);
}
