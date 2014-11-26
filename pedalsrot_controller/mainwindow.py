# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'mainwindow.ui'
#
# Created: Wed Nov 26 19:20:09 2014
#      by: PyQt4 UI code generator 4.11.3
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

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName(_fromUtf8("MainWindow"))
        MainWindow.resize(800, 600)
        self.centralwidget = QtGui.QWidget(MainWindow)
        self.centralwidget.setObjectName(_fromUtf8("centralwidget"))
        self.horizontalLayout = QtGui.QHBoxLayout(self.centralwidget)
        self.horizontalLayout.setObjectName(_fromUtf8("horizontalLayout"))
        self.groupBox = QtGui.QGroupBox(self.centralwidget)
        self.groupBox.setObjectName(_fromUtf8("groupBox"))
        self.verticalLayout = QtGui.QVBoxLayout(self.groupBox)
        self.verticalLayout.setObjectName(_fromUtf8("verticalLayout"))
        self.editor = QtGui.QPlainTextEdit(self.groupBox)
        self.editor.setDocumentTitle(_fromUtf8(""))
        self.editor.setTabStopWidth(20)
        self.editor.setObjectName(_fromUtf8("editor"))
        self.verticalLayout.addWidget(self.editor)
        self.horizontalLayout.addWidget(self.groupBox)
        MainWindow.setCentralWidget(self.centralwidget)
        self.statusbar = QtGui.QStatusBar(MainWindow)
        self.statusbar.setObjectName(_fromUtf8("statusbar"))
        MainWindow.setStatusBar(self.statusbar)
        self.toolBar = QtGui.QToolBar(MainWindow)
        self.toolBar.setMovable(False)
        self.toolBar.setIconSize(QtCore.QSize(48, 48))
        self.toolBar.setToolButtonStyle(QtCore.Qt.ToolButtonIconOnly)
        self.toolBar.setFloatable(False)
        self.toolBar.setObjectName(_fromUtf8("toolBar"))
        MainWindow.addToolBar(QtCore.Qt.TopToolBarArea, self.toolBar)
        self.BoardButtons = QtGui.QDockWidget(MainWindow)
        self.BoardButtons.setObjectName(_fromUtf8("BoardButtons"))
        self.SizerButtons = QtGui.QWidget()
        self.SizerButtons.setObjectName(_fromUtf8("SizerButtons"))
        self.horizontalLayout_2 = QtGui.QHBoxLayout(self.SizerButtons)
        self.horizontalLayout_2.setObjectName(_fromUtf8("horizontalLayout_2"))
        self.BoardButtons.setWidget(self.SizerButtons)
        MainWindow.addDockWidget(QtCore.Qt.DockWidgetArea(1), self.BoardButtons)
        self.dockWidget_2 = QtGui.QDockWidget(MainWindow)
        self.dockWidget_2.setObjectName(_fromUtf8("dockWidget_2"))
        self.dockWidgetContents_4 = QtGui.QWidget()
        self.dockWidgetContents_4.setObjectName(_fromUtf8("dockWidgetContents_4"))
        self.verticalLayout_4 = QtGui.QVBoxLayout(self.dockWidgetContents_4)
        self.verticalLayout_4.setObjectName(_fromUtf8("verticalLayout_4"))
        self.terminal = QtGui.QPlainTextEdit(self.dockWidgetContents_4)
        self.terminal.setReadOnly(True)
        self.terminal.setTabStopWidth(20)
        self.terminal.setObjectName(_fromUtf8("terminal"))
        self.verticalLayout_4.addWidget(self.terminal)
        self.horizontalLayout_3 = QtGui.QHBoxLayout()
        self.horizontalLayout_3.setObjectName(_fromUtf8("horizontalLayout_3"))
        self.butClear = QtGui.QPushButton(self.dockWidgetContents_4)
        self.butClear.setObjectName(_fromUtf8("butClear"))
        self.horizontalLayout_3.addWidget(self.butClear)
        self.buttonEnd = QtGui.QPushButton(self.dockWidgetContents_4)
        self.buttonEnd.setObjectName(_fromUtf8("buttonEnd"))
        self.horizontalLayout_3.addWidget(self.buttonEnd)
        self.verticalLayout_4.addLayout(self.horizontalLayout_3)
        self.inputTerminal = QtGui.QLineEdit(self.dockWidgetContents_4)
        self.inputTerminal.setObjectName(_fromUtf8("inputTerminal"))
        self.verticalLayout_4.addWidget(self.inputTerminal)
        self.dockWidget_2.setWidget(self.dockWidgetContents_4)
        MainWindow.addDockWidget(QtCore.Qt.DockWidgetArea(1), self.dockWidget_2)
        self.dockWidget_5 = QtGui.QDockWidget(MainWindow)
        self.dockWidget_5.setObjectName(_fromUtf8("dockWidget_5"))
        self.dockWidgetContents_6 = QtGui.QWidget()
        self.dockWidgetContents_6.setObjectName(_fromUtf8("dockWidgetContents_6"))
        self.formLayout = QtGui.QFormLayout(self.dockWidgetContents_6)
        self.formLayout.setObjectName(_fromUtf8("formLayout"))
        self.comboPort = QtGui.QComboBox(self.dockWidgetContents_6)
        self.comboPort.setObjectName(_fromUtf8("comboPort"))
        self.formLayout.setWidget(0, QtGui.QFormLayout.FieldRole, self.comboPort)
        self.label = QtGui.QLabel(self.dockWidgetContents_6)
        self.label.setObjectName(_fromUtf8("label"))
        self.formLayout.setWidget(0, QtGui.QFormLayout.LabelRole, self.label)
        self.dockWidget_5.setWidget(self.dockWidgetContents_6)
        MainWindow.addDockWidget(QtCore.Qt.DockWidgetArea(1), self.dockWidget_5)
        self.actionSave_File = QtGui.QAction(MainWindow)
        icon = QtGui.QIcon()
        icon.addPixmap(QtGui.QPixmap(_fromUtf8(":/icons/Actions-document-save-icon.png")), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.actionSave_File.setIcon(icon)
        self.actionSave_File.setObjectName(_fromUtf8("actionSave_File"))
        self.actionNew_File = QtGui.QAction(MainWindow)
        icon1 = QtGui.QIcon()
        icon1.addPixmap(QtGui.QPixmap(_fromUtf8(":/icons/Actions-document-new-icon.png")), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.actionNew_File.setIcon(icon1)
        self.actionNew_File.setObjectName(_fromUtf8("actionNew_File"))
        self.actionSave_As = QtGui.QAction(MainWindow)
        icon2 = QtGui.QIcon()
        icon2.addPixmap(QtGui.QPixmap(_fromUtf8(":/icons/Actions-document-save-as-icon.png")), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.actionSave_As.setIcon(icon2)
        self.actionSave_As.setObjectName(_fromUtf8("actionSave_As"))
        self.actionOpen_file = QtGui.QAction(MainWindow)
        icon3 = QtGui.QIcon()
        icon3.addPixmap(QtGui.QPixmap(_fromUtf8(":/icons/Actions-document-open-icon.png")), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.actionOpen_file.setIcon(icon3)
        self.actionOpen_file.setObjectName(_fromUtf8("actionOpen_file"))
        self.actionConnect = QtGui.QAction(MainWindow)
        self.actionConnect.setCheckable(True)
        icon4 = QtGui.QIcon()
        icon4.addPixmap(QtGui.QPixmap(_fromUtf8(":/icons/Actions-network-connect-icon.png")), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.actionConnect.setIcon(icon4)
        self.actionConnect.setObjectName(_fromUtf8("actionConnect"))
        self.actionDownload = QtGui.QAction(MainWindow)
        icon5 = QtGui.QIcon()
        icon5.addPixmap(QtGui.QPixmap(_fromUtf8(":/icons/Button-Download-icon.png")), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.actionDownload.setIcon(icon5)
        self.actionDownload.setObjectName(_fromUtf8("actionDownload"))
        self.actionGet_ROM = QtGui.QAction(MainWindow)
        icon6 = QtGui.QIcon()
        icon6.addPixmap(QtGui.QPixmap(_fromUtf8(":/icons/Folders-Uploads-Folder-icon.png")), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.actionGet_ROM.setIcon(icon6)
        self.actionGet_ROM.setObjectName(_fromUtf8("actionGet_ROM"))
        self.actionGet_RAM = QtGui.QAction(MainWindow)
        icon7 = QtGui.QIcon()
        icon7.addPixmap(QtGui.QPixmap(_fromUtf8(":/icons/Button-Upload-icon.png")), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.actionGet_RAM.setIcon(icon7)
        self.actionGet_RAM.setObjectName(_fromUtf8("actionGet_RAM"))
        self.actionSave_RAM_to_ROM = QtGui.QAction(MainWindow)
        icon8 = QtGui.QIcon()
        icon8.addPixmap(QtGui.QPixmap(_fromUtf8(":/icons/CD-Burn-icon.png")), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.actionSave_RAM_to_ROM.setIcon(icon8)
        self.actionSave_RAM_to_ROM.setObjectName(_fromUtf8("actionSave_RAM_to_ROM"))
        self.actionUse_RAM = QtGui.QAction(MainWindow)
        self.actionUse_RAM.setCheckable(True)
        icon9 = QtGui.QIcon()
        icon9.addPixmap(QtGui.QPixmap(_fromUtf8(":/icons/Drives-RAM-Metro-icon.png")), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.actionUse_RAM.setIcon(icon9)
        self.actionUse_RAM.setObjectName(_fromUtf8("actionUse_RAM"))
        self.actionUse_ROM = QtGui.QAction(MainWindow)
        self.actionUse_ROM.setCheckable(True)
        icon10 = QtGui.QIcon()
        icon10.addPixmap(QtGui.QPixmap(_fromUtf8(":/icons/rom-manager-2-icon.png")), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.actionUse_ROM.setIcon(icon10)
        self.actionUse_ROM.setObjectName(_fromUtf8("actionUse_ROM"))
        self.actionDebug = QtGui.QAction(MainWindow)
        self.actionDebug.setCheckable(True)
        icon11 = QtGui.QIcon()
        icon11.addPixmap(QtGui.QPixmap(_fromUtf8(":/icons/Bug-icon.png")), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.actionDebug.setIcon(icon11)
        self.actionDebug.setObjectName(_fromUtf8("actionDebug"))
        self.toolBar.addAction(self.actionNew_File)
        self.toolBar.addAction(self.actionOpen_file)
        self.toolBar.addAction(self.actionSave_File)
        self.toolBar.addAction(self.actionSave_As)
        self.toolBar.addSeparator()
        self.toolBar.addAction(self.actionConnect)
        self.toolBar.addSeparator()
        self.toolBar.addAction(self.actionDownload)
        self.toolBar.addAction(self.actionGet_RAM)
        self.toolBar.addAction(self.actionGet_ROM)
        self.toolBar.addAction(self.actionSave_RAM_to_ROM)
        self.toolBar.addSeparator()
        self.toolBar.addAction(self.actionUse_RAM)
        self.toolBar.addAction(self.actionUse_ROM)
        self.toolBar.addSeparator()
        self.toolBar.addAction(self.actionDebug)

        self.retranslateUi(MainWindow)
        QtCore.QObject.connect(self.butClear, QtCore.SIGNAL(_fromUtf8("clicked()")), self.terminal.clear)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow", None))
        self.groupBox.setTitle(_translate("MainWindow", "Editor", None))
        self.toolBar.setWindowTitle(_translate("MainWindow", "toolBar", None))
        self.BoardButtons.setWindowTitle(_translate("MainWindow", "Board buttons", None))
        self.dockWidget_2.setWindowTitle(_translate("MainWindow", "Terminal", None))
        self.butClear.setText(_translate("MainWindow", "Clear", None))
        self.buttonEnd.setText(_translate("MainWindow", "End", None))
        self.inputTerminal.setPlaceholderText(_translate("MainWindow", "Input", None))
        self.dockWidget_5.setWindowTitle(_translate("MainWindow", "Connection", None))
        self.label.setText(_translate("MainWindow", "Port:", None))
        self.actionSave_File.setText(_translate("MainWindow", "Save File", None))
        self.actionSave_File.setShortcut(_translate("MainWindow", "Ctrl+S", None))
        self.actionNew_File.setText(_translate("MainWindow", "New File", None))
        self.actionNew_File.setShortcut(_translate("MainWindow", "Ctrl+N", None))
        self.actionSave_As.setText(_translate("MainWindow", "Save As", None))
        self.actionOpen_file.setText(_translate("MainWindow", "Open file", None))
        self.actionOpen_file.setShortcut(_translate("MainWindow", "Ctrl+O", None))
        self.actionConnect.setText(_translate("MainWindow", "Connect", None))
        self.actionConnect.setShortcut(_translate("MainWindow", "Alt+C", None))
        self.actionDownload.setText(_translate("MainWindow", "Download", None))
        self.actionDownload.setShortcut(_translate("MainWindow", "Ctrl+D", None))
        self.actionGet_ROM.setText(_translate("MainWindow", "Get ROM", None))
        self.actionGet_RAM.setText(_translate("MainWindow", "Get RAM", None))
        self.actionSave_RAM_to_ROM.setText(_translate("MainWindow", "Save RAM to ROM", None))
        self.actionUse_RAM.setText(_translate("MainWindow", "Use RAM", None))
        self.actionUse_ROM.setText(_translate("MainWindow", "Use ROM", None))
        self.actionDebug.setText(_translate("MainWindow", "Debug", None))
        self.actionDebug.setToolTip(_translate("MainWindow", "Debug", None))
        self.actionDebug.setShortcut(_translate("MainWindow", "Ctrl+Shift+D", None))

import resources_rc
