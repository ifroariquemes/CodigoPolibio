#include <cstdlib>
#include <cstring>
#include <iostream>
#include <ctype.h>

using namespace std;

char* mensagem;
int cripto = -1;
char alfabeto[] = "ABCDEFGHIJKLMNOPRSTUVWXYZ";
int posicoes[25];

void configuracaoErrada() {
    cout << "Configuração mal realizada. Por favor, utilize a opção -h.";
}

void mostrarAjuda() {
    cout << "---- Instituto Federal de Rondônia - Campus Ariquemes ----" << endl;
    cout << "Criptografa e decriptografa mensagens usando Código de Políbio" << endl;
    cout << "N. A. V. Simões <natanael.simoes@ifro.edu.br>" << endl;
    cout << "http://github.com/ifroariquemes/CodigoPolibio" << endl << endl;
    cout << "Uso:" << endl << endl;
    cout << "      polibio -c|-d mensagem" << endl << endl;
    cout << " -c mensagem      Criptografa uma mensagem" << endl;
    cout << " -d mensagem      Decriptografa uma mensagem" << endl;
    cout << " -h               Mostra essa mensagem" << endl << endl;
    cout << " Criptografar: polibio -c mensagem " << endl;
    cout << " Decriptografar: polibio -d 3315344311221533" << endl;
}

void carregarPosicoes() {
    for (int i = 0; i < 25; i++) {
        if (i < 5) {
            posicoes[i] = 10 + i + 1;
        } else if (i < 10) {
            posicoes[i] = 20 + i - 4;
        } else if (i < 15) {
            posicoes[i] = 30 + i - 9;
        } else if (i < 20) {
            posicoes[i] = 40 + i - 14;
        } else {
            posicoes[i] = 40 + i - 19;
        }
    }
}

void criptografar() {
    for (int i = 0; mensagem[i]; i++) {
        mensagem[i] = toupper(mensagem[i]);
        if (mensagem[i] == 'Q') {
            mensagem[i] = 'K';
        }
        int j = 0;
        while (alfabeto[j] != mensagem[i]) {
            j++;
        }
        cout << posicoes[j];
    }
    cout << endl;
}

void descriptografar() {
    for (int i = 0; mensagem[i]; i++) {
        int posicao = 10 * (int) (mensagem[i] - '0') + (int) (mensagem[++i] - '0');
        int j = 0;
        while (posicoes[j] != posicao) {
            j++;
        }
        cout << alfabeto[j];
    }
    cout << endl;
}

int main(int argc, char** argv) {
    carregarPosicoes();
    for (int i = 0; i < argc; i++) {
        if (argv[i][0] == '-' && argv[i][2] == '\0') { // Parametro chegando
            switch (argv[i][1]) {
                case 'd':
                    mensagem = argv[++i];
                    cripto = 0;
                    break;
                case 'c':
                    mensagem = argv[++i];
                    cripto = 1;
                    break;
                case 'h':
                    if (argc > 2) {
                        configuracaoErrada();
                        return 1;
                    }
                    mostrarAjuda();
                    return 0;
                default:
                    configuracaoErrada();
                    return 1;
            }
        }
    }
    switch (cripto) {
        case -1:
            configuracaoErrada();
            return 1;
            break;
        case 1:
            criptografar();
            break;
        case 0:
            descriptografar();
            break;
    }
    return 0;
}

