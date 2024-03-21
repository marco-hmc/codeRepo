/*
 * @Author: your name
 * @Date: 2022-02-21 00:10:44
 * @LastEditTime: 2022-02-27 14:01:55
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

int main(){
    Table *table = new_table();
    InputBuffer *input_buffer = new_input_buffer();

    int i = 0;
    while (i<1401)
    {
        i++;
        input_buffer->buffer = copyStr("insert 1 marco marco@163.com");

        if (input_buffer->buffer[0] == '.')
        {
            switch(do_meta_command(input_buffer)){
                case META_COMMAND_SUCCESS:
                    continue;
                case META_COMMAND_UNRECOGNIZED:
                    printf("Unrecognized command '%s'\n", input_buffer->buffer);
                    continue;
            }
        }
        Statement statement;
        switch(prepare_statement(input_buffer, &statement)){
            case PREPARE_SUCCESS:
                break;
            case PREPARE_NEGATIVE_ID:
                printf("ID must be positive.\n");
                continue;
            case PREPARE_STRING_TOO_LONG:
                printf("String is too long.\n");
                continue;
            case PREPARE_SYNTAX_ERROR:
                printf("Syntax error. Could not parse statement.\n");
                continue;
            case PREPARE_UNRECOGNIZED:
                printf("Unrecognized statement '%s'\n", input_buffer->buffer);
                continue;
        }
        switch (execute_statement(&statement, table)) {
        case EXECUTE_SUCCESS:
            printf("Executed.\n");
            break;
        case EXECUTE_TABLE_FULL:
            printf("Error: Table full.\n");
            break;
        }
    }
}