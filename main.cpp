#include <iostream>
#include <string.h>
//#define _CRT_SECURE_NO_DEPRECATE
#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
using namespace std;
#define COLUMN 10
#define ROW 21
#define CAR 5   //1 count
#define BAT 4   //2 count
#define CRU 3   //3 count 
#define DES 2   //4 count
#define CAR_COUNT 1
#define BAT_COUNT 2
#define CRU_COUNT 3
#define DES_COUNT 4
char const PRINT[] = "PRINT";
char const SET_FLEETc[] = "SET_FLEET";
char const NEXT_PLAYER[] = "NEXT_PLAYER";
char const BOARD_SIZE[] = "BOARD_SIZE";
char const INIT_POSITION[] = "INIT_POSITION";
char const REEF[] = "REEF";
char const SHIPc[] = "SHIP";
char const stateC[] = "[state]";
char const playerAc[] = "[playerA]";
char const playerBc[] = "[playerB]";
char const SHOOTc[] = "SHOOT";
char const PLACE_SHIPc[] = "PLACE_SHIP";
char const MOVEc[] = "MOVE";
char const SAVE[] = "SAVE";

struct Board {
    Board() {
        create_board(ROW, COLUMN);
    }
    void create_board(int r, int c);

    unsigned int row;
    unsigned int column;
    int timeOfplacing = 0;      //time of placing ships but in command PLACE_SHIP
    int timeOfplacingSHIP = 0;  //time of placing ships but in command SHIP
    int playerA_placing = 0;
    int playerB_placing = 0;
    int numberOfshoots = 0;
    bool SET_FLEET_usage = false;               //this to insucate if the set fleet was used or not, by default it is false and if it is false that means that it wasn't used
    char** board;
    bool SHOOT_usage = false;                   //this to shows if the shoot was used or not, by default it is false and if it is false that means that it wasn't used
    bool INIT_POSITION_usage = false;
    bool REEF_usage = false;
    bool NEXT_PLAYER_usage = false;
    bool SHIP_usage = false;
    bool move_usage = false;
    int REEF_count = 0;
};
Board board1{};

struct Player {
    Player(unsigned int numOfplace, int car_l, int bat_l, int cru_l, int des_l, int c_car, int c_bat, int c_cru, int c_des, int total_ships, unsigned int Y1, unsigned int X1, unsigned int Y2, unsigned int X2)
        : numberOfPlacing(numOfplace), CAR_L(car_l), BAT_L(bat_l), CRU_L(cru_l), DES_L(des_l), currentCAR(c_car), currentBAT(c_bat), currentCRU(c_cru), currentDES(c_des), totalShips(total_ships), y1(Y1), x1(X1), y2(Y2), x2(X2) {}

    unsigned int numberOfPlacing;
    int CAR_L;		//limits
    int BAT_L;
    int CRU_L;
    int DES_L;
    int currentCAR;
    int currentBAT;
    int currentCRU;
    int currentDES;
    int totalShips;
    unsigned int y1;
    unsigned int x1;
    unsigned int y2;
    unsigned int x2;
};
Player playerA{ 0,1,2,3,4,-1,0,0,0,0,0,0,9,9 };
Player playerB{ 0,1,2,3,4,0,0,0,0,0,11,0,20,9 };

struct Ships {
    unsigned int x, y, number;										//x,y are the spot , number is the number of the ship or what order it is
    char direction;
    int shipType;
    int moves;
};

Ships playerA_ships[20];
Ships playerB_ships[20];

void Board::create_board(int r, int c) {
    row = r;
    column = c;

    board = new char* [row];
    for (int i = 0; i < row; i++)
        board[i] = new char[column];
}

int dictionary(char const command[]) {
    if (strcmp(command, PRINT) == 0)
        return 1;
    else if (strcmp(command, SET_FLEETc) == 0)
        return 2;
    else if (strcmp(command, NEXT_PLAYER) == 0)
        return 3;
    else if (strcmp(command, BOARD_SIZE) == 0)
        return 4;
    else if (strcmp(command, INIT_POSITION) == 0)
        return 5;
    else if (strcmp(command, REEF) == 0)
        return 6;
    else if (strcmp(command, stateC) == 0)
        return 7;
    else if (strcmp(command, SHIPc) == 0)
        return 8;
    else if (strcmp(command, playerAc) == 0)
        return 9;
    else if (strcmp(command, playerBc) == 0)
        return 10;
    else if (strcmp(command, SHOOTc) == 0)
        return 11;
    else if (strcmp(command, PLACE_SHIPc) == 0)
        return 12;
    else if (strcmp(command, MOVEc) == 0)
        return 13;
    else if (strcmp(command, SAVE) == 0)
        return 15;
    else
        return 14;
}

char* getTheTypeOfShip(int i) {
    if (i == 5)
    {
        char* CAR_d = (char*)malloc(100);
        strcpy(CAR_d, "CAR");
        return CAR_d;
    }
    else if (i == 4)
    {
        char* BAT_d = (char*)malloc(100);
        strcpy(BAT_d, "BAT");
        return BAT_d;
    }
    else if (i == 3)
    {
        char* CRU_d = (char*)malloc(100);
        strcpy(CRU_d, "CRU");
        return CRU_d;
    }
    else {
        char* DES_d = (char*)malloc(100);
        strcpy(DES_d, "DES");
        return DES_d;
    }
}

void clear() {

    for (int i = 0; i < board1.row; i++)
    {
        for (int j = 0; j < board1.column; j++)
        {
            board1.board[i][j] = '0';
        }
    }
}

int undestroyedA() {
    int w = 0;

    if (board1.INIT_POSITION_usage == true)
    {
        for (unsigned int i = playerA.y1; i < playerA.y2; i++)    //column is the player  A bounderse
        {
            for (unsigned int j = playerA.x1; j <= playerA.x2; j++)
            {
                if (board1.board[i][j] == '+')
                    w++;
            }
        }
        return w;
    }
    else if (board1.move_usage == true)
    {
        for (int i = 0; i < board1.playerA_placing; i++)
        {
            w = w + playerA_ships[i].shipType;
        }
        return w;
    }
    else
    {
        for (int i = 0; i < board1.column; i++)    //column is the player  A bounderse
        {
            for (int j = 0; j < board1.column; j++)
            {
                if (board1.board[i][j] == '+')
                    w++;
            }
        }
        return w;
    }
}

int undestroyedB() {
    int w = 0;

    if (board1.INIT_POSITION_usage == true)
    {
        for (unsigned int i = playerB.y1; i < playerB.y2; i++)    //column is the player  A bounderse
        {
            for (unsigned int j = playerB.x1; j <= playerB.x2; j++)
            {
                if (board1.board[i][j] == '+')
                    w++;
            }
        }
        return w;
    }
    else if (board1.move_usage == true)
    {
        for (int i = 0; i < board1.playerB_placing; i++)
        {
            w = w + playerB_ships[i].shipType;
        }
        return w;
    }
    else
    {
        for (int i = board1.column; i < board1.row; i++)    //column is the player  A bounderse
        {
            for (int j = 0; j < board1.column; j++)
            {
                if (board1.board[i][j] == '+')
                    w++;
            }
        }
        return w;
    }
}

void show() {

    for (int i = 0; i < board1.row; i++)
    {
        for (int j = 0; j < board1.column; j++)
        {
            cout << board1.board[i][j];
        }
        cout << endl;
    }
    cout << "PARTS REMAINING:: A : " << /*board1.*/undestroyedA() << " B : " << /*board1.*/undestroyedB() << endl;
}

