/*
PoC to detect SPAM with DFA and RANK

CoolerVoid
Contact: coolerlair[at]gmail[dot]com
	acosta[at]conviso[dot]com

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
  EXTENSION,PHISHING,OBFUSCATE,OBFUSCATE2,SHORTURL,COUNTER,END
};

// DFA to test if letter between a-z or A-Z
int test_letter(char p)
{
	unsigned char yych;

	yych = p;
	switch (yych) {
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy3;
	default:	goto yy2;
	}
yy2:
	{ return 1; }
yy3:
	++p;
	{ return 0; }
    

}

char *all2lowcase(char *str)
{
	char *str_new=malloc(sizeof(char)*strlen(str)+1);
	int i=0;
	
	while(*str != '\0')
	{
		
		if(!test_letter( *str ) )
		{

			*(str_new+i)=*str | 0x20;	
			i++;
		} else {
			*(str_new+i)=*str;
			i++;
		}

	
		str++;	
	}


	return str_new;

}

//read lines of file
char *ReadLines(char * NameFile)
{
	FILE * fh;
	char *buffer=NULL;

	fh = fopen(NameFile, "rb");

	if( fh == NULL )
	{

		printf("error in to open() file"); 	 
		exit(1);
	}

	fseek(fh, 0L, SEEK_END);
    	long s = ftell(fh);
    	rewind(fh);
    	buffer = malloc(s);

    	if ( buffer != NULL )
    	{
      		fread(buffer, s, 1, fh);
      		fwrite(buffer, s, 1, stdout);
    	}

 
	if( fclose(fh) == EOF )
	{
		printf("Error in close() file %s",NameFile);
		exit(1);
	}

	fh=NULL;

	return buffer;
}


int dfa_judge_spam(char** p, char** lex)
{
    char* marker;

    for (;;) {
    *lex = *p;
    
	{
		char yych;

		yych = (char)**p;
		switch (yych) {
		case 0x00:	goto yy26;
		case '\n':	goto yy24;
		case '%':	goto yy11;
		case '&':	goto yy16;
		case '(':	goto yy12;
		case '*':
		case '>':	goto yy2;
		case '.':	goto yy4;
		case '0':	goto yy15;
		case '1':	goto yy14;
		case '7':	goto yy18;
		case '[':	goto yy13;
		case 'b':	goto yy23;
		case 'c':	goto yy6;
		case 'f':	goto yy9;
		case 'g':	goto yy20;
		case 'h':	goto yy17;
		case 'i':	goto yy5;
		case 'l':	goto yy10;
		case 'm':	goto yy22;
		case 'o':	goto yy21;
		case 'p':	goto yy7;
		case 's':	goto yy8;
		case 't':	goto yy19;
		default:	goto yy28;
		}
yy2:
		yych = (char)*(marker = ++*p);
		switch (yych) {
		case '%':
		case '&':
		case '(':
		case '*':
		case '.':
		case '0':
		case '1':
		case '7':
		case '>':
		case '[':
		case 'b':
		case 'c':
		case 'f':
		case 'g':
		case 'h':
		case 'i':
		case 'l':
		case 'm':
		case 'o':
		case 'p':
		case 's':
		case 't':	goto yy127;
		default:	goto yy3;
		}
yy3:
		{ continue; }
yy4:
		yych = (char)*(marker = ++*p);
		switch (yych) {
		case '%':
		case '&':
		case '(':
		case '*':
		case '.':
		case '0':
		case '1':
		case '7':
		case '>':
		case '[':
		case 'b':
		case 'c':
		case 'f':
		case 'g':
		case 'h':
		case 'i':
		case 'l':
		case 'm':
		case 'o':
		case 's':
		case 't':	goto yy127;
		case 'e':	goto yy145;
		case 'p':	goto yy139;
		case 'r':	goto yy143;
		case 'z':	goto yy144;
		default:	goto yy3;
		}
yy5:
		yych = (char)*(marker = ++*p);
		switch (yych) {
		case 'n':	goto yy115;
		case 's':	goto yy114;
		default:	goto yy3;
		}
yy6:
		yych = (char)*(marker = ++*p);
		switch (yych) {
		case 'a':	goto yy109;
		case 'p':	goto yy110;
		default:	goto yy3;
		}
yy7:
		yych = (char)*(marker = ++*p);
		switch (yych) {
		case 'a':	goto yy103;
		default:	goto yy3;
		}
yy8:
		yych = (char)*(marker = ++*p);
		switch (yych) {
		case 'e':	goto yy97;
		default:	goto yy3;
		}
yy9:
		yych = (char)*(marker = ++*p);
		switch (yych) {
		case 'o':	goto yy95;
		default:	goto yy3;
		}
yy10:
		yych = (char)*(marker = ++*p);
		switch (yych) {
		case 'o':	goto yy89;
		default:	goto yy3;
		}
yy11:
		yych = (char)*(marker = ++*p);
		switch (yych) {
		case '7':	goto yy88;
		default:	goto yy3;
		}
yy12:
		yych = (char)*(marker = ++*p);
		switch (yych) {
		case 'a':	goto yy83;
		case 'd':	goto yy84;
		default:	goto yy3;
		}
yy13:
		yych = (char)*(marker = ++*p);
		switch (yych) {
		case 'a':	goto yy75;
		case 'd':	goto yy76;
		default:	goto yy3;
		}
yy14:
		yych = (char)*(marker = ++*p);
		switch (yych) {
		case '1':	goto yy72;
		default:	goto yy3;
		}
yy15:
		yych = (char)*(marker = ++*p);
		switch (yych) {
		case '0':	goto yy70;
		default:	goto yy3;
		}
yy16:
		yych = (char)*(marker = ++*p);
		switch (yych) {
		case 's':	goto yy67;
		default:	goto yy3;
		}
yy17:
		yych = (char)*(marker = ++*p);
		switch (yych) {
		case 'x':	goto yy65;
		default:	goto yy3;
		}
yy18:
		yych = (char)*(marker = ++*p);
		switch (yych) {
		case '7':	goto yy60;
		default:	goto yy3;
		}
yy19:
		yych = (char)*(marker = ++*p);
		switch (yych) {
		case 'i':	goto yy49;
		default:	goto yy3;
		}
yy20:
		yych = (char)*(marker = ++*p);
		switch (yych) {
		case 'o':	goto yy45;
		default:	goto yy3;
		}
yy21:
		yych = (char)*(marker = ++*p);
		switch (yych) {
		case 'w':	goto yy42;
		default:	goto yy3;
		}
yy22:
		yych = (char)*(marker = ++*p);
		switch (yych) {
		case 'c':	goto yy37;
		default:	goto yy3;
		}
yy23:
		yych = (char)*(marker = ++*p);
		switch (yych) {
		case 'i':	goto yy29;
		default:	goto yy3;
		}
yy24:
		++*p;
#line 171 "spam.c"
		{ return COUNTER; }
#line 378 "<stdout>"
yy26:
		++*p;
#line 172 "spam.c"
		{ return END; }
#line 383 "<stdout>"
yy28:
		yych = (char)*++*p;
		goto yy3;
yy29:
		yych = (char)*++*p;
		switch (yych) {
		case 't':	goto yy31;
		default:	goto yy30;
		}
yy30:
		*p = marker;
		goto yy3;
yy31:
		yych = (char)*++*p;
		switch (yych) {
		case '.':	goto yy32;
		default:	goto yy30;
		}
yy32:
		yych = (char)*++*p;
		switch (yych) {
		case 'l':	goto yy33;
		default:	goto yy30;
		}
yy33:
		yych = (char)*++*p;
		switch (yych) {
		case 'y':	goto yy34;
		default:	goto yy30;
		}
yy34:
		++*p;
		yych = (char)**p;
		switch (yych) {
		case '\n':	goto yy36;
		default:	goto yy34;
		}
yy36:
		{ return SHORTURL; }
yy37:
		yych = (char)*++*p;
		switch (yych) {
		case 'a':	goto yy38;
		default:	goto yy30;
		}
yy38:
		yych = (char)*++*p;
		switch (yych) {
		case 'f':	goto yy39;
		default:	goto yy30;
		}
yy39:
		yych = (char)*++*p;
		switch (yych) {
		case '.':	goto yy40;
		default:	goto yy30;
		}
yy40:
		yych = (char)*++*p;
		switch (yych) {
		case 'e':	goto yy41;
		default:	goto yy30;
		}
yy41:
		yych = (char)*++*p;
		switch (yych) {
		case 'e':	goto yy34;
		default:	goto yy30;
		}
yy42:
		yych = (char)*++*p;
		switch (yych) {
		case '.':	goto yy43;
		default:	goto yy30;
		}
yy43:
		yych = (char)*++*p;
		switch (yych) {
		case 'l':	goto yy44;
		default:	goto yy30;
		}
yy44:
		yych = (char)*++*p;
		switch (yych) {
		case 'y':	goto yy34;
		default:	goto yy30;
		}
yy45:
		yych = (char)*++*p;
		switch (yych) {
		case 'o':	goto yy46;
		default:	goto yy30;
		}
yy46:
		yych = (char)*++*p;
		switch (yych) {
		case '.':	goto yy47;
		default:	goto yy30;
		}
yy47:
		yych = (char)*++*p;
		switch (yych) {
		case 'g':	goto yy48;
		default:	goto yy30;
		}
yy48:
		yych = (char)*++*p;
		switch (yych) {
		case 'l':	goto yy34;
		default:	goto yy30;
		}
yy49:
		yych = (char)*++*p;
		switch (yych) {
		case 'n':	goto yy50;
		default:	goto yy30;
		}
yy50:
		yych = (char)*++*p;
		switch (yych) {
		case 'y':	goto yy51;
		default:	goto yy30;
		}
yy51:
		yych = (char)*++*p;
		switch (yych) {
		case '.':	goto yy53;
		case 'u':	goto yy52;
		default:	goto yy30;
		}
yy52:
		yych = (char)*++*p;
		switch (yych) {
		case 'r':	goto yy55;
		default:	goto yy30;
		}
yy53:
		yych = (char)*++*p;
		switch (yych) {
		case 'c':	goto yy54;
		default:	goto yy30;
		}
yy54:
		yych = (char)*++*p;
		switch (yych) {
		case 'c':	goto yy34;
		default:	goto yy30;
		}
yy55:
		yych = (char)*++*p;
		switch (yych) {
		case 'l':	goto yy56;
		default:	goto yy30;
		}
yy56:
		yych = (char)*++*p;
		switch (yych) {
		case '.':	goto yy57;
		default:	goto yy30;
		}
yy57:
		yych = (char)*++*p;
		switch (yych) {
		case 'c':	goto yy58;
		default:	goto yy30;
		}
yy58:
		yych = (char)*++*p;
		switch (yych) {
		case 'o':	goto yy59;
		default:	goto yy30;
		}
yy59:
		yych = (char)*++*p;
		switch (yych) {
		case 'm':	goto yy34;
		default:	goto yy30;
		}
yy60:
		yych = (char)*++*p;
		switch (yych) {
		case '7':	goto yy61;
		default:	goto yy30;
		}
yy61:
		yych = (char)*++*p;
		switch (yych) {
		case '7':	goto yy62;
		default:	goto yy30;
		}
yy62:
		++*p;
		yych = (char)**p;
		switch (yych) {
		case '\n':	goto yy64;
		default:	goto yy62;
		}
yy64:
		{ return OBFUSCATE2; }
yy65:
		yych = (char)*++*p;
		switch (yych) {
		case 'x':	goto yy66;
		default:	goto yy30;
		}
yy66:
		yych = (char)*++*p;
		switch (yych) {
		case 'p':	goto yy62;
		default:	goto yy30;
		}
yy67:
		yych = (char)*++*p;
		switch (yych) {
		case 'h':	goto yy68;
		default:	goto yy30;
		}
yy68:
		yych = (char)*++*p;
		switch (yych) {
		case 'y':	goto yy69;
		default:	goto yy30;
		}
yy69:
		yych = (char)*++*p;
		switch (yych) {
		case ';':	goto yy62;
		default:	goto yy30;
		}
yy70:
		yych = (char)*++*p;
		switch (yych) {
		case '0':	goto yy71;
		default:	goto yy30;
		}
yy71:
		yych = (char)*++*p;
		switch (yych) {
		case '0':	goto yy62;
		default:	goto yy30;
		}
yy72:
		yych = (char)*++*p;
		switch (yych) {
		case '1':	goto yy73;
		default:	goto yy30;
		}
yy73:
		yych = (char)*++*p;
		switch (yych) {
		case '1':	goto yy74;
		default:	goto yy30;
		}
yy74:
		yych = (char)*++*p;
		switch (yych) {
		case '1':	goto yy62;
		default:	goto yy30;
		}
yy75:
		yych = (char)*++*p;
		switch (yych) {
		case 't':	goto yy82;
		default:	goto yy30;
		}
yy76:
		yych = (char)*++*p;
		switch (yych) {
		case 'o':	goto yy77;
		default:	goto yy30;
		}
yy77:
		yych = (char)*++*p;
		switch (yych) {
		case 't':	goto yy78;
		default:	goto yy30;
		}
yy78:
		yych = (char)*++*p;
		switch (yych) {
		case ']':	goto yy79;
		default:	goto yy30;
		}
yy79:
		++*p;
		yych = (char)**p;
		switch (yych) {
		case '\n':	goto yy81;
		default:	goto yy79;
		}
yy81:
		{ return OBFUSCATE; }
yy82:
		yych = (char)*++*p;
		switch (yych) {
		case ']':	goto yy79;
		default:	goto yy30;
		}
yy83:
		yych = (char)*++*p;
		switch (yych) {
		case 't':	goto yy87;
		default:	goto yy30;
		}
yy84:
		yych = (char)*++*p;
		switch (yych) {
		case 'o':	goto yy85;
		default:	goto yy30;
		}
yy85:
		yych = (char)*++*p;
		switch (yych) {
		case 't':	goto yy86;
		default:	goto yy30;
		}
yy86:
		yych = (char)*++*p;
		switch (yych) {
		case ')':	goto yy79;
		default:	goto yy30;
		}
yy87:
		yych = (char)*++*p;
		switch (yych) {
		case ')':	goto yy79;
		default:	goto yy30;
		}
yy88:
		yych = (char)*++*p;
		switch (yych) {
		case '7':	goto yy79;
		default:	goto yy30;
		}
yy89:
		yych = (char)*++*p;
		switch (yych) {
		case 'g':	goto yy90;
		default:	goto yy30;
		}
yy90:
		yych = (char)*++*p;
		switch (yych) {
		case 'i':	goto yy91;
		default:	goto yy30;
		}
yy91:
		yych = (char)*++*p;
		switch (yych) {
		case 'n':	goto yy92;
		default:	goto yy30;
		}
yy92:
		++*p;
		yych = (char)**p;
yy93:
		switch (yych) {
		case '\n':	goto yy94;
		default:	goto yy92;
		}
yy94:
		{ return PHISHING; }
yy95:
		yych = (char)*++*p;
		switch (yych) {
		case 'r':	goto yy96;
		default:	goto yy30;
		}
yy96:
		yych = (char)*++*p;
		switch (yych) {
		case 'm':	goto yy92;
		default:	goto yy30;
		}
yy97:
		yych = (char)*++*p;
		switch (yych) {
		case 'c':	goto yy99;
		case 'n':	goto yy98;
		default:	goto yy30;
		}
yy98:
		yych = (char)*++*p;
		switch (yych) {
		case 'h':	goto yy102;
		default:	goto yy30;
		}
yy99:
		yych = (char)*++*p;
		switch (yych) {
		case 'r':	goto yy100;
		default:	goto yy30;
		}
yy100:
		yych = (char)*++*p;
		switch (yych) {
		case 'e':	goto yy101;
		default:	goto yy30;
		}
yy101:
		yych = (char)*++*p;
		switch (yych) {
		case 't':	goto yy92;
		default:	goto yy30;
		}
yy102:
		yych = (char)*++*p;
		switch (yych) {
		case 'a':	goto yy92;
		default:	goto yy30;
		}
yy103:
		yych = (char)*++*p;
		switch (yych) {
		case 's':	goto yy104;
		default:	goto yy30;
		}
yy104:
		yych = (char)*++*p;
		switch (yych) {
		case 's':	goto yy105;
		default:	goto yy30;
		}
yy105:
		yych = (char)*++*p;
		switch (yych) {
		case 'w':	goto yy106;
		default:	goto yy93;
		}
yy106:
		yych = (char)*++*p;
		switch (yych) {
		case 'o':	goto yy107;
		default:	goto yy93;
		}
yy107:
		yych = (char)*++*p;
		switch (yych) {
		case 'r':	goto yy108;
		default:	goto yy93;
		}
yy108:
		yych = (char)*++*p;
		goto yy93;
yy109:
		yych = (char)*++*p;
		switch (yych) {
		case 'r':	goto yy111;
		default:	goto yy30;
		}
yy110:
		yych = (char)*++*p;
		switch (yych) {
		case 'f':	goto yy92;
		default:	goto yy30;
		}
yy111:
		yych = (char)*++*p;
		switch (yych) {
		case 'd':	goto yy92;
		case 't':	goto yy112;
		default:	goto yy30;
		}
yy112:
		yych = (char)*++*p;
		switch (yych) {
		case 'a':	goto yy113;
		default:	goto yy30;
		}
yy113:
		yych = (char)*++*p;
		switch (yych) {
		case 'o':	goto yy92;
		default:	goto yy30;
		}
yy114:
		yych = (char)*++*p;
		switch (yych) {
		case '.':	goto yy118;
		default:	goto yy30;
		}
yy115:
		yych = (char)*++*p;
		switch (yych) {
		case 'p':	goto yy116;
		default:	goto yy30;
		}
yy116:
		yych = (char)*++*p;
		switch (yych) {
		case 'u':	goto yy117;
		default:	goto yy30;
		}
yy117:
		yych = (char)*++*p;
		switch (yych) {
		case 't':	goto yy92;
		default:	goto yy30;
		}
yy118:
		yych = (char)*++*p;
		switch (yych) {
		case 'g':	goto yy119;
		default:	goto yy30;
		}
yy119:
		yych = (char)*++*p;
		switch (yych) {
		case 'd':	goto yy34;
		default:	goto yy30;
		}
yy120:
		yych = (char)*++*p;
		switch (yych) {
		case 'i':	goto yy49;
		default:	goto yy30;
		}
yy121:
		yych = (char)*++*p;
		switch (yych) {
		case 'o':	goto yy45;
		default:	goto yy30;
		}
yy122:
		yych = (char)*++*p;
		switch (yych) {
		case 'w':	goto yy42;
		default:	goto yy30;
		}
yy123:
		yych = (char)*++*p;
		switch (yych) {
		case 'n':	goto yy115;
		case 's':	goto yy114;
		default:	goto yy30;
		}
yy124:
		yych = (char)*++*p;
		switch (yych) {
		case 'c':	goto yy37;
		default:	goto yy30;
		}
yy125:
		yych = (char)*++*p;
		switch (yych) {
		case 'i':	goto yy29;
		default:	goto yy30;
		}
yy126:
		++*p;
		yych = (char)**p;
yy127:
		switch (yych) {
		case '%':	goto yy135;
		case '&':	goto yy132;
		case '(':	goto yy136;
		case '*':
		case '>':	goto yy126;
		case '.':	goto yy128;
		case '0':	goto yy131;
		case '1':	goto yy130;
		case '7':	goto yy134;
		case '[':	goto yy137;
		case 'b':	goto yy125;
		case 'c':	goto yy138;
		case 'f':	goto yy141;
		case 'g':	goto yy121;
		case 'h':	goto yy133;
		case 'i':	goto yy123;
		case 'l':	goto yy142;
		case 'm':	goto yy124;
		case 'o':	goto yy122;
		case 'p':	goto yy153;
		case 's':	goto yy140;
		case 't':	goto yy120;
		default:	goto yy30;
		}
yy128:
		++*p;
		yych = (char)**p;
		switch (yych) {
		case '%':	goto yy135;
		case '&':	goto yy132;
		case '(':	goto yy136;
		case '*':
		case '>':	goto yy126;
		case '.':	goto yy128;
		case '0':	goto yy131;
		case '1':	goto yy130;
		case '7':	goto yy134;
		case '[':	goto yy137;
		case 'b':	goto yy125;
		case 'c':	goto yy138;
		case 'e':	goto yy145;
		case 'f':	goto yy141;
		case 'g':	goto yy121;
		case 'h':	goto yy133;
		case 'i':	goto yy123;
		case 'l':	goto yy142;
		case 'm':	goto yy124;
		case 'o':	goto yy122;
		case 'p':	goto yy139;
		case 'r':	goto yy143;
		case 's':	goto yy140;
		case 't':	goto yy120;
		case 'z':	goto yy144;
		default:	goto yy30;
		}
yy130:
		yych = (char)*++*p;
		switch (yych) {
		case '1':	goto yy72;
		default:	goto yy30;
		}
yy131:
		yych = (char)*++*p;
		switch (yych) {
		case '0':	goto yy70;
		default:	goto yy30;
		}
yy132:
		yych = (char)*++*p;
		switch (yych) {
		case 's':	goto yy67;
		default:	goto yy30;
		}
yy133:
		yych = (char)*++*p;
		switch (yych) {
		case 'x':	goto yy65;
		default:	goto yy30;
		}
yy134:
		yych = (char)*++*p;
		switch (yych) {
		case '7':	goto yy60;
		default:	goto yy30;
		}
yy135:
		yych = (char)*++*p;
		switch (yych) {
		case '7':	goto yy88;
		default:	goto yy30;
		}
yy136:
		yych = (char)*++*p;
		switch (yych) {
		case 'a':	goto yy83;
		case 'd':	goto yy84;
		default:	goto yy30;
		}
yy137:
		yych = (char)*++*p;
		switch (yych) {
		case 'a':	goto yy75;
		case 'd':	goto yy76;
		default:	goto yy30;
		}
yy138:
		yych = (char)*++*p;
		switch (yych) {
		case 'a':	goto yy109;
		case 'p':	goto yy110;
		default:	goto yy30;
		}
yy139:
		yych = (char)*++*p;
		switch (yych) {
		case 'a':	goto yy103;
		case 'd':	goto yy152;
		default:	goto yy30;
		}
yy140:
		yych = (char)*++*p;
		switch (yych) {
		case 'e':	goto yy97;
		default:	goto yy30;
		}
yy141:
		yych = (char)*++*p;
		switch (yych) {
		case 'o':	goto yy95;
		default:	goto yy30;
		}
yy142:
		yych = (char)*++*p;
		switch (yych) {
		case 'o':	goto yy89;
		default:	goto yy30;
		}
yy143:
		yych = (char)*++*p;
		switch (yych) {
		case 'a':	goto yy151;
		default:	goto yy30;
		}
yy144:
		yych = (char)*++*p;
		switch (yych) {
		case 'i':	goto yy150;
		default:	goto yy30;
		}
yy145:
		yych = (char)*++*p;
		switch (yych) {
		case 'x':	goto yy146;
		default:	goto yy30;
		}
yy146:
		yych = (char)*++*p;
		switch (yych) {
		case 'e':	goto yy147;
		default:	goto yy30;
		}
yy147:
		++*p;
		yych = (char)**p;
		switch (yych) {
		case '\n':	goto yy149;
		default:	goto yy147;
		}
yy149:
		{ return EXTENSION; }
yy150:
		yych = (char)*++*p;
		switch (yych) {
		case 'p':	goto yy147;
		default:	goto yy30;
		}
yy151:
		yych = (char)*++*p;
		switch (yych) {
		case 'r':	goto yy147;
		default:	goto yy30;
		}
yy152:
		yych = (char)*++*p;
		switch (yych) {
		case 'f':	goto yy147;
		default:	goto yy30;
		}
yy153:
		++*p;
		switch ((yych = (char)**p)) {
		case 'a':	goto yy103;
		default:	goto yy30;
		}
	}

    }
}


int spam_points(char *buffer) 
{

    char *lowcase = all2lowcase(buffer);
    char *last = lowcase;
    int spam=0,result=0,line_number=1;

// Deterministic finite automaton to detect points and SImple RANK
    while(!result )
	switch (dfa_judge_spam(&buffer, &last)) 
	{
// detect extension like .exe, .pdf ... at urls 
        	case EXTENSION:
	    	spam+=(spam<40)?5:0;
		printf("Have possible Malware here line number %d \n",line_number);	
            	break;

// detect Phishing inputs (forms, fields...)
	        case PHISHING:
	        spam+=(spam<40)?1:0;
     	        printf("Have PHISHING Match line number %d \n",line_number);
   	        break;

// detect Obfuscation type 1
	        case OBFUSCATE:
	        spam+=(spam<40)?1:0;
     	        printf("Have Obfuscation match here! line number %d \n",line_number);
   	        break;

// detect Obfuscation type 2
	        case OBFUSCATE2:
	        spam+=(spam<40)?5:0;
     	        printf("Have Obfuscation2 match here! line number %d \n",line_number);
   	        break;

// Detect common SHORT URL 
	        case SHORTURL:
	        spam+=(spam<40)?8:0;
     	        printf("Have Short URL match here! line number %d \n",line_number);
   	        break;

// Counter of lines
		case COUNTER:
	    	line_number++;
            	break;

        	case END:
	    	result=1;	
            	break;
        }

// free memory
    if(lowcase!=NULL)
    {
    	free(lowcase);
	lowcase=NULL;
    }

// Return Spam points
    return spam;
}


int main()
{
// open e-mail text data
    char *p = ReadLines("log1");

	if(spam_points(p) >= 20) {
		puts("High level of spam rank");
	} 

	else if(spam_points(p) > 10) {
		puts("Medium level of spam rank");
	}
 
	else if(spam_points(p) < 10) {
		puts("Low level of spam rank");
	}

    if(p!=NULL)
    {
    	free(p);
	p=NULL;
    }
	   
    return 0;
}

