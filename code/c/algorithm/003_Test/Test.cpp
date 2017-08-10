#include <stdio.h>
#include <string.h>
#include <stdlib.h>
bool isIsomorphic(char* s, char* t) {
	int len = strlen(s);

    int *dict = (int *)malloc(26*sizeof(int));
	int i,d1,d2,temp;
	for(i=0;i<26;i++){
		dict[i] = -1;
	}
	
	for(i=0;i<len;i++){
		d1 = s[i]-'a';
		d2 = t[i]-'a';
		
		if(dict[d1]==-1){
			dict[d1] = d2;
		}else if(dict[d1]!=d2){
			return false;
		}
	}
	int *dict2 = (int *)malloc(26*sizeof(int));
	for(i=0;i<26;i++){
		dict2[i] = -1;
	}
	for(i=0;i<26;i++){
		printf("dict[%d]=%d\n",i, dict[i]);
        if(dict[i]==-1){
            continue;
        }

		

		if(dict2[dict[i]]==-1){
			dict2[dict[i]] = i;
		}else if(dict2[dict[i]]!=i){
			return false;
		}
	}
	
	return true;
}



int main()
{
	printf("%d\n", isIsomorphic("bar","foo"));
	return 0;
}