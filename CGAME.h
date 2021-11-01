#ifndef CGAME_H
#define CGAME_H

#include "Console.h"
#include "CPEOPLE.h"
#include "CTRUCK.h"
#include "CCAR.h"

class CGAME {
private:
	static CGAME* m_pGame;
	Console m_Console;
	vector<pair<float, string>> m_vecLanes = {
		{0.0f,"p"},
		{1.0f,"a"},
		{1.0f,"a"},
		{1.0f,"a"},
		{2.0f,"a"},
		{1.0f,"p"},
		{3.0f,"c"},
		{1.0f,"t"},
		{4.0f,"c"},
		{1.0f,"c"},
		{1.0f,"c"},
		{0.0f,"p"},
	};
	vector<pair<int,vector<CVEHICLE*>>>m_vecVehicles;

	// Player
	CPEOPLE mPeople;

	// Playing area setting
	CPOINT2D mTopLeft;
	CPOINT2D mBottomRight;

	CGAME(); // Chuẩn bị dữ liệu cho tất cả các đối tượng
public:
	static CGAME* getGame();
	~CGAME() = default; // Hủy tài nguyên đã cấp phát

	// Post process
	void setLanes();
	void setPeople();
	void setPlayingArea();

	CPEOPLE getPeople() const; // Lấy thông tin người
	vector<CVEHICLE> getVehicles() const; // Lấy danh sách các xe
	vector<CANIMAL> getAnimals() const; // Lấy danh sách các thú

	void drawPlayingArea() ; // Vẽ khu vực chơi
	void drawVehicles() ; // Vẽ xe
	void drawAnimals() ; // Vẽ thú
	void drawGame() ; // Thực hiện vẽ trò chơi ra màn hình sau khi có dữ liệu

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
