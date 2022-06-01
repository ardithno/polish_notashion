#ifndef SRC_GRAPH_H_
#define SRC_GRAPH_H_

struct st                 /* Описание стpуктуpы(элемента стека) */
{
    char c; struct st* next;
};
struct st* push(struct st*, char);  /* Пpототипы функций */
char DEL(struct st**);
int PRIOR(char);
void znach(const char *a);
void znachek();
int checkinp(char *a);
int rezult(char *a);

int** setup(char *formula);
double func(char *formula, double x);
void draw(int **field);

struct st* OPERS = NULL;                  /* Стек опеpаций пуст */
char a[80], outstring[80];
int k, point;

#endif  // SRC_GRAPH_H_
