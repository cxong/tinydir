#include <stdio.h>

#ifndef TINYDIR_H
#define _UNICODE
#include "tinydir.h"
#endif

int main(void) {

  FILE *fp;
  tinydir_dir dir;
  tinydir_open(&dir, TINYDIR_STRING("/path/to/dir"));

  fp = fopen("/file/to/output","wb");

#ifdef _WIN32
  char bom[] = "\xFF\xFE";
  fwrite(bom, 1, 2, fp);
#endif

  while (dir.has_next)
  {
    tinydir_file file;
    tinydir_readfile(&dir, &file);

    fwrite(file.name, sizeof(_tinydir_char_t), _tinydir_strlen(file.name), fp);
    if (file.is_dir)
    {
        fwrite(TINYDIR_STRING("/"), sizeof(_tinydir_char_t), _tinydir_strlen(TINYDIR_STRING("/")), fp);
    }
    fwrite(TINYDIR_STRING("\n"), sizeof(_tinydir_char_t), _tinydir_strlen(TINYDIR_STRING("/")), fp);

    tinydir_next(&dir);
  }

  tinydir_close(&dir);

  fclose(fp);

  return 0;
}
