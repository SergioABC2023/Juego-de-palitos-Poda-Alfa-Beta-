#include <iostream>
#include <climits>

// Función para mostrar el tablero
void mostrarTablero(int palitos) {
    std::cout << "Palitos restantes: " << palitos << std::endl;
    for (int i = 0; i < palitos; ++i) {
        std::cout << "| ";
    }
    std::cout << std::endl;
}

// Función para determinar el ganador
bool Ganador(int palitos) {
    return palitos == 0;
}

// Función para evaluar el estado del juego
int evaluarEstado(int palitos, bool Jugador) {
    if (Ganador(palitos)) {
        if (Jugador) {
            return 1;
        } else {
            return -1;
        }
    }
    return 0;
}

//Algoritmo Minimax con poda alfa-beta
int minimax(int palitos, int profundidad, int alfa, int beta, bool Jugador) {
    int estado = evaluarEstado(palitos, Jugador);

    if (profundidad == 0 || estado != 0) {
        return estado;
    }

    if (Jugador) {
        int mejorValor = INT_MIN;

        for (int i = 1; i <= 3; ++i) {
            if (palitos >= i) {
                int valor = minimax(palitos - i, profundidad - 1, alfa, beta, false);
                mejorValor = std::max(mejorValor, valor);
                alfa = std::max(alfa, valor);
                if (beta <= alfa) {
                    break;
                }
            }
        }

        return mejorValor;
    } else {
        int mejorValor = INT_MAX;

        for (int i = 1; i <= 3; ++i) {
            if (palitos >= i) {
                int valor = minimax(palitos - i, profundidad - 1, alfa, beta, true);
                mejorValor = std::min(mejorValor, valor);
                beta = std::min(beta, valor);
                if (beta <= alfa) {
                    break;
                }
            }
        }
        return mejorValor;
    }
}

// Función para que la IA haga su turno
int MovimientoIA(int palitos) {
    int mejorValor = INT_MIN;
    int mejorMovimiento = 0;

    for (int i = 1; i <= 3; ++i) {
        if (palitos >= i) {
            int valor = minimax(palitos - i, 8, INT_MIN, INT_MAX, false);
            if (valor > mejorValor) {
            mejorValor = valor;
            mejorMovimiento = i;
        }
    }
}
return mejorMovimiento;
}

int main() {
int palitos = 15;
int profundidad = 8; // Profundidad máxima para el algoritmo Minimax
int palitosEliminados;

while (!Ganador(palitos)) {
    mostrarTablero(palitos);


    std::cout << "Ingresa el numero de palitos para eliminar (1-3): ";
    std::cin >> palitosEliminados;


    while (palitosEliminados < 1 || palitosEliminados > 3 || palitosEliminados > palitos) {
        std::cout << "Movimiento invalido. Ingresa el numero de palitos para eliminar (1-3): ";
        std::cin >> palitosEliminados;
    }

    palitos -= palitosEliminados;

    if (Ganador(palitos)) {
        std::cout << std::endl;
        std::cout << "La IA ha ganado" << std::endl;
        break;
    }


    std::cout << "Turno de la IA" << std::endl;
    palitosEliminados = MovimientoIA(palitos);
    std::cout << "La IA ha eliminado " << palitosEliminados << " palitos." << std::endl;
    palitos -= palitosEliminados;

    if (Ganador(palitos)) {
        std::cout << std::endl;
        std::cout << "El Jugador ha ganado." << std::endl;
        break;
    }
}

return 0;
}