void destroy_board()
{
    for (int i = 0; i < board1.row; ++i)
        delete[] board1.board[i];
    delete[] board1.board;
}

void resize_board() {
    delete board1.board;                //delete the old table
    int row, column;             //assign new row and column
    cin >> row >> column;
    board1.create_board(row, column);   //create new board
    /* board1.*/clear();
}

bool middle(char player, unsigned int y, unsigned int x, char direction, unsigned int number, char shipType[], char segment[], int SHIP_placeShip,bool checkingMove) {

    if (board1.board[y][x] == 'x' || board1.board[y][x] == '+')
    {
        if (checkingMove == true) //MOVE 0 CAR L
        {
            cout << "INVALID OPERATION \"MOVE " << number << " " << shipType << " " << direction << "\": PLACING SHIP TOO CLOSE TO OTHER SHIP" << endl;
            exit(0);
        }
        else if (SHIP_placeShip == 8)
        {
            cout << "INVALID OPERATION \"SHIP  " << player << " " << y << " " << x << " " << direction << " " << number << " " << shipType << " " << segment << "\": PLACING SHIP TOO CLOSE TO OTHER SHIP" << endl;
            exit(0);
        }
        else if (SHIP_placeShip == 14)    //place_ship 14 it is the same valuable that was passed as a parmenter in PLACE_SHIP
        {
            cout << "INVALID OPERATION \"PLACE_SHIP " << y << " " << x << " " << direction << " " << number << " " << shipType << "\": PLACING SHIP TOO CLOSE TO OTHER SHIP" << endl;
            exit(0);
        }
    }
    else
        return true;
    return true;
}

bool right(char player, unsigned int y, unsigned int x, char direction, unsigned int number, char shipType[], char segment[], int SHIP_placeShip,bool checkingMove) {

    if (board1.board[y][x + 1] == '+' || board1.board[y][x + 1] == 'x')
    {
        if (checkingMove == true) //MOVE 0 CAR L
            cout << "INVALID OPERATION \"MOVE " << number << " " << shipType << " " << direction << "\": PLACING SHIP TOO CLOSE TO OTHER SHIP" << endl;
        else if (SHIP_placeShip == 8)
            cout << "INVALID OPERATION \"SHIP  " << player << " " << y << " " << x << " " << direction << " " << number << " " << shipType << " " << segment << "\": PLACING SHIP TOO CLOSE TO OTHER SHIP" << endl;
        else
            cout << "INVALID OPERATION \"PLACE_SHIP " << y << " " << x << " " << direction << " " << number << " " << shipType << "\": PLACING SHIP TOO CLOSE TO OTHER SHIP" << endl;
        exit(0);
    }
    else
        return true;
}

bool left(char player, unsigned int y, unsigned int x, char direction, unsigned int number, char shipType[], char segment[], int SHIP_placeShip,bool checkingMove) {

    if (board1.board[y][x - 1] == '+' || board1.board[y][x - 1] == 'x')
    {
        if (checkingMove == true) //MOVE 0 CAR L
            cout << "INVALID OPERATION \"MOVE " << number << " " << shipType << " " << direction << "\": PLACING SHIP TOO CLOSE TO OTHER SHIP" << endl;
        else if (SHIP_placeShip == 8)
            cout << "INVALID OPERATION \"SHIP  " << player << " " << y << " " << x << " " << direction << " " << number << " " << shipType << " " << segment << "\": PLACING SHIP TOO CLOSE TO OTHER SHIP" << endl;
        else
            cout << "INVALID OPERATION \"PLACE_SHIP " << y << " " << x << " " << direction << " " << number << " " << shipType << "\": PLACING SHIP TOO CLOSE TO OTHER SHIP" << endl;
        exit(0);
    }
    else
        return true;
}

bool up(char player, unsigned int y, unsigned int x, char direction, unsigned int number, char shipType[], char segment[], int SHIP_placeShip,bool checkingMove) {

    if (board1.board[y - 1][x] == '+' || board1.board[y - 1][x] == 'x')
    {
        if (checkingMove == true) //MOVE 0 CAR L
            cout << "INVALID OPERATION \"MOVE " << number << " " << shipType << " " << direction << "\": PLACING SHIP TOO CLOSE TO OTHER SHIP" << endl;
        else if (SHIP_placeShip == 8)
            cout << "INVALID OPERATION \"SHIP  " << player << " " << y << " " << x << " " << direction << " " << number << " " << shipType << " " << segment << "\": PLACING SHIP TOO CLOSE TO OTHER SHIP" << endl;
        else
            cout << "INVALID OPERATION \"PLACE_SHIP " << y << " " << x << " " << direction << " " << number << " " << shipType << "\": PLACING SHIP TOO CLOSE TO OTHER SHIP" << endl;
        exit(0);
    }
    else
        return true;
}

bool down(char player, unsigned int y, unsigned int x, char direction, unsigned int number, char shipType[], char segment[], int SHIP_placeShip,bool checkingMove) {

    if (board1.board[y + 1][x] == '+' || board1.board[y + 1][x] == 'x')
    {
        if (checkingMove == true) //MOVE 0 CAR L
            cout << "INVALID OPERATION \"MOVE " << number << " " << shipType << " " << direction << "\": PLACING SHIP TOO CLOSE TO OTHER SHIP" << endl;
        else if (SHIP_placeShip == 8)
            cout << "INVALID OPERATION \"SHIP  " << player << " " << y << " " << x << " " << direction << " " << number << " " << shipType << " " << segment << "\": PLACING SHIP TOO CLOSE TO OTHER SHIP" << endl;
        else
            cout << "INVALID OPERATION \"PLACE_SHIP " << y << " " << x << " " << direction << " " << number << " " << shipType << "\": PLACING SHIP TOO CLOSE TO OTHER SHIP" << endl;
        exit(0);
    }
    else
        return true;
}

int getTheTypeOfShip(char shipType[3]) {
    if (shipType[2] == 'R')
    {
        return CAR;
    }
    else if (shipType[2] == 'T')
    {
        return BAT;
    }
    else if (shipType[2] == 'U')
    {
        return CRU;
    }
    else
        return DES;
}

bool checkingThePosition(int y, int x, char direction, int number, char* shipType) {			//if this funstion return true that means that it wasn't placed in the first postion

    if (playerA.numberOfPlacing == 0) {
        if (x == 0 || y == 0) {
            playerA.numberOfPlacing++;
            return false;
        }
        else {
            cout << "INVALID OPERATION \"PLACE_SHIP " << y << " " << x << " " << direction << " " << number << " " << shipType << "\": NOT IN STARTING POSITION" << endl;
            exit(0);
        }
    }
    else
        return false;
}

void errorMessageAlreadySet(unsigned int y, unsigned int x, char direction, char shipType[], unsigned int number) {
    cout << "INVALID OPERATION \"PLACE_SHIP " << y << " " << x << " " << direction << " " << number << " " << shipType << "\": ALL SHIPS OF THE CLASS ALREADY SET" << endl;
    exit(0);
}

bool checkingShipLimit_A(unsigned int y, unsigned int x, char direction, char shipType[], unsigned int number, int shipNumber) {
    if (shipNumber == CAR)  //CAR						
    {
        playerA.CAR_L--;
        if (playerA.CAR_L < 0) {
            errorMessageAlreadySet(y, x, direction, shipType, number);
            return true;
        }
        else
            return false;
    }
    else if (shipNumber == BAT) //BAT
    {
        playerA.BAT_L--;
        if (playerA.BAT_L < 0) {
            errorMessageAlreadySet(y, x, direction, shipType, number);
            return true;
        }
        else
            return false;
    }
    else if (shipNumber == CRU) //CRU
    {
        playerA.CRU_L--;
        if (playerA.CRU_L < 0) {
            errorMessageAlreadySet(y, x, direction, shipType, number);
            return true;
        }
        else
            return false;
    }
    else {
        playerA.DES_L--;
        if (playerA.DES_L < 0) {
            errorMessageAlreadySet(y, x, direction, shipType, number);
            return true;
        }
        else
            return false;
    }
}

