#! /bin/bash

my_function()
{
   # $1 - 첫번째 파라미터 $2 - 두번째 파라미터
   echo "Hello $1 $2"
}

for_function()
{
	# $* : 모든 파라미터
   for i in $*
   do
   	# "" 이 문장으로 쓸 경우 변수로 해석이 가능하지만 '' 인 경우 스트링으로 해석되어 변수값 출력 안됨.
      echo "hello $i"
   done
}
my_files()
{
   FILES=$(ls)
   #echo $FILES
   for f in $FILES
   do
      echo "$f"
   done
}

my_sum()
{
   S=0
   read my_point
   for i in $(seq 1 $my_point)
   do
      # 산술 연산 수행
      S=$((S+i))
      #echo "$i"
   done
   echo "$S"
}


# 함수 호출. 호출 시 파라미터를 넣기 위해서는 아래와 같이 입력
my_function "pch" "INU"
for_function "pch" "INU"
#my_function $1 $2
#for_function $1 $2
my_files
my_sum
