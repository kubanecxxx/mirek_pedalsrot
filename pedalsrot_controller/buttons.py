'''
Created on 25. 11. 2014

@author: kubanec
'''


from PyQt4 import QtCore
from PyQt4 import QtGui


class buttons_widget(QtGui.QWidget):
    def __init__(self,parent = None):
        super(QtGui.QWidget,self).__init__(parent) 
        #create 8 + 1 buttons with property called "number"
        
        self._sizer = QtGui.QHBoxLayout(self)
        
        
        s = self._sizer
        
        for a in range(0,9):
            b = QtGui.QToolButton(self)
            b.setText(str(a + 1))
            b.setProperty("number", a)
            #b.setMaximumWidth(20)
            if a & 1:
                #b.setAutoRaise(True)
                #print b.autoRaise()
                #b.setArrowType(QtCore.Qt.RightArrow)
                pass
            s.addWidget(b)
            b.released.connect(self._button_rel_slot)
            b.pressed.connect(self._button_click_slot)
            
            if a == 8:
                b.setText("harmonizer")
                b.setProperty("number", 20)
            
            
    def _button_click_slot(self):
        num = self.sender().property("number").toInt()[0]
        self.emit(QtCore.SIGNAL("buttonClicked"),num,1)
        

    def _button_rel_slot(self):
        num = self.sender().property("number").toInt()[0]
        self.emit(QtCore.SIGNAL("buttonClicked"),num,0)
        
        
        