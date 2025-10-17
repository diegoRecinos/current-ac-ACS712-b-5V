#include "ACS712.h"

// Parámetros del sensor ACS712-05B (5A)
// Pin analógico, Vref, ADC resolution, sensibilidad (mV/A)
ACS712 ACS(A0, 5.0, 1023, 185);  // Cambia A0 si usas otro pin
int calibration_factor = 0;       // Ajusta si quieres corregir offset en mA

void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println("=== Medición corriente AC con ACS712-05B ===");
}

void loop() {
  float current = readCurrent();
  Serial.print("Corriente AC RMS: ");
  Serial.print(current);
  Serial.println(" mA");

  delay(1000);
}

float readCurrent() {
  float average = 0;
  int muestras = 100;

  for (int i = 0; i < muestras; i++) {
    average += ACS.mA_AC();  // método de la librería que calcula AC RMS en mA
    delay(1);
  }

  float mA = (abs(average / muestras) - calibration_factor);
  if (mA <= 5) mA = 0;  // ruido mínimo ignorado

  // Debug
  Serial.print("Valor instantáneo promedio: ");
  Serial.print(mA);
  Serial.println(" mA");

  return mA;
}
