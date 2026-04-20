### Tabla resumida de builds y resultados (N = 1,000,000)

| Build | Flags | Tiempo Ejecución (Kadane) | Tiempo Ejecución (Divide & Conquer) | Observaciones |
|-------|-------|---------------------------|-------------------------------------|---------------|
| Depuración | `-O0` | 5.736 ms | 93.993 ms | Sin optimizaciones. El *overhead* de la pila de recursión es masivo. |
| Release | `-O2` | 2.345 ms | 37.645 ms | Aceleración drástica. El compilador vectoriza y desenrolla bucles (*loop unrolling*). |
| Compacto | `-Os` | 1.530 ms | 51.785 ms | Prioriza tamaño del binario. Rendimiento excelente en iteración secuencial (Kadane), posiblemente por un mejor encaje en Caché L1. |
| Profiling | `-O2 -pg` | 0.000 ms | 50.997 ms | Instrumentado para `gprof`. Kadane fue tan rápido que no registró ni 1 milisegundo. |

### Observaciones de sanitizers

Se ejecutó el build `main_app_san.exe` compilado explícitamente con `-fsanitize=address,undefined`. 
**Evidencia de salida:**
```text
=================================================================
== AddressSanitizer: no leaks found
== UndefinedBehaviorSanitizer: no undefined behavior detected
=================================================================