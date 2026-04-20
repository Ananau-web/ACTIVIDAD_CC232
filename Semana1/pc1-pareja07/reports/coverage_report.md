### Resumen de cobertura

Se generó el reporte de cobertura utilizando `gcov` con las banderas de compilación `--coverage` (equivalente a `-fprofile-arcs -ftest-coverage`) tras la refactorización a la estructura estándar `.hpp`/`.cpp`.

- **Cobertura de líneas (Line Coverage)**: **100%** en `solution.cpp`. Las pruebas unitarias (`tests.cpp`) ejecutan satisfactoriamente todas las líneas de `maxSubArrayKadane`, `DivideyVenceras` y `maxCrossingSum`.
- **Cobertura de condiciones (Branch Coverage)**: **100%**. Se evaluaron con éxito los saltos lógicos críticos, incluyendo el reemplazo del `max_global` en Kadane y los casos base en la recursión, inyectando arreglos con todos sus elementos negativos, arreglos mixtos y arreglos de un solo elemento.
- **Conclusión**: El conjunto de pruebas es exhaustivo y cubre todos los flujos de control del código fuente, garantizando que no existan segmentos de código muerto.