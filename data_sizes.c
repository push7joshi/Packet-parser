#include<stdio.h>

struct record{
	char first_name[20];
	char last_name[20];
	char middle_initial;
	long account_num;
	short account_type;
	double account_balance;
};

void print_size(){
	printf("Printing sizes of the basic data structures\n");
	printf("int: %ld \n",sizeof(int));
	printf("short: %ld \n",sizeof(short));
	printf("long: %ld \n",sizeof(long));
	printf("float: %ld \n",sizeof(float));
	printf("double: %ld \n",sizeof(double));
	printf("char: %ld \n",sizeof(char));
	printf("void pointer: %ld \n",sizeof(void*));

	printf("\nPrinting size of the struct record\n");
	printf("struct record: %ld \n",sizeof(struct record));
};

void populate_record(){
	struct record r;
	strcpy(r.first_name,"Adam");
	strcpy(r.last_name,"Rajagopalan");
	r.middle_initial = 'A';
	r.account_num = 999999;
	r.account_type = 10;
	r.account_balance = 100.99;

	printf("\n\nPrinting struct elements\n");
	printf("Name: %s %c. %s\n", r.first_name, r.middle_initial, r.last_name);
	printf("Acc#: %ld\n", r.account_num);
	printf("Acc Type: %hd\n",r.account_type);
	printf("Balance: %f\n",r.account_balance);
	char* c = (char*)&r;
	char d = (unsigned int)*c;
	printf("---------%x\n",d);
};

void read_data_from_char_array(){
	char data_record[] = "\x41\x64\x61\x6d\x00\x7f\x00\x00\x30"
"\x57\xf1\x6c\xff\x7f\x00\x00\x00\x00"
"\x00\x00\x41\x76\x69\x76\x00\x4b\xf1"
"\x6c\xff\x7f\x00\x00\x85\xb8\x7e\xc5"
"\xc3\x91\x98\xa0\x4a\x00\x00\x00\x00"
"\x00\x00\x00\x32\x79\x06\x00\x00\x00"
"\x00\x00\x0a\x00\x00\x00\x00\x00\x00"
"\x00\x8d\x97\x6e\x12\x83\x00\xa0\x40";
	struct record r = *((struct record*)data_record);
	printf("\n\nPrinting struct elements\n");
	printf("Name: %s %c. %s\n", r.first_name, r.middle_initial, r.last_name);
	printf("Acc#: %ld\n", r.account_num);
	printf("Acc Type: %hd\n",r.account_type);
	printf("Balance: %f\n",r.account_balance);
	char* c = ((char*)&r);
	printf("%s\n",c);
}

int main(){
	print_size();
	populate_record();
	read_data_from_char_array();
	
}
