#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <tinydir.h>
#include "cbehave.h"

FEATURE(file_open, "File open")
	SCENARIO("Open file in current directory")
		GIVEN("a file in the current directory")
			char name[] = "fileXXXXXX";
			int fd = mkstemp(name);
			close(fd);
		WHEN("we open it")
			tinydir_file file;
			int r = tinydir_file_open(&file, name);
		THEN("the result should be successful")
			SHOULD_INT_EQUAL(r, 0);
		remove(name);
	SCENARIO_END
FEATURE_END

CBEHAVE_RUN("File open:", TEST_FEATURE(file_open))
