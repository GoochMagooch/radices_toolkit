#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// TODO: Don't end program after calculation finishes or error detected

// CLEAR TERMINAL
void clear() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// DISPLAY MENU BANNER
void menu_banner() {
    printf(".___         _ _            ._____.        _ _   _ _\n");
    printf("| _ \\__ _ __| (_)__ ___ ___ |_   _|__  ___| | |_(_) |_\n");
    printf("|   / _` / _` | / _/ -_|_-<   | |/ _ \\/ _ \\ | / / |  _|\n");
    printf("|_|_\\__,_\\__,_|_\\__\\___/__/   |_|\\___/\\___/_|_\\_\\_|\\__|\n\n");
}

// DISPLAY MAIN MENU
void display_menu() {
    printf("Welcome to your Radices Toolkit!\n\n");

    // menu options
    printf("1. Decimal to Radices Converter\n");
    printf("2. Radices to Decimal Converter\n");
    printf("3. Radices Calculator\n\n");
}

// RETURN LENGTH OF CHAR ARRAY
int arr_len(char *arr) {
    int len = 0;
    for (int i = 0; arr[i] != '\0'; i++) {
        len += 1;
    }
    return len;
}

// CONVERT CHARACTER TO INTEGER
int return_int(char ch) {
    int n = 0;
    int counter = 10;

    if (ch >= '0' && ch <= '9') {
        n = ch - '0';
        return n;
    } else {
        for (int i = 97; i < 123; i++) {
            if (tolower(ch) == i) {
                n = counter;
                return n;
            } else {
                counter++;
            }
        }
    }
    return -1;
}

// CONVERT INTEGER TO ASCII CHARACTER
char return_char(int num) {
    char ch;
    int int_counter = 0;

    for (int i = 48; i < 58; i++) {
        if (num == int_counter) {
            ch = i;
            return ch;
        } else {
            int_counter++;
        }
    }

    int_counter = 10;
    for (int i = 65; i < 91; i++) {
        if (num == int_counter) {
            ch = i;
            return ch;
        } else {
            int_counter++;
        }
    }
}

