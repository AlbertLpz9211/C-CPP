# Presentación

`paso-de-argumentos-y-arreglos.odp` — LibreOffice Impress, 16:9, 92
diapositivas, con **notas del orador en cada una**: qué decir, qué preguntar al
grupo y qué ejemplo ejecutar.

`paso-de-argumentos-y-arreglos.pdf` — la misma presentación exportada, por si
en el aula no hay LibreOffice.

## Cómo ver las notas al exponer

En Impress: **Ver → Notas** para editarlas, y **Presentación → Presentación con
pantalla de notas** (o conectar el proyector y activar *Presenter Console*) para
verlas durante la exposición mientras el público ve solo la diapositiva.

## Cómo regenerarla

La presentación se construye con un script, de modo que se puede corregir el
contenido sin pelear con el editor:

```sh
python3.12 generar_presentacion.py
```

- `slide_kit.py` — la maquetación: portada, separadores de sección, viñetas,
  bloques de código con resaltado, tablas, citas a pantalla completa,
  diapositivas de demostración y de práctica.
- `generar_presentacion.py` — el contenido, escrito como un guion. Cada
  diapositiva lleva su texto de notas al lado.

El script produce `.pptx` con python-pptx y lo convierte a `.odp` y `.pdf` con
LibreOffice en modo headless. Requiere `python-pptx` y LibreOffice instalados.

Si editas la presentación a mano en Impress, ten en cuenta que volver a
ejecutar el script **sobrescribe** el archivo.
