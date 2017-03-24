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

#ifndef ARGS_H
# define ARGS_H

typedef struct      s_flags {
    /**
     * Flag for verbose, can be incremented
     * to increase the level of verbosity
     * Default: 0
     */
    char            verbose;

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
}                   flags_t;

flags_t g_flags;

void    nofork(const char *str);
void    logfile(const char *str);
void    pidfile(const char *str);
void    listen_port(const char *str);

#endif /* ARGS_H */
