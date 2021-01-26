#include "Aircraft.h"


Aircraft::Aircraft(){

}

Aircraft::~Aircraft(void)
{

}


/* Get XPLMDataRef from XPlane. Since paths for User and Other Aircrafts are
different, a parameter is needed. */
void Aircraft::vFindXPositionDataRef(char * pcPath){
	this->xXPositionDataRef = XPLMFindDataRef(pcPath);
}
void Aircraft::vFindYPositionDataRef(char * pcPath){
	this->xYPositionDataRef = XPLMFindDataRef(pcPath);
}
void Aircraft::vFindZPositionDataRef(char * pcPath){
	this->xZPositionDataRef = XPLMFindDataRef(pcPath);
}
void Aircraft::vFindThetaAngleDataRef(char * pcPath){
	this->xThetaAngleDataRef = XPLMFindDataRef(pcPath);
}
void Aircraft::vFindPhiAngleDataRef(char * pcPath){
	this->xPhiAngleDataRef = XPLMFindDataRef(pcPath);
}
void Aircraft::vFindPsiAngleDataRef(char * pcPath){
	this->xPsiAngleDataRef = XPLMFindDataRef(pcPath);
}
void Aircraft::vFindLatitudeDataRef(char * pcPath){
	this->xLatitudeDataRef = XPLMFindDataRef(pcPath);
}
void Aircraft::vFindLongitudeDataRef(char * pcPath){
	this->xLongitudeDataRef = XPLMFindDataRef(pcPath);
}
void Aircraft::vFindElevationDataRef(char * pcPath){
	this->xElevationDataRef = XPLMFindDataRef(pcPath);
}

/* Read DataRefs. */
XPLMDataRef Aircraft::xGetXPositionDataRef(void){
	return this->xXPositionDataRef;
}
XPLMDataRef Aircraft::xGetYPositionDataRef(void){
	return this->xYPositionDataRef;
}
XPLMDataRef Aircraft::xGetZPositionDataRef(void){
	return this->xZPositionDataRef;
}
XPLMDataRef Aircraft::xGetThetaAngleDataRef(void){
	return this->xThetaAngleDataRef;
}
XPLMDataRef Aircraft::xGetPhiAngleDataRef(void){
	return this->xPhiAngleDataRef;
}
XPLMDataRef Aircraft::xGetPsiAngleDataRef(void){
	return this->xPsiAngleDataRef;
}
XPLMDataRef Aircraft::xGetLatitudeDataRef(void){
	return this->xLatitudeDataRef;
}
XPLMDataRef Aircraft::xGetLongitudeDataRef(void){
	return this->xLongitudeDataRef;
}
XPLMDataRef Aircraft::xGetElevationDataRef(void){
	return this->xElevationDataRef;
}

/* Set DataRefs. */
void Aircraft::vSetXPositionDataRef(XPLMDataRef xNewRef){
	this->xXPositionDataRef = xNewRef;
}
void Aircraft::vSetYPositionDataRef(XPLMDataRef xNewRef){
	this->xYPositionDataRef = xNewRef;
}
void Aircraft::vSetZPositionDataRef(XPLMDataRef xNewRef){
	this->xZPositionDataRef = xNewRef;
}
void Aircraft::vSetThetaAngleDataRef(XPLMDataRef xNewRef){
	this->xThetaAngleDataRef = xNewRef;
}
void Aircraft::vSetPhiAngleDataRef(XPLMDataRef xNewRef){
	this->xPhiAngleDataRef = xNewRef;
}
void Aircraft::vSetPsiAngleDataRef(XPLMDataRef xNewRef){
	this->xPsiAngleDataRef = xNewRef;
}
void Aircraft::vSetLatitudeDataRef(XPLMDataRef xNewRef){
	this->xLatitudeDataRef = xNewRef;
}
void Aircraft::vSetLongitudeDataRef(XPLMDataRef xNewRef){
	this->xLongitudeDataRef = xNewRef;
}
void Aircraft::vSetElevationDataRef(XPLMDataRef xNewRef){
	this->xElevationDataRef = xNewRef;
}

