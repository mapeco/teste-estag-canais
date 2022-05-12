#include "cliente.h"
#include "transferencia.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <ctime>

// Testa algoritmo com entrada.txt
int main()
{
    std::ifstream entrada;
    entrada.open("entrada2.txt");

    if(entrada.is_open()) {
        std::mt19937 gen(std::time(nullptr));
        std::string linha;
        getline(entrada, linha); getline(entrada, linha); // Pula para primeira entrada

        // Lê e realiza transferência de cada linha
        while(getline(entrada, linha)) {
            int pos = 0;
            std::string var;
            int id;
            int valor;
            char tipo;
            std::vector<Cliente*> clientes(2);
            std::string nome;
            short agencia;
            short conta;
            std::string CPF;

            // Armazena dados da transferência
            var = linha.substr(pos, linha.find('|', pos)); pos = linha.find('|', pos) + 1;
            id = std::stoi(var);

            // Guarda decimais como dois ultimos dígitos do int
            var = linha.substr(pos, linha.find('|', pos) - pos); pos = linha.find('|', pos) + 1;
            if(var.find(',') == std::string::npos) {
                var.append("00");
                valor = std::stoi(var);
            }
            else {
                var.erase(var.find(','), 1);
                valor = std::stoi(var);
            }

            var = linha.substr(pos, linha.find('|', pos) - pos); pos = linha.find('|', pos) + 1;
            if(var == "PIX") tipo = 1;
            else if(var == "TED") tipo = 2;
            else tipo = 3;

            // Inicializa ambos clientes
            for(Cliente* &c : clientes) {
                var = linha.substr(pos, linha.find('|', pos) - pos); pos = linha.find('|', pos) + 1;
                nome = var;
                var = linha.substr(pos, linha.find('|', pos) - pos); pos = linha.find('|', pos) + 1;
                agencia = std::stoi(var);
                var = linha.substr(pos, linha.find('|', pos) - pos); pos = linha.find('|', pos) + 1;
                conta = std::stoi(var);
                var = linha.substr(pos, linha.find('|', pos) - pos); pos = linha.find('|', pos) + 1;
                CPF = var;
                c = new Cliente(nome, agencia, conta, CPF);
            }
            // Gera um saldo aleatório para o emissor (assumindo que o emissor tem sempre no mínimo o valor da transação)
            std::uniform_int_distribution<> uid(valor, valor + valor/2);
            clientes[0]->SetSaldo(uid(gen));

            // Inicializa transferência
            Transferencia t(id, valor, tipo, clientes[0], clientes[1]);
            t.RealizarTransferencia();
            std::cout << std::endl;

            delete clientes[0]; delete clientes[1];
        }
    }
    else
        std::cout << "Não foi possível abrir o arquivo entrada.txt" << std::endl;
    
    entrada.close();
}
