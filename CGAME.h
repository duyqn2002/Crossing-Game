#ifndef CGAME_H
#define CGAME_H

#include "HelpFunctions.h"
#include "Console.h"
#include "CPEOPLE.h"
#include "CTRUCK.h"
#include "CCAR.h"

class CGAME {
private:
	static CGAME* m_pGame;

	Console mConsole;

	vector<pair<float, string>> m_vecLanes = {
		{0.0f,"SAFE"},
		{-1.0f,"CDOG"},
		{1.0f,"CBIRD"},
		{-1.0f,"CDOG"},
		{1.0f,"CBIRD"},
		{1.0f,"SAFE"},
		{-1.0f,"CCAR"},
		{1.0f,"CTRUCK"},
		{-1.0f,"CCAR"},
		{1.0f,"CTRUCK"},
		{-1.0f,"CCAR"},
		{0.0f,"SAFE"},
	};

	vector<pair<int,vector<CVEHICLE*>>>m_vecVehicles;
	vector<pair<int, vector<CANIMAL*>>>m_vecAnimals;

	// Player
	CPEOPLE mPeople;

	// Playing area setting
	CPOINT2D mTopLeft;
	CPOINT2D mBottomRight;

	CGAME(); // Chuẩn bị dữ liệu cho tất cả các đối tượng
public:
	static CGAME* getGame();
	~CGAME(); // Hủy tài nguyên đã cấp phát

	// Post process
	void setObject();
	void setPeople();
	void setPlayingArea(float = 1.0f, float = 1.0f);

	CPEOPLE getPeople() const; // Lấy thông tin người
	vector<CVEHICLE*> getVehicles() const; // Lấy danh sách các xe
	vector<CANIMAL*> getAnimals() const; // Lấy danh sách các thú

	void drawPlayingArea() const; // Vẽ khu vực chơi
	void drawVehicles() const; // Vẽ xe
	void drawAnimals() const; // Vẽ thú
	void drawGame(); // Thực hiện vẽ trò chơi ra màn hình sau khi có dữ liệu

	void nextLevel();
	void resetGame(); // Thực hiện thiết lập lại toàn bộ dữ liệu như lúc đầu
	void startGame(); // Thực hiện bắt đầu vào trò chơi

	void loadGame(istream); // Thực hiện tải lại trò chơi đã lưu
	void saveGame(istream); // Thực hiện lưu lại dữ liệu trò chơi

	void pauseGame(HANDLE) const; // Tạm dừng Thread
	void resumeGame(HANDLE) const; // Quay lai Thread
	void exitGame(HANDLE); // Thực hiện thoát Thread

	void updatePosPeople(DIRECTION); // Thực hiện điều khiển di chuyển của CPEOPLE
	void updatePosVehicle(); // Thực hiện cho CTRUCK & CCAR di chuyển
	void updatePosAnimal(); // Thực hiện cho CDINAUSOR & CBIRD di chuyển
};

#endif // CGAME_H
