/*

Written by Orçun Altınsoy on July 2014

*/

#include "all.h"

int main()
{
    srand(time(NULL));

    SetConsoleWindowSize(ROW_SIZE , COLUMN_SIZE);

    DrawMainArea();

    WriteMenu(main_menu);
    WriteInformation(main_info);

    SetCursorPosition(starting_position);

    int rs = main_box_lower_right_position.X - main_box_upper_left_position.X - 1;
    int cs = main_box_lower_right_position.Y - main_box_upper_left_position.Y - 1;
    // Allocate memory for 'object' array...
    object = (OBJECT**)malloc(sizeof(OBJECT*) * cs);
    for(int i = 0 ; i < cs ; i++) object[i] = (OBJECT*)malloc(sizeof(OBJECT) * rs);
    // Fill 'object' array with spaces...
    for(int i = 0 ; i < cs ; i++) for(int j = 0 ; j < rs ; j++) object[i][j] = NOTHING;

    // Allocate memory for 'weight' array...
    weight = (double**)malloc(sizeof(double*) * cs);
    for(int i = 0 ; i < cs ; i++) weight[i] = (double*)malloc(sizeof(double) * rs);
    // Allocate memory for 'current_background' array...
    current_background = (COLOUR**)malloc(sizeof(COLOUR*) * cs);
    for(int i = 0 ; i < cs ; i++) current_background[i] = (COLOUR*)malloc(sizeof(COLOUR) * rs);
    // Fill 'current_background' array with BLACK values...
    for(int i = 0 ; i < cs ; i++) for(int j = 0 ; j < rs ; j++) current_background[i][j] = BLACK;

    int c;
    for(;;)
    {
        c = getch();

        if(c == SPECIAL_KEY)
        {
            c = getch();
            if(c == UP_KEY)     { if(!IsCursorNearNorthWall()) MoveCursor(UP);    continue; }
            if(c == LEFT_KEY)   { if(!IsCursorNearWestWall())  MoveCursor(LEFT);  continue; }
            if(c == DOWN_KEY)   { if(!IsCursorNearSouthWall()) MoveCursor(DOWN);  continue; }
            if(c == RIGHT_KEY)  { if(!IsCursorNearEastWall())  MoveCursor(RIGHT); continue; }
            if(c == DELETE_KEY) { ClearMainArea(); ResetBackground(); continue; }
        }
        if(c == 'v' || c == 'V') { SetObject(RED_BLOCK); continue; }
        if(c == 'b' || c == 'B') { SetObject(BLUE_BLOCK); continue; }
        if(c == 'd' || c == 'D') { SetObject(NOTHING); continue; }
        if(c == 'r' || c == 'R') { Random(); continue; }
        if(c == 'l' || c == 'L') { Load(); continue; }
        if(c == 's' || c == 'S') { Save(); continue; }
        if(c == ENTER_KEY) { Start(); continue; }
        if(c == ESC_KEY) return 0;
        // if(c == 'q' || c == 'Q') { SetBackground(BLACK); Log(); continue; }
    }
}
