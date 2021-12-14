#ifndef CPOINT2D_H
#define CPOINT2D_H

#include <cmath>

class CPOINT2D {
	int mX, mY;
public:
	CPOINT2D();
	CPOINT2D(int x, int y) : mX(x), mY(y) {};

	// Setter
	void setX(int);
	void setY(int);
	void setXY(int, int);

	// Move a delta distance
	void moveX(int);
	void moveY(int);
	void moveXY(int, int);

	// Getter
	int getX() const;
	int getY() const;

	// Method
	double Distance(const CPOINT2D&) const;
};

#endif // CPOINT2D_H
