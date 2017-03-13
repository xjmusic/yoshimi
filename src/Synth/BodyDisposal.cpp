/*
    BodyDisposal.cpp

    Copyright 2010, Alan Calvert

    This file is part of yoshimi, which is free software: you can
    redistribute it and/or modify it under the terms of the GNU General
    Public License as published by the Free Software Foundation, either
    version 2 of the License, or (at your option) any later version.

    yoshimi is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with yoshimi.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Synth/BodyDisposal.h"

void BodyDisposal::addBody(Carcass *body)
{
    // usually during Part::ComputePartSmps loop
    if (body != NULL)
        corpsePile[ (inFront ? 0 : 1) ].push_back(body);
}


void BodyDisposal::disposeBodies(void)
{
    // usually during mainGuiThread loop
    std::list<Carcass*> *corpses = &corpsePile[ (inFront ? 1 : 0) ];
    for (int x = corpses->size(); x > 0; --x)
    {
        delete corpses->front();
        corpses->pop_front();
    }

    // swap back and front corpsePiles: do not confuse with back/front of list
    // the boolean answers the question, 'where do new bodies *go* right now?'
    // since the adding or disposing always derives from this atomic variable,
    // it makes the change effectively simultaneous across N threads/cores/etc
    // (see "High-Performance and Scalable Updates - The Issaquah Challenge")
    // so we get atomic double buffering. Thanks Paul McKenney for the clues
    // "corpses in piles? yeah i'm just following suit" --dbtx (2017-03-12)
    inFront = !inFront;
}
