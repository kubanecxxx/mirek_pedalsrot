# -*- mode: python -*-
a = Analysis(['main.py'],
             pathex=['.', 'c:\\pythons\\pedals'],
             hiddenimports=[],
             hookspath=None,
             runtime_hooks=None)
pyz = PYZ(a.pure)
exe = EXE(pyz,
          a.scripts,
          a.binaries,
          a.zipfiles,
          a.datas,
          name='gui_client_window.exe',
          debug=False,
          strip=None,
          upx=True,
          console=True )
