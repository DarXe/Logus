@echo off
echo WScript.Echo(new Date().getTime()); > %temp%\time.js
cscript //nologo %temp%\time.js
del %temp%\time.js