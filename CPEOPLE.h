#ifndef CPEOPLE_H
#define CPEOPLE_H

#include "Console.h"
#include "CVEHICLE.h"
#include "CANIMAL.h"

class CPEOPLE{
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
	int Height() const;
	int Width() const;
	CPOINT2D getPosition() const;

	// Moving function
	void toggleForm();
	void Up(int);
	void Left(int);
	void Right(int);
	void Down(int);
	void Move(DIRECTION, int);

	// Check impact
	bool isImpact(const vector<CVEHICLE>&);
	bool isImpact(const vector<CANIMAL>&);

	// Don't let the people go outside the playing area
	void Clip();

	// Handle the event
	bool isFinish() const;
	bool isDead() const;

	// Render people function
	void drawPeople(const Console&) const;
};

#endif // CPEOPLE_H
