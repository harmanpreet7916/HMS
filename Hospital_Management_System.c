#include<stdio.h>
#include<windows.h>
#include<conio.h> 
#include<ctype.h> 
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

// Function prototypes
void startScreen();
void Title();
void MainMenu();
void LoginScreen();
void Add_rec();
void func_list();
void Search_rec();
void Edit_rec();
void Delete_rec();
void Exit_hospital();
bool do_authorization(char*, char*, char*, char*);
void gotoxy(short x, short y) {
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// Structure to hold patient details
struct patient {
    int age;
    char gender;
    char first_name[20];
    char last_name[20];
    char contact_no[20];
    char address[100];
    char email[50];
    char doctor[20];
    char problem[50];
};
struct patient p, temp_patient;

// Main function
int main() {
    startScreen();
    Title();
    LoginScreen();
}

// Function to display the start screen
void startScreen() {
    printf("\n\n\n\n\n\t\t\t --------------------------------------");
    printf("\n\t\t\tWELCOME TO HOSPITAL MANAGEMENT SYSTEM");
    printf("\n\t\t\t ---------------------------------------\n");
    printf("\n\nPress any key to continue...\n");
    getch();  // Wait for a key press
    system("cls");  // Clear screen
}

// Function to display the title
void Title() {
    printf("\n\n\n\n\n\t\t\t --------------------------------");
    printf("\n\t\t\t     HOSPITAL MANAGEMENT SYSTEM");
    printf("\n\t\t\t --------------------------------\n");
}

// Function to display the login screen
void LoginScreen() {
    bool authorized = false;
    int attempts = 3;
    char username[20];
    char password[20];
    char authorized_username[20] = "harman";
    char authorized_password[20] = "coder";
    do {
        printf("\n\n\n\n\t\t\t\tEnter Username and Password: ");
        printf("\n\n\t\t\tUsername: ");
        scanf("%s", username);  // Read username
        printf("\n\n\t\t\tPassword: ");
        scanf("%s", password);  // Read password
        authorized = do_authorization(username, password, authorized_username, authorized_password);  // Check credentials
        if (authorized) {
            printf("\n\n\t\t\tLOGIN SUCCESSFUL\n");
            printf("\n\n\t\t\tWELCOME INSIDE THE HOSPITAL MANAGEMENT SYSTEM\n");
            MainMenu();  // Enter main menu
            break;
        } else {
            attempts--;
            if (attempts == 0) {
                printf("\n\n\t\t\tACCESS DENIED!! EXIT\n");
                exit(0);
            }
            printf("\n\n\t\t\tWRONG CREDENTIALS!! LOGIN AGAIN: %d ATTEMPTS LEFT\n", attempts);
        }
    } while (!authorized);
    system("cls");  // Clear screen
}

// Function to check authorization
bool do_authorization(char* username, char* password, char* correct_username, char* correct_password) {
    return (strcmp(username, correct_username) == 0) && (strcmp(password, correct_password) == 0);
}

// Function to display the main menu
void MainMenu() {
    system("cls");
    int choice;
    Title();
    printf("\n\n\n\t\t\t1. Add Patient Record\n");
    printf("\n\t\t\t2. List Patient Records\n");
    printf("\n\t\t\t3. Search Patient Records\n");
    printf("\n\t\t\t4. Edit Patient Records\n");
    printf("\n\t\t\t5. Delete Patient Records\n");
    printf("\n\t\t\t6. Exit\n");
    printf("\n\n\n\n\t\t\tChoose from 1-6: ");
    scanf("%d", &choice);  // Read user choice
    switch (choice) {
        case 1: Add_rec();
            break;
        case 2: func_list();
            break;
        case 3: Search_rec();
            break;
        case 4: Edit_rec();
            break;
        case 5: Delete_rec();
            break;
        case 6: Exit_hospital();
            exit(0);
        default: 
            printf("\n\t\t\tENTER CORRECT CHOICE\n");
            MainMenu();  // Invalid choice, show menu again
    }
    MainMenu();
}

// Function to add a patient record
void Add_rec() {
    system("cls");
    Title();
    FILE* fp = fopen("patients.dat", "a");
    if (fp == NULL) {
        printf("\n\t\t\tError opening file!");
        return;
    }

    printf("\n\n\n\t\t\t!!!!!! ADD PATIENT DETAILS !!!!!!\n");

    printf("\n\t\t\tFirst Name: ");
    scanf("%s", p.first_name);
    p.first_name[0] = toupper(p.first_name[0]);

    printf("\n\t\t\tLast Name: ");
    scanf("%s", p.last_name);
    p.last_name[0] = toupper(p.last_name[0]);

    fflush(stdin);

    do {
        printf("\n\t\t\tGender(M/F): ");
        scanf("%c", &p.gender);
        p.gender = toupper(p.gender);
        if (p.gender != 'M' && p.gender != 'F') {
            printf("\n\t\t\tENTER CORRECT GENDER\n");
        }
    } while (p.gender != 'M' && p.gender != 'F');

    printf("\n\t\t\tAGE: ");
    scanf("%d", &p.age);

    fflush(stdin);

    printf("\n\t\t\tAddress: ");
    gets(p.address);
    p.address[0] = toupper(p.address[0]);

    fflush(stdin);

    printf("\n\t\t\tContact No.: ");
    scanf("%s", p.contact_no);

    fflush(stdin);

    printf("\n\t\t\tEmail Address: ");
    scanf("%s", p.email);

    fflush(stdin);

    printf("\n\t\t\tDoctor: ");
    gets(p.doctor);

    fflush(stdin);

    printf("\n\t\t\t Health Issue Details: ");
    gets(p.problem);

    fflush(stdin);

    if (fwrite(&p, sizeof(struct patient), 1, fp) == 1) {
        printf("\n\t\t\tDATA WRITTEN SUCCESSFULLY\n");
    } else {
        printf("\n\t\t\tERROR WRITING DATA\n");
    }

    fclose(fp);
    getch();

    printf("\n\n\n\t\t\tDO YOU WANT TO ADD MORE DATA[Y/N]\n");
    char choice;
    scanf(" %c", &choice);  // Read choice
    choice = toupper(choice);
    if (choice == 'Y') {
        Add_rec();
    }
    printf("\n\t\t\tTHANK YOU\n");
}

// Function to list all patient records
void func_list() {
    system("cls");
    Title();

    FILE* fp = fopen("patients.dat", "r");
    if (fp == NULL) {
        printf("\n\t\t\tError opening file!");
        return;
    }

    printf("\n\n\t\t\tListing Patients Records\n");
    gotoxy(1, 15);
    printf("Full Name");
    gotoxy(25, 15);
    printf("Gender");
    gotoxy(32, 15);
    printf("Age");
    gotoxy(45, 15);
    printf("Address");
    gotoxy(59, 15);
    printf("Contact No.");
    gotoxy(74, 15);
    printf("Email");
    gotoxy(88, 15);
    printf("Issue");
    gotoxy(108, 15);
    printf("Doctor\n");
    printf("-----------------------------------------------------------------------------------------------------------------------");

    int row = 17;

    struct patient* pat = (struct patient*)malloc(1 * sizeof(struct patient));
    if (pat == NULL) {
        printf("\n\t\t\tMemory allocation failed!");
        fclose(fp);
        return;
    }

    while (fread(pat, 1, sizeof(struct patient), fp)) {
        gotoxy(1, row);
        printf("%s %s", pat->first_name, pat->last_name);
        gotoxy(25, row);
        printf("%c", pat->gender);
        gotoxy(32, row);
        printf("%d", pat->age);
        gotoxy(45, row);
        puts(pat->address);
        gotoxy(59, row);
        printf("%s", pat->contact_no);
        gotoxy(74, row);
        printf(pat->email);
        gotoxy(98, row);
        puts(pat->problem);
        gotoxy(110, row);
        puts(pat->doctor);
        row++;
    }

    free(pat);
    fclose(fp);
    getch();
    MainMenu();
}

// Function to search for a patient record by contact number
void Search_rec() {
    system("cls");
    Title();

    FILE* fp = fopen("patients.dat", "r");
    if (fp == NULL) {
        printf("\n\t\t\tError opening file!");
        return;
    }

    printf("\n\n\t\t\tEnter the contact number of the record to be searched\n");

    char number[20];
    scanf("%s", number);

    struct patient* pat = (struct patient*)malloc(1 * sizeof(struct patient));
    if (pat == NULL) {
        printf("\n\t\t\tMemory allocation failed!");
        fclose(fp);
        return;
    }

    bool found = false;
    while (fread(pat, 1, sizeof(struct patient), fp)) {
        if (strcmp(pat->contact_no, number) == 0) {
            printf("\n\n\t\t\tRECORD FOUND\n");
            found = true;
            printf("\n\t\t\tNAME: %s %s\n", pat->first_name, pat->last_name);
            printf("\n\t\t\tAGE: %d\n", pat->age);
            printf("\n\t\t\tGENDER: %c\n", pat->gender);
            printf("\n\t\t\tCONTACT NUMBER: %s\n", pat->contact_no);
            printf("\n\t\t\tEMAIL: %s\n", pat->email);
            printf("\n\t\t\tPROBLEM: %s\n", pat->problem);
            printf("\n\t\t\tDOCTOR: %s\n", pat->doctor);
            break;
        }
    }

    if (!found) {
        printf("\n\n\t\t\tSORRY!! NO RECORD FOUND\n");
    }

    free(pat);
    fclose(fp);
    getch();
    MainMenu();
}

// Function to edit a patient record
void Edit_rec() {
    system("cls");
    Title();

    FILE* fpr = fopen("patients.dat", "r");
    FILE* fpw = fopen("temp.dat", "w");
    if (fpr == NULL || fpw == NULL) {
        printf("\n\t\t\tError opening file!");
        return;
    }

    printf("\n\n\t\t\tEnter the contact number of the record to be edited\n");

    char number[20];
    scanf("%s", number);

    struct patient* pat = (struct patient*)malloc(1 * sizeof(struct patient));
    if (pat == NULL) {
        printf("\n\t\t\tMemory allocation failed!");
        fclose(fpr);
        fclose(fpw);
        return;
    }

    bool found = false;
    while (fread(pat, 1, sizeof(struct patient), fpr)) {
        if (strcmp(pat->contact_no, number) == 0) {
            printf("\n\n\t\t\tRECORD FOUND! ENTER NEW DETAILS\n");
            found = true;
            printf("\n\t\t\tFIRST NAME: ");
            fflush(stdin);
            scanf("%s", pat->first_name);
            printf("\n\t\t\tLAST NAME: ");
            fflush(stdin);
            scanf("%s", pat->last_name);
            printf("\n\t\t\tAGE: ");
            fflush(stdin);
            scanf("%d", &pat->age);
            printf("\n\t\t\tGENDER: ");
            fflush(stdin);
            scanf(" %c", &pat->gender);  // Space before %c to consume the newline character
            printf("\n\t\t\tCONTACT NUMBER: ");
            fflush(stdin);
            scanf("%s", pat->contact_no);
            printf("\n\t\t\tEMAIL: ");
            fflush(stdin);
            scanf("%s", pat->email);
            printf("\n\t\t\tPROBLEM: ");
            fflush(stdin);
            gets(pat->problem);
            printf("\n\t\t\tDOCTOR: ");
            fflush(stdin);
            gets(pat->doctor);
            fflush(stdin);
        }
        fwrite(pat, 1, sizeof(struct patient), fpw);
    }

    if (!found) {
        printf("\n\n\t\t\tSORRY!! NO RECORD FOUND\n");
    } else {
        printf("\n\n\t\t\tDATA SUCCESSFULLY EDITED\n");
    }

    free(pat);
    fclose(fpr);
    fclose(fpw);
    remove("patients.dat");
    rename("temp.dat", "patients.dat");
    getch();
    MainMenu();
}

// Function to delete a patient record
void Delete_rec() {
    system("cls");
    Title();

    FILE* fpr = fopen("patients.dat", "r");
    FILE* fpw = fopen("temp.dat", "w");
    if (fpr == NULL || fpw == NULL) {
        printf("\n\t\t\tError opening file!");
        return;
    }

    printf("\n\n\t\t\tEnter the contact number of the record to be deleted\n");

    char number[20];
    scanf("%s", number);

    struct patient* pat = (struct patient*)malloc(1 * sizeof(struct patient));
    if (pat == NULL) {
        printf("\n\t\t\tMemory allocation failed!");
        fclose(fpr);
        fclose(fpw);
        return;
    }

    bool found = false;
    while (fread(pat, 1, sizeof(struct patient), fpr)) {
        if (strcmp(pat->contact_no, number) == 0) {
            found = true;
            continue;  // Skip this record
        }
        fwrite(pat, 1, sizeof(struct patient), fpw);
    }

    if (!found) {
        printf("\n\n\t\t\tSORRY!! NO RECORD FOUND\n");
    } else {
        printf("\n\n\t\t\tRECORD DELETED SUCCESSFULLY\n");
    }

    free(pat);
    fclose(fpr);
    fclose(fpw);
    remove("patients.dat");
    rename("temp.dat", "patients.dat");
    getch();
    MainMenu();
}

// Function to display exit message
void Exit_hospital() {
    system("cls");
    Title();
    printf("\n\n\t\t\tTHANK YOU FOR USING THE HOSPITAL MANAGEMENT SYSTEM\n ");
    printf("\n\n\t\t\tHAVE A GOOD DAY\n");
}
