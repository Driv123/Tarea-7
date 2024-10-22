// Equipo: Hannah Montana Os - codigo OPR (LRU A OPR)


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NUM_FRAMES 4   
#define NUM_PAGES 10   

// Estructura para un frame de pagina en memoria fisica
typedef struct Frame {
    int page;           // Numero de página almacenada en el frame 
    bool valid;         // Indica si el frame está ocupado
    struct Frame *prev; 
    struct Frame *next; 
} Frame;

// Estructura para la lista de frames en memoria fisica
typedef struct FrameList {
    int numFrames;      // Numero de frames actualmente ocupados
    Frame *head;        
    Frame *tail;        
} FrameList;

// Funcion para crear un nuevo frame
Frame* createFrame() {
    Frame *frame = (Frame *)malloc(sizeof(Frame));
    if (frame != NULL) {
        frame->page = -1;   // No hay pagina asignada
        frame->valid = false;
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
void removeFrame(FrameList *frameList, Frame *frame) {
    if (frame->prev != NULL) {
        frame->prev->next = frame->next;
    } else {
        frameList->head = frame->next;
    }
    if (frame->next != NULL) {
        frame->next->prev = frame->prev;
    } else {
        frameList->tail = frame->prev;
    }
    frameList->numFrames--;
    free(frame);
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

// Funcion para encontrar el frame para reemplazar usando el algoritmo OPR (al que se cambio)
Frame* findOptimalFrame(FrameList *frameList, int *futureReferences, int currentIndex, int numFutureReferences) {
    Frame *current = frameList->head;
    Frame *optimalFrame = NULL;
    int farthestIndex = -1;

    // Buscar sobre los frames en memoria para saber cual no sera usado por mucho tiempo
    while (current != NULL) {
        int foundAt = -1;
        for (int i = currentIndex + 1; i < numFutureReferences; i++) {
            if (futureReferences[i] == current->page) {
                foundAt = i;
                break;
            }
        }

       
        if (foundAt == -1) {
            return current;
        }

        // Buscar el frame que se usara despues
        if (foundAt > farthestIndex) {
            farthestIndex = foundAt;
            optimalFrame = current;
        }

        current = current->next;
    }

    return optimalFrame;
}

// Funcion para simular la carga de una pagina a memoria fisica usando OPR
void loadPage(FrameList *frameList, int page, int *futureReferences, int currentIndex, int numFutureReferences) {
    Frame *frame = findFrame(frameList, page);
    if (frame != NULL) {
        return;
    }

    // Si la lista de frames ya esta llena, cambiar la pagina (OPR)
    if (frameList->numFrames == NUM_FRAMES) {
        Frame *optimalFrame = findOptimalFrame(frameList, futureReferences, currentIndex, numFutureReferences);
        removeFrame(frameList, optimalFrame);
    }

    // Poner la nueva pagina
    frame = createFrame();
    frame->page = page;
    frame->valid = true;
    insertFrame(frameList, frame);
}

// Funcion para imprimir la lista de frames actual
void printFrameList(FrameList *frameList) {
    printf("Estado actual de la lista de frames:\n");
    Frame *current = frameList->head;
    while (current != NULL) {
        printf("Página: %d, ", current->page);
        if (current->valid) {
            printf("Estado: Ocupado\n");
        } else {
            printf("Estado: Vacío\n");
        }
        current = current->next;
    }
    printf("\n");
}

int main() {
    FrameList *frameList = createFrameList();

    // Secuencia de referencias para despues
    int futureReferences[NUM_PAGES] = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
    
    // Simular la carga de varias paginas a la memoria física usando OPR
    for (int i = 0; i < NUM_PAGES; i++) {
        loadPage(frameList, futureReferences[i], futureReferences, i, NUM_PAGES);
        printFrameList(frameList);  
    }

   
    free(frameList);

    return 0; //Tetminar el programa god
}
