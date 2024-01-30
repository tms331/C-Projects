#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

// Struct to hold data and the pointer to the next element.
struct node {
    char data;
    struct node* next;
};


// Append the new element to the start of the stack
struct node* push (struct node* stack, char data) {
    struct node* newElement = (struct node*)malloc(sizeof(struct node));

    newElement->data = data;
    newElement->next = stack;
    stack = newElement;


    return stack;
}


bool equal(char topElement, char popElement){

    if(topElement == '(' && popElement == ')'){
        return true;

    }else if(topElement == '[' && popElement == ']'){
        return true;

    }else if(topElement == '{' && popElement == '}'){
        return true;

    }else if(topElement == '<' && popElement == '>'){
        return true;

    }else{
        return false;
    }

}


// Remove element from the top of the stack
char pop ( struct node** stack ) {

    struct node* temp;
    char tmp;

    if (*stack != NULL) {
        temp = *stack;
        tmp = temp->data;
        *stack = temp->next;
        free(temp);

        return tmp;
    } else {
        return '\0';
    }

}


void free_memory(struct node* stack){

    while (stack != NULL){
        //printf("%c", stack->data);
        struct node* tmp = stack;
        stack = tmp->next;
        free(tmp);
    }

}


int main(int argc, char* argv[]) {

    char input[10] = "{([";

    struct node* root = NULL;
    bool balanced = true;


    for(int i = 0; i < sizeof(input); i++){

        switch(input[i]) {
            case '<' :
            case '(' :
            case '[' :
            case '{' :
                root = push(root, input[i]);
                break;

            case '>' :
            case ')' :
            case ']' :
            case '}' :
                if (!equal(pop(&root), input[i])){
                    balanced = false;
                }
                break;
        }
    }


    if(root != NULL){
        balanced = false;
        free_memory(root);
    }


    printf ( balanced ? "yes" : "no" );
}