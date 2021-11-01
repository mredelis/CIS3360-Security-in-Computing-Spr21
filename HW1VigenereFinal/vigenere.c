/*CIS 3360 Spr21 - Security in Computing
  Program #1 Vinegere Cipher
  C Program created by Edelis Molina
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


#define MAX 512 //Max number of plain text alphabetic characters


/* READ IN VIGENERE KEY */
void readKey(FILE *ifpKey, char *newKey)
{
  char key[MAX] = {0};
  int c = 0, i = 0;

  printf("\n\nVigenere Key:\n\n");

  // fgetc returns the character read as an unsigned char cast to an int or EOF on end of file or error.
  while((c = fgetc(ifpKey)) != EOF)
  {    
    if (isalpha(c)) // Only process alphabetic characters
    {
      key[i] = tolower(c);
      printf("%c", key[i]);
      i++;

      if(i % 80 == 0) // print 80 characters per line
        printf("\n");
    }     
  }
  
  /* New generated key */
  int y, z;

  for(y = 0, z = 0; y < MAX; y++, z++)
  {
    if(z == strlen(key))
      z = 0;
    newKey[y] = key[z]; 
  }
  
  newKey[y] = '\0';

}


/* READ IN PLAINTEXT */
void readPlainText(FILE *ifpText, char *plainText)
{
  int c = 0, i = 0;
  
  printf("\n\n\nPlaintext:\n");

  while((c = fgetc(ifpText)) != EOF)
  {
    if (isalpha(c))      // Only process alphabetic characters
    {
      plainText[i] = tolower(c);
      // printf("%c", plainText[i]);
      i++; 
    }  
  }    
      
  // Pad plain text with 'x' if number of alphabetic characters is less than 512
  int plainTextLenght = strlen(plainText);
  int temp = plainTextLenght;

  while(temp < MAX)
  {
    plainText[temp++] = 'x';
  }
  plainText[temp] = '\0'; // String Terminator

  for(i = 0; i < MAX; i++)
  {
    if(i % 80 == 0)
      printf("\n");
    printf("%c", plainText[i]);
  }
}

/* PRODUCE CYPHERTEXT */
void produceCypherText(char *key, char *text, char *cyText)
{
  int i;

  printf("\n\n\nCiphertext:\n");

  for(i = 0; i < MAX; i++)
  {
    cyText[i] = (((text[i] - 'a') + (key[i]) - 'a') % 26) + 'a';
    
    if(i % 80 == 0)
      printf("\n");
    printf("%c", cyText[i]);
  }
  cyText[i] = '\0';

  printf("\n");
}


/* MASTER OF CEREMONIES */
int main(int argc, char *argv[])
{
  char newKey[MAX];
  char plainText[MAX] = {0};
  char cypherText[MAX] = {0};


  if(argc != 3)     // check number of command-line arguments
    printf("Input format: executable keyFile plainTextFile\n");
  else
  {
    FILE *keyFilePtr;
    FILE *plainFilePtr;

    // try to open the input file
    if(((keyFilePtr = fopen(argv[1], "r")) != NULL) && ((plainFilePtr = fopen(argv[2], "r")) != NULL))
    {
      readKey(keyFilePtr, newKey);
      readPlainText(plainFilePtr, plainText);
      produceCypherText(newKey, plainText, cypherText); 

      fclose(keyFilePtr);
      fclose(plainFilePtr);
    }
    else{ // input file could not be opened
      printf("Key File or Plain Text File could not be opened\n");
    }     
  }
  return 0;
}