/*
    YoshiWin.cpp

    This file is part of yoshimi, which is free software: you can redistribute
    it and/or modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either version 2 of
    the License, or (at your option) any later version.

    yoshimi is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.   See the GNU General Public License (version 2 or
    later) for more details.

    You should have received a copy of the GNU General Public License along with
    yoshimi; if not, write to the Free Software Foundation, Inc., 51 Franklin
    Street, Fifth Floor, Boston, MA  02110-1301, USA.

*/

#include "YoshiWin.h"
#include "Misc/NumericFuncs.h"

#include <iostream>

#include <FL/fl_draw.H>
#include <FL/x.H>

using func::limit;

YoshiWin::YoshiWin(int x,int y, int w, int h, const char *label) : Fl_Double_Window(x,y,w,h,label)
{
    ;
}


YoshiWin::~YoshiWin()
{
    ;
}


void YoshiWin::resize(int x, int y, int w, int h)
{
  Fl_Double_Window::resize(x, y, w, h);
  std::cout << "Resized: x" << x << "  y" << y << "  w " << w << "  h " << h << std::endl;
}
