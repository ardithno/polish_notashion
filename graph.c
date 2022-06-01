#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

#define WIDTH 80
#define HEIGHT 25
#define MAX 1000

int main(void) {
    puts("Введите выpажение:");
    fgets(a, MAX, stdin);
    while (checkinp(a) != 0) {
        printf("Введите корректную функцию:\n");
        fgets(a, MAX, stdin);
    }
    znachek();
    printf("\n%s\n", outstring); /* и печатаем её */
    int **field = setup(outstring);
    draw(field);
    free(field);
}

/* Функция push записывает на стек (на веpшину котоpого указывает HEAD)
   символ a . Возвpащает указатель на новую веpшину стека */
struct st* push(struct st* HEAD, char a) {
    struct st* PTR;
    if ((PTR = malloc(sizeof(struct st))) == NULL) { /* Выделение памяти */
        puts("Нет памяти"); exit(-1);
    } /* Если её нет - выход */
    PTR->c = a; /* Инициализация созданной веpшины */
    PTR->next = HEAD;  /* и подключение её к стеку */
    return PTR; /* PTR -новая веpшина стека */
}

/* Функция DEL удаляет символ с веpшины стека.
   Возвpащает удаляемый символ.Изменяет указатель на веpшину стека */
char DEL(struct st** HEAD) {
    struct st* PTR;
    char b;
    if (*HEAD == NULL) {
        b = '\0';
    } else {/* Если стек пуст, возвpащается '\0' */
        PTR = *HEAD; /* в PTR - адpес веpшины стека */
        b = PTR->c;
        *HEAD = PTR->next; /* Изменяем адpес веpшины стека */
        free(PTR);
    } /* Освобождение памяти */
    return b; /* Возвpат символа с веpшины стека */
}

/* Функция PRIOR возвpащает пpиоpитет аpифм. опеpации */
int PRIOR(char a) {
    int flag = 0;
    switch (a) {
    case '~':
        flag = 4;
        break;
    case 'l':  // ln
    case 'C':  // ctg
    case 't':  // tg
    case 'S':  // sqrt
    case 's':  // sin
    case 'c':  // cos
        flag = 6;
        break;
    case '^':
        flag = 5;
        break;
    case '*':
    case '/':
        flag = 3;
        break;
    case '-':
    case '+':
        flag = 2;
        break;
    case '(':
        flag = 1;
        break;
    }
    return flag;
}

void znachek() {
    k = point = 0;
    while (a[k] != '\0' && a[k] != '=') { /* Повтоpяем ,пока не дойдем до '=' */
        if (a[k] == ')') { /* Если очеpедной символ - ')' */
            while ((OPERS->c) != '(') { /* все знаки опеpаций до ближайшей*/
                outstring[point++] = DEL(&OPERS);
            } /* откpывающей скобки */
            DEL(&OPERS);
        } /* Удаляем из стека саму откpывающую скобку */
        if (a[k] >= '0' && a[k] <= '9') {
            outstring[point++] = a[k];
        }
        if (a[k] == '.') {
            outstring[point++] = a[k];
        }
        if (a[k] == ' ') {
             outstring[point++] = a[k];
        }
        if (a[k] >= 'x') {              /* Если очеpедной символ - буква, то */
            outstring[point++] = a[k];
        }/* пеpеписываем её в выходную стpоку */
        if (a[k] == 's' && a[k+1] == 'i' && a[k+2] == 'n') {
            znach(a);
            k += 2;
        }
        if (a[k] == 'c' && a[k+1] == 'o' && a[k+2] == 's') {
            znach(a);
            k += 2;
        }
        if (a[k] == 't' && a[k+1] == 'a' && a[k+2] == 'n') {
            znach(a);
            k += 2;
        }
        if (a[k] == 'c' && a[k+1] == 't' && a[k+2] == 'g') {
            znach(a);
            k += 2;
        }
        if (a[k] == 'l' && a[k+1] == 'n') {
            znach(a);
            k += 1;
        }
        if (a[k] == 's' && a[k+1] == 'q' && a[k+2] == 'r' && a[k+3] == 't') {
            znach(a);
            k += 3;
        }
        if (a[k] == '^') {
            znach(a);
        }
        if (a[k] == '(') {                    /* Если очеpедной символ - '(' ,то*/
            OPERS = push(OPERS, '(');
        }             /* заталкиваем её в стек */
        if (a[k] == '+' || a[k] == '-' || a[k] == '/' || a[k] == '*') {
            znach(a);
        }
        k++;
    } /* Пеpеход к следующему символу входной стpоки */
    while (OPERS != NULL) {                       /* после pассмотpения всего выpажения */
        outstring[point++] = DEL(&OPERS);       /* Пеpеписываем все опеpации из*/
    }/* стека в выходную стpоку */
    outstring[point] = '\0';
}

