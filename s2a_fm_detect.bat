@echo off
break ON
cls
echo Vous devez verifier la derniere ligne de ce fichier afin qu'elle corresponde
echo au dossier dans lequel vous avez installe Python.
echo.
echo IMPORTANT : ce fichier doit etre execute depuis le dossier de s2a_fm,
echo la ou se trouve le fichier s2a_fm.py
echo Vous pouvez par contre en creer un raccourci pour etre execute depuis le bureau.
echo.
for /f "tokens=4 delims=: " %%A in ('mode ^| findstr "COM[0-20]*:"') do c:\python27\python s2a_fm.py %%A

