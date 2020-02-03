x=1
while [ $x -le 1000 ]
do
  curl -X POST -H 'Content-type: application/json' --data '{"data":"abc"}' 'localhost:8000/hashes'
#   echo "$x "
  x=$(( $x + 1 ))
done