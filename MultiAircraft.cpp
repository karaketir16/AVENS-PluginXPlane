#include "MultiAircraft.h"
#include "UserAircraft.h"
#include <string>
#include "XPLMUtilities.h"


MultiAircraft::MultiAircraft(int iAircraftNumber)
{
	char cAuxString[80];
	char cAircraftNumber = iAircraftNumber + 0x30;

	this->iAircraftNumber = iAircraftNumber;

	strcpy(cAuxString, "sim/multiplayer/position/planeX_x");
	cAuxString[30] = cAircraftNumber; // Number to ASCII
	this->vFindXPositionDataRef(cAuxString);
	XPLMDebugString(cAuxString);
	XPLMDebugString("\n");
	strcpy(cAuxString,	"sim/multiplayer/position/planeX_y");
	cAuxString[30] = cAircraftNumber; // Number to ASCII
	this->vFindYPositionDataRef(cAuxString);
	XPLMDebugString(cAuxString);
	XPLMDebugString("\n");
	strcpy(cAuxString,	"sim/multiplayer/position/planeX_z");
	cAuxString[30] = cAircraftNumber; // Number to ASCII
	this->vFindZPositionDataRef(cAuxString);
	XPLMDebugString(cAuxString);
	XPLMDebugString("\n");
	strcpy(cAuxString,	"sim/multiplayer/position/planeX_the");
	cAuxString[30] = cAircraftNumber; // Number to ASCII
	this->vFindThetaAngleDataRef(cAuxString);
	XPLMDebugString(cAuxString);
	XPLMDebugString("\n");
	strcpy(cAuxString,	"sim/multiplayer/position/planeX_phi");
	cAuxString[30] = cAircraftNumber; // Number to ASCII
	this->vFindPhiAngleDataRef(cAuxString);
	XPLMDebugString(cAuxString);
	XPLMDebugString("\n");
	strcpy(cAuxString,	"sim/multiplayer/position/planeX_psi");
	cAuxString[30] = cAircraftNumber; // Number to ASCII
	this->vFindPsiAngleDataRef(cAuxString);
	XPLMDebugString(cAuxString);
	XPLMDebugString("\n");
	strcpy(cAuxString,	"sim/multiplayer/position/planeX_gear_deploy");
	cAuxString[30] = cAircraftNumber; // Number to ASCII
	this->xGearDeployDataRef = XPLMFindDataRef(cAuxString);
	XPLMDebugString(cAuxString);
	XPLMDebugString("\n");
	strcpy(cAuxString, "sim/multiplayer/position/planeX_throttle");
	cAuxString[30] = cAircraftNumber; // Number to ASCII
	this->xThrottleDataRef = XPLMFindDataRef(cAuxString);
	XPLMDebugString(cAuxString);
	XPLMDebugString("\n");
	strcpy(cAuxString, "sim/multiplayer/position/planeX_lat");
	cAuxString[30] = cAircraftNumber; // Number to ASCII
	this->vFindLatitudeDataRef(cAuxString);
	XPLMDebugString(cAuxString);
	XPLMDebugString("\n");
	strcpy(cAuxString, "sim/multiplayer/position/planeX_lon");
	cAuxString[30] = cAircraftNumber; // Number to ASCII
	this->vFindLongitudeDataRef(cAuxString);
	XPLMDebugString(cAuxString);
	XPLMDebugString("\n");
	strcpy(cAuxString, "sim/multiplayer/position/planeX_el");
	cAuxString[30] = cAircraftNumber; // Number to ASCII
	this->vFindElevationDataRef(cAuxString);
	XPLMDebugString(cAuxString);
	XPLMDebugString("\n");
}


MultiAircraft::~MultiAircraft(void)
{
}

void MultiAircraft::vSetGearDeploy(eGearState xNewState){
	for(int i = 0; i < 10; i++){
		this->fGearDeploy[i] = (float) xNewState;
	}
	XPLMSetDatavf(this->xGearDeployDataRef,this->fGearDeploy,0,9);
}
