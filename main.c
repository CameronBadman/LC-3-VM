#include <stdint.h>
#include <stdio.h>

uint16_t memory[65536] = {0};

int load_program(const char *filename, uint16_t *memory) {
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
    memory[current_addr] = instruction;
    printf("Loaded 0x%04X at address 0x%04X\n", instruction, current_addr);

    current_addr++;
  }

  fclose(file);
  return 0;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: %s <program.obj>\n", argv[0]);
    return 1;
  }

  if (load_program(argv[1], memory) == 0) {
    printf("Program loaded successfully\n");
  }
  return 0;
}
