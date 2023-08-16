/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rares <rares@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/01 18:11:27 by rares         #+#    #+#                 */
/*   Updated: 2023/08/16 17:51:43 by raanghel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

//-------LIBRARIES-------//
# include<stdio.h>
# include<stdbool.h>
# include<unistd.h>
# include<string.h>
# include<stdlib.h>
# include<sys/time.h>
# include<stdlib.h>
# include<pthread.h>


//-------PRINTF COLORS-------//
#define RESET	"\x1B[0m"
#define RED		"\x1B[31m"
#define GREEN	"\x1B[32m"
#define YELLOW	"\x1B[33m"
#define BLUE    "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN    "\x1B[36m"


//-------STRUCTS-------//
typedef enum			s_activity
{
	EAT,
	SLEEP,
	THINK,
	FORK_R,
	FORK_L,
	RLS_FORK_L,
	RLS_FORK_R,
	DEAD,
}						t_activity;
						
typedef	struct			s_philo
{
	bool				is_eating;
	bool				fully_ate;
	int					eat_rounds;
	int					pos;
	int					ms;
	int					left_fork;
	int					right_fork;
	long int			time_last_meal;
	pthread_t			thread_id;
	struct s_data		*data;

}						t_philo;

typedef	struct			s_data
{					
	//int					counter;
	bool				philo_alive;
	int					nr_philo;
	int					die_time;
	int					eat_time;
	int					sleep_time;
	int					required_rounds;
	int					completed_rounds;
	long int			start_time;
	t_philo				*philos;
	pthread_mutex_t 	*forks;
	pthread_mutex_t		checking;
	pthread_mutex_t		update_time;
	pthread_mutex_t		printing;
	pthread_mutex_t		stop;
}						t_data;


//-------UTILS-------//
void				raise_error(char *message);
int					ft_atoi(const char *str);
int					check_data(int argc, char **argv);
int					ft_strlen(const char *s);
long int			current_time(void);
void				own_usleep(t_philo *philo, long milliseconds);
void				output_message(t_philo *philo, t_activity activity);
void				update_time_last_meal(t_philo *philo);


//-------INITIALIZE-------//
int					initialize_data(t_data *data, int argc, char **argv);
int					initialize_philo_data(t_data *data);
int					initialize_forks(t_data *data);
int					create_philos(t_data *data);



//-------FREE-------//
int					destroy_mutex(t_data *data);

#endif