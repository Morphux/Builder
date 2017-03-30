#include "test.h"

TEST(flags_init) {
    flags_init();
    TEST_ASSERT(flags_get_verbose() == 0, "Value is wrong");
    TEST_ASSERT(flags_get_nofork() == true, "Value is wrong");
    TEST_ASSERT(flags_get_port() == 5982, "Value is wrong")
    TEST_ASSERT(flags_get_logfile() == NULL, "Value is wrong");
    TEST_ASSERT(flags_get_pidfile() == NULL, "Value is wrong");
    return TEST_SUCCESS;
}

TEST(flags_cleanup) {
    flags_set_pidfile("Test 123");
    flags_cleanup();
    TEST_ASSERT(flags_get_pidfile() == NULL, "Return value is wrong");
    flags_set_logfile("Test 123");
    flags_cleanup();
    TEST_ASSERT(flags_get_logfile() == NULL, "Return value is wrong");
    return TEST_SUCCESS;
}

TEST(flags_no_fork) {
    flags_cleanup();
    TEST_ASSERT(flags_get_nofork() == true, "Return value is wrong");
    flags_set_nofork("");
    TEST_ASSERT(flags_get_nofork() == false, "Return value is wrong");
    return TEST_SUCCESS;
}

TEST(flags_logfile) {
    flags_cleanup();
    TEST_ASSERT(flags_get_logfile() == NULL, "Return value is wrong");
    flags_set_logfile("Something");
    TEST_ASSERT(strcmp(flags_get_logfile(), "Something") == 0, "Return value is wrong");
    return TEST_SUCCESS;
}

TEST(flags_pidfile) {
    flags_cleanup();
    TEST_ASSERT(flags_get_pidfile() == NULL, "Return value is wrong");
    flags_set_pidfile("Something");
    TEST_ASSERT(strcmp(flags_get_pidfile(), "Something") == 0, "Return value is wrong");
    return TEST_SUCCESS;
}

TEST(flags_port) {
    flags_cleanup();
    flags_set_listen_port("4242");
    TEST_ASSERT(flags_get_port() == 4242, "Return value is wrong");
    flags_set_listen_port("wrong");
    TEST_ASSERT(flags_get_port() == 0, "Return value is wrong");
    flags_set_listen_port("4242");
    TEST_ASSERT(flags_get_port() == 4242, "Return value is wrong");
    return TEST_SUCCESS;
}

TEST(flags_verbose) {
    flags_cleanup();
    TEST_ASSERT(flags_get_verbose() == 0, "Return value is wrong");
    flags_set_verbose(NULL);
    TEST_ASSERT(flags_get_verbose() == 1, "Return value is wrong");
    flags_set_verbose(NULL);
    TEST_ASSERT(flags_get_verbose() == 2, "Return value is wrong");
    flags_set_verbose(NULL);
    TEST_ASSERT(flags_get_verbose() == 3, "Return value is wrong");
    flags_set_verbose(NULL);
    TEST_ASSERT(flags_get_verbose() == 3, "Return value is wrong");
    return TEST_SUCCESS;
}

void register_args_test(void) {
    reg_test("flags", flags_init);
    reg_test("flags", flags_cleanup);
    reg_test("flags", flags_no_fork);
    reg_test("flags", flags_pidfile);
    reg_test("flags", flags_logfile);
    reg_test("flags", flags_logfile);
    reg_test("flags", flags_port);
    reg_test("flags", flags_verbose);
}
