#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

enum SquareConstants {
    Go = 0,
    MediterraneanAvenue = 1,
    CommunityChest1 = 2,
    IncomeTax = 4,
    ChanceChest1 = 2,
    JustVisiting = 10,
    FreeParking = 20,
    GotoJail = 30,
    LuxuryTax = 38
};

enum class Action {
    DoNothing,
    DrawCommunityChestCard,
    DrawChanceCard,
    GotoJail,
    PayTax,
    BuyOrAuction,
    PayRent
};
enum class Pieces {
    TopHat,
    Dog,
    Iron,
    Boot,
    RaceCar,
    Thimble,
    Horse,
    Wheelbarrow
};

struct Player {
    Pieces piece;
    int position = 0;
};

struct Square {
    virtual ~Square() = default;
    virtual Action get_action() const = 0;
};
class CommunityChestSquare : public Square {
    Action get_action() const override {
        return Action::DrawCommunityChestCard;
    }
};
class GotoJailSquare : public Square {
    Action get_action() const override {
        return Action::GotoJail;
    }
};

struct TurnInfo {
    Player& player;
    Action action;
};

class Game {
    std::vector<Player> players;
    std::vector<std::unique_ptr<Square>> squares {40};
    std::set<int> available_properties = { MediterraneanAvenue };
    std::set<int> owned_properties;

public:
    Game( std::initializer_list<Pieces> player_pieces = {} ) {
        std::transform(player_pieces.begin(), player_pieces.end(), std::back_inserter(players),
            [](Pieces piece){ return Player{ piece }; } );
        squares[CommunityChest1] = std::make_unique<CommunityChestSquare>();
        squares[GotoJail] = std::make_unique<GotoJailSquare>();
    }
    Action land_on(int square) const {
        if(Square const* sq = squares[square].get()) {
            return sq->get_action();
        }
        if( available_properties.find(square) != available_properties.end() ) {
            return Action::BuyOrAuction;
        }
        if( owned_properties.find(square) != owned_properties.end() ) {
            return Action::PayRent;
        }
        return Action::DoNothing;
    }
    void buy(int square) {
        if( available_properties.find(square) != available_properties.end() ) {
            available_properties.erase(square);
            owned_properties.insert(square);
        }
    }

    auto take_turn() {
        // get current player
        // roll dice
        // move player
        // call land_on for new square
        // adjust action?
        // return TurnInfo
    }
};

TEST(MonopolyTests, PlayerTakesATurn) {
    Game game;
    EXPECT_EQ( game.land_on(Go), Action::DoNothing );
    EXPECT_EQ( game.land_on(JustVisiting), Action::DoNothing );
    EXPECT_EQ( game.land_on(FreeParking), Action::DoNothing );
    EXPECT_EQ( game.land_on(GotoJail), Action::GotoJail );
    EXPECT_EQ( game.land_on(CommunityChest1), Action::DrawCommunityChestCard );

    EXPECT_EQ( game.land_on(MediterraneanAvenue), Action::BuyOrAuction );
}

TEST(MonopolyTests, PlayerBuysAProperty) {
    Game game;
    EXPECT_EQ( game.land_on(MediterraneanAvenue), Action::BuyOrAuction );

    game.buy(MediterraneanAvenue);

    EXPECT_EQ( game.land_on(MediterraneanAvenue), Action::PayRent );
}
