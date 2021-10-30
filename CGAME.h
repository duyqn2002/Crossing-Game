#ifndef CGAME_H
#define CGAME_H

#include "CPEOPLE.h"
#include "CTRUCK.h"
#include "CCAR.h"
#include"CANIMAL.h"
class CGAME {
	static CGAME* m_pGame;
	vector <pair<float,vector<CVEHICLE*>>>m_vecLanes;

	// Game object
	vector<CTRUCK> m_vecTrucks;
	vector<CCAR> m_vecCars;

	// Player
	CPEOPLE mPeople;

	// Playing area setting
	CPOINT2D mTopLeft;
	CPOINT2D mBottomRight;

	CGAME(); // Chuẩn bị dữ liệu cho tất cả các đối tượng
public:
	static CGAME* getGame();
	CGAME(const CGAME&) {};
	~CGAME() = default; // Hủy tài nguyên đã cấp phát

	// Post process
	void setPeople();
	void setPlayingArea();

	CPEOPLE getPeople() const; // Lấy thông tin người
	vector<CVEHICLE> getVehicles() const; // Lấy danh sách các xe
	vector<CANIMAL> getAnimals() const; // Lấy danh sách các thú

	void drawPeopleSafeLane(int, int, int, int) const;
	void drawPlayingArea() const; // Vẽ khu vực chơi
	void drawVehicles() const; // Vẽ xe
	void drawAnimals(); // Vẽ thú
	void drawGame() const; // Thực hiện vẽ trò chơi ra màn hình sau khi có dữ liệu

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
