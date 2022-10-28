#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE 80

struct Process{
    char* name;
    int period;
    int exec_time;
    struct Process *next;
};
typedef struct Process Process;

void parse_input(char *process, char **parsed_process);
void split_lines(char *line, char **arguments);
int file_read(char *filename, char **arguments);
void append(Process** head_ref, char* name, int period, int exec_time);
void printList(Process *node);

int main(int argc, char *argv[]){

    if(argc == 2){

        Process* head = NULL;

        int total_time;
        int file_linesCont = 0;
        int file_totalLines;
        char *all_lines[MAX_LINE]; //total lines aqui ta como zero, da segmentation fault
        char *struct_fields[3];

        file_totalLines = file_read(argv[1], all_lines);

        while(file_linesCont < file_totalLines){
            if(file_linesCont == 0){ //primeira linha = tempo total
                total_time = atoi(all_lines[0]);
            }
            else{
                parse_input(all_lines[file_linesCont], struct_fields);
                append(&head, struct_fields[0], atoi(struct_fields[1]), atoi(struct_fields[2]));
            }
            
            file_linesCont++;

        }
        printf("Tempo total: %d\n", total_time);
        printList(head);
    }
    else if(argc > 2){
        printf("Numero de argumentos invalido\n");
    }
    else{
        printf("Numero de argumentos invalido\n");
    }

}

//recebe cada linha e trata os " "
void parse_input(char *process, char **parsed_process)
{
    char *separator;
    int arg_count = 0;

    int size =  sizeof process / sizeof process[0];

    separator = strtok(process, " ");
    
    while( separator != NULL) {
        parsed_process[arg_count] = malloc(size * sizeof(char));
		parsed_process[arg_count] = strdup(separator);
        separator = strtok(NULL, " ");
        arg_count++;
    }
}

int file_read(char *filename, char **arguments)
{
    char* readline = NULL;
    int cont = 0;
    size_t len = 0;

    FILE *fp = fopen (filename, "r");

    while ((getline(&readline, &len, fp)) != -1) {
        
        char *separator = strtok(readline, "\n");
        arguments[cont] = strdup(separator);
        
        cont++;
    }
    

    fclose(fp);

    return cont;
}

void append(Process **head_ref, char *name, int period, int exec_time)
{
    Process *new_node = (Process*) malloc(sizeof(Process));
 
    Process *last = *head_ref;
 
    new_node->name  = name;
    new_node->period = period;
    new_node->exec_time = exec_time;
 
    new_node->next = NULL;
 
    if (*head_ref == NULL)
    {
       *head_ref = new_node;
       return;
    }

    while (last->next != NULL){
        last = last->next;
    }
 
    last->next = new_node;

}

void printList(Process *node)
{
    while (node != NULL){
        printf("Nome: %s ", node->name);
        printf("Periodo: %d ", node->period);
        printf("Tempo de execucao: %d ", node->exec_time);
        printf("\n");
        node = node->next;
    }
}