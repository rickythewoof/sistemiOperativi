#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "linked_list.h"

#define MATRIX_SIZE 4

typedef struct {
  ListItem list;
  int info;
} IntListItem;

// print method (late binding)
void IntListItem_print(struct ListItem* item){
  printf("[int] %d ",((IntListItem*)item)->info);
}

// vtable for int list (an INSTANCE)
ListItemOps int_list_ops={
  .dtor_fn=0,
  .print_fn=IntListItem_print
};

typedef struct{
  ListItem list;
  ListHead info;
} ListListItem;

void ListListiItem_print(struct ListItem* item){
  printf("[LIST] {\n");
  ListListItem* aux = (ListListItem*) item;
  List_print(&aux->info);
  printf("}\n");
}

ListItemOps list_list_ops={
  .print_fn = ListListiItem_print,
  .dtor_fn = 0
};

typedef struct {
  ListItem list;
  float info;
} FloatListItem;

// print method (late binding)
void FloatListItem_print(struct ListItem* item){
  printf("[float] %f ",((FloatListItem*)item)->info);
}

// vtable for float list (an INSTANCE)
ListItemOps float_list_ops={
  .dtor_fn=0,
  .print_fn=FloatListItem_print
};

int main(int argc, char** argv) {
  ListHead head;
  List_init(&head);
  for(int i = 0; i < MATRIX_SIZE; i++){
    ListListItem* list = malloc(sizeof(ListListItem));
    ListItem_construct((ListItem*)list, &list_list_ops);
    List_init(&list->info);
    for(int j = 0; j < MATRIX_SIZE; j++){
      ListItem* item = NULL;
      if(j&0x1){
        IntListItem* new_elem = malloc(sizeof(IntListItem));
        ListItem_construct((ListItem*)new_elem, &int_list_ops);
        new_elem->info = i+j;
        item = (ListItem*) new_elem;
      } else{
          FloatListItem* new_elem = malloc(sizeof(FloatListItem));
          ListItem_construct((ListItem*)new_elem, &float_list_ops);
          new_elem->info = (i+j)/1.0;
          item = (ListItem*) new_elem;
      }
      List_insert(&list->info, list->info.last,item);
    }
    List_insert(&head, head.last, (ListItem*)list);
  }

  List_print(&head);
}
