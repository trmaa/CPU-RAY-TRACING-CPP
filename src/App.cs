using System;
using System.Windows.Forms;
using System.Diagnostics;

public class App {
    public static Window window = new Window("Renderer",new vec2(1280,720));
    public static Camara camara;

    public static float deltaTime;
    public static Stopwatch stopwatch = new Stopwatch();

    public static Sphere[] sphere = {
        new Sphere(new vec3(0,-1000,0),1000,new vec3(100,255,100)),
        new Sphere(new vec3(0,11,0),10,new vec3(255,255,255)),
        new Sphere(new vec3(21,11,0),10,new vec3(255,50,50)),
        new Sphere(new vec3(-21,11,0),10,new vec3(50,50,255))
    };

    public static void Main() {
        App.sphere[1].material.roughnes = 10;
        App.sphere[2].material.roughnes = 0;
        App.sphere[3].material.roughnes = 0;
        App.camara = new Camara();

        Timer timer = new Timer();
        timer.Interval = 160;
        timer.Tick += (sender, e) => App.update();
        timer.Start();

        App.stopwatch.Start();
        Application.Run(App.window);
    }

    private static void update(){
        App.deltaTime = (float)App.stopwatch.Elapsed.TotalSeconds;
        App.stopwatch.Restart();

        App.camara.move();
        
        //App.sphere[2].orbit();
        //App.sphere[3].orbit();

        App.window.Invalidate();
    }
};