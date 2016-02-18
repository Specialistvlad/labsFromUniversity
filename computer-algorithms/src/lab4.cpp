#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Удобный макрос для перебора списка 
#define foreach_list(name, from, to) \
	for( list_element_t *name = from; name != to; name = (list_element_t *)name->next )

// Структуры данных
// Элемент
typedef struct {
	void *next;
	int val;
} list_element_t;

//Список
typedef struct {
	list_element_t *front, *back;
} list_t;


// Инициализация списка
void list_init(list_t *l)
{
	l->front = NULL;
	l->back  = NULL;
}

// Добавить в список
void list_append(list_t *l, int val)
{
	list_element_t *el = NULL;
	if( !l->front ) {
		el = l->front = (list_element_t *)malloc(sizeof(list_element_t));

		if( !l->back )
			l->back = l->front;

	} else {
		el = (list_element_t *)malloc(sizeof(list_element_t));
		l->back->next = el;
		l->back = el;
	}

	el->next = NULL;
	el->val = val;
}

// Поменять местами
void list_swap(list_element_t *el1, list_element_t *el2)
{
	if( el1 == el2 || !el1 || !el2 )
		return;

	int t = el1->val;
	el1->val = el2->val;
	el2->val = t;
}

// Удалить из списка
void list_remove(list_t *l,  list_element_t *prev, list_element_t *el)
{
	if( prev == el )
		return;

	/* remove front element? */
	if( !prev ) {
		void *next = l->front->next;
		free(l->front);


		if( l->front == l->back ) {
			l->front = l->back = (list_element_t *)next;

		} else {
			l->front = (list_element_t *)next;;
		}
		return;
	}

	prev->next = el->next;
	if( l->back == el )
		l->back = prev;
}


// Вставить в список
void list_insert(list_t *l, list_element_t *after, int val)
{
	/* to front? */
	if( !after ) {
		list_element_t *f = l->front;
		l->front = (list_element_t *)malloc(sizeof(list_element_t));
		l->front->next = f;
		l->front->val = val;
		return;
	}

	list_element_t *next = (list_element_t *)after->next;
	list_element_t *el = (list_element_t *)(after->next = malloc(sizeof(list_element_t)));

	if( after == l->back )
		l->back = el;

	el->next = next;
	el->val = val;
}

// Сортировка списка
void list_sort(list_t *l)
{
	foreach_list(el, l->front, NULL) {
		list_element_t *min_el = el;
		foreach_list(el_b, ((list_element_t *)el->next), NULL) {
			if( el_b->val < min_el->val )
				min_el = el_b;
		}

		list_swap(el, min_el);
	}
}

// Очистить список
void clear_list(list_t *l)
{
	list_element_t *prev = NULL;
	foreach_list(el, l->front, NULL) {
		if( prev )
			free(prev);

		prev = el;
	}

	if( prev )
		free(prev);

	l->back = l->front = NULL;
}

// Вывести список
void print_list(list_t *l)
{
	foreach_list(el, l->front, NULL) {
		printf("%d ", el->val);
	}
	printf("\n\n");
}

int main()
{
	srand(time(NULL)); //randomize random generator

	int remove_me = 15;
	int maxval = 0;
	char flg = 0;
	list_t l;
	list_init(&l);


	/*** chapter 1 ***/
	// fill random values
	for( int i = 0; i < 20; ++i )
		list_append(&l, rand() % 20);

	// foreach and print
	foreach_list(el, l.front, NULL) {
		printf("%d ", el->val);
		if( maxval < el->val )
			maxval = el->val;
	}
	printf("\n\n");

	/*** chapter 2 ***/
	// swap first and last
	list_swap(l.front, l.back);
	printf("Last and first element has been replaced\n");
	print_list(&l);

	/*** chapter 3 ***/
	// find element with value \remove_me and remove
	for( list_element_t *el = l.front, *prev = NULL; el != NULL; prev = el, el = (list_element_t *)el->next ) {
		if( el->val == remove_me ) {
			printf("Element with value %d has been removed at %p\n", el->val, el);
			list_remove(&l, prev, el);
			flg = 1;
			break;
		}
	}

	// dump
	if( !flg )
		printf("Can't remove %d value - not found\n", remove_me);
	print_list(&l);



	/*** chapter 4 ***/

	// insert after value > remove_me
	flg = 0;
	foreach_list(el, l.front, NULL) {
		if( el->val > remove_me ) {
			list_insert(&l, el, maxval);
			printf("Max value %d inserted after %d(%p)\n", maxval, el->val, el);
			flg = 1;
			break;
		}
	}

	/* dump */
	if( !flg )
		printf("Can't insert %d after %d value - not found\n", maxval, remove_me);
	print_list(&l);

	/*** chapter 5 ***/
	list_sort(&l);
	printf("List was sorted\n");

	// dump
	print_list(&l);
	clear_list(&l);
	return 0;
}
