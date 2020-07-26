CC=g++
INCLUDE :=${PARSER_ROOT}/include
SRC := ${PARSER_ROOT}/src
OUT := ${PARSER_ROOT}/out
CFLAGS := -shared  -g -std=c++11 -Wno-deprecated-register -DDEB 
CFLAGS_17 := -shared  -g -std=c++17 -DDEB
LIB_PARSER := libparser.so
                   
all : ${LIB_PARSER}
	
${LIB_PARSER} : libdir outdir  out/yacc out/lexer  obj/parser obj/lexer  obj/data obj/data_cache obj/sloader obj/connection_factory obj/plsql_loader
	${CC}  ${CFLAGS} -o ${PARSER_ROOT}/lib/${LIB_PARSER} ${OUT}/obj/*.o -ll -ly  -lpqxx -lpq
	rm -r ${OUT}

libdir :
	mkdir -p ${PARSER_ROOT}/lib
outdir :
	mkdir -p ${OUT}/src ${OUT}/include ${OUT}/obj

out/yacc : ${SRC}/parser.y
	bison  -o out/src/y.tab.c --defines=out/include/y.tab.h  ${SRC}/parser.y

out/lexer : ${SRC}/parser.l
	flex  -o out/src/lex.yy.c  ${SRC}/parser.l

obj/parser : ${OUT}/src/y.tab.c
	${CC} -fPIC ${CFLAGS} -c  -o  ${OUT}/obj/parser.o  ${OUT}/src/y.tab.c  -I./include -I./out/include 

obj/lexer : ${OUT}/src/lex.yy.c
	${CC} -fPIC ${CFLAGS} -c -o ${OUT}/obj/lexer.o ${OUT}/src/lex.yy.c -I./include -I./out/include

obj/sloader : ${PARSER_ROOT}/static_loader/src/static_loader.cc
	${CC} -fPIC ${CFLAGS} -c -o ${OUT}/obj/sloader.o ${PARSER_ROOT}/static_loader/src/static_loader.cc -I./include -I./static_loader/include

obj/plsql :
	obj/connection_factory

obj/plsql_loader : ${PARSER_ROOT}/plsql/src/plsql_loader.cc
	${CC} -fPIC ${CFLAGS_17} -c -o ${OUT}/obj/plsqlloader.o ${PARSER_ROOT}/plsql/src/plsql_loader.cc -I./include -I./plsql/include

obj/connection_factory :	
	#${CC} -fPIC ${CFLAGS} -c -o ${OUT}/obj/connection_factory.o ${PARSER_ROOT}/plsql/src/connection_factory.cc -I./include -I./plsql/include 
	${CC} ${CFLAGS_17} -fPIC -c -o ${OUT}/obj/connection_factory.o ${PARSER_ROOT}/plsql/src/connection_factory.cc -I./include -I./plsql/include

obj/data : ${SRC}/data.cc
	${CC} -fPIC ${CFLAGS} -c -o ${OUT}/obj/data.o ${SRC}/data.cc  -I./include -I./out/include

obj/data_cache : ${SRC}/data_cache.cc
	${CC} -fPIC ${CFLAGS} -c -o ${OUT}/obj/data_cache.o ${SRC}/data_cache.cc  -I./include -I./out/include

clean:
	rm -rf ${PARSER_ROOT}/lib
	rm -rf ${PARSER_ROOT}/out

#g++ -o main  driver.cc -L./lib/ -lparser -I./include -I./static_loader/include -I./plsql/include -std=c++17
