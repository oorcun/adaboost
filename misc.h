
/*

This header file contains miscellaneous functions.

*/

#ifndef _MISC_H_
#define _MISC_H_

// Change cursor relative to window to coordinates relative to main area.
COORD CursorToCoordinate(const COORD cursor)
{
    COORD c;

    c.Y = cursor.X - starting_position.X;
    c.X = cursor.Y - starting_position.Y;

    return c;
}

// Change coordinates relative to main area to cursor relative to window.
COORD CoordinateToCursor(const COORD coordinate)
{
    COORD c;

    c.Y = coordinate.X + starting_position.Y;
    c.X = coordinate.Y + starting_position.X;

    return c;
}

// Swap two values pointed by the parameters.
void Swap(int *value1 , int *value2)
{
    *value2 = (*value1 + *value2) - (*value1 = *value2);
}

#endif
