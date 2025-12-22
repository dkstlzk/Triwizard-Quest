#include <raylib.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ALL_GAMES_H.h"

#define TILE_SIZE 40
#define MAP_WIDTH 15
#define MAP_HEIGHT 15
#define MAX_GHOSTS 3

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define OFFSET_X ((WINDOW_WIDTH - (MAP_WIDTH * TILE_SIZE)) / 2)
#define OFFSET_Y ((WINDOW_HEIGHT - (MAP_HEIGHT * TILE_SIZE)) / 2)

int original_map[MAP_HEIGHT][MAP_WIDTH]={
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,2,2,2,1,2,2,2,2,2,1,2,2,2,1},
    {1,2,1,2,1,2,1,1,1,2,1,2,1,2,1},
    {1,2,1,2,2,2,2,1,2,2,2,2,1,2,1},
    {1,2,1,2,1,1,2,1,2,1,1,2,1,2,1},
    {1,2,2,2,2,1,2,2,2,1,2,2,2,2,1},
    {1,1,1,1,2,1,1,2,1,1,2,1,1,1,1},
    {1,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
    {1,2,1,1,1,1,1,2,1,1,1,1,1,2,1},
    {1,2,1,2,2,2,1,2,1,2,2,2,1,2,1},
    {1,2,1,2,1,2,2,2,2,2,1,2,1,2,1},
    {1,2,1,2,1,1,1,2,1,1,1,2,1,2,1},
    {1,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
    {1,2,1,1,1,1,1,1,1,1,1,1,1,2,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int map[MAP_HEIGHT][MAP_WIDTH];

typedef struct{
    int x, y;    //give the location of pacman
} Pacman;

typedef struct{
    int x, y;    //location of ghosts
    int lastX, lastY;    //last visited location of ghosts 
    Color color;     //colour from raylib to differentiate the ghosts
} Deatheater;

Pacman snitch;   //making the main character snitch
Deatheater deatheaters[MAX_GHOSTS];   //array of the two ghosts call karne ke liye
int pelletsLeft;
bool lose= false;
bool win= false;

void beforegamestarts(){ 
    snitch.x =1;
    snitch.y =1;   //starting point 

 deatheaters[0]= (Deatheater){12,5,12,5,PURPLE};
 deatheaters[1]= (Deatheater){7,7,7,7,PINK};    //defining ghosts ke starting movements and colour

    pelletsLeft=0;
    for (int j=0; j<MAP_HEIGHT; j++){
        for (int i=0; i< MAP_WIDTH; i++){
            if (map[j][i]== 2){
                pelletsLeft++;
            }
        }

    }
}

void DrawMap(){
    for (int j=0; j<MAP_HEIGHT; j++){    //basically jahaan pe mere golden pellets hai voh mera path signify karega and the rest is just the board
        for (int i=0; i< MAP_WIDTH; i++){ 
            if (map[j][i]==1){
                DrawRectangle(OFFSET_X + i*TILE_SIZE, OFFSET_Y + j*TILE_SIZE, TILE_SIZE, TILE_SIZE, DARKGRAY);
                DrawRectangleLines(OFFSET_X + i*TILE_SIZE, OFFSET_Y + j*TILE_SIZE, TILE_SIZE, TILE_SIZE, GRAY);
            } 
            else if (map[j][i]==2){ 
                DrawCircle(OFFSET_X + i*TILE_SIZE + TILE_SIZE/2, OFFSET_Y + j*TILE_SIZE + TILE_SIZE/2, 5, GOLD);
            }
        }
    }
} 


bool CheckCollision(){
    for (int i=0; i < MAX_GHOSTS; i++){
        if (snitch.x==deatheaters[i].x && snitch.y==deatheaters[i].y){   //if dono ke currrent coordinates same hogaye 
            return true;
        }
    }
    return false;
}

void ghostmovements(Deatheater *ghost, int ghostindex){ 
    int bestDx=0, bestDy=0;
    int minDist=100000;
    bool foundValidMove= false;

    int directions[4][2]= { {0,1}, {1,0}, {0,-1}, {-1,0} };

    for (int i=0; i<4; i++){
        int nx= ghost->x +directions[i][0];
        int ny= ghost->y +directions[i][1];

        if (nx >= 0 && ny >= 0 && nx < MAP_WIDTH && ny < MAP_HEIGHT &&
            map[ny][nx] != 1 && !(nx==ghost->lastX && ny==ghost->lastY)){    //if saare conditions meet hoti hai like outside of game nahi jaa raha and path par hi hai and also last position par bhi nahi hai

            bool positionOccupied= false;
            for (int j=0; j<MAX_GHOSTS; j++){    //making sure ki voh dusre ghost se collide nai kar raha
                if (j!= ghostindex && deatheaters[j].x ==nx && deatheaters[j].y ==ny){ 
                    positionOccupied=true;    //agar nahi kar raha toh this is your new position
                    break;
                }
            }

            if (!positionOccupied){
                int dx= snitch.x - nx;    //distance calculate from ghost to snitch
                int dy= snitch.y - ny; 
                int dist= dx*dx + dy*dy;

                if (dist<minDist){    //if less than distance then usko valid move mila 
                    minDist=dist;
                    bestDx= directions[i][0];
                    bestDy= directions[i][1];
                    foundValidMove= true;
                }
            }
        }
    }

    if (!foundValidMove){
        for (int i=0; i<4; i++){
            int nx= ghost->x +directions[i][0];
            int ny= ghost->y +directions[i][1];
            if (nx>=0 && ny>=0 && nx<MAP_WIDTH && ny<MAP_HEIGHT && map[ny][nx]!=1){   //if not it will go back to its prev positions
                bestDx= directions[i][0];
                bestDy= directions[i][1];
                break;
            }
        }
    }

    ghost->lastX = ghost->x;
    ghost->lastY = ghost->y;
    ghost->x +=bestDx;
    ghost->y +=bestDy;
}
void MoveGhostsSafely(){
    for (int i=0; i<MAX_GHOSTS; i++){
        ghostmovements(&deatheaters[i], i);    //saare ghosts following all movements
    }

    for (int i=0; i<MAX_GHOSTS; i++){     //goes through each ghost
        for (int j=0; j<MAX_GHOSTS; j++){    //aur saare ghosts ko check karta hai
            if (i!=j && deatheaters[i].x == deatheaters[j].x && deatheaters[i].y == deatheaters[j].y){    //if collision
                deatheaters[i].x = deatheaters[i].lastX;    //last position pe chale jao
               deatheaters[i].y =deatheaters[i].lastY; 
            }
        }
    }
}

int snitch_escape(){
    memcpy(map, original_map, sizeof(map));

    win=false;
    lose=false;
    pelletsLeft=0;

    beforegamestarts();
    //InitWindow(MAP_WIDTH * TILE_SIZE, MAP_HEIGHT * TILE_SIZE, "Snitch Escape");   //size of screen with the name on top
    SetTargetFPS(80);
    int ghostFrame = 0;

    while (!WindowShouldClose()){    //jab tak window is open 
        if (!lose && !win){     //the game is not over 
            if (IsKeyPressed(KEY_RIGHT) && map[snitch.y][snitch.x + 1] !=1){
                snitch.x++;     //x location increases
            }
            else if (IsKeyPressed(KEY_LEFT) && map[snitch.y][snitch.x - 1] !=1){
                snitch.x--;    //x location decreases
            }
            else if (IsKeyPressed(KEY_UP) && map[snitch.y - 1][snitch.x] !=1){
                snitch.y--;   //y location decreases
            }
            else if (IsKeyPressed(KEY_DOWN) && map[snitch.y + 1][snitch.x] !=1){
                snitch.y++;    //y location increases
            }

            if (map[snitch.y][snitch.x]==2){      //jab the snitch goes to a tile with pellet
                map[snitch.y][snitch.x]=0;    //total no. of pellets decrease hojaayenge and voh tile will change to empty space
                pelletsLeft--;
            }

            if (++ghostFrame>=30){    //this is for checking ki after every 30 frames the ghost updates its movements
                MoveGhostsSafely();
                ghostFrame=0;
            }

            if (CheckCollision()) lose= true;    //if collision ho jata hai then game over
            if (pelletsLeft==0) win= true;    //ya pellets khatam ho jaate hai then game won
        }

        BeginDrawing();
        ClearBackground(BLACK);

        DrawMap();

        for (int i=0; i<MAX_GHOSTS; i++){
            float centerx= OFFSET_X+ deatheaters[i].x*TILE_SIZE + TILE_SIZE/2;
            float centery= OFFSET_Y+ deatheaters[i].y*TILE_SIZE + TILE_SIZE/2;
            DrawCircle(centerx, centery, (TILE_SIZE/2)-6, deatheaters[i].color); 
            DrawCircle(centerx-5, centery-4, 3, WHITE);
            DrawCircle(centerx+5, centery-4, 3, WHITE);
        }

        float snitchX= OFFSET_X+ snitch.x*TILE_SIZE + TILE_SIZE/2; 
        float snitchY= OFFSET_Y+ snitch.y*TILE_SIZE + TILE_SIZE/2; 

        DrawCircle(snitchX, snitchY, TILE_SIZE/2 - 4, GOLD);


        int textwidth= MeasureText("Caught by Death Eater",30);
        int posx= (WINDOW_WIDTH-textwidth)/2;
        int textwidth2= MeasureText("The Snitch escaped!",30);
        int posx2= (WINDOW_WIDTH-textwidth2)/2;
        
        if (lose) {
            DrawText("Caught by Death Eater!", posx, 300, 30, RED);
        }
        if (win) {
            DrawText("The Snitch escaped!", posx2, 300, 30, GREEN);
        }

        if (win || lose) {
            DrawText("Press ENTER to continue", 200, 380, 20, WHITE);

            if (IsKeyPressed(KEY_ENTER)) {
                break;   // EXIT mini-game
            }
        }



        EndDrawing();
    }
    if(win) return 1;
    else return 0;
}
