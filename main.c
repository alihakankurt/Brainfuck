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
        fprintf(stderr, "Couldn't allocate enough memory for file content");
        return 1;
    }

    fread(source, sizeof(char), size, fp);
    fclose(fp);

    unsigned char *memory = calloc(MEMORY_SIZE, sizeof(char));
    int index, scope;
    for (index = 0; index < size; index++)
    {
        switch (source[index])
        {
            case '>':
                memory++;
                break;

            case '<':
                memory--;
                break;
            
            case '+':
                (*memory)++;
                break;
            
            case '-':
                (*memory)--;
                break;

            case '.':
                putc(*memory, stdout);
                break;
            
            case ',':
                *memory = getc(stdin);
                break;
            
            case '[':
                if (!(*memory))
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
                if (*memory)
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
    free(memory);
    return 0;
}