bool checkingShipLimit_B(unsigned int y, unsigned int x, char direction, char shipType[], unsigned int number, int shipNumber) {
    if (shipNumber == CAR)  //CAR						
    {
        playerB.CAR_L--;
        if (playerB.CAR_L < 0) {
            errorMessageAlreadySet(y, x, direction, shipType, number);
            return true;
        }
        else
            return false;
    }
    else if (shipNumber == BAT) //BAT
    {
        playerB.BAT_L--;
        if (playerB.BAT_L < 0) {
            errorMessageAlreadySet(y, x, direction, shipType, number);
            return true;
        }
        else
            return false;
    }
    else if (shipNumber == CRU) //CRU
    {
        playerB.CRU_L--;
        if (playerB.CRU_L < 0) {
            errorMessageAlreadySet(y, x, direction, shipType, number);
            return true;
        }
        else
            return false;
    }
    else {
        playerB.DES_L--;
        if (playerB.DES_L < 0) {
            errorMessageAlreadySet(y, x, direction, shipType, number);
            return true;
        }
        else
            return false;
    }
}

void errorMessagePresentSet(unsigned int y, unsigned int x, char direction, char shipType[], unsigned int number) {
    cout << "INVALID OPERATION \"PLACE_SHIP " << y << " " << x << " " << direction << " " << number << " " << shipType << "\": SHIP ALREADY PRESENT" << endl;
    exit(0);
}

bool checkingAlreadyPresent_A(unsigned int y, unsigned int x, char direction, char shipType[], int number, int shipNumber) {

    if (shipNumber == CAR)  //CAR						
    {
        if (playerA.currentCAR == -1) {
            playerA.currentCAR = 0;
            return false;
        }
        else if (number == playerA.currentCAR) {
            errorMessagePresentSet(y, x, direction, shipType, number);
            return true;
        }
        else
            return false;
    }
    else if (shipNumber == BAT) //BAT
    {
        playerA.currentBAT++;
        if (playerA.currentBAT > BAT_COUNT) {
            errorMessagePresentSet(y, x, direction, shipType, number);
            return true;
        }
        else
            return false;
    }
    else if (shipNumber == CRU) //CRU
    {
        playerA.currentCRU++;
        if (playerA.currentCRU > CRU_COUNT) {
            errorMessagePresentSet(y, x, direction, shipType, number);
            return true;
        }
        else
            return false;
    }
    else {                     //DES
        playerA.currentDES++;
        if (playerA.currentDES > DES_COUNT) {
            errorMessagePresentSet(y, x, direction, shipType, number);
            return true;
        }
        else
            return false;
    }
}

bool checkingAlreadyPresent_B(unsigned int y, unsigned int x, char direction, char shipType[], int number, int shipNumber) {

    if (shipNumber == CAR)  //CAR						
    {
        playerB.currentCAR++;
        if (playerB.currentCAR > CAR_COUNT) {
            errorMessagePresentSet(y, x, direction, shipType, number);
            return true;
        }
        else
            return false;
    }
    else if (shipNumber == BAT) //BAT
    {
        playerB.currentBAT++;
        if (playerB.currentBAT > BAT_COUNT) {
            errorMessagePresentSet(y, x, direction, shipType, number);
            return true;
        }
        else
            return false;
    }
    else if (shipNumber == CRU) //CRU
    {
        playerB.currentCRU++;
        if (playerB.currentCRU > CRU_COUNT) {
            errorMessagePresentSet(y, x, direction, shipType, number);
            return true;
        }
        else
            return false;
    }
    else {
        playerB.currentDES++;
        if (playerB.currentDES > DES_COUNT) {
            errorMessagePresentSet(y, x, direction, shipType, number);
            return true;
        }
        else
            return false;
    }
}

bool checkingShootRange(unsigned int shootingX, unsigned int shootingY) {
    if ((shootingX > board1.row) || (shootingY > board1.column)) {
        cout << "INVALID OPERATION \"SHOOT " << shootingX << " " << shootingY << "\": FIELD DOES NOT EXIST" << endl;
        exit(0);
    }
    else
        return false;
}

bool checkingAllShipsHavePlayed(unsigned int shootingX, unsigned int shootingY) {
    int shipsWereAssigned = (playerA.totalShips + playerB.totalShips) / 2;
    //cout <<shipsWereAssigned<<endl;

    if (shipsWereAssigned > board1.timeOfplacing) {
        cout << "INVALID OPERATION \"SHOOT " << shootingX << " " << shootingY << "\": NOT ALL SHIPS PLACED" << endl;
        exit(0);
    }
    else
        return false;
}

