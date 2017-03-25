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

#ifndef TEST_H
# define TEST_H

# include <morphux.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <builder.h>

# define DUP_ALL_OUTPUTS(name) dup2(name[1], 1); dup2(name[1], 2); close(name[1]);
# define WAIT_AND_CLOSE(pid, status, fd) pid = waitpid(pid, &status, 0); close(fd[1]);

# define BIN "../builder"

void register_args_test(void);

#endif /* TEST_H */
