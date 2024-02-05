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

	public void print(Graphics g,Color col,vec2 p,vec2 size){
		g.FillRectangle(new SolidBrush(col), p.x, p.y, size.x, size.y);
	}

	public void repaint(Graphics g) {
	    g.Clear(Color.Black);

	    foreach(var p in this.pixel){
	        this.print(g,p.color, p.id, new vec2(1, 1));
	    }

	    // Utiliza la función print para imprimir los rectángulos
	    this.print(g,Color.FromArgb(255, 255, 0, 255), App.camara.project(new vec3(1, 1, 5)), new vec2(10, 10));
	    this.print(g,Color.FromArgb(255, 255, 0, 255), App.camara.project(new vec3(-1, 1, 5)), new vec2(10, 10));
	    this.print(g,Color.FromArgb(255, 255, 0, 255), App.camara.project(new vec3(1, -1, 5)), new vec2(10, 10));
	    this.print(g,Color.FromArgb(255, 255, 0, 255), App.camara.project(new vec3(-1, -1, 5)), new vec2(10, 10));

	    this.print(g,Color.FromArgb(255, 255, 0, 255), App.camara.project(new vec3(1, 1, 4)), new vec2(15, 15));
	    this.print(g,Color.FromArgb(255, 255, 0, 255), App.camara.project(new vec3(-1, 1, 4)), new vec2(15, 15));
	    this.print(g,Color.FromArgb(255, 255, 0, 255), App.camara.project(new vec3(1, -1, 4)), new vec2(15, 15));
	    this.print(g,Color.FromArgb(255, 255, 0, 255), App.camara.project(new vec3(-1, -1, 4)), new vec2(15, 15));
	}
};