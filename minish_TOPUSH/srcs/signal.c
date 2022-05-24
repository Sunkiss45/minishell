/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iderighe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 22:10:32 by iderighe          #+#    #+#             */
/*   Updated: 2022/05/23 22:10:53 by iderighe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_on(int key)
{
	if (key == SIGINT)
	{
		g_sig = -1;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (key == SIGQUIT)
	{
		write(1, "\b\b  \b\b", 6);
		signal(SIGQUIT, SIG_IGN);
		return ;
	}
}

void	signal_off(int key)
{
	if (key == SIGINT)
	{
		write(1, "\n", 1);
		return ;
	}
	if (key == SIGQUIT)
	{
		write(2, "Quit (core dumped)\n", 19);
		return ;
	}
	if (key == SIGSEGV)
	{
		write(2, "Segmentation fault (core dumped)\n", 33);
		return ;
	}
}

void	handle_sig(int key)
{
	if (g_sig == 2)
		return ;
	if (g_sig == 0 || g_sig == -1)
		signal_on(key);
	if (g_sig == 1)
		signal_off(key);
}

void	ft_signal(void)
{
	struct sigaction	sa;

	sa.sa_handler = &handle_sig;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGSEGV, &sa, NULL);
}
