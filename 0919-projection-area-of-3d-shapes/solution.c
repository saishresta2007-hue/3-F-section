int projectionArea(int** grid, int gridSize, int* gridColSize) {
    int area = 0;

    // XY projection
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            if (grid[i][j] > 0)
                area++;
        }
    }

    // YZ projection (row maxima)
    for (int i = 0; i < gridSize; i++) {
        int rowMax = 0;

        for (int j = 0; j < gridSize; j++) {
            if (grid[i][j] > rowMax)
                rowMax = grid[i][j];
        }

        area += rowMax;
    }

    // ZX projection (column maxima)
    for (int j = 0; j < gridSize; j++) {
        int colMax = 0;

        for (int i = 0; i < gridSize; i++) {
            if (grid[i][j] > colMax)
                colMax = grid[i][j];
        }

        area += colMax;
    }

    return area;
}
