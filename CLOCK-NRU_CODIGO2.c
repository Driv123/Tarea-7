// Equipo: Hannah Montana Os - codigo NRU (CLOCK - NRU)


#include <stdio.h>

#define FRAME_COUNT 4  // Numero de marcos de pagina 

// Estructura para un marco de pagina
typedef struct {
    char page;   
    int ref_bit; // bit de referencia
} Frame;

// Funcion para imprimir los marcos
void printFrames(Frame frames[], int frame_count) {
    for (int i = 0; i < frame_count; i++) {
        // Imprimir el estado de cada pagina 
        printf("[%c:%d] ", frames[i].page, frames[i].ref_bit);
    }
    printf("\n");
}

// Funcion que reemplaza una pagina con NRU
void replacePage(Frame frames[], int frame_count, char page, int *pointer) {
    while (1) {

        if (frames[*pointer].ref_bit == 0) {
            // Si el bit de referencia es 0, reemplaza la pagina
            printf("Reemplazando pagina %c por pagina %c\n", frames[*pointer].page, page);
            frames[*pointer].page = page;    // Se actualiza con la nueva pagina
            frames[*pointer].ref_bit = 1;    // La nueva pagina se marca como referenciada 
            *pointer = (*pointer + 1) % frame_count; 
            break;
        } else {
            // Si el bit de referencia es 1 se cambia a 0
            printf("Pagina %c fue referenciada (bit de referencia -> 0)\n", frames[*pointer].page);
            frames[*pointer].ref_bit = 0;    // Cambiamos el bit a 0
            *pointer = (*pointer + 1) % frame_count;  
        }
    }
}

// Funcion que  hace el reemplazo de paginas con el algoritmo NRU
void nruPageReplacement(char pages[], int page_count, int frame_count) {
    Frame frames[FRAME_COUNT];  
    int pointer = 0;           

    // Inicializas los marcos de pagina con las paginas iniciales y sus bits de referencia
    char initial_pages[] = {'A', 'B', 'C', 'D'};   
    int initial_bits[] = {1, 0, 1, 0};             
    for (int i = 0; i < frame_count; i++) {
        frames[i].page = initial_pages[i];        
        frames[i].ref_bit = initial_bits[i];    
    }

    // Muest el estado inicial de los marcos
    printf("Estado inicial de los marcos:\n");
    printFrames(frames, frame_count);

    // Simula la llegada de cada nueva pagina y aplica NRU
    for (int i = 0; i < page_count; i++) {
        char page = pages[i];
        printf("\nCargando pagina %c\n", page);

      
        replacePage(frames, frame_count, page, &pointer);

       
        printFrames(frames, frame_count);
    }
}

int main() {
    char pages[] = {'E'};  // Lista de paginas que se cargaran
    int page_count = sizeof(pages) / sizeof(pages[0]);  // Numero de paginas a cargar
    int frame_count = FRAME_COUNT;                      // Numero de marcos disponibles

    // Simula el cambio de paginas usando NRU
    nruPageReplacement(pages, page_count, frame_count);

    return 0; // Terminamos el programa god
}

