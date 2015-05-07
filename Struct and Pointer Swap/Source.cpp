#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct IDNEXT {
	int ID;
	struct IDNEXT *next;
};

//struct IDNEXT *glo_idnext = NULL;
//struct IDNEXT *bottom = glo_idnext;
//int size = 0;

void swap(struct IDNEXT **p1, struct IDNEXT **p2){
	struct IDNEXT *tmp;
	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

void printIDNEXT(struct IDNEXT *idnext){
	for (;idnext != NULL; idnext = idnext->next){
		printf("address %p ID %d\n", idnext, idnext->ID);
	}
	//printf("address %p next %p\n", idnext, idnext->next);
}

void printIDNEXT_saiki(struct IDNEXT *idnext){
	if (idnext == NULL) return;
	printf("address %p ID %d\n", idnext, idnext->ID);
	printIDNEXT_saiki(idnext->next);
	//printf("address %p next %p\n", idnext, idnext->next);
}

void add(struct IDNEXT **idnext, int num){
	int i;
	struct IDNEXT *bottom = *idnext;
	if (*idnext == NULL) {
		*idnext = (struct IDNEXT*)malloc(sizeof(struct IDNEXT*));
		(*idnext)->ID = rand() % 1000;
		(*idnext)->next = NULL;
		num--;
		bottom = (*idnext);
	}
	else {
		for (; bottom->next != NULL; bottom = bottom->next);
	}
	for (i = 0; i < num; i++) {
		bottom->next = (struct IDNEXT*)malloc(sizeof(struct IDNEXT*));
		bottom = bottom->next;
		bottom->ID = rand() % 1000;
		bottom->next = NULL;
	}
}

void merge(struct IDNEXT *left, struct IDNEXT *right, struct IDNEXT **new_idnext){
	struct IDNEXT *new_bottom = NULL;
	if (left->ID < right->ID) {
		*new_idnext = new_bottom = left;
		left = left->next;
	}
	else {
		*new_idnext = new_bottom = right;
		right = right->next;
	}

	while (left != NULL && right != NULL){
		if (left->ID < right->ID){
			new_bottom->next = left;
			left = left->next;
			new_bottom = new_bottom->next;
		}
		else {
			new_bottom->next = right;
			right = right->next;
			new_bottom = new_bottom->next;
		}
	}
	while (left != NULL){
		new_bottom->next = left;
		left = left->next;
		new_bottom = new_bottom->next;
	}
	while (right != NULL){
		new_bottom->next = right;
		right = right->next;
		new_bottom = new_bottom->next;
	}
	new_bottom->next = NULL;
}

void merge_sort(struct IDNEXT *idnext, struct IDNEXT **new_idnext, int size){
	if (size <= 1) {
		idnext->next = NULL;
		*new_idnext = idnext;
		return;
	}
	struct IDNEXT *idnext_left, *idnext_right, *new_idnext_left, *new_idnext_right;
	int half_size = size / 2;
	idnext_left = idnext_right = idnext;
	int i;
	for (i = 0; i < half_size; i++) {
		idnext_right = idnext_right->next;
	}
	merge_sort(idnext_left, &new_idnext_left, half_size);
	merge_sort(idnext_right, &new_idnext_right, half_size);
	
	merge(new_idnext_left, new_idnext_right, new_idnext);
}

int main() {

	srand((unsigned)time(NULL));
	struct IDNEXT *idnext = NULL;
	struct IDNEXT *bottom = NULL;

	add(&idnext, 8);
	add(&idnext, 8);
	struct IDNEXT *new_idnext = NULL;
	merge_sort(idnext, &new_idnext, 16);
	idnext = new_idnext;

	printf("glo_idnext\n");
	printIDNEXT_saiki(idnext);
}