#include "duktape.h"
#include "duk_v1_compat.h"
#include "duk_console.h"
#include "duk_module_duktape.h"

#include <stdio.h>

static duk_ret_t modSearch(duk_context *ctx)
{
	const char *id = duk_get_string(ctx, 0);

	duk_push_string_file(ctx, id);

	return 1;
}

int main(int argc, char *argv[])
{
	duk_context *ctx = duk_create_heap_default();
	if (!ctx)
		return 1;

	duk_console_init(ctx, 0);
	duk_module_duktape_init(ctx);

	duk_get_global_string(ctx, "Duktape");
	duk_push_c_function(ctx, modSearch, 4);
	duk_put_prop_string(ctx, -2, "modSearch");
	duk_pop(ctx);

//	duk_push_c_function(ctx, test, 0);
//	duk_put_global_string(ctx, "test");

	if (duk_peval_file(ctx, argv[1]) != 0)
		printf("%s\n", duk_safe_to_string(ctx, -1));

	duk_destroy_heap(ctx);

	return 0;
}