#include <fstream>
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <map>
#include <vector>
#include <ostream>
#include <ctime>
#include <random>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <ctime>
using namespace std;




class Botton
{
public:
    vector<Botton*> neibors;

    int emptytilevalue = -1;
    char neiborZfound = '0';
    char mineOrNah = '0';
    char revealedOrNah = '0';
    int howManyAdjacentMines = 0;
    int howManyAdjacentTilesWithAdjacentMines = 0;
    sf::Sprite tile/*, undertile*/, base;
    void setPos(float x, float y)
    {
        tile.setPosition(x, y);
        // undertile.setPosition(x, y);
        base.setPosition(x, y);

    }


    void DrawSprite(sf::RenderWindow& window, int check = 0)
    {
        window.draw(base);
        //window.draw(undertile);
        if (check != 1)
        {
            window.draw(tile);
        }
    }

    void setAdjacentMineTexture(sf::Texture& num_1, sf::Texture& num_2, sf::Texture& num_3, sf::Texture& num_4, sf::Texture& num_5, sf::Texture& num_6, sf::Texture& num_7, sf::Texture& num_8)
    {
        if (howManyAdjacentMines == 1)
        {
            tile.setTexture(num_1);
        }
        if (howManyAdjacentMines == 2)
        {
            tile.setTexture(num_2);
        }
        if (howManyAdjacentMines == 3)
        {
            tile.setTexture(num_3);
        }
        if (howManyAdjacentMines == 4)
        {
            tile.setTexture(num_4);
        }
        if (howManyAdjacentMines == 5)
        {
            tile.setTexture(num_5);
        }
        if (howManyAdjacentMines == 6)
        {
            tile.setTexture(num_6);
        }
        if (howManyAdjacentMines == 7)
        {
            tile.setTexture(num_7);
        }
        if (howManyAdjacentMines == 8)
        {
            tile.setTexture(num_8);
        }

    }
    float vx;
    float vy;

};

class Board
{
public:
    int xEnd;
    int yEnd;
    int bRows;
    int bColums;
    vector<vector<Botton>> setBoard(int rows, int colums)
    {
        bRows = rows;
        bColums = colums;
        vector<vector<Botton>> board(rows);
        for (int i = 0; i < rows; i++)
        {
            board[i] = vector<Botton>(colums);
        }

        int ccheck = 0;
        int rcheck = 0;
        for (int i = 0; i < (rows * colums); i++)
        {

            Botton buttonb;


            if (ccheck <= (colums)-1)
            {
                if (ccheck != (colums)-1)
                {
                    buttonb.vx = rcheck;
                    buttonb.vy = ccheck;
                    board[rcheck][ccheck] = buttonb;
                    ccheck++;

                }
                else { ccheck = 0; rcheck++; }
            }
        }

        return board;
    }

    void SetBoardPosition(float wWidth, float wLength, vector<vector<Botton>>& board)
    {

        float currentX = 0;
        float currentY = 0;
        int check = 0;
        for (int i = 0; i <= bRows - 1; i++)
        {



            for (int j = 0; j <= bColums - 1; j++)
            {
                board[i][j].setPos(currentX, currentY);



                currentX += 32;

                if (currentX >= wWidth || j == bColums - 1)
                {
                    check = 1;
                    currentY += 32;
                    currentX = 0;

                    break;
                }

            }
        }


        xEnd = board[bRows - 1][bColums - 1].base.getPosition().x + 32;
        yEnd = board[bRows - 1][bColums - 1].base.getPosition().y + 32;
    }


    void DrawBoard(vector<vector<Botton>>& board, sf::RenderWindow& window, int check = 0, int x = -1, int y = -1)
    {
        for (int i = 0; i <= bRows - 1; i++)
        {
            for (int j = 0; j <= bColums - 1; j++)
            {
                board[i][j].DrawSprite(window, check);


            }
        }
    }


};


class Random
{
    static std::mt19937 random;
public:
    static int Number(int min, int max)
    {
        std::uniform_int_distribution<int> dist(min, max);

        return dist(random);
    }
};

class testButton
{
public:

    sf::Sprite button;
};

std::mt19937 Random::random(time(0));



class File {
public:

    int brd_rows = 0;
    int brd_colums = 0;
    int temp_colums = 0;
    int testColumCheck = 0;

    //one less than actual, count starts at 0 for vectors;
    int test_numbeerofEnters;

    vector<vector<char>> loadTestBoard(int rows, int colums, const char* filename)
    {
        int checkplas = 0;
        ifstream testBoard(filename);


        char ch;
        vector<vector<char>> testboardVector(rows);

        for (int i = 0; i < rows; i++)
        {
            testboardVector[i] = vector<char>(colums);
        }


        while (testBoard.get(ch))
        {
            if (brd_rows >= rows) { break; }

            if (ch == '\n' || temp_colums >= colums)
            {
                brd_rows++;

                if (testColumCheck == 0) { testColumCheck = 1; }

                if (testColumCheck == 1)
                {
                    brd_colums = temp_colums - 1;

                    temp_colums = 0;
                    testColumCheck = 2;
                }
                else { temp_colums = 0; }

                continue;
            }

          
            testboardVector[brd_rows][temp_colums] = ch;

            temp_colums++;
        }


        //one less than actual, count starts at 0 for vectors;
        test_numbeerofEnters = brd_rows - 2;

        return testboardVector;
    }

    vector<vector<char>> loadRandomBoard(int rows, int colums, int mines)
    {
        char ch;
        int numof1s = 0;
        int checkamount = 0;
        int difference = 0;
        vector<vector<char>> testboardVector(rows);

        for (int i = 0; i < rows; i++)
        {
            testboardVector[i] = vector<char>(colums);
        }


        for (int i = 0; i <= rows - 1; i++)
        {
            for (int j = 0; j <= colums - 1; j++)
            {
                testboardVector[i][j] = '0';

            }
        }



        for (int z = 0; z <= mines; z++)
        {
            int rvalue = 0;
            int cvalue = 0;

            rvalue = Random::Number(0, rows - 1);
            cvalue = Random::Number(0, colums - 1);
            if (z == mines)
            {
                break;
            }

            if (testboardVector[rvalue][cvalue] == '1')
            {
                if (rvalue != rows - 1) {
                    if (testboardVector[rvalue + 1][cvalue] != '1')
                    {
                        testboardVector[rvalue + 1][cvalue] = '1';
                    }
                }

            }
            testboardVector[rvalue][cvalue] = '1';

        }

        for (int i = 0; i <= rows - 1; i++)
        {
            for (int j = 0; j <= colums - 1; j++)
            {
                if (testboardVector[i][j] == '1')
                {
                    numof1s += 1;
                }

            }
        }

        if (numof1s < mines)
        {
            int checkminesValuer = Random::Number(0, rows - 1);
            int checkmineValuec = Random::Number(0, colums - 1);
            difference = mines - numof1s;
            for (int i = 0; i < difference; i++)
            {
                while (testboardVector[checkminesValuer][checkmineValuec] != '0')
                {
                    checkminesValuer = Random::Number(0, rows - 1);
                    checkmineValuec = Random::Number(0, colums - 1);
                }

                testboardVector[checkminesValuer][checkmineValuec] = '1';
            }
        }

        return testboardVector;
    }

};




class MineDisplay
{
public:
    MineDisplay& operator=(MineDisplay& copyingdisplay)
    {
        //place = copyingdisplay.place;
        spriteNum = copyingdisplay.spriteNum;
        value = copyingdisplay.value;
        return *this;
    }
    string value;
    int place = -1;
    sf::Sprite spriteNum;
    void setDisplay(int currentminesForDisplay)
    {
        string currentminesNum = to_string(currentminesForDisplay);



    };
    void digitPlacement(int yEnd, int delte = 0, int checkifThirdDigit = 0)
    {
        if (checkifThirdDigit == 0)
        {
            if (place == 1)
            {
                spriteNum.setPosition(21, yEnd);
            }
            if (place == 2)
            {
                spriteNum.setPosition(42, yEnd);

            }
            if (place == 3)
            {
                spriteNum.setPosition(63, yEnd);
            }
        }
    }

};



