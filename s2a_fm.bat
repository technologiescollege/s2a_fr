@echo off
break ON
cls
echo Vous devez indiquer le numero de port de la carte Arduino :
echo dans le gestionnaire de peripheriques, quel port COM lui est attribue ?
echo Si cette fenêtre se ferme, c'est qu'il ne s'agit pas du bon port...
echo.
echo Vous devez avoir installe Python dans C:\python27.
echo.
echo IMPORTANT : ce fichier doit etre execute depuis le dossier de s2a_fm,
echo la ou se trouve le fichier s2a_fm.py
echo Vous pouvez par contre en creer un raccourci pour etre execute depuis le bureau.
echo.
echo.
rem set /p port=Indiquer le port COM sur lequel est connecte votre interface Arduino (COM1, COM2, etc - voir le Gestionnaire de peripheriques) :
c:\python2\python s2a_fm.py COM3