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

// MENU BANNER
void menu_banner() {
    printf(".___         _ _            ._____.        _ _   _ _\n");
    printf("| _ \\__ _ __| (_)__ ___ ___ |_   _|__  ___| | |_(_) |_\n");
    printf("|   / _` / _` | / _/ -_|_-<   | |/ _ \\/ _ \\ | / / |  _|\n");
    printf("|_|_\\__,_\\__,_|_\\__\\___/__/   |_|\\___/\\___/_|_\\_\\_|\\__|\n\n");
}

// MAIN MENU
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

// CONVERT CHAR TO INT
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

// CONVERT INT AND CHAR TO PROPER DIGIT SYMBOLS
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

// PRINT RADIX NAME IF APPLICABLE
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

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ DECIMAL TO RADICES CONVERTER ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int decimal_to_radix(int decimal, int radix, bool int_return) {
    // TODO: Add functionality for numbers with fractionals

    // XXX: REINSTATE AFTER TESTING IN calc_mul()
    // clear();
    // menu_banner();

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

        char ans[num_length];

        // break down decimal number into radix - send each digit to ans
        int dividend = decimal;
        int index = 1;
        for (int i = 0; dividend > (radix-1); i++) {
            ans[num_length-index] = return_char((dividend % radix));
            dividend = dividend / radix;
            index++;
        }

        ans[num_length-index] = return_char(dividend);
 
        // convert temp_product in calc_mul() to radix digits or print the result of decimal_to_radix()
        int returned_int;
        if (int_return == true) {
            // NOTE: returned_int is returned as a whole number, so any separation will still need to be within calc_mul()
            if (return_int(ans[1]) > 9) {
                returned_int = return_int(ans[0]) * 100;
            } else {
                returned_int = return_int(ans[0]) * 10;
            }
            returned_int += return_int(ans[1]);
            return returned_int;
        } else {
            radices_name(radix);
            if (neg_num == true) {
                printf("-");
            }
            for (int i = 0; i < num_length; i++) {
                printf("%c", ans[i]);
            }
        }
        printf("\n");
        persist = false;
    }
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ RADICES TO DECIMAL CONVERTER ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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

        // check for invalid digit symbols, send to int_arr if valid
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

        // end program if invalid digit symbol detected
        if (persist == false) {
            break;
        }

        // calculate decimal version of radix
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
        persist = false;
    }
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ RADICES CALCULATOR ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// CALCULATES SUM OF 2 INTEGERS FROM BINARY TO BASE36
void calc_add(int *num1, int *num2, int iterator, int r, bool extra_arr, int *ex_arr, int *carry) {
    int mini_sum;
    bool carry_over = false;
    // FIX: ALLOW FOR final_arr TO BECOME INT ARRAY
    //      why is final_arr a char array to begin with?
    //
    //      calc_mul() returning char array, therefore the same array is not able to be used in an extra calculation
    //      Change final_arr to int array,
    //      send mini_sum to final_arr as int
    //      print either the ASCII character of those digits, if using calc_add(), or send them as ints to ex_arr and format printing inside of calc_mul()
    int final_arr[256];
    bool invalid_digit = false;

    // check for invalid digit symbols for chosen radix
    for (int i = (iterator-1); i >= 0; i--) {
        if (num1[i] >= r) {
            invalid_digit = true;
            printf("Digit %c invalid in base %d\n", return_char(num1[i]), r);
            break;
        } else if (num2[i] >= r) {
            invalid_digit = true;
            printf("Digit %c invalid in base %d\n", return_char(num2[i]), r);
            break;
        }
        // check if carry over digit present - separate carry over digit from second digit if true
        mini_sum = (num1[i] + num2[i]);
        printf("mini_sum: %d\n", mini_sum);
        if (carry_over == true) {
            mini_sum += 1;
            if (mini_sum > (r-1)) {
                final_arr[i] = (mini_sum-r);
            } else {
                final_arr[i] = mini_sum;
                carry_over = false;
            }
        } else {
            if (mini_sum > (r-1)) {
                final_arr[i] = (mini_sum-r);
                carry_over = true;
            } else {
                final_arr[i] = mini_sum;
            }
        }
    }

    // output sum
    if (invalid_digit == true) {
        // TODO: FUTURE CODE TO PERSIST LOOP
    } else if (extra_arr == true) {
        for (int i = 0; i < iterator; i++) {
            ex_arr[i] = final_arr[i];
        }
        // carry over digit will always be 1
        if (carry_over == true) {
            *carry = 1;
            printf("1 ");
        }
    } else {
        clear();
        menu_banner();
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
        for (int i = 0; i < iterator; i++) {
            printf("%c", return_char(final_arr[i]));
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
        // calculate subtraction, minuend > subtrahend
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
        // calculate subtraction, subtrahend > minuend
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

// CALCULATES PRODUCTS OF MULTIPLICAND DIGIT * MULTIPLER DIGITS
int calc_single_multiplicand(int x, int *y, int iterator, int multipliers, int r) {

    int temp_quotient = 0;
    int temp_product;
    int temp_conversion;

    for (int i = (iterator-1); i >= 0; i--) {
        // calculates product digits
        temp_product = (x * y[i]);

        // Adds quotient to temp_product
        if (temp_quotient > 0) {
            temp_product += temp_quotient;
            temp_quotient = 0;
        }
        if (temp_product >= r) {
            temp_conversion = decimal_to_radix(temp_product, r, true);

            // Separates product from quotient
            if (temp_conversion > 99) {
                temp_quotient = temp_conversion / 100;
                temp_product = temp_conversion - 100;
            } else {
                temp_quotient = temp_conversion / 10;
                temp_product = temp_conversion - (temp_quotient * 10);
            }
        } else {
            continue;
        }
    }

    // returns 0 or 1 based on presence of temp_quotient
    if (temp_quotient > 0) {
        return 1;
    } else {
        return 0;
    }
}

// CALCULATES PRODUCT OF 2 INTEGERS FROM BINARY TO BASE36
void calc_mul(int *num1, int *num2, int iterator, int r, int muls) {
    // TODO: add functionality for negative numbers


    clear();
    menu_banner();

    bool invalid_digit = false;
    int invalid_condition;
    int invalid_integer;
    char invalid_character;

    printf("\n");
    for (int i = 0; i < iterator; i++) {
        if (num1[i] >= r) {
            invalid_digit = true;
            if (num1[i] > 9) {
                invalid_condition = 0;
                invalid_character = return_char(num1[i]);
            } else {
                invalid_condition = 1;
                invalid_integer = num1[i];
            }
        }
        printf("%d ", num1[i]);
    }
    printf("\n");
    for (int i = 0; i < iterator; i++) {
        if (num2[i] >= r) {
            invalid_digit = true;
            if (num2[i] > 9) {
                invalid_condition = 0;
                invalid_character = return_char(num2[i]);
            } else {
                invalid_condition = 1;
                invalid_integer = num2[i];
            }
        }
        printf("%d ", num2[i]);
    }
    printf("\n\n");

    if (invalid_digit == true) {
        if (invalid_condition == 0) {
            printf("Digit %c invalid in base %d\n", invalid_character, r);
            return;
        } else {
            printf("Digit %d invalid in base %d\n", invalid_integer, r);
            return;
        }
    }

    // Determines if the top number is the multiplicand or multiplier
    int multiplyer_one = 0;
    int multiplyer_two = 0;
    int multiplicand;
    int exponential = 1;
    for (int i = iterator-1; i >= 0; i--) {
        multiplyer_one += num1[i] * exponential;
        exponential = exponential * 10;
    }
    exponential = 1;
    for (int i = iterator-1; i >= 0; i--) {
        multiplyer_two += num2[i] * exponential;
        exponential = exponential * 10;
    }
    // sets value to multiplicand depending on length of each array
    if (multiplyer_one > multiplyer_two) {
        multiplicand = 1;
    } else {
        multiplicand = 0;
    }

    // calculates leading and trailing 0s
    int leading_zero = (muls - 1);
    int trailing_zero = 0;

    int index = iterator+1;
    int row_counter = 0;

    int array_index = 0;
    int temp_quotient = 0;

    int temp_quotient_bool;
    int final_row_size = 0;
    if (multiplicand == 1) {
        temp_quotient_bool = calc_single_multiplicand(num2[iterator-muls], num1, iterator, muls, r);
    } else {
        temp_quotient_bool = calc_single_multiplicand(num1[iterator-muls], num2, iterator, muls, r);
    }
    if (temp_quotient_bool == 1) {
        final_row_size = (index+leading_zero+trailing_zero);
    } else {
        final_row_size = (iterator+leading_zero+trailing_zero);
    }

    int **master_product_array; // Holds all (multiplyer digit * multiplicand digit) calculations
    master_product_array = malloc(muls * sizeof *master_product_array); // Assigns master_product_array a size of muls
 
    // XXX: START OF OUTER LOOP
    for (int i = iterator-1; i >= (iterator-muls); i--) {
        temp_quotient = 0;
        int temp_product;
        int temp_conversion;

        // Dynamically sizes each row of master_product_array, according to index at master_product_array[array_index]
        master_product_array[array_index] = malloc(iterator * sizeof *master_product_array[array_index]);

        // Temporary array whose elements are eventually added to master_product_array on each outer loop
        int temp_product_arr[iterator];

        // XXX: START OF INNER LOOP
        for (int j = iterator-1; j >= 0; j--) {
            int temp_counter = 0;
            // (multiplier digit * multiplicand digit)
            if (multiplicand == 1) { // top number is the multiplicand
                temp_product = num2[i] * num1[j];
            } else { // bottom number is the multiplicand
                temp_product = num1[i] * num2[j];
            }

            // Adds quotient to temp_product
            if (temp_quotient > 0) {
                temp_product += temp_quotient;
                temp_quotient = 0;
            }

            if (temp_product >= r) {
                temp_conversion = decimal_to_radix(temp_product, r, true);

                // Separates product from quotient

                    // FIX: ABB * F and ABB * FF BOTH CORRECT, ABB * FFF STILL WRONG, DEBUG
                    //      PERHAPS ALSO LOOK AT BOTH ABB * F AND ABB* FF TO SEE HOW THEY WORK
                    //      Also try ABB * A, ABB * AA, and ABB * AAA

                    // NOTE:OUTPUT FOR ABB * A (16)
                    //      first temp_product is correct 110, which converts to 6E, which is returned as 614
                    //      Should be separated as [6, 14], but is separating as [61, 4] because 3 digit numbers are separated at the 1s place :tomato_thonk:
                    //      Within decimal_to_radix() there is an array that recieves all digits, and is either returned as digits, or characters.
                    //      But there is an array, so I check ans[1] because no temp_product is ever going to be above 2 digits, the quotient and the other digit.
                    //      If ans[1] > 9 then I know to separate the first digit from the last 2 digits. Otherwise separate the first 2 digits from the last digit.
                    // XXX: Won't work, because decimal_to_radix() turns argument into a single digit. I have to separate the digits another way. With math somehow.
                    //
                    //      10 11 11
                    //       0  0 10
                    //
                    //      CONDITION TWO:
                    //      temp_product: 110
                    //      temp_conversion: 614
                    //      temp_quotient: 61
                    //      temp_product after quotient: 4
                    //      temp_product, end of inner loop: 4
                    //
                    //      CONDITION ONE:
                    //      temp_product: 171
                    //      temp_conversion: 1011
                    //      temp_quotient: 10
                    //      temp_product after quotient: 11
                    //      temp_product, end of inner loop: 11
                    //
                    //      CONDITION TWO:
                    //      temp_product: 110
                    //      temp_conversion: 614
                    //      temp_quotient: 61
                    //      temp_product after quotient: 4
                    //      temp_product, end of inner loop: 4
                    //
                    //      muls: 1
                    //
                    //      Product characters: = 4 B 4
                    //
                    //      Product integers: 61 52 66 52

                if (temp_conversion > 999) {
                    printf("CONDITION ONE: \n");
                    printf("temp_product: %d\n", temp_product);
                    printf("temp_conversion: %d\n", temp_conversion);
                    temp_quotient = (temp_conversion - temp_quotient) / 100;
                    printf("temp_quotient: %d\n", temp_quotient);
                    temp_product = (temp_conversion - (temp_quotient * 100));
                    printf("temp_product after quotient: %d\n", temp_product);

                } else if (temp_conversion > 99) {
                    if (r < 10) {
                        // NOTE: DIGITS THAT REACH THIS CONDITION WILL ALWAYS BE 2 DIGITS LONG
                        printf("CONDITION TWO RADIX <= 9: \n");
                        printf("temp_product: %d\n", temp_product);
                        printf("temp_conversion: %d\n", temp_conversion);
                        temp_quotient = (temp_conversion - temp_quotient) / 10;
                        printf("temp_quotient: %d\n", temp_quotient);
                        temp_product = (temp_conversion - (temp_quotient * 10));
                        printf("temp_product after quotient: %d\n", temp_product);
                    } else {
                        // NOTE: ANY 3 DIGIT RESULT, WITH A RADIX > 9 WILL MEAN THE ONES PLACE IS 2 DIGITS
                        printf("CONDITION TWO RADIX > 9: \n");
                        printf("temp_product: %d\n", temp_product);
                        printf("temp_conversion: %d\n", temp_conversion);
                        // FIX: ACCURATELY RETURNS RESULT OF ABB * A (16), BUT NOT ABB * F (16)
                        //      DO THE MATH FOR ABB * F AND ANALYZE OUTPUT OF PROGRAM
                        //      FIRST temp_product is 165, 105 (16), SEPARATES INTO 1 AND 5 INSTEAD 10 AND 5
                        //      106 / 100 == 1 not 10
                        //      :NOOOOOOOOOO:
                        temp_quotient = (temp_conversion - temp_quotient) / 10;
                        printf("temp_quotient: %d\n", temp_quotient);
                        temp_product = (temp_conversion - (temp_quotient * 100)); // FIX: NEEDS MODIFYING
                        printf("temp_product after quotient: %d\n", temp_product);
                    }
                } else {
                    if (r < 10) {
                        printf("CONDITION THREE: \n");
                        printf("temp_product: %d\n", temp_product);
                        printf("temp_conversion: %d\n", temp_conversion);
                        temp_quotient = temp_conversion / 10;
                        printf("temp_quotient: %d\n", temp_quotient);
                        temp_product = temp_conversion - (temp_quotient * 10);
                        printf("temp_product after quotient: %d\n", temp_product);

                    } else {
                        // NOTE: FOR DIGITS < 100 && RADIX > 9
                        // FIX: CHANGE CODE TO REFLECT CONDITION
                        printf("CONDITION THREE: \n");
                        printf("temp_product: %d\n", temp_product);
                        printf("temp_conversion: %d\n", temp_conversion);
                        temp_quotient = temp_conversion / 10; // XXX: THIS WILL SEPARATE 1B (16) INTO 11
                        printf("temp_quotient: %d\n", temp_quotient);
                        temp_product = temp_conversion - (temp_quotient * 10); // XXX: THIS WILL SEPARATE 1B (16) INTO 0
                        printf("temp_product after quotient: %d\n", temp_product);
                    }
                }

                printf("temp_product, end of inner loop: %d\n", temp_product);
                temp_product_arr[j] = temp_product;
            } else {
                printf("temp_product, end of inner loop: %d\n", temp_product);
                temp_product_arr[j] = temp_product;
            }
            temp_counter++;
            printf("\n");
        } // XXX: END OF INNER LOOP
 
        // Kiiiind of forgot what this does
        if (temp_quotient > 0) {
            leading_zero = final_row_size - (index + trailing_zero);
        } else {
            leading_zero = final_row_size - iterator - trailing_zero;
        }

        if (temp_quotient > 0) {
            int iterator_array[index];
            int iterator_counter = 1;
            // assigns 0 index of iterator_array with temp_quotient
            iterator_array[0] = temp_quotient;

            // allocates elements from temp_product_arr to iterator_array
            for (int i = 0; i < iterator; i++) {
                iterator_array[iterator_counter] = temp_product_arr[i];
                iterator_counter++;
            }

            // This will always ensure the correct number of trailing and leading 0s
            master_product_array[array_index] = malloc(final_row_size * sizeof *master_product_array[array_index]);

            int temp_index = 0;
            for (int i = 0; i < final_row_size; i++) {
                // Adds leading 0s
                if (i < leading_zero) {
                    master_product_array[array_index][i] = 0;
                // Adds elements from temp_product_arr
                } else if (i >= leading_zero && i < (index+leading_zero)) {
                    master_product_array[array_index][i] = iterator_array[temp_index];
                    temp_index++;
                // Adds trailing 0s
                } else {
                    master_product_array[array_index][i] = 0;
                }
            }
        } else {
            master_product_array[array_index] = malloc(final_row_size * sizeof *master_product_array[array_index]);

            int temp_index = 0;
            for (int i = 0; i < final_row_size; i++) {
                if (i < leading_zero) {
                    master_product_array[array_index][i] = 0;
                } else if (i >= leading_zero && i < (iterator + leading_zero)) {
                    master_product_array[array_index][i] = temp_product_arr[temp_index];
                    temp_index++;
                } else {
                    master_product_array[array_index][i] = 0;
                }
            }
        }
        array_index++;
        row_counter++;

        // increments/decrements 0 counters
        leading_zero--;
        trailing_zero++;
    } // XXX: END OF OUTER LOOP

    if (muls == 1) {
        printf("muls: %d\n", muls);
        if (temp_quotient > 0) {
            printf("\nProduct characters: ");
            for (int i = 0; i < muls; i++) {
                for (int j = 0; j < index; j++) {
                    printf("%c ", return_char(master_product_array[i][j]));
                }
            }
            printf("\n");
            // XXX: WILL BE REMOVED LATER
            printf("\nProduct integers: ");
            for (int i = 0; i < muls; i++) {
                for (int j = 0; j < index; j++) {
                    printf("%d ", return_char(master_product_array[i][j]));
                }
            }
            printf("\n");

        } else {
            printf("\nProduct: ");
            for (int i = 0; i < muls; i++) {
                for (int j = 0; j < iterator; j++) {
                   printf("%c ", return_char(master_product_array[i][j]));
                }
            }
            printf("\n");
        }
    } else {
        // FIX: 255555 * 255 RETURNS CORRECT ANSWER, 46976 * 222 DOES NOT - DEBUG
        //      ALL 3 PTRS OF master_product_array ARE CORRECT, calc_add() PRODUCING INCORRECT ANSWER
        //      COULD STILL BE AN ISSUE OF INTEGERS NOT BEING SENT TO ex_arr

        printf("\n");
        // NOTE: ALL 3 PTRS ARE CORRECT
        for (int i = 0; i < muls; i++) {
            printf("master_product_array[%d]: ", i);
            for (int j = 0; j < final_row_size; j++) {
                printf("%d ", master_product_array[i][j]);
            }
            printf("\n");
        }
        printf("\n");

        int final_product_arr[(index+leading_zero+trailing_zero)];
        int carry = 0; // value to be changed to 1 inside of calc_sum() or remain the same
        int counter = 1;
        printf("muls: %d\n\n", muls);
        for (int i = 0; i < (muls - 1); i++) {
            printf("ITERATION %d\n", (i+1));
            if (i == 0) {
                calc_add(master_product_array[0], master_product_array[1], (index+leading_zero+trailing_zero), r, true, final_product_arr, &carry);
            } else {
                printf("master_product_array[%d]: ", counter);
                for (int i = 0; i < (index+leading_zero+trailing_zero); i++) {
                    printf("%d ", master_product_array[counter][i]);
                }
                printf("\n");

                printf("final_product_arr: ");
                for (int i = 0; i < (index+leading_zero+trailing_zero); i++) {
                    printf("%d ", final_product_arr[i]);
                }
                printf("\n");
                calc_add(final_product_arr, master_product_array[counter], (index+leading_zero+trailing_zero), r, true, final_product_arr, &carry);
            }

            if (carry == 1) {
                if (i == 0) {
                    calc_add(master_product_array[0], master_product_array[1], index, r, true, final_product_arr, &carry);
                    printf("final_product_arr on iteration %d: ", i);
                    for (int i = 0; i < index; i++) {
                        printf("%c ", return_char(final_product_arr[i]));
                    }
                    printf("\n");
                } else {
                    calc_add(final_product_arr, master_product_array[counter], index, r, true, final_product_arr, &carry);
                printf("final_product_arr on iteration %d: ", i);
                    for (int i = 0; i < index; i++) {
                        printf("%c ", return_char(final_product_arr[i]));
                    }
                    printf("\n");
                }
            } else {
                printf("final_product_arr on iteration %d: ", i);
                for (int i = 0; i < final_row_size; i++) {
                    printf("%c ", return_char(final_product_arr[i]));
                }
                printf("\n");

            }
            counter++;
            printf("\n");
        }
        if (carry == 1) {
            printf("Product: ");
            for (int i = 0; i < index; i++) {
                printf("%c ", return_char(final_product_arr[i]));
            }
            printf("\n");
        } else {
            printf("Product: ");
            for (int i = 0; i < final_row_size; i++) {
                printf("%c ", return_char(final_product_arr[i]));
            }
            printf("\n");
        }
    }
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
            printf("num1_integers: ");
            for (int i = 0; i < num1_integers_len; i++) {
                printf("%d ", num1_integers[i]);
            }
            printf("\n");
            calc_add(num1_integers, num2_integers, num1_integers_len, radix, false, num1_integers, &carry_over);
        } else if (op == '-') {
            calc_sub(num1_integers, num2_integers, num1_integers_len, radix);
        } else if (op == '*') {
            int multipliers = (num1_integers_len - len_diff);
            calc_mul(num1_integers, num2_integers, num1_integers_len, radix, multipliers);
        } else if (op == '/') {
            calc_div(num1_integers, num2_integers);
        } else {
            printf("\nPlease choose a valid operator...\n");
        }
        persist = false;
    }
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ MAIN MENU ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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
            printf("DECIMAL TO RADICES CONVERTER\n");
            printf("Convert decimal numbers to radices (binary - hexadecimal)!\n\n");

            int dec;
            printf("Enter your number: ");
            scanf("%d", &dec);
            int r;
            printf("Enter your radix: ");
            scanf("%d", &r);
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

