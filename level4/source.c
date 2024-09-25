#include <stdio.h>
#include <stdlib.h>

int m = 0;

void p(char *buf) {
  // stack: 0 -> 24 [opti compilo?]
  printf(buf);
}

void n(void) {
  // stack: 0 -> 8 [opti compilo?]
  char buf[512]; // stack: 8 -> 520
  // stack: 520 -> 536 [opti compilo?]

  fgets(buf /* ebp-0x208 */, 512 /* 0x200 */, stdin /* ds:0x8049804 */);
  p(buf);
  if (m /* ds:0x8049804 */ == 16930116 /* 0x1025544 */) {
    system("/bin/cat /home/user/level5/.pass");
  }
}

void main(void) {
  n();
}