/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    int i;
    int j;
    
    int high_number = (d*d) - 1;
    
    for (i = 0; i < d; i++) {
        for (j = 0; j < d; j++) {
            board[i][j] = high_number;
            high_number--;
        }
    }
    
    // If d is even, swap tiles 1 and 2. If d is odd, do not swap tiles 1 and 2.
    if (d % 2 == 0) {
        int last_row = d-1;
        int second_last_col = d-2;
        int third_last_col = d-3;
        
        int temp = board[last_row][second_last_col];
        board[last_row][second_last_col] = board[last_row][third_last_col];
        board[last_row][third_last_col] = temp;
    }
    return;
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    int i, j;
    
    for(i = 0; i < d; i++) {
        for (j = 0; j < d; j++)
            printf("%2i ", board[i][j]);
        printf("\n");
    }
}

/**
 * Check if adjacent tile is a zero and swap the current tile with it if so. 
 */
bool adj_op(int tile, int tile_row, int tile_col, int adj_tile_row, int adj_tile_col)
{
    if (adj_tile_col >= 0 && adj_tile_col <= d-1 && adj_tile_row >= 0 && adj_tile_row <= d-1) {
        int adj_tile = board[adj_tile_row][adj_tile_col];
        if (adj_tile == 0) {
            int temp = adj_tile;
            board[adj_tile_row][adj_tile_col] = tile;
            board[tile_row][tile_col] = temp;
            return true;
        }
    }
    return false;
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    bool tile_exists = false;
    int tile_row, tile_col;

    // Perform a linear search seeking tile in board.
    for (int i = 0; i < d; i++) {
        for (int j = 0; j < d; j++) {
            if (board[i][j] == tile) {
                tile_row = i;
                tile_col = j;
                tile_exists = true;
                break;
            }
        }
    }

    // Check if the user-inputted tile exists.
    if (!tile_exists)
        return false;
        
    int N_tile_col = tile_col;
    int N_tile_row = tile_row + 1;
    if (adj_op(tile, tile_row, tile_col, N_tile_row, N_tile_col))
        return true;
    
    int S_tile_col = tile_col;
    int S_tile_row = tile_row - 1;
    if (adj_op(tile, tile_row, tile_col, S_tile_row, S_tile_col))
        return true;
    
    int E_tile_col = tile_col + 1;
    int E_tile_row = tile_row;
    if (adj_op(tile, tile_row, tile_col, E_tile_row, E_tile_col))
        return true;
    
    int W_tile_col = tile_col - 1;
    int W_tile_row = tile_row;
    if (adj_op(tile, tile_row, tile_col, W_tile_row, W_tile_col))
        return true;
    
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    // TODO
    return false;
}
