/**
   @file comments.c
   @author Louis Warner (elwarner)
   A program for counting the number of characters, comments, and comment
   characters in an input file. Prints information to standard output about
   the file.
 */
#include <stdio.h>
#include <stdlib.h>

/** Total count of characters. */
int totalChars = 0;

/** Total count of characters that are part of a comment. */
int commentChars = 0;

/** Total number of comments in the input. */
int commentCount = 0;

/** Placeholders for the characters being read from the file */
int current = 0;
int last = 0;

/**
   Performs steps for processing characters that are part of a comment.
*/
void processComment()
{
  //Lightswitch is set to 1 to prevent the first character of a comment from closing the comment
  int lightswitch = 1;
  
  //Increase commentCount and include the first two comment characters in the commentChars count.
  commentCount++;
  commentChars += 2;
  
  //Continually read characters from file
  while(current != EOF){
    last = current;
    current = getchar();
    totalChars++;
    commentChars++;
    
    //Returns Error if file terminates mid-comment 
    if(current == EOF){
      printf("Unterminated comment\n");
      exit(101);
    }
   
    //Returns to main at the end of the comment
    if(lightswitch == 0 && current == 47 && last == 42){
      return;
    }
    
    lightswitch = 0;
  }
}

/**
   Starting point for the program, holds main cycle for reading characters in the file
   and code to pass to processComment if a comment is found. Prints information about the
   file to standard output.
 */
int main()
{  
  current = getchar();
  
  //Returns Error if file has no input
  if(current == EOF){
    printf("Empty input\n");
    exit(100);
  }
  
  //Continually read characters from file  
  while(current != EOF){
    last = current;
    current = getchar();
    totalChars++;
    
    //Sends to process comment if a comment is opened
    if(last == 47 && current == 42){
      processComment();
    }
  }
  
  //Variable for the percentage of characters that are comment characters
  double percentage = (double) commentChars / (double) totalChars * 100;
  
  //The printed output
  printf("Input characters: %d\n", totalChars);
  printf("Comments: %d (%.2f%)\n", commentCount, percentage);
  
  //Successful return
  exit(0);
}