__author__ = 'kuba'



from PyQt4 import QtGui
from PyQt4 import QtCore
import harmonizer

class harm_widget(QtGui.QWidget):
    def __init__(self,parent=None):
        super(QtGui.QWidget,self).__init__(parent)
        self._ui = harmonizer.Ui_widget_harmonizer()
        self._ui.setupUi(self)
        self._ui.dialHarmony.valueChanged.connect(self._dial)
        self._ui.dialHarmony.setProperty("num",3)
        self._ui.dialKey.valueChanged.connect(self._dial)
        self._ui.dialKey.setProperty("num", 2)
        self._ui.dialMode.valueChanged.connect(self._dial)
        self._ui.dialMode.setProperty("num", 1)
        self._ui.dialVol.valueChanged.connect(self._dial)
        self._ui.dialVol.setProperty("num", 4)
        self._ui.buttonToggle.setProperty("num", 0)
        self._ui.buttonToggle.clicked.connect(self._dial)
        
    def _dial(self,num):
        n =  self.sender().property("num").toInt()[0]
        if n == 0:
            num = 2
    
            
        lst = [-1,-1,-1,-1,-1]
        lst[n] = num
        st = "harm_configure(%d,%d,%d,%d,%d)" % (lst[0],lst[1],lst[2],lst[3],lst[4])
        self.emit(QtCore.SIGNAL("changed"),st)
