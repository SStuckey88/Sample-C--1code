#include<iostream>
#include<string>
#include<vector>

using namespace std;


class Point {
    public:
        Point(int xIn, int Yin);
        vector<int> GetLocation() {return position;};
    private:
        vector<int> position;
};

class BerryBush {
    public:
        BerryBush(int xIn, int Yin);
        int GetNumOfBerries() {return NumOfBerries;};
        void damaged();
        bool isDead = false;
    private:
        int NumOfBerries;
        Point* location;
        
};

class Bears {
    public:
        Bears(string name);
        void Attack(BerryBush* enemy);
        int CurrentHP() {return HP;};
        void SetName(string nameIn) {name = nameIn;};
        string GetName() {return name;};
        bool GetStatus() {return isFed;};
    private:
        double HP;
        string name;
        bool isPolarBear;
        bool isFed;
};

Bears::Bears(string name = "") {
    this->name = name;
    isPolarBear = false;
    HP = 10;
}


void Bears::Attack(BerryBush* enemy) {
    if (enemy->isDead){
    enemy->damaged();
    isFed = true;
    }
}


BerryBush::BerryBush(int xIn, int Yin) {
    location = new Point(xIn, Yin);
    NumOfBerries = rand() % 5;
}


void BerryBush::damaged() {
    NumOfBerries -= 1;
    if (NumOfBerries == 0) {
        isDead = true;
        delete location;
    }
};

Point::Point(int xIn, int Yin) {
    position.push_back(xIn);
    position.push_back(xIn);
};

int main() {
    const int ColonyStrength = 20;
    vector<Bears*> bearses;
    string name;
    for (int i = 0; i < ColonyStrength; i++) {
        name = "bear" + i;
        bearses.push_back(new Bears(name));
    }

    const int berryNum = rand() %35;
    vector<BerryBush*> bushes;
    for (int i = 0; i < ColonyStrength; i++) {
        bushes.push_back(new BerryBush((rand()%50),(rand()%50)));
    }

    bool GameOver = false;
    int numBears = ColonyStrength;
    while(!GameOver) {
        for (int i = 0; i < numBears; i++) {
        bearses.at(i)->Attack(bushes.at(rand() % berryNum));

        if (bearses.at(i)->GetStatus()) {
            cout << bearses.at(i)->CurrentHP();
        }
        else {
            delete bearses.at(i);
            bearses.at(i) = new Bears("badBear");
            numBears - 1;
        }
        }
        
        if (ColonyStrength < 10) {
            GameOver = true;
        }
    }

    return 1;
}