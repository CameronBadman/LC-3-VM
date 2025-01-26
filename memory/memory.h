#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>

#define MEMORY_SIZE 65536 // Size of the memory array

// LC3State struct definition
typedef struct {
  uint16_t memory[MEMORY_SIZE]; // Memory array
  uint16_t reg[8];              // Registers
  uint16_t pc;                  // Program counter
  uint16_t psr;                 // Processor status register
} LC3State;

// Function declarations
void initialize_lc3state(LC3State *state);
uint16_t read_memory(const LC3State *state, uint16_t address);
void write_memory(LC3State *state, uint16_t address, uint16_t value);
int load_program(const char *filename, LC3State *state);

#endif // MEMORY_H
