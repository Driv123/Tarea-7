/* Equipo: Hannah Montana Os - codigo CLOCK 

Se hizo dado el siguiente ejemplo:

EJEMPLO:  Si las páginas [A, B, C, D] están en la memoria 
y sus bits de uso son [1, 0, 1, 0], y se necesita cargar una nueva página E, se comenzará desde A. Si A tiene su bit en 1, 
se pone en 0 y se pasa a la siguiente página, B, que será reemplazada si su bit es 0. */

#include <stdio.h>

#define FRAME_COUNT 4  // Numero de marcos de pagina 

// Estructura para un marco de pagina
typedef struct {
    char page;   // Letra de la pagina
    int use_bit; // Bit que indica si la pagina ha sido utilizada hace poco
} Frame;

// Funcion para imprimir el estado de los marcos actualmente
void printFrames(Frame frames[], int frame_count) {
    for (int i = 0; i < frame_count; i++) {
        // Imprimir el estado de cada pagina 
        printf("[%c:%d] ", frames[i].page, frames[i].use_bit);
    }
    printf("\n");
}

// Funcion que reemplaza una pagina segun el algoritmo CLOCK
void replacePage(Frame frames[], int frame_count, char page, int *pointer) {
    while (1) {
        // Verificamos el bit de uso del marco actual al que apunta el puntero
        if (frames[*pointer].use_bit == 0) {
            // Si el bit de uso es 0, reemplazamos la pagina
            printf("Reemplazando pagina %c por pagina %c\n", frames[*pointer].page, page);
            frames[*pointer].page = page;    // Se actualiza con la nueva pagina
            frames[*pointer].use_bit = 1;    // La nueva pagina obtiene su primera oportunidad 
            *pointer = (*pointer + 1) % frame_count;  // Avanzamos el puntero circular
            break;
        } else {
            // Si el bit de uso es 1, le damos una segunda oportunidad y lo cambiamos a 0
            printf("Pagina %c tiene segunda oportunidad (bit de uso -> 0)\n", frames[*pointer].page);
            frames[*pointer].use_bit = 0;    // Cambiamos el bit a 0
            *pointer = (*pointer + 1) % frame_count;  // Avanzamos el puntero circular al siguiente marco
        }
    }
}

// Funcion que simula el reemplazo de paginas con el algoritmo CLOCK
void clockPageReplacement(char pages[], int page_count, int frame_count) {
    Frame frames[FRAME_COUNT]; 
    int pointer = 0;           

    // Inicializamos los marcos de pagina con las paginas iniciales y sus bits de uso
    char initial_pages[] = {'A', 'B', 'C', 'D'};   // Paginas iniciales en la memoria
    int initial_bits[] = {1, 0, 1, 0};             // Bits de uso iniciales
    for (int i = 0; i < frame_count; i++) {
        frames[i].page = initial_pages[i];         // Asignamos las paginas iniciales
        frames[i].use_bit = initial_bits[i];       // Asignamos los bits de uso iniciales
    }

    // Mostramos el estado inicial de los marcos
    printf("Estado inicial de los marcos:\n");
    printFrames(frames, frame_count);

    // Simulamos la llegada de cada nueva pagina y aplicamos el algoritmo CLOCK
    for (int i = 0; i < page_count; i++) {
        char page = pages[i];
        printf("\nCargando pagina %c\n", page);

        // Llamamos a la funcion para reemplazar la pagina si es necesario
        replacePage(frames, frame_count, page, &pointer);

        // Mostramos el estado actual de los marcos despues de cada operacion
        printFrames(frames, frame_count);
    }
}

int main() {
    char pages[] = {'E'};  // Lista de paginas que vamos a cargar
    int page_count = sizeof(pages) / sizeof(pages[0]);  // Numero de paginas a cargar
    int frame_count = FRAME_COUNT;                      // Numero de marcos disponibles

    // Simula el reemplazo de paginas usando el algoritmo CLOCK
    clockPageReplacement(pages, page_count, frame_count);

    return 0; // Terminamos el programa god
}

