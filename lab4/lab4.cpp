// lab4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;
class Figura;

class Szachownica
{
	private:
		Figura *sz[8][8];
		char wiz[8][8];

	public:
		Szachownica();
		bool operator==(const Szachownica &druga_szachownica);
		bool operator==(const char wiz2[][8]);

		Figura *getFigura(int i, int j) { return sz[i][j]; };
		char getWiz(int i, int j) { return wiz[i][j]; };

		void setFigura(int i, int j, Figura *figura, bool deleteFigura = false) { 
			if (deleteFigura) {
				delete sz[i][j];
			}
			sz[i][j] = figura;
		};
		void setWiz(int i, int j, const char wis) { wiz[i][j] = wis; };
};

class Figura
{
	protected:
	Szachownica *s; // adres szachownicy do której należy dana figura 
	int x;
	int y;
	public:
		Figura(int x, int y, Szachownica *s1) : x(x), y(y), s(s1) {
		};
		~Figura();
		virtual bool set(int x, int y)=0; // wstawia figure na pole x,y ; zwraca false w przypadku błędu: pole    
										 //zajęte, przekroczenie zakresu     tablicy

		void setSzachownica(Szachownica *s1) { this->s = s1; };

};

class Wieza : public Figura
{
	public:
		Wieza(int x, int y, Szachownica *s1) : Figura(x, y, s1) {
			this->set(x, y);
		};
		virtual bool set(int x, int y);
};

class Goniec : public Figura
{
	
	private:
		bool checkPosition(int x, int y);

	public:
	
	Goniec(int x, int y, Szachownica *s1) : Figura(x, y, s1) {
		this->set(x, y);
	};
	virtual bool set(int x, int y);


};

bool Goniec::checkPosition(int x, int y) {
	if (x < 0 || y < 0 || x > 7 || y > 7) {
		return false;
	}

	//Sprawdzanie poprawności po 1 skosie
	for (int i = 1; i < 8; i++) {
		for (int j = 1; j < 8; j++) {
			if (x == i && y == j) {
				return true;
			}
		}
	}

	//Sprawdzanie porawności po 2 skosie
	for (int i = 7; i > 0; i--) {
		for (int j = 1; j < 8; j++) {
			if (x == i && y == j) {
				return true;
			}
		}
	}

	return false;
}


bool Wieza::set(int x, int y) {
	if (x < 0 || y < 0 || x > 7 || y > 7) {
		return false;
	}

	//Musi być albo x albo y takie samo 
	if (this->x != x && this->y != y) {
		return false;
	}


	//Można przesunać wieżę i ustawić zasięg bicia
	if (this->y == y) {
		//Sprawdzamy czy po drodze nic nie stoi, jak stoi to to kujemy
		if (x < this->x) {
			int pierwszeKucie = -1;
			int x2 = this->x;
			for (int i = x; i <= x2; i++) {
				
				char wiz = this->s->getWiz(i, y);
				if (wiz != 'O' && wiz != 'X') {
					pierwszeKucie = i;
					break;
				}
			}

			if (pierwszeKucie != -1 && pierwszeKucie != x) {
				return false;
			}
			else {
				//Ustawiamy zasięg bicia -- w prawo
				for (int i = x + 1; i <= x2; i++) {
					this->s->setWiz(i, y, 'X');
				}

				//Ustawiamy zasięg bicia -- w lewo
				for (int i = x - 1; i >= 0; i--) {
					char wiz_left = this->s->getWiz(i, y);

					if (wiz_left == 'O' || wiz_left == 'X') {
						this->s->setWiz(i, y, 'X');
					}
					else {
						break;
					}
				}
			}

		}
		else if (x > this->x) {
			int pierwszeKucie = -1;
			int x2 = this->x;
			for (int i = x; i >= this->x; i--) {

				char wiz = this->s->getWiz(i, y);
				if (wiz != 'O' || wiz != 'X') {
					pierwszeKucie = i;
					break;
				}
			}

			if (pierwszeKucie != -1 && pierwszeKucie != x) {
				return false;
			}
			else {
				//Ustawiamy zasięg bicia -- w lewo
				for (int i = x - 1; i >= 0; i--) {
					this->s->setWiz(i, y, 'X');
				}

				//Ustawiamy zasięg bicia -- w prawo
				for (int i = x + 1; i <= x2; i++) {
					char wiz_right = this->s->getWiz(i, y);

					if (wiz_right == 'O' || wiz_right == 'X') {
						this->s->setWiz(i, y, 'X');
					}
					else {
						break;
					}
				}

			}
		}
	}
	else if (this->x = x) {
		if (y < this->y) {
			int pierwszeKucie = -1;
			int y2 = this->y;
			for (int i = y; i <= y2; i++) {

				char wiz = this->s->getWiz(i, y);
				if (wiz != 'O' && wiz != 'X') {
					pierwszeKucie = i;
					break;
				}
			}

			if (pierwszeKucie != -1 && pierwszeKucie != x) {
				return false;
			}
			else {
				//Ustawiamy zasięg bicia -- do góry
				for (int i = y + 1; i <= y2; i++) {
					this->s->setWiz(x, i, 'X');
				}

				//Ustawiamy zasięg bicia -- na dól
				for (int i = y - 1; y >= 0; i--) {
					char wiz_bottom = this->s->getWiz(x, i);

					if (wiz_bottom == 'O' || wiz_bottom == 'X') {
						this->s->setWiz(x, i, 'X');
					}
					else {
						break;
					}
				}
			}

		}
		else if (x > this->x) {
			int pierwszeKucie = -1;
			int y2 = this->y;
			for (int i = y; i >= y2; i--) {

				char wiz = this->s->getWiz(x, i);
				if (wiz != 'O' || wiz != 'X') {
					pierwszeKucie = i;
					break;
				}
			}

			if (pierwszeKucie != -1 && pierwszeKucie != x) {
				return false;
			}
			else {
				//Ustawiamy zasięg bicia -- na dół
				for (int i = y - 1; i >= 0; i--) {
					this->s->setWiz(x, i, 'X');
				}

				//Ustawiamy zasięg bicia -- do góry
				for (int i = x + 1; i <= y2; i++) {
					char wiz_top = this->s->getWiz(x, i);

					if (wiz_top == 'O' || wiz_top == 'X') {
						this->s->setWiz(x, i, 'X');
					}
					else {
						break;
					}
				}

			}
		}
	}

	//Ustawiamy wieże
	this->s->setWiz(x, y, 'W');
	this->s->setFigura(x, y, this, true);
	this->x = x;
	this->y = y;
	return true;
}

