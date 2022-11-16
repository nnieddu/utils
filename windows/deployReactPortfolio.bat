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
  
@echo off
echo "--------------------------------"
echo "--------------------------------"
echo "--------- FIN DU BUILD ---------"
echo "--------------------------------"
echo "--------------------------------"
echo ""
echo ""
@REM git pull
git add *
git commit -m %1
git push
echo "--------------------------------"
echo "--------- PUSH RAW CODE --------"
echo "--------------------------------"
echo ""
echo ""
cd "nnieddu.github.io\"
git rm -rf "static\"
cd ..
dir
xcopy /E /Y "build\*" "nnieddu.github.io\."
cd "nnieddu.github.io\"
echo ""
echo ""
echo "--------------------------------"
echo "--------- FIN DE COPY ---------"
echo "--------------------------------"
echo ""
echo ""
@REM git pull
echo ""
echo ""
echo "--------------------------------"
echo "--------- FIN DU PULL ---------"
echo "--------------------------------"
echo ""
echo ""
git add *
git commit -m %1
git push
echo ""
echo ""
echo "--------------------------------"
echo "----- FIN DU DEPLOIEMENT -------"
echo "--------------------------------"
