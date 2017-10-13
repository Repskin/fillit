#include <stdio.h>
#include <stdlib.h>

char    **initialize_result_array(int width)
{
    int     i;
    int     j;
    char    **array_result;
    
    i = 0;
    j = 0;
    array_result = malloc(sizeof(char*) * width);
    while (i < width)
    {
        array_result[i] = malloc(sizeof(char) * (width + 1));
        i++;
    }
    i = 0;
    while (i < width)
    {
        while (j < (width + 1))
        {
            array_result[i][j] = '.';
            j++;
        }
        array_result[i][j-1] = '\n';
        j = 0;
        i++;
    }
    return (array_result);
}

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
    printf("|x|0|1|2|3|\n");
    while (result[i])
    {
        printf("|%d", i);
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
    
    result = initialize_result_array(4);
    int     array_pieces[1][4] = {{2, 3, 5, 6}};
    printf("Return : %d\n", put_piece(result, array_pieces, 0, 0, 0, 0, 'a'));
    print_tab(result);
    printf("\n\n\n\n\n");
    
    result = initialize_result_array(4);
    int     array_pieces2[1][4] = {{1, 2, 3, 4}};
    printf("Return : %d\n", put_piece(result, array_pieces2, 0, 0, 0, 0, 'b'));
    print_tab(result);
    printf("\n\n\n\n\n");
    
    result = initialize_result_array(4);
    int     array_pieces3[1][4] = {{1, 2, 6, 7}};
    printf("Return : %d\n", put_piece(result, array_pieces3, 0, 0, 0, 0, 'c'));
    print_tab(result);
    printf("\n\n\n\n\n");
    
    result = initialize_result_array(4);
    int     array_pieces4[1][4] = {{1, 5, 9, 10}};
    printf("Return : %d\n", put_piece(result, array_pieces4, 0, 0, 0, 0, 'd'));
    print_tab(result);
    printf("\n\n\n\n\n");
    
    result = initialize_result_array(4);
    int     array_pieces5[1][4] = {{1, 2, 3, 7}};
    printf("Return : %d\n", put_piece(result, array_pieces5, 0, 0, 0, 0, 'e'));
    print_tab(result);
    printf("\n\n\n\n\n");
    
    result = initialize_result_array(4);
    int     array_pieces6[1][4] = {{1, 2, 5, 6}};
    printf("Return : %d\n", put_piece(result, array_pieces6, 0, 0, 0, 0, 'f'));
    print_tab(result);
    printf("\n\n\n\n\n");
    return (0);
}
