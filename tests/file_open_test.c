#include <stdio.h>

#include <tinydir.h>
#include "cbehave.h"
#include "util.h"


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
	SCENARIO("Open file with a very long filename")
		GIVEN("a file with a long filename in a folder with a long filename")
			char folder[4096];
			make_temp_dir("temp_dir_", folder);
			ASSERT(strlen(folder) > 0, 1);
			strcat(folder, "/AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
			ASSERT(mkdir(folder, 0700) == 0, 0);
			strcat(folder, "/AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
			ASSERT(mkdir(folder, 0700) == 0, 0);
		WHEN("we open it")
			tinydir_file file;
			int r = tinydir_file_open(&file, folder);
		THEN("the result should be successful")
			SHOULD_INT_EQUAL(r, 0);
	SCENARIO_END
FEATURE_END

CBEHAVE_RUN("File open:", TEST_FEATURE(file_open))
