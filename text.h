
/*

This header file contains functions for text operations.

*/

#ifndef _TEXT_H_
#define _TEXT_H_

// Write text contained by parameter 'text' to coordinates specified by parameter 'where'.
void WriteText(const char *text , const COORD where)
{
    COORD c = GetCursorPosition();

    SetCursorPosition(where);
    ClearText(where);
    puts(text);

    SetCursorPosition(c);
}

// Clear text in coordinates specified by the parameter.
// This function clear only one row.
void ClearText(const COORD where)
{
    int i;
    COORD c = GetCursorPosition();

    SetCursorPosition(where);
    for(i = where.X ; i < ROW_SIZE ; i++) printf(" ");

    SetCursorPosition(c);
}

// Write text to menu area.
void WriteMenu(const char *text)
{
    WriteText(text , menu_position);
}

// Clear menu.
void ClearMenu()
{
    ClearText(menu_position);
}

// Write text to information area.
void WriteInformation(const char *text)
{
    WriteText(text , info_position);
}

// Clear information area.
void ClearInformation()
{
    ClearText(info_position);
}

#endif
