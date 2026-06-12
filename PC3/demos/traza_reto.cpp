#include "XorManager.h"
#include <iostream>

int main() {
    std::cout << "Traza de insercion/eliminacion con pares vecinos\n\n";

    XorManager xm(true);

    std::cout << "insert(10) -> solo 1 elemento, minXor = "
              << (xm.insert(10), xm.getMinXor()) << " (no hay par)\n";

    xm.insert(2);
    std::cout << "insert(2) -> par formado: 2 XOR 10 = " << (2 ^ 10)
              << ", minXor = " << xm.getMinXor() << "\n";

    std::cout << "\ninsert(5) va entre 2 y 10:\n";
    std::cout << "  par (2,10) xor=" << (2 ^ 10) << " queda obsoleto\n";
    xm.insert(5);
    std::cout << "  par nuevo (2,5) xor=" << (2 ^ 5) << "\n";
    std::cout << "  par nuevo (5,10) xor=" << (5 ^ 10) << "\n";
    std::cout << "  minXor = " << xm.getMinXor() << " (es 7 = 2 xor 5)\n";

    std::cout << "\ninsert(7) va entre 5 y 10:\n";
    std::cout << "  par (5,10) xor=" << (5 ^ 10) << " queda obsoleto\n";
    xm.insert(7);
    std::cout << "  par nuevo (5,7) xor=" << (5 ^ 7) << "\n";
    std::cout << "  par nuevo (7,10) xor=" << (7 ^ 10) << "\n";
    std::cout << "  minXor = " << xm.getMinXor() << " (es 2 = 5 xor 7)\n";

    std::cout << "\nerase(5):\n";
    std::cout << "  pares (2,5) xor=" << (2 ^ 5) << " y (5,7) xor=" << (5 ^ 7) << " quedan obsoletos\n";
    xm.erase(5);
    std::cout << "  par restaurado (2,7) xor=" << (2 ^ 7) << "\n";
    std::cout << "  minXor = " << xm.getMinXor() << " (es 5 = 2 xor 7)\n";

    std::cout << "\ninsert(7) de nuevo (duplicado):\n";
    std::cout << "  freq[7] pasa a 2, treap no cambia\n";
    std::cout << "  se inserta 0 al heap (7 xor 7 = 0)\n";
    xm.insert(7);
    std::cout << "  minXor = " << xm.getMinXor() << " (es 0 por el duplicado)\n";

    std::cout << "\nerase(7) una instancia:\n";
    xm.erase(7);
    std::cout << "  freq[7] pasa a 1, el 0 se marca obsoleto\n";
    std::cout << "  minXor = " << xm.getMinXor() << " (vuelve a 5 = 2 xor 7)\n";

    return 0;
}
