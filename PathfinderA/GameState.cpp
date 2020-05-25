#include "GameState.h"

int GameState::map(int x, int in_min, int in_max, int out_min, int out_max)
{
   return (x - in_min)* (out_max - out_min) / (in_max - in_min) + out_min;
}

void GameState::updateWall()
{
    if (!startDrawing) {
        for (int j = 0; j < this->JDIM; j++) {
            for (int i = 0; i < this->IDIM; i++) {
                if (this->squaresShape[i][j].getGlobalBounds().contains(mousePosView)) {
                    //Presed make wall
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        switch (this->selectedBuild)
                        {
                        case 1:
                            iStart = i;
                            jStart = j;
                            break;
                        case 2:
                            iEnd = i;
                            jEnd = j;
                            break;
                        case 3:
                            this->squaresShape[i][j].setFillColor(sf::Color::White);
                            squares[i][j] = 1;
                            break;
                        }
                    }
                }
            }
        }

        for (int j = 0; j < this->JDIM; j++) {
            for (int i = 0; i < this->IDIM; i++) {
                if (squares[i][j] == 2 && squares[i][j] == 4) {
                    squares[i][j] = 0;
                }
                if (sf::Color::Green == squaresShape[i][j].getFillColor()) {
                    squaresShape[i][j].setFillColor(sf::Color(20,20,20));
                }
                if (sf::Color::Blue == squaresShape[i][j].getFillColor()) {
                    squaresShape[i][j].setFillColor(sf::Color(20,20,20));
                }
            }
        }

        squares[iStart][jStart] = 2;
        this->infoStartValXText.setString(std::to_string(iStart));
        this->infoStartValYText.setString(std::to_string(jStart));
        squares[iEnd][jEnd] = 4;
        this->infoFinishValXText.setString(std::to_string(iEnd));
        this->infoFinishValYText.setString(std::to_string(jEnd));

        this->squaresShape[iStart][jStart].setFillColor(sf::Color::Green);
        this->squaresShape[iEnd][jEnd].setFillColor(sf::Color::Blue);
    }
}

void GameState::updateButtons()
{
    if (this->finishButton.getGlobalBounds().contains(mousePosView)) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            this->selectedBuild = 2;
            this->finishButton.setFillColor(sf::Color::White);
            this->wallButton.setFillColor(sf::Color(20, 20, 20));
            this->startButton.setFillColor(sf::Color(20, 20, 20));
        }
    }    
    if (this->wallButton.getGlobalBounds().contains(mousePosView)) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            this->selectedBuild = 3;
           this->wallButton.setFillColor(sf::Color::White);
           this->finishButton.setFillColor(sf::Color(20, 20, 20));
           this->startButton.setFillColor(sf::Color(20, 20, 20));
        }
    }    
    if (this->startButton.getGlobalBounds().contains(mousePosView)) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            this->selectedBuild = 1;
            this->startButton.setFillColor(sf::Color::White);
            this->finishButton.setFillColor(sf::Color(20, 20, 20));
            this->wallButton.setFillColor(sf::Color(20, 20, 20));
        }
    }    
    if (!this->startDrawing) {

        if (this->clearShape.getGlobalBounds().contains(mousePosView)) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                this->infoProgressText.setString("0%");
                for (int j = 0; j < this->JDIM; j++) {
                    for (int i = 0; i < this->IDIM; i++) {
                        if (squares[i][j] != 2 && squares[i][j] != 4) {
                            squares[i][j] = 0;
                        }
                        if (sf::Color::Blue != squaresShape[i][j].getFillColor() &&
                            sf::Color::Green != squaresShape[i][j].getFillColor())
                            squaresShape[i][j].setFillColor(sf::Color(20, 20, 20));
                    }
                }

            }
        }    
    
        if (this->runShape.getGlobalBounds().contains(mousePosView)) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                this->elapsed3 = clock.getElapsedTime();
                if (this->elapsed3.asMilliseconds() > 500) {
                    this->initAsearch();
                    this->clock.restart();
                }
            }
        }

        if (this->randomShape.getGlobalBounds().contains(mousePosView)) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

                this->elapsed4 = clock.getElapsedTime();
                if (this->elapsed4.asMilliseconds() > 250) {
                    for (int j = 0; j < this->JDIM; j++) {
                        for (int i = 0; i < this->IDIM; i++) {
                            squares[i][j] = 0;
                            squaresShape[i][j].setFillColor(sf::Color(20, 20, 20));
                        }
                    }
                    this->infoProgressText.setString("0%");
                    int k = rand() % IDIM;
                    int l = rand() % JDIM;

                    iStart = k;
                    jStart = l;

                    squares[k][l] = 2;
                    squaresShape[k][l].setFillColor(sf::Color::Green);


                    k = rand() % IDIM;
                    l = rand() % JDIM;

                    iEnd = k;
                    jEnd = l;

                    squares[k][l] = 3;
                    squaresShape[k][l].setFillColor(sf::Color::Blue);
                    this->clock.restart();
                }

            }
        }
    }
}

