#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void n(void) {
  system("/bin/cat /home/user/level7/.pass");
}

void m(void) {
  puts("Nope");
}

void main(int argc, char *argv[]) {
  void *malloc1; // esp + 0x1c [4 bytes]
  void (**malloc2)(); // esp + 0x18 [4 bytes]

  malloc1 = malloc(64 /* 0x40 */);
  malloc2 = malloc(4 /* 0x4 */);

  *malloc2 = &m;

  strcpy(malloc1 /* esp + 0x18 */, argv[1] /* *(esp + 0x1c + 0x4) */);
  (*malloc2)();
}