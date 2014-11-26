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
          name='hyper-super.exe',
          debug=False,
          strip=None,
          upx=True,
          console=False )
