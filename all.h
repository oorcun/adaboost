
/*

This header file combines all headers together.

*/

#ifndef _ALL_H_
#define _ALL_H_

// Target windows XP operating system. This is required for GetConsoleWindow API.
#define _WIN32_WINNT 0x0500

// Main headers...
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <math.h>
#include <conio.h>
#include <windows.h>

// Custom headers...
#include "constant.h" // Must be included first.
#include "cursor.h" // Some headers depends on this.
#include "misc.h"
#include "graphics.h"
#include "console.h"
#include "text.h"
#include "file.h"
#include "algrithm.h"

#endif
