#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>

#define N 76
typedef struct node{ 
	char *dstnet[20];
	int mask;
	char *nexhop[20];
	struct timeval tv; 
	struct node *next;
}listnode;

listnode* hash_table[N];

int hash_init_hashtable(){
	int i;
	for(i=0; i<N; i++){
		listnode *new_listnode = malloc(sizeof(listnode));
		if(new_listnode != NULL)
			hash_table[i] = new_listnode;
		else
			printf("malloc failed\n");
	}
	return 0;
}
/*rookie route add 192.168.204.1 32 2.2.2.2*/
int hash_add_route(char *dstnet, int mask, char *nexhop)
{
	int key = hash_fuc(dstnet);
	printf("%d\n", key);
	listnode *p = hash_table[key];
	listnode *new_listnode = malloc(sizeof(listnode));
	struct timeval now;
	gettimeofday(&now,NULL);
	if( new_listnode != NULL){
		new_listnode->next = NULL;
		memcpy(new_listnode->nexhop,nexhop,strlen(nexhop));
		memcpy(new_listnode->dstnet,dstnet,strlen(dstnet));
		new_listnode->mask = mask;
		memcpy(&(new_listnode->tv),&now,sizeof(struct timeval));
	} else{
		printf("kmalloc failed");
		return -1;
	}
	
	if( p->next == NULL){
		hash_table[key]->next = new_listnode;
	}else{
		listnode *tmp = p->next;
		while(tmp->next != NULL){
			tmp = tmp->next;
		}
		tmp->next = new_listnode;
	}
	return 0;
}

/*no rookie route 192.168.204.1 32*/
int hash_del_route(char *dstnet, int mask)
{
	int key = hash_fuc(dstnet);
	listnode *p = hash_table[key]->next;
	listnode *pre = hash_table[key];
	if(p == NULL){
		printf("empty del");
		return -1;
	}else{
		while(p != NULL){
			if(strcmp(dstnet,p->dstnet) == 0 && mask == p->mask){
				pre->next = p->next;
				free(p);
				break;
			}else{
				pre = p;
				p = p->next;
			}
		}
	}
	return 0;
}

/*show rookie route*/
void hash_show_route()
{
	printf("    destnet         mask       nexhop\n");
	listnode *p = NULL;
	int i;
	for(i=0; i<N; i++){
		p = hash_table[i]->next;
			while(p != NULL){
				printf("%15s   %4d      %s\n",p->dstnet,p->mask, p->nexhop);  
				// get i;
				// get tmp->nexhop;
				p = p->next;
			}
	}
	return ;
}

/*rookie route add 192.168.204.1 32 1.1.1.1*/
int hash_update_route(char *dstnet, int mask, char *nexhop){
	int key = hash_fuc(dstnet);
	listnode *tmp = hash_table[key]->next;
	while(tmp != NULL){
		if(strcmp(tmp->dstnet,dstnet) ==0 && mask == tmp->mask){
			memset(tmp->nexhop,'\0',strlen(tmp->nexhop));
			memcpy(tmp->nexhop,nexhop,strlen(nexhop));
			tmp->mask = mask;
		}
		tmp = tmp->next;
	}
	return 0;
}

/*no rookie routing*/
int hash_del_all(){
	int i;
	for(i=0; i<N; i++){
		listnode *tmp = NULL;
		listnode *p = hash_table[i]->next;
		while(p != NULL){
			tmp = p;
			p = p->next;
			free(tmp);
		}
		hash_table[i]->next = NULL;
	} 
	return 0;
}

int hash_check_old(int interval){

	/* while loop */
	listnode *p = NULL;
	int i;
	for(i=0; i<33; i++){
		p = hash_table[i];
		if(p != NULL){
			listnode *tmp = p;
			listnode *pre = tmp;
			struct timeval now; 
			gettimeofday(&now,NULL);
			while(tmp != NULL){
				pre = tmp;
				if(now.tv_sec - tmp->tv.tv_sec >= interval){
					listnode *freenode = tmp;
					pre->next = tmp->next;
					free(freenode);
				}
				tmp = pre->next;
			}
		}
	}

	return 0;
}


unsigned long strtou32(char *str) 
{
	unsigned long temp=0;
	unsigned long fact=1;
	unsigned char i;
	unsigned char len=strlen(str);
	char *tmp_str = malloc(len*sizeof(char));
	if(tmp_str == NULL){
		printf("malloc failed\n");
		return -1;
	}
	int j=0;
	for(i=0; i<len; i++){
		if(str[i] != '.'){
			tmp_str[j++] = str[i];
		}
	}
	tmp_str[j] ='\0';

	for(i=strlen(tmp_str); i>0; i--){
		temp += ((tmp_str[i-1]-0x30)*fact);
		fact*=10;
	}
	free(tmp_str);
	return temp;
}

int hash_fuc(char *ip)
{
	int i, sum, len; 
  	i=0;
  	sum = 0;
  	len = strlen(ip);
  	unsigned long IP = strtou32(ip);

  	//unsigned long opmask = oxFFFFFFFF<<(32-mask);
  	//unsigned long net = IP&opmask;
    while(IP/10){
    	sum += IP%10;
    	IP/=10;
    }
  	return sum%=N;      //N是记录的条数
}

// int main(int argc, char** argv){
// 	hash_init_hashtable();
// 	hash_add_route("192.168.2.1",32,"192.168.5.1");
// 	hash_add_route("192.168.2.0",24,"192.168.5.1");
// 	hash_add_route("192.168.89.87",32,"192.168.5.1");
// 	hash_add_route("192.168.89.0",24,"192.168.5.1");
// 	hash_show_route();
// 	hash_update_route("192.168.2.1",32,"192.168.1.1");
// 	hash_del_route("192.168.89.87",32);
// 	hash_show_route();
// 	hash_del_all();
// 	hash_show_route();
// 	return 0;
// }