from dataclasses import dataclass
from enum import Enum


@dataclass
class Portal:
    class Type(Enum):
        Snake = 1
        Ladder = 2

    type: Type
    target: int


portals = {
    2: Portal(Portal.Type.Ladder, 38),
    4: Portal(Portal.Type.Ladder, 14),
    8: Portal(Portal.Type.Ladder, 31),
    21: Portal(Portal.Type.Ladder, 42),
    28: Portal(Portal.Type.Ladder, 84),
    36: Portal(Portal.Type.Ladder, 44),
    47: Portal(Portal.Type.Snake, 26),
    49: Portal(Portal.Type.Snake, 11),
    51: Portal(Portal.Type.Ladder, 67),
    56: Portal(Portal.Type.Snake, 53),
    62: Portal(Portal.Type.Snake, 18),
    64: Portal(Portal.Type.Snake, 60),
    71: Portal(Portal.Type.Ladder, 91),
    80: Portal(Portal.Type.Ladder, 100),
    87: Portal(Portal.Type.Snake, 24),
    93: Portal(Portal.Type.Snake, 73),
    95: Portal(Portal.Type.Snake, 75),
    98: Portal(Portal.Type.Snake, 78)
}

