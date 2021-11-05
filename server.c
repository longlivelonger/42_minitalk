/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbronwyn <sbronwyn@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 14:27:57 by sbronwyn          #+#    #+#             */
/*   Updated: 2021/11/02 22:36:02 by sbronwyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>

void	print_num(int n)
{
	int		digit;
	char	c;

	if (n < 0)
		write(1, "-", 1);
	digit = n % 10;
	if (n < 0)
		digit *= -1;
	c = '0' + digit;
	if (n <= -10)
		print_num((n / 10) * -1);
	if (n >= 10)
		print_num(n / 10);
	write(1, &c, 1);
}

void	print_pid(void)
{
	write(1, "pid: ", 5);
	print_num(getpid());
	write(1, "\n", 1);
}

void	append_bit(int bit)
{
	static char	c = 0;
	static int	i = 0;

	c += bit << i;
	i++;
	if (i >= 8)
	{
		i = 0;
		write(1, &c, 1);
		c = 0;
	}
}

void	signals_handler(int signal, siginfo_t *info, void *context)
{
	(void) context;
	if (signal == SIGUSR1)
	{
		append_bit(1);
		usleep(300);
		kill(info->si_pid, SIGUSR1);
	}
	else if (signal == SIGUSR2)
	{
		append_bit(0);
		usleep(300);
		kill(info->si_pid, SIGUSR2);
	}
}

int	main(void)
{
	struct sigaction	act;

	print_pid();
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = signals_handler;
	sigaction(SIGUSR1, &act, 0);
	sigaction(SIGUSR2, &act, 0);
	while (1)
		pause();
	return (0);
}
