    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>

    #define I 8
    #define R 0
    #define J 2

    #define ADDI 8
    #define LW   35
    #define SW   43

    #define SUB  34
    #define ADD  32
    #define XOR  38

    #define AND  36
    #define OR   37

    int converterBinario(int numero) {
        if (numero == 0) {
            return 0;
        } else {
            return (numero % 2) + 10 * converterBinario(numero / 2);
        }
    }

    int unidade_logica_aritmetica(char *opcode_ula, int operador1, int operador2) {

        if (strcmp(opcode_ula, "ADDI") == 0) {
            return operador1+operador2;
        }else if (strcmp(opcode_ula, "SUB") == 0) {
            return operador1-operador2;
        }
    }

    int identifica_registrador(char *registrador){
        char *registradores[]={"$zero","$at0","$v0","$v1","$a0","$a1","$a2","$a3","$t0","$t1","$t2","$t3","$t4", "$t5", "$t6","$t7","$s0","$s1","$s2","$s3","$s4", "$s5", "$s6","$s7","$t8","$t9","$k0","$k1","$gp","$sp","$s8","$ra"};

        int quant_registradores;
        int i=0;
        quant_registradores = sizeof(registradores)/ sizeof(registrador);

        while(i<quant_registradores){
            if(strcmp(registrador, registradores[i])==0){
                return i;
            }
            i++;
        }
        return -100;
    }

    int registradores_att[32];

    void atualizar_registrador(char *registrador, int valor) {
        int indice = identifica_registrador(registrador);
        registradores_att[indice] = valor;
        printf("Registrador %s atualizado: %d\n", registrador, registradores_att[indice]);
    }

    int program_counter = 644;

    void executar_instrucao_tipo_i(char *opcode) {
        
        int imediato;
        char RD[4];
        char RS[4];

        printf("Digite o registrador1: ");
        scanf(" %3[^\n]", &RD);

        printf("Digite o registrador1: ");
        scanf(" %3[^\n]", &RS);

        printf("Informe o imediato: ");
        scanf(" %d", &imediato);

        printf("\n\n---BUSCA---\n");

        printf("\nProgram Counter: %d\n", program_counter);

        printf("\n---DECODIFICAÇÃO---\n\n");

        printf("          BINARIO             |  DECIMAL\n");

        printf("OPCODE:    %06d             |    %d\n", converterBinario(I), I);

        printf("RS:        %05d              |    %d\n", converterBinario(identifica_registrador(RS)),identifica_registrador(RS));

        printf("RD:        %05d              |    %d\n", converterBinario(identifica_registrador(RD)),identifica_registrador(RD));

        printf("Imediato:  %016d   |    %d\n", converterBinario(imediato),imediato);


        printf("\n\n---EXECUÇÃO---\n");

        int rs_decimal = identifica_registrador(RD);

        int result = unidade_logica_aritmetica(opcode, rs_decimal, imediato);

        printf("Resultado da operação: %d\n", result);

        printf("\n---ESCRITA---\n");

        atualizar_registrador(RD, result);

        printf("Valor atualizado do registrador %s: %d\n",RD, result);

        program_counter=program_counter+4;

        printf("Valor atual do Program counter atualizado: %d", program_counter);

    }

    void executar_instrucao_tipo_r(char *opcode, int funct) {
        
        char RD[4], RS[4], RT[4];
        int shamt = 0;


        printf("Digite o registrador RS: ");
        scanf(" %3[^\n]", RS);

        printf("Digite o registrador RT: ");
        scanf(" %3[^\n]", RT);


        printf("Digite o registrador RD: ");
        scanf(" %3[^\n]", RD);

        printf("\n---BUSCA---\n");
        printf("\nProgram Counter: %d\n", program_counter);

        printf("\n---DECODIFICAÇÃO---\n\n");

        printf("          BINARIO             |  DECIMAL\n");

        printf("OPCODE:    %06d             |    %d\n", converterBinario(R), R);

        printf("RS:        %05d              |    %d\n", converterBinario(identifica_registrador(RS)),identifica_registrador(RS));

        printf("RT:        %05d              |    %d\n", converterBinario(identifica_registrador(RT)),identifica_registrador(RT));

        printf("RD:        %05d              |    %d\n", converterBinario(identifica_registrador(RD)),identifica_registrador(RD));

        printf("SHAMT:     %05d              |    %d\n", converterBinario(shamt), shamt);

        printf("FUNCT:     %06d             |  %d\n ", converterBinario(funct), funct);

        printf("---EXECUÇÃO---\n");

        int rs_decimal = identifica_registrador(RS);

        int rt_decimal = identifica_registrador(RT);

        int result = unidade_logica_aritmetica(opcode, rs_decimal,rt_decimal);

        printf("\nResultado da operação: %d\n", result);


        printf("\n---ESCRITA---\n");

        printf("Valor atualizado do registrador %s: %d\n",RD, result);

        atualizar_registrador(RD, result);

        program_counter=program_counter+4;

        printf("Valor atual do Program counter atualizado: %d", program_counter);

    }

    void executar_instrucao_tipo_j(char *opcode) {
        int endereco_destino;

        printf("informe o endereço de destino: ");
        scanf(" %d", &endereco_destino);

        printf("\n---BUSCA---\n");

        printf("\nProgram Counter: %d\n", program_counter);

        printf("\n---DECODIFICAÇÃO---\n\n");

        printf("          BINARIO             |  DECIMAL\n");

        printf("OPCODE:    %06d             |    %d\n", converterBinario(J), J);

        printf("endereço de destino em binário: %026d", converterBinario(endereco_destino));

        printf("\n---EXECUÇÃO---\n");

        printf("\n---ESCRITA---\n");

        program_counter = endereco_destino;

        printf("Valor atual do Program Counter atualizado: %d", program_counter);

    }

    int main() {
        char comando[5];

        system("clear");
        system("cls");

        printf("Informe o comando: ");
        scanf(" %4[^\n]", comando);

        if (strcmp(comando, "ADDI") == 0) {
            executar_instrucao_tipo_i(comando);
        } else if (strcmp(comando, "LW") == 0) {
            printf("OPCODE: %06d\n", converterBinario(LW));
        } else if (strcmp(comando, "SW") == 0) {
            printf("OPCODE: %06d\n", converterBinario(SW));
        } else if (strcmp(comando, "ADD") == 0) {
            executar_instrucao_tipo_r(comando, ADD);
        } else if (strcmp(comando, "SUB") == 0) {
            executar_instrucao_tipo_r(comando, SUB);
        } else if (strcmp(comando, "AND") == 0) {
            executar_instrucao_tipo_r(comando, AND);
        } else if (strcmp(comando, "OR") == 0) {
            executar_instrucao_tipo_r(comando, OR);
        }

        return 0;
    }