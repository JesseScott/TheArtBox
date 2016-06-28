@echo off

for /F "tokens=2" %%i in ('date /t') do set mydate=%%i
set mytime=%time%
echo Current time is %mydate%:%mytime%

@echo on
PING 127.0.0.1 -n 10 >nul
"C:\Program Files (x86)\Google\Chrome\Application\chrome.exe" --user-data-dir=c:\temp --app="http://theartbox.ca/box/index.html" --new-window "%1" --window-position=0,0 --window-size=5760,2000