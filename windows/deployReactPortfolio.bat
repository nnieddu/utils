```
  "scripts": {
    "mybuild": "npm run sass && npm run prefix && deployScript.bat",
    "sass": "sass ./src/styles/App.scss:./src/styles/App.css --style compressed",
    "prefix": "postcss ./src/styles/App.css --use autoprefixer -d ./src/styles/"
    },
    "browserslist": {
      "production": [
      "last 4 versions",
      ">0.2%",
      "not dead",
      "not op_mini all"
    ],
    "development": [
      "last 4 chrome version",
      "last 4 firefox version",
      "last 4 safari version"
    ]
  }
```
  
@REM [100m !ESC![100m Black !ESC![0m
@REM [101m !ESC![101m Red !ESC![0m
@REM [102m !ESC![102m Green !ESC![0m
@REM [103m !ESC![103m Yellow !ESC![0m
@REM [104m !ESC![104m Blue !ESC![0m
@REM [105m !ESC![105m Magenta !ESC![0m
@REM [106m !ESC![106m Cyan !ESC![0m
@REM [107m !ESC![107m White !ESC![0m

@ECHO OFF
SETLOCAL EnableExtensions DisableDelayedExpansion
for /F %%a in ('echo prompt $E ^| cmd') do (
  set "ESC=%%a"
)
SETLOCAL EnableDelayedExpansion

echo:
echo --------------------------------
echo ---------!ESC![92m FIN DU BUILD !ESC![0m---------
echo --------------------------------
echo:
echo:
@REM git pull
git add *
git commit -m %1
git push
echo --------------------------------
echo ------ FIN PUSH RAW CODE -------
echo --------------------------------
echo:
echo:
cd "nnieddu.github.io\"
git rm -rf "static"
cd ..
pwd
xcopy /E /Y "build\*" ".\nnieddu.github.io\."
cd "nnieddu.github.io\"
echo:
echo:
echo --------------------------------
echo --------- FIN DE COPY ----------
echo --------------------------------
@REM echo:
@REM echo:
@REM git pull
@REM echo:
@REM echo:
@REM echo --------------------------------
@REM echo --------- FIN DU PULL ----------
@REM echo --------------------------------
echo:
echo:
git add *
git commit -m %1
git push
echo:
echo:
echo -------------------------------
echo ---- FIN DU DEPLOIEMENT -------
echo -------------------------------
echo:
