#ifndef CONFIG_H
#define CONFIG_H

// TEMMA_DEFAULT_TOKEN_ARRAY_SIZE describes the max length for a file 
// TEMMA_DEFAULT_TOKEN_SIZE is the maximum size for a token
// TEMMA_DEFAULT_LINE_AMMOUNT_PER_FILE is the maximum ammount of lines in a file 

#define TEMMA_DEFAULT_TOKEN_ARRAY_SIZE      8192 
#define TEMMA_DEFAULT_TOKEN_SIZE            64
#define TEMMA_DEFAULT_LINE_AMMOUNT_PER_FILE 512
#define TEMMA_MAX_VARIABLE_AMMOUNT          65280

#define TEMMA_VARIBALE_RANGE_START          0xFF
#define TEMMA_VARIBALE_RANGE_END            0xFFFF

#define BASE_DECIMAL                        0x0A
#define BASE_HEXADECIMAL                    0x10

#endif // !CONFIG_H
