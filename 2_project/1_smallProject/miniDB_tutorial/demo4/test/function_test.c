/*
 * @Author: your name
 * @Date: 2022-02-21 00:10:44
 * @LastEditTime: 2022-02-27 18:06:21
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /demo3/test/function_test.cpp
 */
#include "common.h"
#include "complier.h"
#include "vm.h"

void insertBufUpdate(InputBuffer* input){
    char *tmp = "insert 1 marco marco@163.com\n";
    memcpy(input->buffer, tmp, 25);
    input->buffer[28] = 0;
}

char* copyStr(const char *const src){
    char *res = malloc(strlen(src) + 1);
    strcpy(res, src);
    return res;
}

void sqlWork(InputBuffer* input_buffer, Table* table){
        if (input_buffer->buffer[0] == '.')
        {
            switch (do_meta_command(input_buffer, table)){
                case META_COMMAND_SUCCESS:
                    return;
                case META_COMMAND_UNRECOGNIZED:
                    printf("Unrecognized command '%s'\n", input_buffer->buffer);
                    return;
            }
        }
        Statement statement;
        switch(prepare_statement(input_buffer, &statement)){
            case PREPARE_SUCCESS:
                break;
            case PREPARE_NEGATIVE_ID:
                printf("ID must be positive.\n");
                return;
            case PREPARE_STRING_TOO_LONG:
                printf("String is too long.\n");
                return;
            case PREPARE_SYNTAX_ERROR:
                printf("Syntax error. Could not parse statement.\n");
                return;
            case PREPARE_UNRECOGNIZED:
                printf("Unrecognized statement '%s'\n", input_buffer->buffer);
                return;
        }
        
        switch (execute_statement(&statement, table)) {
            case EXECUTE_SUCCESS:
                printf("Executed.\n");
                break;
            case EXECUTE_TABLE_FULL:
                printf("Error: Table full.\n");
                break;
            case EXECUTE_UNKNOWN_STMT:
                printf("Error: Unknown statement.\n");
                break;
        }
}

int main(int argc, char **argv){
    if (argc < 2) {
        printf("Must supply a database filename.\n");
        exit(EXIT_FAILURE);
    }
    char *filename = argv[1];
    Table *table = db_open(filename);
    InputBuffer *input_buffer = new_input_buffer();

    int i = 0;
    while (i<500){
        input_buffer->buffer = copyStr("insert 1 marco marco@163.com");
        sqlWork(input_buffer, table);
        input_buffer->buffer = copyStr("select");
        sqlWork(input_buffer, table);
        i++;
    }
}