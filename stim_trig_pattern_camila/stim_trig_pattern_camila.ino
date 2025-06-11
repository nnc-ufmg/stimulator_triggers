#include "Arduino.h"
#include "DueTimer.h"
#include "STIMULADOR.h"


/*
 * Interrupt Numbers
 * 
 * BOARD INT.0 INT.1 INT.2 INT.3 INT.4 INT.5
 * Uno, Ethernet 2 3
 * Mega2560  2 3 21  20  19  18  
 * 32u4 based (e.g Leonardo, Micro)  3 2 0 1 7  
 * 
 */



void setup()
{
    for (int i = 0; i < NumberOfChannels; i++) 
      {
      pinMode(chpinP[i], OUTPUT);
      pinMode(chpinN[i], OUTPUT);
      digital_write_direct(chpinP[i], LOW);
      digital_write_direct(chpinN[i], LOW);
      }


    pinMode(synchronizationPin, OUTPUT);
    digital_write_direct(synchronizationPin, LOW);

     ulTIMElast = micros();
    
     pinMode(interruptPin, INPUT);
     attachInterrupt(digitalPinToInterrupt(interruptPin), OnOffSwitch, CHANGE);  
}

void loop() 
{
  ulTIMEread=micros();

  if (bStart)
    {

    }


}



void OnOffSwitch() 
{
  if (digitalRead(interruptPin))
    {
      ulTIMElast = micros();
      binWordMASK=1;
      binWordMASKTOP=1<<(ulWORDSIZE-1);
      uI_WordCount=0;
      bStart=true; 
      start_stimulation();
    } else  {
            bStart=false; 
            stop_stimulation();
            }
}




void start_stimulation()
{
  
  Timer4.attachInterrupt(stimulation_interrupt);    // Defines the interrupt/worker function for the thread
  
  Timer4.setPeriod(uint16_t (ulBinPeriod));          // Configures the Period of each bin

  Timer4.start();                                   // Starts the thread
}


/*  INTERRUPT FOR DATA STIMULATION
 *  This function will acquire the channels that are configured with high temporal priority
 */
void stimulation_interrupt()
{
  //noInterrupts();                                   // Locks any other interrupt on Arduino
  //First check if we are in-between Words.
  if (ulWORDrepetitionLAGcount>0) ulWORDrepetitionLAGcount--; //if it is grater than zero ... decrease it and leave
     else //We are within a word
      { 
        for (int i = 0; i < numberOfChannelsWORD; i++) 
          if (binWordMASK&chWORD[i][uI_WordCount]) //It is a 1 ... lets stim
              digital_write_direct(chpinP[i],HIGH);

              delayMicroseconds(square_length_positive);

        for (int i = 0; i < numberOfChannelsWORD; i++) 
          if (binWordMASK&chWORD[i][uI_WordCount]) //It is a 1 ... lets stim      
              digital_write_direct(chpinP[i],LOW);

              delayMicroseconds(square_interval);

        for (int i = 0; i < numberOfChannelsWORD; i++) 
          if (binWordMASK&chWORD[i][uI_WordCount]) //It is a 1 ... lets stim                    
              digital_write_direct(chpinN[i],HIGH);
              
              delayMicroseconds(square_length_negative);

        for (int i = 0; i < numberOfChannelsWORD; i++) 
          if (binWordMASK&chWORD[i][uI_WordCount]) //It is a 1 ... lets stim
              digital_write_direct(chpinN[i],LOW);
            
      if (binWordMASK==binWordMASKTOP) digital_write_direct(synchronizationPin,HIGH);

      binWordMASK=binWordMASK>>1; //Moving on to the next BIN 
      
      if (binWordMASK==0) // Unless the less bin is a Finished Word
        { 
          ulWORDrepetitionLAGcount=ulWORDrepetitionLAG;
          binWordMASK=binWordMASKTOP;
          uI_WordCount=uI_WordCount+1;
          if (uI_WordCount>uI_WordCountMAX) uI_WordCount=0; //Return to beggining if it ends
          digital_write_direct(synchronizationPin,LOW);
        }
      }
  //interrupts();                                     // Unlocks any other interrupt on Arduino
} 

/*  STOP ACQUISITION
 *  This function stops the thread that will be in charge of making records at regular intervals
 */
void stop_stimulation()
{
  Timer4.stop();                                    // Stops the thread
  digital_write_direct(synchronizationPin,LOW);
}

