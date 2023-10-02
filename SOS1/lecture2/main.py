from PySide6.QtWidgets import *


class Window (QMainWindow):

    def __init__(self):
        super().__init__()
        button = QPushButton(self)
        button.setText("Button")
        self.setCentralWidget(button)


def main():
    app = QApplication()
    win = Window()
    win.show()
    exit(app.exec())


if __name__ == "__main__":
    main()
