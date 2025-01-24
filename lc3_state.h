#progma once
#include <stdint.h>

#define MEMORY_SIZE 65539

typedef struct {
  uint16_t memory[MEMORY_SIZE];
  uint16_t reg[8];
  uint16_t pc;
  uint16_t psr;
} LC3State
