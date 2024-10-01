#include "Jogo.h"
#include <iostream>
using namespace std;



Jogo::Jogo()
{
    nome = "";
    preco = custo = 0.0f;
    horas = 0;
}

Jogo::Jogo(const string& titulo, float valor, int tempo)
{
    nome = titulo;
    preco = valor;
    horas = tempo;
    custo = valor;
    calcular();
}






void Jogo::atualizar(float valor)
{
    this->preco = valor;
    calcular();
}

void Jogo::jogar(int tempo)
{
    horas = horas + tempo;
    calcular();
}

void Jogo::exibir() const
{
    cout << fixed;
    cout.precision(2);

    cout  <<"\nNome: " << nome << " R$"
        <<" Preço:" << preco << " "
        << " Horas: " << horas << "h = R$"
        << " Custo: " << custo << "/h\n";
}

