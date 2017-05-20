
/*

This header file contains all symbolic constants, type definitions, function declarations and global variables which may or may not take their first values.

*/

#ifndef _CONST_H_
#define _CONST_H_

// Console window's row and column size by the factor of cursor size.
// Numbers are perfectly adjusted to 1024x768 screen resolution.
#define ROW_SIZE   125 // Size of 1 row...
#define COLUMN_SIZE 59 // Size of 1 column...
// ASCII codes for the margin of the main area...
#define EAST_WALL      179
#define WEST_WALL      179
#define NORTHEAST_WALL 191
#define SOUTHWEST_WALL 192
#define NORTH_WALL     196
#define SOUTH_WALL     196
#define SOUTHEAST_WALL 217
#define NORTHWEST_WALL 218
// ASCII code for escape key...
#define ESC_KEY 27
// Primary ASCII code for special keys (arrows or Home, Insert, Delete, End, Page Up, Page Down, etc.)...
#define SPECIAL_KEY 224
// Secondary ASCII codes for arrow keys...
#define UP_KEY     72
#define LEFT_KEY   75
#define RIGHT_KEY  77
#define DOWN_KEY   80
// Secondary ASCII code for delete key...
#define DELETE_KEY 83
// ASCII code for space key...
#define SPACE_KEY 32
// ASCII code for enter key...
#define ENTER_KEY 13
// ASCII code for block graphic...
#define BLOCK_GRAPHIC 43
// Infinity value
#define INFINITY 0x7FFFFFFF

// Enumerations...
enum DIRECTION {UP , LEFT , DOWN , RIGHT};
enum OBJECT    {NOTHING , WALL , RED_BLOCK , BLUE_BLOCK};
enum COLOUR    {RED , BLUE , BLACK};

// Structs..
struct CLASSIFIER
{
    double epsilon;
    double alpha;
    bool is_horizontal;
    int division_place;
    COLOUR left_up;
} *classifier;

// Constants...
HANDLE console_screen_buffer = GetStdHandle(STD_OUTPUT_HANDLE); // Handle to the standard output device.
HWND console_window_handle = GetConsoleWindow(); // Window handle used by the console associated with the calling process.
CONSOLE_SCREEN_BUFFER_INFO console_screen_buffer_info; // Contains cursor position.
const COORD main_box_upper_left_position = {0 , 1}; // Upper left wall position of the main box.
const COORD main_box_lower_right_position = {ROW_SIZE - 2 , COLUMN_SIZE - 3}; // Lower right wall position of the main box.
const COORD starting_position = {main_box_upper_left_position.X + 1 , main_box_upper_left_position.Y + 1}; // Upper left position of main box's interior.
const COORD ending_position = {main_box_lower_right_position.X - 1 , main_box_lower_right_position.Y - 1}; // Lower right position of main box's interior.
OBJECT **object; // Contains objects in main box. It has a matrix coordinates system.
COLOUR ***background; // Contains background colours of each step in algorithm.
COLOUR **current_background; // Contains current background colours.
double **weight; // Contains weights of blocks.
COORD menu_position = {0 , 0}; // Starting position of menu.
COORD info_position = {0 , COLUMN_SIZE - 2}; // Starting position of info text.
int block_infrequency_factor = 2; // Lower number means more blocks.
int step; // Number of steps.
const char *main_menu = "ARROWS = move , VB = put , D = delete , DELETE = reset all , R = random , S = save , L = load , ENTER = start , ESC = exit";
const char *main_info = "Put examples manually or generate a random status.";
int speed = 10; // steps per second.

// console.h functions...
void SetConsoleWindowSize(const int row_size , const int column_size);
// cursor.h functions...
void SetCursorPosition(const COORD where);
COORD GetCursorPosition();
void MoveCursor(const DIRECTION where);
bool IsCursorInsideMainBox();
bool IsCursorInsideMainBox(COORD coordinate);
bool IsCursorNearNorthWall(COORD coordinate);
bool IsCursorNearWestWall(COORD coordinate);
bool IsCursorNearSouthWall(COORD coordinate);
bool IsCursorNearEastWall(COORD coordinate);
bool IsCursorNearNorthWall();
bool IsCursorNearWestWall();
bool IsCursorNearSouthWall();
bool IsCursorNearEastWall();
// graphics.h functions...
void DrawMainArea();
OBJECT GetObject(const COORD where);
void SetObject(const OBJECT object_to_put , const COORD where);
OBJECT GetObject();
void SetObject(const OBJECT object_to_put);
void ClearMainArea();
void SetBackground(COLOUR colour , COORD coordinate);
void SetBackground(COLOUR colour);
// text.h functions..
void WriteText(const char *text , const COORD where);
void ClearText(const COORD where);
void WriteMenu(const char *text);
void ClearMenu();
void WriteInformation(const char *text);
void ClearInformation();
// misc.h functions..
void Swap(int *value1 , int *value2);
COORD CursorToCoordinate(const COORD cursor);
COORD CoordinateToCursor(const COORD coordinate);
// file.h functions..
void Log();
void Save();
void Load();
// algrithm.h functions..
void Random();
int Distance(COORD coordinate1 , COORD coordinate2);
void Start();
void Classify();

#endif
