/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelacou <hdelacou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 22:25:36 by hdelacou          #+#    #+#             */
/*   Updated: 2025/01/17 20:58:20 by hdelacou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
// Philosophers with threads and mutexes

#define BOLD	"\e[1m"
#define RESET	"\e[0m"
#define EAT		"\e[38;2;5;165;135m\t🍏 is eating "
#define THINK	"\e[38;2;240;200;50m\t🤔 is thinking  "
#define SLEEP	"\e[38;2;70;160;240m\t💤 is sleeping  "
#define FORK	"\e[38;2;190;190;190m\t🍴 has taken a fork"
#define DIE		"\e[38;2;255;0;0;1m\t🔥 died\n"

struct	s_rules;
struct	s_philosopher;

/**
 * @brief Structure representing a philosopher.
 * - @id: 				Unique id of the philosopher.
 * - @x_ate: 			Number of meals eaten.
 * - @left_fork_id: 	Id of the left fork.
 * - @right_fork_id: 	Id of the right fork.
 * - @t_last_meal: 		Timestamp of the last meal.
 * - @rules: 			Pointer to the simulation rules.
 * - @thread_id: 		Thread id for the philosopher.
 */
typedef struct s_philosopher
{
	int				id;
	int				x_ate;
	int				left_fork_id;
	int				right_fork_id;
	long long		t_last_meal;
	struct s_rules	*rules;
	pthread_t		thread_id;
}					t_philosopher;

/**
 * @brief Simulation rules.
 * - @nb_philo:         Number of philosophers.
 * - @time_death:       Time in ms before a philosopher dies.
 * - @time_eat:         Time in ms a philosopher eats.
 * - @time_sleep:       Time in ms a philosopher sleeps.
 * - @nb_eat:           -1 for infinite, else times to eat.
 * - @dieded:           Boolean if a philosopher has died.
 * - @first_timestamp:  Start timestamp of the simulation.
 * - @meal_check:       Semaphore for meal check.
 * - @forks:            Array of semaphores for forks.
 * - @writing:          Semaphore for writing to stdout.
 * - @philosophers:     Array of philosophers.
 */
typedef struct s_rules
{
	int					nb_philo;
	int					time_death;
	int					time_eat;
	int					time_sleep;
	int					nb_eat;
	int					dieded;
	int					all_ate;
	long long			first_timestamp;
	pthread_mutex_t		meal_check;
	pthread_mutex_t		forks[250];
	pthread_mutex_t		writing;
	t_philosopher		philosophers[250];
}					t_rules;

//		src/main.c
int			main(int argc, char **argv);
int			init_philosophers(t_rules *rules);
int			init_all(t_rules *rules, char **argv);
int			init_mutex(t_rules *rules);

//		src/message.c
int			write_error(char *str);
int			error_manager(int error);
void		action_print(t_rules *rules, int id, char *string);

//		src/philo.c
void		philo_eats(t_philosopher *philo);
void		p_process(void *void_phil);
void		exit_launcher(t_rules *rules, t_philosopher *philos);
void		death_checker(t_rules *r, t_philosopher *p);
int			launcher(t_rules *rules);

//		src/utils.c
int			ft_atoi(const char *str);
long long	timestamp(void);
void		smart_sleep(long long time, t_rules *rules);
