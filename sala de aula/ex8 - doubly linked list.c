//lista encadeada

typedef struct{
    int value;
    int *next;
    int *last;
} linkedNode;

typedef struct{
    linkedNode *list;
    int *head, *tail;
    int maxSize;
    int atualSize;
} linkedList;

linkedList createLinkedList(){
    linkedList newList;
    newList.maxSize = 8;
    newList.atualSize = 0;
    newList.list = (linkedNode*) malloc(sizeof(linkedNode)*newList.maxSize);
    return newList;
} 

void append(linkedList* list_, int newValue){
    linkedNode newNode;
    if(list_->atualSize + 1 == list_->maxSize){
        list_->list = (linkedNode*) realloc(list_->list, pow(list_->maxSize, 2)*sizeof(linkedNode));
        list_->maxSize += list_->maxSize;
    }
}

void pop(){

}

void add(){
    
}

void searchlist(){
    
}

int main(void){
    linkedList myList = createLinkedList();
    return 1;
}