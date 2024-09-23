import java.awt.*;
import javax.swing.*;
import javax.swing.text.*;
import javax.swing.border.*;

public class SudokuView extends JFrame {

    // Controller to manage the Sudoku interaction
    SudokuController controller;

    public void setSudokuImplementation(SudokuImplementation listener) {
        // Set the listener for Sudoku operations
        controller.setListener(listener);
    }

    public SudokuView() {
        controller = new SudokuController();
        setTitle("Sudoku Solver");
        getContentPane().add(createCenterPanel(), BorderLayout.CENTER);
        getContentPane().add(createBottomPanel(), BorderLayout.SOUTH);
        setMinimumSize(new Dimension(600, 300));
        pack();
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        // Set initial values on the left board
        setInitialLeftValues(new Integer[][]{
                {5, 3, null, null, 7, null, null, null, null},
                {6, null, null, 1, 9, 5, null, null, null},
                {null, 9, 8, null, null, null, null, 6, null},
                {8, null, null, null, 6, null, null, null, 3},
                {4, null, null, 8, null, 3, null, null, 1},
                {7, null, null, null, 2, null, null, null, 6},
                {null, 6, null, null, null, null, 2, 8, null},
                {null, null, null, 4, 1, 9, null, null, 5},
                {null, null, null, null, 8, null, null, 7, 9}
        });
    }

    // Initialize the left Sudoku grid with values
    public void setInitialLeftValues(Integer[][] values) {
        JFormattedTextField[][] leftSudoku = controller.getLeftSudoku();
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (values[i][j] != null) {
                    leftSudoku[i][j].setValue(String.valueOf(values[i][j]));
                } else {
                    leftSudoku[i][j].setValue(""); // Empty if null
                }
            }
        }
    }

    // Create the bottom panel with labels for the Sudoku grids
    private JPanel createBottomPanel() {
        JPanel bottomPanel = new JPanel(new GridBagLayout());
        JLabel leftLabel = createLabel("Left Sudoku");
        JLabel rightLabel = createLabel("Right Sudoku");

        controller.bindLeftLabel(leftLabel);
        controller.bindRightLabel(rightLabel);

        bottomPanel.add(leftLabel, getWholeCellConstraints());
        bottomPanel.add(new JSeparator(JSeparator.VERTICAL));
        bottomPanel.add(rightLabel, getWholeCellConstraints());

        bottomPanel.setBorder(new BevelBorder(BevelBorder.LOWERED));
        return bottomPanel;
    }

    // Create a centered label with given text
    private JLabel createLabel(String text) {
        JLabel label = new JLabel(text);
        label.setHorizontalAlignment(JLabel.CENTER);
        return label;
    }

    // Create the center panel with Sudoku grids and buttons
    private JPanel createCenterPanel() {
        JPanel centerPanel = new JPanel(new GridBagLayout());
        centerPanel.add(createLeftPanel(), getWholeCellConstraints());
        centerPanel.add(createCenterButtonPanel(), getPreferredSizeConstraint());
        centerPanel.add(createRightPanel(), getWholeCellConstraints());
        return centerPanel;
    }

    // Constraints for preferred size
    private GridBagConstraints getPreferredSizeConstraint() {
        return new GridBagConstraints();
    }

    // Create the panel with solve and clear buttons
    private JPanel createCenterButtonPanel() {
        JPanel panel = new JPanel(new GridLayout(2, 1, 5, 5));
        JButton goButton = new JButton("Solve >");
        JButton clearButton = new JButton("Clear");

        controller.bindCenterButton(goButton);
        controller.bindClearButton(clearButton);

        panel.add(goButton);
        panel.add(clearButton);
        return panel;
    }

    private static final Insets sixPixelInset = new Insets(6, 6, 6, 6);

    // Create the right panel (non-editable Sudoku grid)
    private JPanel createRightPanel() {
        JPanel rightPanel = create3x3Panel(6);
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                JPanel panel2 = create3x3Panel(2);
                fillPanelWithNonEditable(panel2, i, j);
                rightPanel.add(panel2);
            }
        }
        rightPanel.setBorder(new EmptyBorder(sixPixelInset));
        return rightPanel;
    }

    // Create the left panel (editable Sudoku grid)
    private JPanel createLeftPanel() {
        JPanel leftPanel = create3x3Panel(6);
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                JPanel panel2 = create3x3Panel(2);
                fillPanelWithEditable(panel2, i, j);
                leftPanel.add(panel2);
            }
        }
        leftPanel.setBorder(new EmptyBorder(sixPixelInset));
        return leftPanel;
    }

    // Constraints for a whole cell in the GridBagLayout
    private GridBagConstraints getWholeCellConstraints() {
        GridBagConstraints wholePanelCnstr = getPreferredSizeConstraint();
        wholePanelCnstr.fill = GridBagConstraints.BOTH;
        wholePanelCnstr.weightx = 1.0;
        wholePanelCnstr.weighty = 1.0;
        return wholePanelCnstr;
    }

    // Fill a panel with editable fields
    private void fillPanelWithEditable(JPanel panel, int majorRow, int majorColumn) {
        for (int minorRow = 0; minorRow < 3; minorRow++) {
            for (int minorColumn = 0; minorColumn < 3; minorColumn++) {
                final JFormattedTextField editableField = createEditableField();
                int column = majorColumn * 3 + minorColumn;
                int row = majorRow * 3 + minorRow;
                controller.bindLeftSudokuCell(row, column, editableField);
                panel.add(editableField);
            }
        }
    }

    // Fill a panel with non-editable fields
    private void fillPanelWithNonEditable(JPanel panel, int majorRow, int majorColumn) {
        for (int minorRow = 0; minorRow < 3; minorRow++) {
            for (int minorColumn = 0; minorColumn < 3; minorColumn++) {
                final JFormattedTextField nonEditableField = createNonEditableField();
                int column = majorColumn * 3 + minorColumn;
                int row = majorRow * 3 + minorRow;
                controller.bindRightSudokuCell(row, column, nonEditableField);
                panel.add(nonEditableField);
            }
        }
    }

    // Create a 3x3 panel with specified gap between cells
    private JPanel create3x3Panel(int gap) {
        final GridLayout gridLayout = new GridLayout(3, 3, 1, 1);
        gridLayout.setHgap(gap);
        gridLayout.setVgap(gap);
        JPanel panel = new JPanel(gridLayout);
        return panel;
    }

    // Create a non-editable formatted text field
    private JFormattedTextField createNonEditableField() {
        JFormattedTextField field = createEditableField();
        field.setEditable(false);
        field.setBackground(Color.WHITE); // Otherwise non-editable gets gray
        return field;
    }

    // Create an editable formatted text field with a number formatter
    private JFormattedTextField createEditableField() {
        JFormattedTextField field = new JFormattedTextField();
        try {
            field.setFormatterFactory(new DefaultFormatterFactory(new MaskFormatter("#")));
        } catch (java.text.ParseException ex) {
            ex.printStackTrace();
        }
        field.setPreferredSize(new Dimension(16, 30));
        field.setHorizontalAlignment(JTextField.CENTER);
        field.setText(" "); // Set to space initially
        field.setBorder(null);
        return field;
    }
}
