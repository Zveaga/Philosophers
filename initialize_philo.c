/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize_philo.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: raanghel <raanghel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 12:51:21 by raanghel      #+#    #+#                 */
/*   Updated: 2023/06/22 21:50:23 by rares         ########   odam.nl         */
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

static void	*routine(void *philo_pt)
{
	t_philo		*philos;
	t_data		*data;
	int			i;

	//usleep(1000);
	philos = (t_philo *) philo_pt;
	data = philos->data;
	i = philos->pos;
	
	
	//if (data->philos[i - 1].is_eating == false)
	// {	
		pthread_mutex_lock(&data->start_mutex);
		
		if (i % 2 == 0)
		{	
			
			pthread_mutex_lock(&data->forks[philos[i - 1].left_fork]);	
			pfffffrrrrrrintf("Philo %d took left_fork (%d)\n", i, data->philos[i - 1].left_fork + 1);
			
			pthread_mutex_lock(&data->forks[philos[i - 1].right_fork]);
			printf("Philo %d took right_fork (%d)\n", i, data->philos[i - 1].right_fork + 1);
			
			//pthread_mutex_lock(&data->start_mutex);
			printf("Philo %d is eating...\n\n", i);
			usleep(2000);
			data->philos[i - 1].is_eating = true;
			
			//pthread_mutex_unlock(&data->start_mutex);
			
			pthread_mutex_unlock(&data->forks[philos[i - 1].left_fork]);
			printf("Philo %d released left_fork (%d)\n", i, data->philos[i - 1].left_fork + 1);
			
			pthread_mutex_unlock(&data->forks[philos[i - 1].right_fork]);
			printf("Philo %d released right_fork (%d)\n", i, data->philos[i - 1].right_fork + 1);

			pthread_mutex_unlock(&data->start_mutex);
			usleep(1000);
			//data->philos[i - 1].is_eating = false;
			
		}
	// 	else
	// 		return (NULL);
	// // }
	// else
	// 	return (NULL);
		//printf("Thread waiting...\n");
	//pthread_mutex_unlock(&data->start_mutex);
	//pthread_mutex_lock(&philo->data->forks[0]);
	
	//printf("%d ", i);
	//pthread_mutex_unlock(&philo->data->forks[0]);
	
	return (NULL);
}

int	initialize_philo(t_data *data)
{
	int			i;
	
	data->start_time = curret_time();
	//printf("\nStart time: %ld\n\n", data->start_time);
	if (data->start_time == -1)
		return (1);
	data->philos = malloc(data->nr_philo * sizeof(t_philo));
	if (data->philos == NULL)
		return (1);
	//printf("1\n");
	i = 0;
	while (i < data->nr_philo)
	{
		//printf("3\n");
		if (pthread_create(&data->philos[i].thread_id, NULL, &routine, &data->philos[i]) != 0)
			return (1);
		data->philos[i].is_eating = false;
		data->philos[i].pos = i + 1;
		data->philos[i].ms = 0;
		data->philos[i].time_last_meal = 0;
		data->philos[i].data = data;
		data->philos[i].left_fork = i;
		if (i == 0)
			data->philos[i].right_fork = data->nr_philo - 1;
		else	
			data->philos[i].right_fork = i - 1;
		i++;
	}
	
	//printf("2\n");
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
	if (pthread_mutex_init(&data->start_mutex, NULL) != 0)
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
	// data.start_mutex = malloc(sizeof(pthread_mutex_t));
	// if (data.start_mutex == NULL)
	// 	return(1);
	
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
	if (pthread_mutex_destroy(&data->start_mutex) != 0)
			return (1);
	return (0);
}
