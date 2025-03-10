/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelacou <hdelacou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 22:38:43 by hdelacou          #+#    #+#             */
/*   Updated: 2025/03/08 22:38:44 by hdelacou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_rules	*is_valid_arg(char **argv)
{
	t_rules	*rules;

	rules = malloc(sizeof(t_rules));
	if (!rules)
	{
		error_manager(9);
		return (NULL);
	}
	rules->check = 0;
	rules = only_digit_arg(rules, argv);
	return (rules);
}

t_rules	*init_rules(int argc, char **argv)
{
	t_rules	*rules;

	rules = is_valid_arg(argv);
	rules->nb_philo = ft_atol(argv[1]);
	if (rules->nb_philo > 200)
	{
		rules->check++;
		error_manager(5);
	}
	rules->time_to_die = ft_atol(argv[2]);
	rules->time_to_eat = ft_atol(argv[3]);
	rules->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
	{
		rules->nb_of_meal = ft_atol(argv[5]);
		if (rules->nb_of_meal < 0)
		{
			error_manager(2);
			rules->check++;
		}
	}
	else
		rules->nb_of_meal = -1;
	rules->start_time = get_timestamp();
	return (rules);
}

t_rules	*init_mutex(t_rules *rules)
{
	rules->philo = malloc(sizeof(t_philo) * (rules->nb_philo + 1));
	if (!rules->philo)
	{
		error_manager(9);
		return (NULL);
	}
	if (pthread_mutex_init(&rules->write_lock, NULL) != 0
		|| pthread_mutex_init(&rules->dead_lock, NULL) != 0
		|| pthread_mutex_init(&rules->state_lock, NULL) != 0)
	{
		error_manager(3);
		return (NULL);
	}
	return (rules);
}

pthread_mutex_t	**init_forks(int nb_philo)
{
	int				i;
	pthread_mutex_t	**fork;

	fork = malloc(sizeof(pthread_mutex_t *) * (nb_philo + 1));
	i = 0;
	while (i < nb_philo)
	{
		fork[i] = malloc(sizeof(pthread_mutex_t));
		if (pthread_mutex_init(fork[i], NULL) != 0)
		{
			while (i != 0)
			{
				pthread_mutex_destroy(fork[i]);
				i--;
			}
			error_manager(3);
			return (NULL);
		}
		i++;
	}
	return (fork);
}

void	init_philo(pthread_mutex_t **fork, t_rules *rules)
{
	int	i;

	i = 0;
	rules = init_mutex(rules);
	while (i < rules->nb_philo)
	{
		rules->philo[i].is_dead = &rules->is_dead;
		rules->philo[i].first_dead = &rules->first_dead;
		rules->philo[i].id = i + 1;
		rules->philo[i].x_ate = 0;
		rules->philo[i].last_meal = get_timestamp();
		rules->philo[i].left_fork = fork[i];
		if (i == 0)
			rules->philo[i].right_fork = fork[rules->nb_philo - 1];
		else
			rules->philo[i].right_fork = fork[i - 1];
		rules->philo[i].rules = rules;
		i++;
	}
}
