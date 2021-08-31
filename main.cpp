//
//
//
//
//	Surubariu Vlad-Marian
//
//
//
//
//

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <dos.h>
#include <time.h>

#define MAXMARIMESARPE 100
#define MAXAXAX 119 //marimea ferestrei jocului pe axa OX
#define MAXAXAY 29  // marimea ferestrei jocului pe axa OY


using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

void gotoxy(int x, int y) {    //se schimba pozitia cursorului, dar si a sarpelui
	CursorPosition.X = x;     //schimbarea valorilor cursorului, in functie de tastele apasate
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);   //se aplica schimbarile
}


class Punct {
private:
	int x; //coordonatele punctului
	int y;
public:
	Punct() { //constructor
		x = y = 10;
	}
	Punct(int x, int y) {  //constructor
		this->x = x;
		this->y = y;
	}
	void SetarePunct(int x, int y) {  //schimbare valori
		this->x = x;
		this->y = y;
	}
	int GetX() {  //primeste coordonata X
		return x; 
	} 
	int GetY() { //primeste coordonata Y
		return y;
	}
	void Sus() {  //merge in sus
		y--;
		if (y < 0)
			y = MAXAXAY;
	}
	void Jos() {  //merge in jos
		y++;
		if (y > MAXAXAY)
			y = 0;
	}  
	void Stanga() { //merge in stanga
		x--;
		if (x < 0)
			x = MAXAXAX;
	}
	void Dreapta() {  //merge in dreapta
		x++;
		if (x > MAXAXAX)
			x = 0;
	}
	void Deseneaza(char ch = 'o') {  //se deseneaza fragmentele sarpelui si fructele
		gotoxy(x, y);
		cout << ch;
	}
	void CopierePozitie(Punct* p) {  //se copiaza pozitia anterioara pentru a putea fi schimbarea ei
		p->x = x;
		p->y = y;
	}

	int VerificaEgalitate(Punct* p) { //se verifica daca s-a facut corect copierea pozitiei anterioare
		if (p->x == x && p->y == y)
			return 1;
		return 0;
	}



};

