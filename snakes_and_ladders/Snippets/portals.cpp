// ****
// **** Code snippets to save time - this file is not part of the project - do not add it!
// ****

// Portals map - starting point
// This will need an include for map and, technically, for uint32_t (although it may not be needed straight away)


struct Portal {
    enum class Type { Snake, Ladder };
    Type type;
    uint32_t target;
};

std::map<uint32_t, Portal> portals =
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
