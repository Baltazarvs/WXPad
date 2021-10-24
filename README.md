## What is this?

This is a simple program created in C++ with wxWidgets.
It demonstrates some functions that can be used with wxWidgets through small notepad.

## How to build this?

There is two known ways how to compile this manually without tools.

## **CMake**

Create a subdirectory inside file where CMakeLists.txt is located. I would create a dir named **build**

```bash
mkdir build
cd build
cmake -G "Unix Makefiles" ..
make
```

And after you finished, just run wxpad like **./wxpad**.


## **G++**

```bash
cd source
g++ wxpad.cpp MainApp.cpp AppFrame.cpp `wx-config --cxxflags --libs` -o WXPad
```

After this, just run like ./WXPad

- **-o WXPad** is optional. Put whatever you want, but it must match with ./THIS_TEXT

There is no many ways I can provide for teaching you how to build this. If first one fails, second will not for sure.

Created 2021 Baltazarus.
