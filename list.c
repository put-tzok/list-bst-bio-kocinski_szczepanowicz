

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned int ns[] = { 1000,5000, 10000, 20000, 30000, 37500,40000, 47500, 60000  };

// each list node contains an integer key value and pointer to next list node
struct node {
    int key;
    struct node *next;
};

// list's beginning is called the head of list
struct node *head = NULL;
struct node* inter;// towrzy obiekt struktury inter do przechowywania wartoœci

struct node* list_insert(int value) {
  struct node * nowy= malloc(sizeof(*nowy));//tworzy dynamicznie obiekt struktury
   nowy->key= value;// przypisuje wartoœci key w nowym obiekcie wartoœæ value
   nowy->next=head;// ustawia head jako nastepny element
    head=nowy;// ustawia obiekt nowy jako head
    return nowy;
return NULL;
}

struct node* list_search(int value) {

    inter=head;// ustawia inter jako pierwszy element listy
    while (inter!=NULL && inter->key!=value)//dopóki inter jest różna od zera i inter.key jest różne od wartości
        inter=inter->next;// inter przesuwa sie na następny element tablicy
    return inter;// zwraca wartość inter
    return NULL;
}

void list_delete(int value) {
   if(head->key==value)// jeśli key od głowy równa się value
    head=head->next;// przesuwa sie na następny element tablicy
   else
   {
       struct node * prev=head;// tworzy nowy obiekt prev i ustawia go jako głowe
       inter=head->next;//ustwia inter jako nastepny element po głowie
       while(inter!=NULL && inter->key!=value)// dopóki inter jest różny od 0 i inter.key jest rożny od value
        {
            prev=inter;
            inter=inter->next;// przesuwamy inter na kolejny element listy
        }
       if (inter!=NULL) // jeśli w else inter nie jest 0 to
        prev->next=inter->next;//prev.next ustawia jako inter.next
   }
}

unsigned int list_size() {
int size=0;//tworzy inta size i ustawia jako zero
inter=head;// ustawia inter jako głowe
while(inter!=NULL)// dopóki inter jest różny od 0
  {
   size=size+1;
inter=inter->next;// inter ustawia jako nastepny element po nim
  }

    return size;
}

/*
 * Fill an array with increasing values.
 *
 * Parameters:
 *      int *t:     pointer to the array
 *      int n:      number of elements in the array
 */
void fill_increasing(int *t, int n) {
    for (int i = 0; i < n; i++) {
        t[i] = i;
    }
}

/*
 * Reorder array elements in a random way.
 *
 * Parameters:
 *      int *t:     pointer to the array
 *      int n:      number of elements in the array
 */
void shuffle(int *t, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % i;
        int temp = t[i];
        t[i] = t[j];
        t[j] = temp;
    }
}

int main() {
    bool no_yes[] = { false, true };

    for (unsigned int i = 0; i < sizeof(no_yes) / sizeof(*no_yes); i++) {
        bool enable_shuffle = no_yes[i];

        for (unsigned int j = 0; j < sizeof(ns) / sizeof(*ns); j++) {
            unsigned int n = ns[j];

            // always create an array of size `n` and fill it with increasing values
            int *t = malloc(n * sizeof(*t));
            fill_increasing(t, n);

            // if true, reorder array elements randomly
            if (enable_shuffle) {
                shuffle(t, n);
            }

            // insert elements in the order present in array `t`
            clock_t insertion_time = clock();
            for (unsigned int k = 0; k < n; k++) {
                struct node *iter = list_insert(t[k]);
                assert(iter != NULL);       // inserted element cannot be NULL
                assert(iter->key == t[k]);  // inserted element must contain the expected value
            }
            insertion_time = clock() - insertion_time;

            // reorder array elements before searching
            shuffle(t, n);

            // search for every element in the order present in array `t`
            clock_t search_time = clock();
            for (unsigned int k = 0; k < n; k++) {
                struct node *iter = list_search(t[k]);
                assert(iter != NULL);       // found element cannot be NULL
                assert(iter->key == t[k]);  // found element must contain the expected value
            }
            search_time = clock() - search_time;

            // reorder array elements before deletion
            shuffle(t, n);

            // delete every element in the order present in array `t`
            for (unsigned int k = 0, l = n; k < n; k++, l--) {
                assert(list_size() == l);   // list size must be equal to the expected value
                list_delete(t[k]);
            }
            assert(list_size() == 0);       // after all deletions, the list size is zero
            assert(head == NULL);           // after all deletions, the list's head is NULL

            free(t);

            printf("%d\t%s\t%f\t%f\n", n, enable_shuffle ? "true" : "false",
                    (double)insertion_time / CLOCKS_PER_SEC,
                    (double)search_time / CLOCKS_PER_SEC);
        }
    }
    return 0;
}



