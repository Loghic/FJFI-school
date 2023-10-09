import sys
from PySide6.QtWidgets import *


class Window(QMainWindow):

    def __init__(self):
        super().__init__()
        self.button = QPushButton(self)
        self.button.setText("Knoflik")

        # self.button.clicked.connect(lambda: self.onClick()) these 2 work same for our case
        # self.button.clicked.connect(self.onClick)

        self.button.pressed.connect(self.onPress)
        self.button.released.connect(self.onRelease)

        self.setCentralWidget(self.button)

    def onClick(self):
        self.button.setText("Click!")

    def onPress(self):
        self.button.setText("Pressed")

    def onRelease(self):
        self.button.setText("Released")


def main():
    app = QApplication()
    win = Window()
    win.show()
    sys.exit(app.exec())


if __name__ == "__main__":
    main()
