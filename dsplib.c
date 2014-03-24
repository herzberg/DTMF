// Sample sound card code for use with Cygwin etc.
// Stuart Kirtman, 2013
//
// For additional information, see:
// http://linuxdevcenter.com/pub/a/linux/2007/08/02/an-introduction-to-linux-audio.html
// or print version at:
// http://linuxdevcenter.com/lpt/a/7099

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/soundcard.h>
#include <math.h>
#include "dsplib.h"


int dsp_fd;		// File descr for sound card; used by several functions


void dsp_open(char *dsp_name, int mode, int samp_fmt, int n_chan, int samp_rate)
{
	int	arg;

	// Open the sound card
	if( (dsp_fd = open(dsp_name, mode)) < 0 )
	{
		printf("Cannot open sound card '%s'\n", dsp_name);
		exit(1);
	}


	// According to article cited above, settings should
	// take place in the following order...
	
	// Set sample format (num. of bits, little/big endian, encoding, etc.)
	arg = samp_fmt;
	if( ioctl(dsp_fd, SNDCTL_DSP_SETFMT, &arg) == -1 )
	{
		printf("Ioctl error setting sound card sample format\n");
		exit(1);
	}
	if( arg != samp_fmt )
	{
		printf("Sound card cannot be set to %d\n", samp_fmt);
		exit(1);
	}


	// Set number of channels (e.g. 1 (mono) or 2 (stereo))
	arg = n_chan;
	if( ioctl(dsp_fd, SNDCTL_DSP_CHANNELS, &arg) == -1 )
	{
		printf("Ioctl error setting number of channels\n");
		exit(1);
	}
	if( arg != n_chan )
	{
		printf("Could not set number of channels to %d\n", n_chan);
		exit(1);
	}


	// Set sample rate (num. of samps. per sec.)
	arg = samp_rate;
	if( ioctl(dsp_fd, SNDCTL_DSP_SPEED, &arg) == -1 )
	{
		printf("Ioctl error setting sample rate\n");
		exit(1);
	}
	if( arg != samp_rate )
	{
		printf("Could not set sample rate to %d\n", samp_rate);
		exit(1);
	}
}


void dsp_write(void *data, size_t samp_size, size_t n_samps)
{
	size_t	tmp;

	tmp = samp_size * n_samps;

	if( write(dsp_fd, data, tmp) != tmp )
	{
		printf("Write error\n");
		exit(1);
	}
}


void dsp_sync(void)
{
	int	tmp;

	tmp = 0;
	if( ioctl(dsp_fd, SNDCTL_DSP_SYNC, &tmp) == -1 )
	{
		printf("Ioctl error syncing dsp\n");
		exit(1);
	}
}


void dsp_close(void)
{
	if( close(dsp_fd) < 0 )
	{
		printf("Error closing sound card\n");
		exit(1);
	}
}


// Test program- plays a sine wave

#define TEST_LEN 96000
#define TEST_FREQ 600
#define SAMP_RATE 48000
#define PI (3.14159265)
