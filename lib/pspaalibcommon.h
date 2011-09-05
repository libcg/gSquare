////////////////////////////////////////////////
//
//		pspaalibcommon.h
//		Part of the PSP Advanced Audio Library
//		Created by Arshia001
//
//		This file includes constant declarations for the
//		PSPAALIB.
//
////////////////////////////////////////////////

#ifndef _PSPAALIBCOMMON_H_
#define _PSPAALIBCOMMON_H_

#include <pspkernel.h>
#include <psputility.h>
#include <pspaudio.h>
#include <string.h>
#include <malloc.h>
#include <limits.h>
#include <math.h>
#include <pspmp3.h>
#include <pspatrac3.h>
#include <tremor/ivorbiscodec.h>
#include <tremor/ivorbisfile.h>

#define bool int
#define FALSE 0
#define TRUE !FALSE

#define PI 3.14159f

#define PSP_SAMPLE_RATE 44100
#define PSPAALIB_HW_CHANNELS 4

#define PSPAALIB_CHANNEL_NONE 0
#define PSPAALIB_CHANNEL_SCEMP3_1 1
#define PSPAALIB_CHANNEL_SCEMP3_2 2

#define PSPAALIB_CHANNEL_AT3_1 5
#define PSPAALIB_CHANNEL_AT3_2 6
#define PSPAALIB_CHANNEL_OGG_1 7
#define PSPAALIB_CHANNEL_OGG_2 8
#define PSPAALIB_CHANNEL_OGG_3 9
#define PSPAALIB_CHANNEL_OGG_4 10
#define PSPAALIB_CHANNEL_OGG_5 11
#define PSPAALIB_CHANNEL_OGG_6 12
#define PSPAALIB_CHANNEL_OGG_7 13
#define PSPAALIB_CHANNEL_OGG_8 14
#define PSPAALIB_CHANNEL_OGG_9 15
#define PSPAALIB_CHANNEL_OGG_10 16
#define PSPAALIB_CHANNEL_WAV_1 17
#define PSPAALIB_CHANNEL_WAV_2 18
#define PSPAALIB_CHANNEL_WAV_3 19
#define PSPAALIB_CHANNEL_WAV_4 20
#define PSPAALIB_CHANNEL_WAV_5 21
#define PSPAALIB_CHANNEL_WAV_6 22
#define PSPAALIB_CHANNEL_WAV_7 23
#define PSPAALIB_CHANNEL_WAV_8 24
#define PSPAALIB_CHANNEL_WAV_9 25
#define PSPAALIB_CHANNEL_WAV_10 26
#define PSPAALIB_CHANNEL_WAV_11 27
#define PSPAALIB_CHANNEL_WAV_12 28
#define PSPAALIB_CHANNEL_WAV_13 29
#define PSPAALIB_CHANNEL_WAV_14 30
#define PSPAALIB_CHANNEL_WAV_15 31
#define PSPAALIB_CHANNEL_WAV_16 32
#define PSPAALIB_CHANNEL_WAV_17 33
#define PSPAALIB_CHANNEL_WAV_18 34
#define PSPAALIB_CHANNEL_WAV_19 35
#define PSPAALIB_CHANNEL_WAV_20 36
#define PSPAALIB_CHANNEL_WAV_21 37
#define PSPAALIB_CHANNEL_WAV_22 38
#define PSPAALIB_CHANNEL_WAV_23 39
#define PSPAALIB_CHANNEL_WAV_24 40
#define PSPAALIB_CHANNEL_WAV_25 41
#define PSPAALIB_CHANNEL_WAV_26 42
#define PSPAALIB_CHANNEL_WAV_27 43
#define PSPAALIB_CHANNEL_WAV_28 44
#define PSPAALIB_CHANNEL_WAV_29 45
#define PSPAALIB_CHANNEL_WAV_30 46
#define PSPAALIB_CHANNEL_WAV_31 47
#define PSPAALIB_CHANNEL_WAV_32 48

