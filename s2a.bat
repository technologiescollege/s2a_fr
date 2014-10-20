@echo off
break ON
rem fichiers BAT et fork cr? par S?stien CANET
cls
echo.
echo 		s2a : la communication Arduino -=- Scratch2 facile !
echo.
echo Vous devez juste indiquer le port de communication de la carte Arduino :
echo dans le gestionnaire de p‚riph‚riques, quel port COM lui est attribu‚ ?
echo.
echo Si cette fenˆtre se ferme, c'est qu'il ne s'agit pas du bon port
echo ou bien Firmata n'est pas bien t‚l‚vers‚ dans votre Arduino...
echo.
echo IMPORTANT
echo ce script doit ˆtre ex‚cut‚ depuis le dossier o— se trouve le fichier s2a.py
echo Vous pouvez par contre en cr‚er un raccourci pour ˆtre ex‚cut‚ depuis le bureau.
echo.
rem ancienne ligne de commande pour l'auto-detect, pose rarement pb
rem for /f "tokens=4 delims=: " %%A in ('mode ^| findstr "COM[0-20]*:"') do .\Python\python s2a_fm.py %%A

echo Indiquer le port COM sur lequel est connect‚e votre Arduino (COM1, COM2, ...) : 
set /p port=
.\Python\python s2a.py %port%