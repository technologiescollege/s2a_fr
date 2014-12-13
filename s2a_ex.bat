@echo off
break ON
rem fichiers BAT et fork créés par Sébastien CANET
cls
SET currentpath=%~dp1
SET dossier_scratch="Scratch 2.exe"
start %dossier_scratch% %currentpath%exemples\allumer_diode_Arduino_PIN13.sb2