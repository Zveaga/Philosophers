/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rares <rares@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/01 18:11:27 by rares         #+#    #+#                 */
/*   Updated: 2023/08/10 20:19:36 by rares         ########   odam.nl         */
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
	bool				is_eating;
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
	int					nr_philo;
	int					eat_rounds;
	int					die_time;
	int					eat_time;
	int					sleep_time;
	long int			start_time;
	t_philo				*philos;
	pthread_mutex_t 	*forks;
	pthread_mutex_t		eating;
}						t_data;

//-------UTILS-------//

void				raise_error(char *message);
int					ft_atoi(const char *str);
int					check_digit(char *str);
int					ft_strlen(const char *s);
long int			curret_time(void);



//-------INITIALIZE-------//

int					initialize_data(t_data *data, char **argv);
int					initialize_philo(t_data *data);
int					initialize_forks(t_data *data);


//-------FREE-------//
int					destroy_mutex(t_data *data);
//-------STRUCTS-------//



#endif