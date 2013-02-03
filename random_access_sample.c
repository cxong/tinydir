#include <stdio.h>
#include "tinydir.h"

int main(void)
{
	tinydir_dir dir;
	int errsv;
	int i;
	if (tinydir_open_sorted(&dir, ".") == -1)
	{
		errsv = errno;
		fprintf(stderr, "Error opening file: %s\n", strerror(errsv));
		goto bail;
	}

	for (i = 0; i < dir.n_files; i++)
	{
		tinydir_file file;
		if (tinydir_readfile_n(&dir, &file, i) == -1)
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
	}

bail:
	tinydir_close(&dir);
	return 0;
}
