#include <stdio.h>
#include <stdlib.h>

int     put_piece(char **array_result, int array_pieces[][4], int index, int x, int y, int piece, char c)
{
    int result;
    
    result = 0;
    printf("Test sur x = %d, y = %d\n", x, y);
    if (array_result[y][x] == '.')
    {
        printf("Test OK\n");
        array_result[y][x] = c;
        piece++;
        if (piece == 4)
            return (1);
        if (!((array_pieces[index][piece] - array_pieces[index][piece-1]) <= (4 * (y + 1) - array_pieces[index][piece-1])))
        {
            x = (array_pieces[index][piece] - array_pieces[index][piece-1]) - (4 - (array_pieces[index][piece-1] - 4 * y)) - 1;
            y++;
        }
        else
            x++;
        result = put_piece(array_result, array_pieces, index, x, y, piece, c);
        if (result)
            return (1);
        else
            return (0);
    }
    printf("Test Faux\n");
    return (0);
}

void    print_tab(char **result)
{
    int i;
    int j;
    i = 0;
    j = 0;
    printf("|x|0|1|2|3|\n|");
    while (result[i] && result[i+1])
    {
        printf("%d", i);
        while (result[i][j])
        {
            printf("|%c", result[i][j]);
            j++;
        }
        j = 0;
        i++;
    }
}

int     main(void)
{
    char    **result;
    result = malloc(sizeof(char*) * 5);
    result[0] = malloc(sizeof(char) * 6);
    result[1] = malloc(sizeof(char) * 6);
    result[2] = malloc(sizeof(char) * 6);
    result[3] = malloc(sizeof(char) * 6);
    result[4] = malloc(sizeof(char) * 6);
    int i;
    i = 0;
    while (i < 4)
    {
        result[i][0] = '.';
        result[i][1] = '.';
        result[i][2] = '.';
        result[i][3] = '.';
        result[i][4] = '\n';
        i++;
    }
    result[4][0] = '\0';
    int     array_pieces[1][4] = {{1, 5, 9, 13}};
    printf("Return : %d\n", put_piece(result, array_pieces, 0, 0, 0, 0, 'a'));
    print_tab(result);
    return (0);
}
