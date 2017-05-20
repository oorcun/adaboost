
/*

This header file contains functions to modify console window.

*/

#ifndef _CONSOLE_H_
#define _CONSOLE_H_

// Set console window size with respect to the row and column parameters of the function.
// These parameters' units are console cursor position, not pixels.
void SetConsoleWindowSize(const int row_size , const int column_size)
{
    const COORD coordinates = {row_size , column_size};

    const SMALL_RECT rectangle = {0 , 0 , coordinates.X , coordinates.Y};

    SetConsoleScreenBufferSize(console_screen_buffer , coordinates);

    SetConsoleWindowInfo(console_screen_buffer , true , &rectangle);

    ShowWindow(console_window_handle , SW_SHOWMAXIMIZED);
}

#endif
