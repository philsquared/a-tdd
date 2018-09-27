// ****
// **** Code snippets to save time - this file is not part of the project - do not add it!
// ****


// Helper lambda for verifying each turn in a progressing game


auto verify = [&]( uint32_t dieRoll, Player::Colour col, Action action ) {
        face = dieRoll;
        auto turnInfo = game.take_turn();
        CHECK( turnInfo.player.colour == col );
        CHECK( turnInfo.action == action );
    };

