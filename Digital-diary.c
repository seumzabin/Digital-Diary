#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ENTRIES 500
#define MAX_TEXT 1024
#define MAX_USER 100
#include <conio.h>   // ADD THIS for getch()

void getMaskedPassword(char *password, int maxLen) {
    int index = 0;
    char ch;

    while (1) {
        ch = getch();  // read a character without showing it

        if (ch == '\r') {  // Enter key
            password[index] = '\0';
            printf("\n");
            return;
        }
        else if (ch == '\b') {  // Backspace
            if (index > 0) {
                index--;
                printf("\b \b"); // erase last *
            }
        }
        else if (index < maxLen - 1) {
            password[index++] = ch;
            printf("*");   // print mask
        }
    }
}


// File paths
const char *PLANNER_FILE = "planner.txt";
const char *TODO_FILE    = "todo.txt";
const char *JOURNAL_FILE = "journal.txt";
const char *USER_FILE    = "users.txt";

// Entry storage
char planner[MAX_ENTRIES][MAX_TEXT];
int plannerCount = 0;

char todoList[MAX_ENTRIES][MAX_TEXT];
int todoCount = 0;

char journal[MAX_ENTRIES][MAX_TEXT];
int journalCount = 0;

// Function declarations
void loadAll();
void saveAll();
void loadSection(const char *filename, char entries[][MAX_TEXT], int *count);
void saveSection(const char *filename, char entries[][MAX_TEXT], int count);

void mainMenu();
void plannerSection();
void todoSection();
void journalSection();

void addEntry(char entries[][MAX_TEXT], int *count, const char *filename);
void viewEntries(char entries[][MAX_TEXT], int count);
void editEntry(char entries[][MAX_TEXT], int *count, const char *filename);
void deleteEntry(char entries[][MAX_TEXT], int *count, const char *filename);

void readLine(char *buffer, int size);
int getIntInput();

// Login functions
int loginScreen();
int signUp();
int login();


// MAIN FUNCTION
int main() {
    if (!loginScreen()) {
        printf("Exiting program...\n");
        return 0;
    }

    loadAll();
    mainMenu();

    return 0;
}


// LOGIN MENU
int loginScreen() {
    while (1) {
        printf("\n==============================\n");
        printf("        DIGITAL DIARY\n");
        printf("==============================\n");
        printf("1. Login\n");
        printf("2. Sign Up\n");
        printf("3. Exit\n");
        printf("Choose an option: ");

        int choice = getIntInput();

        if (choice == 1) return login();
        else if (choice == 2) signUp();
        else if (choice == 3) return 0;
        else printf("Invalid option.\n");
    }
}


// USER SIGN-UP
int signUp() {
    char user[100], pass[100];

    printf("\n--- SIGN UP ---\n");
    printf("Create username: ");
    readLine(user, sizeof(user));

    printf("Create password: ");
    getMaskedPassword(pass, sizeof(pass));

    // Save account
    FILE *fp = fopen(USER_FILE, "a");
    fprintf(fp, "%s %s\n", user, pass);
    fclose(fp);

    printf("Account created successfully!\n");
    return 1;
}


// USER LOGIN
int login() {
    char user[100], pass[100], fileUser[100], filePass[100];
    int attempts = 3;

    while (attempts--) {
        printf("\n--- LOGIN ---\n");
        printf("Username: ");
        readLine(user, sizeof(user));

        printf("Password: ");
        getMaskedPassword(pass, sizeof(pass));

        FILE *fp = fopen(USER_FILE, "r");
        if (!fp) {
            printf("No user accounts found. Please sign up first.\n");
            return 0;
        }

        while (fscanf(fp, "%s %s", fileUser, filePass) != EOF) {
            if (strcmp(user, fileUser) == 0 && strcmp(pass, filePass) == 0) {
                fclose(fp);
                printf("Login successful!\n");
                return 1;
            }
        }

        fclose(fp);
        printf("Incorrect credentials. Attempts left: %d\n", attempts);
    }

    return 0;
}



// LOAD ALL ENTRIES
void loadAll() {
    loadSection(PLANNER_FILE, planner, &plannerCount);
    loadSection(TODO_FILE, todoList, &todoCount);
    loadSection(JOURNAL_FILE, journal, &journalCount);
}


// SAVE ALL ENTRIES
void saveAll() {
    saveSection(PLANNER_FILE, planner, plannerCount);
    saveSection(TODO_FILE, todoList, todoCount);
    saveSection(JOURNAL_FILE, journal, journalCount);
}


// LOAD SECTION
void loadSection(const char *filename, char entries[][MAX_TEXT], int *count) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        *count = 0;
        return;
    }

    char line[MAX_TEXT];
    int i = 0;
    while (i < MAX_ENTRIES && fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\n")] = '\0';
        strncpy(entries[i], line, MAX_TEXT - 1);
        entries[i][MAX_TEXT - 1] = '\0';
        i++;
    }
    *count = i;
    fclose(fp);
}


// SAVE SECTION
void saveSection(const char *filename, char entries[][MAX_TEXT], int count) {
    FILE *fp = fopen(filename, "w");
    if (!fp) return;

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s\n", entries[i]);
    }

    fclose(fp);
}



