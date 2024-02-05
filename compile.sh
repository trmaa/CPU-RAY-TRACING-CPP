#!/bin/bash

delete() {
  read -p "¿Quieres borrar el ejecutable? (N/y): " choice
  choice=${choice,,}

  if [ "$choice" == "y" ]; then
    rm Magyk.exe
    echo "Ejecutable borrado."
  else
    echo "No se ha borrado el ejecutable."
  fi
}

compile() {
  mcs -out:Magyk.exe -r:System.Windows.Forms.dll -r:System.Drawing.dll *.cs

  if [ $? -eq 0 ]; then
    echo "Compilación exitosa. Ejecutando..."
    mono "$(pwd)/Magyk.exe"

    delete
  else
    echo "Error durante la compilación."
  fi
}

clear
compile