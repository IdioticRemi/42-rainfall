#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void m() {
  time(0 /* 0x0 */);
  printf("%s - %d\n" /* 0x80486e0 */, (char *) 0x8049960, 0x0 /* eax - 0x0 */);
}

void main(int argc, char *argv[]) {
  uint *esp_0x1c; // esp + 0x1c [4 bytes]
  uint *esp_0x18; // esp + 0x18 [4 bytes]

  esp_0x1c = malloc(8 /* 0x8 */); /* 0x804a008 */
  esp_0x1c[0] = 0x1; /* 0x1 */

  esp_0x1c[1] = (uint) malloc(8 /* 0x8 */); /* 0x804a018 */

  esp_0x18 = malloc(8 /* 0x8 */); /* 0x804a028 */
  esp_0x18[0] = 0x2; /* 0x2 */

  esp_0x18[1] = (uint) malloc(8 /* 0x8 */); /* 0x804a038 */

  strcpy((char *) esp_0x1c[1], argv[1]);
  strcpy((char *) esp_0x18[1], argv[2]);

  FILE *passfile = fopen("/home/user/level8/.pass" , "r");
  fgets((char *) 0x8049960, 68 /* 0x44 */, passfile);
  fputs("~~" /* 0x8048703 */, MISSING_ARGUMENT);
}

