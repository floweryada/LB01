#include "Finish.h"
#include <fstream>
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstring>

using namespace std;

void myMenu(struct CandidatsList *List, int n)
{
    int quanOfCandidats;
    int quanOfAddedCandidats;
    char enterNumber;

    while(true)
    {
        system("cls");

        cout << "Hello!\nIf You want to: "<<endl;
        cout << "   Exit, please, press <0>\n";
        cout << "   Create new CandidatsList, please, press <1>\n";
        cout << "   Add new Candidats to existing DataBase, please, press <2>\n";
        cout << "   Show the existing DataBase, please, press <3>\n";
        cout << "   Sort the existing DataBase, please, press <4>\n";

        cin >> enterNumber;

        if( enterNumber == '0')
        {
            system("cls");
            exit(0);
        }

        if( enterNumber == '1')
        {
            system("cls");
            cout << "Enter quantity of Candidats (less than 20):\t";
            cin >> quanOfCandidats;
            fstream inf("quanOfCandidats.txt",ios::out|ios::binary|ios::trunc);
            inf.write((char *)&quanOfCandidats,sizeof(int)) << "\n";
            inf.close();

            addCandidats( List, 0, quanOfCandidats);
            fstream info;
            info.open ("CandidatsList.txt", ios::out|ios::binary|ios::trunc);
            info.write((char *)List, quanOfCandidats*sizeof( CandidatsList)) << "\n";
            info.close();
            system("pause");
        }
        if( enterNumber == '2')
        {
            system("cls");
            cout << "Enter the quantity of added Candidats: " << endl;
            cin >> quanOfAddedCandidats;

            addCandidats(List,quanOfCandidats,quanOfCandidats+quanOfAddedCandidats);
            quanOfCandidats+=quanOfAddedCandidats;
            fstream inf("quanOfCandidats.txt",ios::out|ios::binary|ios::trunc);
            inf.write((char *)&quanOfCandidats,sizeof(int)) << "\n";
            inf.close();
            system("pause");
        }
        if( enterNumber == '3')
        {
            system("cls");

            fstream fin("quanOfCandidats.txt",ios::in);
            fin.read((char *)&quanOfCandidats,sizeof(int));
            fin.close();

            cout << endl;
            cout << "This is the existing DataBase:\n" << endl;
            showCandidatsList( List, quanOfCandidats);
            system("pause");
        }
        if( enterNumber == '4')
        {
            system("cls");
            sortDataBase( List, quanOfCandidats);
            system("pause");
        }

    }
}

void addCandidats(struct CandidatsList *List, int Candidats, const int quanOfCandidats)
{
    cin.ignore(1,'\n');
    for(int i = Candidats; i < quanOfCandidats; ++i)
    {
        cout << "Enter Surname Of Candidat: ";
        cin.getline(List[i].surnameOfCandidat, 20);

        cout << "Enter Number Of Electoral District: ";
        cin.getline(List[i].numberOfElectoralDistrict, 10);

        cout << "Enter Name Of Electoral District: ";
        cin.getline(List[i].nameOfElectoralDistrict, 30);

        cout << "Quantity Of Signatures: ";
        cin.getline(List[i].quantityOfSignatures, 10);
        cout << endl;
    }
}

void showCandidatsList(struct CandidatsList *List, const int quanOfCandidats)
{
    cin.ignore(1,'\n');
    for( int i = 0; i < quanOfCandidats; ++i)
    {
        cout << List[i].surnameOfCandidat << "\n";
        cout << List[i].numberOfElectoralDistrict << "\n";
        cout << List[i].nameOfElectoralDistrict << "\n";
        cout << List[i].quantityOfSignatures << "\n";
        cout << endl;
    }
}



void Repair(struct CandidatsList *List, int i, const int quanOfCandidats, int (*fptr)( CandidatsList, CandidatsList))
{
    int n = quanOfCandidats;

    CandidatsList help;

    int l = 2*i+1;
    int r = 2*i+2;
    int larg = i;

    if( l <= n && (*fptr)(List[l], List[i])>0)
    {
        larg = l;
    }
    if( r <= n && (*fptr)(List[i], List[l]) > 0 && (*fptr)(List[i], List[r]) < 0)
    {
        larg = r;
    }

    if( larg != i)
    {
        help = List[larg];
        List[larg] = List[i];
        List[i] = help;
        Repair ( List, larg, quanOfCandidats, (*fptr));
    }
}

void Build (struct CandidatsList *List, const int quanOfCandidats, int (*fptr)( CandidatsList, CandidatsList))
{
    int n = quanOfCandidats;
    for( int i = n/2; i >= 0; --i)
    {
        Repair( List, i, quanOfCandidats, (*fptr));
    }
}

