/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize_philo.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: raanghel <raanghel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 12:51:21 by raanghel      #+#    #+#                 */
/*   Updated: 2023/08/13 19:55:14 by rares         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"	

int	check_args(char **argv)
{
	if (check_digit(argv[1]) == 1
		|| check_digit(argv[2]) == 1
		|| check_digit(argv[3]) == 1
		|| check_digit(argv[4]) == 1)
	{
		return (1);
	}
	return (0);
}

int	check_positive_argv(char **argv)
{
	if (argv[1][0] == '-'
		|| argv[2][0] == '-'
		|| argv[3][0] == '-'
		|| argv[4][0] == '-')
	{
		return (1);
	}
	return (0);
}

int	check_int_overflow(char **argv)
{
	if (ft_atoi(argv[1]) == -1
		|| ft_atoi(argv[2]) == -1
		|| ft_atoi(argv[3]) == -1
		|| ft_atoi(argv[4]) == -1)
	{
		return (1);
	}
	return (0);
}

int	check_data(char **argv)
{
	if (check_args(argv) == 1)
	{
		printf("Program arguments should only contain digits\n");
		return(1);
	}
	if (check_positive_argv(argv) == 1)
	{
		printf("Program arguments should be positive\n");
		return(1);
	}
	if (check_int_overflow(argv) == 1)
	{
		printf("Program arg exceeds MAX_INT\n");
		return(1);
	}
	return (0);
}

int	initialize_data(t_data *data, char **argv)
{
	if (check_data(argv) == 1)
	{
		printf("Invalid arguments.\n");
		return (1);
	}
	data->nr_philo = ft_atoi(argv[1]);
	data->die_time = ft_atoi(argv[2]);
	data->eat_time = ft_atoi(argv[3]);
	data->sleep_time = ft_atoi(argv[4]);
	data->start_time = 0;
	//data->counter = 1;
	return (0);
}

// static void	*routine(void *philos)
// {
// 	//usleep(50);
// 	//printf("--DB--\n");
// 	t_data	*data;
// 	t_philo	*philo;
// 	int		i;
// 	//printf("1\n");
// 	philo = (t_philo *) philos;
// 	i = philo->pos;
// 	data = philo->data;
// 	pthread_mutex_lock(&philo->data->forks[0]);
// 	if (i != data->counter)
// 	{
// 		pthread_mutex_unlock(&philo->data->forks[0]);
// 		pthread_mutex_lock(&philo->data->forks[0]);
// 	}
// 	printf("%d ", i);
// 	data->counter++;
// 	pthread_mutex_unlock(&philo->data->forks[0]);
// 	return (NULL);
// }
// void	take_left_fork(t_data *data, int fork_nr, int philo_nr)
// {
// 	pthread_mutex_lock(&data->forks[philos[fork_nr].left_fork]);
// }
// void	take_left_fork(int fork_nr, int philo_nr)
// {
// }
// void	start_eating


// void	eat_action(t_data *data, int i)
// {
// 	pthread_mutex_lock(&data->forks[philos[i - 1].right_fork]);
// 	printf("Philo %d took right_fork (%d)\n", i, data->philos[i - 1].right_fork + 1);
		
// 	pthread_mutex_lock(&data->forks[philos[i - 1].left_fork]);	
// 	printf("Philo %d took left_fork (%d)\n", i, data->philos[i - 1].left_fork + 1);
		
		
// 		//pthread_mutex_lock(&data->eating);
// 	printf("Philo %d is eating...\n\n", i);
// 	usleep(rand() % 1000000);
// 	sleep(1);
// 		//pthread_mutex_unlock(&data->eating);
		
// 	pthread_mutex_unlock(&data->forks[philos[i - 1].left_fork]);
// 	printf("Philo %d released left_fork (%d)\n", i, data->philos[i - 1].left_fork + 1);
		
// 	pthread_mutex_unlock(&data->forks[philos[i - 1].right_fork]);
// 	printf("Philo %d released right_fork (%d)\n", i, data->philos[i - 1].right_fork + 1);
// }

static void	*routine(void *philo_pt)
{
	t_philo		*philo;
	//t_data		*data;

	//usleep(1000);
	philo = (t_philo *) philo_pt;
	//data = philos->data;
	if (philo->pos % 2 == 0)
		own_usleep(philo, 10);
	// pthread_mutex_lock(&data->eating);

	// usleep(30);
	// printf("I am philo %d\n", i);
	
	// pthread_mutex_unlock(&data->eating);
	while (philo->is_dead == false)
	{	
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		output_message(philo, FORK_R);
		
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		output_message(philo, FORK_L);
		
		//pthread_mutex_lock(&data->eating);
		output_message(philo, EAT);
		own_usleep(philo, philo->data->eat_time);
		//sleep(1);
		//pthread_mutex_unlock(&data->eating);
		
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
		output_message(philo, RLS_FORK_L);
		
		pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
		output_message(philo, RLS_FORK_R);

		
		output_message(philo, SLEEP);
		own_usleep(philo, philo->data->sleep_time);
		
		output_message(philo, THINK);		
	}
	return (NULL);
}

int	initialize_philo_data(t_data *data)
{
	int			i;
	
	//data->start_time = current_time();
	if (data->start_time == -1)
		return (1);
	data->philos = malloc(data->nr_philo * sizeof(t_philo));
	if (data->philos == NULL)
		return (1);
	i = 0;
	while (i < data->nr_philo)
	{
		data->philos[i].is_eating = false;
		data->philos[i].is_dead = false;
		data->philos[i].eat_rounds = 0;
		data->philos[i].pos = i + 1;
		data->philos[i].ms = 0;
		data->philos[i].time_last_meal = 0;
		data->philos[i].data = data;
		data->philos[i].left_fork = i;
		if (i == 0)
			data->philos[i].right_fork = data->nr_philo - 1;
		else	
			data->philos[i].right_fork = i - 1;
		//data->philos[i].right_fork = (i + 1) % data->nr_philo;
		i++;
	}
	return (0);
}

int	create_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nr_philo)
	{
		if (pthread_create(&data->philos[i].thread_id, NULL, &routine,
				&data->philos[i]) != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < data->nr_philo)
	{
		if (pthread_join(data->philos[i].thread_id, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
	
}

int	initialize_forks(t_data *data)
{
	int	i;
	
	if (pthread_mutex_init(&data->eating, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->printing, NULL) != 0)
		return (1);
	data->forks = malloc(data->nr_philo * sizeof(pthread_mutex_t));
	if (data->forks == NULL)
		return (1);
	i = 0;
	while (i < data->nr_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	destroy_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nr_philo)
	{
		if (pthread_mutex_destroy(&data->forks[i]) != 0)
			return (1);
		i++;
	}
	if (pthread_mutex_destroy(&data->eating) != 0)
			return (1);
	return (0);
}
