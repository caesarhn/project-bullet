#include <char/char.h>

class Level
{
private:
    std::vector<Character> Characters;
public:
    void addChar(Character new_character);
};


void Level::addChar(Character new_character){
    Characters.insert(new_character);
}
