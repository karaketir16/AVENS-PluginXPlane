#ifndef MULTIAIRCRAFT_H
#define MULTIAIRCRAFT_H

#include "aircraft.h"
#define MULTI_MAXAIRCRAFTNUMBER 20

class MultiAircraft abstract :
	public Aircraft
{
private:

	int iAircraftNumber;

	// MultiAircraft data
	float fGearDeploy[10];
	float fThrottle[8];

	// MultiAircraft DataRefs
	XPLMDataRef xGearDeployDataRef;
	XPLMDataRef xThrottleDataRef;

	enum eThrottleState{
		FULL_REVERSE = -1,
		NONE = 0,
		FULL_FOWARD = 1
	};

public:
	virtual ~MultiAircraft(void);
	MultiAircraft(int iAircraftNumber);
	// Set Throttle state for all engines.
	void vSetThrottleState(eThrottleState xNewState);
	// Set Gear state for all gear.
	void vSetGearDeploy(eGearState xNewState);
	// Update plane position --- child classes must override
	virtual void vUpdatePosition(void) = 0;
};

#endif /* MULTIAIRCRAFT_H */
