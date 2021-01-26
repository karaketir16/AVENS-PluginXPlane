#include "ConcreteMultiAircraft.h"
#include "UserAircraft.h"
#include "XPLMUtilities.h"


#define module(arg) (arg<0?(-1)*arg:arg) 
//#define updateZPos() dDeltaX > (MAX_DELTA_X - MIN_DELTA_X)/2? true:false
#define updateZPos() true

ConcreteMultiAircraft::ConcreteMultiAircraft(int iAircraftNumber, ePlanePosition ePosition) : MultiAircraft(iAircraftNumber)
{
	this->ePosition = ePosition;

	UserAircraft * pxUser = UserAircraft::getUserAircraft();

	// Set initial position
	switch(ePosition){
	case ABOVE:
		// Aircraft flies above UserAircraft (Y - Axis)
		this->dDeltaX = 0;
		this->dDeltaY = MIN_DELTA_Y;
		this->dDeltaZ = (-1) * (module(dDeltaX)/2);
		this->eXDirection = NO_CHANGE;
		this->eYDirection = INCREASING;
		this->eZDirection = NO_CHANGE;
		break;
	case BELOW:
		// Aircraft flies below UserAircraft (Y - Axis)
		this->dDeltaX = 0;
		this->dDeltaY = (-1) * MIN_DELTA_Y;
		this->dDeltaZ = module(dDeltaY)/2;
		this->eXDirection = NO_CHANGE;
		this->eYDirection = DECREASING;
		this->eZDirection = NO_CHANGE;
		break;
	case FRONT_RIGHT:
		// Aircraft flies in front and to the right
		this->dDeltaX = MIN_DELTA_X;
		this->dDeltaY = 0;
		this->dDeltaZ = (-1) * MIN_DELTA_Z;
		this->eXDirection = INCREASING;
		this->eYDirection = NO_CHANGE;
		this->eZDirection = DECREASING;
		break;
	case FRONT_LEFT:
		// Aircraft files in front and to the left
		this->dDeltaX = (-1) * MIN_DELTA_X;
		this->dDeltaY = 0;
		this->dDeltaZ = (-1) * MIN_DELTA_Z;
		this->eXDirection = DECREASING;
		this->eYDirection = NO_CHANGE;
		this->eZDirection = DECREASING;
		break;
	case BACK_RIGHT:
		// Aircraft flies back and to the right
		this->dDeltaX = MIN_DELTA_X;
		this->dDeltaY = 0;
		this->dDeltaZ = MIN_DELTA_Z;
		this->eXDirection = INCREASING;
		this->eYDirection = NO_CHANGE;
		this->eZDirection = INCREASING;
		break;
	case BACK_LEFT:
		// Aircraft flies back and to the left
		this->dDeltaX = (-1) * MIN_DELTA_X;
		this->dDeltaY = 0;
		this->dDeltaZ = MIN_DELTA_Z;
		this->eXDirection = DECREASING;
		this->eYDirection = NO_CHANGE;
		this->eZDirection = INCREASING;
		break;
	default:
		this->dDeltaX = 0;
		this->dDeltaY = 0;
		this->dDeltaZ = 0;
		this->eXDirection = NO_CHANGE;
		this->eYDirection = NO_CHANGE;
		this->eZDirection = NO_CHANGE;
	}
}


ConcreteMultiAircraft::~ConcreteMultiAircraft(void)
{
}

