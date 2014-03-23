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

void addCandidats(struct CandidatsList *List, int Candidats, const int quanOfCandidats);
void showCandidatsList(struct CandidatsList *List, const int quanOfConclCandidats);

void outFront( struct CandidatsList *List, const int quanOfCandidats);
void outBack( struct CandidatsList *List, const int quanOfCandidats);
void Sort(struct CandidatsList *List, const int quanOfCandidats, int (*fptr)( CandidatsList, CandidatsList));
void sortDataBase(struct CandidatsList *List, const int quanOfCandidats);

int compareBySurnameOfCandidat(struct CandidatsList List1, struct CandidatsList List2);
int compareByNumberOfElectoralDistrict(struct CandidatsList List1, struct CandidatsList List2);
int compareByNameOfElectoralDistrict(struct CandidatsList List1, struct CandidatsList List2);
int compareByQuantityOfSignatures(struct CandidatsList List1, struct CandidatsList List2);

#endif
