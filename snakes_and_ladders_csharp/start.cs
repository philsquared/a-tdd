struct Portal {
    public enum Type { Snake, Ladder };
    public Type type;
    public int target;

    public Portal(Type type, int target)
    {
        this.type = type;
        this.target = target;
    }
};

public class Board
{
    Dictionary<int, Portal> portals = new Dictionary<int, Portal>
        {
            { 2, new Portal( Portal.Type.Ladder, 38 ) },
            { 4, new Portal( Portal.Type.Ladder, 14 ) },
            { 8, new Portal( Portal.Type.Ladder, 31 ) },
            { 21, new Portal( Portal.Type.Ladder, 42 ) },
            { 28, new Portal( Portal.Type.Ladder, 84 ) },
            { 36, new Portal( Portal.Type.Ladder, 44 ) },
            { 47, new Portal( Portal.Type.Snake, 26 ) },
            { 49, new Portal( Portal.Type.Snake, 11 ) },
            { 51, new Portal( Portal.Type.Ladder, 67 ) },
            { 56, new Portal( Portal.Type.Snake, 53 ) },
            { 62, new Portal( Portal.Type.Snake, 18 ) },
            { 64, new Portal( Portal.Type.Snake, 60 ) },
            { 71, new Portal( Portal.Type.Ladder, 91 ) },
            { 80, new Portal( Portal.Type.Ladder, 100 ) },
            { 87, new Portal( Portal.Type.Snake, 24 ) },
            { 93, new Portal( Portal.Type.Snake, 73 ) },
            { 95, new Portal( Portal.Type.Snake, 75 ) },
            { 98, new Portal( Portal.Type.Snake, 78 ) }
        };   
}