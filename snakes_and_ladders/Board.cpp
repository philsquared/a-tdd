//
// Created by Phil Nash on 29/09/2018.
//

#include "Board.h"

const std::map<uint32_t, Portal> Board::portals =
        {
                {2,  {Portal::Type::Ladder, 38}},
                {4,  {Portal::Type::Ladder, 14}},
                {8,  {Portal::Type::Ladder, 31}},
                {21, {Portal::Type::Ladder, 42}},
                {28, {Portal::Type::Ladder, 84}},
                {36, {Portal::Type::Ladder, 44}},
                {47, {Portal::Type::Snake,  26}},
                {49, {Portal::Type::Snake,  11}},
                {51, {Portal::Type::Ladder, 67}},
                {56, {Portal::Type::Snake,  53}},
                {62, {Portal::Type::Snake,  18}},
                {64, {Portal::Type::Snake,  60}},
                {71, {Portal::Type::Ladder, 91}},
                {80, {Portal::Type::Ladder, 100}},
                {87, {Portal::Type::Snake,  24}},
                {93, {Portal::Type::Snake,  73}},
                {95, {Portal::Type::Snake,  75}},
                {98, {Portal::Type::Snake,  78}}
        };

auto Board::landOn( uint32_t square ) -> Action {

    auto finalSquare = [&] {
        auto it = portals.find(square);
        if (it != portals.end())
            return it->second.target;
        return square;
    }();

    if( finalSquare == size )
        return { Action::Type::Win, 0 };
    else if( finalSquare > size )
        return { Action::Type::NoMove, 0 };
    else
        return {Action::Type::MoveTo, finalSquare };
}