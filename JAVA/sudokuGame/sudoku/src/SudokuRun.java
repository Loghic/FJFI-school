import java.awt.EventQueue;
import javax.swing.UIManager;

public class SudokuRun implements Runnable {

    // Main entry point for running the application
    public void run() {
        SudokuImplementation sudokuImplementation = new SudokuSolver();
        SudokuView sudokuView = new SudokuView();
        sudokuView.setSudokuImplementation(sudokuImplementation);
        sudokuView.setVisible(true);
    }

    // Entry point of the application
    public static void main(String[] args) {
        tryToSetSystemLookAndFeel();
        EventQueue.invokeLater(new SudokuRun());
    }

    // Attempt to set the system's look and feel for the application
    private static void tryToSetSystemLookAndFeel() {
        try {
            UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
        } catch (Exception ex) {
            System.out.println("Couldn't set LAF");
        }
    }
}