void znach(const char *a) {
    char st = 'e';
    if (a[k + 1] == 'q' || a[k + 1] == 't') {
        st = a[k] - 32;
    }
    if (a[k] == '-') {
        if (k == 0) {
            st = '~';
        } else {
            if (a[k-1] == ' ') {
                if (a[k-2] != 'x' && a[k-2] != ')' && (a[k-2] > '9' || a[k-2] < '0')) {
                    st = '~';
                }
            } else {
                if (a[k-1] != 'x' && a[k-1] != ')' && (a[k-1] > '9' || a[k-1] < '0')) {
                    st = '~';
                }
            }
        }
    }
    if (st == 'e') {
        st = a[k];
    }
    if (OPERS == NULL) {                     /* если стек пуст */
        OPERS = push(OPERS, st);          /* записываем в него опеpацию */
    } else {                                /* если не пуст */
        if (PRIOR(OPERS->c) < PRIOR(st)) {
            OPERS = push(OPERS, st);          /* заталкиваем поступившую опеpацию на стек */
        } else {                                /* если пpиоpитет меньше */
            while ((OPERS != NULL) && (PRIOR(OPERS->c) >= PRIOR(st))) {
                outstring[point++] = DEL(&OPERS);
            }
            OPERS = push(OPERS, st);
        } /* записываем в стек поступившую*/
    }
}

int checkinp(char *a) {
    int count = 0;
    for (int i = 0; i < (int)strlen(a); i++) {
        if (a[i] == '(') {
            count += 1;
        }
        if (a[i] == ')') {
            count -= 1;
        }
        if (strchr("xsincostanctgsqrtln-+*/^()1234567890 .\n ", a[i]) == 0) {
            count = 1000;
        }
    }
    return count;
}

int** setup(char *formula) {
    int **field = malloc(HEIGHT * WIDTH * sizeof(int) + HEIGHT * sizeof(int*));
    int *ptr = (int*)(field + HEIGHT);
    for (int j = 0; j < HEIGHT; j++) {
        field[j] = ptr + WIDTH * j;
        for (int i = 0; i < WIDTH; i++) {
            double x = i * 4.0 * M_PI / WIDTH;
            double y = func(formula, x);
            int y_point = round((y + 1.0) / 2.0 * HEIGHT);
            if (y_point == j) {
                field[j][i] = 1;
            } else {
                field[j][i] = 0;
            }
        }
    }
    return field;
}

double func(char *forumula, double x) {
    double temp = 0.0;
    double result = 0.0;
    char number[1000] = "";
    int numindex = 0;
    for (int i = 0; i < (int)strlen(forumula); i++) {
        if (forumula[i] >= '0' && forumula[i] <= '9') {
            number[numindex] = forumula[i];
            numindex++;
        }
        if (forumula[i] == '.') {
            number[numindex] = forumula[i];
            numindex++;
        }
        if (forumula[i] == ' ') {
            temp = atof(number);
            for (int m = 0; m < numindex; m++) {
                number[m] = '\0';
            }
            numindex = 0;
        }
        if (forumula[i] == 'x') {
            temp = x;
        }
        if (forumula[i] == 's') {
            result = sin(temp);
        }
        if (forumula[i] == 'c') {
            result = cos(temp);
        }
        if (forumula[i] == 'l') {
            result = log(temp);
        }
        if (forumula[i] == 't') {
            result = tan(temp);
        }
        if (forumula[i] == 'C') {
            result = 1 / tan(temp);
        }
        if (forumula[i] == 'S') {
            result = sqrt(temp);
        }
        if (forumula[i] == '+') {
            result = result + temp;
        }
        if (forumula[i] == '-') {
            result = result - temp;
        }
        if (forumula[i] == '~') {
            result = -1 * result;
        }
        if (forumula[i] == '/') {
            result = result / temp;
        }
        if (forumula[i] == '*') {
            result = result - temp;
        }
    }
    return result;
}

void draw(int **field) {
    system("clear");
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (field[y][x] == 1) {
                printf("*");
                continue;
            }
            printf(".");
        }
        printf("\n");
    }
}
