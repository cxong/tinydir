#pragma once

void make_temp_file(const char *prefix, char *out);
void make_temp_dir(const char *prefix, char *out);

#ifdef _MSC_VER
#include <direct.h>
#define mkdir(p, a) _mkdir(p)
#elif defined(_WIN32)
#define mkdir(p, a) mkdir(p)
#endif
