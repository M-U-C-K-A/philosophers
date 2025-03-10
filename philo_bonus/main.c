/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelacou <hdelacou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 22:42:16 by hdelacou          #+#    #+#             */
/*   Updated: 2025/03/10 17:20:39 by hdelacou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	smart_sleep(long long time, t_philo *philo, t_rules *rules)
{
	long long	i;

	i = get_timestamp();
	while (alive_state(philo, rules))
	{
		if ((get_timestamp() - i) >= time)
			break ;
		usleep(50);
	}
}

long long	get_timestamp(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "Error while getting actual time\n", 33);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	check_rules(t_rules *rules)
{
	if (rules->nb_philo < 0 || rules->time_to_die < 0
		|| rules->time_to_eat < 0 || rules->time_to_eat < 0
		|| rules->time_to_sleep < 0)
	{
		return (0);
	}
	else
		return (1);
}

void	free_all(t_rules *rules)
{
	sem_close(rules->fork);
	sem_close(rules->dead_lock);
	sem_close(rules->write_lock);
	sem_close(rules->state_lock);
	sem_unlink("/fork");
	sem_unlink("/dead");
	sem_unlink("/write");
	sem_unlink("/state");
	free(rules->wait_philo);
	free(rules->philo);
	free(rules);
}

int	main(int argc, char **argv)
{
	t_rules	*rules;

	if (argc < 5 || argc > 6)
		return (error_manager(0));
	rules = init_rules(argc, argv);
	if (rules->check != 0)
		return (free(rules), 1);
	if (rules->nb_philo > 0)
	{
		rules->wait_philo = malloc(sizeof(pid_t) * (rules->nb_philo));
		if (!rules->wait_philo)
			return (free(rules), 1);
	}
	if (check_rules(rules) == 0)
	{
		if (rules->wait_philo)
			free(rules->wait_philo);
		return (error_manager(2), free(rules), 1);
	}
	init_philo(rules);
	if (!rules)
		exit (EXIT_FAILURE);
	create_philo(rules);
	free_all(rules);
	return (0);
}
