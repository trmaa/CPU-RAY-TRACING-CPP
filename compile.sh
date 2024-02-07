#!/bin/bash

commit() {
    read -p "¿Quieres comitear? (N/y): " choice
    choice=${choice,,}

    if [ "$choice" == "y" ]; then
        read -p "Título del commit: " msg
        msg=${msg,,}
        echo "ADD"
        git add .
        echo "COMMIT"
        git commit -m "$msg"
        echo "PUSH"
        git push
    else
        echo "No se ha borrado el ejecutable."
    fi
}

compile() {
    mcs -out:renderer.exe -r:System.Windows.Forms.dll -r:System.Drawing.dll *.cs

    if [ $? -eq 0 ]; then
        echo "Compilación exitosa. Ejecutando..."
        mono "$(pwd)/renderer.exe"

        commit
    else
        echo "Error durante la compilación."
    fi
}

clear
compile