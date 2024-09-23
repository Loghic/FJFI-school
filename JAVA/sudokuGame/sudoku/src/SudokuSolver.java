public class SudokuSolver implements SudokuImplementation {

    public SudokuSolver() {
    }

    @Override
    public void goButtonPressed(Integer[][] leftSudokuValues, SudokuController resultAcceptor) {
        System.out.println("Solving Sudoku...");

        long startTime = System.currentTimeMillis(); // Record the start time

        // Copy the board to solve
        Integer[][] sudokuBoard = new Integer[9][9];
        for (int i = 0; i < 9; i++) {
            System.arraycopy(leftSudokuValues[i], 0, sudokuBoard[i], 0, 9);
        }

        boolean solved = solveSudoku(sudokuBoard);

        long endTime = System.currentTimeMillis(); // Record the end time
        long elapsedTime = endTime - startTime; // Calculate the elapsed time

        // Notify the result of solving
        resultAcceptor.setSudokuResult(sudokuBoard);
        resultAcceptor.setSudokuCompleted(solved);
        resultAcceptor.setSudokuTime(elapsedTime + "ms");
        System.out.println("Done! Solved in " + elapsedTime + "ms");
    }

    // Solve the Sudoku using a backtracking algorithm
    private boolean solveSudoku(Integer[][] board) {
        for (int row = 0; row < 9; row++) {
            for (int col = 0; col < 9; col++) {
                if (board[row][col] == null) {
                    for (int num = 1; num <= 9; num++) {
                        if (isValid(board, row, col, num)) {
                            board[row][col] = num;
                            if (solveSudoku(board)) {
                                return true;
                            }
                            board[row][col] = null;
                        }
                    }
                    return false; // Backtrack if no valid number found
                }
            }
        }
        return true; // Sudoku solved
    }

    // Check if a number can be placed in a specific cell
    private boolean isValid(Integer[][] board, int row, int col, int num) {
        // Check the row
        for (int x = 0; x < 9; x++) {
            if (board[row][x] != null && board[row][x] == num) {
                return false;
            }
        }

        // Check the column
        for (int x = 0; x < 9; x++) {
            if (board[x][col] != null && board[x][col] == num) {
                return false;
            }
        }

        // Check the 3x3 grid
        int startRow = row - row % 3;
        int startCol = col - col % 3;
        for (int r = startRow; r < startRow + 3; r++) {
            for (int d = startCol; d < startCol + 3; d++) {
                if (board[r][d] != null && board[r][d] == num) {
                    return false;
                }
            }
        }
        return true;
    }
}
