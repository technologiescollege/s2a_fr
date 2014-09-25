@echo off
break ON
rem fichiers BAT et fork créés par Sébastien CANET
cls
echo.
echo s2a : la communication Arduino+Scratch2 facile !
echo.
echo Vous devez juste indiquer le numero de port de la carte Arduino :
echo dans le gestionnaire de peripheriques, quel port COM lui est attribue ?
echo Si cette fenetre se ferme, c'est qu'il ne s'agit pas du bon port...
echo.
echo IMPORTANT
echo ce script doit etre execute depuis le dossier ou se trouve le fichier s2a_fm.py
echo Vous pouvez par contre en creer un raccourci pour etre execute depuis le bureau.
echo.
echo Le plus simple pour demarrer est d'ensuite demarrer Scratch2 quand il vous le
echo propose puis ouvrir le fichier "fichier_vide_FR.sb2" (attention extension sb2).
echo.
rem ancienne ligne de commande pour l'auto-detect, pose rarement pb
rem for /f "tokens=4 delims=: " %%A in ('mode ^| findstr "COM[0-20]*:"') do c:\python27\python s2a_fm.py %%A

set /p port=Indiquer le port COM sur lequel est connecte votre interface Arduino (COM1, COM2, etc - voir le Gestionnaire de peripheriques) :
.\Python\python s2a.py %port%