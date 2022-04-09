#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFMAX 1005

typedef struct node {
    char data;
    char *sdata;
    struct node *prev;
    struct node *next;
} node;
typedef struct Stack {
    node *top;
    int len;
} Stack;

//initializare stack
void initS(Stack **s) {
    (*s) = (Stack *) malloc(sizeof(Stack));
    (*s)->len = 0;
    (*s)->top = NULL;
}

int add_stack(Stack *s, char *val) {
    //adaugam top-ul daca lungimea e zero
    if (s->len == 0) {
        node *newNode;
        newNode = (node *) malloc(sizeof(node));
        newNode->sdata = val;
        s->top = newNode;
        s->len++;
        return 1;
    }
    //adaugam nod 
    node *newNode;
    newNode = (node *) malloc(sizeof(node));
    newNode->sdata = val;
    newNode->next = s->top;
    s->top = newNode;
    s->len++;
    return 1;
}

int pop_stack(Stack *s) {
    if (s->top->next == NULL) {
        s->top = NULL;
        return 0;
    }
    if (s->top == NULL)
        return 0;
    node *current;
    current = s->top;
    s->top = s->top->next;
    free(current);
    s->len--;
    return 1;
}

void freeS(Stack **s) {
    Stack *varfulStivei = (*s);
    node *nodulCurent;
    nodulCurent = varfulStivei->top;
    varfulStivei->top->next = NULL;
    varfulStivei->len = 0;
    free(varfulStivei);

    if (nodulCurent == NULL || nodulCurent->next==NULL)
        return;

    node *nextNode = nodulCurent->next;

    while (nextNode != NULL) {
        free(nodulCurent->sdata);
        free(nodulCurent);
        nodulCurent = nextNode;
        nextNode = nextNode->next;
    }
    free(nodulCurent->sdata);
    free(nodulCurent);
    
}

typedef struct TDoubleLinkedList {
    node *cursor;
    node *head;
    node *tail;
    int len;
} TDoubleLinkedList;

void init(TDoubleLinkedList **list) {
    (*list) = (TDoubleLinkedList *) malloc(
            sizeof(TDoubleLinkedList));
    (*list)->tail = NULL;
    (*list)->len = 0;
    (*list)->head = NULL;
    (*list)->cursor = NULL;
}

int length(TDoubleLinkedList *list) {
    return list->len;
}

void print(TDoubleLinkedList *list, FILE* dest) {
    node *current = list->head;
    int i=0;
    for (; i <= list->len - 1; i++) {
        fprintf(dest, "%c", current->data);
        current = current->next;
    }
}

void print_reversed(TDoubleLinkedList *list) {
    node *current = list->tail;
    int i=0;
    for (; i < list->len; i++) {
        printf("%c ", current->data);
        current = current->prev;
    }
}

void printS(Stack *s) {
    node *current = s->top;
    int i=0;
    for (; i < s->len; i++) {
        printf("%s", current->sdata);
        current = current->next;
    }
}

int is_empty(Stack *s) {
    if (s->len == 0)
        return 1;
    return 0;
}

