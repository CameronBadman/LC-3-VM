#include "./memory.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

uint16_t read_memory(const LC3State *state, uint16_t address) {
  return state->memory[address];
}

void write_memory(LC3State *state, uint16_t address, uint16_t value) {
  state->memory[address] = value;
}
void initialize_lc3state(LC3State *state) {
  memset(state->memory, 0, MEMORY_SIZE * sizeof(uint16_t)); // Clear memory
  memset(state->reg, 0, 8 * sizeof(uint16_t));              // Clear registers
  state->pc = 0;  // Initialize program counter
  state->psr = 0; // Initialize processor status register
}

int load_program(const char *filename, LC3State *state) {
  FILE *file = fopen(filename, "rb"); // Binary mode
  if (file == NULL) {
    printf("reading failed\n");
    return -1;
  }

  uint16_t origin;
  size_t read = fread(&origin, sizeof(uint16_t), 1, file);
  if (read != 1) {
    printf("Error: could not read address\n");
    fclose(file);
    return -1;
  }

  // Convert from big-endian
  origin = (origin >> 8) | (origin << 8);

  if (origin != 0x3000) {
    printf("Warning: Program origin 0x%04X differs from standard 0x3000\n",
           origin);
  }

  uint16_t current_addr = origin;
  uint16_t instruction;

  while (fread(&instruction, sizeof(uint16_t), 1, file) == 1) {
    if (current_addr >= 0xffff) {
      printf("Program is too big\n");
      fclose(file);
      return -1;
    }
    // Convert each instruction from big-endian
    instruction = (instruction >> 8) | (instruction << 8);
    printf("Loaded 0x%04X at address 0x%04X\n", instruction, current_addr);
    write_memory(state, current_addr, instruction);
    current_addr++;
  }

  fclose(file);
  return 0;
}
