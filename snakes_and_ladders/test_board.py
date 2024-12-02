from dataclasses import dataclass
from enum import Enum


@dataclass
class Portal:
    class Type(Enum):
        Snake = 1
        Ladder = 2

    type: Type
    target: int

class Action:
    @dataclass
    class MoveTo:
        target: int

    @dataclass
    class Win:
        pass

    @dataclass
    class NoMove:
        pass


class Board:
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

    def land_on(self, square: int) -> Action.MoveTo | Action.Win | Action.NoMove:
        if portal := self.portals.get(square):
            final_square = portal.target
        else:
            final_square = square

        if final_square == 100:
            return Action.Win()
        elif final_square > 100:
            return Action.NoMove()
        return Action.MoveTo(final_square)



def test_board():
    board = Board()
    assert board.land_on(1) == Action.MoveTo(1)
    assert board.land_on(3).target == 3

    assert board.land_on(2).target == 38
    assert board.land_on(47).target == 26  # confidence test

    assert board.land_on(100) == Action.Win()

    assert board.land_on(101) == Action.NoMove()

    assert board.land_on(102) == Action.NoMove() # confidence test

    assert board.land_on(80) == Action.Win()
