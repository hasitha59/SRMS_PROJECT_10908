#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define STUDENT_FILE "students.txt"
#define CREDENTIAL_FILE "credentials.txt"
#define LOG_FILE "logs.txt"
#define BACKUP_FILE "students_backup.txt"

struct Student {
   int roll;
   char name[50];
   float marks;
};

char currentRole[10];
char currentUser[50];

/* FUNCTION PROTOTYPES */
int loginSystem();
void mainMenu();
void adminMenu();
void staffMenu();
void userMenu();
void addStudent();
void displayStudent();
void searchStudent();
void updateStudent();
void deleteStudent();
void sortStudents();
void backupFile();
void changePassword();
void logActivity(const char *user, const char *role);

/*----------------------------------------------------------- MAIN ------------------------------------------------------------*/

int main() {
    if (loginSystem()) {
        mainMenu();
    } else {
        printf("\nAccess Denied. Exiting...\n");
    }
    return 0;
    
}


/*--------------------------------------------- PASSWORD INPUT (HIDDEN) ------------------------------------------------------*/
void inputPassword(char *password) {
    char ch;
    int index = 0;

    while ((ch = getch()) != 13) { // ENTER key
        if (ch == 8 && index > 0) { // BACKSPACE
            printf("\b \b");
            index--;
        } else if (ch != 8) {
            password[index++] = ch;
            printf("*");
        }
    }
    password[index] = '\0';
}

/*----------------------------------------------------- LOGIN SYSTEM --------------------------------------------------------*/
   int loginSystem() {
    char username[50], password[50];
    int attempts = 3;

    while (attempts > 0) {
        printf("==== LOGIN ====\n");
        printf("Username: ");
        scanf("%s", username);

        printf("Password: ");
        inputPassword(password);
        printf("\n");

        // ADMIN LOGIN
        if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
            strcpy(currentRole, "ADMIN");
            strcpy(currentUser, "admin");
            return 1;
        }

        // STAFF LOGIN
        if (strcmp(username, "staff") == 0 && strcmp(password, "staff123") == 0) {
            strcpy(currentRole, "STAFF");
            strcpy(currentUser, "staff");
            return 1;
        }

        // USER LOGIN
        if (strcmp(username, "user") == 0 && strcmp(password, "user123") == 0) {
            strcpy(currentRole, "USER");
            strcpy(currentUser, "user");
            return 1;
        }

        attempts--;
        printf("Incorrect Username or Password! Attempts left: %d\n\n", attempts);
    }

    return 0;
}

/*-------------------------------------------------------- MAIN MENU ---------------------------------------------------------*/
void mainMenu() {
    if (strcmp(currentRole, "ADMIN") == 0)
        adminMenu();
    else if (strcmp(currentRole, "STAFF") == 0)
        staffMenu();
    else
        userMenu();
}

/*-------------------------------------------------------- ADMIN MENU --------------------------------------------------------*/
void adminMenu() {
    int choice;
    do {
        printf("\n====== ADMIN MENU =======\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Sort Students\n");
        printf("7. Backup File\n");
        printf("8. Change Password\n");
        printf("9. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudent(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: sortStudents(); break;
            case 7: backupFile(); break;
            case 8: changePassword(); break;
            case 9: return;
            default: printf("Invalid Choice!\n");
        }
    } while (choice != 9);
}

/*------------------------------------------------------- STAFF MENU ----------------------------------------------------------*/
void staffMenu() {
    int choice;
    do {
        printf("\n====== STAFF MENU =======\n");
        printf("1. Display Students\n");
        printf("2. Search Student\n");
        printf("3. Sort Students\n");
        printf("4. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: displayStudent(); break;
            case 2: searchStudent(); break;
            case 3: sortStudents(); break;
            case 4: return;
            default: printf("Invalid Choice!\n");
        }
    } while (choice != 4);
}

/*------------------------------------------------------- USER MENU ----------------------------------------------------------*/
void userMenu() {
    int choice;
    do {
        printf("\n====== USER MENU =======\n");
        printf("1. Display Students\n");
        printf("2. Search Student\n");
        printf("3. Change Password\n");
        printf("4. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: displayStudent(); break;
            case 2: searchStudent(); break;
            case 3: changePassword(); break;
            case 4: return;
            default: printf("Invalid Choice!\n");
        }
    } while (choice != 4);
}

/*-------------------------------------------------------- FILE FUNCTIONS ----------------------------------------------------*/

void addStudent() {
    struct Student s;
    FILE *fp = fopen(STUDENT_FILE, "a");

    printf("Enter Roll No: ");
    scanf("%d", &s.roll);
    printf("Enter Name: ");
    scanf("%s", s.name);
    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fprintf(fp, "%d %s %f\n", s.roll, s.name, s.marks);
    fclose(fp);

    printf("Student Added!\n");
}

void displayStudent() {
    struct Student s;
    FILE *fp = fopen(STUDENT_FILE, "r");
    if (!fp) {
        printf("No student file found!\n");
        return;
    }

    printf("\nROLL\tNAME\tMARKS\n");
    while (fscanf(fp, "%d %s %f", &s.roll, s.name, &s.marks) == 3) {
        printf("%d\t%s\t%.2f\n", s.roll, s.name, s.marks);
    }
    fclose(fp);
}