void Sort(struct CandidatsList *List, const int quanOfCandidats, int (*fptr)( CandidatsList, CandidatsList))
{
    CandidatsList *help;
    int n = quanOfCandidats;
    for( int i = n-1; i >= 1; --i)
    {
        Build( List, quanOfCandidats, (*fptr));
        int l = 2*i+1;
        int r = 2*i+2;
        int larg = i;
        if(l <= n && (*fptr)(List[l], List[i])>0)
        {
            larg = l;
        }
        if(r <= n && (*fptr)(List[i], List[l]) > 0 && (*fptr)(List[i], List[r]) < 0)
        {
            larg = r;
        }

        *help = List[larg];
        List[larg] = List[i];
        List[i] = *help;
        --n;
        Repair( List, larg, quanOfCandidats, (*fptr));
    }
}

void outFront( struct CandidatsList *List, const int quanOfCandidats)
{
    cin.ignore(1,'\n');
    for( int i = 0; i < quanOfCandidats; ++i)
    {
        cout << List[i].surnameOfCandidat << endl;
        cout << List[i].numberOfElectoralDistrict << endl;
        cout << List[i].nameOfElectoralDistrict << endl;
        cout << List[i].quantityOfSignatures << endl;
        cout << endl;
    }
}

void outBack( struct CandidatsList *List, const int quanOfCandidats)
{
    cin.ignore(1,'\n');
    for( int i = quanOfCandidats-1; i >= 0 ; --i)
    {
        cout << List[i].surnameOfCandidat << endl;
        cout << List[i].numberOfElectoralDistrict << endl;
        cout << List[i].nameOfElectoralDistrict << endl;
        cout << List[i].quantityOfSignatures << endl;
        cout << endl;
    }
}

void sortDataBase(struct CandidatsList *List, const int quanOfCandidats)
{
    CandidatsList *one = new CandidatsList [20];
    typedef int (*pointer)(CandidatsList, CandidatsList);
    pointer *point;
    point = new pointer[4];
    point[0] = compareBySurnameOfCandidat;
    point[1] = compareByNumberOfElectoralDistrict;
    point[2] = compareByNameOfElectoralDistrict;
    point[3] = compareByQuantityOfSignatures;

    cout << "Welcome To Sorting Program For Existing DataBase!" << endl;
    cout << "If You want to sort the DataBase " << endl;

    cout << "   From A till Z by surname of candidat, please, press <1>";
    cout << endl;
    cout << "   From Z till A by surname of candidat, please, press <2>";
    cout << endl;

    cout << "   From A till Z by number of electoral district, please, press <3>";
    cout << endl;
    cout << "   From Z till A by number of electoral district, please, press <4>";
    cout << endl;

    cout << "   From A till Z by name of electoral district, please, press <5>";
    cout << endl;
    cout << "   From Z till A by name of electoral district, please, press <6>";
    cout << endl;

    cout << "   From A till Z by quantity of signatures, please, press <7>";
    cout << endl;
    cout << "   From Z till A by quantity of signatures, please, press <8>";
    cout << endl;

    int enterNumber = getch();

    if( enterNumber == '1')
    {
        system("cls");
        Sort ( one, quanOfCandidats, point[0]);
        outFront( one, quanOfCandidats);
        system("pause");

    }
    if( enterNumber == '2')
    {
        system("cls");
        Sort ( one, quanOfCandidats, point[0]);
        outBack( one, quanOfCandidats);
        system("pause");
    }
    if( enterNumber == '3')
    {
        system("cls");
        Sort ( one, quanOfCandidats, point[1]);
        outFront( one, quanOfCandidats);
        system("pause");
    }
    if( enterNumber == '4')
    {
        system("cls");
        Sort ( one, quanOfCandidats, point[1]);
        outBack( one, quanOfCandidats);
        system("pause");
    }
    if( enterNumber == '5')
    {
        system("cls");
        Sort ( one, quanOfCandidats, point[2]);
        outFront( one, quanOfCandidats);
        system("pause");
    }
    if( enterNumber == '6')
    {
        system("cls");
        Sort ( one, quanOfCandidats, point[2]);
        outBack( one, quanOfCandidats);
        system("pause");
    }
    if( enterNumber == '7')
    {
        system("cls");
        Sort ( one, quanOfCandidats, point[3]);
        outFront( one, quanOfCandidats);
        system("pause");
    }
    if( enterNumber == '7')
    {
        system("cls");
        Sort ( one, quanOfCandidats, point[3]);
        outBack( one, quanOfCandidats);
        system("pause");
    }
    delete []point;
    delete []one;
    return;
}

int compareBySurnameOfCandidat(struct CandidatsList List1, struct CandidatsList List2)
{
    return strcmp(List1.surnameOfCandidat, List2.surnameOfCandidat);
}

int compareByNumberOfElectoralDistrict(struct CandidatsList List1, struct CandidatsList List2)
{
    return strcmp(List1.numberOfElectoralDistrict, List2.numberOfElectoralDistrict);
}

int compareByNameOfElectoralDistrict(struct CandidatsList List1, struct CandidatsList List2)
{
    return strcmp(List1.nameOfElectoralDistrict, List2.nameOfElectoralDistrict);
}

int compareByQuantityOfSignatures(struct CandidatsList List1, struct CandidatsList List2)
{
    return strcmp(List1.quantityOfSignatures, List2.quantityOfSignatures);
}

