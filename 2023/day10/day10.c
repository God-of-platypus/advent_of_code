#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define constants
#define MAX_ROWS 140
#define MAX_COLS 140

int distances[MAX_ROWS][MAX_COLS] = {0};
int visited[MAX_ROWS][MAX_COLS] = {0};
// Define directions
typedef struct {
    int dx, dy;
} Direction;

Direction directions[] = {
    {0, -1},  // Up
    {0, 1},   // Down
    {-1, 0},  // Left
    {1, 0}    // Right
};

// Connection rules for each tile type
Direction connections[128][4];  // ASCII-based mapping

void initialize_connections() {
    // Initialize connection rules
    memset(connections, 0, sizeof(connections));
    connections['|'][0] = directions[0]; // Up
    connections['|'][1] = directions[1]; // Down
    connections['-'][2] = directions[2]; // Left
    connections['-'][3] = directions[3]; // Right
    connections['L'][0] = directions[0]; connections['L'][3] = directions[3]; // Up, Right
    connections['J'][0] = directions[0]; connections['J'][2] = directions[2]; // Up, Left
    connections['7'][1] = directions[1]; connections['7'][2] = directions[2]; // Down, Left
    connections['F'][1] = directions[1]; connections['F'][3] = directions[3]; // Down, Right
}

// Utility function to check bounds
int in_bounds(int x, int y, int rows, int cols) {
    return x >= 0 && x < cols && y >= 0 && y < rows;
}

int get_neighbors(char maze[MAX_ROWS][MAX_COLS], int rows, int cols, int x, int y, int neighbors[MAX_ROWS * MAX_COLS][2]) {
    int count = 0;
    char tile = maze[y][x];

    if (tile == 'S') {
        for (int d = 0; d < 4; ++d) {
            Direction dir = directions[d];
            int nx = x + dir.dx, ny = y + dir.dy;
            if (in_bounds(nx, ny, rows, cols) && maze[ny][nx] != '.') {
                char neighbor_tile = maze[ny][nx];
                for (int rd = 0; rd < 4; ++rd) {
                    Direction reverse = connections[(int)neighbor_tile][rd];
                    if (nx + reverse.dx == x && ny + reverse.dy == y) {
                        neighbors[count][0] = nx;
                        neighbors[count][1] = ny;
                        count++;
                        break;
                    }
                }
            }
        }
    } else {
        for (int d = 0; d < 4; ++d) {
            Direction dir = connections[(int)tile][d];
            if (dir.dx == 0 && dir.dy == 0) continue;

            int nx = x + dir.dx, ny = y + dir.dy;
            if (in_bounds(nx, ny, rows, cols) && maze[ny][nx] != '.') {
                char neighbor_tile = maze[ny][nx];
                for (int rd = 0; rd < 4; ++rd) {
                    Direction reverse = connections[(int)neighbor_tile][rd];
                    if (nx + reverse.dx == x && ny + reverse.dy == y) {
                        neighbors[count][0] = nx;
                        neighbors[count][1] = ny;
                        count++;
                        break;
                    }
                }
            }
        }
    }

    return count;
}// Function to get neighbors

// BFS to find the loop and calculate distances
int find_loop_and_distances(char maze[MAX_ROWS][MAX_COLS], int rows, int cols, int sx, int sy) {
    int max_distance = 0;

    // BFS queue
    int queue[MAX_ROWS * MAX_COLS][2], front = 0, rear = 0;
    queue[rear][0] = sx;
    queue[rear][1] = sy;
    rear++;
    visited[sy][sx] = 1;

    while (front < rear) {
        int cx = queue[front][0];
        int cy = queue[front][1];
        front++;

        int neighbors[MAX_ROWS * MAX_COLS][2];
        int count = get_neighbors(maze, rows, cols, cx, cy, neighbors);

        for (int i = 0; i < count; ++i) {
            int nx = neighbors[i][0];
            int ny = neighbors[i][1];
            if (!visited[ny][nx]) {
                visited[ny][nx] = 1;
                distances[ny][nx] = distances[cy][cx] + 1;
                if (distances[ny][nx] > max_distance) {
                    max_distance = distances[ny][nx];
                }
                queue[rear][0] = nx;
                queue[rear][1] = ny;
                rear++;
            }
        }
    }

    return max_distance;
}

int main() {
    // Open the file containing the maze
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        perror("Failed to open file");
        return 1;
    }

    
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char maze[MAX_ROWS][MAX_COLS];
    int rows = 0, cols = 0;

    while ((read = getline(&line, &len, file)) != -1) {
        line[read - 1] = '\0'; // Remove the newline character at the end of each line
        strncpy(maze[rows], line, MAX_COLS);
        if (cols < read - 1) {
            cols = read - 1; // Update column size if necessary
        }
        rows++;
    }
    free(line);
    fclose(file);

    // Initialize connection rules for tiles
    initialize_connections();

    // Find starting position
    int sx = -1, sy = -1;
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            if (maze[y][x] == 'S') {
                sx = x;
                sy = y;
                break;
            }
        }
        if (sx != -1) break;
    }

    if (sx == -1 || sy == -1) {
        printf("Start position 'S' not found.\n");
        return 1;
    } else {
        printf("The S is at %d, %d\n", sx ,sy);
    }

    // Find the maximum distance
    int max_distance = find_loop_and_distances(maze, rows, cols, sx, sy);
    printf("Maximum distance from S: %d\n", max_distance);
    int res = 0;
    for (int y = 0; y < rows; ++y) {
        int inside = 0;
        for (int x = 0; x < cols; ++x) {
            if (maze[y][x] == '|' || maze[y][x] == 'J' || maze[y][x] == 'L') {
                if (visited[y][x] == 1) {
                    inside = 1 - inside;
                }
            }
            res += inside && (visited[y][x] == 0);      
        }
    }
    printf("Enclosed tiles: %d\n", res);
    return 0;
}

