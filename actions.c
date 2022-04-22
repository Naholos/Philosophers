/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoteo-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:37:12 by aoteo-be          #+#    #+#             */
/*   Updated: 2022/04/21 17:21:02 by aoteo-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"

int	clean_input(t_input *input)
{
	if (input->diners == 0)
	{
		free (input);
		return (0);
	}
	return (1);
}

int	forking(t_philo *phi)
{
	if (phi->id % 2 == 0 /*|| (phi->id % 2 == 1 && phi->id == phi->com->diners)*/)
	{
		usleep(500);
		if (times() - phi->last_meal >= phi->com->time_to_die)
		{
			phi->com->ending = phi->id;
			return (0);
		}
	}
	while (*phi->r_fork != 0)
	{
		if (times() - phi->last_meal >= phi->com->time_to_die)
		{
			phi->com->ending = phi->id;
			return (0);
		}
	}
	pthread_mutex_lock(&phi->m_fork);
	*phi->r_fork = phi->id;
	pthread_mutex_lock(&(phi->prev_phi->m_fork));
	*phi->l_fork = phi->id;
	print_status(0, times() - phi->com->begin, *phi, phi->id);
	return (1);
}

int	eating(t_philo *phi)
{
	if (times() - phi->last_meal >= phi->com->time_to_die)
	{
		phi->com->ending = phi->id;
		return (0);
	}
	print_status(1, times() - phi->com->begin, *phi, phi->id);
	phi->last_meal = times();
	if (phi->times_must_eat > -1)
	{
		phi->times_must_eat--;
		phi->com->repeat++;
		if (phi->com->repeat == phi->com->diners * phi->com->rations)
			phi->com->ending = 1;
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
	if (times() - phi->last_meal >= phi->com->time_to_die)
	{
		phi->com->ending = phi->id;
		return (0);
	}
	print_status(2, times() - phi->com->begin, *phi, phi->id);
	ft_sleep(phi->com->time_to_sleep, phi);
	if (times() - phi->last_meal >= phi->com->time_to_die)
	{
		phi->com->ending = phi->id;
		return (0);
	}
	print_status(3, times() - phi->com->begin, *phi, phi->id);
	if (times() - phi->last_meal >= phi->com->time_to_die)
	{
		phi->com->ending = phi->id;
		return (0);
	}
	return (1);
}