// MAIN MENU
void mainMenu() {
    while (1) {
        printf("\n==============================\n");
        printf("        MAIN MENU\n");
        printf("==============================\n");
        printf("1. Planner\n");
        printf("2. To-Do List\n");
        printf("3. Journaling\n");
        printf("4. Save & Exit\n");
        printf("Enter your choice: ");

        int choice = getIntInput();

        if (choice == 1) plannerSection();
        else if (choice == 2) todoSection();
        else if (choice == 3) journalSection();
        else if (choice == 4) {
            saveAll();
            printf("Saved. Goodbye!\n");
            return;
        }
        else printf("Invalid choice.\n");
    }
}



// PLANNER SECTION
void plannerSection() {
    while (1) {
        printf("\n--- PLANNER ---\n");
        printf("1. Add Entry\n");
        printf("2. View Entries\n");
        printf("3. Edit Entry\n");
        printf("4. Delete Entry\n");
        printf("5. Back\n");
        printf("Choice: ");

        int c = getIntInput();
        if (c == 1) addEntry(planner, &plannerCount, PLANNER_FILE);
        else if (c == 2) viewEntries(planner, plannerCount);
        else if (c == 3) editEntry(planner, &plannerCount, PLANNER_FILE);
        else if (c == 4) deleteEntry(planner, &plannerCount, PLANNER_FILE);
        else if (c == 5) return;
        else printf("Invalid choice.\n");
    }
}



// TO-DO SECTION
void todoSection() {
    while (1) {
        printf("\n--- TO-DO LIST ---\n");
        printf("1. Add Item\n");
        printf("2. View Items\n");
        printf("3. Edit Item\n");
        printf("4. Delete Item\n");
        printf("5. Back\n");
        printf("Choice: ");

        int c = getIntInput();
        if (c == 1) addEntry(todoList, &todoCount, TODO_FILE);
        else if (c == 2) viewEntries(todoList, todoCount);
        else if (c == 3) editEntry(todoList, &todoCount, TODO_FILE);
        else if (c == 4) deleteEntry(todoList, &todoCount, TODO_FILE);
        else if (c == 5) return;
        else printf("Invalid choice.\n");
    }
}



// JOURNAL SECTION
void journalSection() {
    while (1) {
        printf("\n--- JOURNALING ---\n");
        printf("1. Add Entry\n");
        printf("2. View Entries\n");
        printf("3. Edit Entry\n");
        printf("4. Delete Entry\n");
        printf("5. Back\n");
        printf("Choice: ");

        int c = getIntInput();
        if (c == 1) addEntry(journal, &journalCount, JOURNAL_FILE);
        else if (c == 2) viewEntries(journal, journalCount);
        else if (c == 3) editEntry(journal, &journalCount, JOURNAL_FILE);
        else if (c == 4) deleteEntry(journal, &journalCount, JOURNAL_FILE);
        else if (c == 5) return;
        else printf("Invalid choice.\n");
    }
}



// ADD ENTRY
void addEntry(char entries[][MAX_TEXT], int *count, const char *filename) {
    if (*count >= MAX_ENTRIES) {
        printf("Cannot add more entries.\n");
        return;
    }

    printf("Enter your text:\n> ");
    char buffer[MAX_TEXT];
    readLine(buffer, sizeof(buffer));

    strncpy(entries[*count], buffer, MAX_TEXT - 1);
    entries[*count][MAX_TEXT - 1] = '\0';

    (*count)++;
    saveSection(filename, entries, *count);

    printf("Entry added.\n");
}



// VIEW ENTRIES
void viewEntries(char entries[][MAX_TEXT], int count) {
    if (count == 0) {
        printf("No entries found.\n");
        return;
    }

    printf("\n-- ENTRIES (%d) --\n", count);
    for (int i = 0; i < count; i++)
        printf("%d) %s\n", i + 1, entries[i]);
}



// EDIT ENTRY
void editEntry(char entries[][MAX_TEXT], int *count, const char *filename) {
    if (*count == 0) {
        printf("No entries to edit.\n");
        return;
    }

    viewEntries(entries, *count);
    printf("Select entry to edit: ");

    int idx = getIntInput();
    if (idx < 1 || idx > *count) {
        printf("Invalid number.\n");
        return;
    }

    idx--;

    printf("Current text:\n%s\n", entries[idx]);
    printf("Enter new text:\n> ");

    char buffer[MAX_TEXT];
    readLine(buffer, sizeof(buffer));

    strncpy(entries[idx], buffer, MAX_TEXT - 1);
    entries[idx][MAX_TEXT - 1] = '\0';

    saveSection(filename, entries, *count);

    printf("Entry updated.\n");
}



// DELETE ENTRY
void deleteEntry(char entries[][MAX_TEXT], int *count, const char *filename) {
    if (*count == 0) {
        printf("Nothing to delete.\n");
        return;
    }

    viewEntries(entries, *count);
    printf("Select entry to delete: ");

    int idx = getIntInput();
    if (idx < 1 || idx > *count) return;
    idx--;

    for (int i = idx; i < *count - 1; i++) {
        strcpy(entries[i], entries[i + 1]);
    }

    (*count)--;

    saveSection(filename, entries, *count);

    printf("Entry deleted.\n");
}



// SAFE READ LINE
void readLine(char *buffer, int size) {
    fgets(buffer, size, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
}



// SAFE INTEGER INPUT
int getIntInput() {
    char buf[64];
    fgets(buf, sizeof(buf), stdin);
    return atoi(buf);
}

