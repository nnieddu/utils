count=0
while [ $count != 2500 ]
do
    nc 127.0.0.1 8080 -w 1 < file
    ((count=count+1))
done