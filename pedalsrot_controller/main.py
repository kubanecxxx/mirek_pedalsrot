import PyQt4
__author__ = 'kuba'


import sys
import mainwindow
from PyQt4 import QtGui
from PyQt4 import QtCore
import serial.tools.list_ports

import buttons
import time
import harm

class main_window(QtGui.QMainWindow):
    def __init__(self):
        super(QtGui.QMainWindow, self).__init__(None)
        self._ui = mainwindow.Ui_MainWindow()
        self._ui.setupUi(self)
        
        self._ui.toolBar.setToolTip("Version 0.8\n26.11.2014")

        self._ui.actionOpen_file.triggered.connect(self._file_open_slot)
        self._ui.actionSave_File.triggered.connect(self._file_save_slot)
        self._ui.actionSave_As.triggered.connect(self._file_save_as_slot)
        self._ui.actionNew_File.triggered.connect(self._file_new_file)
        self._ui.editor.textChanged.connect(self._editor_changed)
        self._fn = None
        self._path = "/home/kubanec/bdsa"
        self._title = "NoName"
        self._window_name = "Hyper-super"
        self._fileChanged = False
        self._show_start(False)
        self._com = None
        
        # buttons widget
        self._buttons = buttons.buttons_widget(self)
        self._ui.BoardButtons.setWidget(self._buttons)
        # self._buttons.buttonClicked.connect(self._board_button)
        self.connect(self._buttons, QtCore.SIGNAL("buttonClicked"), self._board_button)
        
        # scan serial ports
        self._scan_serial_ports()
        
        self._tmr = QtCore.QTimer()
        self._tmr.timeout.connect(self._timer_slot)
        self._tmr.setInterval(100)
        
        
        self._ui.inputTerminal.returnPressed.connect(self._input_terminal)
        self._ui.inputTerminal.setFocus()
        
        self._ui.actionGet_RAM.triggered.connect(self._get_ramrom)
        self._ui.actionGet_RAM.setProperty("read", "read_ram();")
        self._ui.actionGet_ROM.triggered.connect(self._get_ramrom)
        self._ui.actionGet_ROM.setProperty("read", "read_flash();")
        
        self._ui.actionUse_RAM.triggered.connect(self._use_ramrom)
        self._ui.actionUse_RAM.setProperty("use", "use_ram();")
        self._ui.actionUse_ROM.triggered.connect(self._use_ramrom)
        self._ui.actionUse_ROM.setProperty("use", "use_flash();")
        
        self._actions = [self._ui.actionUse_ROM,self._ui.actionUse_RAM]
        self._ui.actionDownload.triggered.connect(self._download)
        self._ui.buttonEnd.clicked.connect(self._end)
        self._moje = self.moje()
        
        self._ui.actionDebug.triggered.connect(self._debug)
        self._ui.actionSave_RAM_to_ROM.triggered.connect(self._ramtorom)
        
        self._dock = QtGui.QDockWidget(self)
        h = harm.harm_widget(self)
        self._dock.setWidget(h)
        self.addDockWidget(1, self._dock)
        self._dock.setWindowTitle(self.tr("Harmonizer"))
        self.connect(h,QtCore.SIGNAL("changed"),self._harmonizer_changed)
        
        self._dock.close()
        
        self._settings = QtCore.QSettings("hyper.ini")
        name = self._settings.value("main/last").toString()
        port = self._settings.value("main/com").toString()
        geom = self._settings.value("main/geometry").toByteArray()
        self.restoreGeometry(geom)
        
        
        self._ui.actionConnect.triggered.connect(self._connect_port)
            
        lst = []
        for a in range(0,4):
            s = QtGui.QAction(self)
            lst.append(s)
            s.setSeparator(True)
            
        u = self._ui
        lst = [self._ui.actionNew_File, u.actionOpen_file,u.actionSave_File,u.actionSave_As,lst[0],
               u.actionConnect, lst[1], u.actionDownload,u.actionGet_RAM,u.actionGet_ROM,u.actionSave_RAM_to_ROM,
               lst[2], u.actionUse_RAM,u.actionUse_ROM,lst[3],u.actionDebug]
        self._ui.groupBox.addActions(lst)
        self._ui.groupBox.setContextMenuPolicy(QtCore.Qt.ActionsContextMenu)
        
        try:
            idx = self._ui.comboPort.findText(port)
            self._ui.comboPort.setCurrentIndex(idx)
            self._load_file(name)
            self._connect_port(True)
           
        except:
            
            pass
        
    def closeEvent(self, *args, **kwargs):
        self._settings.setValue("main/geometry",self.saveGeometry())
        return QtGui.QMainWindow.closeEvent(self, *args, **kwargs)
        
    def __del__(self):
        try:
            self._settings.setValue("main/last",self._title)
            self._settings.setValue("main/com",self._ui.comboPort.currentText())            
            self._com.close()
            print "Closing com port"
        except:
            pass
        
    class moje():
        def __init__(self):
            self.button = 0
            self.button_old = 0
            self.ms = 0
            self.ms_old = 0
            self.state = 0
            self.state_old = 0
    
    def _enable_widget(self,enable):
        self._ui.comboPort.setDisabled(enable)
        self._ui.actionDebug.setEnabled(enable)
        self._ui.actionDownload.setEnabled(enable)
        self._ui.actionUse_RAM.setEnabled(enable)
        self._ui.actionUse_ROM.setEnabled(enable)
        self._ui.actionGet_RAM.setEnabled(enable)
        self._ui.actionGet_ROM.setEnabled(enable)
        self._ui.actionSave_RAM_to_ROM.setEnabled(enable)
        self._ui.BoardButtons.setEnabled(enable)
        self._ui.inputTerminal.setEnabled(enable)
        self._ui.buttonEnd.setEnabled(enable)
        self._dock.setEnabled(enable)
        
    def _harmonizer_changed(self,string):
        try:
            self._com.write(string + ";\r\n")
        except:
            pass
    
    def _connect_port(self,connect):        
        if connect:
            try:
                name = self._ui.comboPort.currentText()
                self._com = serial.Serial(str(name),115200,rtscts=True,timeout = 1)
                self._ui.actionConnect.setChecked(True)
                self._enable_widget(True)
                self._tmr.start()
            except:
                self._ui.actionConnect.setChecked(False)
                self._enable_widget(False)
                self._ui.statusbar.showMessage(self.tr("Cannot open serial port"))
                self._tmr.stop()
                pass
        else:
            try:
                self._com.close()
                self._ui.actionConnect.setChecked(False)
                self._enable_widget(False)
                self._tmr.stop()
            except:
                pass
        
    def _ramtorom(self):
        try:
            self._com.write("ram_to_rom();")
        except:
            pass
        
    def _debug(self,checked):
        n = 0
        if checked:
            n = 1
        st = "debug(%d);" % n 
        try:
            self._com.write(st + "\r\n")
        except:
            pass
        
    def _end(self):
        try:
            self._com.write("\x03")
        except:
            pass
        
    def _download(self):
        try:
        #send secret function
            self._com.write("super_secret_function();\r\n" )
        #wait
            time.sleep(0.1)
        #send file
            st = self._ui.editor.toPlainText()
            self._com.write(str(st))
        #wait
            time.sleep(0.1)
        #send ctrl+c or ctrl+z
            self._end()
        except:
            pass
        
    def _use_ramrom(self):
        text =  self.sender().property("use").toString()
        idx = self._actions.index(self.sender())
        self.sender().setChecked(True)
        self._actions[idx ^1].setChecked(False)
        try:
            self._com.write(str(text) + "\r\n")
        except:
            pass
    
    def _get_ramrom(self):
        text =  self.sender().property("read").toString()
        try:
            self._com.write(str(text) + "\r\n")
        except:
            pass
    
    def _input_terminal(self):    
        try:
            text = (self._ui.inputTerminal.text())
            self._com.write(str(text) + '\r\n')
            self._ui.terminal.appendPlainText(text)
            self._ui.inputTerminal.clear()
        except:
            pass
    
    def _timer_slot(self):
        try:
            st = None
            while self._com.inWaiting():
                if not st:
                    st = self._com.read()
                st += self._com.read()
                
            self._ui.terminal.appendPlainText(st)
                
                
        except:
            pass
        
    def _scan_serial_ports(self):
        st = serial.tools.list_ports.comports()
        self._ui.comboPort.clear()
        
        lst = []
        for a in st:
            lst.append(a[0])
        
        self._ui.comboPort.addItems(lst)
        pass
        
    def _board_button(self, num, state):
        # print "%d %d" % (num,state)
        # create stimulate parameters and send to serial port
        
        m = self._moje
        m.state_old = m.state
        m.button_old = m.button
        m.state = state
        m.button = num
        m.ms = ( time.time() - m.ms_old )*1000 
        
        st = "stimulate(%d,%d,%d,%d,%d);" % (m.button, m.state, m.button_old, m.state_old,m.ms)
        m.ms_old = time.time() 
        
        try:
            self._com.write(st + "\r\n")
        except:  
            pass
        
    def _file_new_file(self):
        self._title = "NoName"
        self._fn = None
        self._ui.editor.clear()
        self._show_start(False)
        
    def _load_file(self,name):
        if len(name):
            fn = QtCore.QFile(name)
            self._fn = fn
            fn.open(QtCore.QFile.ReadOnly)
            st = fn.readAll()
            fn.close()
            self._ui.editor.clear()
            self._ui.editor.appendPlainText(QtCore.QString(st))
            self._title = name
            self._show_start(False)

    def _file_open_slot(self):
        # QtGui.QDialog.
        rewrite = False
        if self._fileChanged:
            # @todo msg do you really wanna rewrite...
            pass
        else:
            rewrite = True
        
        if rewrite:
            name = QtGui.QFileDialog.getOpenFileNameAndFilter(self, self.tr("Open File"), self._path, "C files (*.c)")
            name = name[0]
            if len(name):
                self._load_file(name)
    
    def _file_save_as_slot(self):
        name = QtGui.QFileDialog.getSaveFileNameAndFilter(self, self.tr("Save File"), self._path, "C files (*.c)")
        name = name[0]
        if len(name):
            if not name.endsWith(".c"):
                name.append(".c")
            
            self._fn = QtCore.QFile(name)
            self._save()
        pass
            
    def _file_save_slot(self):
        if not self._fn:
            self._file_save_as_slot()
        else:
            self._save()
        
        pass
    
    def _save(self):
        if not self._fn:
            return
        
        self._fn.open(QtCore.QFile.WriteOnly)
        self._fn.writeData(self._ui.editor.toPlainText())
        self._fn.close()
        self._title = self._fn.fileName()
        self._show_start(False)
    
    def _show_start(self, show):
        tmp = self._window_name + " - " + self._title
        self._fileChanged = show
        if show:
            tmp += "*"
            
        self.setWindowTitle(tmp)
    
    def _editor_changed(self):
        self._show_start(True)


app = QtGui.QApplication(sys.argv)
mw = main_window()
mw.show()
app.exec_()