void GameState::initFonts()
{
    //Loading font
    this->font.loadFromFile("fonts/arial.ttf");
}

void GameState::initButtons()
{

    this->infoShape.setOutlineColor(sf::Color(120, 120, 120));
    this->infoShape.setFillColor(sf::Color(20, 20, 20));
    this->infoShape.setPosition(sf::Vector2f(1100, 250));
    this->infoShape.setSize(sf::Vector2f(150, 135));
    this->infoShape.setOutlineThickness(5);
    this->clearShape.setOutlineColor(sf::Color(120, 120, 120));

    this->infoXText.setFont(this->font);
    this->infoXText.setFillColor(sf::Color::White);
    this->infoXText.setCharacterSize(15);
    this->infoXText.setPosition(sf::Vector2f(1160, 260));
    this->infoXText.setString("X");    
    
    this->infoYText.setFont(this->font);
    this->infoYText.setFillColor(sf::Color::White);
    this->infoYText.setCharacterSize(15);
    this->infoYText.setPosition(sf::Vector2f(1210, 260));
    this->infoYText.setString("Y");    
    
    this->infoFinishText.setFillColor(sf::Color::Blue);
    this->infoFinishText.setPosition(sf::Vector2f(1110, 290));
    this->infoFinishText.setSize(sf::Vector2f(25, 25)); 
    
    this->infoStartText.setFillColor(sf::Color::Green);
    this->infoStartText.setPosition(sf::Vector2f(1110, 320));
    this->infoStartText.setSize(sf::Vector2f(25, 25));

    this->infoRunShape.setFillColor(sf::Color::Red);
    this->infoRunShape.setPosition(sf::Vector2f(1110, 350));
    this->infoRunShape.setSize(sf::Vector2f(25, 25));
    // ------------

    this->infoRunXText.setFont(this->font);
    this->infoRunXText.setFillColor(sf::Color::White);
    this->infoRunXText.setCharacterSize(15);
    this->infoRunXText.setPosition(sf::Vector2f(1160, 355));

    this->infoRunYText.setFont(this->font);
    this->infoRunYText.setFillColor(sf::Color::White);
    this->infoRunYText.setCharacterSize(15);
    this->infoRunYText.setPosition(sf::Vector2f(1210, 355));

    this->infoProgressText.setFont(this->font);
    this->infoProgressText.setFillColor(sf::Color(20,20,20));
    this->infoProgressText.setCharacterSize(70);
    this->infoProgressText.setPosition(sf::Vector2f(700, 620));
    this->infoProgressText.setString("0%");

    // -------------
    this->infoFinishValXText.setFont(this->font);
    this->infoFinishValXText.setFillColor(sf::Color::White);
    this->infoFinishValXText.setCharacterSize(15);
    this->infoFinishValXText.setPosition(sf::Vector2f(1210, 290));

    this->infoStartValXText.setFont(this->font);
    this->infoStartValXText.setFillColor(sf::Color::White);
    this->infoStartValXText.setCharacterSize(15);
    this->infoStartValXText.setPosition(sf::Vector2f(1210, 325));

    this->infoFinishValYText.setFont(this->font);
    this->infoFinishValYText.setFillColor(sf::Color::White);
    this->infoFinishValYText.setCharacterSize(15);
    this->infoFinishValYText.setPosition(sf::Vector2f(1160, 290));

    this->infoStartValYText.setFont(this->font);
    this->infoStartValYText.setFillColor(sf::Color::White);
    this->infoStartValYText.setCharacterSize(15);
    this->infoStartValYText.setPosition(sf::Vector2f(1160, 325));
    
    this->infoKeysText.setFont(this->font);
    this->infoKeysText.setFillColor(sf::Color(30,30,30));
    this->infoKeysText.setCharacterSize(25);
    this->infoKeysText.setPosition(sf::Vector2f(50, 630));
    this->infoKeysText.setString("Press Enter to start or use on-screen buttons\nUse mouse to interact with the map");



    //----------------------------------

    this->runShape.setFillColor(sf::Color(20, 20, 20));
    this->runShape.setPosition(sf::Vector2f(1100, 480));
    this->runShape.setSize(sf::Vector2f(100, 50));
    this->runShape.setOutlineThickness(5);
    this->runShape.setOutlineColor(sf::Color(120, 120, 120));

    this->runText.setFont(this->font);
    this->runText.setFillColor(sf::Color::White);
    this->runText.setCharacterSize(20);
    this->runText.setPosition(sf::Vector2f(1130, 490));
    this->runText.setString("Run");

    this->randomShape.setFillColor(sf::Color(20, 20, 20));
    this->randomShape.setPosition(sf::Vector2f(1100, 410));
    this->randomShape.setSize(sf::Vector2f(100, 50));
    this->randomShape.setOutlineThickness(5);
    this->randomShape.setOutlineColor(sf::Color(120, 120, 120));

    this->randomText.setFont(this->font);
    this->randomText.setFillColor(sf::Color::White);
    this->randomText.setCharacterSize(20);
    this->randomText.setPosition(sf::Vector2f(1110, 420));
    this->randomText.setString("Random");

    this->clearShape.setFillColor(sf::Color(20, 20, 20));
    this->clearShape.setPosition(sf::Vector2f(1100, 550));
    this->clearShape.setSize(sf::Vector2f(100, 50));
    this->clearShape.setOutlineThickness(5);
    this->clearShape.setOutlineColor(sf::Color(120, 120, 120));

    this->clearText.setFont(this->font);
    this->clearText.setFillColor(sf::Color::White);
    this->clearText.setCharacterSize(20);
    this->clearText.setPosition(sf::Vector2f(1130, 560));
    this->clearText.setString("Clear");

    //-----------------------------------------

    this->finishButton.setFillColor(sf::Color(20, 20, 20));
    this->finishButton.setPosition(sf::Vector2f(1100, 100));
    this->finishButton.setRadius(12.f);
    this->finishButton.setOutlineThickness(5);
    this->finishButton.setOutlineColor(sf::Color(120, 120, 120));
    

    this->startButton.setFillColor(sf::Color(20, 20, 20));
    this->startButton.setPosition(sf::Vector2f(1100, 150));
    this->startButton.setRadius(12.f);
    this->startButton.setOutlineThickness(5);
    this->startButton.setOutlineColor(sf::Color(120, 120, 120));
   
    this->wallButton.setFillColor(sf::Color::White);
    this->wallButton.setPosition(sf::Vector2f(1100, 200));
    this->wallButton.setRadius(12.f);
    this->wallButton.setOutlineThickness(5);
    this->wallButton.setOutlineColor(sf::Color(120, 120, 120));

    this->finishButtonText.setFont(this->font);
    this->finishButtonText.setFillColor(sf::Color::White);
    this->finishButtonText.setCharacterSize(20);
    this->finishButtonText.setPosition(sf::Vector2f(1140, 100));
    this->finishButtonText.setString("Finish");

    this->startButtonText.setFont(this->font);
    this->startButtonText.setFillColor(sf::Color::White);
    this->startButtonText.setCharacterSize(20);
    this->startButtonText.setPosition(sf::Vector2f(1140, 150));
    this->startButtonText.setString("Start");

    this->wallButtonText.setFont(this->font);
    this->wallButtonText.setFillColor(sf::Color::White);
    this->wallButtonText.setCharacterSize(20);
    this->wallButtonText.setPosition(sf::Vector2f(1140, 200));
    this->wallButtonText.setString("Wall");
}

