#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DUZINA_IME 21  // maksimalna dužina za ime i prezime (20 + 1 za null terminator)
#define MAX_STUDENTI 100   // pretpostavimo maksimalni broj studenata

typedef struct {
    char ime[MAX_DUZINA_IME];
    char prezime[MAX_DUZINA_IME];
    int godina_studiranja;
    float prosek;
    float poeni;
} Student;

void izracunaj_poene(Student *student, int a, int b) {
    student->poeni = a * student->godina_studiranja + b * student->prosek;
}

int poredi_studente(const void *s1, const void *s2) {
    Student *student1 = (Student *)s1;
    Student *student2 = (Student *)s2;
    if (student1->poeni < student2->poeni) return -1;
    if (student1->poeni > student2->poeni) return 1;
    return 0;
}

int main() {
    FILE *datoteka = fopen("studenti.txt", "r");
    if (datoteka == NULL) {
        perror("Greška pri otvaranju datoteke");
        return 1;
    }

    int broj_studenata;
    fscanf(datoteka, "%d", &broj_studenata);
    fgetc(datoteka); // Konsumiraj znak novog reda posle broja studenata

    Student studenti[MAX_STUDENTI];
    for (int i = 0; i < broj_studenata; ++i) {
        char linija[100];
        fgets(linija, sizeof(linija), datoteka);

        int ocene, broj_ocena;
        sscanf(linija, "%20s %20s %d %d/%d", studenti[i].ime, studenti[i].prezime,
               &studenti[i].godina_studiranja, &ocene, &broj_ocena);

        studenti[i].prosek = (float) ocene / broj_ocena;
    }
    fclose(datoteka);

    int a, b;
    printf("Unesite dva cela broja a i b: ");
    scanf("%d %d", &a, &b);

    for (int i = 0; i < broj_studenata; ++i) {
        izracunaj_poene(&studenti[i], a, b);
    }

    qsort(studenti, broj_studenata, sizeof(Student), poredi_studente);

    printf("Ime i prezime studenata sortirano po poenima:\n");
    for (int i = 0; i < broj_studenata; ++i) {
        printf("%s %s\n", studenti[i].ime, studenti[i].prezime);
    }

    return 0;
}
