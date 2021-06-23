import sys
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *

class window(QWidget):
   def __init__(self, parent = None):
      super(window, self).__init__(parent)
      self.setWindowTitle("PyQt5")

      self.label = QLabel(self)
      self.label.setText("Hello World")

      font = QFont()
      font.setFamily("Arial")
      font.setPointSize(16)

      self.label.setFont(font)
      self.label.move(5,500) # x, y

def main():
   app = QApplication(sys.argv)
   ex = window()
   ex.showMaximized()
   sys.exit(app.exec_())

if __name__ == '__main__':
   main()