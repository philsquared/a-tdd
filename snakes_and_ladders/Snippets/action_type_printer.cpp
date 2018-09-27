// ****
// **** Code snippets to save time - this file is not part of the project - do not add it!
// ****

// helper for writing the Action::Type enum to a stream (let's Catch print)
// - note this could also be done with a specialisation of Catch::StringMaker<Action::Type>)

std::ostream& operator <<( std::ostream& os, Action::Type type ) {
    switch( type ) {
        case Action::Type::Move: return os << "Move";
        case Action::Type::Win: return os << "Win";
        default:
            os << "{unknown enum value: " << (int)type << "}";
            assert(false);
    }
}