void revursiveRevealFunction(int starter, int i, int j, vector <Botton>& emptytiles, vector<vector<Botton>>& boardVect, int recur_check1, int recur_check2, int recur_check3, int recur_check4, int recur_check5, int recur_check6)
{







    if (boardVect[i][j].howManyAdjacentMines == 0 && boardVect[i][j].mineOrNah == '0') {
        for (int z = 0; z <= boardVect[i][j].neibors.size() - 1; z++)
        {
            //  
            boardVect[i][j].revealedOrNah = '1';
            boardVect[i][j].neibors[z]->revealedOrNah = '1';
            boardVect[i][j].neiborZfound = '1';

            // 

            if (boardVect[i][j].neibors[z]->emptytilevalue >= 0 && boardVect[i][j].neibors[z]->howManyAdjacentMines == 0 && boardVect[i][j].neibors[z]->neiborZfound == '0')
            {
                boardVect[i][j].neibors[z]->neiborZfound = '1';
                revursiveRevealFunction(starter, boardVect[i][j].neibors[z]->vx, boardVect[i][j].neibors[z]->vy, emptytiles, boardVect, recur_check1, recur_check2, recur_check3, recur_check4, recur_check5, recur_check6);
            }
        }
    }
    else {
        if (boardVect[i][j].mineOrNah == '0') {
            boardVect[i][j].revealedOrNah = '1';
        }
    }

    return;
}

