/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoteo-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:37:12 by aoteo-be          #+#    #+#             */
/*   Updated: 2022/01/21 13:58:40 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"

static void	*actions(void *philosophers)
{
	t_philo	*phi;

	phi = (t_philo *) philosophers;
	while (phi->times_must_eat != 0 && phi->com->ending == 0
		&& phi->com->repeat != phi->com->diners * phi->com->rations)
	{
		if (forking(phi) == 0)
			break ;
		if (eating(phi) == 0)
			break ;
		if (sleep_think(phi) == 0)
			break ;
	}
	return (NULL);
}

static void	init_phi(t_input *input, t_philo *phi, int *forks)
{
	int	i;

	i = 0;
	while (i < input->diners)
	{
		phi[i].id = i + 1;
		phi[i].com = input;
		phi[i].last_meal = phi[i].com->begin;
		phi[i].times_must_eat = phi[i].com->rations;
		phi[i].r_fork = &forks[i];
		if (i == 0)
		{
			phi[i].l_fork = &forks[input->diners - 1];
			phi[i].prev_phi = &phi[input->diners - 1];
		}
		else
		{
			phi[i].l_fork = &forks[i - 1];
			phi[i].prev_phi = &phi[i - 1];
		}
		pthread_mutex_init(&phi[i].m_fork, NULL);
		i++;
	}
}

void	main_loop(t_input *input, t_philo	*phi,	pthread_t	*list)
{
	int	i;

	while (1)
	{
		if (input->repeat == input->rations * input->diners || input->ending)
		{
			if (input->repeat != input->rations * input->diners)
				print_status(4, times() - input->begin, phi[i], input->ending);
			input->ending = 1;
			break ;
		}
		else
		{
			i = -1;
			while (++i < phi->com->diners && phi->com->ending == 0)
				pthread_join(list[i], NULL);
		}
		pthread_mutex_unlock(&input->m_death);
	}
}

void	thread_management(t_input *input, t_philo *phi,	pthread_t *list)
{
	pthread_mutex_lock(&input->m_death);
	if (input->diners == 1)
	{
		print_status(0, times() - phi->com->begin, *phi, phi->id);
		ft_sleep(input->time_to_die, phi);
		print_status(4, times() - phi->com->begin, *phi, phi->id);
		return ;
	}
	main_loop(input, phi, list);
}

int	main(int argc, char *argv[])
{
	int			i;
	int			*forks;
	pthread_t	*list;
	t_input		*input;
	t_philo		*phi;

	input = (t_input *)(malloc(sizeof(t_input)));
	if (input == NULL || parse_input(argc, argv, input))
		return (-1);
	list = malloc(input->diners * sizeof(pthread_t));
	forks = malloc(input->diners * sizeof(int));
	phi = malloc(input->diners * sizeof(t_philo));
	if (manage_memory(phi, list, forks, input->diners) != 0)
		return (-1);
	init_phi(input, phi, forks);
	i = -1;
	while (++i < input->diners && input->ending == 0)
		pthread_create(&list[i], NULL, actions, (void *) &phi[i]);
	if (input->repeat == input->rations * input->diners)
		return (0);
	thread_management(input, phi, list);
	return (free_all(phi, list, forks, input));
}
