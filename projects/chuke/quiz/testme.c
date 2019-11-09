#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    //ascii 32 = ' ', lower bound of random character to generate
    int lower = 32;
    //ascii 125 = '}', upper bound of random character to generate
    int upper = 125;
    char random = (rand() % (upper - lower + 1)) + lower;
    return random;
}

char *inputString()
{
    char randomStr[6];
    int i;
    for(i = 0; i < 5; ++i) {
        //ascii 116 = 't', ascii 101 = 'e' which are the bounds of "reset"
        randomStr[i] = (rand() % (116 - 101 + 1)) + 101;
    }
    randomStr[5] = '\0';
    return randomStr;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