int add(TDoubleLinkedList *list, char data, node *cursor) {
    if (list->len == 0) {
        node *newNode;
        newNode = (node *) malloc(sizeof(node));
        newNode->data = data;
        list->head = newNode;
        list->tail = newNode;
        list->head->prev = NULL;
        list->head->next = NULL;
        list->tail->next = NULL;
        list->tail->prev = NULL;
        list->cursor = list->head;
        list->len++;
        return 1;
    }
    if (list->cursor == list->head) {
        node *newNode;
        newNode = (node *) malloc(sizeof(node));
        newNode->data = data;
        newNode->next = list->head;
        list->head->prev = newNode;
        newNode->prev = NULL;
        list->head = newNode;
        list->cursor = list->tail;
        list->len++;
        return 1;
    }
    if (list->cursor == list->tail) {
        node *newNode;
        newNode = (node *) malloc(sizeof(node));
        newNode->data = data;
        newNode->next = NULL;
        newNode->prev = list->tail;
        list->tail->next = newNode;
        list->tail = newNode;
        list->cursor = list->tail;
        list->len++;
        return 1;
    }
    int n = 1;
    node *curent = list->head;
    while (curent != cursor) {
        curent = curent->next;
        n++;
    }

    if (n <= (list->len) / 2) {
        node *newNode;
        newNode = (node *) malloc(sizeof(node));
        newNode->data = data;
        node *nextNode;
        nextNode = list->head;
        int i = 0;
        while (i < n && nextNode != NULL) {
            nextNode = nextNode->next;
            i++;
        }
        newNode->next = nextNode;
        newNode->prev = nextNode->prev;
        nextNode = newNode;
        newNode->prev->next = newNode;
        if (newNode->next != NULL) {
            newNode->next->prev = newNode;
        }
        list->len += 1;
        list->cursor = newNode;
        return 1;
    } else {
        node *newNode = (node *) malloc(sizeof(node));
        newNode->data = data;
        node *prevNode;
        prevNode = list->tail;
        int i = 0;
        n = list->len - n - 1;
        while (i < n && prevNode != NULL) {
            prevNode = prevNode->prev;
            i++;
        }
        newNode->next = prevNode;
        newNode->prev = prevNode->prev;
        prevNode = newNode;
        newNode->prev->next = newNode;
        if (newNode->next != NULL) {
            newNode->next->prev = newNode;
        }
        list->cursor = newNode;
        list->len += 1;
        return 1;

    }

}

node *removeNode(TDoubleLinkedList *list, int n) {
    if (n > list->len + 1 || n < 1)
        return NULL;
    node *nextNode = list->head;
    node *prevNode = list->tail;
    if (n == 1) {
        list->head = nextNode->next;
        nextNode->next->prev = NULL;
        nextNode->prev = NULL;
        nextNode->next = nextNode;
        list->len--;
        list->cursor = list->head;
        return nextNode;
    }
    if (n == list->len) {
        list->tail = prevNode->prev;
        prevNode->prev->next = NULL;
        prevNode->next = NULL;
        prevNode->prev = prevNode;
        list->len--;
        list->cursor = list->tail;
        return prevNode;
    }

    int i=1;
    for (; i < n - 1; i++) {
        nextNode = nextNode->next;
    }
    node *toBeDeleted = nextNode->next;
    nextNode->next = toBeDeleted->next;
    nextNode->prev->next = nextNode;
    nextNode->next->prev = nextNode;
    nextNode->prev = toBeDeleted->prev->prev;
    list->len--;

    toBeDeleted->next = NULL;
    toBeDeleted->prev = NULL;
    list->cursor = nextNode->next;
    return toBeDeleted;
}

node *removeNodeBackwards(TDoubleLinkedList *list, int n, int counter) {
    if (n > list->len + 1 || n < 1)
        return NULL;
    node *nextNode = list->head;
    node *prevNode = list->tail;
    if (n == 1) {
        list->head = nextNode->next;
        nextNode->next->prev = NULL;
        nextNode->prev = NULL;
        nextNode->next = nextNode;
        list->len--;
        list->cursor = NULL;
        return nextNode;
    }
    if (n == list->len) {
        list->tail = prevNode->prev;
        prevNode->prev->next = NULL;
        prevNode->next = NULL;
        prevNode->prev = prevNode;
        list->len--;
        list->cursor = prevNode;
        return prevNode;
    }

    int i=1;
    for (; i < n; i++) {
        nextNode = nextNode->next;
    }

    node *current;
    while (counter > 0) {
        current = nextNode;
        node *toBeDeleted = current->prev;
        current->next = toBeDeleted->next->next;
        current->prev = toBeDeleted->prev;
        current->next->prev = current;
        current->prev->next = current;
        list->len--;

        toBeDeleted->next = NULL;
        toBeDeleted->prev = NULL;
        list->cursor = current->prev;
        counter--;
    }
    return current;
}

void free_list(TDoubleLinkedList **list) {
    TDoubleLinkedList *varfulListei = (*list);
    node *nodulCurent;
    nodulCurent = varfulListei->head;
    varfulListei->head = NULL;
    varfulListei->len = 0;
    free(varfulListei);

    if (nodulCurent == NULL)
        return;

    node *nextNode = nodulCurent->next;

    while (nextNode != NULL) {
        free(nodulCurent);
        nodulCurent = nextNode;
        nextNode = nextNode->next;
    }
    free(nodulCurent);
}

