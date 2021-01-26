#include "ConcreteMultiStraight.h"
#include "UserAircraft.h"

#define DELTA 20

ConcreteMultiStraight::ConcreteMultiStraight(int iAircraftNumber) : MultiAircraft(iAircraftNumber){
	switch (iAircraftNumber)
	{
	case 0:
		this->dDeltaX = 0;
		this->dDeltaY = 0;
		this->dDeltaZ = 0;
		break;
	case 1:
		this->dDeltaX = (-1) * DELTA;
		this->dDeltaY = 0;
		this->dDeltaZ = DELTA;
		break;
	case 2:
		this->dDeltaX = 0;
		this->dDeltaY = 0;
		this->dDeltaZ = DELTA;
		break;
	case 3:
		this->dDeltaX = DELTA;
		this->dDeltaY = 0;
		this->dDeltaZ = DELTA;
		break;
	case 4:
		this->dDeltaX = (-2) * DELTA;
		this->dDeltaY = 0;
		this->dDeltaZ = 2 * DELTA;
		break;
	case 5:
		this->dDeltaX = 0;
		this->dDeltaY = 0;
		this->dDeltaZ = 2 * DELTA;
		break;
	case 6:
		this->dDeltaX = 2 * DELTA;
		this->dDeltaY = 0;
		this->dDeltaZ = 2 * DELTA;
		break;
	default:
		break;
	}
}


ConcreteMultiStraight::~ConcreteMultiStraight(void)
{
}

void ConcreteMultiStraight::vUpdatePosition(void)
{
	char message[100];

	UserAircraft * pxUser = UserAircraft::getUserAircraft();

	this->vSetXPosition(pxUser->dGetXPosition() + dDeltaX);
	this->vSetYPosition(pxUser->dGetYPosition() + dDeltaY);
	this->vSetZPosition(pxUser->dGetZPosition() + dDeltaZ);
	this->vSetThetaAngle(pxUser->fGetThetaAngle());
	this->vSetPsiAngle(pxUser->fGetPsiAngle());
	this->vSetPhiAngle(pxUser->fGetPhiAngle());
	this->vReadLatitude();
	this->vReadLongitude();
	this->vReadElevation();
}