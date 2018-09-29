// ****
// **** Code snippets to save time - this file is not part of the project - do not add it!
// ****

// helper for writing Action and the Action::Type enum to a stream (let's Catch print)
// - note this could also be done with a specialisation of, e.g., Catch::StringMaker<Action::Type>)

std::ostream& operator <<( std::ostream& os, Action::Type type ) {
    switch( type ) {
        case Action::Type::Move: return os << "Move";
        case Action::Type::Win: return os << "Win";
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
