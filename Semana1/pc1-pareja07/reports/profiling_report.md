### Resumen de profiling

Se ejecutó profiling usando `gprof` en el ejecutable compilado con `-pg`, utilizando un vector de prueba generado aleatoriamente con **N = 100,000** elementos.

- **Función que concentra más tiempo**: El análisis revela que en el enfoque de "Divide y Vencerás", la función `maxCrossingSum` y las llamadas recursivas de `DivideyVenceras` concentran el mayor porcentaje del tiempo de CPU debido a la profundidad de la pila de recursión y las iteraciones anidadas. Por el contrario, la función `maxSubArrayKadane` consume una fracción de tiempo casi imperceptible.
- **Coincide con el análisis de complejidad**: Sí. El profiling confirma experimentalmente que Kadane $O(N)$ es órdenes de magnitud más eficiente en tiempo real que Divide y Vencerás $O(N \log N)$ para entradas masivas (N > $10^4$).
- **Conclusión**: El cuello de botella en sistemas de alto rendimiento para este problema es la recursividad. La iteración in-place de Kadane maximiza la localidad de caché, explicando su aplastante superioridad en el profiling.