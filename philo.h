/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rares <rares@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/01 18:11:27 by rares         #+#    #+#                 */
/*   Updated: 2023/06/06 17:13:01 by raanghel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include<stdio.h>
# include<stdbool.h>
# include<unistd.h>
# include<string.h>
# include<stdlib.h>
# include<sys/time.h>
# include<stdlib.h>
# include<pthread.h>


//-------STRUCTS-------//

typedef	struct			s_philo
{	
	int					n;
	int					ms;
	bool				is_eating;
	long int			time_last_meal;
	pthread_t			thread;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	struct s_data		*data;

}						t_philo;

typedef	struct			s_data
{
	int					nr_philo;
	int					die_time;
	int					eat_time;
	int					sleep_time;
	long int			start_time;
	t_philo				*philo;
	pthread_mutex_t 	*forks;
	
}						t_data;

//-------UTILS-------//

void			raise_error(char *message);
int				ft_atoi(const char *str);
int				check_digit(char *str);




//-------INITIALIZE-------//

int			initialize_data(t_data *data, char **argv);


//-------STRUCTS-------//
//-------STRUCTS-------//



#endif