// PRINTS RADIX NAME IF APPLICABLE
void radices_name(int num) {
    if (num == 2) {
        printf("Your number in Binary: ");
    } else if (num == 8) {
        printf("Your number in Octal: ");
    } else if (num == 10) {
        printf("Your number in Decimal: ");
    } else if (num == 16) {
        printf("Your number in Hexadecimal: ");
    }
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~ DECIMAL TO RADICES CONVERTER ~~~~~~~~~~
void decimal_to_radix() {
    // TODO: Add functionality for numbers with fractionals

    clear();
    menu_banner();
    printf("DECIMAL TO RADICES CONVERTER\n");
    printf("Convert decimal numbers to radices (binary - hexadecimal)!\n\n");

    bool persist = true;
    bool neg_num = false;
    bool zer_num = false;

    while(persist) {
        int decimal;
        int radix;

        printf("Enter your number: ");
        scanf("%d", &decimal);

        printf("Enter your radix: ");
        scanf("%d", &radix);

        if (radix > 36 || radix < 2) {
            printf("Please choose a radix 2 and 36!\n");
            break;
        }

        if (decimal < 0) {
            decimal = decimal - decimal - decimal;
            neg_num = true;
        } else if (decimal == 0) {
            printf("Your number is 0 -_-\n");
            zer_num = true;
        }

        if (zer_num == true) {
            break;
        }

        // finds length of array that will be filled later
        int exponent_count = 1;
        int num_length = 0;
        for (int i = 0; decimal >= exponent_count; i++) {
            if (decimal >= exponent_count) {
                exponent_count = exponent_count * radix;
                num_length += 1;
            }
        }

        // calculates decimal to radix
        char ans[num_length];

        int dividend = decimal;
        int divisor = radix;
        int temp_decimal = 0;
        int index = 1;
        for (int i = 0; dividend > (radix-1); i++) {
            ans[num_length-index] = return_char((dividend % radix));
            dividend = dividend / radix;
            index++;
        }

        ans[num_length-index] = return_char(dividend);

        radices_name(radix);

        if (neg_num == true) {
            printf("-");
        }
        for (int i = 0; i < num_length; i++) {
            printf("%c", ans[i]);
        }
        printf("\n");
        persist = false;
    }
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~ RADICES TO DECIMAL CONVERTER ~~~~~~~~~~
void radix_to_decimal() {
    // TODO: Add functionality for numbers with fractionals
    // TODO: Add functionality for negative numbers

    clear();
    menu_banner();
    printf("RADICES TO DECIMAL CONVERTER\n");
    printf("Convert radices (binary - hexadecimal) to decimal!\n\n");

    bool persist = true;

    while(persist) {
        char number[256];
        int radix;

        printf("Enter your radix: ");
        scanf("%d", &radix);

        if (radix < 2 || radix > 36) {
            printf("Please choose a radix 2 and 36!\n");
            break;
        }
 
        printf("Enter your base %d number: ", radix);
        scanf("%255s", number);
        int length = arr_len(number);

        // checks for invalid digit symbols, adds to array if valid
        int int_arr[length];
        for (int i = 0; number[i] != '\0'; i++) {
            if (return_int(number[i]) == -1 || return_int(number[i]) >= radix) {
                printf("Digit %c invalid in base %d\n", number[i], radix);
                persist = false;
                break;
            } else {
                int_arr[i] = return_int(number[i]);
            }
        }

        // ends program if invalid digit symbol detected
        if (persist == false) {
            break;
        }

        // calculates decimal version of radix
        int ans = 0;
        int final_arr[length];
        int position = length-1;
        int position_radix = radix;
        for (int i = 0; i < length; i++) {
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
            position -= 1;
        }

        printf("Your number in decimal: %d\n", ans);
        persist = false;
    }
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~ RADICES CALCULATOR ~~~~~~~~~~~~~~~

// ADD USER NUMBERS IN CHOSEN RADIX
void calc_add(int *num1, int *num2, int iterator, int r) {
    int mini_sum;
    bool carry_over = false;
    char final_arr[256];
    bool overflow = false;

    // calculate sum
    for (int i = (iterator-1); i >= 0; i--) {
        if (num1[i] >= r) {
            overflow = true;
            printf("Digit %c invalid in base %d\n", return_char(num1[i]), r);
            break;
        } else if (num2[i] >= r) {
            overflow = true;
            printf("Digit %c invalid in base %d\n", return_char(num2[i]), r);
            break;
        }
        mini_sum = (num1[i] + num2[i]);
        if (carry_over == true) {
            mini_sum += 1;
            if (mini_sum > (r-1)) {
                final_arr[i] = return_char(mini_sum-r);
            } else {
                final_arr[i] = return_char(mini_sum);
                carry_over = false;
            }
        } else {
            if (mini_sum > (r-1)) {
                final_arr[i] = return_char(mini_sum-r);
                carry_over = true;
            } else {
                final_arr[i] = return_char(mini_sum);
            }
        }
    }

    clear();
    menu_banner();
    // output sum
    if (overflow == true) {
        // TODO: future code to persist loop
    } else {
        for (int i = 0; i < iterator; i++) {
            printf("%c", return_char(num1[i]));
        }
        printf(" + ");
        for (int i = 0; i < iterator; i++) {
            printf("%c", return_char(num2[i]));
        }
        printf(" = ");
        if (carry_over == true) {
            printf("1");
        }
        for (int i = 0; final_arr[i] != '\0'; i++) {
            printf("%c", final_arr[i]);
        }
        if (r == 2) {
            printf(" (Binary)\n");
        } else if (r == 8) {
            printf(" (Octal)\n");
        } else if (r == 10) {
            printf(" (Decimal)\n");
        } else if (r == 16) {
            printf(" (Hexadecimal)\n");
        } else {
            printf(" (base %d)\n", r);
        }
    }
}

void calc_sub(int *num1, int *num2, int iterator, int r) {
    // TODO: convert subtrahend and minuend to binary
    // TODO: find 2s complement of subtrahend
    // TODO: add both together
    // TODO: if no carry over digit find 2's complement of sum
    // TODO: convert back to original base and add '-'
    // TODO: if carry over digit, convert sum to original base

    printf("Subtraction function coming soon...\n");
}

void radices_calculator() {
    clear();
    menu_banner();
    printf("RADICES CALCULATOR\n");
    printf("Add, Subtract or Multiply radices from binary to hexadecimal!\n\n");

    bool persist = true;
    while (persist) {
        int radix;
        printf("Choose a radix from 2 - 36: ");
        scanf("%d", &radix);
        if (radix < 2 || radix > 36) {
            printf("Please enter a radix between 2 and 36!\n");
            break;
        }

        char num1[256];
        if (radix == 2) {
            printf("Enter your first Binary number: ");
        } else if (radix == 8) {
            printf("Enter your first Octal number: ");
        } else if (radix == 10) {
            printf("Enter your first Decimal number: ");
        } else if (radix == 16) {
            printf("Enter your first Hexadecimal number: ");
        } else {
            printf("Enter your first number in base %d: ", radix);
        }
        scanf("%255s", num1);

        char op;
        printf("Enter your operator (*, + or -): ");
        scanf(" %c", &op);

        char num2[256];
        if (radix == 2) {
            printf("Enter your second Binary number: ");
        } else if (radix == 8) {
            printf("Enter your second Octal number: ");
        } else if (radix == 10) {
            printf("Enter your second Decimal number: ");
        } else if (radix == 16) {
            printf("Enter your second Hexadecimal number: ");
        } else {
            printf("Enter your second number in base %d: ", radix);
        }
        scanf("%255s", num2);

        // add leading 0s, if applicable
        int num1_len = arr_len(num1);
        int num2_len = arr_len(num2);
        int len_diff;

        if (num1_len > num2_len) {
            len_diff = num1_len - num2_len;
            num2_len = (num2_len+len_diff);
        } else {
            len_diff = num2_len - num1_len;
            num1_len = (num1_len+len_diff);
        }

        int num1_integers[num1_len];
        int num1_integers_len = sizeof(num1_integers) / sizeof(num1_integers[0]);
        int num2_integers[num2_len];
        int num2_integers_len = sizeof(num2_integers) / sizeof(num2_integers[0]);

        num1_len = arr_len(num1);
        num2_len = arr_len(num2);
        if (num1_len > num2_len) {
            for (int i = 0; i < len_diff; i++) {
                num2_integers[i] = 0;
            }
            for (int i = len_diff; i < num2_integers_len; i++) {
                num2_integers[i] = return_int(num2[(i-len_diff)]);
            }
            for (int i = 0; i < num1_integers_len; i++) {
                num1_integers[i] = return_int(num1[i]);
            }
        } else {
            for (int i = 0; i < len_diff; i++) {
                num1_integers[i] = 0;
            }
            for (int i = len_diff; i < num1_integers_len; i++) {
                num1_integers[i] = return_int(num1[(i-len_diff)]);
            }
            for (int i = 0; i < num2_integers_len; i++) {
                num2_integers[i] = return_int(num2[i]);
            }
        }

        // outputs calculations depending on operator
        if (op == '+') {
            calc_add(num1_integers, num2_integers, num1_integers_len, radix);
        } else if (op == '-') {
            calc_sub(num1_integers, num2_integers, num1_integers_len, radix);
        } else if (op == '*') {
            printf("Multiplication function coming soon...");
        } else if (op == '/') {
            printf("Division function coming soon...");
        } else {
            printf("Please choose a valid operator...");
        }
        persist = false;
    }
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~ MAIN MENU ~~~~~~~~~~~~~~~~~~~~
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

