#include "Position.h"
#include <math.h>

#define RAD2DEG (180.0f/3.14159f)
#define DEG2RAD (3.14159f/180.0f)


Position::Position()
{
	Init();
}


Position::~Position()
{
}

void Position::Init(){
	location = new Point(0, 0, 0);
	velocity = new Point(0, 0, 0);
	accel = new Point(0, 0, 0);
	look = new LookDirection(location);
}

Point* Position::getLocation(){
	return location;
}

void Position::halt(){
	velocity = new Point(0, 0, 0);
	accel = new Point(0, 0, 0);
}

LookDirection* Position::getLook(){
	return look;
}

void Position::lookTo(Direction direction,float magnitude){
	look->lookTo(direction,magnitude);
}

void Position::lookAt(Point* point,bool tracking){
	look->lookAt(location, point, tracking);
}

Point* Position::getVelocity(){
	return velocity;
}

void Position::addVelocity(Point* newSpeed){
	velocity->move(newSpeed);
}

void Position::setVelocity(Point* newSpeed){
	velocity = newSpeed;
}

Point* Position::getAccel(){
	return accel;
}

void Position::setAccel(Point* newAccel){
	accel = newAccel;
}

void Position::addAccel(Point* newAccel){
	accel->move(newAccel);
}

void Position::teleport(Point* coord){
	location = coord;
}

//This is used to start all controlled movements.  It adds velocity in relation to the camera's direction.
void Position::beginMove(Direction direction,float magnitude){
	float azimuth = look->getAzimuth();
	if (direction == Direction::FRONT){
		addVelocity(new Point(
			sin(azimuth*DEG2RAD)*magnitude,
			0.0,
			cos(azimuth*DEG2RAD)*magnitude));
	}
	if (direction == Direction::BACK){
		addVelocity(new Point(
			-sin(azimuth*DEG2RAD)*magnitude,
			0.0,
			-cos(azimuth*DEG2RAD)*magnitude));
	}
	if (direction == Direction::RIGHT){
		addVelocity(new Point(
			sin((90 + azimuth)*DEG2RAD)*magnitude,
			0.0,
			cos((90 + azimuth)*DEG2RAD)*magnitude));
	}
	if (direction == Direction::LEFT){
		addVelocity(new Point(
			-sin((90 + azimuth)*DEG2RAD)*magnitude,
			0.0,
			-cos((90 + azimuth)*DEG2RAD)*magnitude));
	}
	if (direction == Direction::UP){
		velocity->addY(magnitude);
	}
	if (direction == Direction::DOWN){
		velocity->addY(-magnitude);
	}
}

bool Position::isOnGround(){
	//TODO: Make this more intricate to account for other landscapes
	return (location->getX() == 0);
}

//This method updates everything.
void Position::applyTickMovement(int elapsedMills){
	//Note:  Flipping the order of these may break ground pushback.
	//apply current velocity to the position
	location->move(velocity);
	//Add acceleration to velocity to set up for next tick.
	velocity->move(accel);
	//Tick the look tracking
	look->trackingTick();
}