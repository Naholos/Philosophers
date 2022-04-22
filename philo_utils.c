/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoteo-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 13:06:03 by aoteo-be          #+#    #+#             */
/*   Updated: 2022/04/21 16:39:28 by aoteo-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"

int	free_all(t_philo *phi, pthread_t *list, int *forks, t_input *input)
{
	int	i;

	i = -1;
	while (++i < phi->com->diners)
		pthread_mutex_destroy(&phi->m_fork);
	pthread_mutex_destroy(&phi->com->m_print);
	pthread_mutex_destroy(&phi->com->m_print);
	free(input);
	free(list);
	free(forks);
	free(phi);
	return (0);
}

void	ft_sleep(size_t waiting_time, t_philo *phi)
{
	size_t	time;

	time = times();
	while (phi->com->ending != 1)
	{
		if (times() - time >= waiting_time)
			break ;
		usleep(100);
	}
}

int	manage_memory(t_philo *phi, pthread_t *list, int *forks, int number)
{
	if (phi != NULL && list != NULL && forks != NULL)
	{
		memset(forks, 0, number * sizeof(int));
		return (0);
	}
	if (phi == NULL)
		free(phi);
	if (list == NULL)
		free(list);
	if (forks == NULL)
		free(forks);
	return (1);
}

void	print_status(int st, size_t time, t_philo phi, int id)
{
	pthread_mutex_lock(&phi.com->m_print);
	if (st == 0)
	{
		printf("\x1b[36m""%lu ms, %d has taken a fork.\n", time, phi.id);
		if (phi.com->diners > 1)
			printf("\x1b[36m""%lu ms, %d has taken a fork.\n", time, phi.id);
	}
	else if (st == 1)
		printf("\x1b[32m""%lu ms, %d is eating.\n", time, phi.id);
	else if (st == 2 && phi.com->repeat != phi.com->diners * phi.com->rations)
		printf("\x1b[33m""%lu ms, %d is sleeping.\n", time, phi.id);
	else if (st == 3 && phi.com->repeat != phi.com->diners * phi.com->rations)
		printf("\x1b[34m""%lu ms, %d is thinking.\n", time, phi.id);
	else if (st == 4 && phi.com->repeat != phi.com->diners * phi.com->rations)
		printf("\x1b[31m""%lu ms, %d has died.\n", time, id);
	if (st != 4)
		pthread_mutex_unlock(&phi.com->m_print);
}

size_t	times(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((size_t)(current_time.tv_sec * 1000 + current_time.tv_usec / 1000));
}
