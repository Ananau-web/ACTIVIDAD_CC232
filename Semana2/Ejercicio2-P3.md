#### Ejercicio 3. Modificar `expand()`: crecimiento por constante vs duplicación

En `DengVector`, la expansión sigue la estrategia clásica de duplicar capacidad. Esta decisión está ligada al análisis amortizado.



##### 1 y 2. Crear una variante experimental de `DengVector` en la que `expand()` aumente la capacidad por una constante fija `c`.
Para implementar esta variante, tomamos la estructura base de `DengVector` y modificamos exclusivamente el método `expand()`. En lugar de desplazar los bits a la izquierda (`_capacity <<= 1`, que equivale a duplicar), sumamos una constante fija `c`.

```cpp
#pragma once
#include <cassert>

namespace ods {

template<class T>
class DengVectorConstant {
protected:
    inline static constexpr int DEFAULT_CAPACITY = 3;
    inline static constexpr int EXPANSION_CONSTANT = 5; // Constante 'c'

    int _size;
    int _capacity;
    T* _elem;

    // ... (copyFrom, shrink, constructores y resto de la interfaz pública se mantienen igual) ...

    void expand() {
        if (_size < _capacity) return;
        if (_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;
        
        T* oldElem = _elem;
        // VARIACIÓN: Aumento lineal por constante en lugar de duplicación
        _capacity += EXPANSION_CONSTANT; 
        _elem = new T[_capacity];
        
        for (int i = 0; i < _size; ++i) {
            _elem[i] = oldElem[i];
        }
        delete[] oldElem;
    }
    
    // ... resto del código ...
};

} // namespace ods
```


##### 3. Comparar conceptualmente esta variante con la versión original que duplica capacidad.
Duplicación (Original): Crecimiento geométrico/exponencial ($1, 2, 4, 8\dots$). Las expansiones piden mucha memoria de golpe, volviéndose raras e infrecuentes con el tiempo.Constante Fija (Variante): Crecimiento aritmético/lineal ($c, 2c, 3c\dots$). Obliga a la estructura a pedir memoria y reasignar con una frecuencia fija, sin importar qué tan grande sea el vector.
##### 4. Explicar por qué el crecimiento por constante fija empeora el costo amortizado de inserciones repetidas.
Duplicación: El costo total de expansiones forma una suma geométrica $\Theta(n)$. Al repartirlo entre $n$ operaciones, el costo amortizado por inserción es óptimo: $O(1)$.Crecimiento por Constante: Las expansiones ocurren $\frac{n}{c}$ veces. El costo total de copiar elementos es una suma aritmética ($c + 2c + 3c \dots = O(n^2)$). Repartir $O(n^2)$ entre $n$ inserciones empeora el costo amortizado drásticamente a $O(n)$.
##### 5. Dar un ejemplo de secuencia de inserciones donde esa diferencia se vuelva evidente.
Caso A (Constante, $c = 3$): Expande al 4º elemento (copia 3), al 7º (copia 6) y al 10º (copia 9). Total: 18 copias.Caso B (Duplicación): Expande al 4º elemento (copia 3, capacidad a 6) y al 7º (copia 6, capacidad a 12). Total: 9 copias.Conclusión a escala: Para 10,000 elementos, la duplicación hace ~14 expansiones (copiando ~10,000 elementos en total). La constante $c=3$ requeriría 3,333 expansiones, superando las 16 millones de copias.