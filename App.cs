using System;
using System.Windows.Forms;

public class App {
    public static Window window = new Window("Magyk",new vec2(1280,720));
    public static Camara camara = new Camara();

    public static void Main(){
        Application.Run(window);

        Timer timer = new Timer();
        timer.Interval = 16;
        timer.Tick += (sender, e) => update();
        timer.Start();
    }

    private static void update(){
        window.Invalidate();
    }
};