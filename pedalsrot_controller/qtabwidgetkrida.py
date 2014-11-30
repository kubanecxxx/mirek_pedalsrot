__author__ = 'kuba'

from PyQt4 import QtGui
from PyQt4 import QtCore
from qplaintexteditkrida import QPlainTextEditKrida

class QTabWidgetKrida(QtGui.QTabWidget):
    def __init__(self,parent = None):
        super(QtGui.QTabWidget,self).__init__(parent)
        self.currentChanged.connect(self._tab_changed)
        self.tabCloseRequested.connect(self._close_tab)

    def new_tab(self,filepath = None):
        #if tab with the file exists
        cnt = self.count()

        for a in range(0,cnt):
            w = self.widget(a)
            fn = w._fn
            if fn and fn.fileName() == filepath:
                self.setCurrentWidget(w)
                return w

        editor = QPlainTextEditKrida(self)
        editor.load_file(filepath)
        #editor.fileChanged.connect(self._editor_changed)
        self.connect(editor,QtCore.SIGNAL("fileChanged"),self._editor_changed)
        self.currentChanged.connect(self._tab_changed)

        self.addTab(editor,editor.just_name)
        self.setCurrentWidget(editor)
        editor.setFocus()
        editor.setTabStopWidth(20)

        return editor

    def _close_tab(self,a):
        self.removeTab(a)

    def _editor_changed(self,changed):
        idx = self.currentIndex()
        editor = self.currentWidget()
        print idx
        print editor.just_name
        self.setTabText(idx,editor.just_name)

        self.emit(QtCore.SIGNAL("tabSwitched"),editor.name)
        #emit signal tabchanged with new title with or without star

    def _tab_changed(self):
        #emit signal tabchanged with new title wit or without star
        editor = self.currentWidget()
        name = "None"
        if editor:
            name = editor.name
        self.emit(QtCore.SIGNAL("tabSwitched"),name)
        pass

    def save_tab(self,name = None):
        return self.currentWidget().save_file(name)

    def editor(self):
        editor = self.currentWidget()
        return editor

    def plainText(self):
        return self.editor().toPlainText()

    def editor_filenames(self):
        cnt = self.count()
        lst = []
        for a in range(0,cnt):
            w = self.widget(a)
            fn = w._fn
            if fn:
                lst.append(fn.fileName())

        return lst
