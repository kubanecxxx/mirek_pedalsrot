__author__ = 'kuba'


from PyQt4 import QtGui
from PyQt4 import QtCore



class QPlainTextEditKrida(QtGui.QPlainTextEdit):
    def __init__(self,parent=None):
        super(QtGui.QPlainTextEdit,self).__init__(parent)
        self._fn = None
        self._fileChanged = False
        self._changed_prev = False

        file_Changed = QtCore.pyqtSignal(bool,name="fileChanged")
        self.name = "NoName"
        self._title = self.name

        self.textChanged.connect(self._text_changed)

    def load_file(self,filepath):
        if filepath:
            try:
                fn = QtCore.QFile(filepath)
                fn.open(QtCore.QFile.ReadOnly)
                st = fn.readAll()
                fn.close()
                self._fn = fn
                self.setPlainText(QtCore.QString( st))
                self._title = fn.fileName()
            except:
                return False
        else:
            self._fn = None
            self._title = "NoName"

        self._show_star(False)
        return True

    def save_file(self,filepath = None):
        if filepath:
            self._fn = QtCore.QFile(filepath)
        try:
            fn = self._fn
            fn.open(QtCore.QFile.WriteOnly)
            fn.writeData(self.toPlainText())
            fn.close()
            self._fn = fn
            self._title = fn.fileName()
            self._show_star(False)
        except:
            return False
        return True

    def _text_changed(self):
        self._show_star(True)
        pass

    def _show_star(self, show):
        tmp = self._title
        self._fileChanged = show
        self.name = self._title
        if show:
            self.name += "*"

        self.emit(QtCore.SIGNAL("fileChanged"),self._fileChanged)


