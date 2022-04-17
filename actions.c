/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoteo-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:37:12 by aoteo-be          #+#    #+#             */
/*   Updated: 2022/01/21 13:58:40 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"

int	forking(t_philo *phi)
{
//	if (*phi->r_fork != phi->id || *phi->l_fork != phi->id)
//	{
		while (*phi->r_fork != 0)
		{
			if (times() - phi->last_meal >= phi->com->time_to_die)
			{
				phi->com->ending = 1;
				return (0);
			}
		}
		pthread_mutex_lock(&phi->m_fork);
		*phi->r_fork = phi->id;
		while (*phi->l_fork != 0)
		{
			if (times() - phi->last_meal >= phi->com->time_to_die)
			{
				phi->com->ending = 1;
				return (0);
			}
		}
		pthread_mutex_lock(&(phi->prev_phi->m_fork));
		*phi->l_fork = phi->id;
		print_status(0, times() - phi->com->begin, *phi);
//	}
	return (1);
}

int	eating(t_philo *phi)
{
	print_status(1, times() - phi->com->begin, *phi);
	phi->last_meal = times();
	if (phi->times_must_eat > -1)
	{
		phi->times_must_eat--;
		phi->com->repeat++;
	}
	ft_sleep(phi->com->time_to_eat, phi);
	*phi->r_fork = 0;
	pthread_mutex_unlock(&phi->m_fork);
	*phi->l_fork = 0;
	pthread_mutex_unlock(&phi->prev_phi->m_fork);
	return (1);
}

int	sleep_think(t_philo *phi)
{
	print_status(2, times() - phi->com->begin, *phi);
	ft_sleep(phi->com->time_to_sleep, phi);
	print_status(3, times() - phi->com->begin, *phi);
	return (1);
}
