/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelacou <hdelacou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 20:03:36 by hdelacou          #+#    #+#             */
/*   Updated: 2025/03/08 20:51:25 by hdelacou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	write_error(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	write(2, BOLD "Error: ", 12);
	write(2, str, len);
	write(2, RESET ".\n", 7);
	return (1);
}

void	print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->rules->write_lock);
	if ((!alive_state(philo) || !all_alive(philo)) && ft_strcmp(status, DIE))
	{
		pthread_mutex_unlock(&philo->rules->write_lock);
		return ;
	}
	printf(RESET BOLD "%5lli ", get_timestamp() - philo->rules->start_time);
	printf("%3i" RESET, philo->id);
	printf("%s\n", status);
	pthread_mutex_unlock(&philo->rules->write_lock);
}

int	error_manager(int error)
{
	if (error == 0)
		return (write_error("Wrong number of argument"));
	if (error == 1)
		return (write_error("At least one wrong argument"));
	if (error == 2)
		return (write_error("At least one rule is not valid"));
	if (error == 3)
		return (write_error("Fatal error when intializing mutex"));
	if (error == 4)
		return (write_error("Error while getting actual time"));
	if (error == 5)
		return (write_error("Do no test with more than 200 philo"));
	if (error == 6)
		return (write_error("Error while joining thread"));
	if (error == 7)
		return (write_error("One argument contain non numeric parameter"));
	if (error == 8)
		return (write_error("Error while initing philo thread"));
	if (error == 9)
		return (write_error("Error with a malloc function"));
	return (1);
}