char *listToString(TDoubleLinkedList *list) {
    node *current = list->head;
    char *new = malloc(1001 * sizeof(char));
    int i = 0;
    while (current->next != NULL) {
        new[i] = current->data;
        current = current->next;
        i++;
    }
    new[i] = '\n';
    return new;
}

TDoubleLinkedList *stringToList(char *s, node *cursor) {
    TDoubleLinkedList *list;
    init(&list);
    int i = 0;
    for (; i < strlen(s); i++) {
        add(list, s[i], cursor);
    }
    return list;
}

int findCursor(TDoubleLinkedList *list, node *cursor) {
    node *current = list->head;
    int n = 1;
    while (current != cursor && current->next != NULL) {
        current = current->next;
        n++;
    }
    return n;
}

int findCursorLine(TDoubleLinkedList *list, node *cursor) {
    node *current = list->head;
    int n = 1;
    while (current != cursor && current->next != NULL) {
        current = current->next;
        if (current->data == '\n')
            n++;
    }
    n--;
    return n;
}


//pozitioneaza cursorul la inceputul liniei dorite
int placeCursorLineBegin(TDoubleLinkedList *list, int counter) {
    node *current = list->head;
    if (counter == 1) {
        list->cursor = list->head;
        return 1;
    }
    int alfa = 1;
    while (alfa < counter) {
        //tinem cont de '\n'
        while (current->data != '\n') {
            current = current->next;
        }
        if (current->next != NULL) {
            current = current->next;
        }
        alfa++;
    }
    if (current->next != NULL)
        current = current->prev;
    list->cursor = current->next;
    return 1;
}

//sterge linia dorita
int deleteLine(TDoubleLinkedList *list, int counter) {
    node *current = list->head;
    placeCursorLineBegin(list, counter);
    int n = findCursor(list, list->cursor);
    current = list->cursor;
    int ok = 1;
    while (current->data != '\n') {
        ok++;
        current = current->next;
    }
    while (ok > 0) {
        removeNode(list, n);
        ok--;
    }
    return 1;
}

//sterge linia pe care se afla cursorul
int deleteLinePointer(TDoubleLinkedList *list, node *cursor) {
    int space = findCursorLine(list, cursor) + 1;
    deleteLine(list, space);
    return 1;
}

//functia gc 
int placeCharCursor(TDoubleLinkedList *list, int counter, int linie) {
        node *current;
        int ok=1;
        //pozitionam cursorul la inceput de linie
        placeCursorLineBegin(list, linie + 1);
        current = list->cursor;
        //iteram prin lista pana pe pozitia counter
        while (ok < counter) {
            current = current->next;
            ok++;
        }
        list->cursor = current;
    
    return 1;
}

//inlocuieste prima aparitie a textului dupa cursor
int replaceFirstAfter(TDoubleLinkedList *list, char *oldText, char *newText) {
    node *current = list->cursor;
    node *aux = list->cursor;
    int x;
    int beta = 0;
    //identificam de unde incepe textul
    while (current->next != NULL && beta == 0) {
        x = 0;
        while (aux->data == oldText[x]) {
            aux = aux->next;
            x++;
            if(x==strlen(oldText))
                beta = 1;
        }
        if (beta == 0) {
            current = current->next;
            aux = current;
        }
    }
    if(beta==1){
        //cele 3 cazuri, pentru ca depinde de lungimea textlui nou daca scoate adaugam sau lasam pe loc nr de noduri
    if (strlen(oldText) > strlen(newText)) {
        int ok = 0;
        int alfa = strlen(newText);
        while (ok < alfa) {
            current->data = newText[ok];
            current = current->next;
            ok++;
        }
        list->cursor=current->prev;
        int beta=strlen(oldText)-strlen(newText);
        while(beta>0){
            int n = findCursor(list, list->cursor);
            removeNode(list, n);
            beta--;
        }
    }
    if (strlen(oldText) < strlen(newText)) {
        int ok = 0;
        int alfa = strlen(oldText);
        while (ok < alfa) {
            current->data = newText[ok];
            current = current->next;
            ok++;
        }
        list->cursor=current->prev;
        int beta=strlen(newText)-strlen(oldText);
        while(beta>0){
            add(list, newText[ok], list->cursor);
            beta--;
        }
        current=list->cursor;
        list->cursor=current->prev;
    }
    if (strlen(oldText) == strlen(newText)) {
        int ok = 0;
        int alfa = strlen(oldText);
        while (ok < alfa) {
            current->data = newText[ok];
            current = current->next;
            ok++;
        }
        list->cursor=current->prev;
    }
    }
    
    return 1;
}

