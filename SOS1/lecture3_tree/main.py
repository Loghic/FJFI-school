import sys
from PySide6.QtCore import *
from PySide6.QtGui import *
from PySide6.QtWidgets import *


class Window(QMainWindow):

    def __init__(self):
        super().__init__()

        self.widget = QWidget(self)

        self.layout = QVBoxLayout(self.widget)

        self.setCentralWidget(self.widget)

        self.tree = QTreeWidget(self)
        # self.tree.header().setVisible (False)
        self.layout.addWidget(self.tree)

        self.button = QPushButton(self)
        self.button.setText("Add Items")
        self.button.clicked.connect(self.onClick)

        self.layout.addWidget(self.button)

        # first type of font, second how big it is
        # self.setFont(QFont ("", 20)) #this fond is for everything
        # also possible to combine font of everything with specific things.
        self.tree.setFont(QFont("", 20))  # just for tree

    def onClick(self):
        myItem = QTreeWidgetItem(self.tree)

        # we put branch into the tree, the top level
        branch = QTreeWidgetItem(myItem)
        # if you don't write self.tree there
        # you have to do it manually like this: self.tree.addTopLevelItem(branch)
        # after making changes

        myItem.setText(0,"Tree head:)")
        myItem.setForeground(0, QColor("lime")) # Foreground is color of the text
        myItem.setBackground(0, QColor("saddlebrown"))

        branch.setText(0, "abc")
        branch.setForeground(0, QColor("brown"))
        branch.setExpanded(True)

        colors = ["red", "blue", "green", "yellow", "orange", "aqua", "plum"]
        for name in colors:
            #  we put some item into the branch, under tree then under branch
            item = QTreeWidgetItem(branch)
            item.setText(0, name + " item")
            item.setForeground(0, QColor(name))
            item.setExpanded(True)
            for i in range(12):
                node = QTreeWidgetItem(item)
                node.setText(0, "tree list " + str(i + 1))
                node.setForeground(0, QColor.fromHsv(i*30, 200, 150))


if __name__ == "__main__":
    app = QApplication(sys.argv)
    win = Window()
    win.show()
    win.raise_()
    sys.exit(app.exec())
