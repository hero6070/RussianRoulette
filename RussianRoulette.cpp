#include <vector>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <ctime>

using namespace std;

const int Max_ItemCount = 6;

enum EBULLET
{
    EBULLET_BLANK,
    EBULLET_LIVE
};

enum ETURN
{
    ETURN_USER,
    ETURN_DEALER,
};

void wait(int second)
{
    clock_t endWait = clock() + second * CLOCKS_PER_SEC;
    while(clock()<endWait);
}

class Item
{
    public:
    string name;

    virtual void Use() {};
};

class Base_Player
{
    public:
    int max_HP;
    int current_HP;
    vector<Item> items;

    virtual void Setup();

    void Item_Setup();
    void Show_Items();

};

void Base_Player::Setup()
{
    max_HP = 5;
    current_HP = max_HP;
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
    bool addDamage;

    void Shoot(Base_Player* player);
    void Reroad();
    void PrintBullets();
};

class GameManager
{
    public:
    static Gun gun;
    static User user;
    static Dealer dealer;
    static ETURN turn;
    static vector<Item> all_item;
    static bool turnLock;

    void Setup();
};

void Base_Player::Item_Setup()
{
    srand(time(NULL));
    for(int i = 0; i < 2; i++)
    {
        items.push_back(GameManager::all_item[rand()%GameManager::all_item.size()]);
        if(items.size() > Max_ItemCount)
        {
            return;
        }
    }
    Show_Items();
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

void Gun::Shoot(Base_Player* player)
{
    damage = 1;
    if(addDamage)
        damage = 2;
        addDamage = false;
    player->current_HP -= damage;
    if(bullets.back() == EBULLET_BLANK)
    {
        cout << "공포탄 발사!!!";
    }
    else
    {
        cout << "실탄 발사!!!";
    }
    bullets.pop_back();
    if(bullets.empty())
    {
        cout << "총알을 모두 소비했습니다" << endl;
        Reroad();
    }
    damage = 1;
}

void Gun::Reroad()
{
    blank = 0;
    live = 0;
    srand(time(NULL));
    bullets.clear();
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
    cout << "재장전 중.." << endl;
    wait(1);
    PrintBullets();
    wait(1);
    cout << "아이템을 획득합니다" << endl;
    GameManager::user.Item_Setup();
    GameManager::dealer.Item_Setup();
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
        cout << "담배 사용" << endl;
        Base_Player* player;
        if(GameManager::turn == ETURN_USER)
            player = &GameManager::user;
        else
            player = &GameManager::dealer;
        if(player->current_HP >= player->max_HP)
            return;
        player->current_HP++;
    }
};

class Beer : public Item
{
    public:
    void Use()
    {
        cout << "맥주 사용" << endl; 
        if(GameManager::gun.bullets.back() == EBULLET_BLANK)
            cout << "공포탄 소비" << endl; 
        else
            cout << "실탄 소비" << endl;
        GameManager::gun.bullets.pop_back();
        if(GameManager::gun.bullets.empty())
            GameManager::gun.Reroad();
    }
};

class Handcuffs : public Item
{
    public:
    void Use()
    {
        if(GameManager::turnLock)
            cout << "수갑을 이미 사용했습니다" << endl;
            return;
        cout << "수갑 사용" << endl;
        GameManager::turnLock = true;
    }
};

class Knife : public Item
{
    void Use()
    {
        cout << "칼 사용" << endl;
        GameManager::gun.addDamage = true;
    }

};

class Magnifying_Glass : public Item
{
    public:
    void Use()
    {
        cout << "돋보기 사용" << endl;
        cout << "다음 총알 : ";
        if(GameManager::gun.bullets.back() == EBULLET_BLANK)
            cout << "공포탄" << endl;
        else
            cout << "실탄" << endl;
    }
};

void GameManager::Setup()
{
    cigarette _Cigarette;
    _Cigarette.name = "담배";
    Beer _Beer;
    _Beer.name = "맥주";
    Handcuffs _Handcuffs;
    _Handcuffs.name = "수갑";
    Knife _Knife;
    _Knife.name = "나이프";
    Magnifying_Glass _Magnifying_Glass;
    _Magnifying_Glass.name = "돋보기";
    all_item.push_back(_Cigarette);
    all_item.push_back(_Beer);
    all_item.push_back(_Handcuffs);
    all_item.push_back(_Knife);
    all_item.push_back(_Magnifying_Glass);
    turnLock = false;
    gun.addDamage = false;
    user.Setup();
    dealer.Setup();
}

int main()
{
    cout << "시작하려면 아무 키나 눌러주세요" << endl;
    char c;
    cin >> c;
    GameManager::turn = ETURN_USER;
    bool finish = true;
    cout << "게임이 시작되었습니다!!!" << endl;
    GameManager::gun.Reroad();
    while(finish)
    {
        if(GameManager::turn == ETURN_USER)
        {
            cout << "유저턴" << endl;
            cout << "자신에게 쏘려면 S, 상대에게 쏘려면 W를 입력해주세요" << endl;
            for(int i = 0; i < GameManager::user.items.size(); i++)
            {
                cout << i+1 << ". " << GameManager::user.items[0].name << endl;;
            }
            char input;
            cin >> input;
            switch(input)
            {
                case 'S':
                GameManager::gun.Shoot(&GameManager::dealer);
                GameManager::turn = ETURN_DEALER;
                break;
                case 'W':
                GameManager::gun.Shoot(&GameManager::user);
                break;
                case '1':
                if(GameManager::user.items.empty())
                    break;
                GameManager::user.items[0].Use();
                break;
                case '2':
                if(GameManager::user.items.size() < 2)
                    break;
                GameManager::user.items[1].Use();
                break;
                case '3':
                if(GameManager::user.items.size() < 3)
                    break;
                GameManager::user.items[2].Use();
                break;
                case '4':
                if(GameManager::user.items.size() < 4)
                    break;
                GameManager::user.items[3].Use();
                break;
                case '5':
                if(GameManager::user.items.size() < 5)
                    break;
                GameManager::user.items[4].Use();
                break;
                case '6':
                if(GameManager::user.items.size() < 6)
                    break;
                GameManager::user.items[5].Use();
                break;
            }
        }
        else
        {
            cout << "딜러턴";
            finish = false;
        }
        if(GameManager::user.current_HP <= 0)
        {
            cout << "딜러 승리!!!" << endl;
            finish = false;
        }
        else if(GameManager::dealer.current_HP <=0)
        {
            cout << "유저 승리!!!" << endl;
            finish = false;
        }

    }
    return 0;
}