#include<stdio.h>

int main(int argc, char** argv){
	if(argc < 3){
		puts("few parameters");
	}
	freopen(argv[1],"r",stdin);
	freopen(argv[2],"w",stdout);

	char s[200];
	puts("extern \"C\"{");
	puts("#include \"int.h\"");
	puts("}");
	puts("#include \"main.cpp\"");
	while(gets(s)!=NULL){
		puts(s);
	}
	return 0;
}
