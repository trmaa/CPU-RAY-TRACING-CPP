using System;
using System.Drawing;
using System.Windows.Forms;

public static class App {
    private static Form window;
    private static int squareSize = 20;

    public static void Main() {
        window = new Form {
            Text = "Mi Ventana",
            Size = new Size(1280, 720)
        };

        window.Paint += (sender, e) => paintCanvas(e.Graphics);

        Timer timer = new Timer();
        timer.Interval = 16;
        timer.Tick += (sender, e) => update();
        timer.Start();

        Application.Run(window);
    }

    private static void paintCanvas(Graphics g) {
        g.Clear(Color.Black);

        int x = (window.ClientSize.Width - squareSize) / 2;
        int y = (window.ClientSize.Height - squareSize) / 2;
        g.FillRectangle(Brushes.White, x, y, squareSize, squareSize);
    }

    private static void update() {
        window.Invalidate(); // Solicita una actualización de la ventana
    }
}