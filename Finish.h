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

void newCandidatsList(struct CandidatsList *List, int Candidats, const int quanOfCandidats);
void addCandidat(struct CandidatsList *List, int quanOfAddedCandidats, const int quanOfCandidats, int where);
void showCandidatsList(struct CandidatsList *List, const int quanOfConclCandidats);

void outFront( struct CandidatsList *List, const int quanOfCandidats);
void outBack( struct CandidatsList *List, const int quanOfCandidats);
void Sort(struct CandidatsList *List, const int quanOfCandidats, int (*fptr)( CandidatsList, CandidatsList));
void Build (struct CandidatsList *List, const int quanOfCandidats, int (*fptr)( CandidatsList, CandidatsList));
void Repair(struct CandidatsList *List, int i, const int quanOfCandidats, int (*fptr)( CandidatsList, CandidatsList));
void sortDataBase(struct CandidatsList *List, const int quanOfCandidats);

int sortBySurnameOfCandidat(struct CandidatsList List1, struct CandidatsList List2);
int sortByNumberOfElectoralDistrict(struct CandidatsList List1, struct CandidatsList List2);
int sortByNameOfElectoralDistrict(struct CandidatsList List1, struct CandidatsList List2);
int sortByQuantityOfSignatures(struct CandidatsList List1, struct CandidatsList List2);

#endif
