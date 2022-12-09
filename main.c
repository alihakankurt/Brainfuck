#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE 4096

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "The source file wasn't provided");
        return 1;
    }

    FILE *fp = fopen(argv[1], "rb");
    if (!fp)
    {
        fprintf(stderr, "The source file couldn't open");
        return 1;
    }

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char *source = calloc(size, sizeof(char));
    if (!source)
    {
        fclose(fp);
        fprintf(stderr, "Couldn't allocate enough memory for file content");
        return 1;
    }

    fread(source, sizeof(char), size, fp);
    fclose(fp);

    unsigned char memory[MEMORY_SIZE] = { 0 };
    unsigned char *pointer = &memory[0];
    int index, scope;
    for (index = 0; index < size; index++)
    {
        switch (source[index])
        {
            case '>':
                pointer++;
                break;

            case '<':
                pointer--;
                break;
            
            case '+':
                (*pointer)++;
                break;
            
            case '-':
                (*pointer)--;
                break;

            case '.':
                putc(*pointer, stdout);
                break;
            
            case ',':
                *pointer = getc(stdin);
                break;
            
            case '[':
                if (!(*pointer))
                {
                    scope = 1;
                    while (scope)
                    {
                        index++;
                        if (index == size)
                            break;
                        
                        if (source[index] == '[')
                            scope++;
                        
                        if (source[index] == ']')
                            scope--;
                    }
                }

                break;

            case ']':
                if (*pointer)
                {
                    scope = 1;
                    while (scope)
                    {
                        index--;
                        if (index == -1)
                            break;
                        
                        if (source[index] == '[')
                            scope--;
                        
                        if (source[index] == ']')
                            scope++;
                    }
                }

                break;
        }
    }

    free(source);
    return 0;
}
