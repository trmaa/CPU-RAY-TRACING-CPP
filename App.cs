using System;
using System.Windows.Forms;

public class App {
    private static Window window = new Window("Magyk",new vec2(1280,720));

    public static void Main() {
        Timer timer = new Timer();
        timer.Interval = 16;
        timer.Tick += (sender, e) => update();
        timer.Start();

        Application.Run(window);
    }

    private static void update() {
        window.Invalidate();
    }
};