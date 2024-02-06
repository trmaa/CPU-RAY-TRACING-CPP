using System;
using System.Drawing;

public class Camara {
    public vec3 position = new vec3(0,0,0);
    public vec2 angle = new vec2(0,(float)Math.PI/2);

    public float fov = 50;
    public float near = 5;

    public Ray[] ray;

    public Controler controls = new Controler();

    public Camara(){
        this.ray = new Ray[App.window.pixel.Length];

        foreach (var p in App.window.pixel) {
            this.ray[(int)(p.id.x + p.id.y * App.window.viewport.x)] = new Ray(
                this.position,//xcosay zsinay ycosax
                new vec3(
                    (float)((p.id.x-App.window.viewport.x*0.5)/this.fov),
                    (float)((p.id.y-App.window.viewport.y*0.5)/this.fov), 
                    this.near
                )
            );
        }
    }

    public void shader(Graphics g,vec2 id){
        Ray currentr = this.ray[(int)(id.x+id.y*App.window.viewport.x)];

        App.window.print(g, Color.FromArgb(255, 150, 0, 255), App.camara.project(currentr.direction+currentr.origin), new vec2((1280 / App.camara.distance(currentr.direction+currentr.origin) * 0.1f), (1280 / App.camara.distance(currentr.direction+currentr.origin) * 0.1f)));

        float time = Sphere.colision(currentr);
        if(time == 0)
            return;
        else{
            vec3 normal = currentr.f(time) - Sphere.position;
            App.window.pixel[(int)(id.x+id.y*App.window.viewport.x)].color = Color.White;
        }
    }

    public void castRays(vec2 id){
        this.ray[(int)(id.x + id.y * App.window.viewport.x)].origin = new vec3(0,0,0);
        this.ray[(int)(id.x + id.y * App.window.viewport.x)].direction = new vec3(
            (float)(Math.Cos(this.angle.y)*(id.x-App.window.viewport.x*0.5)/this.fov),
            (float)(Math.Cos(this.angle.x)*(id.y-App.window.viewport.y*0.5)/this.fov), 
            (float)Math.Cos(this.angle.y)*this.near
        );
    }

    public float distance(vec3 point){
        return (float)Math.Sqrt(
            Math.Pow(point.x - App.camara.position.x, 2) +
            Math.Pow(point.y - App.camara.position.y, 2) +
            Math.Pow(point.z - App.camara.position.z, 2)
        );
    }

    public vec3 translete(vec3 point) {
        // para angulo y (x,z)
        double a = Math.Atan2(point.x - App.camara.position.x, point.z - App.camara.position.z);
        double b = Math.PI-a-Math.PI/2;
        double c = App.camara.angle.y - Math.PI/2 - b;

        double h = (point.z - App.camara.position.z) / Math.Cos(a);

        // para angulo x (y)
        double d = Math.Atan2(h, point.y - App.camara.position.y);
        double e = Math.PI-d-Math.PI/2;
        double f = App.camara.angle.x - Math.PI/2 - e;

        double i = (point.y - App.camara.position.y) / Math.Cos(d);

        return new vec3(
                (float)(Math.Cos(c) * h),
                (float)(Math.Cos(f) * i),
                (float)(Math.Sin(c) * h));
    }

    public vec2 project(vec3 point) {
        vec3 p = App.camara.translete(point);
        if (p.z <= 0)
            return new vec2(
                    (float)(p.x*(12800/App.camara.distance(point)*0.1f))+(int)(App.window.ClientSize.Width*0.5),
                    (float)(p.y*(12800/App.camara.distance(point)*0.1f))+(int)(App.window.ClientSize.Height*0.5));
        else
            return new vec2(1000, 1000);
    }

    public void move(){
		if(this.controls.wDown){
			this.position.x += (float)Math.Cos(this.angle.y)*0.2f;
			this.position.z += (float)Math.Sin(this.angle.y)*0.2f;
		} 
		if(this.controls.sDown){
			this.position.x -= (float)Math.Cos(this.angle.y)*0.2f;
			this.position.z -= (float)Math.Sin(this.angle.y)*0.2f;
		}
		if(this.controls.dDown){
			this.position.x -= (float)Math.Cos(this.angle.y+Math.PI/2)*0.2f;
			this.position.z -= (float)Math.Sin(this.angle.y+Math.PI/2)*0.2f;
		} 
		if(this.controls.aDown){
			this.position.x += (float)Math.Cos(this.angle.y+Math.PI/2)*0.2f;
			this.position.z += (float)Math.Sin(this.angle.y+Math.PI/2)*0.2f;
		}
		this.position.y += this.controls.eDown?0.2f:0;
		this.position.y -= this.controls.qDown?0.2f:0;

		this.angle.x += this.controls.uArrow?0.02f:0;
		this.angle.x -= this.controls.dArrow?0.02f:0;
		this.angle.y -= this.controls.rArrow?0.02f:0;
		this.angle.y += this.controls.lArrow?0.02f:0;
	}
};
