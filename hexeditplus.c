#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
  char debug_mode;
  char file_name[128];
  int unit_size;
  unsigned char mem_buf[10000];
  size_t mem_count;
  char display_mode; //0 for decimal, 1 for hex
  /*
   .
   
   Any additional fields you deem necessary
  */
} state;

char *carray;
void toggleDebugMode(state* s) {
    if (s->debug_mode) {
        s->debug_mode = 0;
        printf("Debug flag now off\n");
    } else {
        s->debug_mode = 1;
        printf("Debug flag now on\n");
    }
}

void setFileName(state* s) {
    printf("Enter file name: ");
    if (fgets(s->file_name, sizeof(s->file_name), stdin) != NULL) {
        s->file_name[strcspn(s->file_name, "\n")] = '\0'; // Remove newline character
        if (s->debug_mode == 0) {
            printf("Debug: file name set to '%s'\n", s->file_name);
        }
    } else {
        printf("Error reading file name\n");
    }
}

void setUnitSize(state* s) {
    int unit_size;
    printf("Enter unit size (1, 2, or 4): ");
    scanf("%d", &unit_size);
    if (unit_size == 1 || unit_size == 2 || unit_size == 4) {
        s->unit_size = unit_size;
        if (s->debug_mode) {
            printf("Debug: set unit size to %d\n", s->unit_size);
        }
    } else {
        printf("Invalid unit size\n");
    }
    while (getchar() != '\n'); // Clear input buffer
}

void loadIntoMemory(state* s){
    if (strcmp(s->file_name, "") == 0){
        printf("Error: file name is empty\n");
        return;
    }

    FILE *file = fopen(s->file_name, "rb");
    if (file == NULL) {
        printf("Error: could not open file '%s'\n", s->file_name);
        return;
    }

    printf("Please enter <location> <length>\n"); //where we start reading from
    char input[10000];
    fgets(input, sizeof(input), stdin);

    unsigned int location;
    int length;
    sscanf(input, "%x %d", &location, &length);

    if (s->debug_mode) {
        printf("Debug: file name: %s\n", s->file_name);
        printf("Debug: location: %x\n", location);
        printf("Debug: length: %d\n", length);
    }

    fseek(file, location, SEEK_SET);
    size_t bytesRead = fread(s->mem_buf, s->unit_size, length, file);
    
    fclose(file);

    printf("Loaded %zu units into memory\n", bytesRead);

}

void quit(state* s) {
    if (s->debug_mode) {
        printf("quitting\n");
    }
    if (carray != NULL) {
        free(carray);
        carray = NULL; // Set to NULL after freeing to avoid double free
    }
    exit(0);
}

void notImplementedYet(state* s) {
    (void)s; // Suppress unused parameter warning
    printf("Not implemented yet\n");
}

void memoryModify (state* s){
     (void)s; // Suppress unused parameter warning
    printf("Not implemented yet\n");
}


void fileDisplay(state* s){
     if (strcmp(s->file_name, "") == 0) {
        printf("Error: file name is empty\n");
        return;
    }

    FILE *file = fopen(s->file_name, "rb");
    if (file == NULL) {
        printf("Error: could not open file '%s'\n", s->file_name);
        return;
    }

    printf("Enter file offset and lenegth\n");
    unsigned int address;
    int length;
    char input[10000];

    scanf("%x %d", &address, &length); // read the address in hex and the length in decimal
    printf("%s\n", s-> display_mode == 1 ? "Decimal" : "Hexadecimal");
    printf("%s\n", s-> display_mode == 1 ? "=======" : "===========");
    static char* hex_formats[] = {"%#hhx\n", "%#hx\n", "No such unit", "%#x\n"};
    static char* dec_formats[] = {"%#hhd\n", "%#hd\n", "No such unit", "%#d\n"};

    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Error reading input\n");
        fclose(file);
        return;
    }

    for (int i = 0; i < length; i++) {
        int unitSize = s->unit_size;
        int value = 0;
        unsigned char* tmp;        
        tmp = (unsigned char*)(address + i * unitSize);
        value = *((int*)tmp);

        if (s->display_mode == 0) {
            printf(hex_formats[s->unit_size - 1], value);
        } else {
            printf(dec_formats[s->unit_size - 1], value);
        }
    }
}

void memoryDisplay(state* s){
      printf("Please enter <addr> <u>\n");
    char input[100];
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Error reading input\n");
        return;
    }

    unsigned int addr;
    int u;
    if (sscanf(input, "%x %d", &addr, &u) != 2) {
        printf("Invalid input format\n");
        return;
    }

     if (s->debug_mode) {
        printf("Debug: addr: %x\n", addr);
        printf("Debug: u: %d\n", u);
    }

    unsigned char* start_addr = (addr == 0) ? s->mem_buf : (unsigned char*)addr;
    static char* hex_formats[] = {"%#hhx\n", "%#hx\n", "No such unit", "%#x\n"};
    static char* dec_formats[] = {"%#hhd\n", "%#hd\n", "No such unit", "%#d\n"};
    for (size_t i = 0; i < u * s->unit_size; i += s->unit_size) {
        int val = 0;
        memcpy(&val, start_addr + i, s->unit_size);
        if (s->display_mode) {
            printf(hex_formats[s->unit_size - 1], val);
        } else {
            printf(dec_formats[s->unit_size - 1], val);
        }
    }
}

void toggleDisplayMode(state *s){ //changing from 0 to 1 and 1 to 0
     if (s->display_mode) {
        s->display_mode = 0;
        printf("Display flag now off, decimal representation\n");
    } else {
        s->display_mode = 1;
        printf("Display flag now on, hexadecimal representation\n");
    }
}

void saveIntoFile(state* s) {
    (void)s; // Suppress unused parameter warning
    printf("Not implemented yet\n");
}


struct fun_desc {
    char *name;
    void (*fun)(state*);
};

void printMenu(struct fun_desc menu[]) {
    printf("Please select an option from the menu (ctrl^D for exit):\n");
    for (int i = 0; menu[i].name != NULL; i++) {
        printf("%d) %s\n", i, menu[i].name);
    }
}


int main() {
    state s;
    s.debug_mode = 0;
    s.unit_size = 1;
    s.mem_count = 0;
    s.display_mode = 0;
    s.file_name[0] = '\0';
    
    carray = malloc(5 * sizeof(char));
    if (carray == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    struct fun_desc menu[] = {
        {"Toggle Debug Mode", toggleDebugMode},
        {"Set File Name", setFileName},
        {"Set Unit Size", setUnitSize},
        {"Load Into Memory", loadIntoMemory},
        {"Toggle Display Mode", toggleDisplayMode},
        {"File Display", fileDisplay},
        {"Memory Display", memoryDisplay},
        {"Save Into File", saveIntoFile},
        {"Memory Modify", memoryModify},
        {"Quit", quit},
        {NULL, NULL}
    };

    while (1) {
        printMenu(menu);
        int num;
        printf("Option: ");
        if (scanf("%d", &num) != 1) {
            break;
        }
        while (getchar() != '\n'); // Clear input buffer

        if (num < 0 || num >= (int)(sizeof(menu) / sizeof(menu[0]) - 1)) {
            printf("Not within bounds\n");
            continue;
        }
        printf("Within bounds\n");
        printf("Option: %d\n", num);
        menu[num].fun(&s);
    }

    return 0;
}