/* Resolve values from DataRefs. */
void Aircraft::vReadXPosition(void){
	this->dXPosition = XPLMGetDatad(this->xXPositionDataRef);
}
void Aircraft::vReadYPosition(void){
	this->dYPosition = XPLMGetDatad(this->xYPositionDataRef);
}
void Aircraft::vReadZPosition(void){
	this->dZPosition = XPLMGetDatad(this->xZPositionDataRef);
}
void Aircraft::vReadThetaAngle(void){
	this->fThetaAngle = XPLMGetDataf(this->xThetaAngleDataRef);
}
void Aircraft::vReadPhiAngle(void){
	this->fPhiAngle = XPLMGetDataf(this->xPhiAngleDataRef);
}
void Aircraft::vReadPsiAngle(void){
	this->fPsiAngle = XPLMGetDataf(this->xPsiAngleDataRef);
}
void Aircraft::vReadLatitude(void){
	this->dLatitude = XPLMGetDatad(this->xLatitudeDataRef);
}
void Aircraft::vReadLongitude(void){
	this->dLongitude = XPLMGetDatad(this->xLongitudeDataRef);
}
void Aircraft::vReadElevation(void){
	this->dElevation = XPLMGetDatad(this->xElevationDataRef);
}

/* Write values to DataRefs. */
void Aircraft::vWriteXPosition(double dNewValue){
	XPLMSetDatad(this->xXPositionDataRef,this->dXPosition);
}
void Aircraft::vWriteYPosition(double dNewValue){
	XPLMSetDatad(this->xYPositionDataRef,this->dYPosition);
}
void Aircraft::vWriteZPosition(double dNewValue){
	XPLMSetDatad(this->xZPositionDataRef,this->dZPosition);
}
void Aircraft::vWriteThetaAngle(float fNewValue){
	XPLMSetDataf(this->xThetaAngleDataRef,this->fThetaAngle);
}
void Aircraft::vWritePhiAngle(float fNewValue){
	XPLMSetDataf(this->xPhiAngleDataRef,this->fPhiAngle);
}
void Aircraft::vWritePsiAngle(float fNewValue){
	XPLMSetDataf(this->xPsiAngleDataRef,this->fPsiAngle);
}
void Aircraft::vWriteLatitude(double dNewValue){
	XPLMSetDatad(this->xLatitudeDataRef,this->dLatitude);
}
void Aircraft::vWriteLongitude(double dNewValue){
	XPLMSetDatad(this->xLongitudeDataRef,this->dLongitude);
}
void Aircraft::vWriteElevation(double dNewValue){
	XPLMSetDatad(this->xElevationDataRef,this->dElevation);
}

/* Get Aircraft data. */
double Aircraft::dGetXPosition(void){
	return this->dXPosition;
}
double Aircraft::dGetYPosition(void){
	return this->dYPosition;
}
double Aircraft::dGetZPosition(void){
	return this->dZPosition;
}
float Aircraft::fGetThetaAngle(void){
	return this->fThetaAngle;
}
float Aircraft::fGetPhiAngle(void){
	return this->fPhiAngle;
}
float Aircraft::fGetPsiAngle(void){
	return this->fPsiAngle;
}
double Aircraft::dGetLatitude(void){
	return this->dLatitude;
}
double Aircraft::dGetLongitude(void){
	return this->dLongitude;
}
double Aircraft::dGetElevation(void){
	return this->dElevation;
}

/* Set Aircraft data. */
void Aircraft::vSetXPosition(double dNewValue){
	this->dXPosition = dNewValue;
	this->vWriteXPosition(dNewValue);
}
void Aircraft::vSetYPosition(double dNewValue){
	this->dYPosition = dNewValue;
	this->vWriteYPosition(dNewValue);
}

void Aircraft::vSetZPosition(double dNewValue){
	this->dZPosition = dNewValue;
	this->vWriteZPosition(dNewValue);
}
void Aircraft::vSetThetaAngle(float fNewValue){
	this->fThetaAngle = fNewValue;
	this->vWriteThetaAngle(fNewValue);
}

void Aircraft::vSetPhiAngle(float fNewValue){
	this->fPhiAngle = fNewValue;
	this->vWritePhiAngle(fNewValue);
}
void Aircraft::vSetPsiAngle(float fNewValue){
	this->fPsiAngle = fNewValue;
	this->vWritePsiAngle(fNewValue);
}
void Aircraft::vSetLatitude(double dNewValue){
	this->dLatitude = dNewValue;
	this->vWriteLatitude(dNewValue);
}
void Aircraft::vSetLongitude(double dNewValue){
	this->dLongitude = dNewValue;
	this->vWriteLongitude(dNewValue);
}
void Aircraft::vSetElevation(double dNewValue){
	this->dElevation = dNewValue;
	this->vWriteElevation(dNewValue);
}