void GameState::updateMousePos()
{
    this->mousePosScreen = sf::Mouse::getPosition();
    this->mousePosWindow = sf::Mouse::getPosition(*this->mWindow);
    this->mousePosView = mWindow->mapPixelToCoords(sf::Mouse::getPosition(*this->mWindow));
}

void GameState::initNodeShape()
{
	//fixed size

    for (int j = 0; j < this->JDIM; j++) {
        for (int i = 0; i < this->IDIM; i++) {
            squaresShape[i][j].setSize(sf::Vector2f(25, 25));
            squaresShape[i][j].setFillColor(sf::Color(20,20,20));
            squaresShape[i][j].setOrigin(sf::Vector2f(-30,-85));
            squaresShape[i][j].setPosition(sf::Vector2f(26 * i, 26 * j));
        }
    }

    // create empty squares
    for (int j = 0; j < this->JDIM; j++) {
        for (int i = 0; i < this->IDIM; i++) {
            squares[i][j] = 0;
        }
    }

}

void GameState::initAsearch()
{

	//Squares is 2D map
	//0 - clear path
	//1 - Wall

    //CLEAR
    for (int j = 0; j < this->JDIM; j++) {
        for (int i = 0; i < this->IDIM; i++) {
            if (sf::Color::White != squaresShape[i][j].getFillColor() &&
                sf::Color::Blue != squaresShape[i][j].getFillColor() &&
                sf::Color::Green != squaresShape[i][j].getFillColor())
                squaresShape[i][j].setFillColor(sf::Color(20, 20, 20));
        }
    }
    this->maxi2 = 0;

	// get the path
	std::string path = this->Apathfind(Location(iStart, jStart), Location(iEnd, jEnd));

    if (!path.empty()) this->startDrawing = true;

    // follow the path on the squares and display it 
    if (path.length() > 0) {
        char c;
        int m, n;
        int i = iStart;
        int j = jStart;
        

        for (m = 0; m < path.length(); m++) {
            c = path.at(m);
            n = atoi(&c);
            //locate path
            i += iDir[n];
            j += jDir[n];
            //plot path
            squares[i][j] = 3;
            //this->squaresShape[i][j].setFillColor(sf::Color::Red);
            this->vect.push_back(std::make_pair(i, j));
        }
        this->maxi = vect.size();
        //i j are now at end so mark finish 4
        squares[i][j] = 4;
        this->squaresShape[i][j].setFillColor(sf::Color::Blue);

    }
}

