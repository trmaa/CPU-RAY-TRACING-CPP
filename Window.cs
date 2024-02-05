using System;
using System.IO;
using System.Drawing;
using System.Windows.Forms;

public class Window : Form {
	public Pixel[] pixel;

	public Window(String title,vec2 size){
		this.Text = title;
        this.Size = new Size((int)size.x, (int)size.y);

        this.Paint += (sender, e) => repaint(e.Graphics);

        this.pixel = new Pixel[(int)size.x * (int)size.y];
        for(int y = 0;y < size.y;y++){
        	for(int x = 0;x < size.x;x++){
        		this.pixel[x+y*(int)size.x] = new Pixel(Color.FromArgb(255,(int)(255*y/size.y),(int)(255*x/size.x),0),new vec2(x,y));
        	}
        }
	}

	public void repaint(Graphics g) {
        g.Clear(Color.Black);

        foreach(var p in this.pixel){
            g.FillRectangle(new SolidBrush(p.color), p.id.x, p.id.y, 1, 1);
        }
    }
};