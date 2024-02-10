using System;
using System.Windows.Forms;

public class App {
    public static Window window = new Window("Renderer",new vec2(1280,720));
    public static Camara camara;

    public static Light light = new Light(new vec3(-1,-2,0));
    public static Sphere[] sphere = {
        new Sphere(new vec3(0,0,10),10),
        new Sphere(new vec3(20,20,20),5),
        new Sphere(new vec3(-10,25,-10),15)
    };

    public static void Main(){
        App.camara = new Camara();

        Timer timer = new Timer();
        timer.Interval = 16;
        timer.Tick += (sender, e) => update();
        timer.Start();
    
        Application.Run(window);
    }

    private static void update(){
        App.camara.move();
        App.light.orbit();
        App.window.Invalidate();
    }
};