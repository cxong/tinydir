#include <stdio.h>
#include "tinydir.h"

int main(int argc, char *argv[])
{
	tinydir_dir dir;
	int errsv;
	if (tinydir_open(&dir, "C:\\tinydir") == -1)
	{
		errsv = errno;
		fprintf(stderr, "Error opening file: %s\n", strerror(errsv));
		goto bail;
	}

	while (dir.has_next)
	{
		tinydir_file file;
		if (tinydir_readfile(&dir, &file) == -1)
		{
			errsv = errno;
			fprintf(stderr, "Error getting file: %s\n", strerror(errsv));
			goto bail;
		}

		printf("%s", file.name);
		if (file.is_dir)
		{
			printf("/");
		}
		printf("\n");

		tinydir_next(&dir);
	}

bail:
	tinydir_close(&dir);
	return 0;
}
