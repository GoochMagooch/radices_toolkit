#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// CLEAR TERMINAL
void clear() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void menu_banner() {
    printf(" ___         _ _             _____         _ _   _ _\n");
    printf("| _ \\__ _ __| (_)__ ___ ___ |_   _|__  ___| | |_(_) |_\n");
    printf("|   / _` / _` | / _/ -_|_-<   | |/ _ \\/ _ \\ | / / |  _|\n");
    printf("|_|_\\__,_\\__,_|_\\__\\___/__/   |_|\\___/\\___/_|_\\_\\_|\\__|\n\n");
}

void display_menu() {
    printf("Welcome to your Radices Toolkit!\n\n");

    // menu options
    printf("1. Decimal to Radices Converter\n");
    printf("2. Radices to Decimal Converter\n");
    printf("3. Radices Calculator\n\n");
}

/*
// FIND LENGTH OF ARRAY
int length(char* arr) {
    int len = sizeof(arr) / sizeof(arr[0]);

    return len;
}
*/

int return_int(char ch) {
    int n = 0;

    if (ch >= '0' && ch <= '9') {
        n = ch - '0';
    }

    return n;
}

// DECIMAL TO RADICES CONVERTER
void decimal_to_radix() {

    clear();
    menu_banner();
    printf("DECIMAL TO RADICES CONVERTER\n");
    printf("Convert decimal numbers to radices (binary - hexadecimal)!\n\n");

    bool persist = true;

    while(persist) {
        char decimal[10];
        int radix;

        printf("Enter your number: ");
        scanf("%9s", decimal);

        printf("Enter your radix: ");
        scanf("%d", &radix);

        /*
        int len = 0;
        for (int i = 0; decimal[i] != '\0'; i++) {
            len += 1;
        }

        int int_arr[len];
        for (int i = 0; decimal[i] != '\0'; i++) {
            int_arr[i] = return_int(decimal[i]);
        }

        int final_arr[len];
        int position = len-1;
        int ans = 0;
        for (int i = 0; i < len; i++) {
            if (int_arr[i] >= radix) {
                printf("Invalid digit in base %d: %d\n", radix, int_arr[i]);
                break;
            } else {
                if (position > 0) {
                    if (position == 1) {
                        ans += int_arr[i] * radix
                    }
                    ans += int_arr[i] * ();
                } else {
                    ans += int_arr[i] * 1;
                }
            }
        }
        */

        persist = false;
    }

    printf("Coming soon! Program ending...\n");
}

// RADICES TO DECIMAL CONVERTER
void radix_to_decimal() {
    clear();
    menu_banner();
    printf("RADICES TO DECIMAL CONVERTER\n");
    printf("Convert radices (binary - hexadecimal) to decimal!\n\n");

    bool persist = true;

    while(persist) {
        char number[10];
        int radix;

        printf("Enter your radix: ");
        scanf("%d", &radix);

        printf("Enter your base %d number: ", radix);
        scanf("%9s", number);
 
        int len = 0;
        for (int i = 0; number[i] != '\0'; i++) {
            len += 1;
        }

        int int_arr[len];
        for (int i = 0; number[i] != '\0'; i++) {
            if (number[i] == 'A') {
                int_arr[i] = 10;
            } else {
                int_arr[i] = return_int(number[i]);
            }
        }

        int ans = 0;

        int final_arr[len];
        int position = len-1;
        int position_radix = radix;
        for (int i = 0; i < len; i++) {
            if (int_arr[i] >= radix) {
                //TODO: add checks for integers larger than radix
                break;
            } else {
                if (position == 0) {
                    ans += int_arr[i] * 1;
                } else if (position == 1) {
                    ans += int_arr[i] * radix;
                } else {
                    for (int i = 0; i < position-1; i++) {
                        position_radix = position_radix * radix;
                    }
                    ans += int_arr[i] * position_radix;
                    position_radix = radix;
                }
            }
            position -= 1;
        }

        printf("Your number in decimal: %d\n", ans);
        persist = false;
    }
}

// RADICES CALCULATOR
void radices_calculator() {
    clear();
    menu_banner();
    printf("RADICES CALCULATOR\n");
    printf("Add, Subtract or Multiply radices from binary to hexadecimal!\n\n");

    bool persist = true;
    while (persist) {
        int radix;
        printf("Choose your radix: ");
        scanf("%d", &radix);

        int radix_num1;
        printf("Enter your first number in base %d: ", radix);
        scanf("%d", &radix_num1);

        char op;
        printf("Enter your operator (*, + or -): ");
        scanf(" %c", &op);

        int radix_num2;
        printf("Enter your second number in base %d: ", radix);
        scanf("%d", &radix_num2);

        persist = false;
    }

    printf("Thank you, calculator coming soon...\n");
}

// MAIN MENU
int main() {

    // menu functionality
    bool menu_persist = true;
    bool run_menu = true;
    while (menu_persist) {
        if (run_menu) {
            clear();
            menu_banner();
            display_menu();
        } else {
            clear();
            menu_banner();
            display_menu();
            printf("Incorrect choice\n");
        }
        char choice[16];
        printf("Choose your tool (1-3): ");
        scanf("%15s", choice);
        if (strcmp(choice, "1") == 0) {
            decimal_to_radix();
            menu_persist = false;
        } else if (strcmp(choice, "2") == 0) {
            radix_to_decimal();
            menu_persist = false;
        } else if (strcmp(choice, "3") == 0) {
            radices_calculator();
            menu_persist = false;
        } else if (strcmp(choice, "exit") == 0) {
            return EXIT_SUCCESS;
        } else {
            run_menu = false;
            printf("test\n");
        }
    }

    return EXIT_SUCCESS;
}

