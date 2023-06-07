/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: raanghel <raanghel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 12:32:38 by raanghel      #+#    #+#                 */
/*   Updated: 2023/06/07 15:24:23 by raanghel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	raise_error(char *message)
{
	
	printf("%s\n", message);
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

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

int	ft_atoi(const char *str)
{
	int			i;
	long int	number;

	i = 0;
	number = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\r'
		|| str[i] == '\n' || str[i] == '\v' || str[i] == '\f')
	{
		i++;
	}
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = number * 10 + str[i] - '0';
		if (number > 2147483647)
			return (-1);
		i++;
	}
	return (number);
}
