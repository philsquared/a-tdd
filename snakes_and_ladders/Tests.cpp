#include <map>
#include <cstdint>
#include <ostream>

struct Portal {
    enum class Type { Snake, Ladder };
    Type type;
    uint32_t target;
};
struct Action {
    enum class Type { MoveTo, Win };
    Type type;
    uint32_t target;

    bool operator==( Action const& rhs ) const {
        return type == rhs.type &&
               target == rhs.target;
    }

    bool operator!=( Action const& rhs ) const {
        return !(rhs == *this);
    }

    friend std::ostream& operator<<( std::ostream& os, Action const& action ) {
        os << "type: " << (int)action.type << " target: " << action.target;
        return os;
    }
};


class Board {
    static std::map<uint32_t, Portal> portals;
public:
    Action landOn( uint32_t square ) const {
        auto it = portals.find(square);
        if( it != portals.end() )
            return { Action::Type::MoveTo, it->second.target };
        return { Action::Type::MoveTo, square };
    }
};

#include "catch.hpp"

TEST_CASE() {

    Board board;
    REQUIRE( board.landOn( 1 ) == Action{ Action::Type::MoveTo, 1 } );
    REQUIRE( board.landOn( 3 ).target == 3 );
    REQUIRE( board.landOn( 2 ).target == 38 );
    REQUIRE( board.landOn( 47 ).target == 26 );
    REQUIRE( board.landOn( 100 ).type == Action::Type::Win );
}

std::map<uint32_t, Portal> Board::portals =
    {
            { 2, { Portal::Type::Ladder, 38 } },
            { 4, { Portal::Type::Ladder, 14 } },
            { 8, { Portal::Type::Ladder, 31 } },
            { 21, { Portal::Type::Ladder, 42 } },
            { 28, { Portal::Type::Ladder, 84 } },
            { 36, { Portal::Type::Ladder, 44 } },
            { 47, { Portal::Type::Snake, 26 } },
            { 49, { Portal::Type::Snake, 11 } },
            { 51, { Portal::Type::Ladder, 67 } },
            { 56, { Portal::Type::Snake, 53 } },
            { 62, { Portal::Type::Snake, 18 } },
            { 64, { Portal::Type::Snake, 60 } },
            { 71, { Portal::Type::Ladder, 91 } },
            { 80, { Portal::Type::Ladder, 100 } },
            { 87, { Portal::Type::Snake, 24 } },
            { 93, { Portal::Type::Snake, 73 } },
            { 95, { Portal::Type::Snake, 75 } },
            { 98, { Portal::Type::Snake, 78 } }
    };