void GameState::drawNodes()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        
        this->elapsed2 = clock.getElapsedTime();
        if (this->elapsed2.asMilliseconds() > 500) {
            this->initAsearch();
            this->clock.restart();
        }
    }


}

std::string GameState::Apathfind(const Location& locStart, const Location& locFinish)
{
    // A-star algorithm.
// The path returned is a string of direction digits.

    // list of open (not-yet-checked-out) nodes
    static std::priority_queue<Node> q[2];

    // q index
    static int qi;

    static Node* pNode1;
    static Node* pNode2;
    static int i, j, row, col, iNext, jNext;
    static char c;
    qi = 0;

    // reset the Node lists (0 = ".")
    for (j = 0; j < JDIM; j++) {
        for (i = 0; i < IDIM; i++) {
            closedNodes[i][j] = 0;
            openNodes[i][j] = 0;
        }
    }

    // create the start node and push into list of open nodes
    pNode1 = new Node(locStart, 0, 0);
    pNode1->calculateFValue(locFinish);
    q[qi].push(*pNode1);

    // A* search
    while (!q[qi].empty()) {
        // get the current node w/ the lowest FValue
        // from the list of open nodes
        pNode1 = new Node(q[qi].top().getLocation(),
            q[qi].top().getGValue(), q[qi].top().getFValue());

        row = (pNode1->getLocation()).row;
        col = pNode1->getLocation().col;
        //cout << "row, col=" << row << "," << col << endl;

        // remove the node from the open list
        q[qi].pop();
        openNodes[row][col] = 0;

        // mark it on the closed nodes list
        closedNodes[row][col] = 1;

        // stop searching when the goal state is reached
        if (row == locFinish.row && col == locFinish.col) {
            // drawing direction map
            //cout << endl;
            //for (j = JDIM - 1; j >= 0; j--) {
            //    for (i = 0; i < IDIM; i++) {
            //        cout << dirMap[i][j];
            //    }
            //    cout << endl;
            //}
            //cout << endl;

            // generate the path from finish to start from dirMap
            std::string path = "";
            while (!(row == locStart.row && col == locStart.col)) {
                j = dirMap[row][col];
                c = '0' + (j + 4 / 2) % 4;
                path = c + path;
                row += iDir[j];
                col += jDir[j];
            }

            // garbage collection
            delete pNode1;

            // empty the leftover nodes
            while (!q[qi].empty()) q[qi].pop();
            return path;
        }

        // generate moves in all possible directions
        for (i = 0; i < 4; i++) {
            iNext = row + iDir[i];
            jNext = col + jDir[i];

            // if not wall (obstacle) nor in the closed list
            if (!(iNext < 0 || iNext > IDIM - 1 || jNext < 0 || jNext > JDIM - 1 ||
                squares[iNext][jNext] == 1 || closedNodes[iNext][jNext] == 1)) {

                // generate a child node
                pNode2 = new Node(Location(iNext, jNext), pNode1->getGValue(), pNode1->getFValue());
                pNode2->updateGValue(i);
                pNode2->calculateFValue(locFinish);

                // if it is not in the open list then add into that
                if (openNodes[iNext][jNext] == 0) {
                    openNodes[iNext][jNext] = pNode2->getFValue();
                    q[qi].push(*pNode2);
                    // mark its parent node direction
                    dirMap[iNext][jNext] = (i + 4 / 2) % 4;
                }

                // already in the open list
                else if (openNodes[iNext][jNext] > pNode2->getFValue()) {
                    // update the FValue info
                    openNodes[iNext][jNext] = pNode2->getFValue();

                    // update the parent direction info,  mark its parent node direction
                    dirMap[iNext][jNext] = (i + 4 / 2) % 4;

                    // replace the node by emptying one q to the other one
                    // except the node to be replaced will be ignored
                    // and the new node will be pushed in instead
                    while (!(q[qi].top().getLocation().row == iNext &&
                        q[qi].top().getLocation().col == jNext)) {
                        q[1 - qi].push(q[qi].top());
                        q[qi].pop();
                    }

                    // remove the wanted node
                    q[qi].pop();

                    // empty the larger size q to the smaller one
                    if (q[qi].size() > q[1 - qi].size()) qi = 1 - qi;
                    while (!q[qi].empty()) {
                        q[1 - qi].push(q[qi].top());
                        q[qi].pop();
                    }
                    qi = 1 - qi;

                    // add the better node instead
                    q[qi].push(*pNode2);
                }
                else delete pNode2;
            }
        }
        delete pNode1;
    }
    // no path found
    return "";
    
}

