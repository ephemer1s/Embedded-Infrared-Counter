import PyQt5.QtWidgets
from PyQt5.QtWidgets import (QWidget, QToolTip, 
    QPushButton, QApplication)
from PyQt5.QtGui import QFont
import sys


class Master(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()
    
    def initUI(self):
        self.setWindowTitle('WeiCOM-v0.0.1-alpha')
        self.setGeometry(560, 240, 800, 600)

        btn = QPushButton('Button', self) 
        btn.resize(btn.sizeHint())
        btn.move(50, 50)   
        self.show()


if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = Master()
    sys.exit(app.exec_())