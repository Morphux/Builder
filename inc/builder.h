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

#ifndef BUILDER_H
# define BUILDER_H

#ifndef NAME
# define NAME "builder_coverage"
#endif

#ifndef VERSION
# define VERSION "coverage"
#endif

#ifndef MAINTAINER
# define MAINTAINER "morphux@morphux.org"
#endif

# define PID_FILE "/var/run/"NAME".pid"
# define LOG_FILE "/var/log/"NAME".log"

# include <morphux.h>
# include <args.h>
# include <errno.h>

#endif /* BUILDER_H */
