#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "Start.h"
#include "GameExeption.h"

int main() {
        try {
            // Остальной код внутри main без изменений
            Start T;
            T.star_play();
        }
        catch (const GameException& ex) {
            std::cerr << "Game Exception: " << ex.what() << std::endl;
        }
        catch (const std::exception& ex) {
            std::cerr << "Exception: " << ex.what() << std::endl;
        }
        catch (...) {
            std::cerr << "Unknown exception occurred!" << std::endl;
        }

        return 0;
    }

    