int main()
{

    sf::Texture  hiddentile, mine, num_1, num_2, flag;
    sf::Texture   num_3, num_4, num_5, num_6, num_7, num_8, revealedtile, textureTestbrd_1, textureTestbrd_2, textureTestbrd_3, textureDebugButton;
    sf::Texture textureMineDisplay_0, textureMineDisplay_1, textureMineDisplay_2, textureMineDisplay_3, textureMineDisplay_4;
    sf::Texture textureMineDisplay_5, textureMineDisplay_6, textureMineDisplay_7, textureMineDisplay_8, textureMineDisplay_9, textureMineDisplay_negative;
    sf::Texture face_happy, face_win, face_lose;



    hiddentile.loadFromFile("images/tile_hidden.png");
    revealedtile.loadFromFile("images/tile_revealed.png");
    mine.loadFromFile("images/mine.png");
    num_1.loadFromFile("images/number_1.png");
    num_2.loadFromFile("images/number_2.png");
    num_3.loadFromFile("images/number_3.png");
    num_4.loadFromFile("images/number_4.png");
    num_5.loadFromFile("images/number_5.png");
    num_6.loadFromFile("images/number_6.png");
    num_7.loadFromFile("images/number_7.png");
    num_8.loadFromFile("images/number_8.png");
    flag.loadFromFile("images/flag.png");
    textureTestbrd_1.loadFromFile("images/test_1.png");
    textureTestbrd_2.loadFromFile("images/test_2.png");
    textureTestbrd_3.loadFromFile("images/test_3.png");
    textureDebugButton.loadFromFile("images/debug.png");


    face_happy.loadFromFile("images/face_happy.png");
    face_win.loadFromFile("images/face_win.png");
    face_lose.loadFromFile("images/face_lose.png");




    MineDisplay mineDisplay_0, mineDisplay_1, mineDisplay_2, mineDisplay_3, mineDisplay_4;
    MineDisplay mineDisplay_5, mineDisplay_6, mineDisplay_7, mineDisplay_8, mineDisplay_9, mineDisplay_negative;


    textureMineDisplay_0.loadFromFile("images/digits.png", sf::IntRect(0, 0, 21, 32));
    textureMineDisplay_1.loadFromFile("images/digits.png", sf::IntRect(21, 0, 21, 32));
    textureMineDisplay_2.loadFromFile("images/digits.png", sf::IntRect(42, 0, 21, 32));
    textureMineDisplay_3.loadFromFile("images/digits.png", sf::IntRect(63, 0, 21, 32));
    textureMineDisplay_4.loadFromFile("images/digits.png", sf::IntRect(84, 0, 21, 32));
    textureMineDisplay_5.loadFromFile("images/digits.png", sf::IntRect(105, 0, 21, 32));
    textureMineDisplay_6.loadFromFile("images/digits.png", sf::IntRect(126, 0, 21, 32));
    textureMineDisplay_7.loadFromFile("images/digits.png", sf::IntRect(147, 0, 21, 32));
    textureMineDisplay_8.loadFromFile("images/digits.png", sf::IntRect(168, 0, 21, 32));
    textureMineDisplay_9.loadFromFile("images/digits.png", sf::IntRect(189, 0, 21, 32));
    textureMineDisplay_negative.loadFromFile("images/digits.png", sf::IntRect(210, 0, 21, 32));

    mineDisplay_0.spriteNum.setTexture(textureMineDisplay_0);
    mineDisplay_1.spriteNum.setTexture(textureMineDisplay_1);
    mineDisplay_2.spriteNum.setTexture(textureMineDisplay_2);
    mineDisplay_3.spriteNum.setTexture(textureMineDisplay_3);
    mineDisplay_4.spriteNum.setTexture(textureMineDisplay_4);
    mineDisplay_5.spriteNum.setTexture(textureMineDisplay_5);
    mineDisplay_6.spriteNum.setTexture(textureMineDisplay_6);
    mineDisplay_7.spriteNum.setTexture(textureMineDisplay_7);
    mineDisplay_8.spriteNum.setTexture(textureMineDisplay_8);
    mineDisplay_9.spriteNum.setTexture(textureMineDisplay_9);


    mineDisplay_0.value = "0";
    mineDisplay_1.value = "1";
    mineDisplay_2.value = "2";
    mineDisplay_3.value = "3";
    mineDisplay_4.value = "4";
    mineDisplay_5.value = "5";
    mineDisplay_6.value = "6";
    mineDisplay_7.value = "7";
    mineDisplay_8.value = "8";
    mineDisplay_9.value = "9";
    mineDisplay_negative.value = "-";

    MineDisplay firstDigitOnDisplay, secondDigitOnDisplay, thirdDigitOnDisplay;



    int rows;
    int colums;
    int mines;

    ifstream config("boards/config.cfg");
    string token;

    getline(config, token, '\n');

    colums = stoi(token);

    getline(config, token, '\n');

    rows = stoi(token);

    getline(config, token, '\n');

    mines = stoi(token);



    // start of reading test board 1 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    File test_board1;
    vector<vector<char>> test_board1_Vect;
    test_board1_Vect = test_board1.loadTestBoard(rows, colums, "boards/testboard1.brd");


    File test_board2;
    vector<vector<char>> test_board2_Vect;
    test_board2_Vect = test_board2.loadTestBoard(rows, colums, "boards/testboard2.brd");

    File test_board3;
    vector<vector<char>> test_board3_Vect;
    test_board3_Vect = test_board3.loadTestBoard(rows, colums, "boards/testboard3.brd");

    File random_board;
    vector<vector<char>> random_board_Vect;
    random_board_Vect = random_board.loadRandomBoard(rows, colums, mines);






    sf::RenderWindow window(sf::VideoMode(colums * 32, (rows * 32) + 100), "Minesweeper");

    Board board;

    vector<vector<Botton>> boardVect = board.setBoard(rows, colums);




    for (int i = 0; i <= board.bRows - 1; i++)
    {
        for (int j = 0; j <= board.bColums - 1; j++)
        {
            boardVect[i][j].base.setTexture(revealedtile);
            boardVect[i][j].tile.setTexture(hiddentile);
        }
    }



    board.SetBoardPosition(window.getSize().x, window.getSize().y, boardVect);




    int check = 0;








    testButton testboard1Button;
    testboard1Button.button.setTexture(textureTestbrd_1);
    testboard1Button.button.setPosition(board.xEnd / 2 + 208, board.yEnd);


    testButton testboard2Button;
    testboard2Button.button.setTexture(textureTestbrd_2);
    testboard2Button.button.setPosition(board.xEnd / 2 + 272, board.yEnd);



    testButton testboard3Button;
    testboard3Button.button.setTexture(textureTestbrd_3);
    testboard3Button.button.setPosition(board.xEnd / 2 + 336, board.yEnd);


    testButton debugButton;
    debugButton.button.setTexture(textureDebugButton);
    debugButton.button.setPosition(board.xEnd / 2 + 144, board.yEnd);

    testButton resetFace;
    resetFace.button.setTexture(face_happy);
    resetFace.button.setPosition(board.xEnd / 2, board.yEnd);


    int currentminesForDisplay = 0;


    

    static int yOrNoDebug = 0;
    int checkdebugnum2 = 0;

    int cyclecheck = 0;

    int numofFlags = 0;

    firstDigitOnDisplay = mineDisplay_0;
    firstDigitOnDisplay.place = 1;

    secondDigitOnDisplay = mineDisplay_0;
    secondDigitOnDisplay.place = 2;

    thirdDigitOnDisplay = mineDisplay_0;
    thirdDigitOnDisplay.place = 3;

    firstDigitOnDisplay.digitPlacement(board.yEnd);
    secondDigitOnDisplay.digitPlacement(board.yEnd);
    thirdDigitOnDisplay.digitPlacement(board.yEnd);

    const sf::Color& color = sf::Color(255, 255, 255, 255);
    const sf::Color& color2 = sf::Color(0, 0, 0, 0);
    sf::Texture cleartexture;

    sf::RectangleShape rectangle(sf::Vector2f(21.f, 32.f));

    rectangle.setFillColor(color);
    rectangle.setPosition(0, board.yEnd);


    mineDisplay_negative.spriteNum.setPosition(0, board.yEnd);
    mineDisplay_negative.spriteNum.setTexture(textureMineDisplay_negative);

    int checkminebug = 0;
    vector<Botton> emptytiles;
    int empttilchecker = 0;


    int amountOfRevealedTiles = 0;
    int amountoftilesWithoutMine = 0;
    int gameOver = 0;
    int defeat = 0;


    random_board_Vect = random_board.loadRandomBoard(board.bRows, board.bColums, mines);
    for (int i = 0; i <= board.bRows - 1; i++)
    {
        for (int j = 0; j <= board.bColums - 1; j++)
        {
            boardVect[i][j].revealedOrNah = '0';

            boardVect[i][j].base.setTexture(revealedtile);
            boardVect[i][j].tile.setTexture(hiddentile);
            boardVect[i][j].mineOrNah = random_board_Vect[i][j];
         





            if (yOrNoDebug == 1 && boardVect[i][j].mineOrNah == '1')
            {

                boardVect[i][j].base.setTexture(hiddentile);
                boardVect[i][j].tile.setTexture(mine);
            }
            else { boardVect[i][j].revealedOrNah = '0'; }
           

        }
    }

    // run the program as long as the window is open
    while (window.isOpen())
    {


        currentminesForDisplay = 0;

        emptytiles.clear();

        for (int i = 0; i <= board.bRows - 1; i++)
        {

            for (int j = 0; j <= board.bColums - 1; j++)
            {
                if (boardVect[i][j].mineOrNah == '0' && boardVect[i][j].howManyAdjacentMines == 0)
                {
                    emptytiles.push_back(boardVect[i][j]);
                    boardVect[i][j].emptytilevalue = empttilchecker;
                    empttilchecker += 1;
                }
            }
        }




        for (int i = 0; i <= board.bRows - 1; i++)
        {

            for (int j = 0; j <= board.bColums - 1; j++)
            {
                if ((boardVect[i][j].mineOrNah == '1' && boardVect[i][j].revealedOrNah != '1') || (boardVect[i][j].mineOrNah == '5' && boardVect[i][j].revealedOrNah != '1'))
                {
                    currentminesForDisplay++;
                }
            }
        }


        amountOfRevealedTiles = 0;
        amountoftilesWithoutMine = 0;

        for (int i = 0; i <= board.bRows - 1; i++)
        {

            for (int j = 0; j <= board.bColums - 1; j++)
            {
                if (boardVect[i][j].mineOrNah == '0' && boardVect[i][j].revealedOrNah == '1')
                {
                    amountOfRevealedTiles += 1;
                }

                if (boardVect[i][j].mineOrNah == '0' || boardVect[i][j].mineOrNah == '4')
                {
                    amountoftilesWithoutMine += 1;
                }

            }
        }


        

        if (amountoftilesWithoutMine == amountOfRevealedTiles)
        {
            gameOver = 1;
        }

        if (gameOver == 0)
        {
            defeat = 0;
            resetFace.button.setTexture(face_happy);
        }


        if (gameOver == 1 && defeat == 0)
        {
            resetFace.button.setTexture(face_win);


            for (int i = 0; i <= board.bRows - 1; i++)
            {

                for (int j = 0; j <= board.bColums - 1; j++)
                {
                    if (boardVect[i][j].mineOrNah == '1')
                    {
                        boardVect[i][j].base.setTexture(hiddentile);
                        boardVect[i][j].tile.setTexture(flag);
                       
                    }

                }
            }



        }

        currentminesForDisplay -= numofFlags;

        if (gameOver == 1 && defeat == 0)
        {
            currentminesForDisplay = 0;
        }

        
        string parsinfMines;
        string backup;

        if (currentminesForDisplay >= 0)
        {
            parsinfMines = to_string(currentminesForDisplay);

        }
        else
        {
            backup = to_string(currentminesForDisplay);
            parsinfMines = backup.substr(1, backup.size());

        }

        string firstNum = parsinfMines.substr(0, 1);
        string secondNum;
        string thirdNum;

         

        if (currentminesForDisplay > 9 || currentminesForDisplay < -9)
        {
            secondNum = parsinfMines.substr(1, 1);

        }

        if ((currentminesForDisplay > 99 && currentminesForDisplay <= 999) || currentminesForDisplay < -99 && currentminesForDisplay >= -999)
        {
            thirdNum = parsinfMines.substr(2, 3);

        }

        

        if (firstNum == "0")
        {
            if (currentminesForDisplay <= 9 && currentminesForDisplay >= -9)
            {
                mineDisplay_0.place = 3;
                thirdDigitOnDisplay = mineDisplay_0;
                thirdDigitOnDisplay.digitPlacement(board.yEnd);
            }
            if (currentminesForDisplay >= 10 || currentminesForDisplay <= -10)
            {
                mineDisplay_0.place = 2;
                secondDigitOnDisplay = mineDisplay_0;
                secondDigitOnDisplay.digitPlacement(board.yEnd);
            }
            if ((currentminesForDisplay >= 100 && currentminesForDisplay <= 999) || (currentminesForDisplay < -99 && currentminesForDisplay >= -999))
            {
                mineDisplay_0.place = 1;
                firstDigitOnDisplay = mineDisplay_0;
                firstDigitOnDisplay.digitPlacement(board.yEnd);
            }
        }
        if (firstNum == "1")
        {
            if (currentminesForDisplay <= 9 && currentminesForDisplay >= -9)
            {
                mineDisplay_1.place = 3;
                thirdDigitOnDisplay = mineDisplay_1;
                thirdDigitOnDisplay.digitPlacement(board.yEnd);
            }
            if (currentminesForDisplay >= 10 || currentminesForDisplay <= -10)
            {
                mineDisplay_1.place = 2;
                secondDigitOnDisplay = mineDisplay_1;
                secondDigitOnDisplay.digitPlacement(board.yEnd);
            }
            if ((currentminesForDisplay >= 100 && currentminesForDisplay <= 999) || (currentminesForDisplay < -99 && currentminesForDisplay >= -999))
            {
                mineDisplay_1.place = 1;
                firstDigitOnDisplay = mineDisplay_1;
                firstDigitOnDisplay.digitPlacement(board.yEnd);
            }
        }
        if (firstNum == "2")
        {
            if (currentminesForDisplay <= 9 && currentminesForDisplay >= -9)
            {
                mineDisplay_2.place = 3;
                thirdDigitOnDisplay = mineDisplay_2;
                thirdDigitOnDisplay.digitPlacement(board.yEnd);
            }
            if (currentminesForDisplay >= 10 || currentminesForDisplay <= -10)
            {
                mineDisplay_2.place = 2;
                secondDigitOnDisplay = mineDisplay_2;
                secondDigitOnDisplay.digitPlacement(board.yEnd);
            }
            if ((currentminesForDisplay >= 100 && currentminesForDisplay <= 999) || (currentminesForDisplay < -99 && currentminesForDisplay >= -999))
            {
                mineDisplay_2.place = 1;
                firstDigitOnDisplay = mineDisplay_2;
                firstDigitOnDisplay.digitPlacement(board.yEnd);
            }
        }
        if (firstNum == "3")
        {
            if (currentminesForDisplay <= 9 && currentminesForDisplay >= -9)
            {
                mineDisplay_3.place = 3;
                thirdDigitOnDisplay = mineDisplay_3;
                thirdDigitOnDisplay.digitPlacement(board.yEnd);
            }
            if (currentminesForDisplay >= 10 || currentminesForDisplay <= -10)
            {
                mineDisplay_3.place = 2;
                secondDigitOnDisplay = mineDisplay_3;
                secondDigitOnDisplay.digitPlacement(board.yEnd);
            }
            if ((currentminesForDisplay >= 100 && currentminesForDisplay <= 999) || (currentminesForDisplay < -99 && currentminesForDisplay >= -999))
            {
                mineDisplay_3.place = 1;
                firstDigitOnDisplay = mineDisplay_3;
                firstDigitOnDisplay.digitPlacement(board.yEnd);
            }
        }
        if (firstNum == "4")
        {
            if (currentminesForDisplay <= 9 && currentminesForDisplay >= -9)
            {
                mineDisplay_4.place = 3;
                thirdDigitOnDisplay = mineDisplay_4;
                thirdDigitOnDisplay.digitPlacement(board.yEnd);
            }
            if (currentminesForDisplay >= 10 || currentminesForDisplay <= -10)
            {
                mineDisplay_4.place = 2;
                secondDigitOnDisplay = mineDisplay_4;
                secondDigitOnDisplay.digitPlacement(board.yEnd);
            }
            if ((currentminesForDisplay >= 100 && currentminesForDisplay <= 999) || (currentminesForDisplay < -99 && currentminesForDisplay >= -999))
            {
                mineDisplay_4.place = 1;
                firstDigitOnDisplay = mineDisplay_4;
                firstDigitOnDisplay.digitPlacement(board.yEnd);
            }
        }
        if (firstNum == "5")
        {
            if (currentminesForDisplay <= 9 && currentminesForDisplay >= -9)
            {
                mineDisplay_5.place = 3;
                thirdDigitOnDisplay = mineDisplay_5;
                thirdDigitOnDisplay.digitPlacement(board.yEnd);
            }
            if (currentminesForDisplay >= 10 || currentminesForDisplay <= -10)
            {
                mineDisplay_5.place = 2;
                secondDigitOnDisplay = mineDisplay_5;
                secondDigitOnDisplay.digitPlacement(board.yEnd);
            }
            if ((currentminesForDisplay >= 100 && currentminesForDisplay <= 999) || (currentminesForDisplay < -99 && currentminesForDisplay >= -999))
            {
                mineDisplay_5.place = 1;
                firstDigitOnDisplay = mineDisplay_5;
                firstDigitOnDisplay.digitPlacement(board.yEnd);
            }
        }
        if (firstNum == "6")
        {
            if (currentminesForDisplay <= 9 && currentminesForDisplay >= -9)
            {
                mineDisplay_6.place = 3;
                thirdDigitOnDisplay = mineDisplay_6;
                thirdDigitOnDisplay.digitPlacement(board.yEnd);
            }
            if (currentminesForDisplay >= 10 || currentminesForDisplay <= -10)
            {
                mineDisplay_6.place = 2;
                secondDigitOnDisplay = mineDisplay_6;
                secondDigitOnDisplay.digitPlacement(board.yEnd);
            }
            if ((currentminesForDisplay >= 100 && currentminesForDisplay <= 999) || (currentminesForDisplay < -99 && currentminesForDisplay >= -999))
            {
                mineDisplay_6.place = 1;
                firstDigitOnDisplay = mineDisplay_6;
                firstDigitOnDisplay.digitPlacement(board.yEnd);
            }
        }
        if (firstNum == "7")
        {
            if (currentminesForDisplay <= 9 && currentminesForDisplay >= -9)
            {
                mineDisplay_7.place = 3;
                thirdDigitOnDisplay = mineDisplay_7;
                thirdDigitOnDisplay.digitPlacement(board.yEnd);
            }
            if (currentminesForDisplay >= 10 || currentminesForDisplay <= -10)
            {
                mineDisplay_7.place = 2;
                secondDigitOnDisplay = mineDisplay_7;
                secondDigitOnDisplay.digitPlacement(board.yEnd);
            }
            if ((currentminesForDisplay >= 100 && currentminesForDisplay <= 999) || (currentminesForDisplay < -99 && currentminesForDisplay >= -999))
            {
                mineDisplay_7.place = 1;
                firstDigitOnDisplay = mineDisplay_7;
                firstDigitOnDisplay.digitPlacement(board.yEnd);
            }
        }
        if (firstNum == "8")
        {
            if (currentminesForDisplay <= 9 && currentminesForDisplay >= -9)
            {
                mineDisplay_8.place = 3;
                thirdDigitOnDisplay = mineDisplay_8;
                thirdDigitOnDisplay.digitPlacement(board.yEnd);
            }
            if (currentminesForDisplay >= 10 || currentminesForDisplay <= -10)
            {
                mineDisplay_8.place = 2;
                secondDigitOnDisplay = mineDisplay_8;
                secondDigitOnDisplay.digitPlacement(board.yEnd);
            }
            if ((currentminesForDisplay >= 100 && currentminesForDisplay <= 999) || (currentminesForDisplay < -99 && currentminesForDisplay >= -999))
            {
                mineDisplay_8.place = 1;
                firstDigitOnDisplay = mineDisplay_8;
                firstDigitOnDisplay.digitPlacement(board.yEnd);
            }
        }
        if (firstNum == "9")
        {
            if (currentminesForDisplay <= 9 && currentminesForDisplay >= -9)
            {
                mineDisplay_9.place = 3;
                thirdDigitOnDisplay = mineDisplay_9;
                thirdDigitOnDisplay.digitPlacement(board.yEnd);
            }
            if (currentminesForDisplay >= 10 || currentminesForDisplay <= -10)
            {
                mineDisplay_9.place = 2;
                secondDigitOnDisplay = mineDisplay_9;
                secondDigitOnDisplay.digitPlacement(board.yEnd);
            }
            if ((currentminesForDisplay >= 100 && currentminesForDisplay <= 999) || (currentminesForDisplay < -99 && currentminesForDisplay >= -999))
            {
                mineDisplay_9.place = 1;
                firstDigitOnDisplay = mineDisplay_9;
                firstDigitOnDisplay.digitPlacement(board.yEnd);
            }
        }




        if (currentminesForDisplay > 9 || currentminesForDisplay < -9)
        {

            if (secondNum == "0")
            {



                if ((currentminesForDisplay >= 100 && currentminesForDisplay <= 999) || (currentminesForDisplay <= -100 && currentminesForDisplay >= -999))
                {
                    mineDisplay_0.place = 2;
                    secondDigitOnDisplay = mineDisplay_0;
                    secondDigitOnDisplay.digitPlacement(board.yEnd);
                }
                if ((currentminesForDisplay >= 10 && currentminesForDisplay <= 99) || (currentminesForDisplay <= -10 && currentminesForDisplay >= -99))
                {
                    mineDisplay_0.place = 3;
                    thirdDigitOnDisplay = mineDisplay_0;
                    thirdDigitOnDisplay.digitPlacement(board.yEnd);
                }
            }

            if (secondNum == "1")
            {

                if ((currentminesForDisplay >= 100 && currentminesForDisplay <= 999) || (currentminesForDisplay <= -100 && currentminesForDisplay >= -999))
                {
                    mineDisplay_1.place = 2;
                    secondDigitOnDisplay = mineDisplay_1;
                    secondDigitOnDisplay.digitPlacement(board.yEnd);
                }
                if ((currentminesForDisplay >= 10 && currentminesForDisplay <= 99) || (currentminesForDisplay <= -10 && currentminesForDisplay >= -99))
                {
                    mineDisplay_1.place = 3;
                    thirdDigitOnDisplay = mineDisplay_1;
                    thirdDigitOnDisplay.digitPlacement(board.yEnd);
                }
            }
            if (secondNum == "2")
            {
                if ((currentminesForDisplay >= 100 && currentminesForDisplay <= 999) || (currentminesForDisplay <= -100 && currentminesForDisplay >= -999))
                {
                    mineDisplay_2.place = 2;
                    secondDigitOnDisplay = mineDisplay_2;
                    secondDigitOnDisplay.digitPlacement(board.yEnd);
                }
                if ((currentminesForDisplay >= 10 && currentminesForDisplay <= 99) || (currentminesForDisplay <= -10 && currentminesForDisplay >= -99))
                {
                    mineDisplay_2.place = 3;
                    thirdDigitOnDisplay = mineDisplay_2;
                    thirdDigitOnDisplay.digitPlacement(board.yEnd);
                }
            }
            if (secondNum == "3")
            {
                if ((currentminesForDisplay >= 100 && currentminesForDisplay <= 999) || (currentminesForDisplay <= -100 && currentminesForDisplay >= -999))
                {
                    mineDisplay_3.place = 2;
                    secondDigitOnDisplay = mineDisplay_3;
                    secondDigitOnDisplay.digitPlacement(board.yEnd);
                }
                if ((currentminesForDisplay >= 10 && currentminesForDisplay <= 99) || (currentminesForDisplay <= -10 && currentminesForDisplay >= -99))
                {
                    mineDisplay_3.place = 3;
                    thirdDigitOnDisplay = mineDisplay_3;
                    thirdDigitOnDisplay.digitPlacement(board.yEnd);
                }
            }
            if (secondNum == "4")
            {
                if ((currentminesForDisplay >= 100 && currentminesForDisplay <= 999) || (currentminesForDisplay <= -100 && currentminesForDisplay >= -999))
                {
                    mineDisplay_4.place = 2;
                    secondDigitOnDisplay = mineDisplay_4;
                    secondDigitOnDisplay.digitPlacement(board.yEnd);
                }
                if ((currentminesForDisplay >= 10 && currentminesForDisplay <= 99) || (currentminesForDisplay <= -10 && currentminesForDisplay >= -99))
                {
                    mineDisplay_4.place = 3;
                    thirdDigitOnDisplay = mineDisplay_4;
                    thirdDigitOnDisplay.digitPlacement(board.yEnd);
                }
            }
            if (secondNum == "5")
            {
                if ((currentminesForDisplay >= 100 && currentminesForDisplay <= 999) || (currentminesForDisplay <= -100 && currentminesForDisplay >= -999))
                {
                    mineDisplay_5.place = 2;
                    secondDigitOnDisplay = mineDisplay_5;
                    secondDigitOnDisplay.digitPlacement(board.yEnd);
                }
                if ((currentminesForDisplay >= 10 && currentminesForDisplay <= 99) || (currentminesForDisplay <= -10 && currentminesForDisplay >= -99))
                {
                    mineDisplay_5.place = 3;
                    thirdDigitOnDisplay = mineDisplay_5;
                    thirdDigitOnDisplay.digitPlacement(board.yEnd);
                }
            }
            if (secondNum == "6")
            {
                if ((currentminesForDisplay >= 100 && currentminesForDisplay <= 999) || (currentminesForDisplay <= -100 && currentminesForDisplay >= -999))
                {
                    mineDisplay_6.place = 2;
                    secondDigitOnDisplay = mineDisplay_6;
                    secondDigitOnDisplay.digitPlacement(board.yEnd);
                }
                if ((currentminesForDisplay >= 10 && currentminesForDisplay <= 99) || (currentminesForDisplay <= -10 && currentminesForDisplay >= -99))
                {
                    mineDisplay_6.place = 3;
                    thirdDigitOnDisplay = mineDisplay_6;
                    thirdDigitOnDisplay.digitPlacement(board.yEnd);
                }
            }
            if (secondNum == "7")
            {
                if ((currentminesForDisplay >= 100 && currentminesForDisplay <= 999) || (currentminesForDisplay <= -100 && currentminesForDisplay >= -999))
                {
                    mineDisplay_7.place = 2;
                    secondDigitOnDisplay = mineDisplay_7;
                    secondDigitOnDisplay.digitPlacement(board.yEnd);
                }
                if ((currentminesForDisplay >= 10 && currentminesForDisplay <= 99) || (currentminesForDisplay <= -10 && currentminesForDisplay >= -99))
                {
                    mineDisplay_7.place = 3;
                    thirdDigitOnDisplay = mineDisplay_7;
                    thirdDigitOnDisplay.digitPlacement(board.yEnd);
                }
            }
            if (secondNum == "8")
            {
                if ((currentminesForDisplay >= 100 && currentminesForDisplay <= 999) || (currentminesForDisplay <= -100 && currentminesForDisplay >= -999))
                {
                    mineDisplay_8.place = 2;
                    secondDigitOnDisplay = mineDisplay_8;
                    secondDigitOnDisplay.digitPlacement(board.yEnd);
                }
                if ((currentminesForDisplay >= 10 && currentminesForDisplay <= 99) || (currentminesForDisplay <= -10 && currentminesForDisplay >= -99))
                {
                    mineDisplay_8.place = 3;
                    thirdDigitOnDisplay = mineDisplay_8;
                    thirdDigitOnDisplay.digitPlacement(board.yEnd);
                }
            }
            if (secondNum == "9")
            {
                if ((currentminesForDisplay >= 100 && currentminesForDisplay <= 999) || (currentminesForDisplay <= -100 && currentminesForDisplay >= -999))
                {
                    mineDisplay_9.place = 2;
                    secondDigitOnDisplay = mineDisplay_9;
                    secondDigitOnDisplay.digitPlacement(board.yEnd);
                }
                if ((currentminesForDisplay >= 10 && currentminesForDisplay <= 99) || (currentminesForDisplay <= -10 && currentminesForDisplay >= -99))
                {
                    mineDisplay_9.place = 3;
                    thirdDigitOnDisplay = mineDisplay_9;
                    thirdDigitOnDisplay.digitPlacement(board.yEnd);
                }
            }

        }

        if ((currentminesForDisplay > 99 && currentminesForDisplay <= 999) || currentminesForDisplay < -99 && currentminesForDisplay >= -999)
        {

            if (thirdNum == "0")
            {

                if ((currentminesForDisplay >= 100 && currentminesForDisplay <= 999) || (currentminesForDisplay <= -100 && currentminesForDisplay >= -999))
                {


                    mineDisplay_0.place = 3;
                    thirdDigitOnDisplay = mineDisplay_0;
                    thirdDigitOnDisplay.digitPlacement(board.yEnd);
                }

            }
            if (thirdNum == "1")
            {
                if ((currentminesForDisplay >= 100 && currentminesForDisplay <= 999) || (currentminesForDisplay <= -100 && currentminesForDisplay >= -999))
                {
                    mineDisplay_1.place = 3;
                    thirdDigitOnDisplay = mineDisplay_1;
                    thirdDigitOnDisplay.digitPlacement(board.yEnd);
                }
            }
            if (thirdNum == "2")
            {
                if ((currentminesForDisplay >= 100 && currentminesForDisplay <= 999) || (currentminesForDisplay <= -100 && currentminesForDisplay >= -999))
                {
                    mineDisplay_2.place = 3;
                    thirdDigitOnDisplay = mineDisplay_2;
                    thirdDigitOnDisplay.digitPlacement(board.yEnd);
                }
            }
            if (thirdNum == "3")
            {
                if ((currentminesForDisplay >= 100 && currentminesForDisplay <= 999) || (currentminesForDisplay <= -100 && currentminesForDisplay >= -999))
                {
                    mineDisplay_3.place = 3;
                    thirdDigitOnDisplay = mineDisplay_3;
                    thirdDigitOnDisplay.digitPlacement(board.yEnd);
                }
            }
            if (thirdNum == "4")
            {
                if ((currentminesForDisplay >= 100 && currentminesForDisplay <= 999) || (currentminesForDisplay <= -100 && currentminesForDisplay >= -999))
                {
                    mineDisplay_4.place = 3;
                    thirdDigitOnDisplay = mineDisplay_4;
                    thirdDigitOnDisplay.digitPlacement(board.yEnd);
                }
            }
            if (thirdNum == "5")
            {
                if ((currentminesForDisplay >= 100 && currentminesForDisplay <= 999) || (currentminesForDisplay <= -100 && currentminesForDisplay >= -999))
                {
                    mineDisplay_5.place = 3;
                    thirdDigitOnDisplay = mineDisplay_5;
                    thirdDigitOnDisplay.digitPlacement(board.yEnd);
                }
            }
            if (thirdNum == "6")
            {
                if ((currentminesForDisplay >= 100 && currentminesForDisplay <= 999) || (currentminesForDisplay <= -100 && currentminesForDisplay >= -999))
                {
                    mineDisplay_6.place = 3;
                    thirdDigitOnDisplay = mineDisplay_6;
                    thirdDigitOnDisplay.digitPlacement(board.yEnd);
                }
            }
            if (thirdNum == "7")
            {
                if ((currentminesForDisplay >= 100 && currentminesForDisplay <= 999) || (currentminesForDisplay <= -100 && currentminesForDisplay >= -999))
                {
                    mineDisplay_7.place = 3;
                    thirdDigitOnDisplay = mineDisplay_7;
                    thirdDigitOnDisplay.digitPlacement(board.yEnd);
                }
            }
            if (thirdNum == "8")
            {
                if ((currentminesForDisplay >= 100 && currentminesForDisplay <= 999) || (currentminesForDisplay <= -100 && currentminesForDisplay >= -999))
                {
                    mineDisplay_8.place = 3;
                    thirdDigitOnDisplay = mineDisplay_8;
                    thirdDigitOnDisplay.digitPlacement(board.yEnd);
                }
            }
            if (thirdNum == "9")
            {
                if ((currentminesForDisplay >= 100 && currentminesForDisplay <= 999) || (currentminesForDisplay <= -100 && currentminesForDisplay >= -999))
                {
                    mineDisplay_9.place = 3;
                    thirdDigitOnDisplay = mineDisplay_9;
                    thirdDigitOnDisplay.digitPlacement(board.yEnd);
                }
            }

        }

        if ((currentminesForDisplay >= 1 && currentminesForDisplay <= 9) || currentminesForDisplay <= -1 && currentminesForDisplay >= -9)
        {
            firstDigitOnDisplay = mineDisplay_0;
            firstDigitOnDisplay.place = 1;
            firstDigitOnDisplay.digitPlacement(board.yEnd);

            secondDigitOnDisplay = mineDisplay_0;
            secondDigitOnDisplay.place = 2;
            secondDigitOnDisplay.digitPlacement(board.yEnd);
        }

        if ((currentminesForDisplay >= 10 && currentminesForDisplay <= 99) || currentminesForDisplay <= -10 && currentminesForDisplay >= -99)
        {
            firstDigitOnDisplay = mineDisplay_0;
            firstDigitOnDisplay.place = 1;
            firstDigitOnDisplay.digitPlacement(board.yEnd);
        }



        

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ negative sign show or not~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        if (currentminesForDisplay >= 0)
        {
            rectangle.setFillColor(color);
        }
        if (currentminesForDisplay < 0)
        {
            // mineDisplay_negative.spriteNum.setColor(color2);
            // 

            rectangle.setFillColor(color2);



        }
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ negative sign show or not~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~





        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ setting howManyAdjacentMines and howManyAdjacentTilesWithAdjacentMines to zero ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        for (int i = 0; i <= board.bRows - 1; i++)
        {

            for (int j = 0; j <= board.bColums - 1; j++)
            {

                if (boardVect[i][j].mineOrNah == '1')
                {

                    if (j != 0)
                    {
                        boardVect[i][j - 1].howManyAdjacentMines = 0;
                    }


                    if (i != 0 && j != 0)
                    {
                        boardVect[i - 1][j - 1].howManyAdjacentMines = 0;
                    }


                    if (i != 0)
                    {
                        boardVect[i - 1][j].howManyAdjacentMines = 0;
                    }


                    if (i != 0 && j != board.bColums - 1)
                    {
                        boardVect[i - 1][j + 1].howManyAdjacentMines = 0;
                    }


                    if (j != board.bColums - 1)
                    {
                        boardVect[i][j + 1].howManyAdjacentMines = 0;
                    }


                    if (i != board.bRows - 1)
                    {
                        boardVect[i + 1][j].howManyAdjacentMines = 0;
                    }

                    if (i != board.bRows - 1 && j != 0)
                    {
                        boardVect[i + 1][j - 1].howManyAdjacentMines = 0;
                    }

                    if (i != board.bRows - 1 && j != board.bColums - 1)
                    {
                        boardVect[i + 1][j + 1].howManyAdjacentMines = 0;
                    }

                }

                if (boardVect[i][j].mineOrNah == '0')
                {

                    if (j != 0)
                    {
                        boardVect[i][j - 1].howManyAdjacentTilesWithAdjacentMines = 0;
                    }


                    if (i != 0 && j != 0)
                    {
                        boardVect[i - 1][j - 1].howManyAdjacentTilesWithAdjacentMines = 0;
                    }


                    if (i != 0)
                    {
                        boardVect[i - 1][j].howManyAdjacentTilesWithAdjacentMines = 0;
                    }


                    if (i != 0 && j != board.bColums - 1)
                    {
                        boardVect[i - 1][j + 1].howManyAdjacentTilesWithAdjacentMines = 0;
                    }


                    if (j != board.bColums - 1)
                    {
                        boardVect[i][j + 1].howManyAdjacentTilesWithAdjacentMines = 0;
                    }


                    if (i != board.bRows - 1)
                    {
                        boardVect[i + 1][j].howManyAdjacentTilesWithAdjacentMines = 0;
                    }

                    if (i != board.bRows - 1 && j != 0)
                    {
                        boardVect[i + 1][j - 1].howManyAdjacentTilesWithAdjacentMines = 0;
                    }

                    if (i != board.bRows - 1 && j != board.bColums - 1)
                    {
                        boardVect[i + 1][j + 1].howManyAdjacentTilesWithAdjacentMines = 0;
                    }

                }



            }
        }
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ setting howManyAdjacentMines and howManyAdjacentTilesWithAdjacentMines to zero ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~





        for (int i = 0; i <= board.bRows - 1; i++)
        {

            for (int j = 0; j <= board.bColums - 1; j++)
            {

                if (boardVect[i][j].mineOrNah == '1')
                {

                    if (j != 0)
                    {
                        if (boardVect[i][j - 1].mineOrNah == '0')
                        {
                            boardVect[i][j - 1].howManyAdjacentMines++;
                        }
                    }


                    if (i != 0 && j != 0)
                    {
                        if (boardVect[i - 1][j - 1].mineOrNah == '0')
                        {
                            boardVect[i - 1][j - 1].howManyAdjacentMines++;
                        }
                    }


                    if (i != 0)
                    {
                        if (boardVect[i - 1][j].mineOrNah == '0')
                        {
                            boardVect[i - 1][j].howManyAdjacentMines++;
                        }
                    }

                    if (i != 0 && j != board.bColums - 1)
                    {
                        if (boardVect[i - 1][j + 1].mineOrNah == '0')
                        {
                            boardVect[i - 1][j + 1].howManyAdjacentMines++;
                        }
                    }


                    if (j != board.bColums - 1)
                    {
                        if (boardVect[i][j + 1].mineOrNah == '0')
                        {
                            boardVect[i][j + 1].howManyAdjacentMines++;
                        }
                    }


                    if (i != board.bRows - 1)
                    {
                        if (boardVect[i + 1][j].mineOrNah == '0')
                        {
                            boardVect[i + 1][j].howManyAdjacentMines++;
                        }
                    }

                    if (i != board.bRows - 1 && j != 0)
                    {
                        if (boardVect[i + 1][j - 1].mineOrNah == '0')
                        {
                            boardVect[i + 1][j - 1].howManyAdjacentMines++;
                        }
                    }


                    if (i != board.bRows - 1 && j != board.bColums - 1)
                    {
                        if (boardVect[i + 1][j + 1].mineOrNah == '0')
                        {
                            boardVect[i + 1][j + 1].howManyAdjacentMines++;
                        }
                    }


                }






            }
        }


        for (int i = 0; i <= board.bRows - 1; i++)
        {

            for (int j = 0; j <= board.bColums - 1; j++)
            {
                boardVect[i][j].neibors.clear();
            }

        }





        for (int i = 0; i <= board.bRows - 1; i++)
        {


            for (int j = 0; j <= board.bColums - 1; j++)
            {

                if (boardVect[i][j].mineOrNah == '0' && boardVect[i][j].howManyAdjacentMines == 0)
                {
                    if (j != 0)
                    {

                        if (boardVect[i][j - 1].mineOrNah == '0' && boardVect[i][j - 1].howManyAdjacentMines > 0)
                        {
                            boardVect[i][j].howManyAdjacentTilesWithAdjacentMines++;
                        }
                    }

                    if (i != 0 && j != 0)
                    {


                        if (boardVect[i - 1][j - 1].mineOrNah == '0' && (boardVect[i - 1][j - 1].howManyAdjacentMines > 0))
                        {
                            boardVect[i][j].howManyAdjacentTilesWithAdjacentMines++;
                        }
                    }


                    if (i != 0)
                    {

                        if (boardVect[i - 1][j].mineOrNah == '0' && boardVect[i - 1][j].howManyAdjacentMines > 0)
                        {
                            boardVect[i][j].howManyAdjacentTilesWithAdjacentMines++;
                        }
                    }


                    if (i != 0 && j != board.bColums - 1)
                    {

                        if (boardVect[i - 1][j + 1].mineOrNah == '0' && boardVect[i - 1][j + 1].howManyAdjacentMines > 0)
                        {
                            boardVect[i][j].howManyAdjacentTilesWithAdjacentMines++;
                        }
                    }




                    if (j != board.bColums - 1)
                    {



                        if (boardVect[i][j + 1].mineOrNah == '0' && boardVect[i][j + 1].howManyAdjacentMines > 0)
                        {
                            boardVect[i][j].howManyAdjacentTilesWithAdjacentMines++;

                        }

                    }




                    if (i != board.bRows - 1)
                    {

                        if (boardVect[i + 1][j].mineOrNah == '0' && boardVect[i + 1][j].howManyAdjacentMines > 0)
                        {
                            boardVect[i][j].howManyAdjacentTilesWithAdjacentMines++;
                        }
                    }



                    if (i != board.bRows - 1 && j != 0)
                    {

                        if (boardVect[i + 1][j - 1].mineOrNah == '0' && boardVect[i + 1][j - 1].howManyAdjacentMines > 0)
                        {
                            boardVect[i][j].howManyAdjacentTilesWithAdjacentMines++;
                        }
                    }


                    if (i != board.bRows - 1 && j != board.bColums - 1)
                    {


                        if (boardVect[i + 1][j + 1].mineOrNah == '0' && boardVect[i + 1][j + 1].howManyAdjacentMines > 0)
                        {
                            boardVect[i][j].howManyAdjacentTilesWithAdjacentMines++;
                        }
                    }



                }

            }

        }





        for (int i = 0; i <= board.bRows - 1; i++)
        {
            for (int j = 0; j <= board.bColums - 1; j++)
            {
                if (boardVect[i][j].mineOrNah == '0' && boardVect[i][j].howManyAdjacentMines == 0)
                {

                    if (j != 0)
                    {
                        if (boardVect[i][j - 1].mineOrNah == '0')
                        {
                            boardVect[i][j].neibors.push_back(&boardVect[i][j - 1]);
                        }
                    }

                    if (i != 0 && j != 0)
                    {
                        if (boardVect[i - 1][j - 1].mineOrNah == '0')
                        {
                            boardVect[i][j].neibors.push_back(&boardVect[i - 1][j - 1]);
                        }
                    }


                    if (i != 0)
                    {
                        if (boardVect[i - 1][j].mineOrNah == '0')
                        {
                            boardVect[i][j].neibors.push_back(&boardVect[i - 1][j]);
                        }
                    }

                    if (i != 0 && j != board.bColums - 1)
                    {
                        if (boardVect[i - 1][j + 1].mineOrNah == '0')
                        {
                            boardVect[i][j].neibors.push_back(&boardVect[i - 1][j + 1]);
                        }
                    }

                    if (j != board.bColums - 1)
                    {

                        if (boardVect[i][j + 1].mineOrNah == '0')
                        {
                            boardVect[i][j].neibors.push_back(&boardVect[i][j + 1]);
                        }
                    }

                    if (i != board.bRows - 1)
                    {
                        if (boardVect[i + 1][j].mineOrNah == '0')
                        {
                            boardVect[i][j].neibors.push_back(&boardVect[i + 1][j]);
                        }
                    }


                    if (i != board.bRows - 1 && j != 0)
                    {
                        if (boardVect[i + 1][j - 1].mineOrNah == '0')
                        {
                            boardVect[i][j].neibors.push_back(&boardVect[i + 1][j - 1]);
                        }
                    }


                    if (i != board.bRows - 1 && j != board.bColums - 1)
                    {
                        if (boardVect[i + 1][j + 1].mineOrNah == '0')
                        {
                            boardVect[i][j].neibors.push_back(&boardVect[i + 1][j + 1]);
                        }
                    }


                }


            }

        }




        for (int i = 0; i <= board.bRows - 1; i++)
        {

            for (int j = 0; j <= board.bColums - 1; j++)
            {
                if (boardVect[i][j].revealedOrNah == '1' && boardVect[i][j].howManyAdjacentMines == 0 && boardVect[i][j].mineOrNah == '0')
                {
                    boardVect[i][j].tile.setTexture(revealedtile);
                }

                if (boardVect[i][j].revealedOrNah == '1' && boardVect[i][j].howManyAdjacentMines > 0 && boardVect[i][j].mineOrNah == '0')
                {
                    boardVect[i][j].base.setTexture(revealedtile);
                    boardVect[i][j].setAdjacentMineTexture(num_1, num_2, num_3, num_4, num_5, num_6, num_7, num_8);
                }

            }

        }




        if (gameOver == 1 && defeat == 1)
        {
            resetFace.button.setTexture(face_lose);


            for (int i = 0; i <= board.bRows - 1; i++)
            {

                for (int j = 0; j <= board.bColums - 1; j++)
                {
                    if (boardVect[i][j].mineOrNah == '1' || boardVect[i][j].mineOrNah == '5')
                    {
                        boardVect[i][j].base.setTexture(revealedtile);
                        boardVect[i][j].tile.setTexture(mine);
                    }

                }
            }
        }

        if (gameOver == 1 && defeat == 0)
        {
            firstDigitOnDisplay.spriteNum.setTexture(textureMineDisplay_0);
            secondDigitOnDisplay.spriteNum.setTexture(textureMineDisplay_0);
            thirdDigitOnDisplay.spriteNum.setTexture(textureMineDisplay_0);
        }


        window.clear(color);

        window.draw(mineDisplay_negative.spriteNum);
        window.draw(rectangle);
        window.draw(firstDigitOnDisplay.spriteNum);
        window.draw(secondDigitOnDisplay.spriteNum);
        window.draw(thirdDigitOnDisplay.spriteNum);
        window.draw(resetFace.button);






        if (yOrNoDebug == 1) { checkdebugnum2 = 1; }

        
        board.DrawBoard(boardVect, window, check);

        window.draw(testboard1Button.button);
        window.draw(testboard2Button.button);
        window.draw(testboard3Button.button);
        window.draw(debugButton.button);

       
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }


            if (event.type == sf::Event::Resized)
            {

                
            }


            if (event.type == sf::Event::MouseButtonPressed)
            {

                if (event.mouseButton.button == sf::Mouse::Right)
                {



                    sf::Vector2f rightMouseClick(event.mouseButton.x, event.mouseButton.y);

                    if (event.mouseButton.x >= 0 && event.mouseButton.x <= board.xEnd && event.mouseButton.y >= 0 && event.mouseButton.y <= board.yEnd && gameOver != 1 && defeat != 1)
                    {
                        for (int i = 0; i <= board.bRows - 1; i++)
                        {
                            for (int j = 0; j <= board.bColums - 1; j++)
                            {
                                if (boardVect[i][j].base.getGlobalBounds().contains(rightMouseClick) && boardVect[i][j].revealedOrNah == '0')
                                {






                                    if (boardVect[i][j].mineOrNah == '5' || boardVect[i][j].mineOrNah == '4')
                                    {
                                        boardVect[i][j].base.setTexture(revealedtile);
                                        boardVect[i][j].tile.setTexture(hiddentile);
                                        if (boardVect[i][j].mineOrNah == '5')
                                        {
                                            boardVect[i][j].mineOrNah = '1';

                                            if (boardVect[i][j].revealedOrNah == '1' || yOrNoDebug == 1)
                                            {
                                                boardVect[i][j].tile.setTexture(mine);
                                                if (yOrNoDebug == 1 && boardVect[i][j].revealedOrNah == '0')
                                                {
                                                    boardVect[i][j].base.setTexture(hiddentile);


                                                }

                                            }
                                        }

                                        if (boardVect[i][j].mineOrNah == '4')
                                        {


                                            boardVect[i][j].mineOrNah = '0';
                                            if (boardVect[i][j].revealedOrNah == '1')
                                            {
                                                boardVect[i][j].tile.setTexture(revealedtile);

                                            }

                                        }

                                        numofFlags--;

                                    }
                                    else
                                    {


                                        boardVect[i][j].base.setTexture(hiddentile);
                                        boardVect[i][j].tile.setTexture(flag);
                                        if (boardVect[i][j].mineOrNah == '1')
                                        {
                                            boardVect[i][j].mineOrNah = '5';


                                        }

                                        if (boardVect[i][j].mineOrNah == '0')
                                        {
                                            boardVect[i][j].mineOrNah = '4';

                                            if (boardVect[i][j].revealedOrNah == '1') { boardVect[i][j].base.setTexture(revealedtile); }


                                        }

                                        numofFlags++;

                                    }
                                }
                            }
                        }
                    }

                }


                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    int checkforflagYN = 0;



                    sf::Vector2f leftMouseClick(event.mouseButton.x, event.mouseButton.y);



                    if (event.mouseButton.x >= 0 && event.mouseButton.x <= board.xEnd && event.mouseButton.y >= 0 && event.mouseButton.y <= board.yEnd && gameOver != 1 && defeat != 1)
                    {




                        for (int i = 0; i <= board.bRows - 1; i++)
                        {
                            for (int j = 0; j <= board.bColums - 1; j++)
                            {
                                if (boardVect[i][j].base.getGlobalBounds().contains(leftMouseClick) && boardVect[i][j].mineOrNah != '4' && boardVect[i][j].mineOrNah != '5')
                                {





                                    if (boardVect[i][j].mineOrNah == '1')
                                    {
                                        boardVect[i][j].base.setTexture(revealedtile);
                                        boardVect[i][j].tile.setTexture(mine);
                                        defeat = 1;
                                        gameOver = 1;

                                    }

                                    if (boardVect[i][j].mineOrNah == '0')
                                    {

                                        




                                        revursiveRevealFunction(0, i, j, emptytiles, boardVect, 0, 0, 0, 0, 0, 0);

                                    }
                                }
                            }
                        }


                    }

                    if (event.mouseButton.x >= board.xEnd / 2 + 144 && event.mouseButton.x <= board.xEnd && event.mouseButton.y >= board.yEnd && event.mouseButton.y <= board.yEnd + 64)
                    {


                        if (testboard1Button.button.getGlobalBounds().contains(leftMouseClick))
                        {
                            for (int i = 0; i <= board.bRows - 1; i++)
                            {
                                for (int j = 0; j <= board.bColums - 1; j++)
                                {
                                    boardVect[i][j].revealedOrNah = '0';

                                    boardVect[i][j].base.setTexture(revealedtile);
                                    boardVect[i][j].tile.setTexture(hiddentile);
                                    boardVect[i][j].mineOrNah = test_board1_Vect[i][j];
                                    if (boardVect[i][j].mineOrNah != '0' && boardVect[i][j].mineOrNah != '1')
                                    {
                                        boardVect[i][j].mineOrNah = '0';
                                    }

                                    //

                                    if (yOrNoDebug == 1 && boardVect[i][j].mineOrNah == '1')
                                    {

                                        boardVect[i][j].base.setTexture(hiddentile);
                                        boardVect[i][j].tile.setTexture(mine);
                                    }
                                    else { boardVect[i][j].revealedOrNah = '0'; }
                                    
                                }





                            }

                            numofFlags = 0;
                            currentminesForDisplay = 0;
                            numofFlags = 0;

                            for (int i = 0; i <= board.bRows - 1; i++)
                            {

                                for (int j = 0; j <= board.bColums - 1; j++)
                                {
                                    boardVect[i][j].neiborZfound = '0';
                                }

                            }

                            gameOver = 0;
                            defeat = 0;

                        }


                        if (testboard2Button.button.getGlobalBounds().contains(leftMouseClick))
                        {
                            for (int i = 0; i <= board.bRows - 1; i++)
                            {
                                for (int j = 0; j <= board.bColums - 1; j++)
                                {
                                    boardVect[i][j].revealedOrNah = '0';

                                    boardVect[i][j].base.setTexture(revealedtile);
                                    boardVect[i][j].tile.setTexture(hiddentile);
                                    boardVect[i][j].mineOrNah = test_board2_Vect[i][j];
                                    if (boardVect[i][j].mineOrNah != '0' && boardVect[i][j].mineOrNah != '1')
                                    {
                                        boardVect[i][j].mineOrNah = '0';
                                    }


                                    if (boardVect[i][j].mineOrNah == '1')
                                    {
                                        checkminebug++;
                                    }

                                    if (yOrNoDebug == 1 && boardVect[i][j].mineOrNah == '1')
                                    {

                                        boardVect[i][j].base.setTexture(hiddentile);
                                        boardVect[i][j].tile.setTexture(mine);
                                    }
                                    else { boardVect[i][j].revealedOrNah = '0'; }
                                   

                                }
                            }

                            for (int i = 0; i <= board.bRows - 1; i++)
                            {

                                for (int j = 0; j <= board.bColums - 1; j++)
                                {
                                    boardVect[i][j].neiborZfound = '0';
                                }

                            }

                            numofFlags = 0;
                            currentminesForDisplay = 0;
                            numofFlags = 0;

                            gameOver = 0;
                            defeat = 0;
                        }


                        if (testboard3Button.button.getGlobalBounds().contains(leftMouseClick)) {
                            for (int i = 0; i <= board.bRows - 1; i++)
                            {
                                for (int j = 0; j <= board.bColums - 1; j++)
                                {
                                    boardVect[i][j].revealedOrNah = '0';

                                    boardVect[i][j].base.setTexture(revealedtile);
                                    boardVect[i][j].tile.setTexture(hiddentile);
                                    boardVect[i][j].mineOrNah = test_board3_Vect[i][j];
                                    //  


                                    if (boardVect[i][j].mineOrNah != '0' && boardVect[i][j].mineOrNah != '1')
                                    {
                                        boardVect[i][j].mineOrNah = '0';
                                    }

                                    if (yOrNoDebug == 1 && boardVect[i][j].mineOrNah == '1')
                                    {

                                        boardVect[i][j].base.setTexture(hiddentile);
                                        boardVect[i][j].tile.setTexture(mine);
                                    }
                                    else { boardVect[i][j].revealedOrNah = '0'; }
                                    

                                }
                            }

                            numofFlags = 0;
                            currentminesForDisplay = 0;
                            numofFlags = 0;
                            for (int i = 0; i <= board.bRows - 1; i++)
                            {

                                for (int j = 0; j <= board.bColums - 1; j++)
                                {
                                    boardVect[i][j].neiborZfound = '0';
                                }

                            }

                            gameOver = 0;
                            defeat = 0;

                        }

                        for (int i = 0; i <= board.bRows - 1; i++)
                        {
                            for (int j = 0; j <= board.bColums - 1; j++)
                            {

                                boardVect[i][j].howManyAdjacentMines = 0;
                                boardVect[i][j].howManyAdjacentTilesWithAdjacentMines = 0;
                            }

                        }

                        if (debugButton.button.getGlobalBounds().contains(leftMouseClick) && yOrNoDebug == 0 && gameOver != 1) {


                            if (yOrNoDebug == 0)
                            {
                                for (int i = 0; i <= board.bRows - 1; i++)
                                {

                                    for (int j = 0; j <= board.bColums - 1; j++)
                                    {
                                        if (boardVect[i][j].mineOrNah == '1' && yOrNoDebug == 0)
                                        {
                                            if (boardVect[i][j].revealedOrNah == '0')
                                            {
                                                boardVect[i][j].base.setTexture(hiddentile);
                                            }
                                            else
                                            {
                                                boardVect[i][j].base.setTexture(revealedtile);
                                            }
                                            boardVect[i][j].tile.setTexture(mine);

                                        }
                                    }
                                }
                                yOrNoDebug = 1;
                            }



                        }


                        if (debugButton.button.getGlobalBounds().contains(leftMouseClick) && yOrNoDebug == 1 && checkdebugnum2 == 1 && gameOver != 1)
                        {
                            for (int i = 0; i <= board.bRows - 1; i++)
                            {

                                for (int j = 0; j <= board.bColums - 1; j++)
                                {
                                    if (boardVect[i][j].mineOrNah == '1')
                                    {
                                        boardVect[i][j].base.setTexture(revealedtile);
                                        if (boardVect[i][j].revealedOrNah == '0')
                                        {
                                            boardVect[i][j].tile.setTexture(hiddentile);
                                        }
                                        else { boardVect[i][j].tile.setTexture(mine); }

                                    }
                                }
                            }
                            yOrNoDebug = 0;
                            checkdebugnum2 = 0;
                        }

                        // currentminesForDisplay = 0;
                        for (int i = 0; i <= board.bRows - 1; i++)
                        {

                            for (int j = 0; j <= board.bColums - 1; j++)
                            {
                                if (boardVect[i][j].mineOrNah == '1' && boardVect[i][j].revealedOrNah != '1')
                                {
                                    //currentminesForDisplay++;
                                }
                            }
                        }
                    }



                    if (resetFace.button.getGlobalBounds().contains(leftMouseClick))
                    {
                        random_board_Vect = random_board.loadRandomBoard(board.bRows, board.bColums, mines);
                        for (int i = 0; i <= board.bRows - 1; i++)
                        {
                            for (int j = 0; j <= board.bColums - 1; j++)
                            {
                                boardVect[i][j].revealedOrNah = '0';

                                boardVect[i][j].base.setTexture(revealedtile);
                                boardVect[i][j].tile.setTexture(hiddentile);
                                boardVect[i][j].mineOrNah = random_board_Vect[i][j];
                                //  




//
                                if (yOrNoDebug == 1 && boardVect[i][j].mineOrNah == '1')
                                {

                                    boardVect[i][j].base.setTexture(hiddentile);
                                    boardVect[i][j].tile.setTexture(mine);
                                }
                                else { boardVect[i][j].revealedOrNah = '0'; }
                               
                            }
                        }

                        numofFlags = 0;
                        currentminesForDisplay = 0;
                        numofFlags = 0;
                        for (int i = 0; i <= board.bRows - 1; i++)
                        {

                            for (int j = 0; j <= board.bColums - 1; j++)
                            {
                                boardVect[i][j].neiborZfound = '0';
                            }

                        }

                        gameOver = 0;
                        defeat = 0;


                        for (int i = 0; i <= board.bRows - 1; i++)
                        {
                            for (int j = 0; j <= board.bColums - 1; j++)
                            {

                                boardVect[i][j].howManyAdjacentMines = 0;
                                boardVect[i][j].howManyAdjacentTilesWithAdjacentMines = 0;
                            }

                        }
                    }




                }

            }



        }




        window.display();
    }





    return 0;
}


