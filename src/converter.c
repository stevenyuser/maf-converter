#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// removes '-' from string
void removeGaps(char *str)
{
    int i, j;
    int len = strlen(str);
    for (i = 0; i < len; i++)
    {
        if (str[i] == '-')
        {
            for (j = i; j < len; j++)
            {
                str[j] = str[j + 1];
            }
            len--;
            i--;
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Wrong number of arguments\n");
        exit(1);
    }

    char *in = argv[1];
    char *out = argv[2];

    FILE *input_file = NULL;
    FILE *output_file = NULL;
    input_file = fopen(in, "r");
    output_file = fopen(out, "w");

    if (input_file == NULL)
    {
        printf("Could not open input file\n");
        exit(1);
    }

    if (output_file == NULL)
    {
        printf("Could not open output file\n");
        exit(1);
    }

    // read length is determined by the longest read length
    int read_length = 0;
    // number of read pairs that are in the file
    int num_reads = 0;

    char *garbage = NULL;
    int garbage_length = 0;
    size_t garbage_allocated = 0;

    char *line1 = NULL;
    char *line2 = NULL;
    int line1_length = 0;
    int line2_length = 0;
    size_t line1_allocated = 0;
    size_t line2_allocated = 0;
    char *pattern;
    char *text;

    while (1)
    {
        // remove first garbage line
        garbage_length = getline(&garbage, &garbage_allocated, input_file);

        line1_length = getline(&line1, &line1_allocated, input_file);
        if (line1_length == -1)
        {
            break;
        }

        line2_length = getline(&line2, &line2_allocated, input_file);
        if (line2_length == -1)
        {
            break;
        }

        // remove junk before beginning of pattern
        char *pattern;
        pattern = strtok(line1, " ");
        for (int i = 0; i < 6; i++)
        {
            pattern = strtok(NULL, " ");
        }
        // printf("%s\n", pattern);

        // remove "-" characters from pattern
        removeGaps(pattern);

        printf("%s\n", pattern);

        fprintf(output_file, ">%s", pattern);

        // remove junk before beginning of text
        text = strtok(line2, " ");
        for (int i = 0; i < 6; i++)
        {
            text = strtok(NULL, " ");
        }
        // printf("%s\n", text);

        // remove "-" characters from token
        removeGaps(text);

        printf("%s\n", text);

        fprintf(output_file, "<%s", text);


        // -1 accounts for \n at end of line
        if(read_length < (strlen(text) - 1))
        {
            read_length = strlen(text) - 1;
        } else if(read_length < (strlen(pattern) - 1))
        {
            read_length = strlen(pattern) - 1;
        }
        num_reads++;

        // remove last garbage line
        garbage_length = getline(&garbage, &garbage_allocated, input_file);
    }

    fclose(input_file);
    fclose(output_file);

    printf("Read length: %d\n", read_length);
    printf("Number of read pairs: %d\n", num_reads);
    return 0;
}
