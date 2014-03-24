// JOSH Herzberg
// class: Kirtman, 2013
//
// For additional information, see:
// http://linuxdevcenter.com/pub/a/linux/2007/08/02/an-introduction-to-linux-audio.html
// or print version at:
// http://linuxdevcenter.com/lpt/a/7099

#include <stdio.h>
#include <stdlib.h>
#include "dsplib.h"
#include <math.h>

#define TEST_LEN 8000
#define TEST_FREQ 600
#define SAMP_RATE 48000
#define PI (3.14159265)

int freq(char num, int *phigh,int *plow);

int main()
{
	int	i,j, flow, fhigh, pause, newlen;
	int *plow, *phigh, whilecount = 0;
	char number;
	plow = &flow;
	phigh = &fhigh;

	printf("Please enter a phone number:\n");
	//begin the loop which will do each number separately:
	/*
	//alt. buffer method (replace "number" with "phonenum[j]", through code to implament:
	char phonenum[257];
	fgets(phonenum, 257, stdin);
	for (j=0;j < 256;j++)
	*/
	while((number = getchar()) != '\n' && whilecount < 256)
	{
		pause = freq(number,phigh, plow);
		//deal with pause length
		if (pause >0)
			newlen = SAMP_RATE*pause;
		else
			newlen = TEST_LEN;
		unsigned short shigh[newlen], slow[newlen], saverage[newlen];
		printf("%d. number= %c, fhigh =%d,  flow=%d\n",whilecount, number,fhigh,flow);
			
		// Open connection to the sound card
		dsp_open("/dev/dsp", O_WRONLY, AFMT_S16_NE, 1, SAMP_RATE);

		// Create sound
		for(i=0; i < newlen; i++)
		{
			slow[i] = 32767*sin(2.0*PI*flow*i/SAMP_RATE)/2;
			shigh[i] = 32767*sin(2.0*PI*fhigh*i/SAMP_RATE)/2;
			saverage[i]= (slow [i] + shigh[i]);
		}
		// Write the signal
		dsp_write(saverage, sizeof(short), newlen);

		// May be necessary to flush the buffers
		dsp_sync();

		// Close connection to the sound card
		dsp_close();
		
		whilecount++;
	}
	// Successful exit
	exit(0);
}

int freq(char num, int *phigh,int *plow)
{
	int fhigh, flow, pause=0;
	switch(num)
	{
		case '1':
			*phigh = 1209;
			*plow = 697;
			break;
		case '2':
			*phigh = 1336;
			*plow = 697;
			break;
		case '3':
			*phigh = 1477;
			*plow = 697;
			break;
		case '4':
			*phigh = 1209;
			*plow = 770;
			break;
		case '5':
			*phigh = 1336;
			*plow = 770;
			break;
		case '6':
			*phigh = 1477;
			*plow = 770;
			break;
		case '7':
			*phigh = 1209;
			*plow = 852;
			break;
		case '8':
			*phigh = 1336;
			*plow = 852;
			break;
		case '9':
			*phigh = 1477;
			*plow = 852;
			break;
		case '*':
			*phigh = 1209;
			*plow = 941;
			break;
		case '0':
			*phigh = 1336;
			*plow = 941;
			break;
		case '#':
			*phigh = 1477;
			*plow = 941;
			break;
		case 'a':
		case 'A':
			*phigh = 1633;
			*plow = 697;
			break;
		case 'b':
		case 'B':
			*phigh = 1633;
			*plow = 770;
			break;
		case 'c':
		case 'C':
			*phigh = 1633;
			*plow = 852;
			break;
		case 'd':
		case 'D':
			*phigh = 1633;
			*plow = 941;
			break;
		case 'p':
			*phigh = 0;
			*plow = 0;
			pause = 1;
			break;
		case 'P':
			*phigh = 0;
			*plow = 0;
			pause = 2;
			break;
		default:
			printf("Not valid number");
			exit(1);
			break;
	}
	return pause;
	}

