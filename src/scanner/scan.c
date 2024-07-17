#include "scan.h"
#include "tokens.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define BASE_DECIMAL 10

void printldt(struct line_desc arr[], size_t length);
void printtokens(token_t *arr, size_t length);

static token_t *token_list;
static struct identifier_descriptor identifier_descriptor_table[TEMMA_MAX_VARIABLE_AMMOUNT];
static struct line_desc line_descriptor_table[TEMMA_DEFAULT_LINE_AMMOUNT_PER_FILE];
static char no_tokenized_values[TEMMA_DEFAULT_TOKEN_ARRAY_SIZE][TEMMA_DEFAULT_TOKEN_SIZE];
static int offset;

// Indexes
static int idti                  = 0;
static int tli                   = 0;
static int current_identifier_id = 0xFF;

static struct token_desc token_descriptor_table[] = {
  {TOKEN_VALUE_COMMENT, TOKEN_KW_COMMENT},
  {TOKEN_VALUE_DEF, TOKEN_KW_DEF},
  {TOKEN_VALUE_IF, TOKEN_KW_IF},
  {TOKEN_VALUE_END, TOKEN_KW_END},
  {TOKEN_VALUE_VAR, TOKEN_KW_VAR},
  
  {"", TOKEN_NULL}
};

void put_identifier(uint16_t identifier_type){
  if(current_identifier_id > TEMMA_MAX_VARIABLE_AMMOUNT){
    printf("MAXIMUM VARIABLE AMMOUNT REACHED PER FILE:");
    printf(" cannot insert more descriptors\n");
    printf("Exiting with error 1.");
    exit(1);
  }

  char *identifier = no_tokenized_values[offset];
  printf("Putting identifier '%s'\n", identifier);
  offset++;

  identifier_descriptor_table[idti].identifier_id = current_identifier_id;
  current_identifier_id++;

  // Set type of identifier
  identifier_descriptor_table[idti].type = identifier_type;
  idti++;

  token_list[tli] = identifier_type;
  tli++;
}

int set_tokens(struct line_desc line_descriptor)
{
  token_t current_token;
  // TODO: Not the best, but will work for now.
  //
  for(;offset<=line_descriptor.end;offset++)
  {
    int tdti = 0;
    while(token_descriptor_table[tdti].tkn != TOKEN_NULL)
    {
      printf("compare %s with %s\n", no_tokenized_values[offset], token_descriptor_table[tdti].value);
      if(strcmp(no_tokenized_values[offset], token_descriptor_table[tdti].value) == 0){
        
        if(token_descriptor_table[tdti].tkn == TOKEN_KW_COMMENT)
          goto out;

        token_list[tli] = token_descriptor_table[tdti].tkn;
        current_token = token_list[tli];
        printf("current value is %s\n", no_tokenized_values[offset]);
        tli++;
        tdti++;
        offset++;
        switch (current_token) {
          case TOKEN_KW_DEF:
            put_identifier(TOKEN_TYPE_FUNCTION);
            goto out;
            break;
          case TOKEN_KW_VAR:
            printf("Found var: ");
            char *str = no_tokenized_values[offset];
            printf("Allegded var type: %s\n", str);
            /*
             * If-else ladder, this is horrible, but cannot be worked out better for now
             * and I'm using C, so very valid. =)
             */
            if(strcmp(str, TOKEN_VALUE_DATA_INT)==0){
              put_identifier(TOKEN_TYPE_INT);
            }
            else if(strcmp(str, TOKEN_VALUE_DATA_STR)==0)
            {         
              put_identifier(TOKEN_TYPE_STR);
            }
            else if(strcmp(str, TOKEN_VALUE_DATA_BOOL)==0)
            {
              put_identifier(TOKEN_TYPE_BOOL);
            }
            else if(strcmp(str, TOKEN_VALUE_DATA_CHAR)==0)
            {
              put_identifier(TOKEN_TYPE_CHAR);
            }
            else if(strcmp(str, TOKEN_VALUE_DATA_ARRAY)==0)
            {
              put_identifier(TOKEN_TYPE_ARRAY);
            }
            goto out;
            break;
        }
      }
      tdti++;
    }
  }
out:
  return line_descriptor.end+1;
}

token_t* get_token_list_from_file(FILE *fp)
{
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
  token_list = (token_t*) malloc(sizeof(token_t) * num_words);
  // For each line descriptor determine line's type and 
  // tokens
  offset = 0;
  for(int i = 0; i < num_lines; i++)
  {
    offset = set_tokens(line_descriptor_table[i]);

    printf("offset: %d\n", offset);
  }


#ifdef DEBUG_MODE_FULL
  printldt(line_descriptor_table, num_lines);
  printf("num_lines: %zu\n", num_lines);
  printf("bytes_read: %zu\n", bytes_read);
  printf("num_words: %zu\n", num_words);
  printtokens(token_list, num_lines);
  for(int i = 0; i < idti+1; i++) {
    printf("IDENTIFIER%-6d\tID: %-6d\tTYPE: %-6d\n", i, identifier_descriptor_table[i].identifier_id, identifier_descriptor_table[i].type);
  }
#endif /* ifdef  DEBUG_MODE_FULL */

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

void printtokens(token_t *arr, size_t length){
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

