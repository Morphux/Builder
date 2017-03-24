/***********************************LICENSE **********************************\
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

#include <builder.h>
#include <args.h>

typedef struct flags_s {
    /**
     * Flag for verbose, can be incremented
     * to increase the level of verbosity
     * Default: 0
     */
    u8_t            verbose;

    /**
     * Flag that will define if we have to
     * daemonize the process.
     * Default: true
     */
    bool            daemonize;
    bool            quiet;

    /**
     * Flag that will define the port
     * to listen on.
     * Default: 6694
     */
    u32_t           port;

    /**
     * Path of the specified log file, if defined
     * Default: NULL
     */
    char            *pid_file;

    /**
     * Path of the specifiedd PID file, if defined
     * Default: NULL
     */
    char            *log_file;
} flags_t;

static flags_t g_flags;

void flags_init(void) {
    g_flags.verbose = 0;
    g_flags.daemonize = true;
    g_flags.port = 6694;
    g_flags.pid_file = NULL;
    g_flags.log_file = NULL;
}

void flags_cleanup(void) {
    free(g_flags.pid_file);
    free(g_flags.log_file);
}

void flags_set_nofork(const char *str) {
    (void)str;
    g_flags.daemonize = false;
}

bool flags_get_nofork(void) {
    return g_flags.daemonize;
}

void flags_set_logfile(const char *str) {
    if (str != NULL)
        g_flags.log_file = strdup(str);
}

const char *flags_get_logfile(void) {
    return g_flags.log_file;
}

void flags_set_pidfile(const char *str) {
    if (str != NULL)
        g_flags.pid_file = strdup(str);
}

const char *flags_get_pidfile(void) {
    return g_flags.pid_file;
}

void flags_set_listen_port(const char *str) {
    if (str != NULL)
        g_flags.port = strtoull(str, (char **)NULL, 10);
}

u32_t flags_get_port(void) {
    return g_flags.port;
}
