/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztawanna <ztawanna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 23:12:56 by ztawanna          #+#    #+#             */
/*   Updated: 2020/10/21 00:23:11 by ztawanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int			ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\r' ||
	c == '\f' || c == '\v' || c == ' ')
		return (1);
	else
		return (0);
}

int			ft_atoi(const char *str)
{
	int					i;
	int					sign;
	unsigned long int	res;

	i = 0;
	res = 0;
	sign = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (*str && str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - 48);
		if (res > (res * 10 + (str[i + 1] - 48)) && sign == 1)
			return (-1);
		else if (res > (res * 10 + (str[i + 1] - 48)) && sign == -1)
			return (0);
		i++;
	}
	return (res * sign);
}
