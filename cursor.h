
/*

This header file contains functions for cursor operations.

*/

#ifndef _CURSOR_H_
#define _CURSOR_H_

// Set cursor position to coordinates specified by the parameter.
void SetCursorPosition(const COORD where)
{
    SetConsoleCursorPosition(console_screen_buffer , where);
}

// Get current cursor position in terms of coordinates.
COORD GetCursorPosition()
{
    GetConsoleScreenBufferInfo(console_screen_buffer , &console_screen_buffer_info);
    return console_screen_buffer_info.dwCursorPosition;
}

// Move cursor 1 square to direction specified by the parameter.
void MoveCursor(const DIRECTION where)
{
    COORD c = GetCursorPosition();
    if     (where == UP)    c.Y--;
    else if(where == LEFT)  c.X--;
    else if(where == RIGHT) c.X++;
    else if(where == DOWN)  c.Y++;
    SetCursorPosition(c);
}

// Check if cursor is inside the main box.
bool IsCursorInsideMainBox()
{
    COORD c = GetCursorPosition();
    return main_box_upper_left_position.X < c.X && c.X < main_box_lower_right_position.X && main_box_upper_left_position.Y < c.Y && c.Y < main_box_lower_right_position.Y;
}

// Check if cursor specified by parameter is inside the main box.
bool IsCursorInsideMainBox(COORD coordinate)
{
    return main_box_upper_left_position.X < coordinate.X && coordinate.X < main_box_lower_right_position.X && main_box_upper_left_position.Y < coordinate.Y && coordinate.Y < main_box_lower_right_position.Y;
}

// Check if cursor is inside and 1 square down below the north wall.
bool IsCursorNearNorthWall()
{
    COORD c = GetCursorPosition();
    if(IsCursorInsideMainBox()) return c.Y == starting_position.Y;
    return false;
}

// Check if cursor is inside and 1 square right of the west wall.
bool IsCursorNearWestWall()
{
    COORD c = GetCursorPosition();
    if(IsCursorInsideMainBox()) return c.X == starting_position.X;
    return false;
}

// Check if cursor is inside and 1 square up above the south wall.
bool IsCursorNearSouthWall()
{
    COORD c = GetCursorPosition();
    if(IsCursorInsideMainBox()) return c.Y == main_box_lower_right_position.Y - 1;
    return false;
}

// Check if cursor is inside and 1 square left of the east wall.
bool IsCursorNearEastWall()
{
    COORD c = GetCursorPosition();
    if(IsCursorInsideMainBox()) return c.X == main_box_lower_right_position.X - 1;
    return false;
}

// Check if cursor specified by parameter is inside and 1 square down below the north wall.
bool IsCursorNearNorthWall(COORD coordinate)
{
    if(IsCursorInsideMainBox(coordinate)) return coordinate.Y == starting_position.Y;
    return false;
}

// Check if cursor specified by parameter is inside and 1 square right of the west wall.
bool IsCursorNearWestWall(COORD coordinate)
{
    if(IsCursorInsideMainBox(coordinate)) return coordinate.X == starting_position.X;
    return false;
}

// Check if cursor specified by parameter is inside and 1 square up above the south wall.
bool IsCursorNearSouthWall(COORD coordinate)
{
    if(IsCursorInsideMainBox(coordinate)) return coordinate.Y == main_box_lower_right_position.Y - 1;
    return false;
}

// Check if cursor specified by parameter is inside and 1 square left of the east wall.
bool IsCursorNearEastWall(COORD coordinate)
{
    if(IsCursorInsideMainBox(coordinate)) return coordinate.X == main_box_lower_right_position.X - 1;
    return false;
}

#endif
