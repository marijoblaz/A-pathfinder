#pragma once
#include "Location.h"
#include "Node.h"


class GameState
{
private:

	//Init vars
	sf::RenderWindow* mWindow;

	sf::Clock clock; // starts the clock
	sf::Time elapsed1;
	sf::Time elapsed2;
	sf::Time elapsed3;
	sf::Time elapsed4;

	// 1 - player start
	// 2 - player finish
	// 3 - wall
	int maxi = 0;
	int maxi2 = 0;

	int selectedBuild = 3;

	int iStart = 20, jStart = 19;
	int iEnd = 0, jEnd = 0;

	bool startDrawing = false;

	const int IDIM = 40; // horizontal size of the squares
	const int JDIM = 20; // vertical size size of the squares

	// if NDIR = 4
	const int iDir[4] = { 1, 0, -1, 0 };
	const int jDir[4] = { 0, 1, 0, -1 };

	std::vector< std::pair <int, int> > vect;

	int squares[40][20];
	sf::RectangleShape squaresShape[40][20];

	//Info
	sf::Text infoNaslovText;
	sf::RectangleShape infoShape;
	sf::Text infoXText;
	sf::Text infoYText;

	sf::Text infoKeysText;
	sf::Text infoProgressText;

	sf::RectangleShape infoStartText;
	sf::RectangleShape infoFinishText;
	sf::RectangleShape infoRunShape;
	sf::Text infoRunXText;
	sf::Text infoRunYText;

	sf::Text infoStartValXText;
	sf::Text infoStartValYText;
	sf::Text infoFinishValXText;
	sf::Text infoFinishValYText;

	//Buttons
	sf::CircleShape startButton;
	sf::CircleShape finishButton;
	sf::CircleShape wallButton;

	sf::RectangleShape runShape;
	sf::Text runText;

	sf::RectangleShape randomShape;
	sf::Text randomText;

	sf::RectangleShape clearShape;
	sf::Text clearText;

	//font
	//text
	sf::Font font;
	sf::Text startButtonText;
	sf::Text finishButtonText;
	sf::Text wallButtonText;


	// list of closed (check-out) nodes
	int closedNodes[40][20];

	// list of open (not-yet-checked-out) nodes
	int openNodes[40][20];

	// map of directions (0: East, 1: North, 2: West, 3: South) 
	int dirMap[40][20];
	//Mouse pos
	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

private:

	int map(int x, int in_min, int in_max, int out_min, int out_max);

	void updateWall();
	void updateButtons();

	void initButtons();
	void updateMousePos();
	void initNodeShape();
	void initAsearch();
	void initFonts();

	void drawNodes();
	std::string Apathfind(const Location& locStart, const Location& locFinish);

public:

	GameState(sf::RenderWindow* mWindow);
	~GameState();

	void update(const float& dt);
	void render(sf::RenderTarget& mTarget);
};