bool checkingCloseShipsSHIP(char player, unsigned int y, unsigned int x, char direction, unsigned int number, char shipType[], char segment[], int SHIP_placeShip,bool checkingMove) {
    if (x == 0 && y == 0)           //top left          column 10    row 21
    {
        
        if (middle(player, y, x, direction, number, shipType, segment, SHIP_placeShip,checkingMove))
            if (right(player, y, x, direction, number, shipType, segment, SHIP_placeShip,checkingMove))
                if (down(player, y, x, direction, number, shipType, segment, SHIP_placeShip,checkingMove)) {}
        return false;
    }
    else if (x == 0 && y > 0 && y != board1.column - 1)    //top mid  //y!=9

    {
        if (middle(player, y, x, direction, number, shipType, segment, SHIP_placeShip,checkingMove))
            if (right(player, y, x, direction, number, shipType, segment, SHIP_placeShip,checkingMove))
                if (up(player, y, x, direction, number, shipType, segment, SHIP_placeShip,checkingMove))
                    if (down(player, y, x, direction, number, shipType, segment, SHIP_placeShip,checkingMove)) {}
        return false;
    }
    else if (y == 0 && x > 0 && x != board1.column - 1)       //left mid
    {
        if (middle(player, y, x, direction, number, shipType, segment, SHIP_placeShip,checkingMove))
            if (down(player, y, x, direction, number, shipType, segment, SHIP_placeShip,checkingMove))
                if (left(player, y, x, direction, number, shipType, segment, SHIP_placeShip,checkingMove)) {}
        return false;
    }
    else if (y == board1.column - 1 && x == board1.column - 1)       //bottom right
    {
        if (middle(player, y, x, direction, number, shipType, segment, SHIP_placeShip,checkingMove))
            if (up(player, y, x, direction, number, shipType, segment, SHIP_placeShip,checkingMove))
                if (left(player, y, x, direction, number, shipType, segment, SHIP_placeShip,checkingMove)) {}
        return false;
    }
    else if (x == board1.column - 1 && y == 0)   //top right
    {
        if (middle(player, y, x, direction, number, shipType, segment, SHIP_placeShip,checkingMove))
            if (down(player, y, x, direction, number, shipType, segment, SHIP_placeShip,checkingMove))
                if (left(player, y, x, direction, number, shipType, segment, SHIP_placeShip,checkingMove)) {}
        return false;
    }
    else if (y == board1.column - 1 && x > 0 && x != board1.column - 1)    //bottom mid
    {
        if (middle(player, y, x, direction, number, shipType, segment, SHIP_placeShip,checkingMove))
            if (left(player, y, x, direction, number, shipType, segment, SHIP_placeShip,checkingMove))
                if (up(player, y, x, direction, number, shipType, segment, SHIP_placeShip,checkingMove))
                    if (right(player, y, x, direction, number, shipType, segment, SHIP_placeShip,checkingMove)) {}
        return false;
    }
    else if (x == board1.column - 1 && y > 0 && y != board1.column - 1)     //extrem right mid 
    {
        if (middle(player, y, x, direction, number, shipType, segment, SHIP_placeShip,checkingMove))
            if (up(player, y, x, direction, number, shipType, segment, SHIP_placeShip,checkingMove))
                if (left(player, y, x, direction, number, shipType, segment, SHIP_placeShip,checkingMove))
                    if (down(player, y, x, direction, number, shipType, segment, SHIP_placeShip,checkingMove)) {}
        return false;
    }
    else if (y == board1.column - 1 && x == 0)         //bottom left
    {
        if (middle(player, y, x, direction, number, shipType, segment, SHIP_placeShip,checkingMove))
            if (right(player, y, x, direction, number, shipType, segment, SHIP_placeShip,checkingMove))
                if (up(player, y, x, direction, number, shipType, segment, SHIP_placeShip,checkingMove)) {}
        return false;
    }
    else {          // any where in the middle
        if (middle(player, y, x, direction, number, shipType, segment, SHIP_placeShip,checkingMove))
            if (up(player, y, x, direction, number, shipType, segment, SHIP_placeShip,checkingMove))
                if (left(player, y, x, direction, number, shipType, segment, SHIP_placeShip,checkingMove))
                    if (down(player, y, x, direction, number, shipType, segment, SHIP_placeShip,checkingMove))
                        if (right(player, y, x, direction, number, shipType, segment, SHIP_placeShip,checkingMove)) {}
        return false;
    }
}

    bool checkingREEF(unsigned int y, unsigned int x, char direction, unsigned int number, char shipType[], int size) {
        int xCOPY = x;
        int yCOPY = y;
        bool every_thing_is_cool = true;

        if (board1.REEF_count == 2) {
            if (direction == 'N')
            {
                for (int i = 0; i < size; i++)
                {
                    if (board1.board[y][x] == '#')
                    {
                        cout << "INVALID OPERATION \"PLACE_SHIP " << yCOPY << " " << xCOPY << " " << direction << " " << number << " " << shipType << "\": PLACING SHIP ON REEF" << endl;
                        exit(0);
                    }
                    y++;
                }
            }
            else if (direction == 'S')
            {
                for (int i = 0; i < size; i++)
                {
                    if (board1.board[y][x] == '#')
                    {
                        cout << "INVALID OPERATION \"PLACE_SHIP " << yCOPY << " " << xCOPY << " " << direction << " " << number << " " << shipType << "\": PLACING SHIP ON REEF" << endl;
                        exit(0);
                    }
                    y--;
                }
            }
            else if (direction == 'E')
            {
                for (int i = 0; i < size; i++)
                {
                    if (board1.board[y][x] == '#')
                    {
                        cout << "INVALID OPERATION \"PLACE_SHIP " << yCOPY << " " << xCOPY << " " << direction << " " << number << " " << shipType << "\": PLACING SHIP ON REEF" << endl;
                        exit(0);
                    }
                    x--;
                }
            }
            else
            {
                for (int i = 0; i < size; i++)
                {
                    if (board1.board[y][x] == '#')
                    {
                        cout << "INVALID OPERATION \"PLACE_SHIP " << yCOPY << " " << xCOPY << " " << direction << " " << number << " " << shipType << "\": PLACING SHIP ON REEF" << endl;
                        exit(0);
                    }
                    x++;
                }
            }
        }
        else {
            if (board1.board[y][x] == '#')
            {
                cout << "INVALID OPERATION \"PLACE_SHIP " << yCOPY << " " << xCOPY << " " << direction << " " << number << " " << shipType << "\": PLACING SHIP ON REEF" << endl;
                exit(0);
            }
        }
        return !every_thing_is_cool;
    }

void recordTheShipA(unsigned int y, unsigned int x, char direction, unsigned int number, int size, int placingTime) {

    playerA_ships[placingTime].y = y;
    playerA_ships[placingTime].x = x;
    playerA_ships[placingTime].direction = direction;
    playerA_ships[placingTime].number = number;
    playerA_ships[placingTime].shipType = size;
    if (size == CAR)
        playerA_ships[placingTime].moves = 2;
    else
        playerA_ships[placingTime].moves = 3;
}

void recordTheShipB(unsigned int y, unsigned int x, char direction, unsigned int number, int size, int placingTime) {

    playerB_ships[placingTime].y = y;
    playerB_ships[placingTime].x = x;
    playerB_ships[placingTime].direction = direction;
    playerB_ships[placingTime].number = number;
    playerB_ships[placingTime].shipType = size;
    if (size == CAR)
        playerB_ships[placingTime].moves = 2;
    else
        playerB_ships[placingTime].moves = 3;
}

void PLACE_SHIP(unsigned int y, unsigned int x, char direction, int size) {
    if (direction == 'N')
    {
        for (int i = 0; i < size; i++)
        {
            board1.board[y][x] = '+';
            y++;
        }
    }
    else if (direction == 'S')
    {
        for (int i = 0; i < size; i++)
        {
            board1.board[y][x] = '+';
            y--;
        }
    }
    else if (direction == 'E')
    {
        for (int i = 0; i < size; i++)
        {
            board1.board[y][x] = '+';
            x--;
        }
    }
    else
    {
        for (int i = 0; i < size; i++)
        {
            board1.board[y][x] = '+';
            x++;
        }
    }
}

