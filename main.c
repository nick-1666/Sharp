#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdbool.h>
#include <ctype.h>
#include "stack.h"
#include "math.h"

int lines = 1;
int position = 0;

bool hexLiteral = false;
char hexString[32] = "";

char *arithmaticSymbols = "+-*/%";
char *commandSymbols = ".:,;|[]=";
char *hexSymbols = "0123456789abcdef-";
char *validSymbols = "#0123456789abcdef.:,;|[]=()+-*/%\n\t ";

void setPosition(char cc);
void pushHex(char cc);
bool loopOpen(struct stack *pt, FILE *fp, char cc);

int main(int argc, const char * argv[])
{
    struct stack *pt = newStack();
    FILE *fp;
    char cc;

    size_t loop = 0;

    if (argc != 2 || (fp = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "Usage: sharp.exe <filename>.#\n");
        exit(1);
    }

    while ((cc = tolower(fgetc(fp))) != EOF)
    {
        setPosition(cc);
        if(cc == '\t' || cc == ' ' || cc == '\n') continue;
        /* comment handleing. Skips to the next
         * newline. Multilines are unsupported.
         */
        if(cc == '#') {
            do {
                cc = fgetc(fp);
            }
            while (cc != '\n');
            lines++;
            continue;
        }

        /* gets rid of invalid symbols. Comments are done
         * first so that invalid characters in text get ignored
         */
        if(!strchr(validSymbols, cc)) {
            fprintf(stderr, "Unknown character \"%c\" at line %d:%d\n", cc, lines, position);
            exit(1);
        }

        if(hexLiteral) {
            if(cc == ')') {
                hexLiteral = false;
                //allows () to just pop a value
                if(hexString[0] == '\0') pop(pt);
                else push(pt, (int)strtol(hexString, NULL, 16));
                continue;
            }

            if(strchr(hexSymbols, cc)) {
                pushHex(cc);
                continue;
            }
            else {
                fprintf(stderr, "Not a hexidecimal character \"%c\" at line %d:%d\n", cc, lines, position);
                exit(1);
            }
        }

        if(cc == '(') {
            hexLiteral = true;
            memset(hexString, 0, 32);
            continue;
        }

        if(cc == ')') {
            fprintf(stderr, "Extra closing literal at line %d:%d\n", lines, position);
            exit(1);
        }

        if(strchr(arithmaticSymbols, cc)) {
            arithmatic(pt, cc);
            continue;
        }

        if(cc == '[') {
            loop ++;
            if(loopOpen(pt, fp, cc)) {
                continue;
            }
        }

        if(cc == ']') {
            loop --;

            do {
                fseek(fp, -2, SEEK_CUR);
                cc = fgetc(fp);
                if(cc == '\n') lines--;
            } while (cc != '[');
            loopOpen(pt, fp, cc);
        }

        if(cc == '|') { reverse(pt); continue; }
        if(cc == '=') { push(pt, peek(pt)); continue;}

        if(cc == '.') {
            char ci;
            scanf("%c", &ci);
            push(pt, (int)(ci-'0'));
        }

        if(cc == ':') {
            char ci;
            scanf("%c", &ci);
            push(pt, ci);
        }

        if(cc == ',') {
            fprintf(stderr, "%d", pop(pt));
            continue;
        }
        if(cc == ';') {
            fprintf(stderr, "%c", pop(pt));
            continue;
        }

    }

    fclose(fp);

    exit(0);
}

void pushHex(char cc) {
    int len = strlen(hexString);
    hexString[len] = cc;
    hexString[len + 1] = '\0';
}

void setPosition(char cc) {
    if(cc == '\n') {
        lines++;
        // account for newline
        position = -1;
    }

    position++;
}
bool loopOpen(struct stack *pt, FILE *fp, char cc) {
    if(pop(pt) == 0) {
        do {
            cc = fgetc(fp);
            if(cc == '\n') lines++;
        }
        while (cc != ']');
        return true;
    }
    return false;
}