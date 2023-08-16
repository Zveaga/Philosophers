/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize_philo.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: raanghel <raanghel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 12:51:21 by raanghel      #+#    #+#                 */
/*   Updated: 2023/08/16 18:48:03 by raanghel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"	


static int	take_forks(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->data->forks[philo->right_fork]) != 0)
		return (1);
	output_message(philo, FORK_R);
	if (pthread_mutex_lock(&philo->data->forks[philo->left_fork]) != 0)
		return (1);
	output_message(philo, FORK_L);
	return (0);
}

static int	return_forks(t_philo *philo)
{
	if (pthread_mutex_unlock(&philo->data->forks[philo->left_fork]) != 0)
		return (1);
	output_message(philo, RLS_FORK_L);
	if (pthread_mutex_unlock(&philo->data->forks[philo->right_fork]) != 0)
		return (1);
	output_message(philo, RLS_FORK_R);
	
	return (0);
}

static void	eat(t_philo *philo)
{
	update_time_last_meal(philo);
	pthread_mutex_lock(&philo->data->stop);
	output_message(philo, EAT);
	philo->eat_rounds++;
	if (philo->eat_rounds == philo->data->required_rounds)
	{
		philo->data->completed_rounds++;	
		philo->fully_ate = true;
	}
	pthread_mutex_unlock(&philo->data->stop);
	own_usleep(philo, philo->data->eat_time);
}

bool	check_death(t_philo *philo)
{
	if (philo->eat_rounds != 0)
	{
		if (current_time() - philo->time_last_meal >= philo->data->die_time)
			return (true);
	}
	else if (philo->eat_rounds == 0)
	{
		if (current_time() - philo->data->start_time >= philo->data->die_time)
			return (true);
	}
	return (false);
}


// void	free_data(t_philo *philo)
// {
	
// }

static void	*routine(void *philo_pt)
{
	t_philo		*philo;

	philo = (t_philo *) philo_pt;
	if (philo->pos % 2 == 0)
		own_usleep(philo, 10);
	while ((philo->fully_ate == false) && (philo->data->philo_alive == true))
	{	
		pthread_mutex_lock(&philo->data->checking);
		if (check_death(philo) == true)
		{
			philo->data->philo_alive = false;
			printf(YELLOW"\n(%ld) Philo %d died!\n"RESET,
				current_time(), philo->pos);
			pthread_mutex_unlock(&philo->data->checking);
		}
		pthread_mutex_unlock(&philo->data->checking);
		if (take_forks(philo) == 1)
			return (NULL);
		eat(philo);
		if (return_forks(philo) == 1)
			return (NULL); 
		output_message(philo, SLEEP);
		own_usleep(philo, philo->data->sleep_time);
		output_message(philo, THINK);
	}
	return (NULL);
}



// static void	watcher_thread(void *data_pt)
// {
// 	int		i;
// 	t_data	*data;

// 	i = 0;
// 	data = (t_data *) data_pt;
// 	while (1)
// 	{
// 		if (data->philo_alive == false)
// 		{
			
// 			break ;
// 		}
// 		i++;
// 	}
// 	return (NULL);
// }

int	initialize_philo_data(t_data *data)
{
	int			i;
	
	data->philos = malloc(data->nr_philo * sizeof(t_philo));
	if (data->philos == NULL)
		return (1);
	i = 0;
	while (i < data->nr_philo)
	{
		data->philos[i].is_eating = false;
		data->philos[i].fully_ate = false;
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
	data->start_time = current_time();
	printf("Start time: %ld \n\n", data->start_time);
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

int	initialize_data(t_data *data, int argc, char **argv)
{
	if (check_data(argc, argv) == 1)
	{
		printf("Invalid arguments.\n");
		return (1);
	}
	data->philo_alive = true;
	data->nr_philo = ft_atoi(argv[1]);
	data->die_time = ft_atoi(argv[2]);
	data->eat_time = ft_atoi(argv[3]);
	data->sleep_time = ft_atoi(argv[4]);
	data->completed_rounds = 0;
	if (argc == 6)
		data->required_rounds = ft_atoi(argv[5]);
	else
		data->required_rounds = -1;
	printf("----->%d\n\n", data->required_rounds);
	data->start_time = 0;
	//data->counter = 1;
	return (0);
}

int	initialize_forks(t_data *data)
{
	int	i;
	
	if (pthread_mutex_init(&data->checking, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->printing, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->update_time, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->stop, NULL) != 0)
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
	if (pthread_mutex_destroy(&data->checking) != 0)
			return (1);
	return (0);
}