#define PSPAALIB_EFFECT_MIX 0
#define PSPAALIB_EFFECT_PLAYSPEED 1
#define PSPAALIB_EFFECT_STEREO_BY_POSITION 2
#define PSPAALIB_EFFECT_DOPPLER 3
#define PSPAALIB_EFFECT_STRENGTH_BY_POSITION 4
#define PSPAALIB_EFFECT_VOLUME_MANUAL 5
#define PSPAALIB_EFFECT_AMPLIFY 6

#define PSPAALIB_STOP_NOT_STOPPED 0
#define PSPAALIB_STOP_END_OF_STREAM -1
#define PSPAALIB_STOP_ON_REQUEST -2
#define PSPAALIB_STOP_JUST_LOADED -3
#define PSPAALIB_STOP_UNLOADED -4

#define PSPAALIB_STATUS_STOPPED -1
#define PSPAALIB_STATUS_PAUSED -2
#define PSPAALIB_STATUS_PLAYING -3

#define PSPAALIB_SUCCESS 0

#define PSPAALIB_WARNING_WAV_INVALID_SBPS -7

#define PSPAALIB_WARNING_CREATE_THREAD -6
#define PSPAALIB_WARNING_NO_FREE_CHANNELS -5

#define PSPAALIB_WARNING_END_OF_STREAM_REACHED -2
#define PSPAALIB_WARNING_PAUSED_BUFFER_REQUESTED -1

#define PSPAALIB_ERROR_INVALID_CHANNEL 1
#define PSPAALIB_ERROR_UNINITIALIZED_CHANNEL 2
#define PSPAALIB_ERROR_INVALID_EFFECT 3
#define PSPAALIB_ERROR_INVALID_AMPLIFICATION_VALUE 4

#define PSPAALIB_ERROR_WAV_INVALID_CHANNEL 11
#define PSPAALIB_ERROR_WAV_INVALID_FILE 12
#define PSPAALIB_ERROR_WAV_COMPRESSED_FILE 13
#define PSPAALIB_ERROR_WAV_INVALID_SEEK_TIME 14
#define PSPAALIB_ERROR_WAV_UNINITIALIZED_CHANNEL 15
#define PSPAALIB_ERROR_WAV_INSUFFICIENT_RAM 16

#define PSPAALIB_ERROR_SCEMP3_INVALID_CHANNEL 21
#define PSPAALIB_ERROR_SCEMP3_INIT 22
#define PSPAALIB_ERROR_SCEMP3_INIT_RESOURCE 23
#define PSPAALIB_ERROR_SCEMP3_RESERVE_HANDLE 24
#define PSPAALIB_ERROR_SCEMP3_INVALID_FILE 25
#define PSPAALIB_ERROR_SCEMP3_UNINITIALIZED_CHANNEL 26

#define PSPAALIB_ERROR_OGG_INVALID_FILE 41
#define PSPAALIB_ERROR_OGG_OPEN_CALLBACKS 42
#define PSPAALIB_ERROR_OGG_INVALID_CHANNEL 43
#define PSPAALIB_ERROR_OGG_UNINITIALIZED_CHANNEL 44
#define PSPAALIB_ERROR_OGG_INSUFFICIENT_RAM 45

#define PSPAALIB_ERROR_AT3_INVALID_FILE 51
#define PSPAALIB_ERROR_AT3_INVALID_CHANNEL 52
#define PSPAALIB_ERROR_AT3_UNINITIALIZED_CHANNEL 53
#define PSPAALIB_ERROR_AT3_INSUFFICIENT_RAM 54
#define PSPAALIB_ERROR_AT3_GET_ID 55

#define MAXA(A,B) ((A>B)?(A):(B))
#define MINA(A,B) ((A<B)?(A):(B))

typedef struct
{
	float left;
	float right;
} AalibVolume;

#endif
