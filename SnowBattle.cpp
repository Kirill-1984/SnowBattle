//#include "stdafx.h" //���������� ��� Visual Studio
#include <iostream>
#include <locale>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include <set>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <windows.h> //����� ������� - Lucida Console
#include <mmsystem.h>

const int M = 10;
const int N = 12;

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

int f, wr, compSpeed, k;
char ball = (char)149; //��� �������, ������� ������ �� ���� (����� ��������, ���� ������������ �����������)

void gotoxy(int x, int y) //������� ������� ��������� �������
{
    COORD ord;
    ord.X = x;
    ord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ord);
}

void printOutput(char B[][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (B[i][j] == ball)
                SetConsoleTextAttribute(console, 11);
            else if (B[i][j] == 'x')
            {
                SetConsoleTextAttribute(console, 12);
                wr++;
            }
            else if (B[i][j] == '0')
                SetConsoleTextAttribute(console, 14);
            else if (B[i][j] == '*')
                SetConsoleTextAttribute(console, 11);
            else
                SetConsoleTextAttribute(console, 7);
            cout << B[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand((unsigned)time(NULL));

    char A[N][N];
    char B[N][N];
    int p, t, pos, x, y, q;
    int turnx, turny;
    int turnRandX, turnRandY;
    int total, choice;
    int totalOne = 0;
    int totalTwo = 0;
    int snowman1, snowman2;
    int rem1, rem2;
    string playerOneName, playerTwoName;
    vector<int> vec;
    set<pair<int, int>> move;
    set<int> possible = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    PlaySound("greeting.wav", NULL, SND_ASYNC | SND_FILENAME); //������� �����������
    SetConsoleTextAttribute(console, 11);
    cout << "\n*** ���� \"������� ���\" ***" << "\n\n";
    SetConsoleTextAttribute(console, 14);
    cout << "������� ��� ������� ������: ";
    SetConsoleTextAttribute(console, 11);
    getline(cin, playerOneName);
    SetConsoleTextAttribute(console, 14);
    cout << "������� ��� ������� ������: ";
    SetConsoleTextAttribute(console, 11);
    getline(cin, playerTwoName);

    cout << "\n�������� ����� ����:\n\n";
    cout << "1 - Player VS. Player\n";
    cout << "2 - Player VS. Computer (complex)\n";
    cout << "3 - Computer VS. Computer (all random)\n";
    SetConsoleTextAttribute(console, 14);
    cout << "��� �����: ";
    cin >> choice;

    if (choice == 2) compSpeed = 1800; //�������� ������� ��� ������ ������ 2
    if (choice == 3)
    {
        cout << "�������� �������� ���� ���������� (ms): ";
        cin >> compSpeed;
    }
    system("cls"); //������� ����� ����� ������� ����

    //������ ���� (����������� �� ����)

    SetConsoleTextAttribute(console, 7);

    for (int i = 0; i < 100; i++)
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if ((i == 0) || (j == 0) || (i == N - 1) || (j == N - 1))
                {
                    A[i][j] = '?';
                    B[i][j] = '*';
                }
                else
                {
                    A[i][j] = '?';
                }
            }
        }
        for (int t1 = 0, t2 = 0; t1 < 4, t2 < 8; t1++, t2 += 2)
        {
            p = 0;
            while (k != (14 - t2))
            {
                pos = 1 + rand() % 2;
                if (pos == 1)
                {
                    x = 1 + rand() % 10;
                    y = 1 + rand() % (7 + t1);
                    k = 0;
                    for (int i = -1; i <= 4 - t1; i++)
                    {
                        if (A[x - 1][y + i] == '?')
                            k++;
                        if (A[x + 1][y + i] == '?')
                            k++;
                    }
                    if (A[x][y + 4 - t1] == '?')
                        k++;
                    if (A[x][y - 1] == '?')
                        k++;
                    if (k == 14 - t2)
                    {
                        for (int i = 0; i < 4 - t1; i++)
                        {
                            A[x][y + i] = '#';
                        }
                        p++;
                    }
                }
                if (pos == 2)
                {
                    x = 1 + rand() % (7 + t1);
                    y = 1 + rand() % 10;
                    k = 0;
                    for (int i = -1; i <= 4 - t1; i++)
                    {
                        if (A[x + i][y - 1] == '?')
                            k++;
                        if (A[x + i][y + 1] == '?')
                            k++;
                    }
                    if (A[x - 1][y] == '?')
                        k++;
                    if (A[x + 4 - t1][y] == '?')
                        k++;
                    if (k == 14 - t2)
                    {
                        for (int i = 0; i < 4 - t1; i++)
                        {
                            A[x + i][y] = '#';
                        }
                        p++;
                    }
                }
                k = 0;
                if (p == 1 + t1)
                    break;
            }
        }
        q = 0;
        for (int i = 1; i < N - 1; i++)
        {
            for (int j = 1; j < N - 1; j++)
            {
                if (A[i][j] == '#')
                {
                    q++;
                }
            }
        }
        if (q == 20)
        {
            for (int i = 1; i < N - 1; i++)
            {
                for (int j = 1; j < N - 1; j++)
                {
                    if (A[i][j] == '#')
                    {
                        cout << A[i][j] << " ";
                    }
                    else
                        cout << A[i][j] << " ";
                }
                cout << endl;
            }
            break;
        }
    }

    //����� �����������

    gotoxy(0, 0); //��������� ������� ������

    for (int i = 1; i < N - 1; i++)
    {
        for (int j = 1; j < N - 1; j++)
        {
            B[i][j] = '?';
            cout << B[i][j] << " ";
        }
        cout << "\n";
    }

    //���� �������

    int shoot1 = 0;
    int shoot2 = 0;
    
    for (f = 0; f < 100; f++) //������������ ����� �����

    {
        switch (choice)
        {
            case 1: // Player VS. Player

                if (f % 2 == 0)

                { //������ ������ ������� ������

                //��� ������� ������

                moveagain1: //����� 1 ����� ����� (��� ������ �����)

                    SetConsoleTextAttribute(console, 12);
                    cout << playerOneName << " (�������� ���):\n";
                    SetConsoleTextAttribute(console, 10);
                    cout << "������: ";
                    SetConsoleTextAttribute(console, 11);
                    cin >> turnx;
                    SetConsoleTextAttribute(console, 10);
                    cout << "�������: ";
                    SetConsoleTextAttribute(console, 11);
                    cin >> turny;

                    //����� ���� ������� ������

                    if ((possible.find(turnx) == possible.end()) || (possible.find(turny) == possible.end()))
                    {
                        system("cls");
                        printOutput(B); //������ �������� ����������
                        gotoxy(0, N);
                        SetConsoleTextAttribute(console, 14);
                        cout << "������ ��� ����������!" << "\n";
                        PlaySound("error.wav", NULL, SND_ASYNC | SND_FILENAME);
                        goto moveagain1;
                    }
                    else
                    {
                        if (move.find(pair<int, int>(turnx, turny)) != move.end())
                        {
                            system("cls");
                            printOutput(B); //������ �������� ����������
                            gotoxy(0, N);
                            SetConsoleTextAttribute(console, 14);
                            cout << "������ ��� ��� ������! ������ �����!" << "\n";
                            PlaySound("error.wav", NULL, SND_ASYNC | SND_FILENAME);
                            goto moveagain1;
                        }
                        else
                        {
                            move.insert(make_pair(turnx, turny));
                            shoot1++;
                        }
                    }
                } //����� ��������� ���� ������� ������

                else
                {

                //��� ������� ������

                moveagain2: //����� 2 ����� ����� (��� ������ �����)

                    SetConsoleTextAttribute(console, 12);
                    cout << playerTwoName << " (�������� ���):\n";
                    SetConsoleTextAttribute(console, 10);
                    cout << "������: ";
                    SetConsoleTextAttribute(console, 11);
                    cin >> turnx;
                    SetConsoleTextAttribute(console, 10);
                    cout << "�������: ";
                    SetConsoleTextAttribute(console, 11);
                    cin >> turny;

                    //����� ���� ������� ������

                    if ((possible.find(turnx) == possible.end()) || (possible.find(turny) == possible.end()))
                    {
                        system("cls");
                        printOutput(B); //������ �������� ����������
                        gotoxy(0, N);
                        SetConsoleTextAttribute(console, 14);
                        cout << "������ ��� ����������!" << "\n";
                        PlaySound("error.wav", NULL, SND_ASYNC | SND_FILENAME);
                        goto moveagain2;
                    }
                    else
                    {
                        if (move.find(pair<int, int>(turnx, turny)) != move.end())
                        {
                            system("cls");
                            printOutput(B); //������ �������� ����������
                            gotoxy(0, N);
                            SetConsoleTextAttribute(console, 14);
                            cout << "������ ��� ��� ������! ������ �����!" << "\n";
                            PlaySound("error.wav", NULL, SND_ASYNC | SND_FILENAME);
                            goto moveagain2;
                        }
                        else
                        {
                            move.insert(make_pair(turnx, turny));
                            shoot2++;
                        }
                    }
                } //����� ��������� ���� ������� ������
                break;

            case 2: // Player VS. Computer

                if (f % 2 == 0)

                { //������ ���� ������� ������

                //��� ������� ������

                moveagain: //����� 1 ����� ����� (��� ������ �����)
                    SetConsoleTextAttribute(console, 12);
                    cout << playerOneName << " (�������� ���):\n";
                    SetConsoleTextAttribute(console, 10);
                    cout << "������: ";
                    SetConsoleTextAttribute(console, 11);
                    cin >> turnx;
                    SetConsoleTextAttribute(console, 10);
                    cout << "�������: ";
                    SetConsoleTextAttribute(console, 11);
                    cin >> turny;

                    //����� ���� ������� ������

                    if ((possible.find(turnx) == possible.end()) || (possible.find(turny) == possible.end()))
                    {
                        system("cls");
                        printOutput(B); //������ �������� ����������
                        gotoxy(0, N);
                        SetConsoleTextAttribute(console, 14);
                        cout << "������ ��� ����������!" << "\n";
                        PlaySound("error.wav", NULL, SND_ASYNC | SND_FILENAME);
                        goto moveagain;
                    }
                    else
                    {
                        if (move.find(pair<int, int>(turnx, turny)) != move.end())
                        {
                            system("cls");
                            printOutput(B); //������ �������� ����������
                            gotoxy(0, N);
                            SetConsoleTextAttribute(console, 14);
                            cout << "������ ��� ��� ������! ������ �����!" << "\n";
                            PlaySound("error.wav", NULL, SND_ASYNC | SND_FILENAME);
                            goto moveagain;
                        }
                        else
                        {
                            move.insert(make_pair(turnx, turny));
                            shoot1++;
                        }
                    }
                } //����� ��������� ���� ������� ������

                /*
				else
                {

                //��� ���������� (����� �������)

                generateagain:
                    turnRandX = 1 + rand() % 10;
                    turnRandY = 1 + rand() % 10;
                    turnx = turnRandX;
                    turny = turnRandY;
                    if (move.find(pair<int, int>(turnx, turny)) != move.end())
                    {
                        goto generateagain;
                    }
                    else
                    {
                        SetConsoleTextAttribute(console, 12);
                        cout << playerTwoName << " (��� ����������):\n";
                        SetConsoleTextAttribute(console, 10);
                        cout << "������: ";
                        SetConsoleTextAttribute(console, 11);
                        cout << turnx << "\n";
                        SetConsoleTextAttribute(console, 10);
                        cout << "�������: ";
                        SetConsoleTextAttribute(console, 11);
                        cout << turny << "\n";
                        move.insert(make_pair(turnx, turny));
                        shoot2++;
                    }
                } //����� ��������� ���� ����������
                */
                break;

            case 3: // Computer VS. Computer

                if (f % 2 == 0) //������ ������ 3
                {
                generateagain1:
                    turnRandX = 1 + rand() % 10;
                    turnRandY = 1 + rand() % 10;
                    turnx = turnRandX;
                    turny = turnRandY;
                    if (move.find(pair<int, int>(turnx, turny)) != move.end())
                    {
                        goto generateagain1;
                    }
                    else
                    {
                        SetConsoleTextAttribute(console, 12);
                        cout << playerOneName << " (��� ����������):\n";
                        SetConsoleTextAttribute(console, 10);
                        cout << "������: ";
                        SetConsoleTextAttribute(console, 11);
                        cout << turnx << "\n";
                        SetConsoleTextAttribute(console, 10);
                        cout << "�������: ";
                        SetConsoleTextAttribute(console, 11);
                        cout << turny << "\n";
                        move.insert(make_pair(turnx, turny));
                        shoot1++;
                    }
                }
                else
                {
                generateagain2:
                    turnRandX = 1 + rand() % 10;
                    turnRandY = 1 + rand() % 10;
                    turnx = turnRandX;
                    turny = turnRandY;
                    if (move.find(pair<int, int>(turnx, turny)) != move.end())
                    {
                        goto generateagain2;
                    }
                    else
                    {
                        SetConsoleTextAttribute(console, 12);
                        cout << playerTwoName << " (��� ����������):\n";
                        SetConsoleTextAttribute(console, 10);
                        cout << "������: ";
                        SetConsoleTextAttribute(console, 11);
                        cout << turnx << "\n";
                        SetConsoleTextAttribute(console, 10);
                        cout << "�������: ";
                        SetConsoleTextAttribute(console, 11);
                        cout << turny << "\n";
                        move.insert(make_pair(turnx, turny));
                        shoot2++;
                    }
                } //����� ������ 3
                break;
            default:
                SetConsoleTextAttribute(console, 12);
				cout << "����� ���� �� ���������!\n";
				SetConsoleTextAttribute(console, 7);
                exit(0);
        } //����� switch

        //����� ��������� �����

        if (A[turnx][turny] == '#')
        {
            A[turnx][turny] = ball;
            B[turnx][turny] = ball;
            PlaySound("found.wav", NULL, SND_ASYNC | SND_FILENAME);
        }
        else if (A[turnx][turny] == ball)
        {
            A[turnx][turny] = ball;
            B[turnx][turny] = ball;
        }
        else if (A[turnx][turny] == 'x')
        {
            A[turnx][turny] = 'x';
            B[turnx][turny] = 'x';
        }
        else
        {
            A[turnx][turny] = '0';
            B[turnx][turny] = '0';
            PlaySound("miss.wav", NULL, SND_ASYNC | SND_FILENAME);
        }
        
        //����� ������� ���������
        
        if (f % 2 != 0 && choice == 2)
    
    {
    
	bool hor = false; 
	bool ver = false;
	 
	//��������� ��� ���������� 
	 
    generateagainComplex:
		
		turnRandX = 1 + rand() % 10;
	    turnRandY = 1 + rand() % 10;
        
        turnx = turnRandX;
	 	turny = turnRandY;
        
        if (move.find(pair<int, int>(turnx, turny)) != move.end())
        {
		goto generateagainComplex;
		}
		else 
		{
		
        SetConsoleTextAttribute(console, 12);
        cout << playerTwoName << " (��� ����������):\n";
        SetConsoleTextAttribute(console, 10);
        cout << "������: ";
        SetConsoleTextAttribute(console, 11);
        cout << turnx << "\n";
        SetConsoleTextAttribute(console, 10);
        cout << "�������: ";
        SetConsoleTextAttribute(console, 11);
        cout << turny << "\n";
		move.insert(make_pair(turnx, turny));
	    shoot2++;
		}
        
    if (A[turnx][turny] == '#')
        {
            A[turnx][turny] = ball;
            B[turnx][turny] = ball;
            PlaySound("found.wav", NULL, SND_ASYNC | SND_FILENAME);
        }
        else if (A[turnx][turny] == ball)
        {
            A[turnx][turny] = ball;
            B[turnx][turny] = ball;
        }
        else if (A[turnx][turny] == 'x')
        {
            A[turnx][turny] = 'x';
            B[turnx][turny] = 'x';
        }
        else
        {
            A[turnx][turny] = '0';
            B[turnx][turny] = '0';
            PlaySound("miss.wav", NULL, SND_ASYNC | SND_FILENAME);
        }
    
    //���������� ��� ���������� ������� (������������� ��� �����������)
    
    if (A[turnx][turny] == ball) 
    {
    		if (A[turnx][turny-1] == ball || 
	 	    A[turnx][turny+1] == '#' ||
	 	    A[turnx][turny-1] == '#' ||
	  	    A[turnx][turny+1] == ball)
			{    
				hor = true;
    		}
   		 	if (A[turnx-1][turny] == ball || 
	    	A[turnx+1][turny] == '#' ||
	    	A[turnx-1][turny] == '#' ||
	    	A[turnx+1][turny] == ball)
			{     
				ver = true;
    		}
    			if (hor)
    			{
	            	//������
					for (int i = turny; i <= turny + 3; i++)
					{
					if (A[turnx][i] == '?' || A[turnx][i] == '0') break;
					if (A[turnx][i+1] == '#') shoot2++;
				    A[turnx][i] = ball; 
					}
					//����� 
					for (int i = turny; i >= turny - 3; i--)
					{
					if (A[turnx][i] == '?' || A[turnx][i] == '0') break;
					if (A[turnx][i-1] == '#') shoot2++;
				    A[turnx][i] = ball; 
					} 
 				}
 				if (ver)
    			{
	            	//����
					for (int i = turnx; i <= turnx + 3; i++)
					{
					if (A[i][turny] == '?' || A[i][turny] == '0') break;
					if (A[i+1][turny] == '#') shoot2++;
				    A[i][turny] = ball; 
					}
					//����� 
					for (int i = turnx; i >= turnx - 3; i--)
					{
					if (A[i][turny] == '?' || A[i][turny] == '0') break;
					if (A[i-1][turny] == '#') shoot2++;
				    A[i][turny] = ball; 
					} 
 				}
    }
    
} //����� �������� ����������   

        //����� ������� �� ������� � ����� ��������� ���������� ����������

        if ((A[turnx - 1][turny] == '?' && A[turnx + 1][turny] == '?')
            || (A[turnx - 1][turny] == '0' && A[turnx + 1][turny] == '?')
            || (A[turnx - 1][turny] == '?' && A[turnx + 1][turny] == '0')
            || (A[turnx - 1][turny] == '0' && A[turnx + 1][turny] == '0'))

        {
            //�������������� ������

            for (int i = 0; i < N; i++)
            {
                t = 0;
            againHor:
                k = 0;
                for (int j = t; j < N; j++)
                {
                    if (A[i][j] == ball)

                        if ((A[i][j - 1] != '?' || A[i][j + 1] != '?')
                            && (A[i][j - 1] != '0' || A[i][j + 1] != '?')
                            && (A[i][j - 1] != '?' || A[i][j + 1] != '0')
                            && (A[i][j - 1] != '0' || A[i][j + 1] != '0'))
                        {
                            turnx = i;
                            turny = j;
                            for (int p = 0; p <= 3; p++)
                            {
                                if (A[i][turny + p] == ball)
                                    k++;
                                else
                                    break;
                            }
                            if (A[turnx][turny - 1] != '#' && A[turnx][turny + k] != '#')
                            {
                                for (int j = turny; j <= turny + k - 1; j++)
                                {
                                    A[turnx][j] = 'x';
                                    B[turnx][j] = 'x';
                                    if (f % 2 == 0)
                                        totalOne++;
                                    else
                                        totalTwo++;
                                    move.insert(make_pair(turnx, j));
                                }
                                PlaySound("destroyed.wav", NULL, SND_ASYNC | SND_FILENAME);
                                break;
                            }
                            else
                            {
                                t = turny + k;
                                goto againHor;
                            }
                        }
                }
            }
            //����� ��������������� �������
        }

        if ((A[turnx][turny - 1] == '?' && A[turnx][turny + 1] == '?')
            || (A[turnx][turny - 1] == '0' && A[turnx][turny + 1] == '?')
            || (A[turnx][turny - 1] == '?' && A[turnx][turny + 1] == '0')
            || (A[turnx][turny - 1] == '0' && A[turnx][turny + 1] == '0'))
        {

            //������������ ������

            for (int j = 0; j < N; j++)
            {
                t = 0;
            againVer:
                k = 0;
                for (int i = t; i < N; i++)
                {
                    if (A[i][j] == ball)
                        if ((A[i - 1][j] != '?' || A[i + 1][j] != '?')
                            && (A[i - 1][j] != '0' || A[i + 1][j] != '?')
                            && (A[i - 1][j] != '?' || A[i + 1][j] != '0')
                            && (A[i - 1][j] != '0' || A[i + 1][j] != '0'))
                        {
                            turnx = i;
                            turny = j;
                            for (int p = 0; p <= 3; p++)
                            {
                                if (A[turnx + p][j] == ball)
                                    k++;
                                else
                                    break;
                            }
                            if (A[turnx - 1][turny] != '#' && A[turnx + k][turny] != '#')
                            {
                                for (int i = turnx; i <= turnx + k - 1; i++)
                                {
                                    A[i][turny] = 'x';
                                    B[i][turny] = 'x';
                                    if (f % 2 == 0)
                                        totalOne++;
                                    else
                                        totalTwo++;
                                    move.insert(make_pair(i, turny));
                                }
                                PlaySound("destroyed.wav", NULL, SND_ASYNC | SND_FILENAME);
                                break;
                            }
                            else
                            {
                                t = turnx + k;
                                goto againVer;
                            }
                        }
                }
            }
            //����� ������������� �������
        }

        //������ ��� ����� ������ (�������������� ������)

        for (int i = 1; i < N - 1; i++)
        {
            for (int j = 1; j < N - 1; j++)
            {
                if (A[i][j] == ball)

                    if ((A[i - 1][j] != '#' && A[i - 1][j] != ball)
                        && (A[i + 1][j] != '#' && A[i + 1][j] != ball)
                        && (A[i][j - 1] != '#' && A[i][j - 1] != ball)
                        && (A[i][j + 1] != '#' && A[i][j + 1] != ball))
                    {
                        A[i][j] = 'x';
                        B[i][j] = 'x';
                        if (f % 2 == 0)
                            totalOne++;
                        else
                            totalTwo++;
                        PlaySound("destroyed.wav", NULL, SND_ASYNC | SND_FILENAME);
                    }
            }
        }

        Sleep(compSpeed);
        system("cls");
        wr = 0;
        printOutput(B); //������ �������� ����������
        if (wr == 20)
        {
            total = shoot1 + shoot2;
            break;
        }
    }
      
    /*
	//�������� ��������

    int etalon = 0;
    for (int i = 1; i < N - 1; i++)
    {
        for (int j = 1; j < N - 1; j++)
        {
            if (A[i][j] == '?')
                etalon++;
        }
    }
    SetConsoleTextAttribute(console, 14);
	cout << "\n���� ��������!\n";
    SetConsoleTextAttribute(console, 11);
	cout << "\n����� ����� �������: " << total << "/100" << ": " << 100 - total << " = " << etalon << "\n\n";
	} //��������� ��������
	*/
	
	//����� ����
    
	SetConsoleTextAttribute(console, 14);
    cout << "\n���� ��������!\n\n";
    
    SetConsoleTextAttribute(console, 11);
    cout << "����� ����� �������: "; 
    
    SetConsoleTextAttribute(console, 15);
	cout << total << "/100" << "\n\n";

    //����� 1
 
    SetConsoleTextAttribute(console, 10);
	cout << playerOneName << ":\n";
	
	SetConsoleTextAttribute(console, 11);
    cout << "������� �������: ";
    
    SetConsoleTextAttribute(console, 15);
	cout << shoot1 << "\n";
	
	SetConsoleTextAttribute(console, 11);
    cout << "������� ������� ������: ";
    
    SetConsoleTextAttribute(console, 15);
    cout << totalOne << "\n\n";

    //����� 2

    SetConsoleTextAttribute(console, 10);
	cout << playerTwoName << ":\n";
	
	SetConsoleTextAttribute(console, 11);
    cout << "������� �������: ";
    
    SetConsoleTextAttribute(console, 15);
	cout << shoot2 << "\n";
	
	SetConsoleTextAttribute(console, 11);
    cout << "������� ������� ������: ";
    
	SetConsoleTextAttribute(console, 15);
	cout << totalTwo << "\n\n";

    //���������� ����� ����
    
    snowman1 = totalOne / 3;
    rem1 = totalOne % 3;
    
    snowman2 = totalTwo / 3;
    rem2 = totalTwo % 3;

    SetConsoleTextAttribute(console, 14);
	cout << "���� ����:\n\n";
	
	//���� 1
	
    SetConsoleTextAttribute(console, 11);
	cout << playerOneName << " ������ ������� ����������: ";
	
	SetConsoleTextAttribute(console, 15); 
	cout << snowman1 << "\n";
    
    SetConsoleTextAttribute(console, 11);
	cout << playerOneName << " ����� � ������ ������� ������: ";
	
	SetConsoleTextAttribute(console, 15);
	cout << rem1 << "\n\n";
    
    //���� 2
    
    SetConsoleTextAttribute(console, 11);
	cout << playerTwoName << " ������ ������� ����������: ";
	
	SetConsoleTextAttribute(console, 15); 
	cout << snowman2 << "\n";
    
    SetConsoleTextAttribute(console, 11);
	cout << playerTwoName << " ����� � ������ ������� ������: ";
	
	SetConsoleTextAttribute(console, 15);
	cout << rem2 << "\n\n";

    PlaySound("endofgame.wav", NULL, SND_ASYNC | SND_FILENAME); //������� ��� ���������� ����
    SetConsoleTextAttribute(console, 10);
    
    system("pause");
    return 0;
}
