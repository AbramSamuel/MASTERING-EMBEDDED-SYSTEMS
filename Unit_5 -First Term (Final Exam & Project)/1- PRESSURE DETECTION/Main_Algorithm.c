#include "Main_Algorithm.h"
#include "Alarm_Monitor_Driver.h"
void (*P_Main_Algorithm)();

unsigned int Pressure_Value =0;
unsigned int Pressure_Threshold =20;

void WAITING()
{
    Pressure_Value = getPressureVal();
    (Pressure_Value > Pressure_Threshold) ? (P_Main_Algorithm = HIGH_PRESSURE_DETECTED) : (P_Main_Algorithm = WAITING);
}
void HIGH_PRESSURE_DETECTED()
{
        START_ALARM();
}