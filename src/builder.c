/*********************************** LICENSE **********************************\
*                            Copyright 2017 Morphux                            *
*                                                                              *
*        Licensed under the Apache License, Version 2.0 (the "License");       *
*        you may not use this file except in compliance with the License.      *
*                  You may obtain a copy of the License at                     *
*                                                                              *
*                 http://www.apache.org/licenses/LICENSE-2.0                   *
*                                                                              *
*      Unless required by applicable law or agreed to in writing, software     *
*       distributed under the License is distributed on an "AS IS" BASIS,      *
*    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  *
*        See the License for the specific language governing permissions and   *
*                       limitations under the License.                         *
\******************************************************************************/

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <builder.h>
#include <args.h>

#ifndef COMPILE_WITH_TEST

static void daemonize(void) {
    pid_t         pid = 0, sid = 0;
    int           devnull = 0;
    const char    *pid_file = PID_FILE;

    if (flags_get_pidfile() != NULL)
        pid_file = flags_get_pidfile();

    pid = fork();
    if (pid < 0) {
        m_panic("%s\n", strerror(errno));
    } else if (pid > 0) {
        FILE    *fp_pid;

        if (!(fp_pid = fopen(pid_file, "w+"))) {
            m_panic("fopen failed to open %s: %s\n", pid_file, strerror(errno));
        }
        fprintf(fp_pid, "%d\n", pid);
        m_info("PID of the child process is : %d\n", pid);
        fclose(fp_pid);
        exit(0);
    }

    /* Reseting default file permissions */
    umask(0);

    /* Orphan process */
    sid = setsid();
    if (sid < 0)
        m_panic("Setsid failed: %s\n", strerror(errno));
    if (!(devnull = open("/dev/null", O_WRONLY)))
        m_panic("Open failed: %s\n", strerror(errno));

    /* Closing all standard fd, we will not use it. */
    if (dup2(STDIN_FILENO, devnull) == -1)
        m_panic("Can't close STDIN : %s\n", strerror(errno));
    if (dup2(STDOUT_FILENO, devnull) == -1)
        m_panic("Can't close STDOUT : %s\n", strerror(errno));
    if (dup2(STDERR_FILENO, devnull) == -1)
        m_panic("Can't close STDERR : %s\n", strerror(errno));
}

int main(int ac, char *av[]) {
    /* Declare struct containing all possible optionnal parameters */
    static const mopts_t     opts[] = {
        {
            .opt = 'n',
            .s_opt = "nofork",
            .desc = "Do not fork",
            .callback = &flags_set_nofork
        },
        {
            .opt = 'd',
            .desc = "Increase the debug level",
        },
        {
            .opt = 'D',
            .s_opt = "set-debug-level",
            .desc = "Set the debug level",
            .take_arg = true,
            .usage = "[1-3]"
        },
        {
            .opt = 'P',
            .s_opt = "port",
            .desc = "Specify port to listen on",
            .take_arg = true,
            .callback = &flags_set_listen_port,
            .usage = "PORT"
        },
        {
            .opt = 'p',
            .s_opt = "pidfile",
            .desc = "Path to the pid file",
            .take_arg = true,
            .callback = &flags_set_pidfile,
            .usage = "PID_FILE"
        },
        {
            .opt = 'l',
            .s_opt = "logfile",
            .desc = "Path to the log file",
            .take_arg = true,
            .callback = &flags_set_logfile,
            .usage = "LOG_FILE"
        },
        {
            .opt = 'v',
            .desc = "Increase the verbose level (Up to 3)",
            .callback = &flags_set_verbose
        },
        ARGS_EOL
    };
    mlist_t     *params = NULL;

    /* Set program informations */
    set_program_name(NAME);
    set_version(VERSION);
    set_maintainer(MAINTAINER);

    /* Initialize default flags */
    flags_init();

    /* Read all options passed in parameters */
    read_opt(ac, av, opts, &params);

    /* Daemonize the process unless option "nofork" is passed */
    if (flags_get_nofork() == true)
        daemonize();

    flags_cleanup();
    return 0;
}
#endif /* COMPILE_WITH_TEST */
