#include <stdio.h>
#include <string.h>

struct employee {
    int ID;
    char name[50];
    char designation[100];
    float salary;
};


void displayemployee(struct employee emp[], int n) {
    printf("%-10s %-15s %-15s %-10s\n", "ID", "NAME", "DESIGNATION", "SALARY");
    printf("--------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%-10d %-15s %-15s %-10.2f\n", emp[i].ID, emp[i].name, emp[i].designation, emp[i].salary);
    }
}


void highestsalary(struct employee emp[], int n) {
    int index = 0;  
    for (int i = 1; i < n; i++) {
        if (emp[i].salary > emp[index].salary) {
            index = i;
        }
    }
    printf("The highest salary employee:\n");
    printf("%-10s %-15s %-15s %-10s\n", "ID", "NAME", "DESIGNATION", "SALARY");
    printf("--------------------------------------------------------\n");
    printf("%-10d %-15s %-15s %-10.2f\n", emp[index].ID, emp[index].name, emp[index].designation, emp[index].salary);
}

void searchIdName(struct employee emp[], int n) {
    int choice;
    int found = 0;
    int id;
    char name[50];

    printf("Search by:\n1. ID\n2. Name\nEnter choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Enter ID to search: ");
        scanf("%d", &id);
        for (int i = 0; i < n; i++) {
            if (emp[i].ID == id) {
                found = 1;
                printf("Record Found:\n");
                printf("%-10s %-15s %-15s %-10s\n", "ID", "NAME", "DESIGNATION", "SALARY");
                printf("--------------------------------------------------------\n");
                printf("%-10d %-15s %-15s %-10.2f\n", emp[i].ID, emp[i].name, emp[i].designation, emp[i].salary);
                break;
            }
        }
    } else if (choice == 2) {
        printf("Enter Name to search: ");
        scanf("%s", name);
        for (int i = 0; i < n; i++) {
            if (strcmp(emp[i].name, name) == 0) {
                found = 1;
                printf("Record Found:\n");
                printf("%-10s %-15s %-15s %-10s\n", "ID", "NAME", "DESIGNATION", "SALARY");
                printf("--------------------------------------------------------\n");
                printf("%-10d %-15s %-15s %-10.2f\n", emp[i].ID, emp[i].name, emp[i].designation, emp[i].salary);
                break;
            }
        }
    }

    if (!found) {
        printf("No employee found.\n");
    }
}


void giveBonus(struct employee emp[], int n, float threshold) {
    for (int i = 0; i < n; i++) {
        if (emp[i].salary < threshold) {
            emp[i].salary += emp[i].salary * 0.10;
        }
    }
}

int main() {
    int n;
    printf("Enter number of employees: ");
    scanf("%d", &n);

    struct employee emp[n];

    for (int i = 0; i < n; i++) {
        printf("\nEnter details for Employee %d:\n", i + 1);
        printf("ID: ");
        scanf("%d", &emp[i].ID);
        printf("Name: ");
        scanf("%s", emp[i].name);
        printf("Designation: ");
        scanf("%s", emp[i].designation);
        printf("Salary: ");
        scanf("%f", &emp[i].salary);
    }

    printf("\n--- All Employee Records ---\n");
    displayemployee(emp, n);

    printf("\n--- Employee with Highest Salary ---\n");
    highestsalary(emp, n);

    printf("\n--- Search Employee ---\n");
    searchIdName(emp, n);

    printf("\n--- Giving Bonus to Employees earning < 50000 ---\n");
    giveBonus(emp, n, 50000);

    printf("\n--- Updated Employee Records After Bonus ---\n");
    displayemployee(emp, n);

    return 0;
}

	

