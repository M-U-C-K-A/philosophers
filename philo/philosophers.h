/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelacou <hdelacou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 22:25:36 by hdelacou          #+#    #+#             */
/*   Updated: 2025/03/08 22:35:26 by hdelacou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
// Philosophers with threads and mutexes

#define BOLD "\e[1m"
#define RESET "\e[0m"
#define EAT "\e[38;2;5;165;135m\t🍏 is eating "
#define THINK "\e[38;2;240;200;50m\t🤔 is thinking  "
#define SLEEP "\e[38;2;70;160;240m\t💤 is sleeping  "
#define FORK "\e[38;2;190;190;190m\t🍴 has taken a fork"
#define DIE "\e[38;2;255;0;0;1m\t🔥 died\n"

struct	s_philo;
struct	s_rules;

/**
 * @brief Simulation rules
 * - @nb_philo:			Number of philosophers
 * - @time_to_die:		Time before a philosopher dies
 * - @time_to_eat:		Time a philosopher eats
 * - @time_to_sleep:	Time a philosopher sleeps
 * - @nb_of_meal:		-1 for infinite, else times to eat
 * - @check:			Flag for meal check
 * - @is_dead:			Flag for death status
 * - @first_dead:		Flag for first death
 * - @start_time:		Start timestamp of the simulation
 * - @write_lock:		Semaphore for writing to stdout
 * - @dead_lock:		Semaphore for death check
 * - @state_lock:		Semaphore for state check
 * - @philo:			Array of philosophers
 */
typedef struct s_rules
{
	int				nb_philo;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				nb_of_meal;
	int				check;
	int				is_dead;
	int				first_dead;
	long long		start_time;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	state_lock;
	struct s_philo	*philo;
}					t_rules;

/**
 * @brief Information about a philosopher
 * - @id:				Identifier of the philosopher
 * - @x_ate:			Meals consumed count
 * - @nb_philo:			Number of philosophers
 * - @is_dead:			Flag pointer for death status
 * - @first_dead:		Flag pointer for first death
 * - @last_meal:		Last meal timestamp
 * - @thread:			Philosopher's thread
 * - @left_fork:		Left fork mutex
 * - @right_fork:		Right fork mutex
 * - @rules:			Simulation rules pointer
*/
typedef struct s_philo
{
	int				id;
	int				x_ate;
	int				nb_philo;
	int				*is_dead;
	int				*first_dead;
	long long		last_meal;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_rules	*rules;
}					t_philo;

// init
t_rules				*is_valid_arg(char **argv);
t_rules				*init_rules(int argc, char **argv);
t_rules				*init_mutex(t_rules *rules);
pthread_mutex_t		**init_forks(int nb_philo);
void				init_philo(pthread_mutex_t **fork, t_rules *rules);

// main
int					check_rules(t_rules *rules);
void				free_all(pthread_mutex_t **fork, t_rules *rules);
int					main(int argc, char **argv);

// message
int					write_error(char *str);
int					error_manager(int error);
void				print_status(t_philo *philo, char *status);

// philo
void				eating(t_philo *philo);
void				philo_routine(t_philo *philo);
void				create_thread(pthread_mutex_t **fork, t_rules *rules);
int					all_alive(t_philo *philo);
int					alive_state(t_philo *philo);

// utils
long long			get_timestamp(void);
void				smart_sleep(long long time, t_philo *philo);
long long			ft_atol(const char *ptr);
int					ft_strcmp(char *s1, char *s2);
t_rules				*only_digit_arg(t_rules *rules, char **argv);
