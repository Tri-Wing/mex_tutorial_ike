SET "TKPATH=../../m-ex/MexTK/"
SET "FSPATH=../../filesystem/files/"

:: compile main code
"%TKPATH%MexTK.exe" -ff -i "Ike.c" "SpecialHi.c" "SpecialS.c" "SpecialN.c" "SpecialLw.c" -s ftFunction -t "%TKPATH%ftfunction.txt" -l "%TKPATH%melee.link" -dat "%FSPATH%PlBf.dat" -ow

pause