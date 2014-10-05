#include "Box.h"


//By default, box is the unit cube centered around the origin
Box::Box(){
	points[0] = new Point({ -0.5f, 0.5f, 0.5f });
	points[1] = new Point({ 0.5f, 0.5f, 0.5f });
	points[2] = new Point({ 0.5f, 0.5f, -0.5f });
	points[3] = new Point({ -0.5f, 0.5f, -0.5f });
	points[4] = new Point({ -0.5f, -0.5f, 0.5f });
	points[5] = new Point({ 0.5f, -0.5f, 0.5f });
	points[6] = new Point({ 0.5f, -0.5f, -0.5f });
	points[7] = new Point({ -0.5f, -0.5f, -0.5f });
}

Box::Box(Point* _points[8]){
	for (int i = 0; i < 6; i++)
		points[i] = _points[i];
}

Box::~Box(){

}

Triangle** Box::getInwardTriangles(){
	Triangle* triangles[12];
	rectanglesToTriangles(getInwardRectangles(),triangles,6);
	return triangles;
}
Triangle** Box::getOutwardTriangles(){
	Triangle* triangles[12];
	rectanglesToTriangles(getOutwardRectangles(), triangles, 6);
	return triangles;
}

Quad** Box::getInwardRectangles(){
	Quad* rectangles[6];
	rectangles[TOP_FACE] = getInwardTop();
	rectangles[BOTTOM_FACE] = getInwardBottom();
	rectangles[LEFT_FACE] = getInwardLeft();
	rectangles[RIGHT_FACE] = getInwardRight();
	rectangles[FRONT_FACE] = getInwardFront();
	rectangles[BACK_FACE] = getInwardBack();
	return rectangles;
}
Quad** Box::getOutwardRectangles(){
	Quad* rectangles[6];
	rectangles[TOP_FACE] = getOutwardTop();
	rectangles[BOTTOM_FACE] = getOutwardBottom();
	rectangles[LEFT_FACE] = getOutwardLeft();
	rectangles[RIGHT_FACE] = getOutwardRight();
	rectangles[FRONT_FACE] = getOutwardFront();
	rectangles[BACK_FACE] = getOutwardBack();
	return rectangles;
}

Quad* Box::getOutwardTop(){
	return new Quad(points[4], points[5], points[6], points[7]);
}
Quad* Box::getOutwardBottom(){
	return new Quad(points[0], points[1], points[2], points[3]);
}
Quad* Box::getOutwardLeft(){
	return new Quad(points[7], points[4], points[0], points[3]);
}
Quad* Box::getOutwardRight(){
	return new Quad(points[1], points[2], points[6], points[5]);
}
Quad* Box::getOutwardFront(){
	return new Quad(points[3], points[2], points[6], points[7]);
}
Quad* Box::getOutwardBack(){
	return new Quad(points[0], points[1], points[5], points[4]);
}

Quad* Box::getInwardTop(){
	return new Quad(points[7], points[6], points[5], points[4]);
}
Quad* Box::getInwardBottom(){
	return new Quad(points[3], points[2], points[1], points[0]);
}
Quad* Box::getInwardLeft(){
	return new Quad(points[3], points[0], points[4], points[7]);
}
Quad* Box::getInwardRight(){
	return new Quad(points[5], points[6], points[2], points[1]);
}
Quad* Box::getInwardFront(){
	return new Quad(points[7], points[6], points[2], points[3]);
}
Quad* Box::getInwardBack(){
	return new Quad(points[4], points[5], points[1], points[0]);
}

//to array must be twice the size of from, because there will be twice as many triangles as rectangles.
void rectanglesToTriangles(Quad** from, Triangle** to, int size){
	for (int i = 0; i < size; i++){
		copyTriangles(from[i]->getTriangles, to, 2);
	}
}

void copyTriangles(Triangle** from, Triangle** to, int size){
	for (int i = 0; i < size; i++)
		to[i] = from[i];
}