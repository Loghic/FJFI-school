import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionListener;
import java.util.*;

public class MineSweeper {
    private static final int MINE = 10;
    private static final int SIZE = 500;
    private static final double POPULATION_CONSTANT = 1.5;
    private static final Cell[] reusableStorage = new Cell[8];

    private int gridSize;
    private Cell[][] cells;
    private JFrame frame;
    private JButton reset;
    private JButton giveUp;
    private JButton flagButton;
    private JLabel mineCountLabel;
    private JLabel timerLabel;  // Label to display elapsed time
    private int mineCount;
    private javax.swing.Timer timer;
    private int elapsedSeconds = 0;
    private boolean flagMode = false;

    private final ActionListener actionListener = actionEvent -> {
        Object source = actionEvent.getSource();
        if (source == reset) {
            createMines();
        } else if (source == giveUp) {
            revealAllMines();
            revealBoardAndDisplay("You gave up.");
        } else if (source == flagButton) {
            flagMode = !flagMode;
            flagButton.setText(flagMode ? "Flag Mode: ON" : "Flag Mode: OFF");
        } else {
            handleCell((Cell) source);
        }
    };

    private class Cell extends JButton {
        private final int row;
        private final int col;
        private int value;
        private boolean flagged;

        Cell(final int row, final int col, final ActionListener actionListener) {
            this.row = row;
            this.col = col;
            addActionListener(actionListener);
            setText("");
            setFont(new Font("Arial", Font.BOLD, 20));
            setBackground(Color.LIGHT_GRAY);
            setOpaque(true);
            setBorder(BorderFactory.createLineBorder(Color.DARK_GRAY));
        }

        int getValue() {
            return value;
        }

        void setValue(int value) {
            this.value = value;
        }

        boolean isAMine() {
            return value == MINE;
        }

        boolean isFlagged() {
            return flagged;
        }

        void setFlagged(boolean flagged) {
            this.flagged = flagged;
            setText(flagged ? "F" : "");
            setForeground(Color.BLUE); // Color for flags
        }

        void reset() {
            setValue(0);
            setEnabled(true);
            setText("");
            setBackground(Color.LIGHT_GRAY);
            setForeground(Color.BLACK); // Default text color
            setFlagged(false);
        }

        void reveal() {
            if (flagged) return; // Don't reveal if flagged
            setEnabled(false);
            if (isAMine()) {
                setBackground(Color.RED);
                this.setForeground(Color.WHITE); // White text for mines
                setText("X");
            } else {
                setBackground(Color.WHITE);
                this.setForeground(getNumberColor(value)); // Set text color based on number
                setText(value == 0 ? "" : String.valueOf(value));
            }
        }

        void updateNeighbourCount() {
            getNeighbours(reusableStorage);
            int count = 0;
            for (Cell neighbour : reusableStorage) {
                if (neighbour == null) break;
                if (neighbour.isAMine()) count++;
            }
            setValue(count);
        }

        void getNeighbours(final Cell[] container) {
            Arrays.fill(container, null);
            int index = 0;
            for (int rowOffset = -1; rowOffset <= 1; rowOffset++) {
                for (int colOffset = -1; colOffset <= 1; colOffset++) {
                    if (rowOffset == 0 && colOffset == 0) continue;
                    int rowValue = row + rowOffset;
                    int colValue = col + colOffset;
                    if (rowValue >= 0 && rowValue < gridSize && colValue >= 0 && colValue < gridSize) {
                        container[index++] = cells[rowValue][colValue];
                    }
                }
            }
        }

        private Color getNumberColor(int value) {
            switch (value) {
                case 1: return Color.BLUE;
                case 2: return Color.GREEN;
                case 3: return Color.RED;
                case 4: return Color.MAGENTA;
                case 5: return Color.ORANGE;
                case 6: return Color.CYAN;
                case 7: return Color.BLACK;
                case 8: return Color.GRAY;
                default: return Color.BLACK;
            }
        }
    }




    private MineSweeper(final int gridSize) {
        this.gridSize = gridSize;
        cells = new Cell[gridSize][gridSize];
        frame = new JFrame("Minesweeper");
        frame.setSize(SIZE, SIZE);
        frame.setLayout(new BorderLayout());
        initializeButtonPanel();
        initializeGrid();
        frame.setLocationRelativeTo(null);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setVisible(true);
    }

    private void initializeButtonPanel() {
        JPanel buttonPanel = new JPanel();
        reset = new JButton("Reset");
        giveUp = new JButton("Give Up");
        flagButton = new JButton("Flag Mode: OFF");
        mineCountLabel = new JLabel("Mines Left: 0");
        timerLabel = new JLabel("Time: 0");  // Initialize timer label

        reset.addActionListener(actionListener);
        giveUp.addActionListener(actionListener);
        flagButton.addActionListener(actionListener);

        buttonPanel.add(reset);
        buttonPanel.add(giveUp);
        buttonPanel.add(flagButton);
        buttonPanel.add(mineCountLabel);
        buttonPanel.add(timerLabel);  // Add timer label to panel
        frame.add(buttonPanel, BorderLayout.SOUTH);
    }

