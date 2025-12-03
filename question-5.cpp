#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>

#define INITIAL_CAPACITY 4
#define MAX_LINE_LENGTH 1024  


typedef struct {
    char **lines;     
    int size;         
    int capacity;     
} Editor;


void memError(const char *msg) {
    fprintf(stderr, "Memory Allocation Error: %s\n", msg);
    exit(1);
}


void ensureCapacity(Editor *ed) {
    if (ed->size < ed->capacity) return;

    int newCap = ed->capacity * 2;
    char **temp = realloc(ed->lines, newCap * sizeof(char*));
    if (!temp) memError("Unable to expand line buffer.");

    ed->lines = temp;
    ed->capacity = newCap;
}


void insertLine(Editor *ed, int index, const char *text) {
    if (index < 0 || index > ed->size) {
        printf("Invalid index.\n");
        return;
    }

    ensureCapacity(ed);


    memmove(&ed->lines[index + 1], &ed->lines[index],
            (ed->size - index) * sizeof(char*));

  
    ed->lines[index] = malloc(strlen(text) + 1);
    if (!ed->lines[index]) memError("Unable to allocate memory for line.");

    strcpy(ed->lines[index], text);
    ed->size++;
}


void deleteLine(Editor *ed, int index) {
    if (index < 0 || index >= ed->size) {
        printf("Invalid index.\n");
        return;
    }

    free(ed->lines[index]); 

    
    memmove(&ed->lines[index], &ed->lines[index + 1],
            (ed->size - index - 1) * sizeof(char*));

    ed->size--;
}


void printAllLines(Editor *ed) {
    if (ed->size == 0) {
        printf("(buffer is empty)\n");
        return;
    }
    for (int i = 0; i < ed->size; i++) {
        printf("%d: %s\n", i, ed->lines[i]);
    }
}

void shrinkToFit(Editor *ed) {
    char **temp = realloc(ed->lines, ed->size * sizeof(char*));
    if (!temp) memError("Unable to shrink buffer.");

    ed->lines = temp;
    ed->capacity = ed->size;
}

void freeAll(Editor *ed) {
    for (int i = 0; i < ed->size; i++) {
        free(ed->lines[i]);
    }
    free(ed->lines);
}


void saveToFile(Editor *ed, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        printf("Unable to open file.\n");
        return;
    }

    for (int i = 0; i < ed->size; i++) {
        fprintf(fp, "%s\n", ed->lines[i]);
    }

    fclose(fp);
    printf("Saved successfully.\n");
}

void loadFromFile(Editor *ed, const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("File not found.\n");
        return;
    }

  
    freeAll(ed);
    ed->capacity = INITIAL_CAPACITY;
    ed->size = 0;
    ed->lines = malloc(ed->capacity * sizeof(char*));
    if (!ed->lines) memError("Unable to allocate initial buffer.");

    char buffer[MAX_LINE_LENGTH];

    while (fgets(buffer, MAX_LINE_LENGTH, fp)) {
        buffer[strcspn(buffer, "\n")] = '\0'; 
        insertLine(ed, ed->size, buffer);
    }

    fclose(fp);
    printf("File loaded successfully.\n");
}



int main() {
    Editor ed;
    ed.capacity = INITIAL_CAPACITY;
    ed.size = 0;
    ed.lines = malloc(ed.capacity * sizeof(char*));
    if (!ed.lines) memError("Unable to allocate initial buffer.");

    char input[MAX_LINE_LENGTH];
    int choice, index;

    while (1) {
        printf("\n--- Minimal Line-Based Text Editor ---\n");
        printf("1. Insert Line\n");
        printf("2. Delete Line\n");
        printf("3. Print All Lines\n");
        printf("4. Shrink To Fit\n");
        printf("5. Save To File\n");
        printf("6. Load From File\n");
        printf("7. Exit\n");
        printf("Choose: ");
        scanf("%d", &choice);
        getchar(); // clear newline

        if (choice == 1) {
            printf("Enter index: ");
            scanf("%d", &index);
            getchar();

            printf("Enter text: ");
            fgets(input, MAX_LINE_LENGTH, stdin);
            input[strcspn(input, "\n")] = '\0';

            insertLine(&ed, index, input);
        }

        else if (choice == 2) {
            printf("Enter index: ");
            scanf("%d", &index);
            deleteLine(&ed, index);
        }

        else if (choice == 3) {
            printAllLines(&ed);
        }

        else if (choice == 4) {
            shrinkToFit(&ed);
            printf("Shrunk buffer to fit exactly.\n");
        }

        else if (choice == 5) {
            printf("Filename: ");
            scanf("%s", input);
            saveToFile(&ed, input);
        }

        else if (choice == 6) {
            printf("Filename: ");
            scanf("%s", input);
            loadFromFile(&ed, input);
        }

        else if (choice == 7) {
            printf("Exiting...\n");
            break;
        }

        else {
            printf("Invalid choice.\n");
        }
    }

    freeAll(&ed);
    return 0;
}

