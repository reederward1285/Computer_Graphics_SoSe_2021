__author__ = "David Melamend, Reeder Ward, Majbrit Schoettner"
__email__ = "dmelamed@stud.hs-bremen.de, rward@stud.hs-bremen.de, mshoettner@stud.hs-bremen.de"
__title__ = "Implement Toolchain for .OBJ Objects in PyQt5 GUI to Create a 3D Modelling Software"
__course__ = "Computer Graphics"

import os
from PyQt5 import QtCore, QtWidgets
from PyQt5.QtWidgets import QFileDialog
import sys


sys.path.append(".")
from modellingCaller import ModellingCaller

class Ui_Project2_GUI(QtWidgets.QMainWindow):

        

    def setupUi(self, Project2_GUI):
        """Show elements like buttons, spin boxes and combo boxes in a window
        Args: 
            Project2_GUI(QWidget): app
        """
        
        # window
        Project2_GUI.setObjectName("Project2_GUI")
        Project2_GUI.resize(1380, 960)

        # import
        self.button_ImportObjFile = QtWidgets.QPushButton(Project2_GUI)
        self.button_ImportObjFile.setGeometry(QtCore.QRect(30, 10, 80, 22))
        self.button_ImportObjFile.setObjectName("button_ImportObjFile")

        self.label_ObjFileName = QtWidgets.QLabel(Project2_GUI)
        self.label_ObjFileName.setGeometry(QtCore.QRect(150, 15, 101, 16))
        self.label_ObjFileName.setObjectName("label_ObjFileName")

        # export
        self.button_SaveObjFile = QtWidgets.QPushButton(Project2_GUI)
        self.button_SaveObjFile.setGeometry(QtCore.QRect(450, 10, 80, 22))
        self.button_SaveObjFile.setObjectName("button_SaveObjFile")

        # undo
        self.button_Undo = QtWidgets.QPushButton(Project2_GUI)
        self.button_Undo.setGeometry(QtCore.QRect(870, 10, 80, 22))
        self.button_Undo.setObjectName("button_Undo")
        self.button_Undo.setEnabled(False)

        # subdivision
        self.button_PerformSubdivision = QtWidgets.QPushButton(Project2_GUI)
        self.button_PerformSubdivision.setGeometry(QtCore.QRect(30, 220, 285, 25))
        self.button_PerformSubdivision.setObjectName("button_PerformSubdivision")
        self.button_PerformSubdivision.setEnabled(False)       

        self.spinBox_NumOfSubdivisions = QtWidgets.QSpinBox(Project2_GUI)
        self.spinBox_NumOfSubdivisions.setGeometry(QtCore.QRect(220, 120, 91, 22))
        self.spinBox_NumOfSubdivisions.setObjectName("spinBox_NumOfSubdivisions")
        self.spinBox_NumOfSubdivisions.setEnabled(False)

        self.comboBox_TypeOfSubdivision = QtWidgets.QComboBox(Project2_GUI)
        self.comboBox_TypeOfSubdivision.setGeometry(QtCore.QRect(220, 90, 91, 22))
        self.comboBox_TypeOfSubdivision.setObjectName("comboBox_TypeOfSubdivision")
        self.comboBox_TypeOfSubdivision.addItem("")
        self.comboBox_TypeOfSubdivision.addItem("")
        self.comboBox_TypeOfSubdivision.setEnabled(False)

        self.label_2 = QtWidgets.QLabel(Project2_GUI)
        self.label_2.setGeometry(QtCore.QRect(30, 120, 121, 16))
        self.label_2.setObjectName("label_2")
        self.label_3 = QtWidgets.QLabel(Project2_GUI)
        self.label_3.setGeometry(QtCore.QRect(30, 90, 101, 16))
        self.label_3.setObjectName("label_3")

        # scale
        self.button_PerformScale = QtWidgets.QPushButton(Project2_GUI)
        self.button_PerformScale.setGeometry(QtCore.QRect(450, 220, 285, 25))
        self.button_PerformScale.setObjectName("button_PerformScale")
        self.button_PerformScale.setEnabled(False)

        self.comboBox_TypeOfScale = QtWidgets.QComboBox(Project2_GUI)
        self.comboBox_TypeOfScale.setGeometry(QtCore.QRect(640, 90, 91, 22))
        self.comboBox_TypeOfScale.setObjectName("comboBox_TypeOfScale")
        self.comboBox_TypeOfScale.addItem("")
        self.comboBox_TypeOfScale.addItem("")
        self.comboBox_TypeOfScale.addItem("")
        self.comboBox_TypeOfScale.addItem("")
        self.comboBox_TypeOfScale.setEnabled(False)

        self.label_4 = QtWidgets.QLabel(Project2_GUI)
        self.label_4.setGeometry(QtCore.QRect(450, 90, 101, 16))
        self.label_4.setObjectName("label_4")

        self.label_5 = QtWidgets.QLabel(Project2_GUI)
        self.label_5.setGeometry(QtCore.QRect(450, 120, 121, 16))
        self.label_5.setObjectName("label_5")

        self.spinBox_Scale = QtWidgets.QSpinBox(Project2_GUI)
        self.spinBox_Scale.setGeometry(QtCore.QRect(640, 120, 91, 22))
        self.spinBox_Scale.setObjectName("spinBox_Scale")
        self.spinBox_Scale.setMinimum(1)
        self.spinBox_Scale.setMaximum(1000)
        self.spinBox_Scale.setValue(100)
        self.spinBox_Scale.setEnabled(False)

        # manipulate
        self.button_PerformMani = QtWidgets.QPushButton(Project2_GUI)
        self.button_PerformMani.setGeometry(QtCore.QRect(870, 220, 285, 25))
        self.button_PerformMani.setObjectName("button_PerformMani")
        self.button_PerformMani.setEnabled(False)
        
        self.comboBox_TypeOfMani = QtWidgets.QComboBox(Project2_GUI)
        self.comboBox_TypeOfMani.setGeometry(QtCore.QRect(1060, 90, 91, 22))
        self.comboBox_TypeOfMani.setObjectName("comboBox_TypeOfMani")
        self.comboBox_TypeOfMani.addItem("")
        self.comboBox_TypeOfMani.addItem("")
        self.comboBox_TypeOfMani.addItem("")
        self.comboBox_TypeOfMani.addItem("")
        self.comboBox_TypeOfMani.setEnabled(False)

        self.label_6 = QtWidgets.QLabel(Project2_GUI)
        self.label_6.setGeometry(QtCore.QRect(870, 90, 101, 16))
        self.label_6.setObjectName("label_6")

        self.label_7 = QtWidgets.QLabel(Project2_GUI)
        self.label_7.setGeometry(QtCore.QRect(870, 120, 121, 16))
        self.label_7.setObjectName("label_7")

        self.label_8 = QtWidgets.QLabel(Project2_GUI)
        self.label_8.setGeometry(QtCore.QRect(870, 150, 121, 16))
        self.label_8.setObjectName("label_8")

        self.spinBox_Pos = QtWidgets.QSpinBox(Project2_GUI)
        self.spinBox_Pos.setGeometry(QtCore.QRect(1060, 120, 91, 22))
        self.spinBox_Pos.setObjectName("spinBox_Pos")
        self.spinBox_Pos.setMinimum(1)
        self.spinBox_Pos.setMaximum(1000)
        self.spinBox_Pos.setValue(100)
        self.spinBox_Pos.setEnabled(False)

        self.spinBox_Point = QtWidgets.QSpinBox(Project2_GUI)
        self.spinBox_Point.setGeometry(QtCore.QRect(1060, 150, 91, 22))
        self.spinBox_Point.setObjectName("spinBox_Point")
        self.spinBox_Point.setMinimum(-1)
        self.spinBox_Point.setMaximum(-1)
        self.spinBox_Point.setValue(-1)
        self.spinBox_Point.setEnabled(False)

        # modellCaller
        self.mcaller = ModellingCaller(Project2_GUI)
        self.mcaller.move(10, 30)
        self.mcaller.setGeometry(QtCore.QRect(10, 300, 1360, 650))


        self.retranslateUi(Project2_GUI)
        QtCore.QMetaObject.connectSlotsByName(Project2_GUI)

    def retranslateUi(self, Project2_GUI):
        """Retranslate elements in the gui. Buttons will have the right size and the text is set.
        Args: 
            Project2_GUI(QWidget): app
        """

        _translate = QtCore.QCoreApplication.translate
        Project2_GUI.setWindowTitle(_translate("Project2_GUI", "Project2_GUI"))

        # import
        self.button_ImportObjFile.setText(_translate("Project2_GUI", "Import"))
        self.label_ObjFileName.setText(_translate("Project2_GUI", "[No File Chosen]"))

        # export
        self.button_SaveObjFile.setText(_translate("Project2_GUI", "Save"))

        # undo
        self.button_Undo.setText(_translate("Project2_GUI", "Undo"))

        # subdivision
        self.button_PerformSubdivision.setText(_translate("Project2_GUI", "Perform Subdivision"))
        
        self.comboBox_TypeOfSubdivision.setItemText(0, _translate("Project2_GUI", "Linear"))
        self.comboBox_TypeOfSubdivision.setItemText(1, _translate("Project2_GUI", "Loop"))

        self.label_2.setText(_translate("Project2_GUI", "Number of Subdivisions:"))
        self.label_3.setText(_translate("Project2_GUI", "Subdivision Type:"))

        # scale
        self.button_PerformScale.setText(_translate("Project2_GUI", "Perform Scaling"))

        self.comboBox_TypeOfScale.setItemText(0, _translate("Project2_GUI", "all"))
        self.comboBox_TypeOfScale.setItemText(1, _translate("Project2_GUI", "x coordinates"))
        self.comboBox_TypeOfScale.setItemText(2, _translate("Project2_GUI", "y coordinates"))
        self.comboBox_TypeOfScale.setItemText(3, _translate("Project2_GUI", "z coordinates"))

        self.label_4.setText(_translate("Project2_GUI", "Scaling Type:"))
        self.label_5.setText(_translate("Project2_GUI", "Scaling in %: "))

        # manipulate
        self.button_PerformMani.setText(_translate("Project2_GUI", "Perform Manipulation"))

        self.comboBox_TypeOfMani.setItemText(0, _translate("Project2_GUI", "all"))
        self.comboBox_TypeOfMani.setItemText(1, _translate("Project2_GUI", "x coordinate"))
        self.comboBox_TypeOfMani.setItemText(2, _translate("Project2_GUI", "y coordinate"))
        self.comboBox_TypeOfMani.setItemText(3, _translate("Project2_GUI", "z coordinate"))

        self.label_6.setText(_translate("Project2_GUI", "Manipulation Type:"))
        self.label_7.setText(_translate("Project2_GUI", "Manipulation in %: "))
        self.label_8.setText(_translate("Project2_GUI", "Point: "))


        # ---autosize labels---
        # import
        self.button_ImportObjFile.adjustSize()
        self.button_ImportObjFile.clicked.connect(self.importObjFile)
        self.label_ObjFileName.adjustSize()

        # export
        self.button_SaveObjFile.adjustSize()
        self.button_SaveObjFile.clicked.connect(self.saveFileDialog)

        # undo
        self.button_Undo.adjustSize()
       

        # subdivision
        self.label_2.adjustSize()
        self.label_3.adjustSize()
        
        #self.button_PerformSubdivision.adjustSize()
        self.button_PerformSubdivision.clicked.connect(self.subObject)

        # scale
        #self.button_PerformScale.adjustSize()
        self.label_4.adjustSize()
        self.label_5.adjustSize()

        self.button_PerformScale.clicked.connect(self.scaleObject)

        # manipulate
        #self.button_PerformMani.adjustSize()
        self.label_6.adjustSize()
        self.label_7.adjustSize()
        self.label_8.adjustSize()

        self.button_PerformMani.clicked.connect(self.maniPoint)

        # undo
        self.button_Undo.clicked.connect(self.undoStep)

    def importObjFile(self):
        """Import an obj. file into the gui
        """
        
        filename = self.openFileNameDialog()
        self.mcaller.ReadBlend(str(filename))

        self.mcaller.showObject()
        # self.mcaller.showObject()
        # self.mcaller.updateObject()

        # activate elements to deform the object
        self.button_PerformSubdivision.setEnabled(True)
        self.button_PerformScale.setEnabled(True)
        self.button_PerformMani.setEnabled(True)
        self.comboBox_TypeOfMani.setEnabled(True)
        self.comboBox_TypeOfScale.setEnabled(True)
        self.comboBox_TypeOfSubdivision.setEnabled(True)
        self.spinBox_NumOfSubdivisions.setEnabled(True)
        self.spinBox_Point.setEnabled(True)
        self.spinBox_Pos.setEnabled(True)
        self.spinBox_Scale.setEnabled(True)
        self.spinBox_Point.setMinimum(0)
        self.spinBox_Point.setMaximum(len(self.mcaller.mesh.pts)-1)
        self.spinBox_Point.setValue(0)
        self.button_ImportObjFile.setEnabled(False)


    def openFileNameDialog(self):
        """Open Dialog to import an .obj file
        """
        fileName = QFileDialog.getOpenFileName(self.button_ImportObjFile.parent(),"Import OBJ File", "","OBJ Files (*.obj);;All Files (*)")
        
        self.mcaller.createMesh()
        # parse out file name
        filePath = fileName[0]
        fileName = os.path.basename(fileName[0])
        print(fileName)
        self.label_ObjFileName.setText(fileName)
        return filePath

    def saveFileDialog(self):
        """Open Dialog to save .obj file
        """
        name = QFileDialog.getSaveFileName(self, 'Save File')
        
        # gather text info to put into the file
        text = self.mcaller.exportToOBJ()

        # abort if nothing to save
        if (text != ""):
            # write obj file information into the file
            file = open(name[0] + ".obj", 'w')
            file.write(text)
            file.close()

    #scale object (all, x, y or z)
    def scaleObject(self):
        """Scale the object
        """
        axyz = self.comboBox_TypeOfScale.currentIndex()
        factor = self.spinBox_Scale.value()
        self.mcaller.scaleMesh(factor, axyz)
        self.mcaller.showObject()

        self.button_Undo.setEnabled(True)

    # subdivide object
    def subObject(self):
        """subdivide the object
        """
        insertAlg = self.comboBox_TypeOfSubdivision.currentIndex()
        insertQuantity = self.spinBox_NumOfSubdivisions.value()
        self.mcaller.subMesh(insertAlg, insertQuantity)
        self.mcaller.showObject()

        self.spinBox_Point.setMinimum(0)
        self.spinBox_Point.setMaximum(len(self.mcaller.mesh.pts)-1)
        self.spinBox_Point.setValue(0)

        self.button_Undo.setEnabled(True)
    
    # manipulate one point
    def maniPoint(self):
        """Manipulate the object
        """
        axyz = self.comboBox_TypeOfMani.currentIndex()
        factor = self.spinBox_Pos.value()
        point = self.spinBox_Point.value()
        self.mcaller.maniMesh(axyz, factor, point)
        self.mcaller.showObject()

        self.button_Undo.setEnabled(True)

    def undoStep(self):
        """Undo last step
        """
        self.mcaller.undoStep()
        self.mcaller.showObject()
        self.button_Undo.setEnabled(False)


# main
if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    Project2_GUI = QtWidgets.QWidget()
    ui = Ui_Project2_GUI()
    ui.setupUi(Project2_GUI)
    Project2_GUI.show()
    sys.exit(app.exec_())
