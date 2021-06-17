from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_Project2_GUI(object):
    def setupUi(self, Project2_GUI):
        Project2_GUI.setObjectName("Project2_GUI")
        Project2_GUI.resize(390, 280)
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

        # autosize labels
        self.label_ObjFileName.adjustSize()
        self.label_2.adjustSize()
        self.label_3.adjustSize()
        self.button_ImportObjFile.adjustSize()
        self.button_PerformSubdivision.adjustSize()


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    Project2_GUI = QtWidgets.QWidget()
    ui = Ui_Project2_GUI()
    ui.setupUi(Project2_GUI)
    Project2_GUI.show()
    sys.exit(app.exec_())
