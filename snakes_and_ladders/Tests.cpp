#include <random>
#include "Board.h"

#include "catch.hpp"



bool operator==(const Action &lhs, const Action &rhs) {
    return std::tie(lhs.type, lhs.target) == std::tie(rhs.type, rhs.target);
}

std::ostream& operator <<( std::ostream& os, Action::Type type ) {
    switch( type ) {
        case Action::Type::MoveTo: return os << "Move";
        case Action::Type::Win: return os << "Win";
        case Action::Type::NoMove: return os << "NoMove";
        default:
            throw std::logic_error( "{unknown enum value: " + std::to_string( (int)type ) + "}" );
    }
}

std::ostream& operator <<( std::ostream& os, Action action ) {
    os << "Action{ " << action.type;
    if( action.type == Action::Type::MoveTo )
        os << ", " << action.target;
    return os << " }";
}
enum class Colour { Red, Blue, Green, Yellow };

struct Player {
    Colour colour;
    uint32_t square;
};
struct TurnInfo {
    Player player;
    Action action;
};

auto rollDie() -> uint32_t {
    static std::mt19937 rng;
    static bool initialised = false;
    if( !initialised ) {
        rng.seed( std::random_device()() );
        initialised = true;
    }
    std::uniform_int_distribution<> rnd( 1, 6 );
    return rnd(rng);
}

class Game {
    uint32_t m_currentPlayer = 0;
    std::vector<Player> m_players;
    Board m_board;
    std::function<uint32_t()> m_die;
public:
    Game( std::initializer_list<Colour> colours, std::function<uint32_t()> die=rollDie )
    : m_die( die ) {
        std::transform( colours.begin(), colours.end(),
                std::back_inserter( m_players ),
                []( Colour colour ){ return Player{ colour, 1 }; } );
    }
    uint32_t currentPlayer() { return m_currentPlayer; }

    auto takeTurn() -> TurnInfo {
        const auto player = m_players[m_currentPlayer];
        if( ++m_currentPlayer == m_players.size() )
            m_currentPlayer = 0;
        auto action = m_board.landOn(player.square+m_die());
        return TurnInfo{player, action};
    }
};

TEST_CASE("Board tracks where you land") {

    Board board;

    REQUIRE( board.landOn( 1 ) == Action{ Action::Type::MoveTo, 1 } );
    REQUIRE( board.landOn( 2 ) == Action{ Action::Type::MoveTo, 38 } );
    REQUIRE( board.landOn( 3 ) == Action{ Action::Type::MoveTo, 3 } );
    REQUIRE( board.landOn( 47 ) == Action{ Action::Type::MoveTo, 26 } );
    REQUIRE( board.landOn( 100 ).type == Action::Type::Win );
    REQUIRE( board.landOn( 80 ).type == Action::Type::Win );
    REQUIRE( board.landOn( 101 ).type == Action::Type::NoMove );
}

SCENARIO("Players take turns") {

    GIVEN( "A game object with two players" ) {
        Game game({Colour::Red, Colour::Blue});

        THEN("The player is 0") {
            REQUIRE(game.currentPlayer() == 0);
            AND_WHEN("we take the first turn") {
                game.takeTurn();
                THEN( "The player becomes player 1 and something really verbose happens - no even more verbose than that") {
                    REQUIRE(game.currentPlayer() == 1);
                    AND_WHEN("we take another turn") {
                        game.takeTurn();
                        THEN("We go back to player 0") {
                            REQUIRE(game.currentPlayer() == 0);
                        }
                    }
                }
            }
        }
    }
}
TEST_CASE( "Game"){
    u_int32_t face = 0;
    Game game( { Colour::Red, Colour::Blue }, [&face]{
        return face;
    } );

    auto verify = [&]( uint32_t dieRoll, Colour col, Action action ) {
        face = dieRoll;
        auto turnInfo = game.takeTurn();
        CHECK( turnInfo.player.colour == col );
        CHECK( turnInfo.action == action );
    };

    verify( 1, Colour::Red, { Action::Type::MoveTo, 38 } );
    verify( 2, Colour::Blue, { Action::Type::MoveTo, 3 } );

}