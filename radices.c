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
    } else {
        printf("Your number in base %d: ", num);
    }
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~ DECIMAL TO RADICES CONVERTER ~~~~~~~~~~
int decimal_to_radix(int decimal, int radix, bool int_return) {
    // TODO: Add functionality for numbers with fractionals
    // TODO: Return a digit when prompted, print final array when prompted

    /*
    printf("DECIMAL TO RADICES CONVERTER\n");
    printf("Convert decimal numbers to radices (binary - hexadecimal)!\n\n");
    */

    bool persist = true;
    bool neg_num = false;
    bool zer_num = false;
    int test_ans = 0;

    while(persist) {

        if (radix > 36 || radix < 2) {
            printf("Please choose a radix 2 and 36!\n");
            break;
        }

        if (decimal < 0) {
            decimal = decimal - decimal - decimal;
            neg_num = true;
        } else if (decimal == 0) {
            return 0;
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
        int index = 1;
        for (int i = 0; dividend > (radix-1); i++) {
            ans[num_length-index] = return_char((dividend % radix));
            dividend = dividend / radix;
            index++;
        }

        ans[num_length-index] = return_char(dividend);

        if (neg_num == true) {
            printf("-");
        }

        int returned_int = 0;
        // FIX: NOT RETURNING CORRECT INTEGER
        if (int_return == true) {
            for (int i = 0; i < num_length; i++) {
                if (i == 0) {
                    returned_int += return_int(ans[i]) * 10;
                } else {
                    returned_int += return_int(ans[i]);
                }
            }
            return returned_int;
        } else {
            for (int i = 0; i < num_length; i++) {
                printf("%c", ans[i]);
            }
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
    int ans = 0;

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
        // int final_arr[length];
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

        // printf("Your number in decimal: %d\n", ans);
        printf("Test");
        persist = false;
    }
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~ RADICES CALCULATOR ~~~~~~~~~~~~~~~

// CALCULATES SUM OF 2 INTEGERS FROM BINARY TO BASE36
void calc_add(int *num1, int *num2, int iterator, int r, bool sub, int *sub_comp, int *carry) {
    int mini_sum;
    bool carry_over = false;
    char final_arr[256];
    bool invalid_int = false;

    // calculate sum
    for (int i = (iterator-1); i >= 0; i--) {
        if (num1[i] >= r) {
            invalid_int = true;
            printf("Digit %c invalid in base %d\n", return_char(num1[i]), r);
            break;
        } else if (num2[i] >= r) {
            invalid_int = true;
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

    /*
    clear();
    menu_banner();
    */
    // output sum
    if (invalid_int == true) {
        // TODO: future code to persist loop
    } else if (sub == true) {
        // fill empty in array with 2s complement
        for (int i = 0; i < iterator; i++) {
            sub_comp[i] = return_int(final_arr[i]);
        }
        if (carry_over == true) {
            *carry = 1;
        } else {
            *carry = 0;
        }
    } else {
        for (int i = 0; i < iterator; i++) {
            printf("%c", return_char(num1[i]));
        }
        printf(" + ");
        for (int i = 0; i < iterator; i++) {
            printf("%c", return_char(num2[i]));
        }
        printf(" = ");
        if (carry_over == true && sub == false) {
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

// CALCULATES DIFFERENCE OF 2 INTEGERS FROM BINARY TO BASE36
void calc_sub(int *num1, int *num2, int iterator, int r) {

    // convert num1 to decimal (array of integers)
    int dec1 = 0;
    int position = iterator-1;
    int position_radix = r;
    for (int i = 0; i < iterator; i++) {
        if (position == 0) {
            dec1 += num1[i] * 1;
        } else if (position == 1) {
            dec1 += num1[i] * r;
        } else {
            for (int i = 0; i < position-1; i++) {
                position_radix = position_radix * r;
            }
            dec1 += num1[i] * position_radix;
            position_radix = r;
        }
        position -= 1;
    }

    // convert dec1 to binary (array of integers)
    int exponent_count = 1;
    int bin1_length = 1;
    for (int i = 0; dec1 >= exponent_count; i++) {
        if (dec1 >= exponent_count) {
            exponent_count = exponent_count * 2;
            bin1_length += 1;
        }
    }

    char ans_arr1[bin1_length];
    int dividend = dec1;
    int divisor = 2;
    int index = 2;
    for (int i = 0; dividend > (divisor-1); i++) {
        ans_arr1[bin1_length-index] = return_char((dividend % divisor));
        dividend = dividend / divisor;
        index++;
    }

    ans_arr1[bin1_length-index] = return_char(dividend);
    ans_arr1[bin1_length-1] = '\0';
    int ans_arr1_length = arr_len(ans_arr1);

    // convert num2 to decimal (array of integers)
    int dec2 = 0;
    position = iterator-1;
    position_radix = r;
    for (int i = 0; i < iterator; i++) {
        if (position == 0) {
            dec2 += num2[i] * 1;
        } else if (position == 1) {
            dec2 += num2[i] * r;
        } else {
            for (int i = 0; i < position-1; i++) {
                position_radix = position_radix * r;
            }
            dec2 += num2[i] * position_radix;
            position_radix = r;
        }
        position -= 1;
    }

    // convert dec2 to binary (array of integers)
    exponent_count = 1;
    int bin2_length = 1;
    for (int i = 0; dec2 >= exponent_count; i++) {
        if (dec2 >= exponent_count) {
            exponent_count = exponent_count * 2;
            bin2_length += 1;
        }
    }

    char ans_arr2[bin2_length];
    dividend = dec2;
    index = 2;
    for (int i = 0; dividend > (divisor-1); i++) {
        ans_arr2[bin2_length-index] = return_char((dividend % divisor));
        dividend = dividend / divisor;
        index++;
    }

    ans_arr2[bin2_length-index] = return_char(dividend);
    ans_arr2[bin2_length-1] = '\0';
    int ans_arr2_length = arr_len(ans_arr2);

    // populate arrays of binary integers for num1 and num2
    int diff = 0;
    if (ans_arr1_length > ans_arr2_length) {
        index = ans_arr1_length;
        diff = ans_arr1_length - ans_arr2_length;
    } else {
        index = ans_arr2_length;
        diff = ans_arr2_length - ans_arr1_length;
    }
    int minuend[index];
    int subtrahend[index];
    if (ans_arr1_length > ans_arr2_length) {
        for (int i = 0; i < diff; i++) {
            subtrahend[i] = 0;
        }
        for (int i = diff; i < index; i++) {
            subtrahend[i] = return_int(ans_arr2[i-diff]);
        }
        for (int i = 0; i < index; i++) {
            minuend[i] = return_int(ans_arr1[i]);
        }
    } else {
        for (int i = 0; i < diff; i++) {
            minuend[i] = 0;
        }
        for (int i = diff; i < index; i++) {
            minuend[i] = return_int(ans_arr1[i-diff]);
        }
        for (int i = 0; i < index; i++) {
            subtrahend[i] = return_int(ans_arr2[i]);
        }
    }

    int two_complement_sub[index];
    for (int i = 0; i < index; i++) {
        if (subtrahend[i] == 0) {
            subtrahend[i] = 1;
        } else {
            subtrahend[i] = 0;
        }
    }
    for (int i = 0; i < index; i++) {
        if (i == (index-1)) {
            two_complement_sub[i] = 1;
        } else {
            two_complement_sub[i] = 0;
        }
    }

    clear();
    menu_banner();

    int final_two_complement[index];

    int carry_padding;
    calc_add(subtrahend, two_complement_sub, index, 2, true, final_two_complement, &carry_padding);

    int min_plus_2comp[index];
    int carry_over;
    calc_add(minuend, final_two_complement, index, 2, true, min_plus_2comp, &carry_over);


    // checks for the presence of a carry over digit
    if (carry_over == 1) {
        // calculate subtraction - minuend > subtrahend
        int pos_ans = 0;
        int pos_position = index-1;
        int pos_position_r = 2;
        for (int i = 0; i < index; i++) {
            if (pos_position == 0) {
                pos_ans += min_plus_2comp[i] * 1;
            } else if (pos_position == 1) {
                pos_ans += min_plus_2comp[i] * 2;
            } else {
                for (int i = 0; i < pos_position-1; i++) {
                    pos_position_r = pos_position_r * 2;
                }
                pos_ans += min_plus_2comp[i] * pos_position_r;
                pos_position_r = 2;
            }
            pos_position -= 1;
        }
        // convert pos_ans to original radix
        int exponent_count = 1;
        int num_length = 0;
        for (int i = 0; pos_ans >= exponent_count; i++) {
            if (pos_ans >= exponent_count) {
                exponent_count = exponent_count * r;
                num_length += 1;
            }
        }

        char pos_ans_arr[num_length];
        int pos_dividend = pos_ans;
        index = 1;
        for (int i = 0; pos_dividend > (r-1); i++) {
            pos_ans_arr[num_length-index] = return_char((pos_dividend % r));
            pos_dividend = pos_dividend / r;
            index++;
        }

        pos_ans_arr[num_length-index] = return_char(pos_dividend);
        for (int i = 0; i < num_length; i++) {
           printf("%c", pos_ans_arr[i]);
        }

    } else {
        // calculate subtraction - subtrahend > minuend
        int bit_flip[index];
        for (int i = 0; i < index; i++) {
            if (min_plus_2comp[i] == 0) {
                bit_flip[i] = 1;
            } else {
                bit_flip[i] = 0;
            }
        }

        int final_ans[index];
        calc_add(bit_flip, two_complement_sub, index, 2, true, final_ans, &carry_over);

        int neg_ans = 0;
        int neg_position = index-1;
        int neg_position_r = 2;
        for (int i = 0; i < index; i++) {
            if (neg_position == 0) {
                neg_ans += final_ans[i] * 1;
            } else if (neg_position == 1) {
                neg_ans += final_ans[i] * 2;
            } else {
                for (int i = 0; i < neg_position-1; i++) {
                    neg_position_r = neg_position_r * 2;
                }
                neg_ans += final_ans[i] * neg_position_r;
                neg_position_r = 2;
            }
            neg_position -= 1;
        }
        // convert decimal back to original radix
        int exponent_count = 1;
        int num_length = 0;
        for (int i = 0; neg_ans >= exponent_count; i++) {
            if (neg_ans >= exponent_count) {
                exponent_count = exponent_count * r;
                num_length += 1;
            }
        }

        char neg_ans_arr[num_length];
        int neg_dividend = neg_ans;
        index = 1;
        for (int i = 0; neg_dividend > (r-1); i++) {
            neg_ans_arr[num_length-index] = return_char((neg_dividend % r));
            neg_dividend = neg_dividend / r;
            index++;
        }

        neg_ans_arr[num_length-index] = return_char(neg_dividend);
        printf("-");
        for (int i = 0; i < num_length; i++) {
           printf("%c", neg_ans_arr[i]);
        }
    }
    printf("\n");
}

// CALCULATES PRODUCT OF 2 INTEGERS FROM BINARY TO BASE36
void calc_mul(int *num1, int *num2, int iterator, int r, int muls) {
    clear();
    menu_banner();
    int multiplyer_one = 0;
    int multiplyer_two = 0;
    int multiplicand;

    // checks which array has the larger value
    for (int i = 0; i < iterator; i++) {
        multiplyer_one += num1[i];
    }
    for (int i = 0; i < iterator; i++) {
        multiplyer_two += num2[i];
    }
    // sets value to multiplicand depending on length of each array
    if (multiplyer_one > multiplyer_two) {
        multiplicand = 1;
    } else {
        multiplicand = 0;
    }

    // prints contents of num1 and num2
    for (int i = 0; i < iterator; i++) {
        printf("%d ", num1[i]);
    }
    printf("\n");
    for (int i = 0; i < iterator; i++) {
        printf("%d ", num2[i]);
    }
    printf("\n");

    // TODO: Account for extra spaces in outer_array, for digits if muls == 1
    // TODO: if muls == 2, outer_array & inner_array populated
    //       calc_add() used for sum of both arrays
    //       sum of arrays sent to array_sum and printed w/ return_char()
    // TODO: if muls > 2, same process as above
    //       once the 3rd multiplier is calculated the contents of array_sum is sent to outer_array
    //       array_sum is emptied and the sum of outer_array and inner_array are sent to array_sum
    //       the process repeats until array_sum is printed with return_char()
    // TODO: ** account for added 0s for every multiplier > 1

    int index = iterator;
    int *outer_array = malloc(index * sizeof *outer_array);
    int *array_sum = malloc(index * sizeof *array_sum);

    // int ans_place_counter = 1;

    // Currently will only interate as many times as there are multipliers
    for (int i = iterator-1; i >= (iterator-muls); i--) {
        int temp_product;
        int temp_quotient = 0;
        // int multiplicand_place_counter = 1;
        int *inner_array = malloc(index * sizeof *inner_array);
        int temp_conversion;
        for (int j = iterator-1; j >= 0; j--) {
            if (multiplicand == 1) {
                temp_product = num2[i] * num1[j];
            } else {
                temp_product = num1[i] * num2[j];
            }
            if (temp_quotient > 0) {
                temp_product += temp_quotient;
                temp_quotient = 0;
            }
            printf("temp_product on iteration [i: %d][j: %d]: %d\n", i, j, temp_product);
            if (temp_product >= r) {
                temp_conversion = decimal_to_radix(temp_product, r, true);
                printf("temp_conversion on iteration %d: %d\n", j, temp_conversion);
                temp_quotient = temp_conversion / 10;
                printf("temp_quotient on iteration %d: %d\n", j, temp_quotient);
                temp_product = temp_conversion - (temp_quotient * 10);
                printf("temp_product: %d\n", temp_product);
                outer_array[j] = temp_product;
            } else {
                outer_array[j] = temp_product;
            }
        }
        printf("\n");
    }
    printf("Product: ");
    for (int i = 0; i < index; i++) {
        printf("%c", return_char(outer_array[i]));
    }
    printf("\n");
}

void calc_div(int *num1, int *num2) {
    clear();
    menu_banner();
    printf("Division coming soon...\n");
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
        int carry_over;

        // outputs calculations depending on operator
        if (op == '+') {
            calc_add(num1_integers, num2_integers, num1_integers_len, radix, false, num1_integers, &carry_over);
        } else if (op == '-') {
            calc_sub(num1_integers, num2_integers, num1_integers_len, radix);
        } else if (op == '*') {
            int multipliers = (num1_integers_len - len_diff);
            calc_mul(num1_integers, num2_integers, num1_integers_len, radix, multipliers);
        } else if (op == '/') {
            calc_div(num1_integers, num2_integers);
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
            clear();
            menu_banner();
            int dec;
            printf("Enter your number: ");
            scanf("%d", &dec);
            int r;
            printf("Enter your radix: ");
            scanf("%d", &r);
            radices_name(r);
            decimal_to_radix(dec, r, false);
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