void deletingShip(unsigned int y, unsigned int x, char direction, int size) {
    if (direction == 'N')
    {
        for (int i = 0; i < size; i++)
        {
            board1.board[y][x] = ' ';
            y++;
        }
    }
    else if (direction == 'S')
    {
        for (int i = 0; i < size; i++)
        {
            board1.board[y][x] = ' ';
            y--;
        }
    }
    else if (direction == 'E')
    {
        for (int i = 0; i < size; i++)
        {
            board1.board[y][x] = ' ';
            x--;
        }
    }
    else
    {
        for (int i = 0; i < size; i++)
        {
            board1.board[y][x] = ' ';
            x++;
        }
    }
}
//void PLACE_SHIP(unsigned int y, unsigned int x, char direction, unsigned int number, int size) {
//    if (direction == 'N')
//    {
//        for (int i = 0; i < size; i++)
//        {
//            board1.board[y][x] = '+';
//            y++;
//        }
//    }
//    else if (direction == 'S')
//    {
//        for (int i = 0; i < size; i++)
//        {
//            board1.board[y][x] = '+';
//            y--;
//        }
//    }
//    else if (direction == 'E')
//    {
//        for (int i = 0; i < size; i++)
//        {
//            board1.board[y][x] = '+';
//            x--;
//        }
//    }
//    else
//    {
//        for (int i = 0; i < size; i++)
//        {
//            board1.board[y][x] = '+';
//            x++;
//        }
//    }
//}
void moveing_action_R_A(int id) {

    if (playerA_ships[id].direction == 'N') {
        deletingShip(playerA_ships[id].y, playerA_ships[id].x, playerA_ships[id].direction, playerA_ships[id].shipType);
        --(playerA_ships[id].y);
        playerA_ships[id].direction = 'E';
        playerA_ships[id].x = playerA_ships[id].x + (playerA_ships[id].shipType - 1);
        PLACE_SHIP(playerA_ships[id].y, playerA_ships[id].x, playerA_ships[id].direction, playerA_ships[id].shipType);
        playerA_ships[id].moves--;
    }
    else if (playerA_ships[id].direction == 'E')
    {
        deletingShip(playerA_ships[id].y, playerA_ships[id].x, playerA_ships[id].direction, playerA_ships[id].shipType);
        ++(playerA_ships[id].x);
        playerA_ships[id].y = playerA_ships[id].y + playerA_ships[id].shipType;
        playerA_ships[id].direction = 'S';
        PLACE_SHIP(playerA_ships[id].y, playerA_ships[id].x, playerA_ships[id].direction, playerA_ships[id].shipType);
        playerA_ships[id].moves--;
    }
    else if (playerA_ships[id].direction == 'W')
    {
        deletingShip(playerA_ships[id].y, playerA_ships[id].x, playerA_ships[id].direction, playerA_ships[id].shipType);
        --(playerA_ships[id].x);
        playerA_ships[id].y = playerA_ships[id].y - playerA_ships[id].shipType;
        playerA_ships[id].direction = 'N';
        PLACE_SHIP(playerA_ships[id].y, playerA_ships[id].x, playerA_ships[id].direction, playerA_ships[id].shipType);
        playerA_ships[id].moves--;
    }
    else
    {
        deletingShip(playerA_ships[id].y, playerA_ships[id].x, playerA_ships[id].direction, playerA_ships[id].shipType);
        ++(playerA_ships[id].y);
        playerA_ships[id].x = playerA_ships[id].x - (playerA_ships[id].shipType - 1);
        playerA_ships[id].direction = 'W';
        PLACE_SHIP(playerA_ships[id].y, playerA_ships[id].x, playerA_ships[id].direction, playerA_ships[id].shipType);
        playerA_ships[id].moves--;
    }
}

void moveing_action_R_B(int id) {

    if (playerB_ships[id].direction == 'N') {
        deletingShip(playerB_ships[id].y, playerB_ships[id].x, playerB_ships[id].direction, playerB_ships[id].shipType);
        --(playerB_ships[id].y);
        playerB_ships[id].direction = 'E';
        playerB_ships[id].x = playerB_ships[id].x + (playerB_ships[id].shipType - 1);
        PLACE_SHIP(playerB_ships[id].y, playerB_ships[id].x, playerB_ships[id].direction, playerB_ships[id].shipType);
        playerB_ships[id].moves--;
    }
    else if (playerB_ships[id].direction == 'E')
    {
        deletingShip(playerB_ships[id].y, playerB_ships[id].x, playerB_ships[id].direction, playerB_ships[id].shipType);
        ++(playerB_ships[id].x);
        playerB_ships[id].y = playerB_ships[id].y + playerB_ships[id].shipType;
        playerB_ships[id].direction = 'S';
        PLACE_SHIP(playerB_ships[id].y, playerB_ships[id].x, playerB_ships[id].direction, playerB_ships[id].shipType);
        playerB_ships[id].moves--;
    }
    else if (playerB_ships[id].direction == 'W')
    {
        deletingShip(playerB_ships[id].y, playerB_ships[id].x, playerB_ships[id].direction, playerB_ships[id].shipType);
        --(playerB_ships[id].x);
        playerB_ships[id].y = playerB_ships[id].y - playerB_ships[id].shipType;
        playerB_ships[id].direction = 'N';
        PLACE_SHIP(playerB_ships[id].y, playerB_ships[id].x, playerB_ships[id].direction, playerB_ships[id].shipType);
        playerB_ships[id].moves--;
    }
    else
    {
        deletingShip(playerB_ships[id].y, playerB_ships[id].x, playerB_ships[id].direction, playerB_ships[id].shipType);
        ++(playerB_ships[id].y);
        playerB_ships[id].x = playerB_ships[id].x - (playerB_ships[id].shipType - 1);
        playerB_ships[id].direction = 'W';
        PLACE_SHIP(playerB_ships[id].y, playerB_ships[id].x, playerB_ships[id].direction, playerB_ships[id].shipType);
        playerB_ships[id].moves--;
    }
}

void moveing_action_L_A(int id) {

    if (playerA_ships[id].direction == 'N') {
        deletingShip(playerA_ships[id].y, playerA_ships[id].x, playerA_ships[id].direction, playerA_ships[id].shipType);
        playerA_ships[id].direction = 'W';
        --(playerA_ships[id].y);
        playerA_ships[id].x = playerA_ships[id].x - (playerA_ships[id].shipType - 1);
        PLACE_SHIP(playerA_ships[id].y, playerA_ships[id].x, playerA_ships[id].direction, playerA_ships[id].shipType);
        playerA_ships[id].moves--;
    }
    else if (playerA_ships[id].direction == 'E')
    {
        deletingShip(playerA_ships[id].y, playerA_ships[id].x, playerA_ships[id].direction, playerA_ships[id].shipType);
        ++(playerA_ships[id].x);
        playerA_ships[id].y = playerA_ships[id].y - (playerA_ships[id].shipType - 1);
        playerA_ships[id].direction = 'N';
        PLACE_SHIP(playerA_ships[id].y, playerA_ships[id].x, playerA_ships[id].direction, playerA_ships[id].shipType);
        playerA_ships[id].moves--;
    }
    else if (playerA_ships[id].direction == 'W')
    {
        deletingShip(playerA_ships[id].y, playerA_ships[id].x, playerA_ships[id].direction, playerA_ships[id].shipType);
        --(playerA_ships[id].x);
        playerA_ships[id].y = playerA_ships[id].y + (playerA_ships[id].shipType - 1);
        playerA_ships[id].direction = 'S';
        PLACE_SHIP(playerA_ships[id].y, playerA_ships[id].x, playerA_ships[id].direction, playerA_ships[id].shipType);
        playerA_ships[id].moves--;
    }
    else
    {
        deletingShip(playerA_ships[id].y, playerA_ships[id].x, playerA_ships[id].direction, playerA_ships[id].shipType);
        ++(playerA_ships[id].y);
        playerA_ships[id].x = playerA_ships[id].x + (playerA_ships[id].shipType - 1);
        playerA_ships[id].direction = 'E';
        PLACE_SHIP(playerA_ships[id].y, playerA_ships[id].x, playerA_ships[id].direction, playerA_ships[id].shipType);
        playerA_ships[id].moves--;
    }
}