void searchStudent() {
    int roll;
    struct Student s;
    int found = 0;
    FILE *fp = fopen(STUDENT_FILE, "r");

    printf("Enter Roll to Search: ");
    scanf("%d", &roll);

    while (fscanf(fp, "%d %s %f", &s.roll, s.name, &s.marks) == 3) {
        if (s.roll == roll) {
            printf("FOUND: %d %s %.2f\n", s.roll, s.name, s.marks);
            found = 1;
        }
    }
    fclose(fp);

    if (!found) printf("Student Not Found!\n");
}

void updateStudent() {
    int roll;
    struct Student s;
    FILE *fp = fopen(STUDENT_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");

    printf("Enter Roll to Update: ");
    scanf("%d", &roll);

    while (fscanf(fp, "%d %s %f", &s.roll, s.name, &s.marks) == 3) {
        if (s.roll == roll) {
            printf("Enter New Name: ");
            scanf("%s", s.name);
            printf("Enter New Marks: ");
            scanf("%f", &s.marks);
        }
        fprintf(temp, "%d %s %f\n", s.roll, s.name, s.marks);
    }
    fclose(fp);
    fclose(temp);
    remove(STUDENT_FILE);
    rename("temp.txt", STUDENT_FILE);

    printf("Record Updated!\n");
}

void deleteStudent() {
    int roll;
    struct Student s;
    FILE *fp = fopen(STUDENT_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");

    printf("Enter Roll to Delete: ");
    scanf("%d", &roll);

    while (fscanf(fp, "%d %s %f", &s.roll, s.name, &s.marks) == 3) {
        if (s.roll != roll)
            fprintf(temp, "%d %s %f\n", s.roll, s.name, s.marks);
    }

    fclose(fp);
    fclose(temp);
    remove(STUDENT_FILE);
    rename("temp.txt", STUDENT_FILE);

    printf("Student Deleted!\n");
}

/*-------------------------------------------------------- SORT STUDENTS ---------------------------------------------------*/
void sortStudents() {
    struct Student arr[100], temp;
    int n = 0, choice;

    FILE *fp = fopen(STUDENT_FILE, "r");
    while (fscanf(fp, "%d %s %f", &arr[n].roll, arr[n].name, &arr[n].marks) == 3)
        n++;
    fclose(fp);

    printf("Sort By:\n1. Roll\n2. Name\n3. Marks\nChoice: ");
    scanf("%d", &choice);

    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++) {

            int cmp = 0;
            if (choice == 1 && arr[i].roll > arr[j].roll) cmp = 1;
            if (choice == 2 && strcmp(arr[i].name, arr[j].name) > 0) cmp = 1;
            if (choice == 3 && arr[i].marks > arr[j].marks) cmp = 1;

            if (cmp) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }

    fp = fopen(STUDENT_FILE, "w");
    for (int i = 0; i < n; i++)
        fprintf(fp, "%d %s %f\n", arr[i].roll, arr[i].name, arr[i].marks);
    fclose(fp);

    printf("Sorted Successfully!\n");
}

/*-------------------------------------------------------- BACKUP FILE ------------------------------------------------------*/
void backupFile() {
    FILE *src = fopen(STUDENT_FILE, "r");
    FILE *dst = fopen(BACKUP_FILE, "w");
    char ch;

    while ((ch = fgetc(src)) != EOF)
        fputc(ch, dst);

    fclose(src);
    fclose(dst);

    printf("Backup Created!\n");
}

/*-------------------------------------------------------- CHANGE PASSWORD --------------------------------------------------*/
void changePassword() {
    char oldPass[50], newPass[50];
    char fileUser[50], filePass[50], fileRole[10];
    int found = 0;

    printf("Enter Old Password: ");
    inputPassword(oldPass);
    printf("\n");

    FILE *fp = fopen(CREDENTIAL_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");

    while (fscanf(fp, "%s %s %s", fileUser, filePass, fileRole) == 3) {
        if (strcmp(currentUser, fileUser) == 0 && strcmp(oldPass, filePass) == 0) {
            found = 1;
            printf("Enter New Password: ");
            inputPassword(newPass);
            printf("\n");
            fprintf(temp, "%s %s %s\n", fileUser, newPass, fileRole);
        } else {
            fprintf(temp, "%s %s %s\n", fileUser, filePass, fileRole);
        }
    }

    fclose(fp);
    fclose(temp);
    remove(CREDENTIAL_FILE);
    rename("temp.txt", CREDENTIAL_FILE);

    if (found)
        printf("Password Changed Successfully!\n");
    else
        printf("Incorrect Old Password!\n");
}

/*-------------------------------------------------------- LOGIN LOGS -------------------------------------------------------*/
void logActivity(const char *user, const char *role) {
    FILE *fp = fopen(LOG_FILE, "a");

    fprintf(fp, "%s %s logged in\n", user, role);

    fclose(fp);
}
