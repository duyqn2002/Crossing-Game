#ifndef CPOINT2D_H
#define CPOINT2D_H

class CPOINT2D {
	int mX, mY;
public:
	CPOINT2D();
	CPOINT2D(int x, int y) : mX(x), mY(y) {};
	CPOINT2D(const CPOINT2D&);
	// Operator
	CPOINT2D& operator=(const CPOINT2D&);

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
};

#endif // CPOINT2D_H
