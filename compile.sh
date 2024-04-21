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
    fi
}

compile() {
    mcs -out:renderer.exe -r:libs/OpenTK.dll -r:libs/OpenTK.GLControl.dll -r:System.Windows.Forms.dll -r:System.Drawing.dll ./includes/*.cs ./src/*.cs

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