void moveing_action_L_B(int id) {

    if (playerB_ships[id].direction == 'N') {
        deletingShip(playerB_ships[id].y, playerB_ships[id].x, playerB_ships[id].direction, playerB_ships[id].shipType);
        playerB_ships[id].direction = 'W';
        --(playerB_ships[id].y);
        playerB_ships[id].x = playerB_ships[id].x - (playerB_ships[id].shipType - 1);
        PLACE_SHIP(playerB_ships[id].y, playerB_ships[id].x, playerB_ships[id].direction, playerB_ships[id].shipType);
        playerB_ships[id].moves--;
    }
    else if (playerB_ships[id].direction == 'E')
    {
        deletingShip(playerB_ships[id].y, playerB_ships[id].x, playerB_ships[id].direction, playerB_ships[id].shipType);
        ++(playerB_ships[id].x);
        playerB_ships[id].y = playerB_ships[id].y - (playerB_ships[id].shipType - 1);
        playerB_ships[id].direction = 'N';
        PLACE_SHIP(playerB_ships[id].y, playerB_ships[id].x, playerB_ships[id].direction, playerB_ships[id].shipType);
        playerB_ships[id].moves--;
    }
    else if (playerB_ships[id].direction == 'W')
    {
        deletingShip(playerB_ships[id].y, playerB_ships[id].x, playerB_ships[id].direction, playerB_ships[id].shipType);
        --(playerB_ships[id].x);
        playerB_ships[id].y = playerB_ships[id].y + (playerB_ships[id].shipType - 1);
        playerB_ships[id].direction = 'S';
        PLACE_SHIP(playerB_ships[id].y, playerB_ships[id].x, playerB_ships[id].direction, playerB_ships[id].shipType);
        playerB_ships[id].moves--;
    }
    else
    {
        deletingShip(playerB_ships[id].y, playerB_ships[id].x, playerB_ships[id].direction, playerB_ships[id].shipType);
        ++(playerB_ships[id].y);
        playerB_ships[id].x = playerB_ships[id].x + (playerB_ships[id].shipType - 1);
        playerB_ships[id].direction = 'E';
        PLACE_SHIP(playerB_ships[id].y, playerB_ships[id].x, playerB_ships[id].direction, playerB_ships[id].shipType);
        playerB_ships[id].moves--;
    }
}

void moveing_action_F_A(int id) {

    if (playerA_ships[id].direction == 'N') {
        deletingShip(playerA_ships[id].y, playerA_ships[id].x, playerA_ships[id].direction, playerA_ships[id].shipType);
        --(playerA_ships[id].y);
        PLACE_SHIP(playerA_ships[id].y, playerA_ships[id].x, playerA_ships[id].direction, playerA_ships[id].shipType);
        playerA_ships[id].moves--;
    }
    else if (playerA_ships[id].direction == 'E')
    {
        deletingShip(playerA_ships[id].y, playerA_ships[id].x, playerA_ships[id].direction, playerA_ships[id].shipType);
        ++(playerA_ships[id].x);
        PLACE_SHIP(playerA_ships[id].y, playerA_ships[id].x, playerA_ships[id].direction, playerA_ships[id].shipType);
        playerA_ships[id].moves--;
    }
    else if (playerA_ships[id].direction == 'W')
    {
        deletingShip(playerA_ships[id].y, playerA_ships[id].x, playerA_ships[id].direction, playerA_ships[id].shipType);
        --(playerA_ships[id].x);
        PLACE_SHIP(playerA_ships[id].y, playerA_ships[id].x, playerA_ships[id].direction, playerA_ships[id].shipType);
        playerA_ships[id].moves--;
    }
    else
    {
        deletingShip(playerA_ships[id].y, playerA_ships[id].x, playerA_ships[id].direction, playerA_ships[id].shipType);
        ++(playerA_ships[id].y);
        PLACE_SHIP(playerA_ships[id].y, playerA_ships[id].x, playerA_ships[id].direction, playerA_ships[id].shipType);
        playerA_ships[id].moves--;
    }
}

void moveing_action_F_B(int id) {

    if (playerB_ships[id].direction == 'N') {
        deletingShip(playerB_ships[id].y, playerB_ships[id].x, playerB_ships[id].direction, playerB_ships[id].shipType);
        --(playerB_ships[id].y);
        PLACE_SHIP(playerB_ships[id].y, playerB_ships[id].x, playerB_ships[id].direction, playerB_ships[id].shipType);
        playerB_ships[id].moves--;
    }
    else if (playerB_ships[id].direction == 'E')
    {
        deletingShip(playerB_ships[id].y, playerB_ships[id].x, playerB_ships[id].direction, playerB_ships[id].shipType);
        ++(playerB_ships[id].x);
        PLACE_SHIP(playerB_ships[id].y, playerB_ships[id].x, playerB_ships[id].direction, playerB_ships[id].shipType);
        playerB_ships[id].moves--;
    }
    else if (playerB_ships[id].direction == 'W')
    {
        deletingShip(playerB_ships[id].y, playerB_ships[id].x, playerB_ships[id].direction, playerB_ships[id].shipType);
        --(playerB_ships[id].x);
        PLACE_SHIP(playerB_ships[id].y, playerB_ships[id].x, playerB_ships[id].direction, playerB_ships[id].shipType);
        playerB_ships[id].moves--;
    }
    else
    {
        deletingShip(playerB_ships[id].y, playerB_ships[id].x, playerB_ships[id].direction, playerB_ships[id].shipType);
        ++(playerB_ships[id].y);
        PLACE_SHIP(playerB_ships[id].y, playerB_ships[id].x, playerB_ships[id].direction, playerB_ships[id].shipType);
        playerB_ships[id].moves--;
    }
}

void move_A(unsigned int number, int shipType, char movingDirection) {
    char temp = 'x';
    for (int i = 0; i < board1.playerA_placing; i++)
    {
        if (playerA_ships[i].number == number && playerA_ships[i].shipType == shipType)
        {
            if (movingDirection == 'F')
            {
                moveing_action_F_A(i);
                checkingCloseShipsSHIP('A', playerA_ships[i].y, playerA_ships[i].x, movingDirection, playerA_ships[i].number, getTheTypeOfShip(playerA_ships[i].shipType),&temp, 0, true);
                return;
            }
            else if (movingDirection == 'L')
            {
                moveing_action_L_A(i);
            }
            else
                moveing_action_R_A(i);
        }
    }
}

void move_B(unsigned int number, int shipType, char movingDirection) {

    for (int i = 0; i < board1.playerB_placing; i++)
    {
        if (playerB_ships[i].number == number && playerB_ships[i].shipType == shipType)
        {
            if (movingDirection == 'F')
            {
                moveing_action_F_B(i);
                return;
            }
            else if (movingDirection == 'L')
            {
                moveing_action_L_B(i);
            }
            else
                moveing_action_R_B(i);
        }
    }
}

void checkValidationForPlayer_A(unsigned int y, unsigned int x, char direction, unsigned int number, char shipType[3], int SHIP_placeShip) { //function just to call the other function of checking it be in the playerAction function but was taken about used to 

    if (!board1.NEXT_PLAYER_usage)
    {
        if (!checkingThePosition(y, x, direction, number, shipType)) {						//checking if it was in the first position if it was the first move, if it return false that means that it have no problem
            if (!checkingAlreadyPresent_A(y, x, direction, shipType, number, getTheTypeOfShip(shipType))) {
                if (!checkingShipLimit_A(y, x, direction, shipType, number, getTheTypeOfShip(shipType))) {

                }
            }
        }
    }

    if (board1.NEXT_PLAYER_usage)
    {
        char player_temp = 'A';       //temp for the sake of the argymnets function 
        char segment[] = "1";   //temp
        if (!checkingREEF(y, x, direction, number, shipType, getTheTypeOfShip(shipType)))
        {
            if (!checkingCloseShipsSHIP(player_temp, y, x, direction, number, shipType, segment, SHIP_placeShip,false))
            {

            }
        }
    }

    PLACE_SHIP(y, x, direction, getTheTypeOfShip(shipType));
    board1.timeOfplacing++;
    recordTheShipA(y, x, direction, number, getTheTypeOfShip(shipType), board1.playerA_placing);
    board1.playerA_placing++;
}

