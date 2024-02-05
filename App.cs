using System;
using System.Drawing;
using System.Windows.Forms;

public static class App {
    private static Form window;
    private static Panel canvas;

    public static void Main() {
        window = new Form {
            Text = "Mi Ventana",
            Size = new Size(1280, 720)
        };
        canvas = new Panel {
            Size = new Size(192, 108),
            Location = new Point(50, 50)
        };
        window.Controls.Add(canvas);

        Timer timer = new Timer();
        timer.Interval = 16;
        timer.Tick += (sender, e) => update();
        timer.Start();

        Application.Run(window);
    }

    private static void update() {
        using (Graphics g = canvas.CreateGraphics()) {
            g.Clear(Color.Black);
            int squareSize = 20;
            int x = (canvas.Width - squareSize) / 2;
            int y = (canvas.Height - squareSize) / 2;
            g.FillRectangle(Brushes.White, x, y, squareSize, squareSize);
        }
    }
}