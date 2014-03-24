// dsp2.h
// Josh Herzberg


#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/soundcard.h>

#include <math.h>


int dsp_fd;		// File descr for sound card; used by several functions
void dsp_open(char *dsp_name, int mode, int samp_fmt, int n_chan, int samp_rate);
void dsp_write(void *data, size_t samp_size, size_t n_samps);
void dsp_sync(void);
void dsp_close(void);
