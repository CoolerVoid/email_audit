#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

char ordinary[CHAR_MAX] = {
    ['A']=1,['B']=1,['C']=1,['D']=1,['E']=1,['F']=1,['G']=1,['H']=1,['I']=1,
    ['J']=1,['K']=1,['L']=1,['M']=1,['N']=1,['O']=1,['P']=1,['Q']=1,['R']=1,
    ['S']=1,['T']=1,['U']=1,['V']=1,['W']=1,['X']=1,['Y']=1,['Z']=1,

    ['a']=1,['b']=1,['c']=1,['d']=1,['e']=1,['f']=1,['g']=1,['h']=1,['i']=1,
    ['j']=1,['k']=1,['l']=1,['m']=1,['n']=1,['o']=1,['p']=1,['q']=1,['r']=1,
    ['s']=1,['t']=1,['u']=1,['v']=1,['w']=1,['x']=1,['y']=1,['z']=1,[' ']=1
};

int is_special (int c) 
{
    	if (c < 0) 
		return 1;

    	if (c >= CHAR_MAX) 
		return 1;

    return !ordinary[c];
}

void remove_specials_chars (char *str) 
{

        	char *p = str;

        	for (; *str; ++str) 
            		if (!is_special(*str)) 
				*p++ = *str;
	    	
        	*p = '\0';
    
}

enum {
  WORD1,WORD2,WORD3,WORD4, END
};


char *ReadLines(char * NameFile)
{
	FILE * fh;
	char buffer[180800];

	fh = fopen(NameFile, "rb");

	if( fh == NULL )
	{

		exit(-1); 	 
		
	}

	if(fseek(fh, 0L, SEEK_END)==0)
	{
    		long s = ftell(fh);
    		rewind(fh);

    		if ( buffer != NULL && s < 180800 )
    		{
      			if(!fread(buffer, s, 1, fh))
				puts("error \n");
    		}
	}

 
	if( fclose(fh) == EOF )
	{

		exit(1);
	}

	fh=NULL;
	char *tmp=buffer;
	
	return tmp;
}

