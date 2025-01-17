/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelacou <hdelacou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 20:03:36 by hdelacou          #+#    #+#             */
/*   Updated: 2025/01/17 20:49:16 by hdelacou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	write_error(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	write(2, "Error: ", 7);
	write(2, str, len);
	write(2, "\n", 1);
	return (1);
}

int	error_manager(int error)
{
	if (error == 1)
		return (write_error("At least one wrong argument"));
	if (error == 2)
		return (write_error("Fatal error when intializing mutex"));
	return (1);
}

void	action_print(t_rules *rules, int id, char *string)
{
	pthread_mutex_lock(&(rules->writing));
	if (!(rules->dieded))
	{
		printf(RESET BOLD "%5lli ", timestamp() - rules->first_timestamp);
		printf("%3i " RESET, id + 1);
		printf("%s\n", string);
	}
	pthread_mutex_unlock(&(rules->writing));
	return ;
}
