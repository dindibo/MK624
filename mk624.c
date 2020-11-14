#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define BUFFER_SIZE 1024
#define KILO        1000
//#define DEBUG

char *EXECUTABLE_NAME = "mk624";
char *RADIO_EXECUTABLE_NAME = "pi_fm_rds";

void print_usage(void){
    printf("%s channel audio_file\n\n\
channel - MK-624 channel (1-2320)\n\
audio_file - file path\n", EXECUTABLE_NAME);
}

float calcFrequency(int channel){
    static const int freqJump = 25;
    static const int minFreq = 30 * KILO;

    channel--;
    float temp = ((freqJump * channel) + minFreq) / 1000.0f;
    temp = roundy(temp, 3);

    return temp;
}

int main(int argc, char **argv){
    #ifndef DEBUG
    if(argc != 3){
        print_usage();
        exit(1);
    }

    int channel = atoi(argv[1]);

    if(!(channel >= 1 && channel <= 2320)){
        print_usage();
        exit(1);
    }

    float freq = calcFrequency(channel);
    char command[BUFFER_SIZE];

    sprintf(command, "./%s -freq %.2f -audio %s", RADIO_EXECUTABLE_NAME, freq, argv[2]);
    system(command);
    #endif

    return 0;
}
