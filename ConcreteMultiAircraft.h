#pragma once
#include "multiaircraft.h"

#define MIN_DELTA_X 20
#define MIN_DELTA_Y 20
#define MIN_DELTA_Z 20

#define MAX_DELTA_X 100
#define MAX_DELTA_Y 100
#define MAX_DELTA_Z 100

#define COORD_INCREMENT 0.1


class ConcreteMultiAircraft :
	public MultiAircraft
{
public:

	typedef enum{
		FRONT_RIGHT,
		FRONT_LEFT,
		BACK_RIGHT,
		BACK_LEFT,
		ABOVE,
		BELOW,
		OTHER
	} ePlanePosition;

	ConcreteMultiAircraft(int iAircraftNumber, ePlanePosition ePosition);
	virtual ~ConcreteMultiAircraft(void);

	void vUpdatePosition(void);

private:
	ePlanePosition ePosition;

	typedef enum {
		DECREASING = -1,
		NO_CHANGE = 0,
		INCREASING = 1
	} eIncrementDirection;


	// Last difference between UserAircraft and this Aircraft.
	double dDeltaX;
	double dDeltaY;
	double dDeltaZ;

	// Direction of increment for all coordinates
	eIncrementDirection eXDirection;
	eIncrementDirection eYDirection;
	eIncrementDirection eZDirection;

};

