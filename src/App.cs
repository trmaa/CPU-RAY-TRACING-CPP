using System;
using System.Windows.Forms;
using System.Diagnostics;

public class App {
    public static Window window = new Window("Renderer",new vec2(192,108));
    public static Camara camara;

    public static float deltaTime;
    public static Stopwatch stopwatch = new Stopwatch();

    public static Light light = new Light(new vec3(-20,-10,20));

    public static void Main() {
        Scene.start();
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
