#include "cliente.h"

Cliente::Cliente(std::string nome, short conta, short agencia, std::string CPF) 
    : nome(nome),
      conta(conta),
      agencia(agencia),
      CPF(CPF)
{
}

std::string Cliente::GetNome()
{
    return nome;
}

short Cliente::GetConta()
{
    return conta;
}

short Cliente::GetAgencia()
{
    return agencia;
}

int Cliente::GetSaldo()
{
    return saldo;
}

void Cliente::SetSaldo(int novo_saldo)
{
    saldo = novo_saldo;
}

std::string Cliente::GetCPF()
{
    return CPF;
}
