// Equipo: Hannah Montana Os - codigo LRU (FIFO A LRU)



#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NUM_FRAMES 4   // Numero de frames o paginas
#define NUM_PAGES 10   // Numero de paginas virtuales


typedef struct Frame {
    int page;           // Numero de pagina  en el frame (-1 si no tiene nada)
    bool valid;         // Indica si el frame esta ocupado 
    int frequency;      // Contador de frecuencia 
    struct Frame *prev; // Puntero al frame para lista doblemente enlazada
    struct Frame *next; // Puntero al frame siguiente para la lista
} Frame;

// Estructura para la lista de frames
typedef struct FrameList {
    int numFrames;      // frames ocupados
    Frame *head;        // Puntero al primer frame 
    Frame *tail;        // Puntero al ultimo frame 
} FrameList;

// Funcion para crear un nuevo frame
Frame* createFrame() {
    Frame *frame = (Frame *)malloc(sizeof(Frame));
    if (frame != NULL) {
        frame->page = -1;   
        frame->valid = false;
        frame->frequency = 0;  
        frame->prev = NULL;
        frame->next = NULL;
    }
    return frame;
}

// Funcion para inicializar la lista de frames en memoria fisica
FrameList* createFrameList() {
    FrameList *frameList = (FrameList *)malloc(sizeof(FrameList));
    if (frameList != NULL) {
        frameList->numFrames = 0;
        frameList->head = NULL;
        frameList->tail = NULL;
    }
    return frameList;
}

// Funcion para insertar un frame al frente de la lista 
void insertFrame(FrameList *frameList, Frame *frame) {
    if (frameList->head == NULL) {
        frameList->head = frame;
        frameList->tail = frame;
    } else {
        frame->next = frameList->head;
        frameList->head->prev = frame;
        frameList->head = frame;
    }
    frameList->numFrames++;
}

// Funcion para eliminar un frame de la lista 
void removeLFUFrame(FrameList *frameList) {
    Frame *current = frameList->head;
    Frame *lfuFrame = current;

	//Buscar el frame con uso mas bajo
    while (current != NULL) {
        if (current->frequency < lfuFrame->frequency) {
            lfuFrame = current;
        }
        current = current->next;
    }

    // Eliminar el frame con menor uso
    if (lfuFrame->prev != NULL) {
        lfuFrame->prev->next = lfuFrame->next;
    } else {
        frameList->head = lfuFrame->next;
    }
    if (lfuFrame->next != NULL) {
        lfuFrame->next->prev = lfuFrame->prev;
    } else {
        frameList->tail = lfuFrame->prev;
    }

    frameList->numFrames--;
    free(lfuFrame);
}

// Funcion para buscar un frame especifico 
Frame* findFrame(FrameList *frameList, int page) {
    Frame *current = frameList->head;
    while (current != NULL) {
        if (current->page == page) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Función para simular la carga de una página a memoria física utilizando LFU
void loadPage(FrameList *frameList, int page) {
    Frame *frame = findFrame(frameList, page);
    if (frame != NULL) {
        frame->frequency++;
    } else {
        // Si la página no está en memoria, crear un nuevo frame
        frame = createFrame();
        frame->page = page;
        frame->valid = true;
        frame->frequency = 1;  
        if (frameList->numFrames == NUM_FRAMES) {
            removeLFUFrame(frameList);
        }

        // nuevo frame
        insertFrame(frameList, frame);
    }
}

// Funcion para imprimir el estado actual de la lista de frames
void printFrameList(FrameList *frameList) {
    printf("Estado actual de la lista de frames:\n");
    Frame *current = frameList->head;
    while (current != NULL) {
        printf("Pagina: %d, Frecuencia: %d, ", current->page, current->frequency);
        if (current->valid) {
            printf("Estado: Ocupado\n");
        } else {
            printf("Estado: Vacío\n");
        }
        current = current->next;
    }
    printf("\n");
}

int main() { //El main o funcion principal c:
    FrameList *frameList = createFrameList();

    loadPage(frameList, 1);
    loadPage(frameList, 2);
    loadPage(frameList, 3);
    loadPage(frameList, 4);
    printFrameList(frameList);  // Debe imprimir el estado actual de los frames

    loadPage(frameList, 5);
    printFrameList(frameList);  

    // Simular mas accesos a las paginas
    loadPage(frameList, 1);  
    loadPage(frameList, 3);  
    printFrameList(frameList);  

    // Liberar la memoria utilizada por la lista de frames
    free(frameList);

    return 0; //Terminar  el codigo
}
