using System;
using System.Windows.Forms;
using System.Diagnostics;

public class App {
    public static Window window = new Window("Renderer",new vec2(1280,720));
    public static Camara camara;

    public static float deltaTime;
    public static Stopwatch stopwatch = new Stopwatch();

    public static Light light = new Light(new vec3(-1,-2,3));
    public static Sphere[] sphere = {
        new Sphere(new vec3(0,8,15*2),20,new vec3(255,0,0)),
        new Sphere(new vec3(20*2,20,20*2),5,new vec3(0,255,0)),
        new Sphere(new vec3(-10*2,25,-10*2),15,new vec3(0,0,255)),
        new Sphere(new vec3(0,-120,20*2),105,new vec3(255,255,255))
    };

    public static void Main() {
        App.camara = new Camara();

        Timer timer = new Timer();
        timer.Interval = 16;
        timer.Tick += (sender, e) => App.update();
        timer.Start();

        App.stopwatch.Start();
        Application.Run(App.window);
    }

    private static void update(){
        App.deltaTime = (float)App.stopwatch.Elapsed.TotalSeconds;
        App.stopwatch.Restart();

        App.camara.move();
        
        //App.light.orbit();
        //App.sphere[1].orbit();

        App.window.Invalidate();
    }
};