void checkValidationForPlayer_B(unsigned int y, unsigned int x, char direction, unsigned int number, char shipType[3], int SHIP_placeShip) { //function just to call the other function of checking it be in the playerAction function but was taken about used to 

    if (!board1.NEXT_PLAYER_usage)
    {
        if (!checkingAlreadyPresent_B(y, x, direction, shipType, number, getTheTypeOfShip(shipType))) {
            if (!checkingShipLimit_B(y, x, direction, shipType, number, getTheTypeOfShip(shipType))) {

            }
        }
    }

    if (board1.NEXT_PLAYER_usage)
    {
        char player_temp = 'A';       //temp for the sake of the argymnets function 
        char segment[] = "1";   //temp
        if (!checkingREEF(y, x, direction, number, shipType, getTheTypeOfShip(shipType)))
        {
            if (!checkingCloseShipsSHIP(player_temp, y, x, direction, number, shipType, segment, SHIP_placeShip,false))
            {

            }
        }
    }

    PLACE_SHIP(y, x, direction, getTheTypeOfShip(shipType));
    board1.timeOfplacing++;
    recordTheShipB(y, x, direction, number, getTheTypeOfShip(shipType), board1.playerB_placing);
    board1.playerB_placing++;
}

void SHIP(unsigned int y, unsigned int x, char direction, int size, char segment[]) {
    if (direction == 'N')
    {
        for (int i = 0; i < size; i++)
        {
            if (segment[i] == '1')
            {
                board1.board[y][x] = '+';
                y++;
            }
            else
            {
                board1.board[y][x] = 'x';
                y++;
            }
        }
    }
    else if (direction == 'S')
    {
        for (int i = 0; i < size; i++)
        {
            if (segment[i] == '1')
            {
                board1.board[y][x] = '+';
                y--;
            }
            else
            {
                board1.board[y][x] = 'x';
                y--;
            }
        }
    }
    else if (direction == 'E')
    {
        for (int i = 0; i < size; i++)
        {
            if (segment[i] == '1')
            {
                board1.board[y][x] = '+';
                x--;
            }
            else
            {
                board1.board[y][x] = 'x';
                x--;
            }
        }
    }
    else
    {
        for (int i = 0; i < size; i++)
        {
            if (segment[i] == '1')
            {
                board1.board[y][x] = '+';
                x++;
            }
            else
            {
                board1.board[y][x] = 'x';
                x++;
            }
        }
    }
}

void checkValidationForPlayer_SHIP(char player, unsigned int y, unsigned int x, char direction, unsigned int number, int size, char shipType[], char segment[], int SHIP_placeShip) {
    board1.SHIP_usage = true;

    if (board1.SHIP_usage && player == 'A')
    {
        if (!checkingCloseShipsSHIP(player, y, x, direction, number, shipType, segment, SHIP_placeShip,false))
        {

        }
    }

    SHIP(y, x, direction, size, segment);
    board1.timeOfplacingSHIP++;
}

void SHOOT(unsigned int x, unsigned int y) {

    if (board1.board[x][y] == '+')
        board1.board[x][y] = 'x';

    if (board1.SET_FLEET_usage)
    {

        if (playerA.totalShips > 0)		// to check how many ships left in the set fleet A
            playerA.totalShips--;

        else if (playerB.totalShips > 0)  // to check how many ships left in the set fleet b
            playerB.totalShips--;

        if (playerB.totalShips == 0 && playerA.totalShips == 0)
            exit(0);
    }
}

void checkTheWinnerB() {
    bool playerB_won = true;

    for (int i = 0; i < board1.column; i++) //10 is the plyaer  A bounderse
    {
        for (int j = 0; j < board1.column; j++)
        {
            if (board1.board[i][j] == '+') {
                playerB_won = false;
                i = board1.column;
                j = board1.column;  // just to break the loop
            }
        }
    }

    if (playerB_won) {
        cout << "B won" << endl;
        exit(0);
    }
}

void checkTheWinnerA() {
    bool playerA_won = true;

    for (int i = board1.column + 1; i < board1.row; i++)		// board1.column+1 is the player b bounderse
    {
        for (int j = 0; j < board1.column; j++)
        {
            if (board1.board[i][j] == '+') {
                playerA_won = false;
                i = board1.row;
                j = board1.column;
            }
        }
    }

    if (playerA_won)
    {
        cout << "A won" << endl;
        exit(0);
    }
}

bool checkingIfplayerA_starts(char command[]) {
    if (board1.numberOfshoots == 0) {
        if (command[7] == 'A')
        {
            return false;
        }
        else {
            cout << "INVALID OPERATION \"[playerB] \": THE OTHER PLAYER EXPECTED";
            exit(0);
        }
    }
    else
        return false;
}

void checkValidationForShootings(unsigned int shootingX, unsigned int shootingY, char command[]) {
    bool inSideTheBoard = false;
    bool allShipsWerePlayed = false;
    bool playerAstarts = false;

    if (!checkingShootRange(shootingX, shootingY)) {
        inSideTheBoard = true;
        if (board1.SET_FLEET_usage) {
            if (!checkingAllShipsHavePlayed(shootingX, shootingY)) {
                allShipsWerePlayed = true;
                if (!checkingIfplayerA_starts(command)) {
                    playerAstarts = true;
                }
            }
        }
        else
            allShipsWerePlayed = true;
    }

    if (inSideTheBoard && allShipsWerePlayed) {			//if it is true make a move
        SHOOT(shootingX, shootingY);
        board1.SHOOT_usage = true;
        board1.numberOfshoots++;
        checkTheWinnerA();
        checkTheWinnerB();
    }
}

void SET_FLEET(char player, int car, int bat, int cru, int des) {
    board1.SET_FLEET_usage = true;
    if (player == 'A') {
        playerA.CAR_L = car;
        playerA.BAT_L = bat;
        playerA.CRU_L = cru;
        playerA.DES_L = des;
        playerA.totalShips = (car + bat + cru + des) * 2;
    }
    else {
        playerB.CAR_L = car;
        playerB.BAT_L = bat;
        playerB.CRU_L = cru;
        playerB.DES_L = des;
        playerB.totalShips = (car + bat + cru + des) * 2;
    }
}

void INIT_POSTION_f(char player, unsigned int y1, unsigned int x1, unsigned int y2, unsigned int x2) {
    board1.INIT_POSITION_usage = true;
    if (player == 'A')
    {
        playerA.y1 = y1;
        playerA.x1 = x1;
        playerA.y2 = y2;
        playerA.x2 = x2;
    }
    else
    {
        playerB.y1 = y1;
        playerB.x1 = x1;
        playerB.y2 = y2;
        playerB.x2 = x2;
    }
}

void REEF_f(unsigned int y, unsigned int x) {
    if (y > board1.row || x > board1.column)
    {
        cout << "REEF IS NOT PLACED ON BOARD" << endl;
        exit(0);
    }

    board1.REEF_usage = true;
    board1.board[y][x] = '#';
    board1.REEF_count++;
}

void playerA_Actions(char command[]) {

    char temp[20] = "";

    while (cin >> temp)
    {
        switch (dictionary(temp))
        {
        case 12:	//PLACE_SHIP
        {
            unsigned int x, y, number;										//x,y are the spot , number is the number of the ship or what order it is
            char direction;
            char shipType[20];
            cin >> y >> x >> direction >> number >> shipType;
            checkValidationForPlayer_A(y, x, direction, number, shipType, 14);
            break;
        }
        case 11:    //SHOOT
        {
            unsigned int shootingX, shootingY;
            cin >> shootingX >> shootingY;
            checkValidationForShootings(shootingX, shootingY, command);
            break;
        }
        case 13:    //MOVE
        {
            unsigned int number;
            char shipType[20];
            char movingDirection;
            cin >> number >> shipType >> movingDirection;
            board1.move_usage = true;
            move_A(number, getTheTypeOfShip(shipType), movingDirection);
            break;
        }
        case 9:     //[playerA]
            return;

        default:
            cout << "undefied operation" << endl;
            break;
        }
    }
}

