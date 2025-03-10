/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelacou <hdelacou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 22:38:21 by hdelacou          #+#    #+#             */
/*   Updated: 2025/03/08 22:38:22 by hdelacou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	get_timestamp(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		error_manager(3);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	smart_sleep(long long time, t_philo *philo)
{
	long long	i;

	i = get_timestamp();
	while (alive_state(philo) && all_alive(philo))
	{
		if ((get_timestamp() - i) >= time)
			break ;
		usleep(50);
	}
}

long long	ft_atol(const char *ptr)
{
	int			a;
	long long	convert;
	int			min;

	convert = 0;
	a = 0;
	while ((ptr[a] > 8 && ptr[a] < 14) || (ptr[a] == 32))
		a++;
	min = 0;
	if (ptr[a] == '-' || ptr[a] == '+')
	{
		if (ptr[a] == '-')
			min++;
		a++;
	}
	while (ptr[a] >= '0' && ptr[a] <= '9')
	{
		convert *= 10;
		convert += ptr[a] - '0';
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
			if ((argv[i][j] < '0' || argv[i][j] > '9')
				&& argv[i][j] != '-' && argv[i][j] != '+')
			{
				error_manager(7);
				rules->check++;
				return (rules);
			}
			j++;
		}
		i++;
	}
	return (rules);
}
