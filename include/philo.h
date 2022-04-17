/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoteo-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:15:38 by aoteo-be          #+#    #+#             */
/*   Updated: 2022/01/21 13:51:59 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <unistd.h>

typedef struct s_input
{
	int				ending;
	int				diners;
	size_t			begin;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	long long		rations;
	long long		repeat;
	pthread_mutex_t	m_print;
	pthread_mutex_t	m_death;
}	t_input;

typedef struct s_philo
{
	int				id;
	int				*l_fork;
	int				*r_fork;
	long long		times_must_eat;
	pthread_mutex_t	m_fork;
	struct s_philo	*prev_phi;
	size_t			last_meal;
	t_input			*com;
}	t_philo;

int		forking(t_philo *phi);
int		eating(t_philo *phi);
int		sleep_think(t_philo *phi);
int		ft_atoi(const char *nptr);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	print_status(int status, size_t time, t_philo phi);
int		free_all(t_philo *phi, pthread_t *list, int *forks, t_input *input);
void	ft_sleep(size_t waiting_time, t_philo *phi);
size_t	times(void);
int		parse_input(int argc, char *argv[], t_input *input);

#endif
