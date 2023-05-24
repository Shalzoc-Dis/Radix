#pragma once
#include "vex.h"

//#define DEBUG
#define RELEASE

// Toggle between holonomic xdrive or mecanum drive
#if 1
# define RX_MECANUM
#else
# define RX_XDRIVE
#endif

// Debug stuff
#ifdef RELEASE
# define DEBUG_ONLY(x) {;}
#else
# define DEBUG_ONLY(x) {x;}
#endif