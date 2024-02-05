using System;
using System.IO;
using System.Drawing;
using System.Windows.Forms;

public class Window : Form {
	public vec2 viewport;
	public vec2 aspectratio;
	public Pixel[] pixel;

	public Window(String title,vec2 size){
		this.Text = title;
        this.Size = new Size((int)size.x, (int)size.y);

        this.viewport = new vec2(128,72);
        this.aspectratio = size/viewport;

        this.Paint += (sender, e) => repaint(e.Graphics);

        this.pixel = new Pixel[(int)viewport.x * (int)viewport.y];
        for(int y = 0;y < viewport.y;y++){
        	for(int x = 0;x < viewport.x;x++){
        		this.pixel[x+y*(int)viewport.x] = new Pixel(Color.FromArgb(255,(int)(255*y/viewport.y),(int)(255*x/viewport.x),0),new vec2(x,y));
        	}
        }

        this.DoubleBuffered = true;
	}

	public void print(Graphics g,Color col,vec2 p,vec2 size){
		g.FillRectangle(new SolidBrush(col), p.x, p.y, size.x, size.y);
	}

	public void repaint(Graphics g) {
	    g.Clear(Color.Black);

	    foreach(var p in this.pixel){
	    	//definir color con los rayos
	        this.print(g,p.color, p.id*this.aspectratio, this.aspectratio);
	    }

	    this.print(g, Color.FromArgb(255, 255, 0, 255), App.camara.project(new vec3(1, 1, 6)), new vec2((1280 / App.camara.distance(new vec3(1, 1, 6)) * 0.1f), (1280 / App.camara.distance(new vec3(1, 1, 6)) * 0.1f)));
		this.print(g, Color.FromArgb(255, 255, 0, 255), App.camara.project(new vec3(-1, 1, 6)), new vec2((1280 / App.camara.distance(new vec3(-1, 1, 6)) * 0.1f), (1280 / App.camara.distance(new vec3(-1, 1, 6)) * 0.1f)));
		this.print(g, Color.FromArgb(255, 255, 0, 255), App.camara.project(new vec3(1, -1, 6)), new vec2((1280 / App.camara.distance(new vec3(1, -1, 6)) * 0.1f), (1280 / App.camara.distance(new vec3(1, -1, 6)) * 0.1f)));
		this.print(g, Color.FromArgb(255, 255, 0, 255), App.camara.project(new vec3(-1, -1, 6)), new vec2((1280 / App.camara.distance(new vec3(-1, -1, 6)) * 0.1f), (1280 / App.camara.distance(new vec3(-1, -1, 6)) * 0.1f)));

		this.print(g, Color.FromArgb(255, 255, 0, 255), App.camara.project(new vec3(1, 1, 4)), new vec2((1280 / App.camara.distance(new vec3(1, 1, 4)) * 0.1f), (1280 / App.camara.distance(new vec3(1, 1, 4)) * 0.1f)));
		this.print(g, Color.FromArgb(255, 255, 0, 255), App.camara.project(new vec3(-1, 1, 4)), new vec2((1280 / App.camara.distance(new vec3(-1, 1, 4)) * 0.1f), (1280 / App.camara.distance(new vec3(-1, 1, 4)) * 0.1f)));
		this.print(g, Color.FromArgb(255, 255, 0, 255), App.camara.project(new vec3(1, -1, 4)), new vec2((1280 / App.camara.distance(new vec3(1, -1, 4)) * 0.1f), (1280 / App.camara.distance(new vec3(1, -1, 4)) * 0.1f)));
		this.print(g, Color.FromArgb(255, 255, 0, 255), App.camara.project(new vec3(-1, -1, 4)), new vec2((1280 / App.camara.distance(new vec3(-1, -1, 4)) * 0.1f), (1280 / App.camara.distance(new vec3(-1, -1, 4)) * 0.1f)));
	}
};