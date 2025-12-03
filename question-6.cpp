#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "members.dat"



typedef struct {
    int studentID;
    char fullName[100];
    char batch[50];            
    char membershipType[10];   
    char regDate[11];         
    char dob[11];              
    char interest[10];         
} Student;



Student *db = NULL;      
int dbSize = 0;          
int dbCapacity = 0;     



void ensureCapacity() {
    if (dbSize < dbCapacity) return;

    int newCap = (dbCapacity == 0) ? 10 : dbCapacity * 2;
    Student *temp = realloc(db, newCap * sizeof(Student));

    if (!temp) {
        printf("ERROR: Memory allocation failed.\n");
        exit(1);
    }

    db = temp;
    dbCapacity = newCap;
}

int idExists(int id) {
    for (int i = 0; i < dbSize; i++)
        if (db[i].studentID == id)
            return 1;
    return 0;
}



void loadDatabase(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        printf("Database file not found. Creating new one...\n");
        return;
    }

    Student temp;
    while (fread(&temp, sizeof(Student), 1, fp)) {
        ensureCapacity();
        db[dbSize++] = temp;
    }

    fclose(fp);
    printf("%d records loaded from database.\n", dbSize);
}

void saveDatabase(const char *filename) {
    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        printf("ERROR: Could not save database.\n");
        return;
    }

    fwrite(db, sizeof(Student), dbSize, fp);
    fclose(fp);
}


void addStudentToFile(Student s, const char *filename) {
    FILE *fp = fopen(filename, "ab");
    if (!fp) {
        printf("ERROR: Could not open file for appending.\n");
        return;
    }

    fwrite(&s, sizeof(Student), 1, fp);
    fclose(fp);
}


void deleteStudentFromFile(int id, const char *filename) {
    FILE *fp = fopen(filename, "rb");
    FILE *temp = fopen("temp.dat", "wb");

    if (!fp || !temp) {
        printf("ERROR: Could not delete record.\n");
        return;
    }

    Student s;
    while (fread(&s, sizeof(Student), 1, fp)) {
        if (s.studentID != id)
            fwrite(&s, sizeof(Student), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove(filename);
    rename("temp.dat", filename);
}


void rewriteDatabase(const char *filename) {
    saveDatabase(filename);
}




void addStudent() {
    Student s;

    printf("Enter Student ID: ");
    scanf("%d", &s.studentID);
    getchar();

    if (idExists(s.studentID)) {
        printf("ERROR: Student ID already exists.\n");
        return;
    }

    printf("Enter Full Name: ");
    fgets(s.fullName, 100, stdin);
    s.fullName[strcspn(s.fullName, "\n")] = 0;

    printf("Enter Batch (CS/SE/AI/Cyber Security): ");
    fgets(s.batch, 50, stdin);
    s.batch[strcspn(s.batch, "\n")] = 0;

    printf("Enter Membership Type (IEEE/ACM): ");
    fgets(s.membershipType, 10, stdin);
    s.membershipType[strcspn(s.membershipType, "\n")] = 0;

    printf("Enter Registration Date (YYYY-MM-DD): ");
    scanf("%s", s.regDate);

    printf("Enter Date of Birth (YYYY-MM-DD): ");
    scanf("%s", s.dob);

    printf("Interest (IEEE/ACM/Both): ");
    scanf("%s", s.interest);

    ensureCapacity();
    db[dbSize++] = s;
    addStudentToFile(s, FILENAME);

    printf("Student Registered Successfully!\n");
}

void updateStudent() {
    int id;
    printf("Enter Student ID to update: ");
    scanf("%d", &id);

    for (int i = 0; i < dbSize; i++) {
        if (db[i].studentID == id) {
            printf("Update Batch: ");
            scanf("%s", db[i].batch);

            printf("Update Membership (IEEE/ACM): ");
            scanf("%s", db[i].membershipType);

            rewriteDatabase(FILENAME);
            printf("Record updated!\n");
            return;
        }
    }

    printf("Student ID not found.\n");
}

void deleteStudent() {
    int id;
    printf("Enter Student ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < dbSize; i++) {
        if (db[i].studentID == id) {
           
            db[i] = db[dbSize - 1];
            dbSize--;

            deleteStudentFromFile(id, FILENAME);
            printf("Record Deleted Successfully!\n");
            return;
        }
    }

    printf("Student ID not found.\n");
}

void displayAll() {
    if (dbSize == 0) {
        printf("No records found.\n");
        return;
    }

    for (int i = 0; i < dbSize; i++) {
        Student s = db[i];
        printf("\nID: %d\nName: %s\nBatch: %s\nMembership: %s\nReg Date: %s\nDOB: %s\nInterest: %s\n",
               s.studentID, s.fullName, s.batch, s.membershipType,
               s.regDate, s.dob, s.interest);
    }
}

void batchWiseReport() {
    char batch[50];
    char type[10];

    printf("Enter batch to filter: ");
    scanf("%s", batch);

    printf("Enter membership type (IEEE/ACM/Both): ");
    scanf("%s", type);

    printf("\n--- Batch-Wise Report ---\n");

    for (int i = 0; i < dbSize; i++) {
        if (strcmp(db[i].batch, batch) == 0 &&
            strcmp(db[i].interest, type) == 0) {
            printf("%d - %s\n", db[i].studentID, db[i].fullName);
        }
    }
}



void menu() {
    int choice;

    while (1) {
        printf("\n===== IEEE/ACM Membership Manager =====\n");
        printf("1. Register Student\n");
        printf("2. Update Student\n");
        printf("3. Delete Student\n");
        printf("4. View All Students\n");
        printf("5. Batch-wise Reports\n");
        printf("6. Exit\n");
        printf("Choose: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: addStudent(); break;
            case 2: updateStudent(); break;
            case 3: deleteStudent(); break;
            case 4: displayAll(); break;
            case 5: batchWiseReport(); break;
            case 6: saveDatabase(FILENAME);
                    printf("Goodbye!\n");
                    return;
            default: printf("Invalid choice.\n");
        }
    }
}




int main() {
    loadDatabase(FILENAME);
    menu();
    free(db);
    return 0;
}

