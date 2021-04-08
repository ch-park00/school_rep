#해당 생성 파일 중 일부만 수정될 경우에는 수정된 파일과 해당 파일과 의존성을 가지는 파일만 다시 컴파일된다.
#매크로 정의
PROJ_DIR= ${PWD}
INC_DIR=${PROJ_DIR}/include
BIN_DIR=${PROJ_DIR}/bin
OBJ_DIR=${PROJ_DIR}/obj
SRC_DIR=${PROJ_DIR}/src
OBJS=${OBJ_DIR}/foo.o ${OBJ_DIR}/goo.o ${OBJ_DIR}/myapp.o 
SRCS=${shell find ${SRC_DIR}/ -name "*.c"}
#중요한 확장자임을 정의. 해당 확장자가 나오면 밑에 있는 컴파일 규칙이 있음을 알려준다.
.SUFFIXES: .o .c
all: dep ${BIN_DIR}/myapp

#실제 파일 컴파일 및 생성
${BIN_DIR}/myapp : ${OBJS} 
	gcc -o ${BIN_DIR}/myapp ${OBJS}

#해당 코드를 통해 밑에 있는 세개의 파일을 모두 생성 가능
${OBJ_DIR}/%.o : ${SRC_DIR}/%.c
	gcc -c $< -I./include -o $@


# action line(밑줄)의 경우, 스페이스바가 아닌 TAB을 이용해 공백을 만들어야 한다.
#./obj/myapp.o : ./include/funcs.h ./src/myapp.c 
#	gcc -c src/myapp.c -o obj/myapp.o -I./include  
#./obj/foo.o : ./src/foo.c 
#	gcc -c src/foo.c -o obj/foo.o -I./include
#./obj/goo.o : ./src/goo.c 
#	gcc -c src/goo.c -o obj/goo.o -I./include
#헤더파일에 대한 의존성 생성=> 헤더 파일이 수정될 경우 이 내용이 반영될 수 있도록 하는 것.
dep: .depend

.depend: ${SRCS}
	rm -f ./.depend
	gcc ${CFLAGS} -I${INC_DIR} -M $^ > ./.depend

include  ./.depend
clean :
	rm ${OBJ_DIR}/*
	rm ${BIN_DIR}/*
	rm -f ./.depend