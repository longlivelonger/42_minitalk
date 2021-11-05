/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbronwyn <sbronwyn@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 15:25:09 by sbronwyn          #+#    #+#             */
/*   Updated: 2021/11/03 13:24:51 by sbronwyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>

int	ft_atoi(const char *str)
{
	int	num;
	int	i;
	int	minus;

	minus = 0;
	num = 0;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			minus = 1;
	i--;
	while (str[++i] >= '0' && str[i] <= '9')
	{
		if (num * 10 < 0 && minus)
			return (0);
		if (num * 10 < 0)
			return (-1);
		num = num * 10 + str[i] - '0';
	}
	if (minus)
		return (-num);
	return (num);
}

void	send_signals(int pid, char *str)
{
	int	i;
	int	j;

	i = -1;
	while (str[++i] != '\0')
	{
		j = -1;
		while (++j < 8)
		{
			if (str[i] & (1 << j))
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			pause();
			usleep(300);
		}
	}
}

void	signals_handler(int signal, siginfo_t *info, void *context)
{
	(void) signal;
	(void) info;
	(void) context;
}

int	main(int argc, char **argv)
{
	struct sigaction	act;
	int					pid;

	if (argc != 3)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = signals_handler;
	sigaction(SIGUSR1, &act, 0);
	sigaction(SIGUSR2, &act, 0);
	send_signals(pid, argv[2]);
	return (0);
}
