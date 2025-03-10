/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelacou <hdelacou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 22:38:38 by hdelacou          #+#    #+#             */
/*   Updated: 2025/03/08 22:38:39 by hdelacou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_rules(t_rules *rules)
{
	return (rules->nb_philo >= 0
		&& rules->time_to_die >= 0
		&& rules->time_to_eat >= 0
		&& rules->time_to_sleep >= 0);
}

void	free_all(pthread_mutex_t **fork, t_rules *rules)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&rules->write_lock);
	pthread_mutex_destroy(&rules->dead_lock);
	pthread_mutex_destroy(&rules->state_lock);
	while (i < rules->nb_philo)
	{
		pthread_mutex_destroy(fork[i]);
		free(fork[i]);
		i++;
	}
	free(rules->philo);
	free(rules);
	free(fork);
}

int	main(int argc, char **argv)
{
	t_rules				*rules;
	pthread_mutex_t		**fork;

	if (argc < 5 || argc > 6)
		return (error_manager(0));
	rules = init_rules(argc, argv);
	rules->is_dead = 0;
	rules->first_dead = 0;
	if (rules->check != 0)
		return (free(rules), 1);
	if (check_rules(rules) == 0)
	{
		free(rules);
		return (error_manager(2));
	}
	fork = init_forks(rules->nb_philo);
	init_philo(fork, rules);
	create_thread(fork, rules);
	free_all(fork, rules);
	return (0);
}
