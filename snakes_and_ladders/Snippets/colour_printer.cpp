// ****
// **** Code snippets to save time - this file is not part of the project - do not add it!
// ****

// helper for writing the Colour enum to a stream (let's Catch print)
// - note this could also be done with a specialisation of Catch::StringMaker<Colour>)

std::ostream& operator <<( std::ostream& os, Colour colour ) {
    switch( colour ) {
        case Colour::Red: return os << "Red";
        case Colour::Blue: return os << "Blue";
        case Colour::Green: return os << "Green";
        case Colour::Yellow: return os << "Yellow";
        default:
            throw std::logic_error( "{unknown enum value: " + std::to_string( (int)colour ) + "}" );
    }
}
