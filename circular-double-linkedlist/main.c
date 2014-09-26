#include <stdio.h>
#include <stdlib.h>	//Dynamic memory allocation
#include <string.h>
#include <time.h>
#include "my402list.h"
#define sort "sort"
#define POS "?,???,???.??"
#define NEG "(?,???,???.?\?)"

typedef struct My402Elem {
	char sign;
	time_t date;
	float amount;
	char desc[1026];
} My402Elem;

void FileRead(int argc, char *argv[], My402List *mylist)
{
	FILE *fp;
	char buf[1026];
	char *start_ptr, *tab_ptr, *temp_ptr;
	My402ListElem *iter_ptr;
	int count, flag;

	if (argc != 3 || strcmp(argv[1], sort)) {
		printf("error: Input Format is wrong.\n");
		exit(1);
	}

	if (NULL == (fp = fopen(argv[2], "r"))) {
		printf("error: Could not open file.\n");
		exit(1);
	}
	
	while(fgets(buf, sizeof(buf), fp) != NULL) {
//		printf("%s", buf);
		My402Elem *myelem;
		if (NULL == (myelem = malloc(sizeof(My402Elem)))) {
			printf("error: Could not create My402Elem.\n");
			exit(1);
		}

		if (strlen(buf) > 1024) {
			printf("error: This line is over 1024 units.\n");
			exit(1);
		}
		
		count = flag = 0;
		start_ptr = buf;
		tab_ptr = strchr(start_ptr, '\t');
		while (tab_ptr != NULL) {
			*tab_ptr++ = '\0';
			if (count == 0) {
				if (tab_ptr - start_ptr == 2) {
					myelem->sign = *start_ptr;
//					printf("%c\n", myelem->sign);
				} else {
					printf("error: sign format is wrong.\n");
					exit(1);
				}
			} else if (count == 1) {
				if (tab_ptr - start_ptr < 12) {
					myelem->date = atoi(start_ptr);
//					printf("%d\n", (unsigned int)myelem->date);
				} else {
					printf("error: date format is wrong.\n");
					exit(1);
				}
			} else if (count == 2) {
				myelem->amount = atof(start_ptr);
				if (myelem->sign == '-') {
					myelem->amount = -myelem->amount;
				}
//				printf("%f\n", myelem->amount);
				strncpy(myelem->desc, tab_ptr, strlen(tab_ptr) + 1);
				temp_ptr = strchr(myelem->desc, '\n');
				*temp_ptr = '\0';
//				printf("Input: %s\n", myelem->desc);
			}

			start_ptr = tab_ptr;
			tab_ptr = strchr(start_ptr, '\t');
			count++;
		}

//		printf("before insert: %d\n", mylist->num_members);
		if (My402ListEmpty(mylist)) {
			My402ListAppend(mylist, myelem);
			iter_ptr = My402ListFirst(mylist);
		} else {
			for (iter_ptr = My402ListFirst(mylist); iter_ptr != NULL; iter_ptr = My402ListNext(mylist, iter_ptr)) {
				if (myelem->date < ((My402Elem*)(iter_ptr->obj))->date) {
					My402ListInsertBefore(mylist, myelem, iter_ptr);
					flag++;
					break;
				} else if (myelem->date == ((My402Elem*)(iter_ptr->obj))->date) {
					printf("error: identical timestamp.\n");
					exit(1);
				}
			}
			if (flag == 0) {
				My402ListAppend(mylist, myelem);
				iter_ptr = My402ListLast(mylist);
			}
		}
//		printf("after insert: %d\n", mylist->num_members);
//		printf("Insert: %s\n", ((My402Elem*)(iter_ptr->obj))->desc);
	}

	if (fclose(fp) != 0) {
		printf("error: Could not close file %s\n", argv[1]);
		exit(1);
	}
}

void FilePrint(My402List *mylist)
{
	float balance = 0;
	My402ListElem *iter_ptr = NULL;
	My402Elem *elem_ptr = NULL;
	struct tm *tm_temp;
	char time_str[16];

	printf("+-----------------+--------------------------+----------------+----------------+\n");
	printf("|       Date      | Description              |         Amount |        Balance |\n");
	printf("+-----------------+--------------------------+----------------+----------------+\n");
	for (iter_ptr = My402ListFirst(mylist); iter_ptr != NULL; iter_ptr = My402ListNext(mylist, iter_ptr)) {
		printf("| ");
		elem_ptr = (My402Elem*)iter_ptr->obj;		
		// Convert time_t to tm as UTC time
		if (NULL == (tm_temp = gmtime(&elem_ptr->date))) {
			fprintf(stderr, "Could not convert time format.\n");
			exit(1);
		}
		// Format time as string
		strftime(time_str, 16, "%a %b %d %G", tm_temp);
		printf("%s", time_str);
		printf(" | ");
		if (strlen(elem_ptr->desc) > 24) {
			elem_ptr->desc[24] = '\0';
		}
		printf("%-24s", elem_ptr->desc);
		printf(" | ");
		if (elem_ptr->amount > 0 && elem_ptr->amount < 10000000) {
			printf("%14.2f", elem_ptr->amount);
		} else if (elem_ptr->amount >= 10000000) {
			printf("%14s", POS);
		} else if (elem_ptr->amount < 0 && elem_ptr->amount > -10000000) {
			printf("(%12.2f)", -elem_ptr->amount);
		} else if (elem_ptr->amount <= -10000000) {
			printf("%14s", NEG);
		}
		printf(" | ");
		balance = balance + elem_ptr->amount;
		if (balance > 0 && balance < 10000000) {
			printf("%14.2f", balance);
		} else if (balance >= 10000000) {
			printf("%14s", POS);
		} else if (balance < 0 && balance > -10000000) {
			printf("(%12.2f)", -balance);
		} else if (balance <= -10000000) {
			printf("%14s", NEG);
		}
		printf(" |\n");
	}
	printf("+-----------------+--------------------------+----------------+----------------+\n");
}

int main(int argc, char *argv[])
{
	My402List mylist;
	if (!My402ListInit(&mylist)) {
		printf("error: List creation failed.\n");
	}
	FileRead(argc, argv, &mylist);
//	printf("total num: %d\n", mylist.num_members);
	FilePrint(&mylist);

	return 0;
}
