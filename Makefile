# change to your ARM compiler prefix
ARMCROSSPREFIX	= arm-none-eabi-

CFLAGS	= -std=c11 -Wall -Wextra -Werror
ARMCFLAGS	= -nostdlib -march=armv4t -mtune=arm7tdmi -mthumb-interwork

gba:
	$(ARMCROSSPREFIX)gcc $(CFLAGS) $(ARMCFLAGS) -O2 -T gba.ld -o player_gba.o head.S player_gba.c -lgcc
	$(ARMCROSSPREFIX)objcopy -O binary player_gba.o player_gba.bin
	$(ARMCROSSPREFIX)gcc $(CFLAGS) $(ARMCFLAGS) -Os -T boot.ld -o gba_f3m.o boot.S
	$(ARMCROSSPREFIX)objcopy -O binary gba_f3m.o gba_f3m.gba

oss: # linux only
	$(CC) $(CFLAGS) -o player_oss player_oss.c
	ls -l player_oss

ma:
	$(CC) $(CFLAGS) -o player_ma player_ma.c

all: gba oss ma

clean:
	rm -f gba_f3m.gba player_gba.bin player_gba.o player_oss player_ma