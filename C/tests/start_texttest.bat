set TEXTTEST_HOME=%~dp0
cd %TEXTTEST_HOME%
if not exist "venv" (
    py -m venv venv
)
venv\Scripts\pip install -r requirements.txt
if %ERRORLEVEL% GEQ 1 (
    pause
) else (
    texttestc.exe %*
)