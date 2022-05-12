#include "transferencia.h"
#include <iostream>

Transferencia::Transferencia(int id, int valor, char tipo, Cliente* emissor, Cliente* receptor) 
    : id(id),
      valor(valor),
      tipo(tipo),
      emissor(emissor),
      receptor(receptor)
{
}

void Transferencia::RealizarTransferencia()
{
    // Checa se a transferência segue as regras
    int error_code = ChecarValidade();

    // Caso error code seja 0 realiza a transferência
    if(error_code == 0) {
        emissor->SetSaldo(emissor->GetSaldo() - valor);
        receptor->SetSaldo(receptor->GetSaldo() + valor);
    }

    // Imprime o resultado
    ImprimirResultado(error_code);
}

int Transferencia::ChecarValidade()
{
    // Ultimos dois dígitos representam decimais
    if(tipo == PIX && valor > 500000)
        return PIX_VALOR_ALTO;
    else if(tipo == TED) {
        if(valor <= 500000)
            return TED_VALOR_BAIXO;
        else if(valor > 1000000)
            return TED_VALOR_ALTO;
    }
    else if(tipo == DOC && valor <= 1000000)
        return DOC_VALOR_BAIXO;

    // Caso for uma transferência para a mesma conta
    if(emissor->GetAgencia() == receptor->GetAgencia() && emissor->GetConta() == receptor->GetConta())
        return TRANSFERENCIA_MESMA_CONTA;

    // Caso o emissor não tenha saldo o suficiente para a transação
    if(emissor->GetSaldo() < valor)
        return SALDO_INSUFICIENTE;

    return 0;
}

void Transferencia::ImprimirResultado(int error_code)
{
    if(error_code == 0) {
        // Separa parte inteira do saldo da parte decimal
        int saldo_emissor_int = emissor->GetSaldo()/100;
        int saldo_emissor_dec = emissor->GetSaldo() - saldo_emissor_int*100;
        int saldo_receptor_int = receptor->GetSaldo()/100;
        int saldo_receptor_dec = receptor->GetSaldo() - saldo_receptor_int*100;
        // Imprime resultado
        std::cout << "Sua transferência foi realizada com sucesso!" << std::endl 
        << "Saldo do emissor: " << saldo_emissor_int << "," << saldo_emissor_dec << std::endl
        << "Saldo do receptor: " << saldo_receptor_int << "," << saldo_receptor_dec << std::endl;
    }
    else {
        std::cout << "Sua transferência não foi completada pois ";

        switch(error_code) {
            case PIX_VALOR_ALTO:
                std::cout << "o valor é maior que o limite para transferências PIX." << std::endl;
            break;
            case TED_VALOR_BAIXO:
                std::cout << "o valor é menor que o limite para transferências TED." << std::endl;
            break;
            case TED_VALOR_ALTO:
                std::cout << "o valor é maior que o limite para transferências TED." << std::endl;
            break;
            case DOC_VALOR_BAIXO:
                std::cout << "o valor é menor que o limite para transferências DOC." << std::endl;
            break;
            case TRANSFERENCIA_MESMA_CONTA:
                std::cout << "transferências para a mesma conta não são permitidas." << std::endl;
            break;
            case SALDO_INSUFICIENTE:
                std::cout << "o saldo do emissor não é suficiente para completar a transação." << std::endl;
        }
    }
}
