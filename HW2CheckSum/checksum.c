/*=============================================================================
| Assignment: HW 02 – Calculating the 8, 16, or 32 bit checksum for a
|             given input file
|
| Author: Edelis Molina
| Language: C
|
| To Compile: gcc checksum.c
|
| To Execute: ./checksum inputTextFile.txt checkSumSize (single integer, allowed values of 8, 16 or 32)
|              where the files in the command line are in the current directory.
|
|              The text file contains text is mixed case with spaces, punctuation,
|              and is terminated by the hexadecimal ‘0A’, inclusive.
|              (The 0x’0A’ is included in the checksum calculation.)
|
|              The checksum_checkSumSize contains digit(s) expressing the checksum checkSumSize
|              of either 8, 16, or 32 bits
|
| Class: CIS3360 - Security in Computing – Spring 2021
| Instructor: McAlpin
| Due Date: April 04, 2021
|
+=============================================================================*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE_MAX 1024

// Function prototypes
unsigned long int checksum8(char *charArray);
unsigned long int checksum16(char *charArray);
unsigned long int checksum32(char *charArray);


/* MASTER OF CEREMONIES */
int main(int argc, char *argv[])
{
  char charArray[SIZE_MAX] = {0};
  int checkSumSize;           // checksum checkSumSize in bits. Valid values, 8, 16, 32
  int characterCount = 0;     // number of characters
  unsigned long int checksum;
  FILE *ifp;
  FILE *ofp;
  
  
  if(argc != 3)     // check number of command-line arguments
    printf("Input format: executable fileName checkSumSize(8, 16, 32 bits)\n");
  else
  {
      checkSumSize = atoi(argv[2]);
      
      if(checkSumSize == 8 || checkSumSize == 16 || checkSumSize == 32)
      {
        ifp = fopen(argv[1], "r");

        if(ifp == NULL) //error opening text file
        {
          printf("Error opening input file.\n");
          return(-1);
        }
        else 
        {
          ofp = fopen("out.txt", "w");
          // Read in a line of text including NEWLINE character
          fgets(charArray, SIZE_MAX - 1, ifp);
          // printf("\nAfter reading\n%s\n", charArray);

          switch(checkSumSize){
            case 8:
              checksum = checksum8(charArray);
              break;
            case 16:
              checksum = checksum16(charArray);
              break;
            case 32:
              checksum = checksum32(charArray);
              break;
          } // end of switch

          characterCount = strlen(charArray);
          // The echoed input text read is in rows of 80 characters
          // printf("\nAfter processing");
          for(int i = 0; i < characterCount; i++)
          {
            // Print new line after 80 characters
            if(i % 80 == 0)
            {
              printf("\n");
              fprintf(ofp, "\n");
            }      
            printf("%c", charArray[i]);  
            fprintf(ofp, "%c", charArray[i]); 
          }
          printf("\n");
          fprintf(ofp, "\n");

          printf("%2d bit checksum is %8lx for all %4d chars\n", checkSumSize, checksum, characterCount);
          fprintf(ofp, "%2d bit checksum is %8lx for all %4d chars\n", checkSumSize, checksum, characterCount);

          fclose(ifp);
          fclose(ofp);
        }

      }
      else{
        printf("Valid checksum checkSumSizes are 8, 16, or 32\n");
        fprintf(stderr,"Valid checksum checkSumSizes are 8, 16, or 32\n"); //STDERR standar error
      }

  }

  return 0;
}


/* Returns 8 bits checksum */
unsigned long int checksum8(char *charArray)
{
  unsigned long int checkSum = 0;

  int i = 0;
  while(charArray[i] != '\0')
  {
    // printf("i = %d char = %c\n", i, charArray[i]);
    checkSum += charArray[i++];
  }

  checkSum %= 256; // 2^8

  return checkSum;
}


/* Returns 16 bits checksum */
unsigned long int checksum16(char *charArray)
{
  unsigned long int checkSum = 0;

  int cCount = strlen(charArray);
  unsigned long int val;

  if((cCount % 2) != 0) // pad with 'X' after '\n' char
  {
    charArray[cCount++] = 'X';
    charArray[cCount] = '\0';
  }

  for(int i = 0; i < cCount; i += 2)
  {
    val = (charArray[i] << 8) + charArray[i + 1];
    // printf("Hex.....%lx\n", val);
    checkSum += val;
  }

  checkSum %= 65536; // 2^16 

  return checkSum;
}


/* Returns 32 bits checksum */
unsigned long int checksum32(char *charArray)
{
  unsigned long int checkSum = 0;

  int cCount = strlen(charArray);
  unsigned long int val;

  // pad with 'X' after '\n' char until cCount % 4 == 0
  while((cCount % 4) != 0)
    charArray[cCount++] = 'X';

  charArray[cCount] = '\0';

  for(int i = 0; i < cCount; i += 4)
  {
    val = (charArray[i] << 24) + (charArray[i + 1] << 16) + (charArray[i + 2] << 8) + charArray[i + 3];
    // printf("Hex.....%lx\n", val);
    checkSum += val;
  }

  checkSum %= 4294967296; // 2^32 

  return checkSum;
}



/*=============================================================================
| I Edelis Molina (ed293125) affirm that this program is
| entirely my own work and that I have neither developed my code together with
| any another person, nor copied any code from any other person, nor permitted
| my code to be copied or otherwise used by any other person, nor have I
| copied, modified, or otherwise used programs created by others. I acknowledge
| that any violation of the above terms will be treated as academic dishonesty.
+=============================================================================*/