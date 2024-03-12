using System;
using System.Drawing;
using System.Linq;

public class Shader{
public static void update(vec2 id)
{

App.camara.castRays(id);

int index = (int)(id.x+id.y*App.window.viewport.x);
Ray currentr = App.camara.ray[index];


App.window.pixel[index].color = Color.Black;
vec3 skycolor = new vec3(0.8f,0.9f,1);
vec3 pcolor = new vec3(255,255,255);
float importance = 1;

const int bounces = 50;
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
        if(j<1){
            App.window.pixel[index].color = Color.Black;
            break;
        } else {
            vec3 col = (skycolor*pcolor);
            App.window.pixel[index].color = Color.FromArgb(255,(int)col.x,(int)col.y,(int)col.z);
            break;
        }
    } else {
        vec3 normal = (currentr.f(time[t]) - App.sphere[t].position).unit();

        vec3 col = (1/255)*(App.sphere[t].material.color*skycolor);
        pcolor = importance*col*pcolor;

        App.window.pixel[index].color = Color.FromArgb(255,(int)col.x*255,(int)col.y*255,(int)col.z*255);

        Random rand = new Random();
        int threshold = 4;
        vec3 difusion = new vec3(0,0,0);
        if(App.sphere[t].material.roughnes!=0 && j <= threshold){
            difusion = new vec3(
                (float) rand.NextDouble()*App.sphere[t].material.roughnes*2-App.sphere[t].material.roughnes,
                (float) rand.NextDouble()*App.sphere[t].material.roughnes*2-App.sphere[t].material.roughnes,
                (float) rand.NextDouble()*App.sphere[t].material.roughnes*2-App.sphere[t].material.roughnes
            );
        }

        currentr.origin = currentr.f(time[t]) + normal;
        currentr.direction = (currentr.direction - 2*currentr.direction.dot(normal)*normal)+difusion;

        importance*=0.9f;
    }
}

}
};