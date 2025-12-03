#include <stdio.h>
#include<string.h>

struct Book {
    int id;
    int popularity;
    int lastAccess;   
};

int main() {
    int capacity, Q;
    scanf("%d %d", &capacity, &Q);

    struct Book shelf[100];  
    int size = 0;
    int time = 0; 

    while (Q--) {
        char command[10];
        scanf("%s", command);

        if (strcmp(command, "ADD") == 0) {
            int x, y;
            scanf("%d %d", &x, &y);
            time++;

            int found = -1;

           
            for (int i = 0; i < size; i++) {
                if (shelf[i].id == x) {
                    shelf[i].popularity = y;
                    shelf[i].lastAccess = time;
                    found = 1;
                    break;
                }
            }

            if (found == 1) continue;

          
            if (size < capacity) {
                shelf[size].id = x;
                shelf[size].popularity = y;
                shelf[size].lastAccess = time;
                size++;
            } 
            else {
               
                int lruIndex = 0;
                int minAccess = shelf[0].lastAccess;

                for (int i = 1; i < size; i++) {
                    if (shelf[i].lastAccess < minAccess) {
                        minAccess = shelf[i].lastAccess;
                        lruIndex = i;
                    }
                }

            
                shelf[lruIndex].id = x;
                shelf[lruIndex].popularity = y;
                shelf[lruIndex].lastAccess = time;
            }

        } 
        else if (strcmp(command, "ACCESS") == 0) {
            int x;
            scanf("%d", &x);
            time++;

            int found = 0;

            for (int i = 0; i < size; i++) {
                if (shelf[i].id == x) {
                    printf("%d\n", shelf[i].popularity);
                    shelf[i].lastAccess = time;  
                    found = 1;
                    break;
                }
            }

            if (!found) {
                printf("-1\n");
            }
        }
    }

    return 0;
}


