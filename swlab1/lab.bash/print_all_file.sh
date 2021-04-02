#! /bin/bash

Var=$(ls)

for i in $Var

do
   # 디렉토리가 아니고 && 실행파일이 아닌 조건 검색
   if [ ! -d $i ] && [ ! -x $i ]
   then echo "$i : $(cat $i | wc -w)"
   fi
done
