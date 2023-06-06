#include<iostream>
#include<conio.h>
#include<iomanip>
#include<windows.h>
using namespace std;
int Turn;
#define capac 100
void getRowColbyLeftClick(int& rpos, int& cpos)
{
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD Events;
    INPUT_RECORD InputRecord;
    SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
    do
    {
        ReadConsoleInput(hInput, &InputRecord, 1, &Events);
        if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
        {
            cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
            rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
            break;
        }
    } while (true);
}
void gotoRowCol(int rpos, int cpos)
{
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = cpos;
    scrn.Y = rpos;
    SetConsoleCursorPosition(hOuput, scrn);
}
void SetClr(int clr)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), clr);
}


void initialize(char brd[][capac], int dim, int Win, char sym[], char Pnames[][capac], int& nop, int turn)
{
	cout << "\nEnter total no. of players";
	cin >> nop;
	for (int r = 0; r < dim; r++)
	{
		for (int c = 0; c < dim; c++)
		{
			brd[r][c] = '-';
		}
	}

	for (int i = 0; i < nop; i++)
	{
		cout << "Enter [" << i + 1 << "] Name plz :";
		cin >> Pnames[i];
	}
	for (int i = 0; i < nop; i++)
	{
		cout << "Enter [" << i + 1 << "] Symbol plz :";
		cin >> sym[i];
	}
	turn = rand() % nop;
}
void Selectpos(int& Pr, int& Pc, int Dim)
{
	cout << "Select row (r should b < than dim)" ;
	cin >> Pr;
	cout << "Select column (c should b < than dim)" ;
	cin >> Pc;

	Pr--;
	Pc--;

}
bool Valid(char brd[][capac], int pr, int pc, int dim)
{
	return  (brd[pr][pc] == '-') && (pr >= 0 && pc >= 0) && (pr < dim&& pc < dim) ;
}
void printboard(char Brd[][capac], int dim)
{
	for (int r = 0; r < dim; r++)
	{
		for (int c = 0; c < dim; c++)
		{
			cout <<setw(3)<< Brd[r][c] << " ";
		}
		cout << endl;
	}
}
void move(char brd[][capac],int dim, int pr, int pc, char sym)
{
	brd[pr][pc] = sym;
}
void updateboard(char brd[][capac], int dim, int Pr, int Pc, char sym)
{
	brd[Pr][Pc] = sym;
}
void turnchange(int& Turn, int& nop)
{
	Turn = (Turn + 1) % nop;
}
bool isdraw(char brd[][capac], int dim,char sym)
{
	for (int r = 0; r < dim; r++)
	{
		for (int c = 0; c < dim; c++)
		{
			if (brd[r][c] == '-')
			{
				return false;
			}
		}
	}
	return true;
}
void printMsgturn(char PNames[][capac], int Turn)
{
	cout << PNames[Turn] << "\'s Turn: " << endl;
}
void printboardcc(char Brd[][capac], int d)
{
    for (int r = 0; r < d; r++)
    {
        for (int c = 0; c < d; c++)
        {
            cout << Brd[r][c];
        }
        cout << endl;
    }
}
void Turnmsgcc(string Name)
{
    cout << Name << "'s TURN\n";
}
void movecc(char Brd[][capac], int pr, int pc, char sym)
{
    Brd[pr][pc] = sym;
}

