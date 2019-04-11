// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

// add headers that you want to pre-compile hereW
#include <iostream>
#include <vector>
#include <cstdlib>
#include <conio.h>
#include <algorithm>
#include <process.h>
#include <Windows.h>
#include <string>
#include "curses.h"

#include "Word.h"
#include "Player.h"
#include "Committer.h"

#ifdef _MSC_VER
#include <winsqlite/winsqlite3.h>
#else
#include <sqlite3.h>
#endif // 

#endif //PCH_H
