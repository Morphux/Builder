/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhezard <jhezard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 17:04:29 by jhezard           #+#    #+#             */
/*   Updated: 2017/01/22 13:44:33 by jhezard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builder.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>


void	nothing(const char *str) {
	(void)str;
}

void	daemonize(void) {
	pid_t	pid = 0, sid = 0;
	int		ret = 0;

	pid = fork();
	if (pid < 0) {
		m_panic("Fork failed\n");
	} else if (pid > 0) {
		FILE	*fp_pid;

		if (!(fp_pid = fopen(PID_FILE, "w+"))) {
			m_panic("Open of the PID file "PID_FILE" failed\n");
		}
		fprintf(fp_pid, "%d\n", pid);
		m_info("PID of the child process is : %d\n", pid);
		fclose(fp_pid);
		_exit(0);
	}

	waitpid(pid, &ret, 0);
	if (WEXITSTATUS(ret))
		_exit(1);

	/* Reseting default file permissions */
	umask(0);

	sid = setsid();
	if (sid < 0)
		m_panic("Setsid failed\n");

	/* Closing all standard fd, we will not use it. */
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}

int		main(int ac, char *av[]) {
	margs_t		opts[] = {
		{'f', "force", "Do not launch the program as a daemon.", false, &nothing},
		ARGS_EOL
	};

	set_program_name(NAME);
	set_version(VERSION);
	set_maintainer(MAINTAINER);
	read_opt(ac, av, opts);

	daemonize();
	return 0;
}
