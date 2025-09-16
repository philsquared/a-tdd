1. If `buy()` is called for an already owned property, throw an exception (remember to write the test(s) first)
2. Add a `Dice` class with a `roll()` method (use die_roll.h). Remember that "dice" is plural, and in Monopoly there are two. Remember to drive it through tests.
   * How can you test the functionality of Dice?
4. Can you stop our code (currently in main.cpp) from depending on `<random>`?
5. Now look at `take_turn()`. How can we implement this? What is going to be needed?
   * Don't do it all at once - break it down
   * Drive each step from tests
   * Note that there is a basic `TurnInfo` type already written
6. How can we control the non-determinism of the dice roll within `take_turn()`?
7. How will we handle the case that a property is owned by the player that lands on it?