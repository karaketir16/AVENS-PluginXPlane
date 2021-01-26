
#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include "SDK\CHeaders\XPLM\XPLMDataAccess.h"

class Aircraft abstract
{
private:

	// Common Aircraft Data
	double dXPosition;
	double dYPosition;
	double dZPosition;
	float fThetaAngle;
	float fPhiAngle;
	float fPsiAngle;
	double dLatitude;
	double dLongitude;
	double dElevation;

	// Data References for each data
	XPLMDataRef xXPositionDataRef;
	XPLMDataRef xYPositionDataRef;
	XPLMDataRef xZPositionDataRef;
	XPLMDataRef xThetaAngleDataRef;
	XPLMDataRef xPhiAngleDataRef;
	XPLMDataRef xPsiAngleDataRef;
	XPLMDataRef xLatitudeDataRef;
	XPLMDataRef xLongitudeDataRef;
	XPLMDataRef xElevationDataRef;

protected:

	/* Get XPLMDataRef from XPlane. Since paths for User and Other Aircrafts are
	different, a parameter is needed. */
	void vFindXPositionDataRef(char * pcPath);
	void vFindYPositionDataRef(char * pcPath);
	void vFindZPositionDataRef(char * pcPath);
	void vFindThetaAngleDataRef(char * pcPath);
	void vFindPhiAngleDataRef(char * pcPath);
	void vFindPsiAngleDataRef(char * pcPath);
	void vFindLatitudeDataRef(char * pcPath);
	void vFindLongitudeDataRef(char * pcPath);
	void vFindElevationDataRef(char * pcPath);

	/* Return DataRefs. */
	XPLMDataRef xGetXPositionDataRef(void);
	XPLMDataRef xGetYPositionDataRef(void);
	XPLMDataRef xGetZPositionDataRef(void);
	XPLMDataRef xGetThetaAngleDataRef(void);
	XPLMDataRef xGetPhiAngleDataRef(void);
	XPLMDataRef xGetPsiAngleDataRef(void);
	XPLMDataRef xGetLatitudeDataRef(void);
	XPLMDataRef xGetLongitudeDataRef(void);
	XPLMDataRef xGetElevationDataRef(void);

	/* Set DataRefs. */
	void vSetXPositionDataRef(XPLMDataRef xNewRef);
	void vSetYPositionDataRef(XPLMDataRef xNewRef);
	void vSetZPositionDataRef(XPLMDataRef xNewRef);
	void vSetThetaAngleDataRef(XPLMDataRef xNewRef);
	void vSetPhiAngleDataRef(XPLMDataRef xNewRef);
	void vSetPsiAngleDataRef(XPLMDataRef xNewRef);
	void vSetLatitudeDataRef(XPLMDataRef xNewRef);
	void vSetLongitudeDataRef(XPLMDataRef xNewRef);
	void vSetElevationDataRef(XPLMDataRef xNewRef);

	/* Resolve from DataRefs. */
	void vReadXPosition(void);
	void vReadYPosition(void);
	void vReadZPosition(void);
	void vReadThetaAngle(void);
	void vReadPhiAngle(void);
	void vReadPsiAngle(void);
	void vReadLatitude(void);
	void vReadLongitude(void);
	void vReadElevation(void);

	/* Write to DataRefs. */
	void vWriteXPosition(double dNewValue);
	void vWriteYPosition(double dNewValue);
	void vWriteZPosition(double dNewValue);
	void vWriteThetaAngle(float fNewValue);
	void vWritePhiAngle(float fNewValue);
	void vWritePsiAngle(float fNewValue);
	void vWriteLatitude(double dNewValue);
	void vWriteLongitude(double dNewValue);
	void vWriteElevation(double dNewValue);

public:
	// Constructor and Destructor.
	Aircraft();
	virtual ~Aircraft(void);
	virtual void vUpdatePosition(void) = 0;

	enum eGearState{
		GEAR_UP,
		GEAR_DOWN
	};

	/* Get Aircraft data. */
	double dGetXPosition(void);
	double dGetYPosition(void);
	double dGetZPosition(void);
	float fGetThetaAngle(void);
	float fGetPhiAngle(void);
	float fGetPsiAngle(void);
	double dGetLatitude(void);
	double dGetLongitude(void);
	double dGetElevation(void);

	void vSetXPosition(double dNewValue);
	void vSetYPosition(double dNewValue);
	void vSetZPosition(double dNewValue);
	void vSetThetaAngle(float fNewValue);
	void vSetPhiAngle(float fNewValue);
	void vSetPsiAngle(float fNewValue);
	void vSetLatitude(double dNewValue);
	void vSetLongitude(double dNewValue);
	void vSetElevation(double dNewValue);

};

#endif /* AIRCRAFT_H */