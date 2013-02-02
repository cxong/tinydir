#ifndef TINYDIR_H
#define TINYDIR_H

#include <errno.h>
#include <string.h>
#ifdef _MSC_VER
#include <windows.h>
#else
#include <dirent.h>
#include <sys/stat.h>
#endif


/* types */

#define _TINYDIR_PATH_MAX 4096
#ifdef _MSC_VER
/* extra chars for the "\\*" mask */
#define _TINYDIR_PATH_EXTRA 2
#else
#define _TINYDIR_PATH_EXTRA 0
#endif

typedef struct
{
	char path[_TINYDIR_PATH_MAX];
	int has_next;

#ifdef _MSC_VER
	HANDLE _h;
	WIN32_FIND_DATA _f;
#else
	DIR *_d;
	struct dirent *_e;
#endif
} tinydir_dir;

typedef struct
{
	char path[_TINYDIR_PATH_MAX];
	const char *name;
	int is_dir;

#ifdef _MSC_VER
#else
	struct stat _s;
#endif
} tinydir_file;


/* declarations */

int tinydir_open(tinydir_dir *dir, const char *path);
void tinydir_close(tinydir_dir *dir);

int tinydir_next(tinydir_dir *dir);
int tinydir_readfile(const tinydir_dir *dir, tinydir_file *file);


/* definitions*/

int tinydir_open(tinydir_dir *dir, const char *path)
{
	if (dir == NULL || path == NULL || strlen(path) == 0)
	{
		errno = EINVAL;
		return -1;
	}
	if (strlen(path) + _TINYDIR_PATH_EXTRA >= _TINYDIR_PATH_MAX)
	{
		errno = ENAMETOOLONG;
		return -1;
	}

	/* initialise dir */
#ifdef _MSC_VER
	dir->_h = INVALID_HANDLE_VALUE;
#else
	dir->_d = NULL;
#endif
	tinydir_close(dir);

	strcpy(dir->path, path);
#ifdef _MSC_VER
	strcat(dir->path, "\\*");
	dir->_h = FindFirstFile(dir->path, &dir->_f);
	dir->path[strlen(dir->path) - 2] = '\0';
	if (dir->_h == INVALID_HANDLE_VALUE)
#else
	dir->_d = opendir(path);
	if (dir->_d == NULL)
#endif
	{
		errno = ENOENT;
		goto bail;
	}

	/* read first file */
	dir->has_next = 1;
#ifndef _MSC_VER
	dir->_e = readdir(dir->_d);
	if (dir->_e == NULL)
	{
		dir->has_next = 0;
	}
#endif

	return 0;

bail:
	tinydir_close(dir);
	return -1;
}

void tinydir_close(tinydir_dir *dir)
{
	if (dir == NULL)
	{
		return;
	}

	memset(dir->path, 0, sizeof(dir->path));
	dir->has_next = 0;
#ifdef _MSC_VER
	if (dir->_h != INVALID_HANDLE_VALUE)
	{
		FindClose(dir->_h);
	}
	dir->_h = INVALID_HANDLE_VALUE;
#else
	if (dir->_d)
	{
		closedir(dir->_d);
	}
	dir->_d = NULL;
	dir->_e = NULL;
#endif
}

int tinydir_next(tinydir_dir *dir)
{
	if (dir == NULL)
	{
		errno = EINVAL;
		return -1;
	}
	if (!dir->has_next)
	{
		errno = ENOENT;
		return -1;
	}

#ifdef _MSC_VER
	if (FindNextFile(dir->_h, &dir->_f) == 0)
#else
	dir->_e = readdir(dir->_d);
	if (dir->_e == NULL)
#endif
	{
		dir->has_next = 0;
	}

#ifdef _MSC_VER
	if (GetLastError() != ERROR_SUCCESS &&
		GetLastError() != ERROR_NO_MORE_FILES)
	{
		tinydir_close(dir);
		errno = EIO;
		return -1;
	}
#endif

	return 0;
}

int tinydir_readfile(const tinydir_dir *dir, tinydir_file *file)
{
	if (dir == NULL || file == NULL)
	{
		errno = EINVAL;
		return -1;
	}
#ifdef _MSC_VER
	if (dir->_h == INVALID_HANDLE_VALUE)
#else
	if (dir->_e == NULL)
#endif
	{
		errno = ENOENT;
		return -1;
	}
	if (strlen(dir->path) +
		strlen(
#ifdef _MSC_VER
			dir->_f.cFileName
#else
			dir->_e->d_name
#endif
		) + 1 + _TINYDIR_PATH_EXTRA >=
		_TINYDIR_PATH_MAX)
	{
		/* the path for the file will be too long */
		errno = ENAMETOOLONG;
		return -1;
	}

	strcpy(file->path, dir->path);
	strcat(file->path, "/");
	file->name = file->path + strlen(file->path);
	strcat(file->path,
#ifdef _MSC_VER
		dir->_f.cFileName
#else
		dir->_e->d_name
#endif
	);
#ifndef _MSC_VER
	if (stat(file->path, &file->_s) == -1)
	{
		return -1;
	}
#endif
	file->is_dir =
#ifdef _MSC_VER
		!!(dir->_f.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);
#else
		S_ISDIR(file->_s.st_mode);
#endif

	return 0;
}

#endif
