#!/bin/bash

echo "<html>"
echo "<head>"
echo "<title>Numero Aleatorio</title>"
echo "<style>"
echo "body {"
echo "    font-family: Arial, sans-serif;"
echo "    background-color: #3498db;"  # Cambio de color de fondo
echo "    margin: 0;"
echo "    padding: 0;"
echo "}"
echo ".container {"
echo "    width: 50%;"
echo "    margin: 50px auto;"
echo "    background-color: #fff;"
echo "    padding: 20px;"
echo "    border-radius: 10px;"
echo "    box-shadow: 0 0 10px rgba(0, 0, 0, 0.3);"  # Cambio de sombra
echo "    text-align: center;"  # Centrar contenido
echo "}"
echo "h1 {"
echo "    color: #333;"
echo "}"
echo "</style>"
echo "</head>"
echo "<body>"
echo "<div class=\"container\">"
echo "<h1>Bienvenido</h1>"
echo "<p>¡Hola! Bienvenido a nuestro sitio web. Aquí tienes un numero aleatorio:</p>"

# Generar un número aleatorio entre 1 y 10
numero_aleatorio=$((RANDOM % 50 + 1))
echo "<p>El numero aleatorio es: $numero_aleatorio</p>"
echo "<p> para ganar un premio, el numero debe ser 42</p>"
if [ $numero_aleatorio -eq 42 ]; then
    echo "<p>Felicidades, has ganado un premio!</p>"
    echo "<p><iframe src="https://giphy.com/embed/Gfw2JsQ9WilQohiEYW" width="356" height="480" frameBorder="0" class="giphy-embed" allowFullScreen></iframe><p></p></p>"
  else
    echo "<p>Lo siento, no has ganado un premio. Inténtalo de nuevo!</p>"
fi
echo "<p><a href=\"/juego.bash\">Generar otro numero</a></p>"

echo "</div>"
echo "</body>"
echo "</html>"

