#pragma once
#include "multiaircraft.h"
class ConcreteMultiStraight :
	public MultiAircraft
{
public:
	ConcreteMultiStraight(int iAircraftNumber);
	virtual ~ConcreteMultiStraight(void);
	void vUpdatePosition(void);

private:
	double dDeltaX;
	double dDeltaY;
	double dDeltaZ;
};