void ConcreteMultiAircraft::vUpdatePosition(void)
{
	char message[100];

	UserAircraft * pxUser = UserAircraft::getUserAircraft();

	switch(ePosition){
	case ABOVE:
		// Aircraft goes up and then down
		if(this->eYDirection == INCREASING){
			dDeltaY += COORD_INCREMENT;
			if(module(dDeltaY) > MAX_DELTA_Y){
				dDeltaY = MAX_DELTA_Y;
				this->eYDirection = DECREASING;
			}
		}else{
			dDeltaY -= COORD_INCREMENT;
			if(module(dDeltaY) < MIN_DELTA_Y){
				dDeltaY = MIN_DELTA_Y;
				this->eYDirection = INCREASING;
			}
		}
		break;
	case BELOW:
		// Aircraft goes down and then up
		if(this->eYDirection == DECREASING){
			dDeltaY -= COORD_INCREMENT;
			if(module(dDeltaY) > MAX_DELTA_Y){
				dDeltaY = (-1) * MAX_DELTA_Y;
				this->eYDirection = INCREASING;
			}
		}else{
			dDeltaY += COORD_INCREMENT;
			if(module(dDeltaY) < MIN_DELTA_Y){
				dDeltaY = (-1) * MIN_DELTA_Y;
				this->eYDirection = DECREASING;
			}
		}
		break;
	case FRONT_RIGHT:
		// Aircraft flies in front and to the right
		if(this->eXDirection == INCREASING){
			dDeltaX += COORD_INCREMENT;
			if(module(dDeltaX) > MAX_DELTA_X){
				dDeltaX = MAX_DELTA_X;
				this->eXDirection = DECREASING;
			}
		}else{
			dDeltaX -= COORD_INCREMENT;
			if(module(dDeltaX) < MIN_DELTA_X){
				dDeltaX = MIN_DELTA_X;
				this->eXDirection = INCREASING;
			}
		}
		if(updateZPos() == true){
			if(this->eZDirection == DECREASING){
				dDeltaZ -= COORD_INCREMENT;
				if(module(dDeltaZ) > MAX_DELTA_Z){
					dDeltaZ = (-1) * MAX_DELTA_Z;
					this->eZDirection = INCREASING;
				}
			}else{
				dDeltaZ += COORD_INCREMENT;
				if(module(dDeltaZ) < MIN_DELTA_Z){
					dDeltaZ = (-1) * MIN_DELTA_Z;
					this->eZDirection = DECREASING;
				}
			}
		}
		break;
	case FRONT_LEFT:
		// Aircraft files in front and to the left
		if(this->eXDirection == DECREASING){
			dDeltaX -= COORD_INCREMENT;
			if(module(dDeltaX) > MAX_DELTA_X){
				dDeltaX = (-1) * MAX_DELTA_X;
				this->eXDirection = INCREASING;
			}
		}else{
			dDeltaX += COORD_INCREMENT;
			if(module(dDeltaX) < MIN_DELTA_X){
				dDeltaX = (-1) * MIN_DELTA_X;
				this->eXDirection = DECREASING;
			}
		}
		if(updateZPos() == true){
			if(this->eZDirection == DECREASING){
				dDeltaZ -= COORD_INCREMENT;
				if(module(dDeltaZ) > MAX_DELTA_Z){
					dDeltaZ = (-1) * MAX_DELTA_Z;
					this->eZDirection = INCREASING;
				}
			}else{
				dDeltaZ += COORD_INCREMENT;
				if(module(dDeltaZ) < MIN_DELTA_Z){
					dDeltaZ = (-1) * MIN_DELTA_Z;
					this->eZDirection = DECREASING;
				}
			}
		}
		break;
	case BACK_RIGHT:
		// Aircraft flies back and to the right
		if(this->eXDirection == INCREASING){
			dDeltaX += COORD_INCREMENT;
			if(module(dDeltaX) > MAX_DELTA_X){
				dDeltaX = MAX_DELTA_X;
				this->eXDirection = DECREASING;
			}
		}else{
			dDeltaX -= COORD_INCREMENT;
			if(module(dDeltaX) < MIN_DELTA_X){
				dDeltaX = MIN_DELTA_X;
				this->eXDirection = INCREASING;
			}
		}
		if(updateZPos() == true){
			if(this->eZDirection == INCREASING){
				dDeltaZ += COORD_INCREMENT;
				if(module(dDeltaZ) > MAX_DELTA_Z){
					dDeltaZ = MAX_DELTA_Z;
					this->eZDirection = DECREASING;
				}
			}else{
				dDeltaZ -= COORD_INCREMENT;
				if(module(dDeltaZ) < MIN_DELTA_Z){
					dDeltaZ = MIN_DELTA_Z;
					this->eZDirection = INCREASING;
				}
			}
		}
		break;
	case BACK_LEFT:
		// Aircraft flies back and to the left
		if(this->eXDirection == DECREASING){
			dDeltaX -= COORD_INCREMENT;
			if(module(dDeltaX) > MAX_DELTA_X){
				dDeltaX = (-1) * MAX_DELTA_X;
				this->eXDirection = INCREASING;
			}
		}else{
			dDeltaX += COORD_INCREMENT;
			if(module(dDeltaX) < MIN_DELTA_X){
				dDeltaX = (-1) * MIN_DELTA_X;
				this->eXDirection = DECREASING;
			}
		}
		if(updateZPos() == true){
			if(this->eZDirection == INCREASING){
				dDeltaZ += COORD_INCREMENT;
				if(module(dDeltaZ) > MAX_DELTA_Z){
					dDeltaZ = MAX_DELTA_Z;
					this->eZDirection = DECREASING;
				}
			}else{
				dDeltaZ -= COORD_INCREMENT;
				if(module(dDeltaZ) < MIN_DELTA_Z){
					dDeltaZ = MIN_DELTA_Z;
					this->eZDirection = INCREASING;
				}
			}
		}
		break;
	default:
		this->dDeltaX = 0;
		this->dDeltaY = 0;
		this->dDeltaZ = 0;
		this->eXDirection = NO_CHANGE;
		this->eYDirection = NO_CHANGE;
		this->eZDirection = NO_CHANGE;
	}

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