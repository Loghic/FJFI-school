import sys
import os

from PySide6.QtWidgets import *

# app = QApplication ([""])
# win = QPushButton ()

# win.setText ("Konflik")
# win.show()

# app.exec_()


app = QApplication ([])

win = QTextEdit ()
win.setText ("Text")
win.append ("dalsi text")
win.append ("jiny text")
for i in range (10):
    win.append(str(i))


win.show()

app.exec_()
