/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelacou <hdelacou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 22:44:57 by hdelacou          #+#    #+#             */
/*   Updated: 2025/03/08 22:53:55 by hdelacou         ###   ########.fr       */
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
		rules->number_of_meal = ft_atol(argv[5]);
		if (rules->number_of_meal < 0)
		{
			error_manager(2);
			rules->check++;
		}
	}
	else
		rules->number_of_meal = -1;
	rules->start_time = get_timestamp();
	return (rules);
}

int	exit_print(char *message)
{
	printf("%s\n", message);
	return (EXIT_FAILURE);
}

t_rules	*init_semaphore(t_rules *rules)
{
	rules->philo = malloc(sizeof(t_philo) * (rules->nb_philo + 1));
	if (!rules->philo)
	{
		error_manager(9);
		return (NULL);
	}
	sem_unlink("/write");
	rules->write_lock = sem_open("/write", O_CREAT, 0755, 1);
	sem_unlink("/dead");
	rules->dead_lock = sem_open("/dead", O_CREAT, 0755, 1);
	sem_unlink("/state");
	rules->state_lock = sem_open("/state", O_CREAT, 0755, 1);
	sem_unlink("/fork");
	rules->fork = sem_open("/fork", O_CREAT, 0755, rules->nb_philo);
	if (rules->fork == SEM_FAILED || rules->state_lock == SEM_FAILED
		|| rules->dead_lock == SEM_FAILED || rules->write_lock == SEM_FAILED)
		exit (error_manager(3));
	return (rules);
}

void	init_philo(t_rules *rules)
{
	int	i;

	i = 0;
	rules = init_semaphore(rules);
	while (i < rules->nb_philo)
	{
		rules->philo[i].id = i + 1;
		rules->philo[i].time_eaten = 0;
		rules->philo[i].last_meal = get_timestamp();
		rules->philo[i].rules = rules;
		i++;
	}
}
