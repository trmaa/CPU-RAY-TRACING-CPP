using System;
using System.Drawing;
using System.Linq;

public class Camara {
    public vec3 position = new vec3(0,10,-100);
    public vec3 angle = new vec3(0,(float)Math.PI*0.5f,0);
    public vec3 direction = new vec3(0,0,1);

    public float fov = 50;
    public float near = 2;

    public Ray[] ray;

    public Controler controls = new Controler();
    public bool moving = false;

    public Camara(){
        float scalefactor = App.window.viewport.x/128;

        this.fov = (100-App.window.aspectratio.x*this.fov/50);
        this.near = this.fov/(scalefactor>3?(100+(70/2)-(70/2)*scalefactor):30);
        
        this.ray = new Ray[App.window.pixel.Length];

        foreach (Pixel p in App.window.pixel) {
            int index = (int)(p.id.x + p.id.y * App.window.viewport.x);
            this.ray[index] = new Ray(
                this.position,//xcosay zsinay ycosax
                new vec3(
                    (float)((p.id.x-App.window.viewport.x*0.5)/this.fov),
                    (float)((p.id.y-App.window.viewport.y*0.5)/this.fov), 
                    (float)this.near
                ).unit()
            );
        }
    }

    public void castRays(vec2 id){
        int index = (int)(id.x+id.y*App.window.viewport.x);

        vec3 angTarg = this.ray[index].idleA+this.angle;

        vec3 targuet = new vec3(
            this.ray[index].idleD.z*(float)Math.Cos(angTarg.y)*(float)Math.Cos(angTarg.x),
            this.ray[index].idleD.z*(float)Math.Sin(angTarg.x),
            this.ray[index].idleD.z*(float)Math.Cos(angTarg.x)*(float)Math.Sin(angTarg.y)
        ).unit();

        this.ray[index].origin = this.position;
        this.ray[index].direction = (this.ray[index].idleD.unit().z*targuet).unit();
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

    public void move() {
        float speed = 50.0f;
        
        float x = (float)(Math.Cos(angle.y)*Math.Cos(angle.x));
        float y = (float)Math.Sin(angle.x);
        float z = (float)(Math.Sin(angle.y)*Math.Cos(angle.x));

        this.direction = new vec3(x, y, z).unit();

        if (controls.wDown) {
            position.x += (float)Math.Cos(angle.y) * speed * App.deltaTime;
            position.z += (float)Math.Sin(angle.y) * speed * App.deltaTime;
        }
        if (controls.sDown) {
            position.x -= (float)Math.Cos(angle.y) * speed * App.deltaTime;
            position.z -= (float)Math.Sin(angle.y) * speed * App.deltaTime;
        }
        if (controls.dDown) {
            position.x -= (float)Math.Cos(angle.y + Math.PI / 2) * speed * App.deltaTime;
            position.z -= (float)Math.Sin(angle.y + Math.PI / 2) * speed * App.deltaTime;
        }
        if (controls.aDown) {
            position.x += (float)Math.Cos(angle.y + Math.PI / 2) * speed * App.deltaTime;
            position.z += (float)Math.Sin(angle.y + Math.PI / 2) * speed * App.deltaTime;
        }
        position.y += controls.eDown ? speed * App.deltaTime : 0;
        position.y -= controls.qDown ? speed * App.deltaTime : 0;

        angle.x += controls.uArrow ? 0.5f * App.deltaTime : 0;
        angle.x -= controls.dArrow ? 0.5f * App.deltaTime : 0;
        angle.y += controls.lArrow ? 0.5f * App.deltaTime : 0;
        angle.y -= controls.rArrow ? 0.5f * App.deltaTime : 0;
    }
};
