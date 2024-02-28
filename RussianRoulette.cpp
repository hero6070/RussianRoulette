#include <vector>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

const int Max_ItemCount = 6;
int Round_Count = 3;

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
    vector<Item> items;

    void Item_Setup(vector<Item> _Items,int _Item_Count);
    void Show_Items();

};

void Base_Player::Item_Setup(vector<Item> _Items,int _Item_Count)
{
    srand(time(NULL));
    for(int i = 0; i < _Item_Count; i++)
    {
        items.push_back(_Items[rand()%_Items.size()]);
        if(items.size() > Max_ItemCount)
        {
            return;
        }
    }
}

void Base_Player::Show_Items()
{
    cout << "아이템 : ";
    for(int i = 0; i < items.size(); i++)
    {
        cout << items[i].name;
        if(items.size()-1 != i)
        {
            cout << ", ";
        }
        else
        {
            cout << endl;
        }
    }
}
    



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
    vector<EBULLET> bullets;
    int blank;
    int live;

    void Shoot(Base_Player* player,int damage);
    void Bullets_Setup();
    void PrintBullets();
};

void Gun::Shoot(Base_Player* player,int damage)
{
    player->current_HP -= damage;
    bullets.pop_back();
    if(bullets.empty())
    {
        Bullets_Setup();
    }
}

void Gun::Bullets_Setup()
{
    blank = 0;
    live = 0;
    srand(time(NULL));
    int k = 0;
    for(int i = 0; i < (rand() % 7) + 1; i++)
    {
        if(rand() % 2)
        {
            bullets.push_back(EBULLET_BLANK);
            blank++;
        }
        else
        {
            bullets.push_back(EBULLET_LIVE);
            live++;
        }
    }
    PrintBullets();
}

void Gun::PrintBullets()
{
    cout << "실탄 : " << live << ", 공포탄 : " << blank << endl;
}

class cigarette : public Item
{
    public:
    void Use()
    {

    }
};

class Beer : public Item
{

};

class Handcuffs : public Item
{

};

class Knife : public Item
{

};

class Magnifying_Glass : public Item
{

};

int main()
{
    Gun gun;
    User user;
    user.current_HP = 5;
    int i = 0;
    cin >> i;
    cout << i;

    for(int i = 0; i < Round_Count; i++)
    {
        gun.Bullets_Setup();
        char c = ' ';
        cin >> c;
        if(c == 's')
        {
            gun.Shoot(&user,1);
            gun.PrintBullets();
        }
            
    }
    return 0;
}