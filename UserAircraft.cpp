
#include "UserAircraft.h"
#include "XPLMUtilities.h"

UserAircraft * UserAircraft::pxUserAircraft = NULL;

UserAircraft::UserAircraft(void):Aircraft()
{
	// Resolve dataRefs
	XPLMDebugString("Construtor User");
	this->vFindXPositionDataRef("sim/flightmodel/position/local_x");
	this->vFindYPositionDataRef("sim/flightmodel/position/local_y");
	this->vFindZPositionDataRef("sim/flightmodel/position/local_z");
	this->vFindThetaAngleDataRef("sim/flightmodel/position/theta");
	this->vFindPhiAngleDataRef("sim/flightmodel/position/phi");
	this->vFindPsiAngleDataRef("sim/flightmodel/position/psi");
	this->vFindLatitudeDataRef("sim/flightmodel/position/latitude");
	this->vFindLongitudeDataRef("sim/flightmodel/position/longitude");
	this->vFindElevationDataRef("sim/flightmodel/position/elevation");
	this->xAGLDataRef = XPLMFindDataRef("sim/flightmodel/position/y_agl");
	this->xAutopilotModeDataRef = XPLMFindDataRef("sim/cockpit/autopilot/autopilot_mode");
	this->xLatitudeReferenceDataRef = XPLMFindDataRef("sim/flightmodel/position/lat_ref");
	this->xLongitudeReferenceDataRef = XPLMFindDataRef("sim/flightmodel/position/lon_ref");
	this->fLatitudeReference = XPLMGetDataf(this->xLatitudeReferenceDataRef);
	this->fLongitudeReference = XPLMGetDataf(this->xLongitudeReferenceDataRef);
}


UserAircraft::~UserAircraft(void)
{

}

UserAircraft * UserAircraft::getUserAircraft(void){
	if(UserAircraft::pxUserAircraft == NULL){
		UserAircraft::pxUserAircraft = new UserAircraft();
	}
	return UserAircraft::pxUserAircraft;
}

void UserAircraft::vUpdatePosition(void){
	this->vReadXPosition();
	this->vReadYPosition();
	this->vReadZPosition();
	this->vReadThetaAngle();
	this->vReadPhiAngle();
	this->vReadPsiAngle();
	this->vReadLatitude();
	this->vReadLongitude();
	this->vReadElevation();
	this->fAGL = XPLMGetDataf(this->xAGLDataRef);
	this->fLatitudeReference = XPLMGetDataf(this->xLatitudeReferenceDataRef);
	this->fLongitudeReference = XPLMGetDataf(this->xLongitudeReferenceDataRef);
}

float UserAircraft::fGetAltitude(){
	return this->fAGL;
}

float UserAircraft::fGetLatitudeReference(){
	return this->fLatitudeReference;
}

float UserAircraft::fGetLongitudeReference(){
	return this->fLongitudeReference;
}

int UserAircraft::iReadAutoPilotMode(void){
	this->iAutoPilotMode = XPLMGetDatai(this->xAutopilotModeDataRef);
	return this->iAutoPilotMode;
}