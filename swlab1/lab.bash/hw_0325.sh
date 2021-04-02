RAND_NUM="$(($RANDOM%101))"
cnt=0
while :
do 
   cnt=$((cnt+1))
   echo -n "[$cnt]:enter your guesses [0..100]:"
   read num
   if [ $num -lt $RAND_NUM ]
   	then echo "answer is greater than $num"
   elif [ $num -gt $RAND_NUM ]
   	then echo "answer is less than $num"
   else
   	echo "you are correct!";break
   fi
done