//e la fel ca functia de mai sus dar folosim un while si la final pozitionam cursorul pe nodul head
int replaceAllAfter(TDoubleLinkedList *list, char *oldText, char *newText) {
    node *lastAppearance;
    node *current = list->cursor;
    node *aux = list->cursor;
    int x;
    while(current->next!=NULL){
    int beta = 0;
    while (current->next != NULL && beta == 0) {
        x = 0;
        while (aux->data == oldText[x]) {
            aux = aux->next;
            x++;
            if(x==strlen(oldText))
                beta = 1;
        }
        if (beta == 0) {
            current = current->next;
            aux = current;
        }
    }
    if(beta==1){
    if (strlen(oldText) > strlen(newText)) {
        int ok = 0;
        int alfa = strlen(newText);
        while (ok < alfa) {
            current->data = newText[ok];
            current = current->next;
            ok++;
        }
        list->cursor=current->prev;
        int beta=strlen(oldText)-strlen(newText);
        while(beta>0){
            int n = findCursor(list, list->cursor);
            removeNode(list, n);
            beta--;
        }
        lastAppearance=list->cursor;
    }
    if (strlen(oldText) < strlen(newText)) {
        int ok = 0;
        int alfa = strlen(oldText);
        while (ok < alfa) {
            current->data = newText[ok];
            current = current->next;
            ok++;
        }
        list->cursor=current->prev;
        int beta=strlen(newText)-strlen(oldText);
        while(beta>0){
            add(list, newText[ok], list->cursor);
            beta--;
        }
        current=list->cursor;
        list->cursor=current->prev;
        lastAppearance=list->cursor;
    }
    if (strlen(oldText) == strlen(newText)) {
        int ok = 0;
        int alfa = strlen(oldText);
        while (ok < alfa) {
            current->data = newText[ok];
            current = current->next;
            ok++;
        }
        
        list->cursor=current->prev;
        lastAppearance=list->cursor;
    }
    }
    }
    list->cursor=lastAppearance;
    return 1;
}

