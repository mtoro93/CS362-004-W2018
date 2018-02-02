#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

int checkForRepeat(int* indices, int length, int target);

char inputChar()
{	
	// generate random ascii values from 32 - 125 (upper and lower bound of our target chars)
	int asciiValue = rand() % 94;
	char randomChar = ' ' + asciiValue;
    return randomChar;
}

char *inputString()
{
	int i;
	int randomIndex = rand() % 5;
	int priorIndices[5];
	
	for (i = 0; i < 5; i++)
		priorIndices[i] = 999;
	
	// make a random anagram of reset
	char* targetString = "reset";
	char randomString[6];
	
	for (i = 0; i < 5; i++)
	{
		do
		{
			randomIndex = rand() % 5;
		}while(checkForRepeat(priorIndices, 5, randomIndex));
		
		priorIndices[i] = randomIndex;
		randomString[i] = targetString[randomIndex];
	}
	
	randomString[5] = '\0';
	
    return randomString;
}

// helper function to maintain uniqueness of indices
int checkForRepeat(int* indices, int length, int target)
{
	int i;
	for (i = 0; i < length; i++)
	{
		if (target == indices[i])
			return 1;
	}
	
	return 0;
	
	
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
