import java.awt.EventQueue;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import javax.swing.JButton;
import javax.swing.JFormattedTextField;
import javax.swing.JLabel;

public class SudokuController {

    JLabel leftLabel, rightLabel;
    JFormattedTextField[][] leftSudoku, rightSudoku;
    JButton goButton, clearButton;
    SudokuHelper sudokuHelper; // Reference to the SudokuHelper class

    public SudokuController() {
        leftSudoku = new JFormattedTextField[9][9]; // standard sudoku size
        rightSudoku = new JFormattedTextField[9][9];
        sudokuHelper = new SudokuHelper(); // Initialize SudokuHelper
    }

    void bindLeftLabel(JLabel label) {
        leftLabel = label;
    }

    void bindRightLabel(JLabel label) {
        rightLabel = label;
    }

    void bindLeftSudokuCell(final int row, final int column, JFormattedTextField field) {
        field.addPropertyChangeListener("value", new PropertyChangeListener() {
            public void propertyChange(PropertyChangeEvent evt) {
                String newValue = (String) evt.getNewValue();
                if (newValue != null && !newValue.trim().isEmpty()) {
                    try {
                        int value = Integer.valueOf(newValue.trim());
                        userEditedValueAt(row, column, value);
                    } catch (NumberFormatException ex) {
                        // Handle invalid input gracefully (log it, ignore it, etc.)
                        System.err.println("Invalid input at row " + row + ", column " + column + ": " + newValue);
                    }
                } else {
                    // Handle clearing of the cell or empty input here if needed
                    System.out.println("Cell at row " + row + ", column " + column + " was cleared.");
                }
            }
        });
        leftSudoku[row][column] = field;
    }

    void userEditedValueAt(int row, int column, int value) {
        System.out.println("Value changed at row:" + row + ", column:" + column + " to " + value);
        // Store value in SudokuHelper for potential future use
        sudokuHelper.addValue(row + "," + column, value);
    }

    void bindRightSudokuCell(int row, int column, JFormattedTextField field) {
        rightSudoku[row][column] = field;
    }

    void bindCenterButton(JButton goButton) {
        this.goButton = goButton;
        goButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                goButtonPressed();
            }
        });
    }

    void bindClearButton(JButton clearButton) {
        this.clearButton = clearButton;
        clearButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                clearLeftSudoku();
            }
        });
    }

    private void goButtonPressed() {
        if (listener != null) {
            if (backGroundThread == null || (backGroundThread != null && !backGroundThread.isAlive())) {
                backGroundThread = new Thread() {
                    @Override
                    public void run() {
                        listener.goButtonPressed(getLeftValues(), SudokuController.this);
                    }
                };
                backGroundThread.start();
            }
        }
    }

    private Integer[][] getLeftValues() {
        Integer[][] values = new Integer[9][9];
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (!leftSudoku[i][j].getText().trim().isEmpty()) {
                    values[i][j] = Integer.valueOf(leftSudoku[i][j].getText().trim());
                }
            }
        }
        return values;
    }

    private void clearLeftSudoku() {
        EventQueue.invokeLater(new Runnable() {
            public void run() {
                for (int i = 0; i < 9; i++) {
                    for (int j = 0; j < 9; j++) {
                        leftSudoku[i][j].setValue(""); // Ensure that the field is cleared properly
                        sudokuHelper.removeValue(i + "," + j); // Also clear values from SudokuHelper
                    }
                }
            }
        });
    }

    SudokuImplementation listener;

    public void setListener(SudokuImplementation listener) {
        this.listener = listener;
    }

    Thread backGroundThread;

    public void setSudokuResult(final Integer[][] result) {
        EventQueue.invokeLater(new Runnable() {
            public void run() {
                // Ensure we are updating the GUI on the Event Dispatch Thread
                for (int i = 0; i < 9; i++) {
                    for (int j = 0; j < 9; j++) {
                        // Check if result[i][j] is null before setting the value
                        if (result[i][j] != null) {
                            rightSudoku[i][j].setValue(String.valueOf(result[i][j]));
                        } else {
                            rightSudoku[i][j].setValue(""); // Clear cell if no result
                        }
                    }
                }
            }
        });
    }

    public void setSudokuTime(final String time) {
        EventQueue.invokeLater(new Runnable() {
            public void run() {
                leftLabel.setText("<html>Running time: <b>" + time);
            }
        });
    }

    public void setSudokuCompleted(final boolean completed) {
        EventQueue.invokeLater(new Runnable() {
            public void run() {
                rightLabel.setText("<html>Completely Solved: <b>" + completed);
            }
        });
    }

    public JFormattedTextField[][] getLeftSudoku() {
        return leftSudoku;
    }
}
