# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'form.ui'
##
## Created by: Qt User Interface Compiler version 6.1.0
##
## WARNING! All changes made in this file will be lost when recompiling UI file!
################################################################################

from PySide6.QtCore import *
from PySide6.QtGui import *
from PySide6.QtWidgets import *


class Ui_Project2_GUI(object):
    def setupUi(self, Project2_GUI):
        if not Project2_GUI.objectName():
            Project2_GUI.setObjectName(u"Project2_GUI")
        Project2_GUI.resize(467, 299)
        self.button_ImportObjFile = QPushButton(Project2_GUI)
        self.button_ImportObjFile.setObjectName(u"button_ImportObjFile")
        self.button_ImportObjFile.setGeometry(QRect(10, 10, 80, 22))
        self.label_ObjFileName = QLabel(Project2_GUI)
        self.label_ObjFileName.setObjectName(u"label_ObjFileName")
        self.label_ObjFileName.setGeometry(QRect(100, 10, 101, 16))
        self.spinBox_NumOfSubdivisions = QSpinBox(Project2_GUI)
        self.spinBox_NumOfSubdivisions.setObjectName(u"spinBox_NumOfSubdivisions")
        self.spinBox_NumOfSubdivisions.setGeometry(QRect(160, 90, 91, 22))
        self.comboBox_TypeOfSubdivision = QComboBox(Project2_GUI)
        self.comboBox_TypeOfSubdivision.addItem("")
        self.comboBox_TypeOfSubdivision.addItem("")
        self.comboBox_TypeOfSubdivision.setObjectName(u"comboBox_TypeOfSubdivision")
        self.comboBox_TypeOfSubdivision.setGeometry(QRect(160, 60, 91, 22))
        self.label_2 = QLabel(Project2_GUI)
        self.label_2.setObjectName(u"label_2")
        self.label_2.setGeometry(QRect(30, 90, 121, 16))
        self.label_3 = QLabel(Project2_GUI)
        self.label_3.setObjectName(u"label_3")
        self.label_3.setGeometry(QRect(30, 60, 101, 16))

        self.retranslateUi(Project2_GUI)

        QMetaObject.connectSlotsByName(Project2_GUI)
    # setupUi

    def retranslateUi(self, Project2_GUI):
        Project2_GUI.setWindowTitle(QCoreApplication.translate("Project2_GUI", u"Project2_GUI", None))
        self.button_ImportObjFile.setText(QCoreApplication.translate("Project2_GUI", u"Import", None))
        self.label_ObjFileName.setText(QCoreApplication.translate("Project2_GUI", u"[No File Chosen]", None))
        self.comboBox_TypeOfSubdivision.setItemText(0, QCoreApplication.translate("Project2_GUI", u"Linear", None))
        self.comboBox_TypeOfSubdivision.setItemText(1, QCoreApplication.translate("Project2_GUI", u"Loop", None))

        self.label_2.setText(QCoreApplication.translate("Project2_GUI", u"Number of Subdivisions:", None))
        self.label_3.setText(QCoreApplication.translate("Project2_GUI", u"Subdivision Type:", None))
    # retranslateUi

