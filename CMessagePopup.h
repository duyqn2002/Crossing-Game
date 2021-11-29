#ifndef CMESSAGE_POPUP_H
#define CMESSAGE_POPUP_H

#include "Console.h"

class CMessagePopup
{
private:
	CPOINT2D mTopLeftPos;

	int mWidth;
	int mHeight;

	COLOUR mBorderColor;
public:
	CMessagePopup();
	~CMessagePopup();

	void setGeometry(int, int, int, int);
	void Resize(int, int);

	void Display(Console&);
};

#endif // CMESSAGE_POPUP_H


