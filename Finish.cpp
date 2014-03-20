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
    int where;
    char wayToFile[256];
    char enterNumber;

    while(true)
    {
        system("cls");

        cout << "Hello!\nIf You want to: "<<endl;
        cout << "   Exit, please, press <0>\n";
        cout << "   Create new CandidatsList, please, press <1>\n";
        cout << "   Add new Candidat to existing DataBase, please, press <2>\n";
        cout << "   Open and show the existing DataBase, please, press <3>\n";
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
            newCandidatsList( List, 0, quanOfCandidats, wayToFile);
            system("pause");
        }
        if( enterNumber == '2')
        {
            system("cls");
            cout << "Enter the quantity of added Candidats: " << endl;
            cin >> quanOfAddedCandidats;
            cout << "Enter the index, where you want to save your new Candidats: " << endl;
            cin >> where;
            addCandidat( List, quanOfAddedCandidats, quanOfCandidats, where);
            system("pause");

            fstream info;
            info.open("CandidatsList.txt",ios::out|ios::binary|ios::trunc);
            info.write((char *)List, quanOfCandidats*sizeof( CandidatsList)) << "\n";
            info.close();
        }
        if( enterNumber == '3')
        {
            system("cls");
            cout << "This is the existing DataBase:\n";
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

void newCandidatsList(struct CandidatsList *List, int CandidatsList, const int quanOfCandidats, char wayToFile[])
{
    cin.ignore(1,'\n');
    for(int i = 0; i < quanOfCandidats; ++i)
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

    cout << "Enter The Way To File Where You Want To Save The Information:\n";
    cin.getline( wayToFile, 255 ,'\n');
    fstream info(wayToFile,ios::out|ios::binary|ios::trunc);
    info.write((char *)List ,quanOfCandidats*sizeof( CandidatsList)) << "\n";
    info.close();

}

void addCandidat(struct CandidatsList *List, int quanOfAddedCandidats, int quanOfCandidats, int where)
{
    cin.ignore(1,'\n');
    for( int i = where; i < quanOfCandidats; ++i)
    {
        cout << "Enter Surname Of Candidat: ";
        cin.getline(List[i].surnameOfCandidat, 20);
        cout<<endl;

        cout << "Enter Number Of Electoral District: ";
        cin.getline(List[i].numberOfElectoralDistrict, 10);
        cout<<endl;

        cout << "Enter Name Of Electoral District: ";
        cin.getline(List[i].nameOfElectoralDistrict, 30);
        cout<<endl;

        cout << "Quantity Of Signatures: ";
        cin.getline(List[i].quantityOfSignatures, 10);
        cout<<endl;
    }
    fstream fout("CandidatsList.txt", ios::out|ios::binary|ios::trunc);
    fout.write((char *)List, sizeof( CandidatsList)) << "\n";
    fout.close();
}

void showCandidatsList(struct CandidatsList *List, int quanOfCandidats)
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



void Repair(struct CandidatsList *List, int i, int quanOfCandidats, int (*fptr)( CandidatsList, CandidatsList))
{
    int n = quanOfCandidats;

    CandidatsList *help;

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
        *help = List[larg];
        List[larg] = List[i];
        List[i] = *help;
        Repair ( List, larg, quanOfCandidats, (*fptr));
    }
}

void Build (struct CandidatsList *List, int quanOfCandidats, int (*fptr)( CandidatsList, CandidatsList))
{
    int n = quanOfCandidats;
    for( int i = n/2; i >= 0; --i)
    {
        Repair( List, i, quanOfCandidats, (*fptr));
    }
}

void Sort(struct CandidatsList *List, int quanOfCandidats, int (*fptr)( CandidatsList, CandidatsList))
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

void outFront( struct CandidatsList *List, int quanOfCandidats)
{
    for( int i = 0; i < quanOfCandidats; ++i)
    {
        cout << List[i].surnameOfCandidat << endl;
        cout << List[i].numberOfElectoralDistrict << endl;
        cout << List[i].nameOfElectoralDistrict << endl;
        cout << List[i].quantityOfSignatures << endl;
        cout << endl;
    }
}

void outBack( struct CandidatsList *List, int quanOfCandidats)
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

void sortDataBase(struct CandidatsList *List, int quanOfCandidats)
{
    CandidatsList *one = new CandidatsList [22];
    typedef int (*pointer)(CandidatsList, CandidatsList);
    pointer *point;
    point = new pointer[4];
    point[0] = sortBySurnameOfCandidat;
    point[1] = sortByNumberOfElectoralDistrict;
    point[2] = sortByNameOfElectoralDistrict;
    point[3] = sortByQuantityOfSignatures;


    cout << "Welcome To Sorting Program For Existing DataBase!" << endl;
    cout << "If You want to sort the DataBase ";

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
        Sort ( one, quanOfCandidats, point[0]);
        outFront( one, quanOfCandidats);

    }
    if( enterNumber == '2')
    {
        Sort ( one, quanOfCandidats, point[0]);
        outBack( one, quanOfCandidats);
    }
    if( enterNumber == '3')
    {
        Sort ( one, quanOfCandidats, point[1]);
        outFront( one, quanOfCandidats);
    }
    if( enterNumber == '4')
    {
        Sort ( one, quanOfCandidats, point[1]);
        outBack( one, quanOfCandidats);
    }
    if( enterNumber == '5')
    {
        Sort ( one, quanOfCandidats, point[2]);
        outFront( one, quanOfCandidats);
    }
    if( enterNumber == '6')
    {
        Sort ( one, quanOfCandidats, point[2]);
        outBack( one, quanOfCandidats);
    }
    if( enterNumber == '7')
    {
        Sort ( one, quanOfCandidats, point[3]);
        outFront( one, quanOfCandidats);
    }
    if( enterNumber == '7')
    {
        Sort ( one, quanOfCandidats, point[3]);
        outBack( one, quanOfCandidats);
    }
    delete []point;
    delete []one;
    return;
}

int sortBySurnameOfCandidat(struct CandidatsList List1, struct CandidatsList List2)
{
    return strcmp(List1.surnameOfCandidat, List2.surnameOfCandidat);
}

int sortByNumberOfElectoralDistrict(struct CandidatsList List1, struct CandidatsList List2)
{
    return strcmp(List1.numberOfElectoralDistrict, List2.numberOfElectoralDistrict);
}

int sortByNameOfElectoralDistrict(struct CandidatsList List1, struct CandidatsList List2)
{
    return strcmp(List1.nameOfElectoralDistrict, List2.nameOfElectoralDistrict);
}

int sortByQuantityOfSignatures(struct CandidatsList List1, struct CandidatsList List2)
{
    return strcmp(List1.quantityOfSignatures, List2.quantityOfSignatures);
}