    private void initializeGrid() {
        JPanel grid = new JPanel();
        grid.setLayout(new GridLayout(gridSize, gridSize));
        for (int row = 0; row < gridSize; row++) {
            for (int col = 0; col < gridSize; col++) {
                cells[row][col] = new Cell(row, col, actionListener);
                grid.add(cells[row][col]);
            }
        }
        createMines();
        frame.add(grid, BorderLayout.CENTER);
    }

    private void resetAllCells() {
        for (int row = 0; row < gridSize; row++) {
            for (int col = 0; col < gridSize; col++) {
                cells[row][col].reset();
            }
        }
    }

    private void createMines() {
        resetAllCells();
        mineCount = (int) (POPULATION_CONSTANT * gridSize);
        mineCountLabel.setText("Mines Left: " + mineCount);
        final Random random = new Random();
        Set<Integer> positions = new HashSet<>(gridSize * gridSize);
        for (int row = 0; row < gridSize; row++) {
            for (int col = 0; col < gridSize; col++) {
                positions.add(row * gridSize + col);
            }
        }
        for (int index = 0; index < mineCount; index++) {
            int choice = random.nextInt(positions.size());
            int row = choice / gridSize;
            int col = choice % gridSize;
            cells[row][col].setValue(MINE);
            positions.remove(choice);
        }
        for (int row = 0; row < gridSize; row++) {
            for (int col = 0; col < gridSize; col++) {
                if (!cells[row][col].isAMine()) {
                    cells[row][col].updateNeighbourCount();
                }
            }
        }
        startTimer();
    }

    private void startTimer() {
        if (timer != null) {
            timer.stop();
        }
        elapsedSeconds = 0;
        timer = new javax.swing.Timer(1000, e -> {
            elapsedSeconds++;
            timerLabel.setText("Time: " + elapsedSeconds);  // Update timer label
        });
        timer.start();
    }

    private void handleCell(Cell cell) {
        if (flagMode) {
            cell.setFlagged(!cell.isFlagged());
            mineCountLabel.setText("Mines Left: " + (mineCount - getFlaggedCount()));
            return;
        }

        if (cell.isAMine()) {
            cell.setForeground(Color.WHITE);
            cell.reveal();
            revealAllMines();
            revealBoardAndDisplay("You clicked on a mine!");
            return;
        }

        if (cell.getValue() == 0) {
            Set<Cell> positions = new HashSet<>();
            positions.add(cell);
            cascade(positions);
        } else {
            cell.reveal();
        }

        checkForWin();
    }

    private int getFlaggedCount() {
        int count = 0;
        for (int row = 0; row < gridSize; row++) {
            for (int col = 0; col < gridSize; col++) {
                if (cells[row][col].isFlagged()) {
                    count++;
                }
            }
        }
        return count;
    }

    private void revealAllMines() {
        for (int row = 0; row < gridSize; row++) {
            for (int col = 0; col < gridSize; col++) {
                Cell cell = cells[row][col];
                if (cell.isAMine() && !cell.isFlagged()) {
                    cell.setForeground(Color.RED);
                    cell.reveal();
                    cell.setBackground(Color.YELLOW);
                }
            }
        }
    }

    private void revealBoardAndDisplay(String message) {
        for (int row = 0; row < gridSize; row++) {
            for (int col = 0; col < gridSize; col++) {
                if (!cells[row][col].isEnabled()) {
                    cells[row][col].reveal();
                }
            }
        }

        JOptionPane.showMessageDialog(
                frame, message, "Game Over",
                JOptionPane.ERROR_MESSAGE
        );

        timer.stop();  // Stop the timer when the game ends
        createMines();
    }

    private void cascade(Set<Cell> positionsToClear) {
        while (!positionsToClear.isEmpty()) {
            Cell cell = positionsToClear.iterator().next();
            positionsToClear.remove(cell);
            cell.reveal();

            cell.getNeighbours(reusableStorage);
            for (Cell neighbour : reusableStorage) {
                if (neighbour == null) break;
                if (neighbour.getValue() == 0 && neighbour.isEnabled()) {
                    positionsToClear.add(neighbour);
                } else {
                    neighbour.reveal();
                }
            }
        }
    }

    private void checkForWin() {
        boolean won = true;
        outer:
        for (Cell[] cellRow : cells) {
            for (Cell cell : cellRow) {
                if (!cell.isAMine() && cell.isEnabled()) {
                    won = false;
                    break outer;
                }
            }
        }

        if (won) {
            JOptionPane.showMessageDialog(
                    frame, "You have won!", "Congratulations",
                    JOptionPane.INFORMATION_MESSAGE
            );
            timer.stop();  // Stop the timer when the player wins
        }
    }

    private static void run(final int gridSize) {
        try {
            UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
        } catch (Exception ignore) { }
        new MineSweeper(gridSize);
    }

    public static void main(String[] args) {
        final int gridSize = 10;
        SwingUtilities.invokeLater(() -> MineSweeper.run(gridSize));
    }
}
