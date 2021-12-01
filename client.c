/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuka < rmatsuka@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 22:50:10 by rmatsuka          #+#    #+#             */
/*   Updated: 2021/06/09 14:27:12 by rmatsuka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

volatile sig_atomic_t	g_flag = 0;

static void	check_ack(int sig)
{
	if (sig == SIGUSR1)
		g_flag = 1;
	ft_putendl_fd("Message was successfully sent!", 1);
}

static void	send_char(pid_t pid, char c)
{
	int	i;
	int	bit;

	i = 0;
	while (i < 8)
	{
		usleep(50);
		bit = (c >> i) & 1;
		if (bit == 1)
			bit = kill(pid, SIGUSR1);
		else
			bit = kill(pid, SIGUSR2);
		if (bit == -1)
			exit(1);
		i++;
	}
}

static int	send_message(pid_t pid, char *message)
{
	int	i;

	i = 0;
	while (1)
	{
		send_char(pid, message[i]);
		if (message[i] == '\0')
			break ;
		i++;
	}
	return (0);
}

static void	start_the_client(char **argv)
{
	pid_t	pid;

	pid = ft_atoi(argv[1]);
	if (pid <= 0 || kill(pid, 0) == -1)
	{
		ft_putendl_fd("Wrong pid", STDERR_FILENO);
		exit(1);
	}
	g_flag = 0;
	if (signal(SIGUSR1, check_ack) == SIG_ERR
		 || send_message(pid, argv[2]) != 0)
		return ;
	if (!g_flag)
		usleep(50);
	if (g_flag)
		return ;
	ft_putendl_fd("Failed to send message", 2);
}

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		ft_putendl_fd("Usage: ./client [server process-id] [message]",
			STDERR_FILENO);
		return (1);
	}
	start_the_client(argv);
	return (0);
}
