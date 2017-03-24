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

void flags_init(void);
void flags_cleanup(void);
void flags_set_nofork(const char *str);
bool flags_get_nofork(void);
void flags_set_logfile(const char *str);
const char *flags_get_logfile(void);
void flags_set_pidfile(const char *str);
const char *flags_get_pidfile(void);
void flags_set_listen_port(const char *str);
u32_t flags_get_port(void);

#endif /* ARGS_H */
