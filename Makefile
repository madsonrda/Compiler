all: geracaocodigo.c y.tab.c lex.yy.c parser.y scanner.l
	flex -l scanner.l
	bison -d -y parser.y
	gcc -c y.tab.c lex.yy.c 
	gcc -g y.tab.c lex.yy.c geracaocodigo.c -o compilador
