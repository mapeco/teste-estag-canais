#ifndef TRANSFERENCIA_H
#define TRANSFERENCIA_H

#include <string>
#include "cliente.h"

#define PIX 1
#define TED 2
#define DOC 3

// Define valores de erro
#define PIX_VALOR_ALTO            -1
#define TED_VALOR_BAIXO           -2
#define TED_VALOR_ALTO            -3
#define DOC_VALOR_BAIXO           -4
#define TRANSFERENCIA_MESMA_CONTA -5
#define SALDO_INSUFICIENTE        -6

class Transferencia
{
    public:
        Transferencia(int id, int valor, char tipo, Cliente* emissor, Cliente* receptor);
        void RealizarTransferencia();
        int ChecarValidade();
        void ImprimirResultado(int error_code);

    private:
        int id;
        unsigned int valor;
        char tipo; // 1 = PIX, 2 = TED, 3 = DOC.
        Cliente* emissor;
        Cliente* receptor; 
};

#endif // TRANSFERENCIA_H
