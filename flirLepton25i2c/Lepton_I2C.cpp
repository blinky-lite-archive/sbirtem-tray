#include "Lepton_I2C.h"

#include "LEPTON_SDK.h"
#include "LEPTON_SYS.h"
#include "LEPTON_OEM.h"
#include "LEPTON_Types.h"
#include <cstdio>

bool _connected = false;

LEP_CAMERA_PORT_DESC_T _port;

int lepton_connect() {
	LEP_OpenPort(1, LEP_CCI_TWI, 400, &_port);
	_connected = true;
	return 0;
}

void lepton_perform_ffc() {
	if(!_connected) {
		lepton_connect();
	}
	LEP_RunSysFFCNormalization(&_port);
}

//presumably more commands could go here if desired

void lepton_reboot() {
	if(!_connected) {
		lepton_connect();
	}
	LEP_RunOemReboot(&_port);
}
int main( int argc, char **argv )
{
    LEP_FLOAT32 fpaTemperature;
    LEP_SYS_FFC_SHUTTER_MODE_OBJ_T shutterModeObj;
    printf("%s\n", "hello world!");
    lepton_connect();
    LEP_GetSysFpaTemperatureCelcius( &_port, &fpaTemperature );
    LEP_GetSysFfcShutterModeObj(  &_port, &shutterModeObj );
//    lepton_perform_ffc();
    printf("%s\n", "hello world again!");
    printf("fpaTemperature:          %f\n", fpaTemperature);
    printf("shutterMode:             %d\n", shutterModeObj.shutterMode);
    printf("tempLockoutState:        %d\n", shutterModeObj.tempLockoutState);
    printf("videoFreezeDuringFFC:    %d\n", shutterModeObj.videoFreezeDuringFFC);
    printf("ffcDesired:              %d\n", shutterModeObj.ffcDesired);
    printf("elapsedTimeSinceLastFfc: %d\n", shutterModeObj.elapsedTimeSinceLastFfc);
    printf("desiredFfcPeriod:        %d\n", shutterModeObj.desiredFfcPeriod);
    printf("explicitCmdToOpen:       %d\n", shutterModeObj.explicitCmdToOpen);
    printf("desiredFfcTempDelta:     %d\n", shutterModeObj.desiredFfcTempDelta);
    printf("imminentDelay:           %d\n", shutterModeObj.imminentDelay);
    printf("port:                    %d\n", _port);
    shutterModeObj.shutterMode = LEP_SYS_FFC_SHUTTER_MODE_MANUAL;
//    LEP_SetSysFfcShutterModeObj(  &_port, shutterModeObj );
    return 0;
}

