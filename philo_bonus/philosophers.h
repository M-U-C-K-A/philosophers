/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelacou <hdelacou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 22:38:15 by hdelacou          #+#    #+#             */
/*   Updated: 2025/03/10 17:19:08 by hdelacou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>
// philosophers with processes and semaphores

#define BOLD "\e[1m"
#define RESET "\e[0m"
#define EAT "\e[38;2;5;165;135m\t🍏 is eating "
#define THINK "\e[38;2;240;200;50m\t🤔 is thinking  "
#define SLEEP "\e[38;2;70;160;240m\t💤 is sleeping  "
#define FORK "\e[38;2;190;190;190m\t🍴 has taken a fork"
#define DIE "\e[38;2;255;0;0;1m\t🔥 died\n"

typedef struct s_rules
{
	int				nb_philo;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				number_of_meal;
	int				check;
	long long		start_time;
	sem_t			*write_lock;
	sem_t			*dead_lock;
	sem_t			*state_lock;
	sem_t			*fork;
	pid_t			*wait_philo;
	struct s_philo	*philo;
}					t_rules;

typedef struct s_philo
{
	int				id;
	int				time_eaten;
	long long		last_meal;
	struct s_rules	*rules;
}					t_philo;

// INIT
t_rules				*is_valid_arg(char **argv);
t_rules				*init_rules(int argc, char **argv);
int					exit_print(char *message);
t_rules				*init_semaphore(t_rules *rules);
void				init_philo(t_rules *rules);

// MAIN
void				smart_sleep(long long time, t_philo *philo, t_rules *rules);
long long			get_timestamp(void);
int					check_rules(t_rules *rules);
void				free_all(t_rules *rules);
int					main(int argc, char **argv);

// MESSAGE
int					write_error(char *str);
int					error_manager(int error);
void				print_status(t_philo *philo, char *status, t_rules *rules);

// PHILO
void				eating(t_philo *philo, t_rules *rules);
void				philo_routine(t_philo *philo, t_rules *rules);
void				end_process(t_rules *rules, pid_t death_check);
void				wait_till_end(t_rules *rules);
void				create_philo(t_rules *rules);

// UTILS
int					alive_state(t_philo *philo, t_rules *rules);
size_t				ft_strlen(const char *s);
long long			ft_atol(const char *ptr);
int					ft_strcmp(char *s1, char *s2);
t_rules				*only_digit_arg(t_rules *rules, char **argv);
