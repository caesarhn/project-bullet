class Character {
private:
    char *id;
    int atk;
    int hp;
    float loc[2];
    float speed;

public:
    std::string texture;

    Character (char *id, int atk, int hp, float locx, float locy, float speed);
    int damaged(int damage);
    int regeneration(int regen);
    float* getLocation();
    void moveX(float direction);
};