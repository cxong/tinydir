#include <stdio.h>

#include <tinydir.h>
#include "cbehave.h"

static void make_temp_file(const char *prefix, char *out)
{
#ifdef _MSC_VER
	if (GetTempFileName(".", prefix, 0, out) != 0)
	{
		// Strip the ".\\" prefix
		if (strncmp(out, ".\\", 2) == 0)
		{
			memmove(out, out + 2, strlen(out));
		}
		// Create file
		fclose(fopen(out, "w"));
	}
#else
	#include <stdlib.h>
	#include <unistd.h>
	sprintf(out, "%sXXXXXX", prefix);
	close(mkstemp(out));
#endif
}

FEATURE(file_open, "File open")
	SCENARIO("Open file in current directory")
		GIVEN("a file in the current directory")
			char name[4096];
			make_temp_file("temp_file_", name);
		WHEN("we open it")
			tinydir_file file;
			int r = tinydir_file_open(&file, name);
		THEN("the result should be successful")
			SHOULD_INT_EQUAL(r, 0);
		remove(name);
	SCENARIO_END
FEATURE_END

CBEHAVE_RUN("File open:", TEST_FEATURE(file_open))
