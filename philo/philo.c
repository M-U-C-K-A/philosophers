/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelacou <hdelacou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 22:38:26 by hdelacou          #+#    #+#             */
/*   Updated: 2025/03/08 22:38:27 by hdelacou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eating(t_philo *philo)
{
	if (philo->id % 2 == 0)
		pthread_mutex_lock(philo->left_fork);
	else
		pthread_mutex_lock(philo->right_fork);
	print_status(philo, FORK);
	if (philo->rules->nb_philo == 1)
	{
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	if (philo->id % 2 == 0)
		pthread_mutex_lock(philo->right_fork);
	else
		pthread_mutex_lock(philo->left_fork);
	print_status(philo, FORK);
	print_status(philo, EAT);
	philo->last_meal = get_timestamp();
	philo->x_ate++;
	smart_sleep(philo->rules->time_to_eat, philo);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_routine(t_philo *philo)
{
	if (philo->id % 2 == 0)
		usleep(500);
	while (alive_state(philo) && all_alive(philo))
	{
		eating(philo);
		if (philo->rules->nb_philo == 1)
		{
			usleep(philo->rules->time_to_die * 1000);
			break ;
		}
		if (philo->x_ate == philo->rules->nb_of_meal)
			return ;
		print_status(philo, SLEEP);
		smart_sleep(philo->rules->time_to_sleep, philo);
		print_status(philo, THINK);
	}
	pthread_mutex_lock(&philo->rules->dead_lock);
	if (*philo->first_dead == 1)
	{
		pthread_mutex_unlock(&philo->rules->dead_lock);
		return ;
	}
	*philo->first_dead = 1;
	pthread_mutex_unlock(&philo->rules->dead_lock);
	print_status(philo, DIE);
}

void	create_thread(pthread_mutex_t **fork, t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->nb_philo)
	{
		if (pthread_create(&rules->philo[i].thread, NULL, (void *)philo_routine,
				&rules->philo[i]) != 0)
		{
			free_all(fork, rules);
			error_manager(8);
			return ;
		}
		i++;
	}
	i = 0;
	while (i < rules->nb_philo)
	{
		if (pthread_join(rules->philo[i].thread, NULL) != 0)
		{
			error_manager(6);
			return ;
		}
		i++;
	}
}

int	all_alive(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->state_lock);
	if (*philo->is_dead == 1)
	{
		pthread_mutex_unlock(&philo->rules->state_lock);
		return (0);
	}
	else
	{
		pthread_mutex_unlock(&philo->rules->state_lock);
		return (1);
	}
}

int	alive_state(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->state_lock);
	if (((get_timestamp() - philo->last_meal) > philo->rules->time_to_die))
	{
		*philo->is_dead = 1;
		pthread_mutex_unlock(&philo->rules->state_lock);
		return (0);
	}
	pthread_mutex_unlock(&philo->rules->state_lock);
	return (1);
}
