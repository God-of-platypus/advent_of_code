#define _POSIX_C_SOURCE 200810L
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef enum {
    FiveOfKind,
    FourOfKind,
    FullHouse,
    ThreeOfKind,
    TwoPair,
    OnePair,
    High,
} HandType;

typedef struct {
    char *value;
    HandType type;
    int bid;
} Hand;

HandType getType(char *str) {
    int array[13] = {0};
    for(int i = 0; i < strlen(str); i++) {
        switch (str[i]) {
            case 'A':
                array[0]++;
                break;
            case 'K':
                array[1]++;
                break;
            case 'Q':
                array[2]++;
                break;
            case 'J':
                array[3]++;
                break;
            case 'T':
                array[4]++;
                break;
            case '9':
                array[5]++;
                break;
            case '8':
                array[6]++;
                break;
            case '7':
                array[7]++;
                break;
            case '6':
                array[8]++;
                break;
            case '5':
                array[9]++;
                break;
            case '4':
                array[10]++;
                break;
            case '3':
                array[11]++;
                break;
            case '2':
                array[12]++;
                break;
            default:
                break;
        }
    }
    int five = 0;
    int four = 0;
    int three = 0;
    int two = 0;
    int joker = array[3];
    array[3] = 0; 
    for (int i = 0; i < 13; i++) {
        switch (array[i]) {
            case 5:
                five++;
                break;
            case 4:
                four++;
                break;
            case 3:
                three++;
                break;
            case 2:
                two++;
                break;
            default:
                break;
        }
    }
    if (five || joker == 5 || joker == 4) {
        return FiveOfKind;
    }
    if (four) {
        if (joker == 1) {
            return FiveOfKind;
        }
        return FourOfKind;
    }
    if (three && two) {
        return FullHouse;
    }
    if (three) {
        if (joker == 2) {
            return FiveOfKind;
        }
        if (joker == 1) {
            return FourOfKind;
        }
        return ThreeOfKind;
    }
    if (two == 2) {
        if (joker == 1) {
            return FullHouse;
        }
        return TwoPair;
    }
    if (two) {
        if (joker == 3) {
            return FiveOfKind;
        }
        if (joker == 2) {
            return FourOfKind;
        }
        if (joker) {
            return ThreeOfKind;
        }
        return OnePair;
    }
    if (joker == 3) {
        return FourOfKind;
    }
    if (joker == 2) {
        return ThreeOfKind;
    }
    if (joker) {
        return OnePair;
    }
    return High;
}

int compare_hand_value(char *s1, char *s2) {
    for(int i = 0; i < 5; i++) {
        if (s1[i] == s2[i]) {
            continue;
        }
        if (s1[i] == 'J')
            return -1;
        if (s2[i] == 'J')
            return 1;
        if (isdigit(s1[i]) && isdigit(s2[i])) {
            if (s1[i] > s2[i])
                return 1;
            else
                return -1;
        }
        if (isdigit(s1[i]))
            return -1;
        if (isdigit(s2[i]))
            return 1;
        if (s1[i] == 'A')
            return 1;
        if (s2[i] == 'A')
            return -1;
        if (s1[i] == 'K')
            return 1;
        if (s2[i] == 'K')
            return -1;
        if (s1[i] == 'Q')
            return 1;
        if (s2[i] == 'Q')
            return -1;
        if (s1[i] == 'T')
            return -1;
        if (s2[i] == 'T')
            return 1;
    }
    return 0;
}

void sort(Hand **arr, int len) {
    int i,j;
    for (i = 0; i < len - 1; i++) {
        for (j = 0; j < len - 1 - i; j++) {
            Hand *a = arr[j];
            Hand *b = arr[j+1];
            if (a->type < b->type) {
                Hand *tmp = a;
                arr[j] = arr[j+1];
                arr[j+1] = a;
            } else if (compare_hand_value(a->value, b->value) > 0 && a->type == b->type) {
                Hand *tmp = a;
                arr[j] = arr[j+1];
                arr[j+1] = a;
            }
        }
    }
}

int main(void) {
    char *line;
    long unsigned int acc = 0;
    FILE *file = fopen("input.txt", "r");
    size_t len = 0;
    ssize_t nread;
    Hand **hands = malloc(sizeof(Hand*));
    int len_hand = 0;

    while ((nread = getline(&line, &len, file)) != -1) {
        char *str = malloc(6 * sizeof(char));
        int i = 0;
        while (line[i] != ' ') {
            str[i] = line[i];
            i++;
        }
        str[i+1] = 0;
        i++;
        int bid = 0;
        while (isdigit(line[i])) {
            bid = bid * 10 + line[i++] - '0';
        }
        Hand *hand = malloc(sizeof(Hand));
        hand->value = str;
        hand->bid = bid;
        hand->type = getType(str);
        hands[len_hand++] = hand;
        Hand **tmp = realloc(hands, (len_hand + 1) * sizeof(Hand *));
        if (tmp != hands) {
            hands = tmp;
        }
    }
    sort(hands, len_hand);
    for (int i = 0; i < len_hand; i++) {
        acc += (i +1) * hands[i]->bid;
    }
    printf("The result of part 1 is %ld\n", acc);
}


