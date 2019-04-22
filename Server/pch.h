// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.
#define _SILENCE_CXX17_RESULT_OF_DEPRECATION_WARNING
#ifndef PCH_H
#define PCH_H

// add headers that you want to pre-compile here
#include <uvw.hpp>
#include <string>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <list>
#include <iostream>
#include <mysql+++.h>
#include "user.h"
#include "md5.h"
#endif //PCH_H
