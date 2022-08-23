#include "util.h"

void email(char data) {
    static states state = q1;
    static char email[256];
    static size_t pos = 0;

    switch (state) {
        case q1:
            switch (data) {
                case 0 ... 9:
                case 'a' ... 'z':
                case 'A' ... 'Z':
                case '.':
                case '_':
                    state = q2;
                    email[pos] = data;
                    pos++;
                    break;
            }
            break;
        case q2:
            switch (data) {
                case 0 ... 9:
                case 'a' ... 'z':
                case 'A' ... 'Z':
                case '.':
                case '_':
                    email[pos] = data;
                    pos++;
                    break;
                case '@':
                    state = q3;
                    email[pos] = data;
                    pos++;
                    break;
                default:
                    state = q1;
                    memset(email, 0, strlen(email));
                    pos = 0;
                    break;
            }
            break;
        case q3:
            switch (data) {
                case 0 ... 9:
                case 'a' ... 'z':
                case 'A' ... 'Z':
                    state = q4;
                    email[pos] = data;
                    pos++;
                    break;
                default:
                    state = q1;
                    memset(email, 0, strlen(email));
                    pos = 0;
                    break;
            }
            break;
        case q4:
            switch (data) {
                case 0 ... 9:
                case 'a' ... 'z':
                case 'A' ... 'Z':
                    email[pos] = data;
                    pos++;
                    break;
                case '.':
                    state = q3;
                    email[pos] = data;
                    pos++;
                    break;
                default:
                    printf("%s\n", email);
                    state = q1;
                    memset(email, 0, strlen(email));
                    pos = 0;
                    break;
            }
    }
}


size_t process_data(char *data, size_t a, size_t n, void* b) {

    for(int i = 0; i < n; i++) {
        email(data[i]);
    }

    return n;
}
