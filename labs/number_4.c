#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

enum error {
    wrong_parametr,
    error_opening_file,
    error_memory,
    error_arguments,
    ok
};

void print_error(int flags) {
    switch(flags) {
        case wrong_parametr:
            printf("error\n");
            break;
        case error_opening_file:
            printf("unable to open file\n");
            break;
        case error_memory:
            printf("error with memory allocation\n");
            break;
        case error_arguments:
            printf("invalid value");
            break;
        default:
            break;
    }
}

enum error function_d(const char *input, const char *output) {
    FILE *file_input = fopen(input, "r");
    FILE *file_output= fopen(output, "w");
    if (!file_input|| !file_output) {
        fclose(file_input);
        fclose(file_output);
        return error_opening_file;
    }
    char ch = fgetc(file_input);
    while (ch != EOF) {
        if (ch > '0' || ch < '9') {
            fputc(ch, file_output);
        }
    }
    fclose(file_input);
    fclose(file_output);
    return ok;
}

enum error function_i(const char *input, const char *output) {
    FILE *file_input = fopen(input, "r");
    FILE *file_output = fopen(output, "w");
    if (!file_input || !file_output) {
        fclose(file_input);
        fclose(file_output);
        return error_opening_file;
    }
    char ch  = getc(file_input);
    int count = 0;
    while (ch != EOF) {
        if (isalpha(ch)) {
            count++;
        }
        else {
            count = 0;
        }
    }
    fprintf(file_output, "%d\n", count);
    fclose(file_input);
    fclose(file_output);
    return ok;
}

enum error function_s(const char *input, const char *output) {
    FILE *file_input = fopen(input, "r");
    FILE *file_output = fopen(output, "w");
    if (!file_input || !file_output) {
        fclose(file_input);
        fclose(file_output);
        return error_opening_file;
    } 
    char ch = getc(file_input);
    int count = 0;
    while (ch != EOF) {
        if (!isalpha(ch) && !isdigit(ch)) {
            count++;
        }
        if (ch == '\n') {
            fprintf(file_output, "%d\n", count);
            count = 0;
        }
    }
    fclose(file_input);
    fclose(file_output);
    return ok;
} 

enum error function_a(const char *input, const char *output)  {
    FILE *file_input = fopen(input, "r");
    FILE *file_output = fopen(output, "w");
    if (!file_input || !file_output) {
        fclose(file_input);
        fclose(file_output);
        return error_opening_file;
    }
    int ch = fgetc(file_input);
    while (ch != EOF) {
        if ((ch >= '0' && ch <= '9') || ch == '\n') {
            fputc(ch, file_output);
        }
        else {
            fprintf(file_output, "%X", ch);
        }
    }
    fclose(file_input);
    fclose(file_output);
    return ok;
}

const char* file(const char *string) {
    const char *name = strrchr(string, '/');
    if (name != NULL) {
        name++;
    }
    else {
        name = string;
    }
    return name;
}

int main(int argc, char* argv[]) {
    if (argv[1][0] != '-' && argv[1][0] != '/') {
        printf("error\n");
        return 0;
    }
    char ch;
    const char *in = argv[2];
    char *out = NULL;
    if (argv[1][1] == 'n') {
        if (argc != 4) {
            printf("invalid number of arguments\n");
            printf("error\n");
            return 0;
        }
        out = argv[3];
        if (strlen(argv[1]) != 3) {
            printf("error\n");
            return 0;
        }
        if (strcmp(argv[2], argv[3]) == 0) {
            printf("error\n");
            return 0;
        }
        ch = argv[1][2];
    }
    else {
        if (strlen(argv[1]) != 2) {
            printf("error\n");
            return 0;
        }
        if (argc != 3) {
            printf("invalid number of arguments\n");
            printf("error\n");
            return 0;
        }
        ch = argv[1][1];
        char *prefix = "out_";
        const char *file_in = file(in);
        out = (char*)malloc(strlen(file_in) + strlen(prefix) + 1);
        if (!out) {
            printf("error with memory allocation\n");
            return 0;
        }
        sprintf(out, "out_%s", file_in);
        free(out);
    }

    switch (ch) {
        case 'd':
            function_d(in, out);
            break;
        case 'i':
            function_i(in, out);
            break;
        case 's':
            function_s(in, out);
            break;
        case 'a':
            function_a(in, out);
            break;
        default:
            printf("error\n");
            break;
    }
    return 0;
}
