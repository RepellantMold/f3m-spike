/*
 * F3M Spiked
 * originally made in 2015 by GreaseMonkey - Public Domain
 * forked by RepellantMold in 2023
 */
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <errno.h>

#include <assert.h>

#define MA_NO_DECODING
#define MA_NO_ENCODING
#define MA_DEBUG_OUTPUT
#define MA_NO_ENGINE
#define MA_NO_RESOURCE_MANAGER
#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

#define F3M_ENABLE_DYNALOAD
#define F3M_FREQ   48000
#include "f3m.c"

player_s player;
static int32_t mbuf[F3M_BUFLEN*F3M_CHNS];

static void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
{
	player.bufsize = frameCount;
	f3m_player_play(&player, (int32_t*)pDevice->pUserData, (ma_uint8*)pOutput);

	(void)pInput;
}

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;

	ma_device_config deviceConfig;
	ma_device device;

	deviceConfig = ma_device_config_init(ma_device_type_playback);
	deviceConfig.playback.format = ma_format_u8;
	deviceConfig.playback.channels = F3M_CHNS;
	deviceConfig.sampleRate = F3M_FREQ;
	deviceConfig.dataCallback = data_callback;
	deviceConfig.pUserData = &mbuf;

	assert(argc > 1);
	mod_s *mod = f3m_mod_dynaload_filename(argv[1]);
	f3m_player_init(&player, mod);

	if (ma_device_init(NULL, &deviceConfig, &device) != MA_SUCCESS) {
		printf("Failed to open playback device.\n");
		return -4;
	}

	if (ma_device_start(&device) != MA_SUCCESS) {
		printf("Failed to start playback device.\n");
		ma_device_uninit(&device);
		return -5;
	}

	player.bufsize = device.playback.internalPeriodSizeInFrames;

	for(;;)
	{
	}

	ma_device_uninit(&device);
	f3m_mod_free(mod);

	return 0;
}

