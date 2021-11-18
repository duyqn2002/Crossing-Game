#ifndef CPEOPLE_H
#define CPEOPLE_H

#include "CLANE.h"

class CPEOPLE {
private:
	// Current position 2D
	CPOINT2D mCurrPos;

	// Limit zone
	CPOINT2D mTopLeft;
	CPOINT2D mBottomRight;

	// Height and width of people
	int mHeight;
	int mWidth;

	// State of alive
	bool mState;

	// People form in ascii
	Texture mPeopleLeftForm;
	Texture mPeopleRightForm;
	Texture* mCurrForm;
public:
	CPEOPLE();
	CPEOPLE(int, int);
	CPEOPLE(int, int, CPOINT2D, CPOINT2D);
	CPEOPLE(const CPEOPLE&);
	~CPEOPLE() = default;

	CPEOPLE& operator= (const CPEOPLE&);

	// Setter
	void setXY(int, int);
	void setLimitZone(CPOINT2D, CPOINT2D);

	// Getter
	int getX() const;
	int getY() const;
	int Height() const;
	int Width() const;

	// Moving function
	void Up(int);
	void Left(int);
	void Right(int);
	void Down(int);
	void Move(KEY, int);

	// Check impact
	template <class T>
	bool isImpact(const CLANE<T>&);

	// Don't let the people go outside the playing area
	void Clip();

	// Handle the event
	bool isFinish() const;
	bool isDead() const;

	// Render people function
	void drawPeople(Console&);
};

template <class T>
bool CPEOPLE::isImpact(const CLANE<T>& Lane) {
	bool isImpact = false;

	for (int i = 0; i < Lane.size(); i++) {
		if (getX() + Width() >= Lane[i].getX() && getX() <= Lane[i].getX() + Lane[i].Width()) {
			isImpact = true;
			break;
		}
	}

	// If impact with object, people will die
	if (isImpact)
		mState = false;
	return isImpact;
}

#endif // CPEOPLE_H
