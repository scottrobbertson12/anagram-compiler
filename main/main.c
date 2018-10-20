#include<stdio.h>

#include<common.h>
#include<tstring.h>
#include<ttypes.h>
#include<token.h>
#include<lex.h>

int main(int argc, char* argv[]){
	if(argc > 1){
		printf("%s\n", argv[1]);
		FILE* codefile = fopen(argv[1],"r");
		fseek(codefile, 0L,  SEEK_END); int chars = ftell(codefile); rewind(codefile);
		char* code = malloc(sizeof(char) * chars + 1);
	       	if((fread(code,sizeof(char),chars,codefile) == 0)){
			printf("Error reading file %s\n", argv[1]);
			exit(1);
		}

		string s = string_new(code);
		DARRAY(token) tokens = get_tokens(s);
		FOR(i,0,tokens->count,
				string v = token_print(DARRAY_GET(token,tokens,i));
				printf("%s\n", c_string(v));
				string_delete(v);
		);


		DARRAY_DELETE(token,tokens);	
		string_delete(s);
		keywords_delete();
		return RETURN_NO_ERROR;
	} else {
		printf("USAGE %s filename\n",argv[0]);
	}
}
