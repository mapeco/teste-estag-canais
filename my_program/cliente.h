#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>

class Cliente
{
    public:
        Cliente(std::string nome, short conta, short agencia, std::string CPF);
        std::string GetNome();
        short GetAgencia();
        short GetConta();
        int GetSaldo();
        void SetSaldo(int novo_saldo);
        std::string GetCPF();

    private:
        std::string nome;
        short agencia;
        short conta;
        int saldo = 0;
        std::string CPF;
};

#endif // CLIENTE_H
