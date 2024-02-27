#include <list>
#include <string>
#include <iostream>

using namespace std;

enum EBULLET
{
    EBULLET_BLANK,
    EBULLET_LIVE
};

class Item
{
    public:
    string name;

    virtual void Use()
    {
        std::cout << "Use";
    }
};


class Base_Player
{
    public:
    string name;
    int max_HP;
    int current_HP;
    list<Item> items;
};

class User : public Base_Player
{
    public:
};

class Dealer : public Base_Player
{
    public:
};

class Gun
{
    public:
    int damage;
    list<EBULLET> bullets;

    void Shoot(Base_Player* player,int damage);
};

void Gun::Shoot(Base_Player* player,int damage)
{
    player->current_HP -= damage;
    bullets.pop_back();
}

class cigarette : public Item
{
    public:
    void Use()
    {

    }


};

class Beer : Item
{

};

class Handcuffs : Item
{

};

class Knife : Item
{

};

class Magnifying_Glass : Item
{

};

int main()
{
    cigarette c;
    c.Use();
    return 0;
}