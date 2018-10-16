#include <stdlib.h>
#include <stdio.h>
#include <iup.h>
#include "operacoes.h"

#define NUM_BOTOES 16

// variaveis globais
Ihandle *multitext, *multitext_op;		// caixas de texto
char operacao = NULL;					// indica operacao a ser realizada
int valor_um = 0;						// valor salvo

void btnNum(Ihandle *self) {
	// evento dos botoes 0 a 9
	char *s = IupGetAttribute(self, "TITLE");
	
	char *k = malloc(sizeof(s) + 1);
    sprintf(k, "%s%s", IupGetAttribute(multitext, "VALUE"), s);
    
    IupSetAttribute(multitext, "VALUE", k);
    free(k);
}

void btnOperacao(Ihandle *self) {
	// evento dos botoes +, -, X e /
	char *s = IupGetAttribute(self, "TITLE");
	
    IupSetAttribute(multitext_op, "VALUE", s);
    
    if (operacao == '\0') {
        valor_um = string_to_int(IupGetAttribute(multitext, "VALUE"));
        IupSetAttribute(multitext, "VALUE", NULL);
    }
    
    operacao = s[0];
}

void btnIgual(Ihandle *self) {
    // evento do botao igual
    int valor_dois, resultado;
    
    if (operacao != '\0') {
        valor_dois = string_to_int(IupGetAttribute(multitext, "VALUE"));
        
        switch (operacao) {
            case '+' :
                resultado = soma(valor_um, valor_dois);
                break;
            case '-' :
                resultado = sub(valor_um, valor_dois);
                break;
            case 'X' :
                resultado = mult(valor_um, valor_dois);
                break;
            case '/' :
                resultado = divisao(valor_um, valor_dois);
                break;
        }
        
        IupSetAttribute(multitext, "VALUE", int_to_string(resultado));
        IupSetAttribute(multitext_op, "VALUE", NULL);
        operacao = '\0';
    }
}

void btnLimpa(Ihandle *self) {
    // evento botao limpar
    IupSetAttribute(multitext, "VALUE", "");
    IupSetAttribute(multitext_op, "VALUE", "");
    operacao = '\0';
    valor_um = 0;
}

int main(int argc, char **argv) {
    Ihandle *label;
    Ihandle *hbox0, *hbox1, *hbox2, *hbox3, *hbox4, *hbox5;
    Ihandle *vbox, *dlg;
    Ihandle *vetor_btn[NUM_BOTOES];

    // inicia IUP
    IupOpen(&argc, &argv);

    // label
    label = IupLabel("Calculadora");

    // caixa texto
    multitext = IupText(NULL);
    IupSetAttribute(multitext, "SIZE", "120x12");
    IupSetAttribute(multitext, "ALIGNMENT", "ACENTER");
    IupSetAttribute(multitext, "FONT", "DEFAULTFONT, 14");
    IupSetAttribute(multitext, "ACTIVE", "NO");

    multitext_op = IupText(NULL);
    IupSetAttribute(multitext_op, "SIZE", "20x12");
    IupSetAttribute(multitext_op, "ALIGNMENT", "ACENTER");
    IupSetAttribute(multitext_op, "FONT", "DEFAULTFONT, 14");
    IupSetAttribute(multitext_op, "ACTIVE", "NO");

    // botoes
    int i;
    for (i=0; i <= 9; i++) {
        vetor_btn[i] = IupButton(int_to_string(i), NULL);                	// cria botoes 0 a 9
    }

	vetor_btn[10] = IupButton("Limpar", NULL);								// cria outros botoes
	vetor_btn[11] = IupButton("=", NULL);
	vetor_btn[12] = IupButton("+", NULL);
	vetor_btn[13] = IupButton("-", NULL);
	vetor_btn[14] = IupButton("X", NULL);
	vetor_btn[15] = IupButton("/", NULL);

	for (i=0; i < NUM_BOTOES; i++) {
        IupSetAttribute(vetor_btn[i], "FONT", "DEFAULTFONT, Bold 9");   	// formata os botoes
        IupSetAttribute(vetor_btn[i], "SIZE", "45x30");
	}


    // linhas
    hbox0 = IupHbox(label, NULL);
    hbox1 = IupHbox(multitext, multitext_op, NULL);
    hbox2 = IupHbox(vetor_btn[7], vetor_btn[8], vetor_btn[9], vetor_btn[12], NULL);
    hbox3 = IupHbox(vetor_btn[4], vetor_btn[5], vetor_btn[6], vetor_btn[13], NULL);
    hbox4 = IupHbox(vetor_btn[1], vetor_btn[2], vetor_btn[3], vetor_btn[14], NULL);
    hbox5 = IupHbox(vetor_btn[10], vetor_btn[0], vetor_btn[11], vetor_btn[15], NULL);

    // vbox
    vbox = IupVbox(hbox0, hbox1, hbox2, hbox3, hbox4, hbox5, NULL);
    IupSetAttribute(vbox, "ALIGNMENT", "ACENTER");
    IupSetAttribute(vbox, "GAP", "5");
    IupSetAttribute(vbox, "MARGIN", "5x5");

    // janela principal
    dlg = IupDialog(vbox);
    IupSetAttribute(dlg, "TITLE", "");

    // calbacks ou eventos
    for (i=0; i <= 9; i++) {
    	IupSetCallback(vetor_btn[i], "ACTION", (Icallback) btnNum);				// botoes 0 a 9
	}
	
    IupSetCallback(vetor_btn[10], "ACTION", (Icallback) btnLimpa);				// botoes limpa e igual
	IupSetCallback(vetor_btn[11], "ACTION", (Icallback) btnIgual);			
		
	for (i=12; i < NUM_BOTOES; i++) {
		IupSetCallback(vetor_btn[i], "ACTION", (Icallback) btnOperacao);		// botoes de operacao
    }

    // mostra jalela principal
    IupShowXY(dlg, IUP_CENTER, IUP_CENTER);
    // loop infinito
    IupMainLoop();
    // fim
    IupClose();
    return EXIT_SUCCESS;
}

