# Word Clear
C++ homework, a word clear game.

## Build
### Server
To build server, you need `cmake` and a compiler which support C++17. For compiler support, you can see [here](https://en.cppreference.com/w/cpp/compiler_support)
Also you need to install [libuv](libuv.org) and [UVW](https://github.com/skypjack/uvw), and then add them to your include path.
To build:
```
cd Server
cmake .
make -j4
```
Then you can run with:
```
bin/wordGamed -p [PORT]
```
The template of the MySQL database is `word_clear_game.sql`.
### Client
To build client, you need `.NET Framework 4.0+`. Before building, remember to install [Json.NET](https://www.newtonsoft.com/json) first.
To build:
```
msbuild Word_Clear.sln
```
