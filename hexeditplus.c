#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
 
bool debug = false;
int unitSize = 1;
char fileName[128] = "";
int memCount = 0;

typedef struct {
  char debug_mode;
  char file_name[128];
  int unit_size;
  unsigned char mem_buf[10000];
  size_t mem_count;
  /*
   .
   
   Any additional fields you deem necessary
  */
} state;

 void toggleDebugMode(){
    if(!debug){
        debug = true;
        printf("Debug flag now on\n");
    }
    else{
        debug = false;
        printf("Debug flag now off\n");
    }
    "";
 }
 void SetFileName(){
    "";
 }
void SetUnitSize(){
    "";
}
void LoadIntoMemory(){
    printf("Not implemented yet\n");
}
void ToggleDisplayMode(){
    printf("Not implemented yet\n");
}
void FileDisplay(){
    printf("Not implemented yet\n");
}
void MemoryDisplay(){
    printf("Not implemented yet\n");
}
void SaveIntoFile(){
    printf("Not implemented yet\n");
}
void MemoryModify(){
    printf("Not implemented yet\n");
}
void Quit(){
    "";
}


 struct fun_desc
 {
    char *name;
    char (*fun)(char);
 };
 
 void menu(){
    if(debug){
        printf("Unit size is %d\n", unitSize);
        printf("File name is %s\n", fileName);
        printf("Mem count is %d\n", memCount);
    }
    char* carray=malloc(5*sizeof(char));
    struct fun_desc menu[] =
    {
        {"Toggle Debug Mode", toggleDebugMode},
        {"Set File Name", SetFileName},
        {"Set Unit Size", SetUnitSize},
        {"Load Into Memory", LoadIntoMemory},
        {"Toggle Display Mode", ToggleDisplayMode},
        {"File Display", FileDisplay},
        {"Memory Display", MemoryDisplay},
        {"Save Into File", SaveIntoFile},
        {"Memory Modify", MemoryModify},
        {"Quit", Quit},
        {NULL, NULL}
    };

    int bounds = sizeof(menu)/sizeof(menu[0]);
    int done = 0;
    int num;
    while(!done){   
        printf("Please select an option from the menu!(ctrl^D for exit)\n");
        for(int i = 0; i<sizeof(menu)/sizeof(menu[0]); i++){
          printf("%d. %s\n", i, menu[i].name);
        }
        if((scanf("%d", &num))==EOF){
          done = 1;
          break;
        }
        if(num>bounds){
            printf("Not within bounds\n");
            done = 1;
            break;
        }
        else{
            printf("Within bounds\n");
            carray = map(carray,5 , menu[num].fun);
        }
        
        
    }
    free(carray);
}
void main(){
    menu();
}