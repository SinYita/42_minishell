/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weiyuandu <weiyuandu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:30:00 by wedu              #+#    #+#             */
/*   Updated: 2026/02/12 21:57:49 by weiyuandu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_signal_received = 0;

/*
为什么这样设计？
问题: 信号处理函数中不能直接修改复杂的数据结构（如 shell 结构体），因为信号处理是异步的，可能导致数据竞争。

解决方案:

信号处理函数只设置一个简单的全局标志 g_signal_received
主循环在安全的时机检查这个标志并更新 exit_status
退出状态码 130
按照 UNIX 惯例：

正常退出：0-255
被信号中断：128 + 信号编号
SIGINT = 2，所以 128 + 2 = 130
这样 echo $? 就能正确显示上次被 Ctrl+C 中断的状态了！

*/
void	handle_sigint(int sig)
{
	(void)sig;
	g_signal_received = SIGINT;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();//通知readline准备新的输入行
	rl_replace_line("", 0); //清空当前输入缓冲区
	rl_redisplay(); // 刷新显示，重新绘制提示符
}

void	handle_sigquit(int sig)
{
	(void)sig;
	/* Do nothing - just ignore SIGQUIT */
}
//SIGINT ctrl+c 用来中断当前执行
//SIGQUIT ctrl + \用来(在这里被忽略了)

void	setup_signals(void)
{
	struct sigaction sa_int;
	struct sigaction sa_quit;

	sa_int.sa_handler = &handle_sigint;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);

	sa_quit.sa_handler = &handle_sigquit;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa_quit, NULL);
}
