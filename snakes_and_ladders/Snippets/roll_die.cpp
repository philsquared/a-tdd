// ****
// **** Code snippets to save time - this file is not part of the project - do not add it!
// ****

// a not-great, but self-contained example implementation for modelling a random die roll
// - will need an #include <random>


uint32_t roll_die() {
    static std::mt19937 rng;
    static bool initialised = false;
    if( !initialised ) {
        rng.seed( std::random_device()() );
        initialised = true;
    }
    std::uniform_int_distribution<> rnd( 1, 6 );
    return rnd(rng);
}