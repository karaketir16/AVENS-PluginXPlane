#ifndef USERAIRCRAFT_H
#define USERAIRCRAFT_H

#include "Aircraft.h"


class UserAircraft :
	public Aircraft
{
private:
	// Other data --- User Aircraft only
	float fAGL;
	float fLatitudeReference;
	float fLongitudeReference;
	int iAutoPilotMode;

	// References to data
	XPLMDataRef xAGLDataRef;
	XPLMDataRef xAutopilotModeDataRef;
	XPLMDataRef xLatitudeReferenceDataRef;
	XPLMDataRef xLongitudeReferenceDataRef;

	// Singleton pattern
	UserAircraft(void);
	virtual ~UserAircraft(void);
	static UserAircraft * pxUserAircraft;

public:
	// Singleton pattern
	static UserAircraft * getUserAircraft(void);

	/* Get UserAircraft data.*/
	float fGetAltitude(void);
	float fGetLatitudeReference(void);
	float fGetLongitudeReference(void);
	int iReadAutoPilotMode(void);
	void vUpdatePosition(void);

};

#endif /* USERAIRCRAFT_H */