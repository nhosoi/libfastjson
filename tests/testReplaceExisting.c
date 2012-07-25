#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "json.h"

int main(int argc, char **argv)
{
	MC_SET_DEBUG(1);

	/*
	 * Check that replacing an existing object keeps the key valid,
	 * and that it keeps the order the same.
	 */
	json_object *my_object = json_object_new_object();
	json_object_object_add(my_object, "foo1", json_object_new_string("bar1"));
	json_object_object_add(my_object, "foo2", json_object_new_string("bar2"));
	json_object_object_add(my_object, "foo3", json_object_new_string("bar3"));
	const char *original_key = NULL;
	int orig_count = 0;
	json_object_object_foreach(my_object, key, val)
	{
		printf("Key at index %d is [%s]\n", orig_count, key);
		orig_count++;
		if (strcmp(key, "foo2") != 0)
			continue;
		printf("replacing value for key [%s]\n", key);
		original_key = key;
		json_object_object_add(my_object, key, json_object_new_string("zzz"));
	}

	printf("==== second loop starting ====\n");

	int new_count = 0;
	int retval = 0;
	json_object_object_foreach(my_object, key2, val2)
	{
		printf("Key at index %d is [%s]\n", new_count, key2);
		new_count++;
		if (strcmp(key2, "foo2") != 0)
			continue;
		printf("pointer for key [%s] does %smatch\n", key2,
		       (key2 == original_key) ? "" : "NOT ");
		if (key2 != original_key)
			retval = 1;
	}
	if (new_count != orig_count)
	{
		printf("mismatch between original count (%d) and new count (%d)\n",
		       orig_count, new_count);
		retval = 1;
	}

	return 0;
}
