#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

const char* keywords[] = {
    "int", "return", "const", "char", "if", "else", "while", "for", "void",
    "float", "double", "struct", "typedef", "enum", "break", "continue", "switch", "case",
    "default", "do", "goto", "sizeof", "static", "extern", "inline", NULL
};

typedef enum {
    IDENTIFIER,
    NUMBER,
    STRING,
    PUNCTUATION,
    KEYWORD,
    OPERATOR,
    ELLIPSIS,
    UNKNOWN,
    LEXME_EOF
} TokenType;

const char* token_type_to_name(TokenType type) {
    switch (type) {
        case IDENTIFIER: return "identifier";
        case NUMBER: return "number";
        case STRING: return "string";
        case PUNCTUATION: return "punctuation";
        case KEYWORD: return "keyword";
        case OPERATOR: return "operator";
        case ELLIPSIS: return "ellipsis";
        case UNKNOWN: return "unknown";
        case LEXME_EOF: return "eof";
        default: return "invalid";
    }
}

typedef struct {
    TokenType type;
    char value[256];
    unsigned int start;
    unsigned int length;
    unsigned int line;
} Token;

void Usage() {
    printf("\t\t'LexMe' is minimized lexical analysis tokenizer for compiler development's first stage ...\n");
    printf("\n[>] Lexme.exe <file.c>\n");
}

bool isCFile(const char* filename) {
    const char* p = strrchr(filename, '.');
    if (!p || strcmp(p, ".c") != 0) {
        printf("[!] FILE : %s is not a C file, please be careful in extension\n", filename);
        return false;
    }
    return true;
}

char* ReadCFile(const char *filename) {
    if (!isCFile(filename)) return NULL;

    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "[!] Cannot read file %s\n", filename);
        return NULL;
    }

    fseek(file , 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    char *buff = malloc(size + 1);
    if (!buff) {
        fprintf(stderr, "[!] Memory allocation failed.\n");
        fclose(file);
        return NULL;
    }

    fread(buff, 1, size, file);
    buff[size] = '\0';
    fclose(file);

    return buff;
}

int is_keyword(const char* word) {
    for (int i = 0; keywords[i]; i++) {
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

char* input = NULL;
int pos = 0;
unsigned int current_line = 1;

char peek() {
    return input[pos];
}

char advance() {
    char c = input[pos++];
    if (c == '\n')
        current_line++;
    
    return c;
}

void skip_whitespace() {
    while (isspace(peek())) advance();
}

void skip_comments() {
    if (peek() == '/' && input[pos + 1] == '/') 
        while (peek() != '\n' && peek() != '\0') advance();
    
    else if (peek() == '/' && input[pos + 1] == '*') {
        pos += 2;  // skip /*

        while (peek() != '\0') {
            if (peek() == '*' && input[pos + 1] == '/') {
                pos += 2;  // skip */
                break;
            }
            advance();
        }
    }
}

Token next_token() {
    skip_whitespace();
    skip_comments();
    skip_whitespace();

    char c = peek();

    Token token;
    token.value[0] = '\0';
    token.start = pos;
    token.line = current_line;

    if (c == '\0') {
        token.type = LEXME_EOF;
        token.length = 0;
        return token;
    }

    if (isalpha(c) || c == '_') {
        int i = 0;
        
        while (isalnum(peek()) || peek() == '_') 
            token.value[i++] = advance();
        
        token.value[i] = '\0';
        token.type = is_keyword(token.value) ? KEYWORD : IDENTIFIER;
        token.length = i;
        
        return token;
    }

    if (isdigit(c)) {
        int i = 0;
        int has_dot = 0;
     
        while (isdigit(peek()) || (!has_dot && peek() == '.')) {
            if (peek() == '.') has_dot = 1;
            token.value[i++] = advance();
        }
     
        token.value[i] = '\0';
        token.type = NUMBER;
        token.length = i;
     
        return token;
    }

    if (c == '"') {
        advance();
        int i = 0;

        while (peek() != '"' && peek() != '\0') 
            token.value[i++] = advance();
        
        advance();
        
        token.value[i] = '\0';
        token.type = STRING;
        token.length = i + 2;
        
        return token;
    }

    if (c == '.' && input[pos + 1] == '.' && input[pos + 2] == '.') {
        pos += 3;
        strcpy(token.value, "...");
        token.type = ELLIPSIS;
        token.length = 3;
        return token;
    }

    char punct = advance();

    token.value[0] = punct;
    token.value[1] = '\0';
    token.length = 1;

    if (strchr("(){};,*", punct)) 
        token.type = PUNCTUATION;
    
    else if (strchr("+-=/%", punct)) 
        token.type = OPERATOR;

    else 
        token.type = UNKNOWN;

    return token;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        Usage();
        return -1;
    }

    const char *filename = argv[1];
    char *content = ReadCFile(filename);

    if (!content) return -1;

    printf("[\n");

    bool first = true;
    input = content;
    
    Token token;

    do {
        token = next_token();
        if (token.type == LEXME_EOF) break;

        if (!first) 
            printf(",\n");

        first = false;

        printf("  {\n");
        printf("    \"type\": \"%s\",\n", token_type_to_name(token.type));
        printf("    \"value\": \"%s\",\n", token.value);
        printf("    \"start\": %u,\n", token.start);
        printf("    \"length\": %u,\n", token.length);
        printf("    \"line\": %u\n", token.line);
        
        printf("  }");
    } while (1);
    
    printf("\n]\n");

    free(content);

    return 0;
}
