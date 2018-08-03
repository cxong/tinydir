
CFLAGS = -std=gnu99 -Wall -Wextra -pedantic -ggdb3 -O1
CFLAGSW2 = -fshort-wchar -DUSE_WCHAR2LIB -I../doxymd/lib/include
LDDFLAGSW2 = -L/home/admin/main_daemon/doxymd/lib/lib \
    -Wl,-rpath=/home/admin/main_daemon/doxymd/lib/lib \
    -lwchar2

all: clean exelibc exewchar2

exelibc:
	gcc $(CFLAGS) tinydir-test.c -o iterate_sample.libc

exewchar2:
	gcc $(CFLAGS) $(CFLAGSW2) $(LDDFLAGSW2) tinydir-test.c -o iterate_sample.wchar2

clean:
	@rm -f iterate_sample.libc iterate_sample.wchar2 ./core.*

.PHONY: clean exelibc exewchar2
