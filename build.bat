@echo off

arm-none-eabi-gcc -c code/main.cpp -mthumb-interwork -mthumb -O2 -o main.o
arm-none-eabi-gcc main.o -mthumb-interwork -mthumb -specs=gba.specs -o main.elf
arm-none-eabi-objcopy -v -O binary main.elf main.gba
gbafix main.gba