GameState::GameState(sf::RenderWindow* mWindow)
{
    this->mWindow = mWindow;

    this->initFonts();
    this->initButtons();

	this->initNodeShape();
  
}

GameState::~GameState()
{
	
}

void GameState::update(const float& dt)
{

    this->updateMousePos();
    this->drawNodes();
    this->updateWall();
    this->updateButtons();

    if (startDrawing) {
        
        this->elapsed1 = clock.getElapsedTime();
        
        if (this->elapsed1.asMilliseconds() > 100) {

            std::pair <int, int > a = *this->vect.begin();
            this->vect.erase(this->vect.begin());

            this->squaresShape[a.first][a.second].setFillColor(sf::Color::Red);
            this->infoRunXText.setString(std::to_string(a.second));
            this->infoRunYText.setString(std::to_string(a.first));

            this->maxi2++;
            this->infoProgressText.setString(std::to_string(this->map(maxi2,0,this->maxi-1, 0, 100)) + "%");

            if (vect.size() < 2) {
                startDrawing = false;
                vect.clear();
            }
            this->clock.restart();
        }
    }

}

void GameState::render(sf::RenderTarget& mTarget)
{
	
    for (int j = 0; j < this->JDIM; j++) {
        for (int i = 0; i < this->IDIM; i++) {
            mTarget.draw(squaresShape[i][j]);
        }
    }

    mTarget.draw(this->clearShape);
    mTarget.draw(this->clearText);

    mTarget.draw(this->runShape);
    mTarget.draw(this->runText);

    mTarget.draw(this->infoShape);
    mTarget.draw(this->infoXText);
    mTarget.draw(this->infoYText);
    mTarget.draw(this->infoStartText);
    mTarget.draw(this->infoRunShape);
    mTarget.draw(this->infoRunXText);
    mTarget.draw(this->infoRunYText);
    mTarget.draw(this->infoStartValXText);
    mTarget.draw(this->infoStartValYText);
    mTarget.draw(this->infoFinishText);
    mTarget.draw(this->infoFinishValXText);
    mTarget.draw(this->infoFinishValYText);


    mTarget.draw(this->finishButton);
    mTarget.draw(this->finishButtonText);

    mTarget.draw(this->randomShape);
    mTarget.draw(this->randomText);

    mTarget.draw(this->startButton);
    mTarget.draw(this->startButtonText);

    mTarget.draw(this->wallButton);
    mTarget.draw(this->wallButtonText);

    mTarget.draw(this->infoKeysText);
    mTarget.draw(this->infoProgressText);
}
