
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
extern void stimulation_interrupt();
extern void stop_stimulation();
extern void OnOffSwitch();


/*
Setting definitions of variables to be used in the current version of this software
*/
const byte interruptPin = 21;             //This is the ON/OFF switch form the trigger
const byte synchronizationPin = 20;       //This is the pin synchronizing each word.


unsigned long square_length_positive = 100;         // in microseconds
unsigned long square_length_negative = 100;         // in microseconds
unsigned long square_interval = 5;                  // in microseconds


// unsigned long ulBinPeriod = 14000;                  // in microseconds (each word's binary number the period of the stimulation is ulBinPeriod x )
unsigned long ulBinPeriod = 10000;                  // in microseconds (each word's binary number the period of the stimulation is ulBinPeriod x )
unsigned long ulWORDSIZE = 10;                      // in number of Bins per word
unsigned long ulWORDrepetitionLAG = 10;             // if ZERO is continuous => if non zero, represents the number of SILENT BINS
unsigned long binWordMASK;                          // This is the logical mask for & with the WORD Currently beeing stimulated
unsigned long binWordMASKTOP;                       // MAX WORDMASK  i.e. 2ˆ10
unsigned long ulWORDrepetitionLAGcount=0;
int uI_WordCount=0;                                 // Which Word in the list
int uI_WordCountMAX=210;                            // Number of words to play (all possibilities to 10 bits word with more than 6 bits equal to one)

unsigned long ulTIMElast,ulTIMEread;


bool bStart=false;

#define numberOfChannelsWORD 2
#define numberOfWORDs 210
unsigned long  chWORD[numberOfChannelsWORD][numberOfWORDs] = {
{795,633,819,917,693,723,605,933,921,937,881,917,839,807,739,571,969,603,629,931,697,621,697,795,711,629,843,627,791,711,873,663,655,857,867,839,679,821,977,627,963,945,741,717,845,599,753,725,729,599,573,963,797,945,573,621,791,745,729,567,543,715,853,627,907,591,869,655,741,825,903,667,669,917,933,843,571,813,559,753,933,825,811,729,869,691,977,573,867,907,745,619,965,605,921,591,685,993,543,907,903,915,797,993,591,821,725,845,993,619,633,685,945,915,693,655,567,691,965,615,663,845,667,739,963,873,881,811,679,851,819,821,697,723,683,711,723,797,683,965,669,685,909,909,615,669,783,909,811,915,881,715,663,857,813,839,543,619,739,693,969,791,853,745,921,559,615,853,715,667,819,931,807,753,867,725,603,783,825,843,969,741,567,851,717,683,633,783,795,621,691,857,937,679,629,931,937,977,813,717,559,903,851,869,571,603,873,807,605,599},
{685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685,685}
};

//685	1010101101
//int b[ 2 ][ 2 ] = { { 1, 2 }, { 3, 4 } };

#define NumberOfChannels 8
static byte chpinP[NumberOfChannels] = {
  2,3,4,5,6,7,8,9
  };
static byte chpinN[NumberOfChannels] = {
  12,13,14,15,16,17,18,19
  };
#endif
