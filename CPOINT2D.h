#ifndef CPOINT2D_H
#define CPOINT2D_H

class CPOINT2D {
	int mX, mY;
public:
	CPOINT2D();
	CPOINT2D(int x, int y) : mX(x), mY(y) {};
	void setX(int);
	void setY(int);
	void setXY(int, int);
	void moveX(int);
	void moveY(int);
	void moveXY(int, int);
	int getX() const;
	int getY() const;
};

#endif // CPOINT2D_H
