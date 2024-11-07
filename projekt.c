#include <stdio.h>
#include <stdlib.h> // Ez a könyvtár az exit() függvény miatt szükséges
#include <string.h>

enum {
    CODE_C,
    CODE_JAVA,
    CODE_PY,
    CODE_BASH
};

void PrintDefaultCode(const char *path, int iType, int PrintOut) {
    if(PrintOut == 1){
        switch(iType){
            case CODE_C:
                printf("#include <stdio.h>\n\n");
                printf("int main() {\n");
                printf("    printf(\"Hello, World!\\n\");\n");
                printf("    return 0;\n");
                printf("}\n");
                break;
            case CODE_JAVA:
                printf("public class HelloWorld {\n");
                printf("    public static void main(String[] args) {\n");
                printf("        System.out.println(\"Hello, World!\");\n");
                printf("    }\n");
                printf("}\n");
                break;
            case CODE_PY:
                printf("print(\"Hello, World!\")\n");
                break;
            case CODE_BASH:
                printf("#!/bin/bash\n");
                printf("echo \"Hello, Bash!\"\n");
                break; 
        }
        return;
    }

    FILE *file;
    file = fopen(path, "r");
    if (file != NULL) {
        printf("A fájl már létezik: %s\n", path);
        fclose(file);
        return;
    }

    file = fopen(path, "w");
    if (file == NULL) {
        printf("Hiba a fájl létrehozása közben.\n");
        return;
    }

    switch(iType){
        case CODE_C:
            fprintf(file, "#include <stdio.h>\n\n");
            fprintf(file, "int main() {\n");
            fprintf(file, "    printf(\"Hello, World!\\n\");\n");
            fprintf(file, "    return 0;\n");
            fprintf(file, "}\n");
            break;
        case CODE_JAVA:
            fprintf(file, "public class HelloWorld {");
            fprintf(file, "    public static void main(String[] args) {");
            fprintf(file, "        System.out.println(\"Hello, World!\");");
            fprintf(file, "    }");
            fprintf(file, "}");
            break;
        case CODE_PY:
            fprintf(file, "print(\"Hello, World!\")\n");
            break;
        case CODE_BASH:
            fprintf(file, "#!/bin/bash");
            fprintf(file, "echo \"Hello, Bash!\"");
            break; 
    }

    fclose(file);
    printf("A fájl létrehozva: %s\n", path);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Nem adtál meg parancsot!\n");
        return 1;
    }

    if(strcmp(argv[1], "-h") == 0){
        printf("Segítség:\n");
        printf("1. -v -> verzió:\n");
        printf("2. -h -> segítség:\n");
        printf("3. alap c (vagy java, py, sh) --stdout -> kiírja az adott nyelv forráskódját!\n");
        printf("4. alap c (vagy java, py, sh) -> készít egy fájlt az adott nyelv alap forráskódjával!\n");
    }
    else if(strcmp(argv[1], "-v") == 0){
        printf("Verzió: 0.0.3\n");
        return 1;
    }
    else if (strcmp(argv[1], "alap") == 0) {
        const char *command = argv[2];

        const char *szType[] = {"c", "java", "py", "sh"};

        int iType = -1;

        for(int i = 0; i < sizeof(szType) / sizeof(szType[0]); i++){
            if(strcmp(command, szType[i]) == 0){
                iType = i;
                break;
            }
        }

        if(iType == -1){
            printf("Ismeretlen parancs: alap %s\n", command);
            return 1;
        }

        char szPath[128];
        sprintf(szPath, "file.%s", szType[iType]);

        int PrintOut = 0;

        if(argc > 3){
            if(strcmp(argv[3], "--stdout") == 0)
                PrintOut = 1;
            else{
                printf("Ismeretlen parancs: %s\n", argv[3]);
                return 1;
            }
        }

        PrintDefaultCode(szPath, iType, PrintOut);
    }
    else {
        printf("Ismeretlen parancs: %s\n", argv[1]);
        return 1;
    }

    return 0;
}