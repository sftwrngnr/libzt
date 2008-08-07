/*
 * sha1_test.c        test assertions
 *
 * Copyright (C) 2008, Jason L. Shiffer <jshiffer@zerotao.org>.  All Rights Reserved.
 * See file COPYING for details.
 *
 */

/*
 * Description: 
 */
#include <libzt/zt.h>
#include <libzt/zt_unit.h>
#include <libzt/zt_sha1.h>


static void
basic_tests(struct zt_unit_test *test, void *data)
{
	/* get rid of the log message for the moment */
	char		* tdata[] = { "abc",
							  "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq",
							  "http://www.google.com" };

	char		* results[] = { "a9993e364706816aba3e25717850c26c9cd0d89d",
								"84983e441c3bd26ebaae4aa1f95129e5e54670f1",
								"738ddf35b3a85a7a6ba7b232bd3d5f1e4d284ad1" };
	uint8_t		  digest[20];
	char		  sha1[41];
	
	char		* result;
	int			  i;
	zt_sha1_ctx	  ctx;
	
	for (i=0; i < sizeof_array(tdata); i++) {
		zt_sha1_data(tdata[i], strlen(tdata[i]), digest);
		zt_sha1_tostr(digest, sha1);
		ZT_UNIT_ASSERT(test, strncmp(results[i], sha1, 20) == 0);
	}

	zt_sha1_init(&ctx);
	for (i=0; i<1000000; i++){
		zt_sha1_update(&ctx, (uint8_t *)"a", 1);
	}
	zt_sha1_finalize(&ctx, digest);
	
	zt_sha1_tostr(digest, sha1);
	ZT_UNIT_ASSERT(test, strncmp(sha1, "34aa973cd4c4daa4f61eeb2bdbad27316534016f", 20) == 0);

}

int
register_sha1_suite(struct zt_unit *unit)
{
	struct zt_unit_suite	* suite;

	suite = zt_unit_register_suite(unit, "sha1 tests", NULL, NULL, NULL);
	zt_unit_register_test(suite, "basic", basic_tests);
	return 0;
}