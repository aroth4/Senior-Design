#pragma once
#include "Point.h"
#include "Direction.h"

class LookDirection
{
public:
	LookDirection(Point* from);
	~LookDirection();
	void Init(Point* from);
	float getAzimuth();
	bool isTracking();
	void setTracking(bool tracking);
	void setAzimuth(float azimuth);
	float getElevation();
	void setElevation(float elevation);
	void lookAt(Point* lookFrom,Point* lookAt,bool tracking);
	void trackingTick();
	void lookTo(Direction direction, float magnitude);
	Point* getLookAtPoint();

private:
	void updatePoint();
	void updateAzEl();

protected:
	float azimuth;
	float elevation;
	Point* lookAtPoint;
	Point* lookFromPoint;
	bool tracking;
};

