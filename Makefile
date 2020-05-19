CC=g++
INCLUDE :=${PARSER_ROOT}/include
SRC := ${PARSER_ROOT}/src
OUT := ${PARSER_ROOT}/out
CFLAGS := -shared  -g -std=c++11 -DDEB
LIB_DATA := libparser.so
                   
all : ${LIB_DATA}
	
${LIB_DATA} : libdir outdir  out/yacc out/lexer  obj/parser obj/lexer  obj/data obj/data_cache obj/sloader
	${CC}  ${CFLAGS} -o ${PARSER_ROOT}/lib/${LIB_DATA} ${OUT}/obj/*.o -ll -ly
	rm -r ${OUT}

libdir :
	mkdir -p ${PARSER_ROOT}/lib
outdir :
	mkdir -p ${OUT}/src ${OUT}/include ${OUT}/obj

out/yacc : ${SRC}/parser.y
	yacc -o out/src/y.tab.c --define=out/include/y.tab.h  ${SRC}/parser.y

out/lexer : ${SRC}/parser.l
	flex -o out/src/lex.yy.c  ${SRC}/parser.l

obj/parser : ${OUT}/src/y.tab.c
	${CC} -fPIC ${CFLAGS} -c  -o  ${OUT}/obj/parser.o  ${OUT}/src/y.tab.c  -I./include -I./out/include

obj/lexer : ${OUT}/src/lex.yy.c
	${CC} -fPIC ${CFLAGS} -c -o ${OUT}/obj/lexer.o ${OUT}/src/lex.yy.c -I./include -I./out/include

obj/sloader: ${PARSER_ROOT}/static_loader/src/static_loader.cc
	${CC} -fPIC ${CFLAGS} -c -o ${OUT}/obj/sloader.o ${PARSER_ROOT}/static_loader/src/static_loader.cc -I./include -I./static_loader/include

obj/data : ${SRC}/data.cc
	${CC} -fPIC ${CFLAGS} -c -o ${OUT}/obj/data.o ${SRC}/data.cc  -I./include -I./out/include

obj/data_cache : ${SRC}/data_cache.cc
	${CC} -fPIC ${CFLAGS} -c -o ${OUT}/obj/data_cache.o ${SRC}/data_cache.cc  -I./include -I./out/include

clean:
	rm -rf ${PARSER_ROOT}/lib
	rm -rf ${PARSER_ROOT}/out
