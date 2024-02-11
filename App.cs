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
        new Sphere(new vec3(0,0,10),10,new vec3(255,0,0)),
        new Sphere(new vec3(20,20,20),5,new vec3(0,255,0)),
        new Sphere(new vec3(-10,25,-10),15,new vec3(0,0,255))
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
        foreach(var s in App.sphere){
            //s.orbit();
        }
        App.window.Invalidate();
    }
};