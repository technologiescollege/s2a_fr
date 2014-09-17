@echo off
break ON
cls
echo Preparation pour s2a_fm
echo.
echo Cette installation va installer le langage Python dans C:\python27,
echo puis les complements pyserial et normalement PyMata.
echo.
echo Il ne vous restera plus qu'a programmer votre carte Arduino
echo avec le sketch FirmataPlus.
echo.
echo Appuyez sur une touche quand vous etes pret, sinon appuyez sur Ctrl+C.
echo.
pause
msiexec /i 1-python-2.7.8.msi TARGETDIR=c:\python27 ALLUSERS=1 /passive
set PATH=%PATH%;c:\python27
cd 2.pyserial-2.7
python setup.py install
cd..
cd 3.PyMata-1.58
python setup.py install
cd ..
echo.
echo Normalement tout s'est bien passe....
pause