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

#include "test.h"

TEST(main) {
	int			st, fd[2];
	pid_t		pid;

	pipe(fd);
	if ((pid = fork()) == 0) {
		DUP_ALL_OUTPUTS(fd);
		execl(BIN, BIN, "--help", NULL);
		exit(1);
	} else {
		WAIT_AND_CLOSE(pid, st, fd);
	}
	return TEST_SUCCESS;
}

TEST(main2) {
	int			st, fd[2];
	pid_t		pid;

	pipe(fd);
	if ((pid = fork()) == 0) {
		DUP_ALL_OUTPUTS(fd);
		execl(BIN, BIN, NULL);
		exit(1);
	} else {
		WAIT_AND_CLOSE(pid, st, fd);
	}
	return TEST_SUCCESS;

}


int		main(void) {
	u32_t	ret;

	reg_test("main", main);
	reg_test("main", main2);

	m_info("Beginning tests...\n");
	ret = test_all();
	test_free();

	return ret;
}
