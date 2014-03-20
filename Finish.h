#ifndef Finish_H
#define Finish_H

struct CandidatsList
{
    char surnameOfCandidat[20];
    char numberOfElectoralDistrict[10];
    char nameOfElectoralDistrict[30];
    char quantityOfSignatures[10];
};

void myMenu(struct CandidatsList *List, int n);

void newCandidatsList(struct CandidatsList *List, int CandidatsList, const int quanOfCandidats, char wayToFile[]);
void addCandidat(struct CandidatsList *List, int quanOfAddedCandidats, int quanOfCandidats, int where);
void showCandidatsList(struct CandidatsList *List, int quanOfConclCandidats);

void outFront( struct CandidatsList *List, int quanOfCandidats);
void outBack( struct CandidatsList *List, int quanOfCandidats);
void Sort(struct CandidatsList *List, int quanOfCandidats, int (*fptr)( CandidatsList, CandidatsList));
void Build (struct CandidatsList *List, int quanOfCandidats, int (*fptr)( CandidatsList, CandidatsList));
void Repair(struct CandidatsList *List, int i, int quanOfCandidats, int (*fptr)( CandidatsList, CandidatsList));
void sortDataBase(struct CandidatsList *List, int quanOfCandidats);

int sortBySurnameOfCandidat(struct CandidatsList List1, struct CandidatsList List2);
int sortByNumberOfElectoralDistrict(struct CandidatsList List1, struct CandidatsList List2);
int sortByNameOfElectoralDistrict(struct CandidatsList List1, struct CandidatsList List2);
int sortByQuantityOfSignatures(struct CandidatsList List1, struct CandidatsList List2);

#endif
