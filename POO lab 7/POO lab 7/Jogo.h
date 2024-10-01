#ifndef JOGO_H
#define JOGO_H

#include <fstream>
#include <string>
#include <iostream>
using std::string;



class Jogo
{
private:
	string nome;									
	float preco;									
	int horas;										
	float custo;									
	void calcular();								
	

public:
	Jogo();											
	Jogo(const string& titulo, float valor = 0, int tempo = 0);										
	void atualizar(float valor);					
	void jogar(int tempo);							
	void exibir() const;	
	const Jogo& comparar(const Jogo& jogo, const Jogo& (Jogo::* func)(const Jogo&) const) const;
	const Jogo& MaisJogado(const Jogo& jogo) const;
	const Jogo& MenorCusto(const Jogo& jogo) const;
	const Jogo& MenorPreco(const Jogo& jogo) const;
	friend std::istream& operator>>(std::istream& is, Jogo& j) {
		
		std::cout << "\nDigite o Nome do Jogo: ";
		is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::getline(is, j.nome); 

		
		std::cout << "\nDigite O Preco do jogo: ";
		is >> j.preco;
		is.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

		
		std::cout << "\nDigite as Horas jogadas: ";
		is >> j.horas;
		is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		
		j.calcular();
		return is; 
	}
	void salvar(std::ofstream& ofs) const {
		size_t length = nome.size();
		ofs.write(reinterpret_cast<const char*>(&length), sizeof(length));
		ofs.write(nome.c_str(), length);
		ofs.write(reinterpret_cast<const char*>(&custo), sizeof(custo));
		ofs.write(reinterpret_cast<const char*>(&preco), sizeof(preco));
		ofs.write(reinterpret_cast<const char*>(&horas), sizeof(horas));
	}
	void carregar(std::ifstream& ifs) {
		size_t length = nome.size();
		ifs.read(reinterpret_cast<char*>(&length), sizeof(length));
		nome.resize(length);
		ifs.read(&nome[0], length);
		ifs.read(reinterpret_cast<char*>(&custo), sizeof(custo));
		ifs.read(reinterpret_cast<char*>(&preco), sizeof(preco));
		ifs.read(reinterpret_cast<char*>(&horas), sizeof(horas));
	}
    
};



inline void Jogo::calcular()
{
	if (horas > 0)
		custo = preco / horas;
	else {
		custo = preco;
	}
}

inline const Jogo& Jogo::comparar(const Jogo& jogo, const Jogo& (Jogo::* func)(const Jogo&) const) const {
	return (this->*func)(jogo);
}

inline const Jogo& Jogo::MaisJogado(const Jogo& jogo) const {
	if (jogo.horas > this->horas) {
		return jogo;
	}
	else {
		return  *this;
	}
}


	inline const Jogo& Jogo::MenorCusto(const Jogo & jogo) const {
		if (jogo.custo < this->custo) {
			return jogo;
		}
		else {
			return  *this;
		}


}


	inline const Jogo& Jogo::MenorPreco(const Jogo& jogo) const {
		if (jogo.preco < this->preco) {
			return jogo;
		}
		else {
			return  *this;
		}


	}



#endif