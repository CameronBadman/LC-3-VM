#!/bin/bash

# Output executable name
EXECUTABLE="lc3_simulator"

# Compile the program
echo "Compiling..."
gcc main.c memory/memory.c -o $EXECUTABLE

# Check if compilation was successful
if [ $? -eq 0 ]; then
  echo "Compilation successful! Executable created: $EXECUTABLE"

  # Run the program if the "run" argument is provided
  if [ "$1" == "run" ]; then
    echo "Running the program..."
    ./$EXECUTABLE
  fi
else
  echo "Compilation failed."
  exit 1
fi
