import os, sys, time
from PySide6.QtCore import *
from PySide6.QtGui import *
from PySide6.QtWidgets import *

class Window (QMainWindow) :

    def __init__ (self) :
        super().__init__ ()

        self.splitter = QSplitter (self)
        self.setCentralWidget (self.splitter)

        self.tree = QTreeWidget (self)
        # self.tree.header().setVisible (False)
        self.tree.setHeaderLabels (["name", "size", "date"])

        node = QTreeWidgetItem (self.tree)
        node.setText (0, "root")
        node.setBackground (0, QColor ("yellow").lighter())
        node.setForeground (0, QColor ("brown"))

        node2 = QTreeWidgetItem (node)
        node2.setText (0, "branch")
        node2.setForeground (0, QColor ("brown"))

        for i in [1, 2, 3] :
           node3 = QTreeWidgetItem (node2)
           node3.setText (0, "list " + str (i))
           node3.setForeground (0, QColor ("lime"))

        self.tree.expandAll ()

        self.tree.itemDoubleClicked.connect (self.onClick)

        self.tabs = QTabWidget (self)

        self.splitter.addWidget (self.tree)
        self.splitter.addWidget (self.tabs)

    def onClick (self, node, column) :
        #node.setForeground (0, QColor ("lime"))
        path = node.toolTip (0)
        if os.path.isfile (path) :

           # f = open (path)
           # lines = f.readlines()
           # f.close ()

           with open (path) as f :
              lines = f.readlines()

           text = ""
           for line in lines :
              text = text + line

           edit = QTextEdit (self)
           edit.setPlainText (text)

           above_name, local_name = os.path.split (path)
           self.tabs.addTab (edit, local_name)

           cnt = self.tabs.count ()
           self.tabs.setTabToolTip (cnt-1, path)


    def showSubDir (self, top, path) :
        # import os
        items = os.listdir (path)
        items.sort ()
        for name in items :
            node = QTreeWidgetItem (top)
            node.setText (0, name)
            file_name = os.path.join (path, name)
            node.setToolTip (0, file_name)
            if os.path.isdir (file_name) :
               node.setForeground (0, QColor ("blue"))
               self.showSubDir (node, file_name)
            else :
               node.setForeground (0, QColor ("red"))
               node.setText (1, str (os.path.getsize (file_name)))
               t = os.path.getmtime (file_name)
               u = time.gmtime (t)
               s = time.strftime("%d-%m-%Y %H:%M:%S", u)
               node.setText (2, s)

    def showDir (self, path) :
        self.tree.clear ()

        path = os.path.abspath (path)
        above_name, local_name = os.path.split (path)
        top = QTreeWidgetItem (self.tree)
        top.setText (0, local_name)
        top.setToolTip (0, path)
        top.setForeground (0, QColor ("blue"))

        self.showSubDir (top, path)


def main():
    app = QApplication (sys.argv)
    win = Window ()
    win.show ()
    win.showDir ("..")
    sys.exit (app.exec())


if __name__ == "__main__":
    main()
