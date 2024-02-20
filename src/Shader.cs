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
vec3 skycolor = new vec3(1,1,1);
vec3 pcolor = new vec3(0,0,0);
vec3 multiplier = new vec3(1,1,1);

const int bounces = 20;
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
            vec3 col = (multiplier*skycolor*pcolor);
            App.window.pixel[index].color = Color.FromArgb(255,(int)col.x,(int)col.y,(int)col.z);
            break;
        }
    }
    else {
        vec3 normal = (currentr.f(time[t]) - App.sphere[t].position).unit();
        float bright = normal.dot(App.light.normal); 

        vec3 col = (bright>0?new vec3(bright,bright,bright):new vec3(0,0,0))*App.sphere[t].material.color*skycolor*multiplier;
        pcolor = col;

        App.window.pixel[index].color = Color.FromArgb(255,(int)col.x,(int)col.y,(int)col.z);

        //float dotp = 2*currentr.direction.dot(normal);
        //currentr.direction = currentr.direction-normal*new vec3(dotp,dotp,dotp);

        vec3 difusion = new vec3(1,1,1);
        if(App.sphere[t].material.roughnes>0){
            difusion = new vec3(
                (float) new Random().Next((int)App.sphere[t].material.roughnes),
                (float) new Random().Next((int)App.sphere[t].material.roughnes),
                (float) new Random().Next((int)App.sphere[t].material.roughnes)
            ).unit();
        }

        currentr.origin = currentr.f(time[t]) + normal;
        currentr.direction = (difusion*currentr.direction + normal+normal);
        
        if(j>0)
            multiplier = multiplier*new vec3(0.9f,0.9f,0.9f);
    }
}

}
};