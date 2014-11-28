# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'harmonizer.ui'
#
# Created: Thu Nov 27 07:57:37 2014
#      by: PyQt4 UI code generator 4.11.2
#
# WARNING! All changes made in this file will be lost!

from PyQt4 import QtCore, QtGui

try:
    _fromUtf8 = QtCore.QString.fromUtf8
except AttributeError:
    def _fromUtf8(s):
        return s

try:
    _encoding = QtGui.QApplication.UnicodeUTF8
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig, _encoding)
except AttributeError:
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig)

class Ui_widget_harmonizer(object):
    def setupUi(self, widget_harmonizer):
        widget_harmonizer.setObjectName(_fromUtf8("widget_harmonizer"))
        widget_harmonizer.resize(278, 145)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Expanding, QtGui.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(widget_harmonizer.sizePolicy().hasHeightForWidth())
        widget_harmonizer.setSizePolicy(sizePolicy)
        widget_harmonizer.setMaximumSize(QtCore.QSize(10000, 1000))
        self.verticalLayout = QtGui.QVBoxLayout(widget_harmonizer)
        self.verticalLayout.setObjectName(_fromUtf8("verticalLayout"))
        self.gridLayout = QtGui.QGridLayout()
        self.gridLayout.setObjectName(_fromUtf8("gridLayout"))
        self.dialHarmony = QtGui.QDial(widget_harmonizer)
        self.dialHarmony.setMaximum(10)
        self.dialHarmony.setPageStep(1)
        self.dialHarmony.setObjectName(_fromUtf8("dialHarmony"))
        self.gridLayout.addWidget(self.dialHarmony, 1, 1, 1, 1)
        self.dialKey = QtGui.QDial(widget_harmonizer)
        self.dialKey.setMaximum(11)
        self.dialKey.setPageStep(1)
        self.dialKey.setObjectName(_fromUtf8("dialKey"))
        self.gridLayout.addWidget(self.dialKey, 1, 2, 1, 1)
        self.dialMode = QtGui.QDial(widget_harmonizer)
        self.dialMode.setMaximum(4)
        self.dialMode.setPageStep(1)
        self.dialMode.setObjectName(_fromUtf8("dialMode"))
        self.gridLayout.addWidget(self.dialMode, 1, 3, 1, 1)
        self.dialVol = QtGui.QDial(widget_harmonizer)
        self.dialVol.setMaximum(100)
        self.dialVol.setObjectName(_fromUtf8("dialVol"))
        self.gridLayout.addWidget(self.dialVol, 1, 0, 1, 1)
        self.label_8 = QtGui.QLabel(widget_harmonizer)
        self.label_8.setAlignment(QtCore.Qt.AlignCenter)
        self.label_8.setObjectName(_fromUtf8("label_8"))
        self.gridLayout.addWidget(self.label_8, 2, 2, 1, 1)
        self.label_7 = QtGui.QLabel(widget_harmonizer)
        self.label_7.setAlignment(QtCore.Qt.AlignCenter)
        self.label_7.setObjectName(_fromUtf8("label_7"))
        self.gridLayout.addWidget(self.label_7, 2, 1, 1, 1)
        self.label_10 = QtGui.QLabel(widget_harmonizer)
        self.label_10.setAlignment(QtCore.Qt.AlignCenter)
        self.label_10.setObjectName(_fromUtf8("label_10"))
        self.gridLayout.addWidget(self.label_10, 2, 0, 1, 1)
        self.label_9 = QtGui.QLabel(widget_harmonizer)
        self.label_9.setAlignment(QtCore.Qt.AlignCenter)
        self.label_9.setObjectName(_fromUtf8("label_9"))
        self.gridLayout.addWidget(self.label_9, 2, 3, 1, 1)
        self.label_5 = QtGui.QLabel(widget_harmonizer)
        self.label_5.setAlignment(QtCore.Qt.AlignCenter)
        self.label_5.setObjectName(_fromUtf8("label_5"))
        self.gridLayout.addWidget(self.label_5, 0, 0, 1, 1)
        self.label_4 = QtGui.QLabel(widget_harmonizer)
        self.label_4.setAlignment(QtCore.Qt.AlignCenter)
        self.label_4.setObjectName(_fromUtf8("label_4"))
        self.gridLayout.addWidget(self.label_4, 0, 1, 1, 1)
        self.label_3 = QtGui.QLabel(widget_harmonizer)
        self.label_3.setAlignment(QtCore.Qt.AlignCenter)
        self.label_3.setObjectName(_fromUtf8("label_3"))
        self.gridLayout.addWidget(self.label_3, 0, 2, 1, 1)
        self.label_6 = QtGui.QLabel(widget_harmonizer)
        self.label_6.setAlignment(QtCore.Qt.AlignCenter)
        self.label_6.setObjectName(_fromUtf8("label_6"))
        self.gridLayout.addWidget(self.label_6, 0, 3, 1, 1)
        self.verticalLayout.addLayout(self.gridLayout)
        self.buttonToggle = QtGui.QPushButton(widget_harmonizer)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Minimum, QtGui.QSizePolicy.Minimum)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.buttonToggle.sizePolicy().hasHeightForWidth())
        self.buttonToggle.setSizePolicy(sizePolicy)
        self.buttonToggle.setObjectName(_fromUtf8("buttonToggle"))
        self.verticalLayout.addWidget(self.buttonToggle)
        self.verticalLayout.setStretch(1, 1)

        self.retranslateUi(widget_harmonizer)
        QtCore.QObject.connect(self.dialVol, QtCore.SIGNAL(_fromUtf8("valueChanged(int)")), self.label_10.setNum)
        QtCore.QObject.connect(self.dialHarmony, QtCore.SIGNAL(_fromUtf8("valueChanged(int)")), self.label_7.setNum)
        QtCore.QObject.connect(self.dialKey, QtCore.SIGNAL(_fromUtf8("valueChanged(int)")), self.label_8.setNum)
        QtCore.QObject.connect(self.dialMode, QtCore.SIGNAL(_fromUtf8("valueChanged(int)")), self.label_9.setNum)
        QtCore.QMetaObject.connectSlotsByName(widget_harmonizer)

    def retranslateUi(self, widget_harmonizer):
        widget_harmonizer.setWindowTitle(_translate("widget_harmonizer", "Form", None))
        self.label_8.setText(_translate("widget_harmonizer", "0", None))
        self.label_7.setText(_translate("widget_harmonizer", "0", None))
        self.label_10.setText(_translate("widget_harmonizer", "0", None))
        self.label_9.setText(_translate("widget_harmonizer", "0", None))
        self.label_5.setText(_translate("widget_harmonizer", "Volume", None))
        self.label_4.setText(_translate("widget_harmonizer", "Harmony/shift", None))
        self.label_3.setText(_translate("widget_harmonizer", "Key", None))
        self.label_6.setText(_translate("widget_harmonizer", "Mode", None))
        self.buttonToggle.setText(_translate("widget_harmonizer", "Toggle", None))