// DFA to parse HTML tags of e-mail
int parse_clear(char** p, char** lex)
{
    char* marker;

    for (;;) {
    *lex = *p;
    

	{
		char yych;

		yych = (char)**p;
		switch (yych) {
		case 0x00:	goto yy4;
		case '>':	goto yy2;
		default:	goto yy6;
		}
yy2:
		yych = (char)*(marker = ++*p);
		switch (yych) {
		case '>':	goto yy3;
		default:	goto yy7;
		}
yy3:

		{ continue; }

yy4:
		++*p;

		{ return END; }

yy6:
		yych = (char)*++*p;
		goto yy3;
yy7:
		++*p;
		yych = (char)**p;
		switch (yych) {
		case '<':	goto yy10;
		case '>':	goto yy9;
		default:	goto yy7;
		}
yy9:
		*p = marker;
		goto yy3;
yy10:
		++*p;
		yych = (char)**p;
		switch (yych) {
		case '/':	goto yy12;
		case '<':	goto yy10;
		case '>':	goto yy9;
		default:	goto yy7;
		}
yy12:
		++*p;
		yych = (char)**p;
		switch (yych) {
		case '<':	goto yy10;
		case '>':	goto yy9;
		case 'D':
		case 'd':	goto yy14;
		case 'P':
		case 'p':	goto yy13;
		case 'T':
		case 't':	goto yy15;
		default:	goto yy7;
		}
yy13:
		++*p;
		yych = (char)**p;
		switch (yych) {
		case '<':	goto yy10;
		case '>':	goto yy27;
		case 'R':
		case 'r':	goto yy26;
		default:	goto yy7;
		}
yy14:
		++*p;
		yych = (char)**p;
		switch (yych) {
		case '<':	goto yy10;
		case '>':	goto yy9;
		case 'I':
		case 'i':	goto yy22;
		default:	goto yy7;
		}
yy15:
		++*p;
		yych = (char)**p;
		switch (yych) {
		case '<':	goto yy10;
		case '>':	goto yy9;
		case 'I':
		case 'i':	goto yy16;
		default:	goto yy7;
		}
yy16:
		++*p;
		yych = (char)**p;
		switch (yych) {
		case '<':	goto yy10;
		case '>':	goto yy9;
		case 'T':
		case 't':	goto yy17;
		default:	goto yy7;
		}
yy17:
		++*p;
		yych = (char)**p;
		switch (yych) {
		case '<':	goto yy10;
		case '>':	goto yy9;
		case 'L':
		case 'l':	goto yy18;
		default:	goto yy7;
		}
yy18:
		++*p;
		yych = (char)**p;
		switch (yych) {
		case '<':	goto yy10;
		case '>':	goto yy9;
		case 'E':
		case 'e':	goto yy19;
		default:	goto yy7;
		}
yy19:
		++*p;
		yych = (char)**p;
		switch (yych) {
		case '<':	goto yy10;
		case '>':	goto yy20;
		default:	goto yy7;
		}
yy20:
		++*p;

		{ return WORD3; }

yy22:
		++*p;
		yych = (char)**p;
		switch (yych) {
		case '<':	goto yy10;
		case '>':	goto yy9;
		case 'V':
		case 'v':	goto yy23;
		default:	goto yy7;
		}
yy23:
		++*p;
		yych = (char)**p;
		switch (yych) {
		case '<':	goto yy10;
		case '>':	goto yy24;
		default:	goto yy7;
		}
yy24:
		++*p;

		{ return WORD4; }

yy26:
		++*p;
		yych = (char)**p;
		switch (yych) {
		case '<':	goto yy10;
		case '>':	goto yy9;
		case 'E':
		case 'e':	goto yy29;
		default:	goto yy7;
		}
yy27:
		++*p;

		{ return WORD1; }

yy29:
		++*p;
		yych = (char)**p;
		switch (yych) {
		case '<':	goto yy10;
		case '>':	goto yy30;
		default:	goto yy7;
		}
yy30:
		++*p;

		{ return WORD2; }

	}


    }
}

// prepare e-mail to use with any NLP algorithm
char *prepare_text(char *filename) 
{

    char cleartext[500000];
    char *p = ReadLines(filename);
    char *last = p;
    int sz;
    int result=0;

    while(!result )
    	switch (parse_clear(&p, &last)) 
	{
// parse p tag 
	       case WORD1:
       		     sz = p - last - 4;
		    char tmp2[2048];		
	            snprintf(tmp2,2047,"%.*s\n", sz, last);

		    if(strlen(tmp2)>10)
	    	    {			
			remove_specials_chars (tmp2);
	    		strncat(cleartext,tmp2,500000-1);
	    	    }
                    break;

        	case WORD2:
            	    sz = p - last - 6;
	    	    char tmp3[2048];	
// pre tag	
            	    snprintf(tmp3,2047,"%.*s\n", sz, last);

	    		if(strlen(tmp3)>10)
	    		{		
				remove_specials_chars (tmp3);
	    			strncat(cleartext,tmp3,500000-1);
	    		}
            	   break;
// title tag
        case WORD3:
            	   sz = p - last - 8;
	    	   char tmp4[2048];		
            	   snprintf(tmp4,2047,"%.*s\n", sz, last);

	    	   if(strlen(tmp4)>10)
	    	   {	
			remove_specials_chars (tmp4);
	    		strncat(cleartext,tmp4,500000-1);
	    	   }
            	   break;

// div tag
        case WORD4:
            	  sz = p - last - 6;
	    	  char tmp5[2048];		
            	  snprintf(tmp5,2047,"%.*s\n", sz, last);
	    	  if(strlen(tmp5)>16)
	    	  {	
			remove_specials_chars (tmp5);
	    		strncat(cleartext,tmp5,500000-1);
	    	  }
            	  break;

        case END:
            puts("End line\n");
	    result=1;	
            break;
    }

    return cleartext;
}
