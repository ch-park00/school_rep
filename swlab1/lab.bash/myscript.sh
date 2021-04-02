#! /bin/bash

#MY_NAME="PCH"

# echo 뒤에 -n 옵션이 붙은 경우 줄바꿈이 되지 않음.
echo -n "NAME:"
read MY_NAME
echo "Hello! $MY_NAME";
echo "GOODBYE";
echo $MY_NAME;

