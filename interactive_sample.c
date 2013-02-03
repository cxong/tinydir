#include <stdio.h>
#include "tinydir.h"

int main(int argc, char *argv[])
{
	tinydir_dir dir;
	int errsv;

	if (tinydir_open_sorted(&dir, ".") == -1)
	{
		errsv = errno;
		fprintf(stderr, "Error opening file: %s\n", strerror(errsv));
		goto bail;
	}

	while (1)
	{
		int i;
		char input[256];
		for (i = 0; i < dir.n_files; i++)
		{
			tinydir_file file;
			if (tinydir_readfile_n(&dir, &file, i) == -1)
			{
				errsv = errno;
				fprintf(stderr, "Error getting file: %s\n", strerror(errsv));
				goto bail;
			}

			if (file.is_dir)
			{
				printf("[%d] ", i);
			}
			printf("%s", file.name);
			if (file.is_dir)
			{
				printf("/");
			}
			printf("\n");
		}
		printf("?");

		if (fgets(input, 256, stdin) == NULL)
		{
			break;
		}
		else
		{
			int choice = atoi(input);
			if (choice >= 0 && choice < dir.n_files)
			{
				if (tinydir_open_subdir_n(&dir, choice) == -1)
				{
					errsv = errno;
					fprintf(stderr, "Error opening subdirectory: %s\n", strerror(errsv));
					goto bail;
				}
			}
		}
	}

bail:
	tinydir_close(&dir);
	return 0;
}
