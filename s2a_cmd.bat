@echo off
break ON
rem fichiers BAT et fork créés par Sébastien CANET
cls
SET currentpath=%~dp1
cd %currentpath%
start .\Python\python.exe s2a.py COM10