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
            m_panic("fopen failed to open %s: %s\n", PID_FILE, strerror(errno));
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
    /*Declare struct containing all possible optionnal parameters*/
    mopts_t     opts[] = {
        {'n', "nofork", "[No] Do not fork.", false, &flags_set_nofork},
        {'d', "debug-level", "[No] Increase the debug level.", false, &nothing},
        {'D', "set-debug-level", "[Int] Set the debug level.", true, &nothing},
        {'P', "port", "[Int] Specify port to listen on.", true, &flags_set_listen_port},
        {'p', "pidfile", "[Str] Path to the pid file.", true, &flags_set_pidfile},
        {'l', "logfile", "[Str] Path to the log file.", true, &flags_set_logfile},
        ARGS_EOL
    };
    mlist_t     *params;

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
