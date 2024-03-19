@echo off

set CROSSPREFIX=arm-none-eabi-

%CROSSPREFIX%gcc -std=c11 -Wall -Wextra -Werror -O2 -nostdlib -march=armv4t -mtune=arm7tdmi -mthumb-interwork -T gba.ld -o player_gba.o head.S player_gba.c -lgcc
%CROSSPREFIX%objcopy -O binary player_gba.o player_gba.bin
%CROSSPREFIX%gcc -std=c11 -Wall -Wextra -Werror -O2 -nostdlib -march=armv4t -mtune=arm7tdmi -mthumb-interwork -T boot.ld -o gba_f3m.o boot.S
%CROSSPREFIX%objcopy -O binary gba_f3m.o gba_f3m.gba