//gaseste prima aparitie a unui text de dupa cursor si pozitioneaza cursorul pe primul nod(litera)
int findFirst(TDoubleLinkedList *list, char* text, node *cursor){
    node *current = list->cursor;
    node *aux = list->cursor;
    int x;
    int beta=0;
    int n = 0;
    while (current->next != NULL && beta == 0) {
        x = 0;
        while (aux->data == text[x]) {
            aux = aux->next;
            x++;
            if(x==strlen(text))
                beta = 1;
        }
        if (beta == 0) {
            current = current->next;
            aux = current;
        }
    }
    list->cursor=current;
    return n;

}
int main() {
    FILE *src, *dest;
    char buffer[BUFMAX];
    TDoubleLinkedList *list;
    Stack *stack;
    Stack *comenzi;
    Stack *redoStack;
    //lista de comenzi
    initS(&comenzi);
    //lista care tine textul redo
    initS(&redoStack);
    //lista care tine toate formele textului
    initS(&stack);
    //lista mea de text, dublu inlantuita
    init(&list);
    //chestii ajutatoare
    int icount = 0;
    int ok = 0;
    int integer = 0;

    src = fopen("editor.in", "r");
    dest = fopen("editor.out", "w");
    if (src == NULL || dest == NULL)
        printf("Nu s-a putut deschide fisierul");
    else
    //ok imi zice daca s-a ajuns la q
        while (fgets(buffer, BUFMAX, src) != NULL && ok == 0) {
            //icount tine cont de inserare text
            //cand e par, inserez in text, cand e impar, se insereaza comenzi
            if (icount % 2 == 0) {
                int k = 0;
                char i = buffer[k];
                //tin cont de atentie la linii si sa nu fie ::i comanda
                while (i != '\n' && i != ':') {
                    add(list, buffer[k], list->cursor);
                    k++;
                    i = buffer[k];
                }
                if (i != ':')
                    add(list, '\n', list->cursor);
                //daca ::i e comanda adaug in stack actuala lista si in lista de comenzi comanda ::i
                if (strcmp(buffer, "::i\n") == 0) {
                    add_stack(stack, listToString(list));
                    add_stack(comenzi, "::i\n");
                    icount++;
                }

            } else {
                //tin cont daca am comanda simpla sau comanda cu argumente
                char *aux = malloc(101 * sizeof(char));
                char *linie = malloc(101 * sizeof(char));
                //scoatem acel /n de la final de comenzi
                buffer[strlen(buffer) - 1] = '\0';
                strcpy(aux, buffer);
                //adaugam in lista de comenzi comanda simpla
                add_stack(comenzi, aux);
                char *cuv = malloc(101 * sizeof(char));
                strcpy(linie, aux);
                //daca am comanda cu argumente, separ comanda de argumente
                char *pch = strtok(linie, " ");
                if (pch == NULL) {
                    strcpy(cuv, buffer);
                } else strcpy(cuv, pch);
                int alfa;
                //vad ce comanda am actual, ca sa pot sa identific in switch
                //alfa e ce ma ajuta sa o identific
                if (strcmp(cuv, "r") == 0)
                    alfa = 0;
                if (strcmp(cuv, "s") == 0)
                    alfa = 1;
                if (strcmp(cuv, "u") == 0)
                    alfa = 2;
                if (strcmp(cuv, "dl") == 0)
                    alfa = 3;
                if (strcmp(cuv, "b") == 0)
                    alfa = 4;
                if (strcmp(cuv, "gl") == 0)
                    alfa = 5;
                if (strcmp(cuv, "gc") == 0)
                    alfa = 6;
                if (strcmp(cuv, "re") == 0)
                    alfa = 7;
                if (strcmp(cuv, "ra") == 0)
                    alfa = 8;
                if (strcmp(cuv, "dw") == 0)
                    alfa = 9;
                if (strcmp(cuv, "da") == 0)
                    alfa = 10;
                if (strcmp(cuv, "q") == 0)
                    alfa = 11;
                if (strcmp(cuv, "d") == 0)
                    alfa = 12;
                if (strcmp(cuv, "::i") == 0)
                    alfa = 13;
                //chestii care ma ajuta in switch, deoarece nu mai pot initializa chestii in el
                char *newState = malloc(101 * sizeof(char));
                int counter;
                int n;
                char *auxString = malloc(101 * sizeof(char));
                node *cursor = list->cursor;
                switch (alfa) {
                    case 0:
                        //redo
                        //din stiva de redo(redoStack) dau pop la primul element pe care il salvez in stiva de text 
                        add_stack(stack, redoStack->top->sdata);
                        pop_stack(redoStack);
                        free_list(&list);
                        init(&list);
                        list = stringToList(stack->top->sdata, cursor);
                        break;
                    case 1:
                        //save
                        //salvez top-ul din stiva de text, eliberez lista, stiva 
                        //salvez in ambele acel top (newState)
                        strcpy(newState, stack->top->sdata);
                        freeS(&stack);
                        initS(&stack);
                        add_stack(stack, newState);
                        free_list(&list);
                        init(&list);
                        cursor = list->cursor;
                        list = stringToList(newState, cursor);
                        break;
                    case 2:
                        //undo
                        //salvez in stiva de redo top-ul din stiva text si dau pop
                        //modific lista
                        add_stack(redoStack, stack->top->sdata);
                        pop_stack(stack);
                        free_list(&list);
                        init(&list);
                        cursor = list->cursor;
                        list = stringToList(stack->top->sdata, cursor);
                        break;
                    case 3:
                        //dl
                        //identific daca e specificat vreun parametru
                        //daca e, acela e counter si apelez functia de deleteLine
                        //daca nu e, sterg in functie de unde se afla cursorul meu
                        pch = strtok(NULL, " ");
                        if (pch != NULL) {
                            counter = atoi(pch);
                            deleteLine(list, counter);
                        } else {
                            deleteLinePointer(list, list->cursor);
                        }
                        //salvez forma textului in stiva de text (stack)
                        add_stack(stack, listToString(list));
                        break;
                    case 4:
                        //b
                        //identific locul pe care se afla cursorul, si cresc cu unu ca sa imi stearga din spate
                        n = findCursor(list, list->cursor)+1;
                        //daca e la final de tot, sterg si acel \n
                        if (n == list->len && list->cursor->data == '\n') {
                            removeNode(list, n);
                            removeNode(list, n - 1);
                        }
                        removeNode(list, n);
                        add_stack(stack, listToString(list));
                        break;
                    case 5:
                        //gl
                        //plasez cursorul la inceput de linia counter 
                        pch = strtok(NULL, " ");
                        if (pch != NULL) {
                            counter = atoi(pch);
                            placeCursorLineBegin(list, counter);
                        }
                        break;
                    case 6:
                        //gc
                        //pch tine cont daca imi specifica si linia sau nu
                        pch = strtok(NULL, " ");
                        counter = atoi(pch);
                        pch = strtok(NULL, " ");
                        if (pch != NULL) {
                            //plasez la inceput de linie pch
                            //de pe pozitia aia incep si numar counter pozitii
                            placeCursorLineBegin(list, atoi(pch));
                            n = findCursorLine(list, list->cursor);
                            placeCharCursor(list, counter, n);
                        } else {
                            //aceeasi idee ca mai sus dar n este actuala linie si nu mai plasam pe alta
                            n = findCursorLine(list, list->cursor);
                            placeCharCursor(list, counter, n);
                        }
                        break;
                    case 7:
                        //re
                        pch = strtok(NULL, " ");
                        strcpy(auxString, pch);
                        pch = strtok(NULL, " ");
                        replaceFirstAfter(list, auxString, pch);
                        add_stack(stack, listToString(list));
                        break;
                    case 8:
                        //ra
                        pch = strtok(NULL, " ");
                        strcpy(auxString, pch);
                        pch = strtok(NULL, " ");
                        replaceAllAfter(list, auxString, pch);
                        add_stack(stack, listToString(list));
                        break;
                    case 9:
                        //da
                        pch = strtok(NULL, " ");
                        //gaseste locul unde se afla prima aparitie, imediat dupa cursor
                        findFirst(list, pch, list->cursor);
                        n=findCursor(list, list->cursor);
                        integer=strlen(pch);
                        //stergem strlen(pch) noduri de pe pozitia n, adica lungimea cuvantului
                        while(integer>0){
                        removeNode(list, n);
                        integer--;
                        }
                        //adaugam in stiva text forma noua a textului
                        add_stack(stack, listToString(list));
                        
                        break;
                    case 10:
                        //dw
                        //snalog ca ma sus, doar ca aape un while ca next !=null ca sa parcurga textul pana la final si sa caute toate aparitiile
                        pch = strtok(NULL, " ");
                        while(list->cursor->next!=NULL){
                        findFirst(list, pch, list->cursor);
                        n=findCursor(list, list->cursor);
                        integer=strlen(pch);
                        while(integer>0){
                        removeNode(list, n);
                        if(list->cursor->data=='\n')
                        removeNode(list, n);
                        integer--;
                        }
                        }
                        add_stack(stack, listToString(list));
                        break;
                    case 11:
                        //q
                        //dam pop ca sa scapam de ce nu am salvat
                        while (stack->len > 1) {
                            pop_stack(stack);
                        }
                        list->cursor = list->head;
                        list = stringToList(stack->top->sdata, list->cursor);
                        print(list, dest);
                        ok++;
                        break;
                    case 12:
                        //d 
                        //e analog cu functia b, doar ca stregem invers si tinem cont de counter, adica de nr de stregeri
                        n = findCursor(list, list->cursor);
                        pch = strtok(NULL, " ");
                        if (pch != NULL) {
                            counter = atoi(pch);
                            removeNodeBackwards(list, n, atoi(pch));
                        } else
                            removeNodeBackwards(list, n, 1);
                        //salvam lista
                        add_stack(stack, listToString(list));
                        break;
                    case 13:
                        icount++;
                        break;
                }
            }
        }
}
