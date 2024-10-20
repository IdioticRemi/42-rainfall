#include <stdio.h>
#include <string.h>
#include <unistd.h>

void p(char str[20], const char idk[4]) {
  char unknown[14];
  char stack[4096];

  puts(idk);
  read(0, stack, 4096);
  strchr(stack, '\n')[0] = 0;
  strncpy(str, stack, 20);
}

void pp(char result[42]) {
  char unknown[8];
  char str2[20];
  char str1[20];
  char unknown2[8];
  int i;
  char unknown3[20];

  p(str1, " - ");
  p(str2, " - ");

  strcpy(result, str1);

  i = 0; // i = strlen(result)
  while (result[i] != 0) {
    i++;
  }

  result[i] = ' ';
  result[i + 1] = '\0';
  strcat(result, str2);
}

int main() {
  char result[42];
  char unknown[22];

  pp(result);
  puts(result);
}