bool winhorizontal(char Brd[][capac], int dim, char sym, int wc, int pr, int pc)
{
    for (int i = 0; i < wc; i++)
    {
        if (Brd[pr][pc + i] != sym)
        {
            return false;
        }
    }
    return true;
}
bool winvertically(char Brd[][capac], int dim, char sym, int wc, int pr, int pc)
{
    for (int i = 0; i < wc; i++)
    {
        if (Brd[pr][pr + i] != sym)
        {
            return false;
        }
    }
    return true;
}
bool windiagTl2br(char Brd[][capac], int dim, char sym, int winc, int ri, int ci)
{
    int count = 0;
    for (int i = 0; i < winc; i++)
    {

        if (Brd[ri + i][ci + i] == sym)
        {
            count++;
        }
    }
    return count == winc;


}
bool windiagTr2bl(char Brd[][capac], int dim, char sym, int winc, int ri, int ci)
{
    int count = 0;
    for (int i = 0; i < winc; i++)
    {

        if (Brd[ri + i][ci - i] == sym)
        {
            count++;
        }
    }
    return count == winc;


}
bool winhere(char Brd[][capac], int ri, int ci, int dim, char sym, int winc)
{
    if ((winhorizontal(Brd, dim, sym, winc, ri, ci) == true) || (winvertically(Brd, dim, sym, winc, ri, ci) == true)
        || (windiagTl2br(Brd, dim, sym, winc, ri, ci) == true)
        || (windiagTr2bl(Brd, dim, sym, winc, ri, ci) == true))
    {
        return true;
    }
    return false;
}
bool winhorizonta(char Brd[][capac], int dim, int r, int c, char sym, int win)
{
    if (c + win > dim)
        return false;
    int count = 0;
    for (int i = 0; i < win; i++)
        if (Brd[r][c + i] == sym)
            count++;
    if (count == win)
        return true;
    return false;

}
bool winverticall(char Brd[][capac], int d, int r, int c, char sym, int win)
{
    if (r + win > d)
        return false;
    int count = 0;
    for (int i = 0; i < win; i++)
        if (Brd[r + i][c] == sym)
            count++;
    if (count == win)
        return true;
    return false;

}
bool winL2Rcc(char Brd[][capac], int dim, int r, int c, char sym, int win)
{
    int count = 0;
    for (int i = 0; i < win; i++)
        if (Brd[r + i][c + i] == sym)
            count++;
    if (count == win)
        return true;
    return false;

}
bool winR2Lcc(char Brd[][capac], int dim, int r, int c, char sym, int win)
{

    int count = 0;
    for (int i = 0; i < win; i++)
        if (Brd[r + i][c - i] == sym)
            count++;
    if (count == win)
        return true;
    return false;

}
bool iswin(char Brd[][capac], int dim, char sym, int winc)
{
    for (int ri = 0; ri < dim; ri++)
    {
        for (int ci = 0; ci < dim; ci++)
        {
            if (winhere(Brd, ri, ci, dim, sym, winc) == true)
            {
                return true;
            }
        }
    }
    return false;
}
bool wincc(char Brd[][capac], int dim, char sym[], int win, int Turn)
{
    for (int r = 0; r < dim; r++)
    {
        for (int c = 0; c < dim; c++)
        {
            if (winhorizonta(Brd, dim, r, c, sym[Turn], win))
                return true;
            if (winR2Lcc(Brd, dim, r, c, sym[Turn], win))
                return true;
            if (winverticall(Brd, dim, r, c, sym[Turn], win))
                return true;
            if (winL2Rcc(Brd, dim, r, c, sym[Turn], win))
                return true;

        }
    }
    return false;
}
void turncc(int& turn, int nop)
{
    turn = (turn + 1) % nop;
}
bool isvalidcc(char Brd[][capac], int d, int r, int c)
{
    return (r >= 0 && r < d) && (c >= 0 && c < d) && (Brd[r][c] == '-');
}
void initializecc(char Brd[][capac], int dim, string Namep[], int nop, char sym[], int& Turn)
{
    for (int r = 0; r < dim; r++)
    {
        for (int c = 0; c < dim; c++)
        {
            Brd[r][c] = '-';
        }
    }
    for (int i = 0; i < nop; i++)
    {
        cout << "Player [" << i + 1 << "] name :";
        string name;
        cin >> name;
        Namep[i] = name;
        cout << "Player [" << i + 1 << "] symbol :";
        char Sym;
        cin >> Sym;
        sym[i] = Sym;
    }
    Turn = rand() % nop;

}