void playerB_Actions(char command[]) {

    char temp[20] = "";

    while (cin >> temp)
    {
        switch (dictionary(temp))
        {
        case 12:	//PLACE_SHIP
        {
            unsigned int x, y, number;										//x,y are the spot , number is the number of the ship or what order it is
            char direction;
            char shipType[20];
            cin >> y >> x >> direction >> number >> shipType;
            checkValidationForPlayer_B(y, x, direction, number, shipType, 14);
            break;
        }
        case 11:    //SHOOT
        {
            unsigned int shootingX, shootingY;
            cin >> shootingX >> shootingY;
            checkValidationForShootings(shootingX, shootingY, command);
            break;
        }
        case 13:    //MOVE
        {
            unsigned int number;
            char shipType[20];
            char movingDirection;
            cin >> number >> shipType >> movingDirection;
            board1.move_usage = true;
            move_B(number, getTheTypeOfShip(shipType), movingDirection);
            break;
        }
        case 10:    //[playerB]
            return;

        default:
            cout << "undefied operation" << endl;
            break;
        }
    }
}

void search(int y, int x, char direction, int shipType) {
    int holderPositionAX = x;
    int holderPositionAY = y;
    //cout << holderPositionAY << " " << holderPositionAY <<" "<<i<< endl;
    if (direction == 'N')
    {
        for (int i = 0; i < shipType; i++)
        {
            if (board1.board[holderPositionAY][holderPositionAX] == '+')
                cout << "1";
            else
                cout << "0";
            holderPositionAY++;
        }
    }
    else if (direction == 'S')
    {
        for (int i = 0; i < shipType; i++)
        {
            if (board1.board[holderPositionAY][holderPositionAX] == '+')
                cout << "1";
            else
                cout << "0";            
            holderPositionAY--;
        }
    }
    else if (direction == 'E')
    {
        for (int i = 0; i < shipType; i++)
        {
            if (board1.board[holderPositionAY][holderPositionAX] == '+')
                cout << "1";
            else
                cout << "0";         
            holderPositionAX--;
        }
    }
    else
    {
        for (int i = 0; i < shipType; i++)
        {
            if (board1.board[holderPositionAY][holderPositionAX] == '+')
                cout << "1";
            else
                cout << "0";
            holderPositionAX++;
        }
    }
}

void printingShipType(int shipType) {
    
    if (shipType == CAR)
        cout << "CAR";
    else if (shipType == BAT)
        cout << "BAT";
    else if (shipType == CRU)
        cout << "CRU";
    else
        cout << "DES";
}

void printShips(int i) {

    cout << "SHIP A " << playerA_ships[i].y << " " << playerA_ships[i].x << " " << playerA_ships[i].direction << " " << playerA_ships[i].number << " ";
    printingShipType(playerA_ships[i].shipType);
    cout << " ";
    search(playerA_ships[i].y, playerA_ships[i].x, playerA_ships[i].direction, playerA_ships[i].shipType);
    cout << endl;
}

void printingShipsInOrder() {
    for (int i = 0; i < board1.playerA_placing; i++)
    {
        if (playerA_ships[i].shipType == CAR)
            printShips(i);
    }

    for (int i = 0; i < board1.playerA_placing; i++)
    {
        if (playerA_ships[i].shipType == BAT)
            printShips(i);
    }

    for (int i = 0; i < board1.playerA_placing; i++)
    {
        if (playerA_ships[i].shipType == CRU)
            printShips(i);
    }

    for (int i = 0; i < board1.playerA_placing; i++)
    {
        if (playerA_ships[i].shipType == DES)
            printShips(i);
    }
}

void save() {
                                                 
    cout << "[state]" << endl;
    cout << "BOARD_SIZE " << board1.row << " " << board1.column << endl;
    
    // player A cout 
    if (board1.NEXT_PLAYER_usage)
        cout << NEXT_PLAYER << " A" << endl;
    cout << INIT_POSITION << " A " << playerA.y1 << " " << playerA.x1 << " " << playerA.y2 << " "<<playerA.x2 << endl;
    if (board1.SET_FLEET_usage)
        cout << SET_FLEETc << " A " << playerA.CAR_L << " " << playerA.BAT_L << " " << playerA.CRU_L << " "<< playerA.DES_L << endl;
    if (board1.playerA_placing) 
        printingShipsInOrder();

    //player B cout
    cout << INIT_POSITION << " B " << playerB.y1 << " " << playerB.x1 << " " << playerB.y2 << " " << playerB.x2 << endl;
    if (board1.SET_FLEET_usage)
        cout << SET_FLEETc << " B " << playerB.CAR_L << " " << playerB.BAT_L << " " << playerB.CRU_L << " " << playerB.DES_L << endl;
    for (int i = board1.playerB_placing; i --> 0;)
    {
        cout << "SHIP B " << playerB_ships[i].y << " " << playerB_ships[i].x << " " << playerB_ships[i].direction << " " << playerB_ships[i].number << " ";
        printingShipType(playerB_ships[i].shipType);
        cout << " ";
        search(playerB_ships[i].y, playerB_ships[i].x, playerB_ships[i].direction, playerB_ships[i].shipType);
        cout << endl;
    }
    cout << "[state]" << endl;
}                                          

void state() {

    char temp[20] = "";
    //cin >> temp;
    while (cin >> temp)
    {
        switch (dictionary(temp))
        {
        case 1:	             //PRINT
        {
            int i;
            cin >> i;
            if (i == 0)
                show();
            break;
        }
        case 2:             //SET_FLEET
        {
            char p;
            int car, bat, cru, des;
            cin >> p >> car >> bat >> cru >> des;
            SET_FLEET(p, car, bat, cru, des);
            break;
        }
        case 3:             //NEXT_PLAYER
        {                   //NEXT_PLAYER A
            char player;
            cin >> player;
            board1.NEXT_PLAYER_usage = true;
            break;
        }
        case 4:             //BOARD_SIZE
        {
            /*board1.*/resize_board();
            break;
        }
        case 5:            //INIT_POSITION
        {                  //INIT_POSITION A 0 0 5 5
            char player;
            unsigned int y1, x1, y2, x2;
            cin >> player >> y1 >> x1 >> y2 >> x2;
            INIT_POSTION_f(player, y1, x1, y2, x2);
            break;
        }
        case 6:            //REEF
        {
            unsigned int y, x;
            cin >> y >> x;
            REEF_f(y, x);
            break;
        }
        case 7:             //[state] was used again
            return;
        case 8:              // SHIP
        {
            unsigned int x, y, number;             // SHIP A 0 0 N 0 CAR 11101
            char player, direction;
            char shipType[20], segment[20];
            cin >> player >> y >> x >> direction >> number >> shipType >> segment;
            checkValidationForPlayer_SHIP(player, y, x, direction, number, getTheTypeOfShip(shipType), shipType, segment, dictionary(temp));
            break;
        }
        case 15:              //SAVE
            save();
            break;
        default:
            cout << "ERROR input of state" << endl;
            break;
        }
    }
}

int main()
{     
    clear();	    //inizlatize the board to empty 

    char command[100] = {};
    while (cin >> command)
    {
        switch (dictionary(command))
        {
        case 9:	   //[playerA] 
            playerA_Actions(command);
            break;

        case 10:   //[playerB] 
            playerB_Actions(command);
            break;

        case 7:    //[state]
            state();
            break;

        default:
            cout << "ERROR in the input";
            break;
        }
    }
    return 0;

}