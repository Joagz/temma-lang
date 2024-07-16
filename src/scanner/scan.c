#include "scan.h"
#include "tokens.h"
#include <stdio.h>
#include <string.h>

void printldt(struct line_desc arr[], size_t length);
void printtokens(unsigned int *arr, size_t length);

  static struct token_desc token_descriptor_table[] = {
  {TOKEN_VALUE_DEF, TOKEN_KW_DEF},
  {TOKEN_VALUE_IF, TOKEN_KW_IF},
  {TOKEN_VALUE_END, TOKEN_KW_END},
  {TOKEN_VALUE_COMMENT, TOKEN_KW_COMMENT},

  {"", TOKEN_NULL}
};

int set_tokens(struct line_desc line_descriptor_table, char *no_tokenized_values[TEMMA_DEFAULT_TOKEN_ARRAY_SIZE], token_t *token_list, int offset)
{
  int k = line_descriptor_table.start;
  int i = offset;

  for(;k<=line_descriptor_table.end;k++)
  {
    int l = 0;
    while(token_descriptor_table[l].tkn != TOKEN_NULL)
    {
      if(strcmp(no_tokenized_values[k], token_descriptor_table[l].value) == 0){

        token_list[i] = token_descriptor_table[l].tkn;
        i++;
      }
      l++;
    }
  }

  return i;
}

token_t* get_token_list_from_file(FILE *fp)
{
  struct line_desc line_descriptor_table[TEMMA_DEFAULT_LINE_AMMOUNT_PER_FILE];

  char *no_tokenized_values[TEMMA_DEFAULT_TOKEN_ARRAY_SIZE];
  for(int k = 0; k < TEMMA_DEFAULT_TOKEN_ARRAY_SIZE; k++)
  {
    no_tokenized_values[k] = (char*)malloc(sizeof(char) * TEMMA_DEFAULT_TOKEN_SIZE);
  }

  char *cur_word    = (char*) malloc(sizeof(char) * TEMMA_DEFAULT_TOKEN_SIZE);
  char c            = 0;
  size_t num_lines  = 0;
  size_t num_words  = 0;
  size_t bytes_read = 0;
  size_t k          = 0;
  size_t ldsi       = 0;
  memset(cur_word, 0, sizeof(char) * TEMMA_DEFAULT_TOKEN_SIZE);

  while((c=getc(fp)) > 0)
  {
    bytes_read++;

    // Ignore empty lines
    if(c == '\n' && k == 0)
      continue;

    if(c == '\n' && k > 0)
    {
      strncpy(no_tokenized_values[num_words], cur_word, k);
      k=0;

      line_descriptor_table[num_lines].end=num_words;

      ldsi++;
      num_words++;

      line_descriptor_table[num_lines].start=num_words-ldsi;

      num_lines++;    
      ldsi = 0;
      continue;
    }

    if(c == ' ')
    {
      strncpy(no_tokenized_values[num_words], cur_word, k);
      k=0;

      num_words++;
      ldsi++;
      continue;
    }

    cur_word[k] = c;
    k++;
  }

  // TODO: this will not be optimized because a good part of the words of a file 
  // could be just comments. However is better than having a default size.
  token_t *token_list = (token_t*) malloc(sizeof(token_t) * num_words);

  // For each line descriptor determine line's type and 
  // tokens
  int offset = 0;
  for(int i = 0; i < num_lines; i++)
  {
    offset = set_tokens(line_descriptor_table[i], no_tokenized_values, token_list, offset);
  }


#ifdef DEBUG_MODE_FULL
  printldt(line_descriptor_table, num_lines);
  printf("num_lines: %zu\n", num_lines);
  printf("bytes_read: %zu\n", bytes_read);
  printf("num_words: %zu\n", num_words);
  printtokens(token_list, num_lines);
#endif /* ifdef  DEBUG_MODE_ON */

  for(int k = 0; k < TEMMA_DEFAULT_TOKEN_ARRAY_SIZE; k++)
    free(no_tokenized_values[k]); 

  return 0;
}

int scan_file_list(char *farr[], size_t farr_length)
{

  for(int i = 0; i < farr_length; i++)
  {
    char *filename = farr[i];

    FILE *fp = fopen(filename, "r+");

    token_t * tokens = get_token_list_from_file(fp);

    fclose(fp); 
  }

  return 0; 
}











/* ########### UTILITY FUNCTIONS ########### */

void printldt(struct line_desc arr[], size_t length)
{
  printf("%-5s\n", "LINE DESCRIPTOR TABLE");
  for(int i = 0; i < length; i++)
  {
    printf("DESC%-3d\tSTART=%-3zu\tEND=%-3zu\n", i, arr[i].start, arr[i].end);
  }
}

void printtokens(unsigned int *arr, size_t length){
  for(int i = 0; i < length; i++)
  {
    int k = 0;
    while(token_descriptor_table[k].tkn != TOKEN_NULL) {
      if(token_descriptor_table[k].tkn == arr[i])
        printf("%s\n",token_descriptor_table[k].value);
      k++;
    }
  }
}
/* ########### END OF UTILITY FUNCTIONS ########### */

