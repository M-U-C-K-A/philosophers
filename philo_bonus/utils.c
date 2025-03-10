/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelacou <hdelacou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:02:03 by hdelacou          #+#    #+#             */
/*   Updated: 2025/03/10 17:24:59 by hdelacou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	alive_state(t_philo *philo, t_rules *rules)
{
	sem_wait(philo->rules->state_lock);
	if (((get_timestamp() - philo->last_meal) > philo->rules->time_to_die))
	{
		sem_post(philo->rules->state_lock);
		free_all(rules);
		exit(EXIT_SUCCESS);
	}
	sem_post(philo->rules->state_lock);
	return (1);
}

size_t	ft_strlen(const char *s)
{
	int	a;

	a = 0;
	while (s[a] != '\0')
		a++;
	return (a);
}

long long	ft_atol(const char *smart_sleep)
{
	int			a;
	long long	convert;
	int			min;

	convert = 0;
	a = 0;
	while ((smart_sleep[a] > 8 && smart_sleep[a] < 14)
		|| (smart_sleep[a] == 32))
		a++;
	min = 0;
	if (smart_sleep[a] == '-' || smart_sleep[a] == '+')
	{
		if (smart_sleep[a] == '-')
			min++;
		a++;
	}
	while (smart_sleep[a] >= '0' && smart_sleep[a] <= '9')
	{
		convert *= 10;
		convert += smart_sleep[a] - '0';
		a++;
	}
	if (min % 2 == 1)
		convert *= -1;
	return (convert);
}

int	ft_strcmp(char *s1, char *s2)
{
	size_t	a;

	a = 0;
	while (s1[a] && s2[a] && s1[a] == s2[a])
		a++;
	return ((unsigned char)s1[a] - (unsigned char)s2[a]);
}

t_rules	*only_digit_arg(t_rules *rules, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if ((argv[i][j] < '0' || argv[i][j] > '9') && argv[i][j] != '-'
				&& argv[i][j] != '+')
			{
				write(2, "One argument contain non numeric parameter.\n", 45);
				rules->check++;
				return (rules);
			}
			j++;
		}
		i++;
	}
	return (rules);
}
