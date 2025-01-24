#include "lc3_state.h"

uint16_t mem_read(LC3State *state, uint16_t address) {
  return state->memory[address];
}

void mem_write(LC3State *state, uint16_t address, uint16_t value) {
  state->memory[address] = value;
}
