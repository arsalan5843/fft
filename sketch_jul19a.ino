#include <arduinoFFT.h>

#define SAMPLES 64          
#define SAMPLING_FREQUENCY 10000

arduinoFFT FFT = arduinoFFT();

unsigned int sampling_period_us;
unsigned long microseconds;

double vReal[SAMPLES];
double vImag[SAMPLES];

void setup() {
  Serial.begin(115200);

  sampling_period_us = round(1000000 * (1.0 / SAMPLING_FREQUENCY));
}

void loop() {

  /*SAMPLING*/
  for (int i = 0; i < SAMPLES; i++)
  {
    microseconds = micros();    //Overflows after around 70 minutes!

    vReal[i] = analogRead(0);
    vImag[i] = 0;

    while (micros() < (microseconds + sampling_period_us)) {
    }
  }

  /*FFT*/
  FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
  FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
  
  for (int i = 0; i < (SAMPLES / 2); i++)
  {

    Serial.print((i * 1.0 * SAMPLING_FREQUENCY) / SAMPLES, 1);
    Serial.print(" ");
    Serial.println(vReal[i], 1);   
  }

 delay(1000);  //Repeat the process every second
 
}
