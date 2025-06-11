#include "Arduino.h"
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

     pinMode(interruptPin, INPUT);
     attachInterrupt(digitalPinToInterrupt(interruptPin), OnOffSwitch, CHANGE);  
}

void loop() 
{
  ulTIMEread=micros();
  bAnyChannelActive=false;

//ALL POSITIVE HIGH TRANSITIONS HERE
  if ((bStartChannel1)&&((ulTIMEread-LastReadChannel1)>(1000*INTERVALS_Channel1[PositionChannel1])))
  {
    digital_write_direct(bytePosPinChannel1,HIGH);
    bAnyChannelActive=true;
  }
  if ((bStartChannel2)&&((ulTIMEread-LastReadChannel2)>(1000*INTERVALS_Channel2[PositionChannel2])))
  {
    digital_write_direct(bytePosPinChannel2,HIGH);
    bAnyChannelActive=true;
  }
  if ((bStartChannel3)&&((ulTIMEread-LastReadChannel3)>(1000*INTERVALS_Channel3[PositionChannel3])))
  {
    digital_write_direct(bytePosPinChannel3,HIGH);
    bAnyChannelActive=true;
  }
  if ((bStartChannel4)&&((ulTIMEread-LastReadChannel4)>(1000*INTERVALS_Channel4[PositionChannel4])))
  {
    digital_write_direct(bytePosPinChannel4,HIGH);
    bAnyChannelActive=true;
  }
  if ((bStartChannel5)&&((ulTIMEread-LastReadChannel5)>(1000*INTERVALS_Channel5[PositionChannel5])))
  {
    digital_write_direct(bytePosPinChannel5,HIGH);
    bAnyChannelActive=true;
  }

  if (bAnyChannelActive) delayMicroseconds(square_length_positive);

//ALL POSITIVE LOW TRANSITIONS HERE
  if ((bStartChannel1)&&((ulTIMEread-LastReadChannel1)>(1000*INTERVALS_Channel1[PositionChannel1])))
      digital_write_direct(bytePosPinChannel1,LOW);
  if ((bStartChannel2)&&((ulTIMEread-LastReadChannel2)>(1000*INTERVALS_Channel2[PositionChannel2])))
      digital_write_direct(bytePosPinChannel2,LOW);
  if ((bStartChannel3)&&((ulTIMEread-LastReadChannel3)>(1000*INTERVALS_Channel3[PositionChannel3])))
      digital_write_direct(bytePosPinChannel3,LOW);
  if ((bStartChannel4)&&((ulTIMEread-LastReadChannel4)>(1000*INTERVALS_Channel4[PositionChannel4])))
      digital_write_direct(bytePosPinChannel4,LOW);
  if ((bStartChannel5)&&((ulTIMEread-LastReadChannel5)>(1000*INTERVALS_Channel5[PositionChannel5])))
      digital_write_direct(bytePosPinChannel5,LOW);


  if (bAnyChannelActive) delayMicroseconds(square_interval);

//ALL NEGATIVE HIGH TRANSITIONS HERE
  if ((bStartChannel1)&&((ulTIMEread-LastReadChannel1)>(1000*INTERVALS_Channel1[PositionChannel1])))
    digital_write_direct(byteNegPinChannel1,HIGH);
  if ((bStartChannel2)&&((ulTIMEread-LastReadChannel2)>(1000*INTERVALS_Channel2[PositionChannel2])))
    digital_write_direct(byteNegPinChannel2,HIGH);
  if ((bStartChannel3)&&((ulTIMEread-LastReadChannel3)>(1000*INTERVALS_Channel3[PositionChannel3])))
    digital_write_direct(byteNegPinChannel3,HIGH);
  if ((bStartChannel4)&&((ulTIMEread-LastReadChannel4)>(1000*INTERVALS_Channel4[PositionChannel4])))
    digital_write_direct(byteNegPinChannel4,HIGH);
  if ((bStartChannel5)&&((ulTIMEread-LastReadChannel5)>(1000*INTERVALS_Channel5[PositionChannel5])))
    digital_write_direct(byteNegPinChannel5,HIGH);


  if (bAnyChannelActive) delayMicroseconds(square_length_negative);

//ALL NEGATIVE LOW TRANSITIONS HERE
  if ((bStartChannel1)&&((ulTIMEread-LastReadChannel1)>(1000*INTERVALS_Channel1[PositionChannel1])))
    {
      digital_write_direct(byteNegPinChannel1,LOW);
      PositionChannel1++;
      if(PositionChannel1>(SizeOfChannel1-1)) PositionChannel1=0;
      LastReadChannel1=ulTIMEread;
    }
if ((bStartChannel2)&&((ulTIMEread-LastReadChannel2)>(1000*INTERVALS_Channel2[PositionChannel2])))
    {
      digital_write_direct(byteNegPinChannel2,LOW);
      PositionChannel2++;
      if(PositionChannel2>(SizeOfChannel2-1)) PositionChannel2=0;
      LastReadChannel2=ulTIMEread;
    }      
if ((bStartChannel3)&&((ulTIMEread-LastReadChannel3)>(1000*INTERVALS_Channel3[PositionChannel3])))
    {
      digital_write_direct(byteNegPinChannel3,LOW);
      PositionChannel3++;
      if(PositionChannel3>(SizeOfChannel3-1)) PositionChannel3=0;
      LastReadChannel3=ulTIMEread;
    }
if ((bStartChannel4)&&((ulTIMEread-LastReadChannel4)>(1000*INTERVALS_Channel4[PositionChannel4])))
    {
      digital_write_direct(byteNegPinChannel4,LOW);
      PositionChannel4++;
      if(PositionChannel4>(SizeOfChannel4-1)) PositionChannel4=0;
      LastReadChannel4=ulTIMEread;
    }
if ((bStartChannel5)&&((ulTIMEread-LastReadChannel5)>(1000*INTERVALS_Channel5[PositionChannel5])))
    {
      digital_write_direct(byteNegPinChannel5,LOW);
      PositionChannel5++;
      if(PositionChannel5>(SizeOfChannel5-1)) PositionChannel5=0;
      LastReadChannel5=ulTIMEread;
    }
}



void OnOffSwitch() 
{
  if (digitalRead(interruptPin))
    {
      LastReadChannel1 = LastReadChannel2 = LastReadChannel3 = LastReadChannel4 = LastReadChannel5 = micros();

      start_stimulation();
    } else  {
            stop_stimulation();
            }
}




void start_stimulation()
{
  bStartChannel1=true;                           // Starts the thread
  bStartChannel2=false;                           // Starts the thread
  bStartChannel3=true;                           // Starts the thread
  bStartChannel4=false;                           // Starts the thread
  bStartChannel5=true;                           // Starts the thread
}


/*  STOP ACQUISITION
 *  This function stops the thread that will be in charge of making records at regular intervals
 */
void stop_stimulation()
{
  bStartChannel1=false;                           // Starts the thread
  bStartChannel2=false;                           // Starts the thread
  bStartChannel3=false;                           // Starts the thread
  bStartChannel4=false;                           // Starts the thread
  bStartChannel5=false;                           // Starts the thread
}

