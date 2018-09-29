// ****
// **** Code snippets to save time - this file is not part of the project - do not add it!
// ****


// Demo game loop

for( bool stillPlaying = true; stillPlaying;){
    auto turn = game.take_turn();

    std::cout << turn.player.colour << " ";
    switch( turn.action.type ) {
        case Action::Type::MoveTo:
            std::cout << "moves to " << turn.action.target << "\n";
            break;
        case Action::Type::NoMove:
            std::cout << "misses go\n";
            break;
        case Action::Type::Win:
            std::cout << "wins!\n";
            stillPlaying = false;
            break;
    }
}
