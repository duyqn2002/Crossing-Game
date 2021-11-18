#ifndef CGAME_H
#define CGAME_H

#include "CPEOPLE.h"
#include "CLANE.h"

class CGAME {
private:
	bool isPlaying;
	bool isPause;
	thread mRenderGame;

	Console* m_pConsole;

	vector<pair<float, ENEMY>> mLanes = {
		{0.0f,ENEMY::NO_ENEMY},
		{-1.0f,ENEMY::CDOG},
		{1.0f,ENEMY::CBIRD},
		{-1.0f,ENEMY::CDOG},
		{1.0f,ENEMY::CBIRD},
		{1.0f,ENEMY::NO_ENEMY},
		{-1.0f,ENEMY::CCAR},
		{1.0f,ENEMY::CTRUCK},
		{-1.0f,ENEMY::CCAR},
		{1.0f,ENEMY::CTRUCK},
		{-1.0f,ENEMY::CCAR},
	};

	vector<CLANE<CVEHICLE>> mVehiclesLane;
	vector<CLANE<CANIMAL>> mAnimalsLane;

	// Player
	CPEOPLE mPeople;
	int peopleScore;

	// Playing area setting
	CPOINT2D mTopLeft;
	CPOINT2D mBottomRight;

	CGAME(); // Chuẩn bị dữ liệu cho tất cả các đối tượng
	CGAME(const CGAME&);
	CGAME& operator=(const CGAME&);
public:
	static CGAME* getGame();
	~CGAME(); // Hủy tài nguyên đã cấp phát

	// Post process
	void setObjects();
	void setPeople();
	void setPlayingArea(float = 1.0f, float = 1.0f);

	CPEOPLE getPeople() const; // Lấy thông tin người
	CLANE<CVEHICLE> getVehicles() const; // Lấy danh sách các xe
	CLANE<CANIMAL> getAnimals() const; // Lấy danh sách các thú

	void drawPlayingArea(); // Vẽ khu vực chơi
	void drawVehicles(); // Vẽ xe
	void drawAnimals(); // Vẽ thú
	void drawGame(); // Thực hiện vẽ trò chơi ra màn hình sau khi có dữ liệu

	void renderGameThread(KEY*);
	void resetGame(); // Thực hiện thiết lập lại toàn bộ dữ liệu như lúc đầu
	void gameMainMenu();

	void nextLevel() {};
	void startGame(); // Thực hiện bắt đầu vào trò chơi

	void loadGame(istream); // Thực hiện tải lại trò chơi đã lưu
	void saveGame(istream); // Thực hiện lưu lại dữ liệu trò chơi

	void pauseGame(); // Tạm dừng Thread
	void resumeGame(); // Quay lai Thread
	void exitGame(); // Thực hiện thoát Thread

	void updatePosPeople(KEY); // Thực hiện điều khiển di chuyển của CPEOPLE
	void updatePosVehicle(); // Thực hiện cho CTRUCK & CCAR di chuyển
	void updatePosAnimal(); // Thực hiện cho CDINAUSOR & CBIRD di chuyển
};

#endif // CGAME_H