bool drawcc(char Brd[][capac], int dim)
{
    int count = 0;
    for (int r = 0; r < dim; r++)
    {
        for (int c = 0; c < dim; c++)
        {
            if (Brd[r][c] == '-')
                count++;
        }
    }
    if (count == 0)
        return true;
    else
        return false;
}
void computercc(char Brd[][capac], int d, int& R, int& C, char sym[], int winc, int turn, int nop)
{

    for (int w = winc; w > 1; w--)
    {
        for (int r = 0; r < d; r++)
        {
            for (int c = 0; c < d; c++)
            {
                if (isvalidcc(Brd, d, r, c))
                {
                    Brd[r][c] = sym[turn];
                    if (wincc(Brd, d, sym, w, turn))
                    {
                        Brd[r][c] = '-';
                        R = r; C = c;

                    }
                    Brd[r][c] = '-';
                }
            }
        }
        int t2 = 0;
        if (turn < nop)
        {
            t2++;
            for (int r = 0; r < d; r++)
            {
                for (int c = 0; c < d; c++)
                {
                    if (isvalidcc(Brd, d, r, c))
                    {
                        Brd[r][c] = sym[t2];
                        if (wincc(Brd, d, sym, w, t2))
                        {
                            Brd[r][c] = '-';
                            R = r; C = c;
                            return;
                        }
                        Brd[r][c] = '-';
                    }
                }
            }
        }
    }


}
int mainComp()
{
    char B[capac][capac];
    int dim, nop, turn = 0, row = 0, col = 0, winc = 0, y = 0;
    cout << "Dimension plz..:";
    cin >> dim;
    cout << "how many players..: ";
    cin >> nop;
    string PN[capac];
    PN[0] = "Computer";
    char Sym[capac];
    Sym[0] = '*';
    if (dim == 3)
    {
        winc = 3;
    }
    else
    {
        cout << "Win count should b smaller than " << dim << endl;
        cin >> winc;
    }
    initializecc(B, dim, PN, nop, Sym, turn);
    while (y == 0)
    {
        system("Cls");
        printboardcc(B, dim); cout << "\n";
        Turnmsgcc(PN[turn]);
        if (turn == 0)
        {
            computercc(B, dim, row, col, Sym, winc, turn, nop);
        }
        else {
            do
            {
                getRowColbyLeftClick(row, col);
            } while (!isvalidcc(B, dim, row, col));
        }
        movecc(B, row, col, Sym[turn]);
        if (wincc(B, dim, Sym, winc, turn))
        {
            system("Cls");
            printboardcc(B, dim);
            cout << "\n\nPlayer " << turn + 1 << " " << PN[turn] << " Wins\n\n";
            y = 1;
        }
        if (drawcc(B, dim))
        {
            system("Cls");
            printboardcc(B, dim);
            cout << "\n\noops ... TIED \n\n";
            y = 1;
        }
        turncc(turn, nop);

    }
    return 0;
}
int mainHuman()
{
	srand(time(0));
	char brd[capac][capac] = {};
	int dim, Pr, Pc, winCount, nop;
	char Pnames[capac][capac] = {};
	char sym[capac] = {};
	cout << "Ennter Wincount :";
	cin >> winCount;
	cout << "Enter Dimension plzz";
	cin >> dim;
	initialize(brd, dim, winCount, sym, Pnames, nop, Turn);
	do {
		system("Cls");
		printboard(brd, dim);
		printMsgturn(Pnames, Turn);
		do {
			Selectpos(Pr, Pc, dim);
		} while (Valid(brd, Pr, Pc, dim) == false);
		move(brd, dim, Pr, Pc, sym[Turn]);
		if (iswin(brd, dim, sym[Turn], winCount) == true)
		{
			printboard(brd, dim);
			break;
		}

		turnchange(Turn, nop);
	} while (true);

	if (iswin(brd, dim, sym[Turn], winCount)==true)
	{
		cout << "\n\nCongratulations Player " << Pnames[Turn] << " You Have won the game.......\n\n\n";			
	}
	return 0;


}
int main()
{
    int choice;
    cout << "Enter Choice : ";
    cin >> choice;
    if (choice == 1)
    {
        mainHuman();
    }
    if (choice == 2)
    {
        mainComp();
    }
}