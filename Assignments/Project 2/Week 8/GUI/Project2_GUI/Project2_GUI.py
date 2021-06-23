import os
import sys
import matplotlib
matplotlib.use('Qt5Agg')
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg
from matplotlib.figure import Figure

from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtWidgets import QFileDialog
import sys
from PyQt5.QtWidgets import (QLabel, QRadioButton, QPushButton, QVBoxLayout, QApplication, QWidget)

sys.path.append(".")
from caller import Caller

class Ui_Project2_GUI(object):

        

    def setupUi(self, Project2_GUI):
        self.caller = Caller()
        

        Project2_GUI.setObjectName("Project2_GUI")
        Project2_GUI.setGeometry(100,100,600,400)

        self.button_ImportObjFile = QtWidgets.QPushButton(Project2_GUI)
        self.button_ImportObjFile.setGeometry(QtCore.QRect(10, 10, 80, 22))
        self.button_ImportObjFile.setObjectName("button_ImportObjFile")

        self.button_PerformSubdivision = QtWidgets.QPushButton(Project2_GUI)
        self.button_PerformSubdivision.setGeometry(QtCore.QRect(220, 220, 80, 22))
        self.button_PerformSubdivision.setObjectName("button_PerformSubdivision")

        self.label_ObjFileName = QtWidgets.QLabel(Project2_GUI)
        self.label_ObjFileName.setGeometry(QtCore.QRect(150, 15, 101, 16))
        self.label_ObjFileName.setObjectName("label_ObjFileName")

        self.spinBox_NumOfSubdivisions = QtWidgets.QSpinBox(Project2_GUI)
        self.spinBox_NumOfSubdivisions.setGeometry(QtCore.QRect(220, 120, 91, 22))
        self.spinBox_NumOfSubdivisions.setObjectName("spinBox_NumOfSubdivisions")

        self.comboBox_TypeOfSubdivision = QtWidgets.QComboBox(Project2_GUI)
        self.comboBox_TypeOfSubdivision.setGeometry(QtCore.QRect(220, 90, 91, 22))
        self.comboBox_TypeOfSubdivision.setObjectName("comboBox_TypeOfSubdivision")
        self.comboBox_TypeOfSubdivision.addItem("")
        self.comboBox_TypeOfSubdivision.addItem("")

        self.label_2 = QtWidgets.QLabel(Project2_GUI)
        self.label_2.setGeometry(QtCore.QRect(30, 120, 121, 16))
        self.label_2.setObjectName("label_2")
        self.label_3 = QtWidgets.QLabel(Project2_GUI)
        self.label_3.setGeometry(QtCore.QRect(30, 90, 101, 16))
        self.label_3.setObjectName("label_3")

        # Add 3D Viewer to application-window (Project_GUI)
        #self.view3d = QtWidgets.

        #scale
        self.button_PerformScale = QtWidgets.QPushButton(Project2_GUI)
        self.button_PerformScale.setGeometry(QtCore.QRect(620, 220, 80, 22))
        self.button_PerformScale.setObjectName("button_PerformScale")

        self.comboBox_TypeOfScale = QtWidgets.QComboBox(Project2_GUI)
        self.comboBox_TypeOfScale.setGeometry(QtCore.QRect(620, 90, 91, 22))
        self.comboBox_TypeOfScale.setObjectName("comboBox_TypeOfScale")
        self.comboBox_TypeOfScale.addItem("")
        self.comboBox_TypeOfScale.addItem("")
        self.comboBox_TypeOfScale.addItem("")
        self.comboBox_TypeOfScale.addItem("")

        self.label_4 = QtWidgets.QLabel(Project2_GUI)
        self.label_4.setGeometry(QtCore.QRect(430, 90, 101, 16))
        self.label_4.setObjectName("label_4")

        self.label_5 = QtWidgets.QLabel(Project2_GUI)
        self.label_5.setGeometry(QtCore.QRect(430, 120, 121, 16))
        self.label_5.setObjectName("label_5")

        self.spinBox_Scale = QtWidgets.QSpinBox(Project2_GUI)
        self.spinBox_Scale.setGeometry(QtCore.QRect(620, 120, 91, 22))
        self.spinBox_Scale.setObjectName("spinBox_Scale")
        self.spinBox_Scale.setMinimum(1)
        self.spinBox_Scale.setMaximum(1000)
        self.spinBox_Scale.setValue(100)
        

        

        self.retranslateUi(Project2_GUI)
        QtCore.QMetaObject.connectSlotsByName(Project2_GUI)

    def retranslateUi(self, Project2_GUI):
        _translate = QtCore.QCoreApplication.translate
        Project2_GUI.setWindowTitle(_translate("Project2_GUI", "Project2_GUI"))
        self.button_ImportObjFile.setText(_translate("Project2_GUI", "Import"))
        self.button_PerformSubdivision.setText(_translate("Project2_GUI", "Perform Subdivision"))
        self.label_ObjFileName.setText(_translate("Project2_GUI", "[No File Chosen]"))
        self.comboBox_TypeOfSubdivision.setItemText(0, _translate("Project2_GUI", "Linear"))
        self.comboBox_TypeOfSubdivision.setItemText(1, _translate("Project2_GUI", "Loop"))
        self.label_2.setText(_translate("Project2_GUI", "Number of Subdivisions:"))
        self.label_3.setText(_translate("Project2_GUI", "Subdivision Type:"))

        #scale
        self.button_PerformScale.setText(_translate("Project2_GUI", "Perform Scaling"))

        self.comboBox_TypeOfScale.setItemText(0, _translate("Project2_GUI", "all"))
        self.comboBox_TypeOfScale.setItemText(1, _translate("Project2_GUI", "x coordinates"))
        self.comboBox_TypeOfScale.setItemText(2, _translate("Project2_GUI", "y coordinates"))
        self.comboBox_TypeOfScale.setItemText(3, _translate("Project2_GUI", "z coordinates"))

        self.label_4.setText(_translate("Project2_GUI", "Scaling Type:"))
        self.label_5.setText(_translate("Project2_GUI", "Scaling in %: "))

        # autosize labels
        self.label_ObjFileName.adjustSize()
        self.label_2.adjustSize()
        self.label_3.adjustSize()
        self.button_ImportObjFile.adjustSize()
        self.button_ImportObjFile.clicked.connect(self.importObjFile)
        self.button_PerformSubdivision.adjustSize()

        self.button_PerformSubdivision.clicked.connect(self.subObject)

        #scale
        self.button_PerformScale.adjustSize()
        self.label_4.adjustSize()
        self.label_5.adjustSize()

        self.button_PerformScale.clicked.connect(self.scaleObject)

        

    def importObjFile(self):
        filename = self.openFileNameDialog()

    def openFileNameDialog(self):
        fileName = QFileDialog.getOpenFileName(self.button_ImportObjFile.parent(),"Import OBJ File", "","All Files (*);;Obj Files (*.obj)")
        
        # parse out file name
        fileName = os.path.basename(fileName[0])
        print(fileName)
        self.label_ObjFileName.setText(fileName)

        #self.caller.showObject()
        self.caller.updateObject()

    def scaleObject(self):
        axyz = self.comboBox_TypeOfScale.currentIndex()
        factor = self.spinBox_Scale.value()
        self.caller.scaleMesh(factor, axyz)
        self.caller.showObject()
        #self.caller.updateObject()

    def subObject(self):
        insertAlg = self.comboBox_TypeOfSubdivision.currentIndex()
        insertQuantity = self.spinBox_NumOfSubdivisions.value()
        self.caller.subMesh(insertAlg, insertQuantity)
        self.caller.showObject()
    


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    Project2_GUI = QtWidgets.QWidget()
    ui = Ui_Project2_GUI()
    ui.setupUi(Project2_GUI)
    Project2_GUI.showMaximized()
    sys.exit(app.exec_())
