#include <string.h>
#define ZT_WITH_UNIT
#include <zt.h>

static size_t
cvt_S(int code UNUSED, void * value,
      int put(int c, void *cl), void *cl,
      unsigned char flags[], ssize_t width, ssize_t precision)
{
    char * str = *(char **)value;

    zt_assert(str);

    return zt_fmt_puts(str, strlen(str), put, cl, flags, width, precision);
}


static void
basic_tests(struct zt_unit_test *test, void *data UNUSED)
{
    char   buf[256];
    char * str;

    zt_fmt_sprintf(buf, 256, "%s: %d\n", "this is a test", 34);
    ZT_UNIT_ASSERT(test,
                   zt_cstr_cmp(buf, 0, -1,
                               "this is a test: 34\n", 0, -1) == 0);

    zt_fmt_sprintf(buf, 256, "\t%s: 0x~x~~ %% %~ ~%\n", "this is a test", 34);
    ZT_UNIT_ASSERT(test,
                   zt_cstr_cmp(buf, 0, -1,
                               "\tthis is a test: 0x22~ % ~ %\n", 0, -1) == 0);


    ZT_UNIT_ASSERT(test, zt_fmt_register('S', cvt_S, 's') == 0);

    zt_fmt_sprintf(buf, 256, "%S:\n", "this is a test");
    ZT_UNIT_ASSERT(test,
                   zt_cstr_cmp(buf, 0, -1,
                               "this is a test:\n", 0, -1) == 0);


    str = zt_fmt_strprintf("%s: %d\n", "this is a test", 34);
    ZT_UNIT_ASSERT(test,
                   zt_cstr_cmp(str, 0, -1,
                               "this is a test: 34\n", 0, -1) == 0);
    zt_free(str);

    str = zt_fmt_strprintf("\t%s: 0x~x~~ %% %~ ~%\n", "this is a test", 34);
    ZT_UNIT_ASSERT(test,
                   zt_cstr_cmp(str, 0, -1,
                               "\tthis is a test: 0x22~ % ~ %\n", 0, -1) == 0);
    zt_free(str);

    str = zt_fmt_strprintf("%#0.1s", "This is a test", 34);
    ZT_UNIT_ASSERT(test, zt_cstr_cmp(str, 0, -1, "T", 0, -1) == 0);
    zt_free(str);

    str = zt_fmt_strprintf("%#4.1s", "This is a test", 34);
    ZT_UNIT_ASSERT(test, zt_cstr_cmp(str, 0, -1, " ", 0, -1) == 0);
    zt_free(str);

    str = zt_fmt_strprintf("%#30.1s", "This is a test", 34);
    ZT_UNIT_ASSERT(test, zt_cstr_cmp(str, 0, -1, "T", 0, -1) == 0);
    zt_free(str);

    str = zt_fmt_strprintf("%p", (void *)0xFFFFFFFF);
    ZT_UNIT_ASSERT(test, zt_cstr_cmp(str, 0, -1, "ffffffff", 0, -1) == 0);
    zt_free(str);
} /* basic_tests */

int
register_format_suite(struct zt_unit *unit)
{
    struct zt_unit_suite * suite;

    suite = zt_unit_register_suite(unit, "format", NULL, NULL, NULL);
    zt_unit_register_test(suite, "basic", basic_tests);
    return 0;
}

