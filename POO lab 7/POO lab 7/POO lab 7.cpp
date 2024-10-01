#include <iostream>
#include <fstream>
#include "Jogo.h"
#include <cstdio>
using namespace std;

static void adicionarJogos() {
    cout << "\nQuantos Jogos você quer adicionar? ";
    int quantidadeJogos;
    cin >> quantidadeJogos;

    Jogo* colecao = new Jogo[quantidadeJogos];

    for (int i = 0; i < quantidadeJogos; i++) {
        cout << "Digite o jogo " << (i + 1) << ": " << '\n';
        cin >> colecao[i];
    }

    {
        std::ofstream ofs("jogos.bin", std::ios::binary | std::ios::app);
        for (int i = 0; i < quantidadeJogos; i++) {
            colecao[i].salvar(ofs);
        }
    }

    delete[] colecao;
}

static void verBiblioteca(Jogo*& jogosCarregados, int& jogosCarregadosCount) {
    jogosCarregadosCount = 0;

    std::ifstream ifs("jogos.bin", std::ios::binary);
    if (!ifs) {
        cerr << "Erro ao abrir o arquivo." << '\n';
        return;
    }

    int capacidade = 10;
    jogosCarregados = new Jogo[capacidade];

    while (true) {
        Jogo jogo;
        jogo.carregar(ifs);

        if (ifs.eof()) break;

        if (jogosCarregadosCount >= capacidade) {
            capacidade += 10;
            Jogo* temp = new Jogo[capacidade];
            for (int i = 0; i < jogosCarregadosCount; i++) {
                temp[i] = jogosCarregados[i];
            }
            delete[] jogosCarregados;
            jogosCarregados = temp;
        }

        jogosCarregados[jogosCarregadosCount] = jogo;
        jogosCarregadosCount++;
    }

    cout << "\nBiblioteca de Jogos:\n";
    for (int i = 0; i < jogosCarregadosCount; i++) {
        cout << i + 1 << ". ";
        jogosCarregados[i].exibir();
    }
}

static void limparBiblioteca() {
    if (remove("jogos.bin") == 0) {
        cout << "Biblioteca de jogos limpa!\n";
    }
    else {
        cerr << "Erro ao limpar a biblioteca.\n";
    }
}

static void JogarJogo(Jogo* jogosCarregados, int jogosCarregadosCount) {
    int numeroJogar, quantidadeHoras;
    cout << "Qual jogo deseja jogar? (Digite o número correspondente na biblioteca) ";
    cin >> numeroJogar;

    if (numeroJogar < 1 || numeroJogar > jogosCarregadosCount) {
        cout << "Número inválido. Nenhum jogo selecionado.\n";
        return;
    }

    cout << "Por quantas horas quer jogar? ";
    cin >> quantidadeHoras;

    jogosCarregados[numeroJogar - 1].jogar(quantidadeHoras);

    std::ofstream ofs("jogos.bin", std::ios::binary | std::ios::trunc);
    for (int i = 0; i < jogosCarregadosCount; i++) {
        jogosCarregados[i].salvar(ofs);
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    Jogo* jogosCarregados = nullptr;
    int jogosCarregadosCount = 0;

    int escolha;
    do {
        cout << "\nEscolha uma opção:\n";
        cout << "1. Adicionar Jogos\n";
        cout << "2. Ver Biblioteca de Jogos\n";
        cout << "3. Limpar Biblioteca de Jogos\n";
        cout << "4. Jogar Jogo\n";
        cout << "5. Sair\n";
        cout << "Digite sua escolha: ";
        cin >> escolha;

        switch (escolha) {
        case 1:
            adicionarJogos();
            break;
        case 2:
            verBiblioteca(jogosCarregados, jogosCarregadosCount);
            break;
        case 3:
            limparBiblioteca();
            break;
        case 4:
            if (jogosCarregadosCount == 0) {
                cout << "Nenhum jogo carregado. Carregue a Biblioteca.\n";
            }
            else {
                JogarJogo(jogosCarregados, jogosCarregadosCount);
            }
            break;
        case 5:
            cout << "Saindo do programa...\n";
            break;
        default:
            cout << "Opção inválida. Tente novamente.\n";
        }
    } while (escolha != 5);

    delete[] jogosCarregados;
    return 0;
}
