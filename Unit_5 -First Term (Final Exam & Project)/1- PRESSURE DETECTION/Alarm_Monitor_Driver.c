#include "Alarm_Monitor_Driver.h"
#include "Main_Algorithm.h"

void (*P_Alarm_Monitor)();

void START_ALARM()
{
 
        Set_Alarm_actuator(1);
        Delay(300000);
        Set_Alarm_actuator(0);
        P_Alarm_Monitor = STOP_ALARM;

}

void STOP_ALARM()
{
    Set_Alarm_actuator(1);
}