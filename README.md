TinyDir
=======

Lightweight, portable and easy to integrate C directory and file reader.

Example
=======

Error checking omitted:

```C
tinydir_dir dir;
tinydir_open(&dir, "/path/to/dir");

while (dir.has_next)
{
	tinydir_file file;
	tinydir_readfile(&dir, &file);

	printf("%s", file.name);
	if (file.is_dir)
	{
		printf("/");
	}
	printf("\n");

	tinydir_next(&dir);
}

tinydir_close(&dir);
```

Language
========

ANSI C, or C90.

Platforms
=========

POSIX and Windows supported. Open to the possibility of supporting other platforms.

License
=======

BSD.

Known Limitations
=================

Not threadsafe
Limited path and filename sizes
No wide char support
