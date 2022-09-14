//lista encadeada

typedef struct{
    int value;
    int *next;
} node;

typedef struct{
    node *list;
    int *head, *tail;
    int maxSize;
    int atualSize;
} list;

list createList(){
    list newList;
    newList.maxSize = 8;
    newList.atualSize = 0;
    newList.list = (node*) malloc(sizeof(node)*newList.maxSize);
    return newList;
} 

void appendBackList(list* list_, int newValue){
    node newNode;
    if(list_->atualSize + 1 == list_->maxSize){
        list_->list = (node*) realloc(list_->list, pow(list_->maxSize, 2)*sizeof(node));
        list_->maxSize += list_->maxSize;
    }
}

void appendFrontList(){

}

void popList(){

}

void searchlist(){
    
}

int main(void){
    list myList = createList();
    return 1;
}