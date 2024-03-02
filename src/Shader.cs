using System;
using System.Drawing;
using System.Linq;

public class Shader{
public static void update(vec2 id)
{

App.camara.castRays(id);

int index = (int)(id.x+id.y*App.window.viewport.x);
Ray currentr = App.camara.ray[index];

/*App.window.print(g, Color.FromArgb(255, 50, 0, 150), 
    this.project(currentr.direction+currentr.origin), 
    new vec2((64 / this.distance(currentr.direction+currentr.origin) * 0.1f),
        (64 / App.camara.distance(currentr.direction+currentr.origin) * 0.1f)
    )
);*/

App.window.pixel[index].color = Color.Black;
vec3 skycolor = new vec3(0.8f,0.9f,1);
vec3 pcolor = new vec3(255,255,255);

const int bounces = 200;
for(int j = 0;j < bounces;j++){
    float[] time = new float[App.sphere.Length];
    for(int i = 0;i < App.sphere.Length;i++){
        time[i] = App.sphere[i].colision(currentr);
    }
    int t = time.Select((v, i) => new {Value = v, Index = i})
        .Where(pair => pair.Value > 0)
        .OrderBy(pair => pair.Value)
        .Select(pair => pair.Index)
        .FirstOrDefault();

    if(time[t] <= 0){
        if(j<1)
            break;
        else {
            vec3 col = (skycolor*pcolor);
            App.window.pixel[index].color = Color.FromArgb(255,(int)col.x,(int)col.y,(int)col.z);
            break;
        }
    } else {
        vec3 normal = (currentr.f(time[t]) - App.sphere[t].position).unit();

        vec3 col = App.sphere[t].material.color*skycolor;
        pcolor = col.unit()*pcolor;

        App.window.pixel[index].color = Color.FromArgb(255,(int)col.x,(int)col.y,(int)col.z);

        int threshold = 4;
        vec3 difusion = new vec3(1,1,1);
        if(App.sphere[t].material.roughnes>0 && j <= threshold){
            difusion = new vec3(
                (float) new Random().Next((int)App.sphere[t].material.roughnes),
                (float) new Random().Next((int)App.sphere[t].material.roughnes),
                (float) new Random().Next((int)App.sphere[t].material.roughnes)
            );
        }

        currentr.origin = currentr.f(time[t]) + normal;
        currentr.direction = (difusion*currentr.direction.unit() + 2*normal.unit());
    }
}

}
};