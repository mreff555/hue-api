#include "console.h"
#include <clocale>

#include <cstdlib>
#include <clocale>
#include <iostream>

#include <ncpp/NotCurses.hh>
#include <ncpp/Menu.hh>
#include <ncpp/Pile.hh>
#include <ncpp/Plane.hh>
#include <ncpp/Reel.hh>
#include <ncpp/MultiSelector.hh>
#include <ncpp/Selector.hh>
#include <ncpp/Visual.hh>
#include <ncpp/Direct.hh>
#include <ncpp/Plot.hh>
#include <ncpp/FDPlane.hh>
#include <ncpp/Subproc.hh>
#include <ncpp/Progbar.hh>

using namespace ncpp;

Console::Console(){}

void Console::runEventLoop(bool &terminate)
{
    if(setlocale(LC_ALL, "") == nullptr)
    {
        terminate = true;
    }

    notcurses_options ncopts{};
    auto nc = notcurses_init(&ncopts, NULL);
    if(nc == nullptr)
    {
        terminate = true;
    }

    while(!terminate)
    {

    }
    notcurses_stop(nc);
}