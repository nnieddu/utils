@echo off
@REM npm run build
echo "--------------------------------"
echo "--------------------------------"
echo "--------- FIN DU BUILD ---------"
echo "--------------------------------"
echo "--------------------------------"
echo ""
echo ""
git pull
git add *
git commit -m %1
git push
echo "--------------------------------"
echo "--------------------------------"
echo "--------- PUSH RAW CODE --------"
echo "--------------------------------"
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
echo "--------------------------------"
echo "--------- FIN DE COPY ---------"
echo "--------------------------------"
echo "--------------------------------"
echo ""
echo ""
@REM git pull
echo ""
echo ""
echo "--------------------------------"
echo "--------------------------------"
echo "--------- FIN DU PULL ---------"
echo "--------------------------------"
echo "--------------------------------"
echo ""
echo ""
git add *
git commit -m %1
git push
echo ""
echo ""
echo "--------------------------------"
echo "--------------------------------"
echo "----- FIN DU DEPLOIEMENT -------"
echo "--------------------------------"
echo "--------------------------------"
