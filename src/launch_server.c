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

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <builder.h>
#include <args.h>

#define BACKLOG 10 /* How many pending connection we will keep in queue */

void launch_server(void) {
    int             sockfd,     /* Read on this one */
                    rval;       /* To stock getaddrinfo() return */
    s8_t            enable = 1; /* Int to enable the option in setsockopt */
    struct addrinfo hints,      /* Flags of getaddrinfo() */
                    *servinfo,  /* Result of getaddrinfo() */
                    *ptr;        /* Variable used to loop into the linked lst*/
    char            port_str[6]; /* Buffer to hold the port number */

    bzero(&hints, sizeof hints);
    hints.ai_family = AF_UNSPEC;     /* Don't care IPv4 and IPv6 */
    hints.ai_socktype = SOCK_STREAM; /* Use TCP stream socket */

    /* Get port number as a string */
    snprintf(port_str, 6, "%d", flags_get_port());

    if ((rval = getaddrinfo(NULL, port_str, &hints, &servinfo)) != 0)
    {
        /* Exit if getaddrinfo fails */
        m_panic("getaddrinfo failed : %s\n", gai_strerror(rval));
    }

    /* Now we will loop into the linked list */
    for (ptr = servinfo; ptr != NULL; ptr = ptr->ai_next)
    {
        /* Try to get a fd from node of linked list */
        if ((sockfd = socket(ptr->ai_family, 
                ptr->ai_socktype, ptr->ai_protocol)) == -1)
        {
            /* If it fails, display the error and try with the next struct */
            m_error("Server: socket" , strerror(errno));
            continue ;
        }
        /* If socket succeded, call setsockopt */
        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, 
            sizeof(int)) == 1)
        {
            /* If it fails, display the error and exit */
            m_panic("Server: socket" , strerror(errno));
        }
        /* If we got here, try to bind to the socket */
        if (bind(sockfd, ptr->ai_addr, ptr->ai_addrlen) == -1)
        {
            /* If it fails, display the error and try with the next struct */
            close(sockfd);
            m_error("Server: bind" , strerror(errno));
            continue ;
        }
        /* If all that succeded, get out of the loop */
        break ;
    }
    /* Don't need this struct anymore */
    freeaddrinfo(servinfo);

    if (ptr == NULL)
    {
        /* Exit if we looked at all the stucts and bound on none */
        m_panic("Server: failed to bind");
    }

    if (listen(sockfd, BACKLOG) == -1)
    {
        m_panic("Server: listen" , strerror(errno));
    }

    m_info("Waiting for connections ...");

}