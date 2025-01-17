/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelacou <hdelacou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 20:00:47 by hdelacou          #+#    #+#             */
/*   Updated: 2025/01/17 20:01:12 by hdelacou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

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
		return (write_error("Fatal error when intializing semaphores"));
	return (1);
}

void	action_print(t_rules *rules, int id, char *string)
{
	sem_wait(rules->writing);
	if (!(rules->dieded))
	{
		printf(RESET BOLD "%5lli ", timestamp() - rules->first_timestamp);
		printf("%3i " RESET, id + 1);
		printf("%s\n", string);
	}
	sem_post(rules->writing);
	return ;
}
