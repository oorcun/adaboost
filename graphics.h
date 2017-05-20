
/*

This header file contains functions for graphics operations.

*/

#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

// Draw rectangular main area.
void DrawMainArea()
{
    COORD c = GetCursorPosition();
    int i , j;

    SetCursorPosition(main_box_upper_left_position);

    // Upper side...
    putchar(NORTHWEST_WALL);
    for(i = main_box_upper_left_position.X + 1 ; i < main_box_lower_right_position.X ; i++) putchar(NORTH_WALL);
    putchar(NORTHEAST_WALL);

    putchar('\n');

    // Middle...
    for(i = main_box_upper_left_position.Y + 1 ; i < main_box_lower_right_position.Y ; i++)
    {
        putchar(WEST_WALL);
        for(j = main_box_upper_left_position.X + 1 ; j < main_box_lower_right_position.X ; j++) printf(" ");
        putchar(EAST_WALL);
        putchar('\n');
    }

    // Lower side...
    putchar(SOUTHWEST_WALL);
    for(i = main_box_upper_left_position.X + 1 ; i < main_box_lower_right_position.X ; i++) putchar(SOUTH_WALL);
    putchar(SOUTHEAST_WALL);

    SetCursorPosition(c);
}

// Return 'OBJECT' from cursor position specified by the 'where' parameter.
OBJECT GetObject(const COORD where)
{
    COORD c = CursorToCoordinate(where);

    return object[c.X][c.Y];
}

// Put 'object' to cursor position specified by the 'where' parameter.
void SetObject(const OBJECT object_to_put , const COORD where)
{
    COORD c = GetCursorPosition();
    COORD d = CursorToCoordinate(where);

    object[d.X][d.Y] = object_to_put;

    int o;
    if(object_to_put == NOTHING) o = SPACE_KEY;
    else if(object_to_put == RED_BLOCK)
    {
        o = BLOCK_GRAPHIC;
        SetConsoleTextAttribute(console_screen_buffer , FOREGROUND_RED | FOREGROUND_INTENSITY);
    }
    else if(object_to_put == BLUE_BLOCK)
    {
        o = BLOCK_GRAPHIC;
        SetConsoleTextAttribute(console_screen_buffer , FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    }
    SetCursorPosition(where);
    printf("%c" , o);

    SetConsoleTextAttribute(console_screen_buffer , FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);

    SetCursorPosition(c);
}

// Return 'OBJECT' from current cursor position.
OBJECT GetObject()
{
    return GetObject(GetCursorPosition());
}

// Put 'object' to current cursor position.
void SetObject(const OBJECT object_to_put)
{
    SetObject(object_to_put , GetCursorPosition());
}

// Clear inside the main area.
void ClearMainArea()
{
    COORD c;

    for(c.X = starting_position.X ; c.X <= ending_position.X ; c.X++) for(c.Y = starting_position.Y ; c.Y <= ending_position.Y ; c.Y++) if(GetObject(c) != NOTHING) SetObject(NOTHING , c);
}

// Set background colour to 'colour' of cursor position specified by 'coordinate'.
void SetBackground(COLOUR colour , COORD coordinate)
{
    COORD d , c = GetCursorPosition();
    OBJECT o;
    int g;

    SetCursorPosition(coordinate);

    o = GetObject();
    if(o == RED_BLOCK && colour == RED)
    {
        g = BLOCK_GRAPHIC;
        SetConsoleTextAttribute(console_screen_buffer , FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_RED);
    }
    else if(o == RED_BLOCK && colour == BLUE)
    {
        g = BLOCK_GRAPHIC;
        SetConsoleTextAttribute(console_screen_buffer , FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_BLUE);
    }
    else if(o == BLUE_BLOCK && colour == RED)
    {
        g = BLOCK_GRAPHIC;
        SetConsoleTextAttribute(console_screen_buffer , FOREGROUND_BLUE | FOREGROUND_INTENSITY | BACKGROUND_RED);
    }
    else if(o == BLUE_BLOCK && colour == BLUE)
    {
        g = BLOCK_GRAPHIC;
        SetConsoleTextAttribute(console_screen_buffer , FOREGROUND_BLUE | FOREGROUND_INTENSITY | BACKGROUND_BLUE);
    }
    else if(o == NOTHING && colour == RED)
    {
        g = SPACE_KEY;
        SetConsoleTextAttribute(console_screen_buffer , BACKGROUND_RED);
    }
    else if(o == NOTHING && colour == BLUE)
    {
        g = SPACE_KEY;
        SetConsoleTextAttribute(console_screen_buffer , BACKGROUND_BLUE);
    }
    printf("%c" , g);

    d = CursorToCoordinate(coordinate);
    current_background[d.X][d.Y] = colour;

    SetConsoleTextAttribute(console_screen_buffer , FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);

    SetCursorPosition(c);
}

// Set background colour to 'colour' of current cursor position.
void SetBackground(COLOUR colour)
{
    COORD c = GetCursorPosition();

    SetBackground(colour , c);
}

// Reset background colour to black.
void ResetBackground()
{
    COORD d = GetCursorPosition() , c;
    OBJECT o;
    int g;
    int rs = main_box_lower_right_position.X - main_box_upper_left_position.X - 1;
    int cs = main_box_lower_right_position.Y - main_box_upper_left_position.Y - 1;

    for(c.X = starting_position.X ; c.X <= ending_position.X ; c.X++) for(c.Y = starting_position.Y ; c.Y <= ending_position.Y ; c.Y++)
    {
        SetCursorPosition(c);
        o = GetObject();
        if(o == RED_BLOCK)
        {
            g = BLOCK_GRAPHIC;
            SetConsoleTextAttribute(console_screen_buffer , FOREGROUND_INTENSITY | FOREGROUND_RED);
        }
        else if(o == BLUE_BLOCK)
        {
            g = BLOCK_GRAPHIC;
            SetConsoleTextAttribute(console_screen_buffer , FOREGROUND_INTENSITY | FOREGROUND_BLUE);
        }
        else if(o == NOTHING)
        {
            g = SPACE_KEY;
            SetConsoleTextAttribute(console_screen_buffer , FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
        }
        printf("%c" , g);
    }

    for(int i = 0 ; i < cs ; i++) for(int j = 0 ; j < rs ; j++) current_background[i][j] = BLACK;

    SetConsoleTextAttribute(console_screen_buffer , FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);

    SetCursorPosition(d);
}

#endif
