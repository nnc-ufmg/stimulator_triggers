
#ifndef STIMULADOR_H
#define STIMULADOR_H

/* SERIAL DIGITAL WRITE   
 *  
 */
inline void digital_write_direct(int pin, boolean val){
  if(val) g_APinDescription[pin].pPort -> PIO_SODR = g_APinDescription[pin].ulPin;
  else    g_APinDescription[pin].pPort -> PIO_CODR = g_APinDescription[pin].ulPin;
}
/* SERIAL DIGITAL READ 
 *  
 */
inline int digital_read_direct(int pin){
  return !!(g_APinDescription[pin].pPort -> PIO_PDSR & g_APinDescription[pin].ulPin);
}


/* ALL FUNCTIONS
*/
extern void start_stimulation();
extern void stop_stimulation();
extern void OnOffSwitch();


/*
Setting definitions of variables to be used in the current version of this software
*/
const byte interruptPin = 21;             //This is the ON/OFF switch form the trigger
const byte synchronizationPin = 20;       //This is the pin synchronizing each word.
bool bAnyChannelActive=false;
unsigned long ulTIMEread;

// Settings to trigger the stimulator
unsigned long square_length_positive = 100;         // in microseconds
unsigned long square_length_negative = 100;         // in microseconds
unsigned long square_interval = 5;                  // in microseconds

// To test on osciloscope is better to increase the square length
//unsigned long square_length_positive = 1000;         // in microseconds
//unsigned long square_length_negative = 1000;         // in microseconds
//unsigned long square_interval = 5;                  // in microseconds

//DATA PER EACH CHANNEL

// Periodic
#define SizeOfChannel1 1
unsigned long INTERVALS_Channel1 [SizeOfChannel1]={
 500
};
unsigned long LastReadChannel1=0;
unsigned long PositionChannel1=0;
bool bStartChannel1=false;
const byte bytePosPinChannel1=2;
const byte byteNegPinChannel1=12;

// Non-Periodic - IH
#define SizeOfChannel2 1
unsigned long INTERVALS_Channel2 [SizeOfChannel2]={
  250
};
unsigned long LastReadChannel2=0;
unsigned long PositionChannel2=0;
bool bStartChannel2=false;
const byte bytePosPinChannel2=3;
const byte byteNegPinChannel2=13;

// Unorganized pattern (different words)
#define SizeOfChannel3 1
unsigned long INTERVALS_Channel3 [SizeOfChannel3]={
  166
};
unsigned long LastReadChannel3=0;
unsigned long PositionChannel3=0;
bool bStartChannel3=false;
const byte bytePosPinChannel3=4;
const byte byteNegPinChannel3=14;

// Organized pattern (same word)
#define SizeOfChannel4 4
unsigned long INTERVALS_Channel4 [SizeOfChannel4]={
 125
};  //553	1000101001
unsigned long LastReadChannel4=0;
unsigned long PositionChannel4=0;
bool bStartChannel4=false;
const byte bytePosPinChannel4=5;
const byte byteNegPinChannel4=15;

#define NumberOfChannels 8
static byte chpinP[NumberOfChannels] = {
  2,3,4,5,6,7,8,9
  };
static byte chpinN[NumberOfChannels] = {
  12,13,14,15,16,17,18,19
  };
#endif
