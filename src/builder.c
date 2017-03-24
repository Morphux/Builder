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

/* Bullshint function for callback, until i know what to do for some options */
void    nothing(const char *str) {
    g_flags.port = 100;
    (void)str;
}

static void daemonize(void) {
    pid_t   pid = 0, sid = 0;
    int     devnull = 0;

    pid = fork();
    if (pid < 0) {
        m_panic("%s\n", strerror(errno));
    } else if (pid > 0) {
        FILE    *fp_pid;
        if (!(fp_pid = fopen(PID_FILE, "w+"))) {
            m_panic("%s\n", strerror(errno));
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
        m_panic("%s\n", strerror(errno));
    if (!(devnull = open("/dev/null", O_WRONLY)))
        m_panic("%s\n", strerror(errno));

/* Closing all standard fd, we will not use it. */
    if (dup2(STDIN_FILENO, devnull) == -1)
        m_panic("Can't close STDIN : %s\n", strerror(errno));
    if (dup2(STDOUT_FILENO, devnull) == -1)
        m_panic("Can't close STDOUT : %s\n", strerror(errno));
    if (dup2(STDERR_FILENO, devnull) == -1)
        m_panic("Can't close STDERR : %s\n", strerror(errno));
}

static void usage(void) {
    fprintf(STDERR_FILENO,
"usage : builder [-nd] [-D debug-level] [-P port_number]\n"
"                [-p pidfile] [-l logfile]"
    )
}

int main(int ac, char *av[]) {
    /*Declare struct containing all possible optionnal parameters*/
    mopts_t     opts[] = {
        {'n', "nofork", "[No] Do not fork.", false, &nofork},
        {'d', "debug-level", "[No] Increase the debug level.", false, &nothing},
        {'D', "set-debug-level", "[Int] Set the debug level.", true, &nothing},
        {'P', "port", "[Int] Specify port to listen on.", true, &listen_port},
        {'p', "pidfile", "[Str] Path to the pid file.", true, &pidfile},
        {'l', "logfile", "[Str] Path to the log file.", true, &logfile},
        ARGS_EOL
    };
    mlist_t     *params;

    /*Set program informations*/
    set_program_name(NAME);
    set_version(VERSION);
    set_maintainer(MAINTAINER);

    /* Initialize default flags */
    g_flags.verbose = 0;
    g_flags.daemonize = true;
    g_flags.port = 6694;
    g_flags.pid_file = NULL;
    g_flags.log_file = NULL;

    /*Read all options passed in parameters*/
    read_opt(ac, av, opts, &params);

    /*Daemonize the process unless option "nofork" is passed*/
    if (g_flags.daemonize == true)
        daemonize();

    return 0;
}