bool Goniec::set(int x, int y) {
	if (x < 0 || y < 0 || x > 7 || y > 7) {
		return false;
	}

	//W przypadku pierwszego przesunięcia możemy postawić gońca, gdzie chcemy oczywiście chodzi o pola gońca
	if (!checkPosition(x, y)) {
		return false;
	}

	//Jeśli pozycja jest prawidłowa sprawdzamy czy nic nie stoi na przeszkodzie

	//Ustawiamy zasięg bicia


	return true;
}


//Implementacja metod
Figura::~Figura() {
	if (x && y) {
		s->setWiz(x, y, 'O');
		s->setFigura(x, y, NULL, true);
	}
}


Szachownica::Szachownica() {

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			sz[i][j] = NULL;
			wiz[i][j] = 'O';
		}
	}
}

bool Szachownica::operator==(const char wiz2[][8]) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			
			if (wiz[i][j] != wiz2[i][j]) {
				return false;
			}

		}
	}

	return true;
}

bool Szachownica::operator==(const Szachownica &druga_szachownica) {
	return *this == druga_szachownica.wiz;
}


int main()
{
	Szachownica szachownica1;
	Szachownica szachownica2;
	cout << "Pierwszy test operatora ==" << endl;
	if (szachownica1 == szachownica2) {
		cout << "Szachownice są takie same" << endl;
	}
	else {
		cout << "Szachownice nie są takie same" << endl;
	}

	//Ustawiamy wieże na pozycje domyślne
	Figura *wieza1 = new Wieza(0, 0, &szachownica1);
	Figura *wieza2 = new Wieza(0, 7, &szachownica1);
	Figura *wieza3 = new Wieza(7, 0, &szachownica1);
	Figura *wieza4 = new Wieza(7, 7, &szachownica1);

	//Kujemy wieza1 wieze 7
	if (wieza1->set(7, 0)) {
		cout << "Pomyślnie ustawiono wieże na pozycje (7, 0)" << endl;
		wieza3 = NULL;
	}
	else {
		cout << "Nie udało się ustawić wieży na pozycje (7, 0)" << endl;
	}

	//wieza3->set(7, 0) -- wywala błąd, więc wieża została pomyślnie skuta!!
	
	//Tworzymy i ustawiamy gońce
	Figura *goniec1 = new Goniec(1, 1, &szachownica1);
	Figura *goniec2 = new Goniec(1, 7, &szachownica1);
	Figura *goniec3 = new Goniec(7, 1, &szachownica1);
	Figura *goniec4 = new Goniec(7, 6, &szachownica1);


	//Figura *wieza2 = new Wieza(0, 0, &szachownica1);
	cout << "Drugi test operatora ==" << endl;
	if (szachownica1 == szachownica2) {
		cout << "Szachownice są takie same" << endl;
	}
	else {
		cout << "Szachownice nie są takie same" << endl;
	}
	system("pause");
    return 0;
}

