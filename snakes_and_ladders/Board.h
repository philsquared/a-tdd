#include <map>
#include <cstdint>

#ifndef SNAKES_AND_LADDERS_BOARD_H
#define SNAKES_AND_LADDERS_BOARD_H

struct Portal {
    enum class Type { Snake, Ladder };
    Type type;
    uint32_t target;
};
struct Action {
    enum class Type { MoveTo, Win, NoMove };
    Type type;
    uint32_t target;
};

class Board {
    static const std::map<uint32_t, Portal> portals;
    static const uint32_t size = 100;

public:
    auto landOn( uint32_t square ) -> Action;
};

#endif //SNAKES_AND_LADDERS_BOARD_H
