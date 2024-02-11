using System;
using System.Drawing;
using System.Linq;

public class Camara {
    public vec3 position = new vec3(0,0,-250);
    public vec2 angle = new vec2(0,(float)Math.PI/2);

    public float fov = 50;
    public float near = 2;

    public Ray[] ray;

    public Controler controls = new Controler();

    public Camara(){
        float scalefactor = App.window.viewport.x/128;

        this.fov = (100-App.window.aspectratio.x*this.fov/50);
        this.near = this.fov/(scalefactor>3?(100+(70/2)-(70/2)*scalefactor):30);
        
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
        this.castRays(id);

        int index = (int)(id.x+id.y*App.window.viewport.x);
        Ray currentr = this.ray[index];

        /*App.window.print(g, Color.FromArgb(255, 50, 0, 150), 
            this.project(currentr.direction+currentr.origin), 
            new vec2((64 / this.distance(currentr.direction+currentr.origin) * 0.1f),
                (64 / App.camara.distance(currentr.direction+currentr.origin) * 0.1f)
            )
        );*/

        App.window.pixel[index].color = Color.Black;

        int bounces = 2;
        for(int j = 0;j < bounces;j++){
            float[] time = new float[App.sphere.Length];
            for(int i = 0;i < App.sphere.Length;i++){
                time[i] = App.sphere[i].colision(currentr);
            }
            int t = time.Select((v, i) => new {Value=v,Index=i}).Aggregate(
                (a, b) => {
                    if(a.Value<b.Value&&a.Value>0){
                        return a;
                    } else if(b.Value>0){
                        return b;
                    } else {
                        return a;
                    }
            }).Index;

            if(time[t] <= 0)
                break;
            else {
                vec3 normal = currentr.f(time[t]) - App.sphere[t].position;
                float bright = normal.unit().dot(App.light.normal.unit());

                vec3 col = (bright>0?new vec3(bright,bright,bright):new vec3(0,0,0)) * App.sphere[t].color; 

                App.window.pixel[index].color = Color.FromArgb(255,(int)col.x,(int)col.y,(int)col.z);

                currentr.origin = currentr.f(time[t]) + normal.unit();
                currentr.direction = currentr.direction.unit()*normal.unit();
            }
        }
    }

    public void castRays(vec2 id){
        int index = (int)(id.x+id.y*App.window.viewport.x);

        vec3 init = new vec3(
            (float)((id.x-App.window.viewport.x*0.5)/this.fov),
            (float)((id.y-App.window.viewport.y*0.5)/this.fov), 
            (float)this.near
        );

        float angle = (float)Math.Atan2(init.x,init.z);
        float bngle = (float)Math.Atan2(init.y,init.z);

        float cNear = this.near/(float)Math.Cos(angle);

        angle += this.angle.y;
        bngle += this.angle.x;
        init.z = cNear;

        vec3 targuet = new vec3(
            init.z*(float)Math.Cos(angle),
            init.z*(float)Math.Sin(bngle),
            init.z*(float)Math.Cos(bngle)*(float)Math.Sin(angle)
        );

        this.ray[index].origin = this.position;
        this.ray[index].direction = targuet;
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

        angle.x += controls.uArrow ? 0.5f * App.deltaTime : 0; // Velocidad de rotación ajustable
        angle.x -= controls.dArrow ? 0.5f * App.deltaTime : 0;
        angle.y -= controls.rArrow ? 0.5f * App.deltaTime : 0;
        angle.y += controls.lArrow ? 0.5f * App.deltaTime : 0;
    }
};
