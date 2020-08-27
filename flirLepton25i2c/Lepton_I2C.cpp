#include "Lepton_I2C.h"

#include "LEPTON_SDK.h"
#include "LEPTON_SYS.h"
#include "LEPTON_OEM.h"
#include "LEPTON_Types.h"
#include <cstdio>
#include <cstring>

bool _connected = false;

LEP_CAMERA_PORT_DESC_T _port;

int connect() 
{
	LEP_OpenPort(1, LEP_CCI_TWI, 400, &_port);
	_connected = true;
	return 0;
}

void performFfc() 
{
	if(!_connected) connect();
	LEP_RunSysFFCNormalization(&_port);
}

void getShutterTemp()
{
	if(!_connected) connect();
    LEP_FLOAT32 fpaTemperature;
    LEP_GetSysFpaTemperatureCelcius( &_port, &fpaTemperature );
    printf("{fpaTemperature : %f}", fpaTemperature);
}
void getFfcState()
{
	if(!_connected) connect();
    LEP_SYS_FFC_SHUTTER_MODE_OBJ_T shutterModeObj;
    LEP_GetSysFfcShutterModeObj(  &_port, &shutterModeObj );
    printf("{shutterMode : %d, ", shutterModeObj.shutterMode);
    printf("tempLockoutState : %d, ", shutterModeObj.tempLockoutState);
    printf("videoFreezeDuringFFC : %d, ", shutterModeObj.videoFreezeDuringFFC);
    printf("ffcDesired : %d, ", shutterModeObj.ffcDesired);
    printf("elapsedTimeSinceLastFfc : %d, ", shutterModeObj.elapsedTimeSinceLastFfc);
    printf("desiredFfcPeriod : %d, ", shutterModeObj.desiredFfcPeriod);
    printf("explicitCmdToOpen : %d, ", shutterModeObj.explicitCmdToOpen);
    printf("desiredFfcTempDelta : %d, ", shutterModeObj.desiredFfcTempDelta);
    printf("imminentDelay :  %d}", shutterModeObj.imminentDelay);
}
void setFfcStateToManual()
{
	if(!_connected) connect();
    LEP_SYS_FFC_SHUTTER_MODE_OBJ_T shutterModeObj;
    LEP_GetSysFfcShutterModeObj(  &_port, &shutterModeObj );
    shutterModeObj.shutterMode = LEP_SYS_FFC_SHUTTER_MODE_MANUAL;
    LEP_SetSysFfcShutterModeObj(  &_port, shutterModeObj );
}
void reboot() 
{
	if(!_connected) connect();
	LEP_RunOemReboot(&_port);
}
int main( int argc, char **argv )
{
    if (argc != 2) return -1;
    if (strcmp(argv[1], "getShutterTemp") == 0) getShutterTemp();
    if (strcmp(argv[1], "getFfcState")    == 0) getFfcState();
    if (strcmp(argv[1], "reboot")         == 0) reboot();
    if (strcmp(argv[1], "performFfc")     == 0) performFfc();
    if (strcmp(argv[1], "setFfcStateToManual")     == 0) setFfcStateToManual();
    return 0;
}

