/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_input.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rares <rares@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/15 12:20:59 by rares         #+#    #+#                 */
/*   Updated: 2023/08/15 12:53:02 by rares         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

int	check_digit(char *str)
{
	int	i;
	
	i = 0;
	
	while (str && str[i])
	{
		if (str[i] == '+' || str[i] == '-')
			i++;
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	check_args(int argc, char **argv)
{
	if (check_digit(argv[1]) == 1
		|| check_digit(argv[2]) == 1
		|| check_digit(argv[3]) == 1
		|| check_digit(argv[4]) == 1)
	{
		return (1);
	}
	if (argc == 6)
	{
		if (check_digit(argv[5]) == 1)
			return (1);
	}
	
	return (0);
}

int	check_positive_argv(int argc, char **argv)
{
	if (argv[1][0] == '-'
		|| argv[2][0] == '-'
		|| argv[3][0] == '-'
		|| argv[4][0] == '-')
	{
		return (1);
	}
	if (argc == 6)
	{
		if (argv[5][0] == '-')
			return (1);
	}
	return (0);
}

int	check_int_overflow(int argc, char **argv)
{
	if (ft_atoi(argv[1]) == -1
		|| ft_atoi(argv[2]) == -1
		|| ft_atoi(argv[3]) == -1
		|| ft_atoi(argv[4]) == -1)
	{
		return (1);
	}
	if (argc == 6)
	{
		if (ft_atoi(argv[5]) == 1)
			return (1);
	}
	return (0);
}

int	check_data(int argc, char **argv)
{
	if (check_args(argc, argv) == 1)
	{
		printf("Program arguments should only contain digits\n");
		return(1);
	}
	if (check_positive_argv(argc, argv) == 1)
	{
		printf("Program arguments should be positive\n");
		return(1);
	}
	if (check_int_overflow(argc, argv) == 1)
	{
		printf("Program arg exceeds MAX_INT\n");
		return(1);
	}
	return (0);
}
