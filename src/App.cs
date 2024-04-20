using System;
using System.Windows.Forms;
using System.Diagnostics;

public class App {
    public static Window window = new Window("Renderer",new vec2(192,108));
    public static Camara camara;

    public static float deltaTime;
    public static Stopwatch stopwatch = new Stopwatch();

    public static Light light = new Light(new vec3(-20,-10,20));
    public static Sphere[] sphere = {
        new Sphere(new vec3(0,-1000,0),1000,new vec3(50,255,50)),
        new Sphere(new vec3(0,11,0),10,new vec3(255,255,255)),
        new Sphere(new vec3(21,11,0),10,new vec3(255,50,50)),
        new Sphere(new vec3(-21,11,0),10,new vec3(50,70,255)),
        new Sphere(new vec3(1200,1200,0),1150,new vec3(200,255,255)),
        new Sphere(new vec3(-1300,0,1200),1000,new vec3(255,50,70))
    };

    public static void Main() {
        App.sphere[1].material.roughnes = 1;
        App.sphere[3].material.roughnes = 10;
        App.sphere[3].material.emission = 1;
        App.sphere[4].material.emission = 1;
        App.sphere[5].material.emission = 1;
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
        
        //App.sphere[5].orbit();

        App.window.Invalidate();
    }
};