class Snake {
private:
	Punct* fragment[MAXMARIMESARPE]; //vectorul ce reprezinta numarul de fragmente din sarpe
	int marime; // marimea curenta
	char directie; // directia sarpelui
	Punct fruct; //fructele ce trebuiesc colectate
	int stare;  //se verifica daca jocul a inceput sau s-a terminat
	int VerificareJocInceput; //se verifica daca a inceput jocul si se foloseste pentru a ajuta la disparitia ecranului de start
	int clipire; //clipirea fructului
public:
	Snake() {
		marime = 1; //marimea de inceput a sarpelui
		fragment[0] = new Punct(20, 20); //se atribuie dinamic sarpelui punctul de start
		for (int i = 1; i < MAXMARIMESARPE; i++) {
			fragment[i] = NULL; //se initializeaza pozitiile pentru corpul sarpelui
		}
		fruct.SetarePunct(rand() % MAXAXAX, rand() % MAXAXAY); //se alege la intamplare pozitia fructului
		stare = 0; //jocul nu a inceput
		VerificareJocInceput = 0; //jocul nu a inceput
	} 
	void AdaugareFragment(int x, int y) { //se mareste numarul de fragmente din care este facut sarpele
		fragment[marime++] = new Punct(x, y);
	}
	void IntoarceSus() {  //functie folosita pentru a schimba directia spre sus
		if (directie != 's')
			directie = 'w';
	} 
	void IntoarceJos() {  //functie folosita pentru a schimba directia spre jos
		if (directie != 'w')
			directie = 's';
	}
	void IntoarceStanga() {  //functie folosita pentru a schimba directia spre stanga
		if (directie != 'd')
			directie = 'a';
	}
	void IntoarceDreapta() {  //functie folosita pentru a schimba directia spre dreapta
		if (directie != 'a')
			directie = 'd';
	}
	void StartingScreen() { //ecran de inceput
		cout << endl;
		SetConsoleTextAttribute(console, 48); //formatarea consolei
		cout << endl << endl << endl << endl << endl;
		cout << "                                                                                                                        " << endl;
		cout << "                                                                                                                        " << endl;
		cout << "                                                                                                                        " << endl;
		cout << "              _______________     _____       _____    ___________                                                      " << endl;
		cout << "             |               |   |     |     |     |  |           |                                                     " << endl;
		cout << "             |_             _|   |     |     |     |  |     ______|              /^\\ /^\\                                " << endl;
		cout << "               \\__       __/     |     |_____|     |  |    |_                  _|__|  O|\\                               " << endl;
		cout << "                  |     |        |                 |  |      |         \\/     /~     \\_/ \\                              " << endl;
		cout << "                  |     |        |      _____      |  |     _|          \\____|__________/ \\                             " << endl;
		cout << "                  |     |        |     |     |     |  |    |______           \\_______      \\                            " << endl;
		cout << "                  |     |        |     |     |     |  |           |                  `\\     \\                           " << endl;
		cout << "                  |_____|        |_____|     |_____|  |___________|                                                     " << endl;

		cout << "                                                                                                                        " << endl;
		cout << "                                                                                                                        " << endl;
	}
	void Miscare() {
		system("cls"); //dispar elementele de pe ecran

		if (stare == 0) { //daca jocul nu a inceput
			if (!VerificareJocInceput) { //daca ecranul de start inca nu a aparut
				StartingScreen(); //afisez ecranul de start
				cout << "                                         Apasa o tasta pentru a incepe                                                  " << endl;
				cout << "                                                                                                                        " << endl;
				_getch(); //se va apasa o tasta la intamplare pentru a incepe jocul
				stare = 1; // a inceput jocul 
				VerificareJocInceput = 1; //a aparut ecranul de start
			}
			else {
				cout << endl << "Ai pierdut" << endl; //daca ecranul de start a fost deja, dar jocul nu a inceput inseamna ca jucatorul a pierdut
				cout << "Apasa o tasta pentru a incepe din nou"; 
				_getch(); //se va introduce un caracter pentru a incepe din nou jocul
				stare = 1; //se marcheaza din nou inceputul jocului
				marime = 1; //numarul de elemente din sarpe revine la 1
			}

		}

		for (int i = marime - 1; i > 0; i--) {  // noii pozitii ii este atribuita vechea pozitie+1
			fragment[i - 1]->CopierePozitie(fragment[i]);
		}


		switch (directie) {
		case 'w':
			fragment[0]->Sus(); //capul sarpelui isi schimba directia spre sus 
			break;
		case 's':
			fragment[0]->Jos(); //capul sarpelui isi schimba directia spre jos
			break;
		case 'a':
			fragment[0]->Stanga(); //capul sarpelui isi schimba directia spre stanga
			break;
		case 'd':
			fragment[0]->Dreapta(); //capul sarpelui isi schimba directia spre dreapta
			break;
		}

		if (Coliziune()) //daca sarpele se mananca singura
			stare = 0; //jucatorul a pierdut



		if (fruct.GetX() == fragment[0]->GetX() && fruct.GetY() == fragment[0]->GetY()) { //dupa ce capul sarpelui se afla pe aceeasi pozitie cu fructul
			AdaugareFragment(0, 0); //se mai adauga un element in marimea sarpelui
			fruct.SetarePunct(rand() % MAXAXAX, rand() % MAXAXAY); //si apare un nou fruct
		}

		for (int i = 0; i < marime; i++)
			fragment[i]->Deseneaza(); //dupa ce am sters elementele din consola rescriem sarpele

		SetConsoleTextAttribute(console, 63); //infrumusetare
		if (!clipire) //se asigura faptul ca fructul va clipi mereu, el fiind sters si desenat constant
			fruct.Deseneaza('$');
		clipire = !clipire; 
		SetConsoleTextAttribute(console, 48); //infrumusetare
		Sleep(50);
	}
	int Coliziune() { //verificam daca sarpele se mananca
		for (int i = 1; i < marime; i++) //parcurgem toate elementele corpului 
			if (fragment[0]->VerificaEgalitate(fragment[i])) //si verificam daca se afla pe aceeasi pozitie ca si capul sarpelui
				return 1;
		return 0;

	}

};


int main() {

	Snake snake;
	char tasta = 'l'; //initializam 
	do {
		if (_kbhit()) { //daca se atinge tastatura
			tasta = _getch(); //preluam tasta atinsa
		} 
		switch (tasta) { //verificam tasta atinsa si mutam sarpele in directia de care este nevoie
		case 'w':
		case 'W':
			snake.IntoarceSus(); //daca apasam W sau w sarpele schimba directia spre sus
			break;
		case 's':
		case 'S':
			snake.IntoarceJos(); //daca apasam S sau s sarpele schimba directia spre jos
			break;
		case 'a':
		case 'A':
			snake.IntoarceStanga(); //daca apasam A sau a sarpele schimba directia spre stanga
			break;
		case 'd':
		case 'D':
			snake.IntoarceDreapta(); //daca apasam D sau dsarpele schimba directia spre dreapta
			break;
		case 'p':
		case 'P':
			system("pause");
		}
		snake.Miscare();



	} while (tasta != 'e'); //cand apasam e se opreste jocul

	return 0;
}
