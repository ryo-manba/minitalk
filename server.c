/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuka < rmatsuka@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 16:12:49 by rmatsuka          #+#    #+#             */
/*   Updated: 2021/06/09 16:13:05 by rmatsuka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

static void	restore_data(int bit, pid_t client_pid)
{
	static int	i;
	static int	len;
	static char	c;
	static char	buf[1010];

	if (i < 8)
	{
		c += (bit << i);
		i++;
	}
	if (i == 8)
	{
		buf[len] = c;
		len++;
		if (c == '\0' || len >= 1000)
		{
			ft_putstr_fd(buf, STDOUT_FILENO);
			len = 0;
			if (c == '\0')
				if (kill(client_pid, SIGUSR1) == -1)
					exit(1);
		}
		i = 0;
		c = 0;
	}
}

static void	sig_handler(int sig, siginfo_t *info, void *context)
{
	(void)context;
	if (sig == SIGUSR1)
		restore_data(1, info->si_pid);
	if (sig == SIGUSR2)
		restore_data(0, info->si_pid);
}

static void	set_signal(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = sig_handler;
	if (sigemptyset(&act.sa_mask) != 0
		|| sigaction(SIGUSR1, &act, NULL) != 0
		|| sigaction(SIGUSR2, &act, NULL) != 0)
		exit(1);
}

int	main(int argc, char **argv)
{
	pid_t	pid;

	(void)argv;
	if (argc != 1)
	{
		ft_putendl_fd("Take no arguments", 2);
		return (1);
	}
	set_signal();
	pid = getpid();
	ft_putstr_fd("pid:", STDOUT_FILENO);
	ft_putnbr_fd(pid, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	while (1)
		pause();
	return (0);
}
