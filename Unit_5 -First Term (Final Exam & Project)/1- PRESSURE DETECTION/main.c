#include "Alarm_Monitor_Driver.h"
#include "Main_Algorithm.h"
#include "driver.h"

#include <stdint.h>
#include <stdio.h>

int main (){
	GPIO_INITIALIZATION();
	P_Alarm_Monitor = STOP_ALARM;
	P_Main_Algorithm = WAITING;

	while (1)
	{
		WAITING();
			P_Alarm_Monitor();
			P_Main_Algorithm();
			Delay(300000);
		

	}
}
