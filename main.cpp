#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

class Poz
{
private:
    int x;
    int y;

public:
    Poz() : x(), y() {}
    Poz(int x, int y) : x(x), y(y) {}

    Poz(const Poz& other) : x(other.x), y(other.y){}  ///constructor de copiere

    Poz& operator = (const Poz& other)
    {
        if (this != &other) {
            x = other.x;
            y = other.y;
        }
        return *this;
    }

    ~Poz() {}  ///destructor

    void SetarePunct(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    int GetX() const {
        return x;
    }

    int GetY() const {
        return y;
    }


    void Scrie() const {
        cout << "*";
    }

    void Sterge() const {
        cout << " ";
    }

    void Debug(){
			cout<<"("<<x<<","<<y<<") ";
		}

    friend ostream& operator<<(ostream& os, const Poz& poz) {       ///supraincarcarea operatorului <<
        os << "(" << poz.x << "," << poz.y << ")";
        return os;
    }
};

class Mancare {
private:
    int x;
    int y;

public:
    ///constructor de initializare
    Mancare() : x(0), y(0) {}

    Mancare(int maxX, int maxY) : x(rand() % maxX), y(rand() % maxY) {}

    ///constructor de copiere
    Mancare(const Mancare& other) : x(other.x), y(other.y) {}

    ///operator de copiere
    Mancare& operator=(const Mancare& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
        }
        return *this;
    }

    ~Mancare() {}

    friend ostream& operator<<(ostream& os, const Mancare& mancare) {
        os << "Mancare(" << mancare.x << "," << mancare.y << ")";
        return os;
    }

    void GenerareNoua(int maxX, int maxY) {
        x = rand() % maxX;
        y = rand() % maxY;
    }

    bool EsteMancata(const Poz& poz) const {
        return (x == poz.GetX() && y == poz.GetY());
    }

    void Desenare() const {
        cout << "o";
    }

};

class Sarpe
{
private:
    int x;
    int y;
    int lungime;
    char directie;
    Poz& poz;

public:

    Sarpe(Poz& poz) : x(10), y(10), lungime(1), directie('d'), poz(poz) {}

    Sarpe(const Sarpe& other) : x(other.x), y(other.y), lungime(other.lungime), directie(other.directie), poz(other.poz) {}

    Sarpe& operator=(const Sarpe& other)
    {
        if (this != &other)
        {
            x = other.x;
            y = other.y;
            lungime = other.lungime;
            directie = other.directie;
            poz = other.poz;
        }
        return *this;
    }

    ~Sarpe() {}

    friend ostream& operator<<(ostream& os, const Sarpe& sarpe)
    {
        os << "Sarpe(" << sarpe.x << "," << sarpe.y << "), Lungime: " << sarpe.lungime << ", Directie: " << sarpe.directie;
        return os;
    }

    void MiscareSiVerificareMancare(const Mancare& mancare)
    {
        poz.Sterge();
        switch (directie)
        {
            case 'w':
                y++;
                break;
            case 's':
                y--;
                break;
            case 'a':
                x--;
                break;
            case 'd':
                x++;
                break;
        }
        if (x >= poz.GetX()) x = 0;
        if (x < 0) x = poz.GetX() - 1;
        if (y >= poz.GetY()) y = 0;
        if (y < 0) y = poz.GetY() - 1;
        poz.SetarePunct(x, y);
        poz.Scrie();
        if (mancare.EsteMancata(poz))
            lungime++;

    }

    void SchimbaDirectie(char nouaDirectie)
    {
        if ((nouaDirectie == 'w' && directie != 's') ||
            (nouaDirectie == 's' && directie != 'w') ||
            (nouaDirectie == 'a' && directie != 'd') ||
            (nouaDirectie == 'd' && directie != 'a'))
                directie = nouaDirectie;

    }


    bool Coliziune()
    {
        for (int i = 1; i < lungime; i++)
            if (x == poz.GetX() && y == poz.GetY())
                return true;

        return false;
    }

};

int main()
{
    Poz harta(20, 20);
    Sarpe sarpe(harta);
    Mancare mancare(harta.GetX(), harta.GetY());

    bool jocInceput = true;
    int scor = 0;

    while (true) {
        if (jocInceput)
        {
            cout << "Jocul Snake \n";
            cout << "Instructiuni:\n";
            cout << "Foloseste tastele W, A, S, D pentru a controla sarpele.\n";
            cout << "Mananca mancarea (o) pentru a creste.\n";
            cout << "Evita sa te lovesti de pereti sau de tine insuti!\n";
            cout << "Apasa orice tasta pentru a incepe...\n";
            _getch();
            jocInceput = false;
        }

        if (_kbhit()) {
            char input = _getch();
            sarpe.SchimbaDirectie(input);
        }

        sarpe.MiscareSiVerificareMancare(mancare);

        if (sarpe.Coliziune()) {
            cout << "Joc încheiat! Scor: " << scor << endl;
            break;
        }

        cout << "Scor: " << scor << endl;
        cout << harta << endl;
        harta.Debug();
        mancare.Desenare();
        Sleep(100);


    }

    return 0;
}
